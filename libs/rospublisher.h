#ifndef ___ROS_PUBLISHER_H___
#define ___ROS_PUBLISHER_H___

#include "rosservice.h"
#include <string>
#include <QtCore>
#include <QThread>
#include <queue>
#include <std_msgs/String.h>

template<class T>
class RosPublisher : public QThread {
public:
    void send(const T &msg) {
        msgsQ.push(msg);
    }

    RosPublisher(const std::string &topic, QObject* parent = nullptr)
        : QThread(parent), topic(topic), cancelled(false) {
        ros::NodeHandle n;
        publisher = n.advertise<T>(topic, 100);
        start();
    }

    ~RosPublisher() {
        this->shutdown();
        publisher.shutdown();
        wait();
    }

    void shutdown() {
        cancelled = true;
    }

    void run() override {
        ros::Rate loop_rate(100);
        while (ros::ok() && !cancelled)
        {
            if (msgsQ.size()) {
                auto msg = msgsQ.front();
                msgsQ.pop();
                publisher.publish(msg);
            }
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    std::string topic;
    bool cancelled;
    ros::Publisher publisher;
    std::queue<T> msgsQ;
};

#endif
