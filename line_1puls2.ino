/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
*/
//#include <MsTimer2.h>
int zad = 100, trig = 0;
unsigned long imp = 0, imp1 = 0, i = 0;

String str;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  TCCR1A = 0; TCCR1B = 0;
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  static uint32_t reqfreq = 10000; //переменная запроса частоты
  uint32_t ocr = OCR1A;  uint16_t divider = 1;  float freq;

  if (Serial.available() > 0) {
//imp=Serial.read();
    str = Serial.readString();
    Serial.println(str);
    if (str == "m")trig = 1;
    if (str == "c")trig = 2;
    if (str != "c" && str != "m") {
      //imp = constrain(imp, 0, 50000000);
      imp = str.toInt();
    }
  }
  if(imp>0) digitalWrite(11, HIGH); 
  // delayMicroseconds(300);
  while (imp > 0 && trig==2)
  { //digitalWrite(11, HIGH); 

    if (reqfreq == 0 || reqfreq > F_CPU / 2) {  return;    }
    
    ocr = (F_CPU / reqfreq / 2 / divider);
    
    byte shifts[] = {3, 3, 2, 2};
    for (byte i = 0; i < 4; i++) {
      if (ocr > 65536) {        divider <<= shifts[i];
        ocr = F_CPU / reqfreq / 2 / divider;      }
      else {        TCCR1B = (i + 1) | (1 << WGM12);   //Mode4 (CTC)
        break;      }}
 // if(imp>1) {
   OCR1A = ocr - 1; TCCR1A = 1 << COM1A0;//}
    //  else { 
    delayMicroseconds(imp);
   // delay(imp);
   // if(imp==1)  {OCR1A = ocr - 1; TCCR1A = 0;}
    //  }
    //freq = (float) F_CPU / 2 / (OCR1A + 1) / divider;
    //if (freq < 10000) {      Serial.print(freq, 1);      Serial.println(" Hz "); }
    //if (freq >= 10000) { Serial.print(freq / 1000, 3); Serial.println(" kHz"); }
  // delayMicroseconds(imp);
   //imp--;
    OCR1A = ocr - 1; TCCR1A = 0;
    imp=0;
  }
  
// if(imp>0) digitalWrite(11, HIGH); 
  // delayMicroseconds(300);
  while (imp > 0  && trig==1)
  { //digitalWrite(11, HIGH); 

    if (reqfreq == 0 || reqfreq > F_CPU / 2) {  return;    }
    
    ocr = (F_CPU / reqfreq / 2 / divider);
    
    byte shifts[] = {3, 3, 2, 2};
    for (byte i = 0; i < 4; i++) {
      if (ocr > 65536) {        divider <<= shifts[i];
        ocr = F_CPU / reqfreq / 2 / divider;      }
      else {        TCCR1B = (i + 1) | (1 << WGM12);   //Mode4 (CTC)
        break;      }}
 // if(imp>1) {
   OCR1A = ocr - 1; TCCR1A = 1 << COM1A0;//}
    //  else { 
    //delayMicroseconds(imp);
    delay(imp);
   // if(imp==1)  {OCR1A = ocr - 1; TCCR1A = 0;}
    //  }
    //freq = (float) F_CPU / 2 / (OCR1A + 1) / divider;
    //if (freq < 10000) {      Serial.print(freq, 1);      Serial.println(" Hz "); }
    //if (freq >= 10000) { Serial.print(freq / 1000, 3); Serial.println(" kHz"); }
  // delayMicroseconds(imp);
   //imp--;
    OCR1A = ocr - 1; TCCR1A = 0;
    imp=0;
  } 
  digitalWrite(11, LOW);

}
