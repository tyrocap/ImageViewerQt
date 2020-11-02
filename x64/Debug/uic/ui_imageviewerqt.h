/********************************************************************************
** Form generated from reading UI file 'imageviewerqt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWERQT_H
#define UI_IMAGEVIEWERQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageViewerQtClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageViewerQtClass)
    {
        if (ImageViewerQtClass->objectName().isEmpty())
            ImageViewerQtClass->setObjectName(QString::fromUtf8("ImageViewerQtClass"));
        ImageViewerQtClass->resize(600, 400);
        menuBar = new QMenuBar(ImageViewerQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ImageViewerQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageViewerQtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ImageViewerQtClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ImageViewerQtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ImageViewerQtClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ImageViewerQtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ImageViewerQtClass->setStatusBar(statusBar);

        retranslateUi(ImageViewerQtClass);

        QMetaObject::connectSlotsByName(ImageViewerQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageViewerQtClass)
    {
        ImageViewerQtClass->setWindowTitle(QCoreApplication::translate("ImageViewerQtClass", "ImageViewerQt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageViewerQtClass: public Ui_ImageViewerQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWERQT_H
