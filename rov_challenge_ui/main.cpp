#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <joystick.h>

int main(int argc, char *argv[])
{
    Joystick *myJoystick = new Joystick();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
