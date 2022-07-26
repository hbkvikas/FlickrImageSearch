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
    int m_currentPage = 1;
    int m_lastPage;
    QString m_searchKey;
    void init();

public:
    Ui::FlickrSearchMainWindow *ui;

public slots:
    void flickrSearch(int pageNumber = 1);
    void loadImage();
    void displayImage(const QString& imgUrl,
                      QImage* image,
                      const QSize &target_size);
    void downloadSetImage(QString imageUrl, QSize sz);

    void viewImage(QListWidgetItem*);

    void goToNextPage();
    void goToPrevPage();
    void goToLastPage();
    void goToFirstPage();


signals:
    void setImage(QString imageUrl, QSize sz);

};
#endif // FLICKRSEARCHMAINWINDOW_H
