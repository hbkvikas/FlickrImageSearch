#include "flickrapi.h"

FlickrApi::FlickrApi(QString apiKey, QObject *parent) :
    QObject{parent},
    m_apiKey(apiKey)
{
    listImageUrl = new QList<QString>();
}

QString FlickrApi::getApiKey() const
{
    return m_apiKey;
}

bool FlickrApi::getimageSearchJson(QString searchKey, int pageNumber, QString apiKey)
{
    if(m_searchKey != searchKey)
    {
        m_totalPagesSet = false;
    }
    m_searchKey = searchKey;
    listImageUrl->clear();
    if(apiKey == "")
        apiKey = getApiKey();

    // url for photo search
    QString url(QString("https://api.flickr.com/services/rest/?method=flickr.photos.search&api_key=%1&format=json&nojsoncallback=1&safe_search=1&text=%2&page=%3") \
                .arg(apiKey) \
                .arg(searchKey)
                .arg(QString::number(pageNumber)));

    qDebug() << "Requested URL: " << url;

    restClient = new FlickrRestClient(url);
    restClient->get();

    connect(restClient, SIGNAL(jsonInfoReceived()), this, SLOT(jsonInfoReceived()));
    return true;
}

void FlickrApi::jsonInfoReceived()
{
    QJsonObject *jsonList = restClient->userJsonInfo;

    auto photoObject = jsonList->value("photos").toObject();

    if(!m_totalPagesSet)
    {
        m_totalPages = photoObject.value("pages").toInt();
        m_totalPagesSet = true;
    }

    auto photosJsonList = photoObject.value("photo").toArray();

    for(auto value: qAsConst(photosJsonList))
    {
        const QString farm = QString::number(value.toObject().value("farm").toInt());
        const QString server = value.toObject().value("server").toString();
        const QString id = value.toObject().value("id").toString();
        const QString secret = value.toObject().value("secret").toString();

        FlickrImageUrl flickrImgUrl(farm,
                                    server,
                                    id,
                                    secret);

        listImageUrl->append(flickrImgUrl.getImageUrl());
    }
    emit gotImagesUrlList();
}

