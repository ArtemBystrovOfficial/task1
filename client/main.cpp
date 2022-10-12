#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "appwindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QQmlApplicationEngine eng;
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    AppWindow wid;

    wid.setMinimumHeight(240);
    wid.setMinimumWidth(720);
    wid.resize(720,480);

    wid.show();

    return app.exec();
}

