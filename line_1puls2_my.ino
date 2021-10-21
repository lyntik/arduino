1/*
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

const uint32_t reqfreq = 20000;

String str;


// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin 13 as an output.
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  TCCR1A = 0; TCCR1B = 0;
  Serial.begin(9600);
}

void fuckingGO_MS(unsigned long ms)
{
  Serial.println("fucking go ms");
  Serial.println(ms);
  
  uint32_t ocr = OCR1A;
  uint16_t divider = 1; 
  
  if (reqfreq == 0 || reqfreq > F_CPU / 2) { return; }
  
  ocr = (F_CPU / reqfreq / 2 / divider);
  
  byte shifts[] = {3, 3, 2, 2};
  for (byte i = 0; i < 4; i++) 
  {
    if (ocr > 65536) 
    {
      divider <<= shifts[i];
      ocr = F_CPU / reqfreq / 2 / divider;      
    }
    else 
    {
      TCCR1B = (i + 1) | (1 << WGM12);   //Mode4 (CTC)
      break;      
    }
  }

  OCR1A = ocr - 1; TCCR1A = 1 << COM1A0;
  delay(ms);
  OCR1A = ocr - 1; TCCR1A = 0;
}

void fuckingGO_US(unsigned long us)
{
  Serial.println("fucking go us");
  Serial.println(us);

  uint32_t ocr = OCR1A;
  uint16_t divider = 1; 
  
  if (reqfreq == 0 || reqfreq > F_CPU / 2) { return; }
  
  ocr = (F_CPU / reqfreq / 2 / divider);
  
  byte shifts[] = {3, 3, 2, 2};
  for (byte i = 0; i < 4; i++) 
  {
    if (ocr > 65536) 
    {
      divider <<= shifts[i];
      ocr = F_CPU / reqfreq / 2 / divider;      
    }
    else 
    {
      TCCR1B = (i + 1) | (1 << WGM12);   //Mode4 (CTC)
      break;      
    }
  }

  OCR1A = ocr - 1; TCCR1A = 1 << COM1A0;
  delayMicroseconds(us);
  OCR1A = ocr - 1; TCCR1A = 0;
}


void moveMotor(int32_t imp)
{
  uint32_t ocr = OCR1A;  
  
  if (imp>0) digitalWrite(11, HIGH); 
  else digitalWrite(11, LOW);
  imp = abs(imp);
  
  Serial.println(imp);
  unsigned long timeUS = imp*50;
  Serial.println("time to go (us):");
  Serial.println(timeUS);
      
  while (timeUS > 0)
  {
      if (timeUS > 1000)
      {
        unsigned long ms = timeUS / 1000;
        fuckingGO_MS(ms);
        timeUS -= ms * 1000;
      }      
      else
      {
        fuckingGO_US(timeUS);
        timeUS = 0;
      }
  }
  
  digitalWrite(11, LOW);      
}

// the loop function runs over and over again forever
void loop() 
{
  
  if (Serial.available() > 0) 
  {

    str = Serial.readString();
    Serial.println(str);
    
    if (str == "t")
    {
      int sensorValue = analogRead(A1);
      Serial.println(sensorValue);
      sensorValue = analogRead(A6);
      Serial.println(sensorValue);
    }
    else if (str == "h1")
    {
      while (analogRead(A6) < 1000)
        moveMotor(-10000);
    }    
    else if (str == "h2")
    {
      while (analogRead(A1) < 1000)
        moveMotor(10000);
    }        
    else 
    {
      //imp = constrain(imp, 0, 50000000);
      int32_t imp = str.toInt();
      Serial.println(imp);
      
      //unsigned long timeUS = imp*100;
      //Serial.println(timeUS);
      if (imp != 0)
        moveMotor(imp);
      
     
      /*if (imp>0) digitalWrite(11, HIGH); 
      else digitalWrite(11, LOW);
      imp = abs(imp);
        
      
      fuckingGO_MS(imp);*/
      
    }
    
    Serial.println("end");
  }
  

  


}
