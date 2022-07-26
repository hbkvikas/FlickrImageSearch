#include "flickrimageurl.h"

FlickrImageUrl::FlickrImageUrl(const QString &farm,
                               const QString &server,
                               const QString &id,
                               const QString &secret,
                               const QString &owner,
                               const QString &title,
                               const QString &ispublic,
                               const QString &isfriend,
                               const QString &isfamily):
    farm(farm),
    server(server),
    id(id),
    owner(owner),
    secret(secret),
    title(title),
    ispublic(ispublic),
    isfriend(isfriend),
    isfamily(isfamily)
{

}

QString FlickrImageUrl::getImageUrl()
{
    QString imageUrl = QString("https://farm%1.static.flickr.com/%2/%3_%4.jpg") \
                        .arg(farm) \
                        .arg(server) \
                        .arg(id) \
                        .arg(secret);

    return imageUrl;
}
