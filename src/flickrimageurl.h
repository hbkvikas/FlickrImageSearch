#ifndef FLICKRIMAGEURL_H
#define FLICKRIMAGEURL_H

#include <QtCore>

class FlickrImageUrl
{
    QString farm, server, id, owner, secret,
            title, ispublic, isfriend, isfamily;
public:
    FlickrImageUrl(const QString &farm,
                   const QString &server,
                   const QString &id,
                   const QString &secret,
                   const QString &owner = "",
                   const QString &title = "",
                   const QString &ispublic = "",
                   const QString &isfriend = "",
                   const QString &isfamily = "");
    QString getImageUrl();
};

#endif // FLICKRIMAGEURL_H
