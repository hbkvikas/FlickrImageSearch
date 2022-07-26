#include "flickrsearchmainwindow.h"
#include "ui_flickrsearchmainwindow.h"
#include <QSplitter>
#include <QPainter>

int FlickrSearchMainWindow::counter = 0;

FlickrSearchMainWindow::FlickrSearchMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , flickrApi(FlickrApi("63bcddc9a52d56634945477704924a1e")),
      ui(new Ui::FlickrSearchMainWindow)
{
    ui->setupUi(this);

    auto image_spliter = new QSplitter(Qt::Horizontal);
    image_spliter->addWidget(ui->listWidget);
    image_spliter->addWidget(m_imgViewer = new ImageViewer());

    auto main_spliter = new QSplitter(Qt::Vertical);
    main_spliter->addWidget(ui->grpFlickrSearch);
    main_spliter->addWidget(image_spliter);

    m_imgViewer->setHidden(true);

    int w = main_spliter->width();
    main_spliter->setSizes({w / 7, 10 * w / 7});
    setCentralWidget(main_spliter);

    statusImgUrlLabel = new QLabel(this);
    statusBar()->addPermanentWidget(statusImgUrlLabel);
    statusImgUrlLabel->setText("Image Url: None");

    connect(ui->btnFlickrSearch, &QPushButton::clicked, this, &FlickrSearchMainWindow::flickrSearch);
    connect(&flickrApi, &FlickrApi::gotImagesUrlList, this, &FlickrSearchMainWindow::loadImage);
    connect(&imgDownloader, &FileDownloader::downloaded, this, &FlickrSearchMainWindow::displayImage);
    connect(this, &FlickrSearchMainWindow::setImage, this, &FlickrSearchMainWindow::downloadSetImage);
    ui->listWidget->setViewMode(QListWidget::IconMode);

    connect(ui->listWidget, &QListWidget::itemClicked, this, &FlickrSearchMainWindow::viewImage);
    this->showMaximized();
}

FlickrSearchMainWindow::~FlickrSearchMainWindow()
{
    delete ui;
}

void FlickrSearchMainWindow :: flickrSearch()
{

    if(ui->edtFlickrSearch->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "No search input provided");
        return;
    }
    m_imgViewer->init();
    m_imgViewer->setHidden(true);
    counter = 0;
    flickrApi.getimageSearchJson(ui->edtFlickrSearch->text());
    ui->listWidget->clear();
    m_mpImageList.clear();
}

void FlickrSearchMainWindow::loadImage()
{
    auto imageUrl = flickrApi.listImageUrl->at(counter++);
    qDebug() << imageUrl;
    emit setImage(imageUrl, QSize(200, 200));
}

void FlickrSearchMainWindow::displayImage(const QString& imgUrl,
                                          QImage* image,
                                          const QSize &target_size)
{
    if (image)
    {
        const QImage img = *image;
        auto scaledImg = img.scaled(target_size);
        QPixmap *pixmap = new QPixmap(target_size);
        pixmap->fill(Qt::transparent);
        QPainter painter(pixmap);
        int x = (target_size.width() - scaledImg.width()) / 2;
        int y = (target_size.height() - scaledImg.height()) / 2;
        painter.drawImage(QRect{{x, y}, scaledImg.size()}, scaledImg);
        painter.end();

        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::DecorationRole, *pixmap);
        item->setData(Qt::UserRole, imgUrl);
        ui->listWidget->addItem(item);
        m_mpImageList.insert(item, image);
    }

    if(counter < flickrApi.listImageUrl->size())
        loadImage();
}

void FlickrSearchMainWindow::downloadSetImage(QString imageUrl, QSize sz)
{
    imgDownloader.setFile(imageUrl, sz);
}

void FlickrSearchMainWindow::viewImage(QListWidgetItem* item)
{
    m_imgViewer->setHidden(false);

    auto imgPtr = m_mpImageList[item];

    if(imgPtr){
        m_imgViewer->attachImagePtr(imgPtr);

        auto imgUrl = item->data(Qt::UserRole).toString();
        statusImgUrlLabel->setText(QString("Image Url: %1").arg(imgUrl));
    }
}

void FlickrSearchMainWindow::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return))
        flickrSearch();
    else
        QMainWindow::keyPressEvent(event);
}
