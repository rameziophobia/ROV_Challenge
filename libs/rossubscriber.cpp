//#include "rossubscriber.h"

//RosSubscriber::RosSubscriber(const std::string &topic, QObject* parent)
//    : m_topic(topic), thread(new QThread(parent)) {}

//void RosSubscriber::start() {
//    this->moveToThread(thread);
//    connect(thread, &QThread::started, this, &RosSubscriber::run);

//    ros::NodeHandle n;
//    subscriber = n.subscribe<std_msgs::String, RosSubscriber>(m_topic, 100, &RosSubscriber::callback, this);
//    thread->start();
//}

//void RosSubscriber::run() {
//    ros::spin();
//}

//void RosSubscriber::callback(const std_msgs::String msg) {
//    Q_EMIT msgReceived(msg.data.c_str());
//}
