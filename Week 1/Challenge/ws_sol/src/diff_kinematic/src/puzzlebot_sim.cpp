#include <ros/ros.h>

#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>

#include <cmath>

/* How can I propose Kinda attributes for the Node?*/
int nodeFreq = 20;
geometry_msgs::Twist self_Twist;
geometry_msgs::PoseStamped self_Pose;

/* ====== Callbacks ====== */
void inputVelCallback(const geometry_msgs::Twist &msg)
{
    self_Twist.linear.x = msg.linear.x;
    self_Twist.angular.x = msg.angular.z;
}

/* ====== MAIN ====== */
int main(int argc, char* argv[])
{
    ros::init(argc, argv, "puzzlebot_sim");
    ros::NodeHandle nh;
    
    // Subscribers and publishers: 
    ros::Subscriber velSubs;
    velSubs = nh.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, inputVelCallback);
    
    ros::Publisher posePublis;
    posePublis = nh.advertise<geometry_msgs::PoseStamped>("/pose_sim", 10);
    
    // Rate
    ros::Rate loop_rate(nodeFreq);

    while (ros::ok())
    {
        // Robot position 

        float x_d = self_Twist.linear.x * std::cos(1);
        float y_d = self_Twist.linear.x * std::sin(1);

        float theta_d = self_Twist.angular.x;

        self_Pose.pose.position.x = x_d/nodeFreq;
        self_Pose.pose.position.y = y_d/nodeFreq;

        ros::spinOnce();
        loop_rate.sleep();
    }
}
