/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date 09 2020
 *
 * @author Syong 
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/qtros/qnode.hpp"
std_msgs::String TEST_out;

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtros {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"qtros");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	kinematics_publisher = n.advertise<std_msgs::Float32MultiArray>("kinematics", 5);
	start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"qtros");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	kinematics_publisher = n.advertise<std_msgs::Float32MultiArray>("kinematics", 5);
	start();
	return true;
}

//bool QNode::TEST(const std::string &in_TEST) {
//	TEST_out.data = in_TEST;
//}

void QNode::run() {
	ros::Rate loop_rate(1);

//------------------------------------------------------------------------//

	float Method = 0; 	//FK = 0, 	IK = 1;
	float Data1 = 0; 	//FK : th1, 	IK : position x;
	float Data2 = 120;	//FK : th2, 	IK : position y;

//------------------------------------------------------------------------//

	while ( ros::ok() ) {

		std_msgs::Float32MultiArray kinematics;
		kinematics.data.clear();
		kinematics.data.push_back(Method);
		kinematics.data.push_back(Data1);
		kinematics.data.push_back(Data2);
		kinematics_publisher.publish(kinematics);

		//TEST
		

		std::stringstream ss;
		if(kinematics.data.at(0) == 0)
		{
			//ss << "Mothod = Forward Kinematics,  th1 = "<< kinematics.data.at(1) << ",  th2 = " << kinematics.data.at(2);
		}
		else if(kinematics.data.at(0) == 1)
		{
			//ss << "Mothod = Inverse Kinematics,  posision_x = "<< kinematics.data.at(1) << ",  position_y = " << kinematics.data.at(2);
		}

		//log(Info, ss.str());
		//log(Info, TEST_out.data); //TEST
		ros::spinOnce();
		loop_rate.sleep();
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

}  // namespace qtros
