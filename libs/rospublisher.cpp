#include "rospublisher.h"


RosPublisher::RosPublisher(const std::string &topic): topic(topic), cancelled(false) {
    thread = new QThread();
    this->moveToThread(thread);
    connect(thread, &QThread::started, this, &RosPublisher::run);

    ros::NodeHandle n;
    publisher = n.advertise<std_msgs::String>(topic, 100);
    thread->start();
}

RosPublisher::~RosPublisher() {
    this->shutdown();
    publisher.shutdown();
    thread->wait();
}

void RosPublisher::send(const std::string &msg) {
    std_msgs::String rosMsg;
    rosMsg.data = msg.c_str();
    msgsQ.push(rosMsg);
}

void RosPublisher::run() {
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

void RosPublisher::shutdown() {
    cancelled = true;
}
