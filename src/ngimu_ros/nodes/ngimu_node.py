#!/usr/bin/env python3

import rospy
import serial
import string
import math
import sys

import osc_decoder

from datetime import datetime
import time
from sensor_msgs.msg import Imu

degrees2rad = math.pi/180.0

rospy.init_node("ngimu_node")
pub = rospy.Publisher('imu', Imu, queue_size=1)
imuMsg = Imu()

# define port name here
port='/dev/ttyACM0'

# Check your COM port and baud rate
rospy.loginfo("Opening %s...", port)
try:
    ser = serial.Serial(port=port, baudrate=115200, timeout=1)
except serial.serialutil.SerialException:
    rospy.logerr("IMU not found at port "+port + ". Did you specify the correct port in the launch file?")
    #exit
    sys.exit(0)

roll=0
pitch=0
yaw=0
seq=0

rospy.loginfo("Publishing IMU data...")

data_line = []
bundle_data = []
pub_flag = 0

while not rospy.is_shutdown():
    for c in ser.readline():
        data_line.append(c)
        #rospy.loginfo("data_c:%s", c)
        #rospy.loginfo("data_s:%s", bytes(data_line))

        if c == 192:
            message = osc_decoder.decode(bytes(data_line))

            if len(message) != 0:
                #rospy.loginfo("%s", message[0][1:])
                msg = message[0][1:]
                #rospy.loginfo("%s", message[0][1:])
                if msg[0] == "/sensors":
                    imuMsg.angular_velocity.x = msg[1]
                    imuMsg.angular_velocity.y = msg[2]
                    imuMsg.angular_velocity.z = msg[3]

                    imuMsg.linear_acceleration.x = msg[4]
                    imuMsg.linear_acceleration.y = msg[5]
                    imuMsg.linear_acceleration.z = msg[6]
                    
                    pub_flag += 1 

                if msg[0] == "/quaternion":
                    imuMsg.orientation.x = msg[1]
                    imuMsg.orientation.y = msg[2]
                    imuMsg.orientation.z = msg[3]
                    imuMsg.orientation.w = msg[4]

                    pub_flag += 1 

            del data_line[:]

        if pub_flag == 2:
            #rospy.loginfo("published")
            imuMsg.header.stamp= rospy.Time.now()
            imuMsg.header.frame_id = 'ngimu'
            imuMsg.header.seq = seq
            seq += 1
            pub.publish(imuMsg)
            pub_flag = 0

ser.close
