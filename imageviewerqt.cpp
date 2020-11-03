#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>
#include "imageviewerqt.h"
#include <opencv2/opencv.hpp> 
#include <iostream>

ImageViewerQt::ImageViewerQt(QWidget* parent)
    : QMainWindow(parent)
    , fileMenu(nullptr)
    , viewMenu(nullptr)
    , currentImage(nullptr)
{
    initUI();
}

ImageViewerQt::~ImageViewerQt() {

}


void ImageViewerQt::initUI() {
    this->resize(800, 600);

    // setup menubar
    fileMenu = menuBar()->addMenu("&File");
    editMenu = menuBar()->addMenu("&Edit");
    viewMenu = menuBar()->addMenu("&View");

    // setup toolbar
    fileToolBar = addToolBar("File");
    editToolBar = addToolBar("Edit");
    viewToolBar = addToolBar("View");

    // main area for the image
    imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageScene);
    setCentralWidget(imageView);

    // setup status bar
    mainStatusBar = statusBar();
    mainStatusLabel = new QLabel(mainStatusBar);
    mainStatusBar->addPermanentWidget(mainStatusLabel);
    mainStatusLabel->setText("Image Information will be here!");

    createActions();
}

//void createActions();
    //void showImage(QString);
    //void setupShortcuts();


void ImageViewerQt::createActions() {
    // create action & add them to menu
    // FileMenu
    openAction = new QAction("&Open", this);
    fileMenu->addAction(openAction);

    saveasAction = new QAction("&Save as", this);
    fileMenu->addAction(saveasAction);

    exitAction = new QAction("E&xit", this);
    fileMenu->addAction(exitAction);

    // ViewMenu
    zoomInAction = new QAction("Zoom in", this);
    viewMenu->addAction(zoomInAction);

    zoomOutAction = new QAction("Zoom out", this);
    viewMenu->addAction(zoomOutAction);

    prevAction = new QAction("&Previous Image", this);
    viewMenu->addAction(prevAction);

    nextAction = new QAction("&Next Image", this);
    viewMenu->addAction(nextAction);

    // EditMenu
    blurAction = new QAction("Blur", this);
    editMenu->addAction(blurAction);

    erodeAction = new QAction("Erode", this);
    editMenu->addAction(erodeAction);

    dilateAction = new QAction("Dilate", this);
    editMenu->addAction(dilateAction);

    // add actions to toolbar
    // FileToolBar
    fileToolBar->addAction(openAction);

    // ViewToolBar
    viewToolBar->addAction(zoomInAction);
    viewToolBar->addAction(zoomOutAction);
    viewToolBar->addAction(prevAction);
    viewToolBar->addAction(nextAction);

    // EditToolBar
    editToolBar->addAction(blurAction);
    editToolBar->addAction(erodeAction);
    editToolBar->addAction(dilateAction);

    // connect the signals and slots
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openImage()));
    connect(saveasAction, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
    connect(exitAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(quit()));
    connect(zoomInAction, SIGNAL(triggered(bool)), this, SLOT(zoomIn()));
    connect(zoomOutAction, SIGNAL(triggered(bool)), this, SLOT(zoomOut()));
    connect(prevAction, SIGNAL(triggered(bool)), this, SLOT(prevImage()));
    connect(nextAction, SIGNAL(triggered(bool)), this, SLOT(nextImage()));
    connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(blurImage()));
    connect(erodeAction, SIGNAL(triggered(bool)), this, SLOT(erodeImage()));
    connect(dilateAction, SIGNAL(triggered(bool)), this, SLOT(dilateImage()));

    setupShortcuts();
}

void ImageViewerQt::openImage() {
    QFileDialog dialog(this);
    dialog.setWindowTitle("Open Image");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));
    QStringList filePaths;
    if (dialog.exec()) {
        filePaths = dialog.selectedFiles();
        showImage(filePaths.at(0));
    }
}

void ImageViewerQt::showImage(QString path) {
    imageScene->clear();
    imageView->resetMatrix();
    QPixmap image(path);
    currentImage = imageScene->addPixmap(image);
    imageScene->update();
    imageView->setSceneRect(image.rect());
    QString status = QString("%1, %2x%3, %4 Bytes").arg(path).arg(image.width()).arg(image.height()).arg(QFile(path).size());
    mainStatusLabel->setText(status);
    currentImagePath = path;
}


void ImageViewerQt::zoomIn() {
    imageView->scale(1.2, 1.2);
}

void ImageViewerQt::zoomOut() {
    imageView->scale(1 / 1.2, 1 / 1.2);
}


void ImageViewerQt::prevImage() {
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.jpg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegExp(QRegExp::escape(current.fileName())));
    if (idx > 0) {
        showImage(dir.absoluteFilePath(fileNames.at(idx - 1)));
    }
    else {
        QMessageBox::information(this, "Information", "Current image is the first one.");
    }
}

void ImageViewerQt::nextImage() {
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.jpg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegExp(QRegExp::escape(current.fileName())));
    if (idx < fileNames.size() - 1) {
        showImage(dir.absoluteFilePath(fileNames.at(idx + 1)));
    }
    else {
        QMessageBox::information(this, "Information", "Current image is the last one.");
    }
}

void ImageViewerQt::saveAs() {
    if (currentImage == nullptr) {
        QMessageBox::information(this, "Information", "Nothing to save.");
        return;
    }
    QFileDialog dialog(this);
    dialog.setWindowTitle("Save Image As ...");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));
    QStringList fileNames;

    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        if (QRegExp(".+\\.(png|bmp|jpg)").exactMatch(fileNames.at(0))) {
            currentImage->pixmap().save(fileNames.at(0));
        }
        else {
            QMessageBox::information(this, "Information", "Save error: bad format or filename.");
        }
    }
}


void ImageViewerQt::setupShortcuts() {
    QList<QKeySequence> shortcuts;
    shortcuts << Qt::Key_Plus << Qt::Key_Equal;
    zoomInAction->setShortcuts(shortcuts);

    shortcuts.clear();
    shortcuts << Qt::Key_Minus << Qt::Key_Underscore;
    zoomOutAction->setShortcuts(shortcuts);

    shortcuts.clear();
    shortcuts << Qt::Key_Up << Qt::Key_Left;
    prevAction->setShortcuts(shortcuts);

    shortcuts.clear();
    shortcuts << Qt::Key_Down << Qt::Key_Right;
    nextAction->setShortcuts(shortcuts);
}

void ImageViewerQt::blurImage() {
    QPixmap pixmap = currentImage->pixmap();
    QImage image = pixmap.toImage();
    image = image.convertToFormat(QImage::Format_RGB888);
    cv::Mat mat = cv::Mat(
        image.height(),
        image.width(),
        CV_8UC3,
        image.bits(),
        image.bytesPerLine());
    cv::Mat tmp;
    try {
		cv::blur(mat, tmp, cv::Size(8, 8));
    }
    catch (const cv::Exception& e) {
        QMessageBox::information(this, "Information", "There is an error");
    }
    mat = tmp;
    QImage image_blurred(
        mat.data,
        mat.cols,
        mat.rows,
        mat.step,
        QImage::Format_RGB888
    );
    pixmap = QPixmap::fromImage(image_blurred);
    imageScene->clear();
    imageView->resetMatrix();
    currentImage = imageScene->addPixmap(pixmap);
    imageScene->update();
    imageView->setSceneRect(pixmap.rect());
}

void ImageViewerQt::erodeImage() {
    QPixmap pixmap = currentImage->pixmap();
    QImage image = pixmap.toImage();
    image = image.convertToFormat(QImage::Format_RGB888);
    cv::Mat mat = cv::Mat(
        image.height(),
        image.width(),
        CV_8UC3,
        image.bits(),
        image.bytesPerLine());
    try {
		cv::erode(mat, mat, cv::Mat(), cv::Point(-1, -1), 1);
    }
    catch (const cv::Exception& e) {
        QMessageBox::information(this, "Information", "There is an error");
    }
    QImage image_blurred(
        mat.data,
        mat.cols,
        mat.rows,
        mat.step,
        QImage::Format_RGB888
    );
    pixmap = QPixmap::fromImage(image_blurred);
    imageScene->clear();
    imageView->resetMatrix();
    currentImage = imageScene->addPixmap(pixmap);
    imageScene->update();
    imageView->setSceneRect(pixmap.rect());
}



void ImageViewerQt::dilateImage() {
    QPixmap pixmap = currentImage->pixmap();
    QImage image = pixmap.toImage();
    image = image.convertToFormat(QImage::Format_RGB888);
    cv::Mat mat = cv::Mat(
        image.height(),
        image.width(),
        CV_8UC3,
        image.bits(),
        image.bytesPerLine());
    try {
		cv::dilate(mat, mat, cv::Mat(), cv::Point(-1, -1), 1);
    }
    catch (const cv::Exception& e) {
        QMessageBox::information(this, "Information", "There is an error");
    }
    QImage image_blurred(
        mat.data,
        mat.cols,
        mat.rows,
        mat.step,
        QImage::Format_RGB888
    );
    pixmap = QPixmap::fromImage(image_blurred);
    imageScene->clear();
    imageView->resetMatrix();
    currentImage = imageScene->addPixmap(pixmap);
    imageScene->update();
    imageView->setSceneRect(pixmap.rect());
}

// TODO: add this function
// converting Qt's QGraphicsPixmapItem to Opencv's Mat  
void ImageViewerQt::pixmapToMat(QGraphicsPixmapItem *currentImage, ImageViewerQt *parent, cv::Mat mat) {

}
