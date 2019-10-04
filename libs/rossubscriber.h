#ifndef ___ROS_SUBSCRIBER_H___
#define ___ROS_SUBSCRIBER_H___

#include "rosservice.h"
#include <string>
#include <QtCore>
#include <QThread>
#include <queue>
#include <std_msgs/String.h>
#include <ros/ros.h>
#include <QDebug>

class RosSubscriber : public QObject {
    Q_OBJECT
public:
    RosSubscriber(const std::string &topic, QObject* parent = nullptr);
    Q_SIGNAL void msgReceived(const QString &msg);
    void start();

private:
    ros::Subscriber subscriber;
    Q_SLOT void run();
    Q_SLOT void callback(const std_msgs::String msg);
    QThread* thread;
    std::string m_topic;
};

#endif
