#include "filedownloader.h"
#include "src/flickrsearchmainwindow.h"

#include <QListWidgetItem>
#include <QPainter>

FileDownloader::FileDownloader(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
}

FileDownloader::~FileDownloader()
{
    manager->deleteLater();
}

void FileDownloader::setFile(QString fileURL,
                          const QSize target_size)
{
    m_DownloadedData.clear();
    m_target_size = target_size;
    m_fileUrl = fileURL;

    QNetworkRequest request;
    request.setUrl(QUrl(fileURL));

    request.setRawHeader("User-Agent", userAgent);

    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setProtocol(QSsl::AnyProtocol);
    request.setSslConfiguration(sslConfiguration);

    reply = manager->get(request);
}


void FileDownloader::onFinished(QNetworkReply * reply)
{
    switch(reply->error())
    {
        case QNetworkReply::NoError:
        {
//            qDebug("file is downloaded successfully.");
        }
        break;
        default:
        {
            qDebug(reply->errorString().toLatin1());
        };
    }

    //emit a signal
    reply->deleteLater();
    m_DownloadedData.append(reply->readAll());
    QImage *image = new QImage;
    image->loadFromData(m_DownloadedData);

    emit downloaded(m_fileUrl, image, m_target_size);

}
