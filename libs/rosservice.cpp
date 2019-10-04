#include "rosservice.h"
#include <std_msgs/String.h>

bool RosService::init(int argc, char** argv, const std::string &nodeName) {
    ros::init(argc, argv, nodeName);
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start();
    ros::Time::init();
    return true;
}

bool RosService::init(const std::string &masterUrl, const std::string &hostUrl, const std::string &nodeName) {
    std::map<std::string,std::string> remappings;
    remappings["__master"] = masterUrl;
    remappings["__hostname"] = hostUrl;
    ros::init(remappings, nodeName);
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start();
    ros::Time::init();
    return true;
}

void RosService::dispose() {
    if (ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }
}
