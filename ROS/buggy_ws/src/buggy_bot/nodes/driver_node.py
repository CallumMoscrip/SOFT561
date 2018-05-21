#!/usr/bin/env python

import rospy
import keyboard
import socket
from std_msgs.msg import Int8
from std_msgs.msg import Float32
import I2C_LCD_driver
import time

HOST = ''
PORT = 21567
BUFSIZE = 1024
ADDR = (HOST,PORT)
global front_range

tcpSerSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

mylcd = I2C_LCD_driver.lcd()
ctrCmd = ['Up','Down','Left','Right','Stop']

def process_front(data):
    global front_range
    front_range = data.data
    #rospy.loginfo(front_range)
    #print('front range :',front_range)
    
def process_left(data):
    left_range = data.data
    #rospy.loginfo(left_range)
    #print('left range :',left_range)

def process_right(data):
    right_range = data.data
    #rospy.loginfo(right_range)
    #print('right range :',right_range)
    
if __name__=='__main__':
    global front_range
    while True:
        #rospy.init_node('buggy_sensors', anonymous = True)
        rospy.Subscriber("chatter1", Float32, process_front)
        rospy.Subscriber("chatter2", Float32, process_left)
        rospy.Subscriber("chatter3", Float32, process_right)

        pub = rospy.Publisher('drive_command', Int8, queue_size=10)
        rospy.init_node('buggy_command', anonymous=False)
        print ('Waiting for connection')
        tcpCliSock,addr = tcpSerSock.accept()
        print ('...connected from :', addr)
        mylcd.lcd_display_string("               ", 1)
        mylcd.lcd_display_string("               ", 2)
        mylcd.lcd_display_string("Now lets move!", 1)
        time.sleep(0.1)
        try:
            while True:
                data = ''
                data = tcpCliSock.recv(BUFSIZE)
                if not data:
                    break
                if data == ctrCmd[0]:
                    if front_range < 15:
                        drive_command = 5
                        rospy.loginfo(drive_command)
                        pub.publish(drive_command)
                        mylcd.lcd_display_string("               ", 1)
                        mylcd.lcd_display_string("               ", 2)
                        mylcd.lcd_display_string("Look out!", 1)
                        mylcd.lcd_display_string("Object to close!", 2)
                        drive_command = 1
                        rospy.loginfo(drive_command)
                        pub.publish(drive_command)
                    else:
                        print ('Forward')
                        mylcd.lcd_display_string('Moving forward!',2)
                        drive_command = 1
                        rospy.loginfo(drive_command)
                        pub.publish(drive_command)
                if data == ctrCmd[1]:
                    print ('Reverse')
                    mylcd.lcd_display_string('Back away!',2)
                    drive_command = 3
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
                if data == ctrCmd[2]:
                    print ('Left')
                    mylcd.lcd_display_string('Lets turn left!',2)
                    drive_command = 4
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
                if data == ctrCmd[3]:
                    print ('Right')
                    mylcd.lcd_display_string('Lets turn right!',2)
                    drive_command = 2
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
                if data == ctrCmd[4]:
                    print ('Stop')
                    mylcd.lcd_display_string('Better stop!',2)
                    drive_command = 5
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
        
        except KeyboardInterrupt:
            Servomotor.close()
            GPIO.cleanup()
    tcpSerSock.close();
