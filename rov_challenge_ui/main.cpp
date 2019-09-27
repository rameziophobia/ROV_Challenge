#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rovtimer.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<RovTimer>("RovTimer", 1, 0, "RovTimer");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
