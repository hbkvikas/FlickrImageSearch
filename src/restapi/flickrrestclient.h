#ifndef FLICKRRESTCLIENT_H
#define FLICKRRESTCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>


class FlickrRestClient : public QObject
{
    Q_OBJECT
private:
    QString url;
public:
    explicit FlickrRestClient(QString url, QObject *parent = nullptr);
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QByteArray dataBuffer;
    QPixmap *img;

    void get();
    QJsonObject *userJsonInfo;

signals:
    void jsonInfoReceived();

public slots:
    void readData();
    void finishReading();
};

#endif // FLICKRRESTCLIENT_H
