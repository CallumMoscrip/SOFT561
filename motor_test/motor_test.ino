#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

long dur;
int dist;
int dist1;

//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  lcd.begin(16,2);

// ------- Quick 3 blinks of backlight  -------------
/*  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on 

  //-------- Write characters on the display ------------------
  // NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hello, world!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("HI!YourDuino.com");
  delay(8000); */
  
  // channel A MOTOR
  pinMode(12, OUTPUT);  //Motor Channel
  pinMode(9, OUTPUT);   //Brake

  // Channel B MOTOR
  pinMode(13, OUTPUT);  //Motor Channel
  pinMode(8, OUTPUT);   //Brake

  //Ultrasound
  pinMode(24, INPUT);   //Echo pin 24 dig
  pinMode(22, OUTPUT);  //Trig Ping pin 22 dig
}

/*
int get_distance(void);
int advance(void);
int brake(void);
int reverse(void);
int turn_left(void);
int turn_right(void);
*/

void loop() 
{

  dist = get_distance();
 /*   if(dist > 10) { 
      advance();
    }
    else  {
      reverse();
      turn_left();
    }
  */
}

int get_distance() {
  int local_dist;
  //Ultrasound Setup
  digitalWrite(22, LOW);  //turning off trig pin
  delayMicroseconds(2);   //delay

  digitalWrite(22, HIGH);
  delayMicroseconds(20);
  digitalWrite(22, LOW);

  dur = pulseIn(24, HIGH);
  local_dist = dur*0.034/2;
  Serial.println(String(dist));
  return local_dist;
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
  }

// Stopping function
void brake()  {
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
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
  }


