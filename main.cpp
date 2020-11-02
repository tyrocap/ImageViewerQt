#include "imageviewerqt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ImageViewerQt window;
    window.show();
    return app.exec();
}


