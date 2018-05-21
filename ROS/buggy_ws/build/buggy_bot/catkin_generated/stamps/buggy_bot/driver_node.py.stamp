#!/usr/bin/env python

import rospy
import keyboard
import socket
from std_msgs.msg import Int8

HOST = ''
PORT = 21567
BUFSIZE = 1024
ADDR = (HOST,PORT)

tcpSerSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

ctrCmd = ['Up','Down','Left','Right']


if __name__=='__main__':
    while True:
        pub = rospy.Publisher('drive_command', Int8, queue_size=10)
        rospy.init_node('buggy_command', anonymous=False)
        print 'Waiting for connection'
        tcpCliSock,addr = tcpSerSock.accept()
        print '...connected from :', addr
        try:
            while True:
                data = ''
                data = tcpCliSock.recv(BUFSIZE)
                if not data:
                    break
                if data == ctrCmd[0]:
                    print 'Forward'                                                
                    drive_command = 1
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
                if data == ctrCmd[1]:
                    print 'Reverse'
                    drive_command = 3
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
                if data == ctrCmd[2]:
                    print 'Left'
                    drive_command = 4
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
                if data == ctrCmd[3]:
                    print 'Right'
                    drive_command = 2
                    rospy.loginfo(drive_command)
                    pub.publish(drive_command)
        except KeyboardInterrupt:
            Servomotor.close()
            GPIO.cleanup()
    tcpSerSock.close();
