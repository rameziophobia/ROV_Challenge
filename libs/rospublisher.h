#ifndef ___ROS_PUBLISHER_H___
#define ___ROS_PUBLISHER_H___

#include "rosservice.h"
#include <string>
#include <QtCore>
#include <QThread>
#include <queue>
#include <std_msgs/String.h>

class RosPublisher : public QObject {
    Q_OBJECT
public:
    void send(const std::string &msg);
    RosPublisher(const std::string &topic);
    ~RosPublisher();
    Q_SLOT void run();
    void shutdown();

private:
    std::string topic;
    QThread* thread;
    bool cancelled;
    ros::Publisher publisher;
    std::queue<std_msgs::String> msgsQ;
};

#endif
