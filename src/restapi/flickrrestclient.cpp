#include "flickrrestclient.h"

FlickrRestClient::FlickrRestClient(QString url, QObject *parent)
    : QObject{parent}
{
    this->url = url;
}

void FlickrRestClient::readData()
{
    dataBuffer.append(netReply->readAll());
}

void FlickrRestClient::get()
{
    QNetworkRequest req{url};
    netManager = new QNetworkAccessManager(this);
    netReply = netManager->get(req);
    qDebug() << netReply->readBufferSize();

    connect(netReply, &QNetworkReply::readyRead, this, &FlickrRestClient::readData);
    connect(netReply, &QNetworkReply::finished, this, &FlickrRestClient::finishReading);
}

void FlickrRestClient::finishReading()
{
    if(netReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error : " << netReply->errorString();
        QMessageBox::warning(NULL, "Error", QString("Request[Error] : %1").arg(netReply->errorString()));
    }
    else
    {
        //CONVERT THE DATA FROM A JSON DOC TO A JSON OBJECT
        userJsonInfo = new QJsonObject(QJsonDocument::fromJson(dataBuffer).object());
        emit jsonInfoReceived();
    }
}
