import I2C_LCD_driver
import socket
import time
import subprocess

mylcd = I2C_LCD_driver.lcd()
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
mylcd.lcd_display_string("IP Address:", 1)

def get_ip_address2(ifname):
    s.connect(('google.com',0))
    ipaddr=s.getsockname()[0]
    return ipaddr

time.sleep(60)
mylcd.lcd_display_string(get_ip_address2('eth0'),2)

#p = subprocess.Popen(["roslaunch /home/callum/buggy_ws/launch/buggy.launch"],
#                     stdout=subprocess.PIPE,stderr = subprocess.PIPE, shell = True)
#print (p.communicate())

