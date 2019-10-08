#include <QtCore>
#include <QThread>
#include <ros/ros.h>
#include "rov_challenge/GetMetalType.h"

class GetMetalTypeClient : public QObject {
    Q_OBJECT
public:
    GetMetalTypeClient(QObject* parent = nullptr)
        : QObject(), m_thread(new QThread(parent)) {
        moveToThread(m_thread);
        connect(m_thread, &QThread::started, this, &GetMetalTypeClient::init, Qt::QueuedConnection);
        m_thread->start();
    }

    Q_SLOT void metalTypeNeeded() {
        try {
            rov_challenge::GetMetalType srv;
            if (client.call(srv)) {
                Q_EMIT metalDetected(srv.response.metalType.c_str());
            } else {
                Q_EMIT errorOccurred();
            }
        } catch (...) {
            Q_EMIT errorOccurred();
        }
    }

    Q_SIGNAL void metalDetected(QString metalType);
    Q_SIGNAL void errorOccurred();

private:
    Q_SLOT void init() {
        ros::NodeHandle n;
        client = n.serviceClient<rov_challenge::GetMetalType>("get_metal_type");
    }
    QThread* m_thread;
    ros::ServiceClient client;
};
