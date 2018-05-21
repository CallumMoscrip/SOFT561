
#include <ros.h>
#include <Wire.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int8.h>

ros::NodeHandle nh;
std_msgs::Float32 front_msg;
ros::Publisher chatter1("chatter1", &front_msg);
std_msgs::Float32 left_msg;
ros::Publisher chatter2("chatter2", &left_msg);
std_msgs::Float32 right_msg;
ros::Publisher chatter3("chatter3", &right_msg);

int drive_command;

void drive_control(const std_msgs::Int8& drive_msg){
  drive_command=drive_msg.data;
  
}

ros::Subscriber<std_msgs::Int8> sub("drive_command", &drive_control );

long durF;
long durL;
long durR;
int distF;
int distL;
int distR;
int dist;
int EchoF = 23;
int PingF = 22;
int EchoL = 27;
int PingL = 26;
int EchoR = 25;
int PingR = 24;
float local_distF;
float local_distL;
float local_distR;



void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.advertise(chatter1);
  nh.advertise(chatter2);
  nh.advertise(chatter3);
  
  nh.subscribe(sub);
  pinMode(LED_BUILTIN, OUTPUT);

  // channel A MOTOR
  pinMode(12, OUTPUT);  //Motor Channel
  pinMode(9, OUTPUT);   //Brake

  // Channel B MOTOR
  pinMode(13, OUTPUT);  //Motor Channel
  pinMode(8, OUTPUT);   //Brake

  //Ultrasound
  pinMode(EchoF, INPUT);   //Echo pin 24 dig
  pinMode(PingF, OUTPUT);  //Trig Ping pin 22 dig
  pinMode(EchoL, INPUT);   //Echo pin 24 dig
  pinMode(PingL, OUTPUT);  //Trig Ping pin 22 dig
  pinMode(EchoR, INPUT);   //Echo pin 24 dig
  pinMode(PingR, OUTPUT);  //Trig Ping pin 22 dig
}

void loop() 
{
  
  dist = get_distance();
  front_msg.data = local_distF;
  chatter1.publish( &front_msg );
  left_msg.data = local_distL;
  chatter2.publish( &left_msg );
  right_msg.data = local_distR;
  chatter3.publish( &right_msg );
  
  if(drive_command == 1 && local_distF >= 20){
    advance();
  }
  else if(drive_command == 1 && local_distF < 20){
    if(local_distR > 20){
      turn_right();
    }
    else if(local_distL > 20){
      turn_left();
    }
    else{
      reverse();
    }
  }
  else if(drive_command==2){
    turn_right();
  }
  else if(drive_command==3){
    reverse();
  }
  else if(drive_command==4){
    turn_left();
  }
  else{
    brake();
  }
  nh.spinOnce();

}


int get_distance() {
 
  //Ultrasound Setup
  digitalWrite(PingF, LOW);  //turning off trig pin
  digitalWrite(PingR, LOW);  //turning off trig pin
  digitalWrite(PingL, LOW);  //turning off trig pin
  delayMicroseconds(2);   //delay
  digitalWrite(PingF, HIGH);
  delayMicroseconds(10);
  digitalWrite(PingF, LOW);
  durF = pulseIn(EchoF, HIGH);
  local_distF = durF*0.034/2;
  if(local_distF>=15){
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if(local_distF<15){
    digitalWrite(LED_BUILTIN, HIGH);
  }  
  digitalWrite(PingL, HIGH);
  delayMicroseconds(10);
  digitalWrite(PingL, LOW);
  durL = pulseIn(EchoL, HIGH);
  local_distL = durL*0.034/2;
  
  digitalWrite(PingR, HIGH);
  delayMicroseconds(10);
  digitalWrite(PingR, LOW); 
  durR = pulseIn(EchoR, HIGH);
  local_distR = durR*0.034/2;
  
  return local_distF, local_distL, local_distR;
  
  }

// Move forward function
void advance() {
  //Full speed ahead! channel A
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  analogWrite(3, 255); //motor speed

  //Full speed ahead! channel B
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(11, 255); //motor speed
  delay(1000);
  
  digitalWrite(9, HIGH);
  analogWrite(3, 0); //motor speed
  digitalWrite(8, HIGH);
  analogWrite(11, 0); //motor speed
  }

// Stopping function
void brake()  {
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(3, 0); //motor speed
  analogWrite(11, 0); //motor speed
  }

// Reversing Function
void reverse()  {
  //reverse Thrusters! channel A
  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  analogWrite(3, 125);  //reverse half speed

  //reverse Thrusters!  channel B
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  analogWrite(11, 125);  //reverse half speed
  delay(1000);
  
  digitalWrite(9, HIGH);
  analogWrite(3, 0); //motor speed
  digitalWrite(8, HIGH);
  analogWrite(11, 0); //motor speed
  }

//Left turn Function
void turn_left()  {
  // turning left
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(11, 125);  //reverse half speed

  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  analogWrite(3, 125); //motor speed
  delay(1000);
  
  digitalWrite(9, HIGH);
  analogWrite(3, 0); //motor speed
  digitalWrite(8, HIGH);
  analogWrite(11, 0); //motor speed
  }

//Right turn Function
void turn_right() {
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  analogWrite(11, 125);  //reverse half speed

  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  analogWrite(3, 125); //motor speed
  delay(1000);
  
  digitalWrite(9, HIGH);
  analogWrite(3, 0); //motor speed
  digitalWrite(8, HIGH);
  analogWrite(11, 0); //motor speed
  }


