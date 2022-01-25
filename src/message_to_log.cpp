//
// Created by jcremona on 3/9/20.
//

#include "message_to_log.h"
#include <fstream>

void MessageToLog::PoseToLog(const geometry_msgs::Pose pose) {
    m_xPos = pose.position.x;
    m_yPos = pose.position.y;
    m_zPos = pose.position.z;
    m_qw = pose.orientation.w;
    m_qx = pose.orientation.x;
    m_qy = pose.orientation.y;
    m_qz = pose.orientation.z;
}

MessageToLog::MessageToLog(const nav_msgs::Odometry::ConstPtr &msg) {
    PoseToLog(msg->pose.pose);
    timestamp = msg->header.stamp.toSec();
}

MessageToLog::MessageToLog(const geometry_msgs::PoseStamped::ConstPtr &msg) {
    PoseToLog(msg->pose);
    timestamp = msg->header.stamp.toSec();
}

MessageToLog::MessageToLog(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &msg) {
    PoseToLog(msg->pose.pose);
    timestamp = msg->header.stamp.toSec();
}

MessageToLog::MessageToLog(const sensor_msgs::Imu::ConstPtr &msg) {
    timestamp = msg->header.stamp.toSec();
    m_xPos = 0;
    m_yPos = 0;
    m_zPos = 0;
    m_qw = msg->orientation.w;
    m_qx = msg->orientation.x;
    m_qy = msg->orientation.y;
    m_qz = msg->orientation.z;
}

inline void Logger(std::string filePath, std::string logMsg) {

    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app);
    if(!ofs) {
        std::cerr << "ERROR: Unable to create output file: " << filePath << std::endl;
        exit(1);
    }
//    ofs << now << '\t' << logMsg << '\n';
    ofs << logMsg << std::endl;
    ofs.close();
}

void MessageToLog::saveTUMFormat(std::string filePath) {
    std::stringstream ss;
    ss << std::fixed << timestamp << " " << m_xPos << " " << m_yPos << " " << m_zPos << " " << m_qx << " " << m_qy
       << " " << m_qz << " " << m_qw;
    // ROS_INFO("Pose: (%f, %f, %f, %f, %f, %f, %f, %f)", timestamp, m_xPos, m_yPos, m_zPos, m_qx, m_qy, m_qz, m_qw);
    std::string T_b_w_str = ss.str();
    Logger(filePath, T_b_w_str);
}
