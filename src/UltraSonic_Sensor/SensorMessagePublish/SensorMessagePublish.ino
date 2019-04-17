/*
 * The following code prints the values of the Ultrasonic Distance Sensor to the 
 * Serial Monitor and Publishes the same to a Topic ultrasonic/raw
*/
#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Range.h>

int echoPin = A4;
int trigPin = A5;

ros::NodeHandle  nh;
//std_msgs::String str_msg;
//std_msgs::Float64 sr;
sensor_msgs::Range sr;
//sr object of message type Range in Ros package sensor_msgs


//ros::Publisher chatter("chatter", &str_msg);

//Declaring publisher of name chatter publishing a topic ultrasonic/raw
ros::Publisher chatter("ultrasonic/raw", &sr);



//char hello[13] = "hello world!";

void setup()
{
   Serial.begin(9600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  //initializing rosnode handle named nh
  nh.initNode();
  //advertising the publisher named chatter
  nh.advertise(chatter);
}

//function for sonar readings
double getSonarReadingMillimeters()
{
  //setting digital pin as low and high with a delay of 10microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  double duration_us = pulseIn(echoPin, HIGH);
  double distance_mm = (duration_us / 58.0) * 10;
  
  
  //returning distance with data type double
  return distance_mm;
}

void loop()
{
  double us = getSonarReadingMillimeters(); //Get distance from wall with ultrasonic sensor
  //printing to serial monitor
  Serial.println(us/1000);
  delay(20);
  
  //str_msg.data = hello;
  
  //converting millimeter to meter
  us = us/1000;
  // setting value to variable range in object sr of message type Range
  sr.range = us;
  sr.min_range = 0.02;
  sr.max_range= 4;
  sr.field_of_view = 0.785;
  sr.header.frame_id = "ultrasonicmodule";
  //str_msg.data= String(us);
  
  //publishing the object sr under the topic ultrasonic/raw
  chatter.publish(&sr);
  
  //chatter.publish( &str_msg );
  
  //continuous iteration of the ros node handle
  nh.spinOnce();
  
  //delay of 1000 milliseconds or 1 second
  delay(1000);
}
