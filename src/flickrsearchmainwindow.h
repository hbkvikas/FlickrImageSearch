#ifndef FLICKRSEARCHMAINWINDOW_H
#define FLICKRSEARCHMAINWINDOW_H

#include "flickrapi.h"
#include "imageviewer.h"
#include "filedownloader.h"

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class FlickrSearchMainWindow; }
QT_END_NAMESPACE

class FlickrSearchMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    FlickrSearchMainWindow(QWidget *parent = nullptr);
    ~FlickrSearchMainWindow();
    FlickrApi flickrApi;
    FileDownloader imgDownloader;
    static int counter;

    QMap<QListWidgetItem*, QImage*> m_mpImageList;

    ImageViewer *m_imgViewer;

private:
    QLabel *statusImgUrlLabel;
    void keyPressEvent(QKeyEvent *event) override;

public:
    Ui::FlickrSearchMainWindow *ui;

public slots:
    void flickrSearch();
    void loadImage();
    void displayImage(const QString& imgUrl,
                      QImage* image,
                      const QSize &target_size);
    void downloadSetImage(QString imageUrl, QSize sz);

    void viewImage(QListWidgetItem*);


signals:
    void setImage(QString imageUrl, QSize sz);

};
#endif // FLICKRSEARCHMAINWINDOW_H
