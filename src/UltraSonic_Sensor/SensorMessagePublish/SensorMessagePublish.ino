/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Range.h>

int echoPin = A4;
int trigPin = A5;

ros::NodeHandle  nh;
//std_msgs::String str_msg;
//std_msgs::Float64 sr;
sensor_msgs::Range sr;

//ros::Publisher chatter("chatter", &str_msg);

ros::Publisher chatter("ultrasonic/raw", &sr);



//char hello[13] = "hello world!";

void setup()
{
   Serial.begin(9600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
}

long getSonarReadingMillimeters()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  double duration_us = pulseIn(echoPin, HIGH);
  double distance_mm = (duration_us / 58.0) * 10;
  
  
  
  return distance_mm;
}

void loop()
{
  double us = getSonarReadingMillimeters(); //Get distance from wall with ultrasonic sensor
  Serial.println(us/1000);
  delay(20);
  
  //str_msg.data = hello;
  
  us = us/1000;
  sr.range = us;
  sr.min_range = 0.02;
  sr.max_range= 4;
  sr.field_of_view = 0.785;
  sr.header.frame_id = "ultrasonicmodule";
  //str_msg.data= String(us);
  
  chatter.publish(&sr);
  
  //chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
