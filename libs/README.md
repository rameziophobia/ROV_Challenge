# How To Use Ros Libraries

## Using Ros Publisher

 1. Include rospublisher.h file

    #include "libs/rospublisher.h"

 2. Create object of RosPublisher
It takes the type of message, topic name and parent (QObject that created the publisher), preferred to declare it as a member variable

    RosPublisher<std_msgs::String> rosPublisher("/example_topic", this);
In previous code, we created ros publisher that publish messages of type *std_msgs::String* to topic *"/example_topic"*

 3. To publish message use `RosTopic\<T\>::send(T msg)`
 function, for example

    std_msgs::String msg;
    msg.data = "Hello Ros";
    rosPublisher.send(msg);
Here we use ros publisher that we created before to send message

## Using RosSubscriber

 1. Include rossubscriber.h file

    #include "libs/rossubscriber.h"

 2. Create RosSubscriber object

    RosSubscriber<M, T> (std::string topic, &T::callback, M* obj, QObject* parent);
M is type of message will be received
T type of object that contains the callback functio
For example, if we created in MainWindow class the following callback function

    void MainWindow::callback(std_msgs::String msg) {
	    qDebug() << msg.data.c_str();
    }
Then, we can create the following RosSubscriber

    RosSubscriber<std_msgs::String, MainWindow> rosSubscriber("/example_topic", &MainWindow::callback, this, this);
The third parameter specify the object that contains the callback function
