#include <Servo.h>

Servo esc1;           // create servo object to control an esc
Servo esc2;           // create servo object to control an esc

// NOTE: PLEASE SET VALUES TO ACTUAL PINS!
int balance_in = 1;     // potentiometer in for motor fine balancing
int balance;            // motor fine balancing value;
int balance_range = 10;
int power_in = 2;     // potentiometer in for motor power setting
int power;            // motor power value;
int power_min = 90;    // minimal power output on trigger_down
int power_max = 180;  // maximal power output on trigger_down
int ESC_ONE_OUT = 3;  // output pin for flywheel motor esc 1
int ESC_TWO_OUT = 4;  // output pin for flywheel motor esc 2
int trigger = 5;      // switch in for triggering the flywheel motors
                      // -> the firing trigger is not controlled by the arduino, as there is no need to.
                      //    it's directly wired to the feedbelt motor.

void setup() {
  // put your setup code here, to run once

  esc1.attach(ESC_ONE_OUT); // attach esc1 servo object to the correct output pin. 
  esc2.attach(ESC_TWO_OUT); // attach esc1 servo object to the correct output pin. 

  // delay loop, long enough for escs to boot withpout input from arduino.
  // this prevents reprogramming the escs accidentally.
}

void loop() {
  // put your main code here, to run repeatedly

  //update balance and power values from potentiometers, mapping values from 0-1024 to 0-180 
  balance = analogRead(balance_in);
  balance = map(balance, 0, 1023, 0-balance_range, balance_range);
  power = analogRead(power_in);
  power = map(power, 0, 1023, power_min, power_max);

  //if trigger circuit is closed, the motor speed is updated. if not, the motors power down.
  if (digitalRead(trigger) == HIGH) {
 
    esc1.write(power + balance);
    esc2.write(power - balance);
    
  } else {
    
    esc1.write(0);
    esc2.write(0);
    
  }
}
