// Testskript
#include "LowPower.h"
#include "Adafruit_NeoPixel.h"
#include "IRremote.h"
//Variablendeklaration
  int LAMPE = 4;
  int ONBOARDLED = 13;
  int NUMPIXELS = 10;
  int LED_STRIPE = 8;
  int command=0;
  int brightness=0;
  bool blinkLoop=0;
  int currentMillis=0;
  int previousMillis=0;
  int zyklus=0;

  int IR_RECEIVE_PIN = 3;    
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_STRIPE, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(LAMPE, OUTPUT);
  pinMode(ONBOARDLED, OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.begin(9600);
  pixels.begin();
  LED_Deactivate_OFF();
}
  
void loop() {
  if (IrReceiver.decode()) {
    command=IrReceiver.decodedIRData.command;
    translateIR();
    IrReceiver.resume();
 }

  currentMillis=millis();
  if(currentMillis-previousMillis >= 1000)
  {
    previousMillis=currentMillis;
    zyklus++;
    zyklus=zyklus%4;
  }
  if (zyklus<2){
      digitalWrite(ONBOARDLED,HIGH);
    }else{
      digitalWrite(ONBOARDLED,LOW);
    }

  if (blinkLoop)
  {
    switch(zyklus)
    {
      case 0: LED_Activate_WHITE();break;
      case 1: LED_Activate_GREEN();break;
      case 2: LED_Activate_BLUE();break;
      case 3: LED_Activate_RED();break;
    }
  }
}

void translateIR()
{
  switch(command)  {
  case 69: 
    Serial.println("POWER");
    if (0==brightness)    {
      brightness = 255;
      LED_Activate_WHITE();
    }else{ 
      LED_Deactivate_OFF(); 
    }
    break;
  case 70: Serial.println("VOL+"); break;
  case 71: Serial.println("FUNC/STOP"); break;
  case 68: Serial.println("FAST BACK");    break;
  case 64: Serial.println("PAUSE");    break;
  case 67: Serial.println("FAST FORWARD");   break;
  case 7: Serial.println("DOWN"); LED_Reduce_Brightness();   break;
  case 21: Serial.println("VOL-");    break;
  case 9: Serial.println("UP"); LED_Increase_Brightness();   break;
  case 22: Serial.println("0"); LED_Activate_WHITE();   break;
  case 25: Serial.println("EQ");    break;
  case 13: Serial.println("ST/REPT"); LED_SwitchBlinkActivity();    break;
  case 12: Serial.println("1"); LED_Activate_RED();    break;
  case 24: Serial.println("2"); LED_Activate_GREEN();   break;
  case 94: Serial.println("3"); LED_Activate_BLUE();   break;
  case 8: Serial.println("4");    break;
  case 28: Serial.println("5");    break;
  case 90: Serial.println("6");    break;
  case 66: Serial.println("7");    break;
  case 82: Serial.println("8");    break;
  case 74: Serial.println("9");    break;
  //case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
  default: 
    Serial.println(" other button");
  }// End Case
  delay(200); // Do not get immediate repeat
} //END translateIR

void LED_Reduce_Brightness()
{
  brightness=brightness/2;
  pixels.setBrightness(brightness);
  pixels.show();
}
void LED_Increase_Brightness()
{
  brightness=brightness*2;
  pixels.setBrightness(brightness);
  pixels.show();
}

void LED_Deactivate_OFF()
{
// put your main code here, to run repeatedly:
  pixels.setPixelColor(1, pixels.Color(0,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(2, pixels.Color(0,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(3, pixels.Color(0,0,0)); // Pixel1 leuchtet in der Farbe Grün
  brightness=0;
  pixels.show(); // Durchführen der Pixel-Ansteuerung
}

void LED_Activate_WHITE()
{
  Serial.println("LED_Activate_WHITE");
  pixels.setBrightness(brightness);
// put your main code here, to run repeatedly:
  pixels.setPixelColor(1, pixels.Color(255,255,255)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(2, pixels.Color(255,255,255)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(3, pixels.Color(255,255,255)); // Pixel1 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
}

void LED_Activate_BLUE()
{
  Serial.println("LED_Activate_BLUE");
  pixels.setBrightness(brightness);
  pixels.setPixelColor(1, pixels.Color(0,0,255)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(2, pixels.Color(0,0,255)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(3, pixels.Color(0,0,255)); // Pixel1 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
}

void LED_Activate_GREEN()
{
  Serial.println("LED_Activate_GREEN");
pixels.setBrightness(brightness);
  pixels.setPixelColor(1, pixels.Color(0,255,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(2, pixels.Color(0,255,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(3, pixels.Color(0,255,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
}

void LED_Activate_RED()
{
  Serial.println("LED_Activate_RED");
pixels.setBrightness(brightness);
  pixels.setPixelColor(1, pixels.Color(255,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(2, pixels.Color(255,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.setPixelColor(3, pixels.Color(255,0,0)); // Pixel1 leuchtet in der Farbe Grün
  pixels.show(); // Durchführen der Pixel-Ansteuerung
}

void LED_SwitchBlinkActivity()
{
  blinkLoop= (!blinkLoop);
}
