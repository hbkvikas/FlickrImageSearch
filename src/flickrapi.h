#ifndef FLICKRAPI_H
#define FLICKRAPI_H

#include <QtCore>
#include "flickrimageurl.h"
#include "restapi/flickrrestclient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


class FlickrApi : public QObject
{
    Q_OBJECT
private:
    const QString m_apiKey;
public:
    explicit FlickrApi(QString apiKey, QObject *parent = nullptr);
    QString getApiKey() const;
    bool getimageSearchJson(QString url, QString apiKey = "");
    FlickrRestClient *restClient;
    QList<QString> *listImageUrl;

signals:
    void gotImagesUrlList();

public slots:
    void jsonInfoReceived();
};

#endif // FLICKRAPI_H
