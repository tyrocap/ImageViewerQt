#pragma once
#include <QtWidgets/QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStatusBar>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <opencv2/opencv.hpp>
#include "ui_imageviewerqt.h"

class ImageViewerQt : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageViewerQt(QWidget* parent = Q_NULLPTR);
    ~ImageViewerQt();

private:
    void initUI();
    void createActions();
    void showImage(QString);
    void setupShortcuts();

    // Qt's image to OpenCV image
    void pixmapToMat(QGraphicsPixmapItem* currentImage, ImageViewerQt* parent, cv::Mat mat);

private slots:
    void openImage();
    void zoomIn();
    void zoomOut();
    void prevImage();
    void nextImage();
    void saveAs();
    void blurImage();
    void erodeImage();
    void dilateImage();

private:
    QMenu* fileMenu;
    QMenu* viewMenu;
    QMenu* editMenu;

    QToolBar* fileToolBar;
    QToolBar* viewToolBar;
    QToolBar* editToolBar;

    QGraphicsScene* imageScene;
    QGraphicsView* imageView;

    QStatusBar* mainStatusBar;
    QLabel* mainStatusLabel;

    QAction* openAction;
    QAction* saveasAction;
    QAction* exitAction;
    QAction* zoomInAction;
    QAction* zoomOutAction;
    QAction* prevAction;
    QAction* nextAction;
    QAction* blurAction;
    QAction* erodeAction;
    QAction* dilateAction;

    QString currentImagePath;
    QGraphicsPixmapItem* currentImage;
};

