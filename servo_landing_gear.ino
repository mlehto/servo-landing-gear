#include <Servo.h>

//Code to control servo output with smooth start & stop based on PWM input
//from RC receiver.

float current_pos;
float target_pos;
float distance_to_target;
int easing_distance = 200;
int reverse;

float max_step = 0.23;
float required_step;

Servo fl_motor;
float fl_min = 1110;
float fl_max = 2150;

void setup() {
   target_pos = 1000;
   current_pos = 1000;
   fl_motor.attach(9);
}

void loop() {
  if (millis() - reverse > 3000) {
    if (target_pos == 1000) {target_pos = 0;}
    else {target_pos = 1000;}
    reverse = millis();
  }
  
  required_step = target_pos - current_pos;
  if (required_step > max_step) required_step = max_step;
  if (required_step < -max_step) required_step = -max_step;
  distance_to_target = abs(target_pos - current_pos);
  if (distance_to_target < easing_distance) {required_step = required_step * abs(target_pos - current_pos) / easing_distance;}
  if (distance_to_target > 1000 - easing_distance) {required_step = required_step * (1000 - easing_distance) / distance_to_target;}
  
  current_pos = current_pos + required_step;
  
  fl_motor.writeMicroseconds( (int)map(current_pos, 0, 1000, fl_min, fl_max) );
}
