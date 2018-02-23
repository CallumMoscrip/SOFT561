#include <TimerOne.h>

#define trigPin 12
#define echoPin 2
#define echo_int 0
#define TIMER_uS 50
#define TICK_COUNTS 4000

volatile long echo_start = 0;
volatile long echo_end = 0;
volatile long echo_duration = 0;
volatile int trigger_time_count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Ultrasound
  pinMode(echoPin, INPUT);   //Echo pin 24 dig
  pinMode(trigPin, OUTPUT);  //Trig Ping pin 22 dig

  Timer1.initialize(TIMER_uS);
  Timer1.attachInterrupt( timerIsr );
  attachInterrupt(echo_int, echo_interrupt, CHANGE);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(echo_duration/58);
  delay(200);
  
}

void timerIsr() {
  trigger_pulse();
}


void trigger_pulse() {
  static volatile int state = 0;

  if (!(--trigger_time_count)) {
    trigger_time_count = TICK_COUNTS;
    state = 1;
  }
  switch(state) {
    case 0:
      break;

    case 1:
      digitalWrite(trigPin, HIGH);
      state = 2;
      break;

    case 2:
    default:
      digitalWrite(trigPin, LOW);
      state = 0;
      break;
    }
}

void echo_interrupt() {
  switch (digitalRead(echoPin)) {
    case HIGH:
      echo_end = 0;
      echo_start = micros();
      break;

    case LOW:
      echo_end = micros();
      echo_duration = echo_end - echo_start;
      break;
  }
}


