#ifndef ___ROSSERVICE_H___
#define ___ROSSERVICE_H___

#include <ros/ros.h>
#include <string>
#include <QtCore>

class RosService {
public:
    static bool init(int argc, char** argv, const std::string &nodeName);
    static bool init(const std::string &masterUrl, const std::string &hostUrl, const std::string &nodeName);
    static void dispose();
};

#endif
