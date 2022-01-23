#include "SoftwareSerial.h" //library for communication

#define echo 2 // connect echo pin to arduino D2 (ultra sonic sensor)
#define trig 3 // connect trig pin to arduino D3 (ultra sonic sensor)

long duration; // store time duration of sound travel
double first_distance; // store actual distance 
double second_distance;
double distance; 
double speed;

SoftwareSerial mySerial(7, 8); // RX, TX // creation of object 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(echo, INPUT); // Sets the echoPin as an Input
  pinMode(trig, OUTPUT); //Sets the trigPin as an Output
}
void loop() { // run over and over
  first_distance = checkDistance(); //calls function checkDistance();
  delay(1000); //giving a time gap of 1 sec
  second_distance=checkDistance();
  //formula change in distance divided by change in time
  speed = (second_distance - first_distance)/1.0; //as the time gap is 1 sec we divide it by 1.
  //Displaying  distances and speed
  Serial.print("Speed in cm/s  :  "); 
  Serial.println(speed);
  sendSMS("+255766089662", " First distance is " + String(first_distance) + " Cm \n" "Second distance is " +String(second_distance) + " cm\n " " Speed is " + String(speed) ); // send msg one time#
  delay(100);
}
double checkDistance() {
  digitalWrite(trig, LOW);
  delay(1000);
  digitalWrite(trig, HIGH); // triger signal as datasheet
  delay(1000);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH); 
  distance = duration * (0.034 / 2.00); // speed of sound
  // Prints the distance on the Serial Monitor
  Serial.print("Distance in cm :");
  Serial.println(distance);

  return distance;
}
void sendSMS(String mobileNUmber, String msgBody) {
  mySerial.println("AT"); // check connection
    delay(1000);
    mySerial.println("AT+CMGF=1");// SET MODULE TO TEXT MODE
    delay(1000);
    mySerial.println("AT+CMGS=\"" + mobileNUmber + "\""); // sender mob number
  delay(1000);
  mySerial.println(msgBody); // enter msg body
  delay(1000);
  mySerial.print((char)26); // send msg
  delay(1000);
}

double checkDistance_real(){
  double number=checkDistance();
  if(number>=20){
    Serial.print(checkDistance());
  }
  else{
  }
  }
