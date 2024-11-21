#include <Arduino.h>
#include <ESP32Servo.h>

#define SERVO5PIN 12 //Orange

#define BUTTONMOVE180 15
#define BUTTONMOVE0 16
#define BUTTONSAVE 17
#define BUTTONSTART 18

Servo servo5;

int minUs = 1000;
int maxUs = 2000;

int ButtonMove180val = 0;
int ButtonMove0val = 0;
int ButtonSaveval = 0;
int ButtonStartval = 0;

int ButtonMove180val_last = 0;
int ButtonMove0val_last = 0;
int ButtonSaveval_last = 0;
int ButtonStartval_last = 0;

int counter = 0;

int Delay = 100;

int Save[10];
int savespace = 0;

int pos = 0;      // position in degrees
ESP32PWM pwm;


void setup() {
    // put your setup code here, to run once:
    // Allow allocation of all timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    Serial.begin(9600);

    pinMode(BUTTONMOVE180, INPUT_PULLUP);
    pinMode(BUTTONMOVE0, INPUT_PULLUP);
    pinMode(BUTTONSAVE, INPUT_PULLUP);
    pinMode(BUTTONSTART, INPUT_PULLUP);

    pinMode(SERVO5PIN, OUTPUT);

    servo5.setPeriodHertz(50);      // Standard 50hz servo

    servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe F)
void loop(){
    ButtonMove180val = digitalRead(BUTTONMOVE180);
    ButtonMove0val = digitalRead(BUTTONMOVE0);
    ButtonSaveval = digitalRead(BUTTONSAVE);
    ButtonStartval = digitalRead(BUTTONSTART);

    if(ButtonMove180val == LOW) {
        for(pos; pos <= 180; pos++){
            servo1.write(pos);
            counter++;
            delay(Delay);
            if(counter >= 10){
                counter = 0;
                if(Delay >= 10){
                Delay -= 5;
                }
            }
        }
    }
    else{
        Delay = 100;
    }
    
    if(ButtonMove0val == LOW) {
        for(pos; pos >= 0; pos--){
            servo1.write(pos);
            delay(100);
            counter++;
            delay(Delay);
            if(counter >= 10){
                counter = 0;
                if(Delay >= 10){
                    Delay -= 5;
                }
        }
    }
    }
    else{
        Delay = 100;
    }

    if((ButtonSaveval != ButtonSaveval_last) && (ButtonSaveval == LOW)){
        Save[savespace] = pos;
        savespace++;
        if(savespace <= 9){
            savespace = 0;
        }
    }

    if((ButtonStartval != ButtonStartval_last) && (ButtonStartval == LOW)){
        for(int i = 0; i <= 9; i++){
            servo1.write(save[i]);
            delay(500);
        }
    }

    ButtonSaveval_last = ButtonSaveval;
    ButtonStartval_last = ButtonStartval;
}