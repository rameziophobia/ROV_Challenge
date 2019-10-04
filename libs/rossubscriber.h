#ifndef ___ROS_SUBSCRIBER_H___
#define ___ROS_SUBSCRIBER_H___

#include <ros/ros.h>
#include <string>
#include <QtCore>
#include <QThread>

template <class M, class T>
class RosSubscriber : public QThread {
public:
    RosSubscriber(const std::string &topic, void(T::*fp)(M), T* obj, QObject* parent)
        :QThread(parent), cancelled(false) {
        ros::NodeHandle n;
        subscriber = n.subscribe(topic, 100, fp, obj);
        start();
    }

    void run() override {
        ros::Rate loop_rate(100);
        while (ros::ok() && !cancelled)
        {
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void shutdown() {
        cancelled = true;
    }

    ~RosSubscriber() {
        shutdown();
        subscriber.shutdown();
        wait();
    }

private:
    ros::Subscriber subscriber;
    bool cancelled;
};

#endif
