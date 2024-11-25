/* Aufgabe_F.cpp
 by Nora Hüppi
 
 Like in assigment D and E the servo rotates vrom 180° t0 0° if btnmove0 is pressed, 
 when realised the servo stops. and vice verca if btnmove180 is pressed an realised.
 it still makes 1° steps in both directions. The rotation speed goes faster after 
 every 10 repetitions. Additopnally if you stop the rotation of the servo you can
 press btnsave for a short moment so that a flak is detected and it will save the position
 of the servo in an array. You can safe 10 positions. If you press the btnstart and a flank is
 detected the servo will drive these 10 saved positions, one by one int the order you saved them.

 Connection of the Servos:
 Servo Datapin (Orange/White) -> Pin12
 Servo Vcc (Red) -> 5V
 Servo GND (Brown) -> GND
 
 Connection of BUTTONMOVE180:
 3.3V -> PIN15
 
 Connection of BUTTONMOVE0:
 3.3V -> PIN16

 Connection of BUTTONSAVE:
 3.3V -> PIN17

 Connection of BUTTONSTART:
 3.3V -> PIN18

 created 28 Oktober 2024
 by Nora Hüppi
 edited 21 November 2024
 by Nora Hüppi
*/

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

int LEDPin_Blue = 7;
int LEDPin_Green = 6;
int LEDPin_Red = 5;

int counter = 0;
int Sekundencounter = 0;

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

    //Zieht Button intern auf HIGH
    pinMode(BUTTONMOVE180, INPUT_PULLUP);
    pinMode(BUTTONMOVE0, INPUT_PULLUP);
    pinMode(BUTTONSAVE, INPUT_PULLUP);
    pinMode(BUTTONSTART, INPUT_PULLUP);

    //Bestimmt Servo als Output
    pinMode(SERVO5PIN, OUTPUT);

    //Besstimmt LEDs als Output
    pinMode(LEDPin_Red, OUTPUT);
    pinMode(LEDPin_Blue, OUTPUT);
    pinMode(LEDPin_Green, OUTPUT);

    servo5.setPeriodHertz(50);      // Standard 50hz servo

    servo5.attach(SERVO5PIN, minUs, maxUs);
}

//Aufgabe F)
void loop(){
    ButtonMove180val = digitalRead(BUTTONMOVE180); //Liest Button ein
    ButtonMove0val = digitalRead(BUTTONMOVE0); //Liest Button ein
    ButtonSaveval = digitalRead(BUTTONSAVE); //Liest Button ein
    ButtonStartval = digitalRead(BUTTONSTART); //Liest Button ein

    digitalWrite(LEDPin_Blue, HIGH); //Schreibe LED auf HIGH
    digitalWrite(LEDPin_Green, HIGH); //Schreibe LED auf HIGH
    digitalWrite(LEDPin_Red,LOW); //SChreibe LED auf LOW

    if(ButtonMove180val == LOW) { //Schaut ob Button auf LOW gezogen ist
        digitalWrite(LEDPin_Blue, HIGH); //Schreibe LED auf HIGH
        digitalWrite(LEDPin_Green, LOW); //SChreibe LED auf LOW
        digitalWrite(LEDPin_Red,LOW); //SChreibe LED auf LOW

        Delay = 100; //Setzt delay auf 100
        for(pos; pos <= 180; pos ++){ //Bleibt solange im Loop bis pos auf 180 ist
            servo5.write(pos); //schreibt die position ins Servo
            counter++; //Zählt counter hoch
            ButtonMove180val = digitalRead(BUTTONMOVE180); //Liest Button ein
            //Wenn Button HIGH ist dann geht es asu dem For
            if (ButtonMove180val == HIGH){ 
                break;
            }
            delay(Delay); //
            if(counter >= 10){
                if(Delay >= 10){
                    Delay -= 10;
                }
                counter = 0;
            }
        }
    }

    if(ButtonMove0val == LOW) {
        digitalWrite(LEDPin_Blue, LOW);
        digitalWrite(LEDPin_Green, HIGH); //Schreibe LED auf HIGH
        digitalWrite(LEDPin_Red,LOW);

        Delay = 100;
        for(pos; pos <= 180; pos ++){
            servo5.write(pos);
            counter++;
            ButtonMove0val = digitalRead(BUTTONMOVE0);
            if (ButtonMove0val == HIGH){
                break;
            }
            delay(Delay);
            if(counter >= 10){
                if(Delay >= 10){
                    Delay -= 10;
                }
                counter = 0;
            }
        }
    }

    if((ButtonSaveval != ButtonSaveval_last) && (ButtonSaveval == LOW)){
        digitalWrite(LEDPin_Blue, LOW);
        digitalWrite(LEDPin_Green, LOW);
        digitalWrite(LEDPin_Red,HIGH); //Schreibe LED auf HIGH      

        Save[savespace] = pos;
        savespace++;
        if(savespace >= 9){
            savespace = 0;
        }
    }

    if((ButtonStartval != ButtonStartval_last) && (ButtonStartval == LOW)){
        savespace = 0;
        for(savespace >= 0; savespace <= 9; savespace++){
            digitalWrite(LEDPin_Blue, LOW);
            digitalWrite(LEDPin_Green, HIGH);
            digitalWrite(LEDPin_Red,HIGH);         
            servo5.write(Save[savespace]);
            delay(1000);
        }
    }

    ButtonSaveval_last = ButtonSaveval;
    ButtonStartval_last = ButtonStartval;
}