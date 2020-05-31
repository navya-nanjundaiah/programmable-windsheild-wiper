# include <Servo.h>
# include <EEPROM.h>
Servo myservo;
int LED=4;
int buzz_1=5;
int buttonpin=2;
byte value;
int addr = 0;
int angle,e ;
int initial =0;
int button_pressed_loop;
int seq[60];
//long lastDebounceTime = 0;  // the last time the output pin was toggled
//long debounceDelay = 50;
const int buttonPin = 2;
//volatile byte buzzer=LOW;
boolean buttonState = LOW; 
boolean lastButtonState = LOW; 
int button;
int pressed=0;
int val=0;
int pos=0;
  int i=0;
  int k=0;
  int j=0;
    int l=0;
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 4000; 
void setup() {
    Serial.begin(9600); 
    pinMode(LED,OUTPUT);
    pinMode(buzz_1,OUTPUT);
    myservo.attach(9);
    pinMode(buttonpin,INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonpin),buzzer,HIGH);
 //tone(5, 242, 10);
}

void loop() {
    // Serial.println("ready");
     button= Button_Pressed(); 
   
     switch(button)
     {
         case 1:
              digitalWrite(LED,HIGH);
              play_seq();        
              break;
       case 2:
              Serial.println("code 2");
              digitalWrite(LED,HIGH);
              loop_seq();
              break;
       case 3:
            tone(5,3500,1000);
            digitalWrite(LED,HIGH);
            Programming_Mode();
            break;
       case 4:
            //myservo.write(135);
            k=0;
            while(k<=3)
            {
                Serial.println("code 4");
                digitalWrite(LED,HIGH);
                delay(500);
                digitalWrite(LED,LOW);
                delay(500);
                k++;
            }
            for (int e = 0 ; e < 60 ; e++) {
                   EEPROM.write(e, seq[e]);
            }  
            tone(5,3500,1000);        
            break;
      case 6:
            while(l<=5)
            {
                digitalWrite(LED,HIGH);
                Serial.println("code 6");
                delay(500);
                digitalWrite(LED,LOW);
                delay(500);
                l++;
            }
            for (e = 0 ; e < EEPROM.length() ; e++) {
                   EEPROM.write(e, 0);
            }
            tone(5,3500,1000);
            break;
     default:
            digitalWrite(LED,HIGH);
           
            //tone(5, 242, 10);
          //  noTone(6);
            break;
  } //End of Switch

  if(initial == 0)
  {
       tone(5,3500,1000);
      myservo.write(180);
     Serial.println("setup");
     noTone(6);
     initial++;
  }
} //Emd of Loop

void Programming_Mode(){
  int count = 0;
  Serial.println("Programming Mode");
       while(1){
          angle = Button_Pressed();
          seq[count] = 0;
          if(angle>=6){
            Serial.println("Going to ready");
            break;
          }
          k = 0;
          //poition led blink starts
           while(k<count+1 & angle > 0)
            {
                Serial.println(k);
                Serial.println(count);
                digitalWrite(LED,HIGH);
                delay(200);
                digitalWrite(LED,LOW);
                delay(200);
                k++;
            }
            digitalWrite(LED,HIGH);
            //ends
          switch(angle){
              case 1:
                myservo.write(0);
                Serial.println("angle 0");
                  action(angle);
                  seq[count] = angle;
                  count++;
                break;
              case 2:
                myservo.write(45);
                Serial.println("angle 45");
                  action(angle);
                  seq[count] = angle;
                  count++;
                break;
              case 3:
                  myservo.write(90);
                  Serial.println("angle 90");
                                    action(angle);
                  seq[count] = angle;
                  count++;
                  break;
             case 4:
                  myservo.write(135);
                  Serial.println("angle 135");
                  action(angle);
                  seq[count] = angle;
                  count++;
                  break;
             case 5:
                  myservo.write(180);
                  Serial.println("angle 180");
                  action(angle);
                  seq[count] = angle;
                  count++;
                  break;
           }
       }
}// end of programming mode
//////////////////////////////////////////////////////////// 
void action(int angle){          

              switch(angle){
              case 1:
                myservo.write(0);
                Serial.println("angle 0");
                break;
              case 2:
                myservo.write(45);
                Serial.println("angle 45");
                break;
              case 3:
                  myservo.write(90);
                  Serial.println("angle 90");
                  break;
             case 4:
                  myservo.write(135);
                  Serial.println("angle 135");
                  break;
             case 5:
                  myservo.write(180);
                  Serial.println("angle 180");
                  break;
              }
     }

////////////////////////////////////////////////////
void play_seq()
{  
    for (e = 0 ; e < EEPROM.length() ; e++) {
                   value = EEPROM.read(e);
                   if(value == 0)
                      break;
                   action(value);                 
                   Serial.print(value);
                   delay(1000);
      } 
}
////////////////////////////////////////////
void loop_seq(){
  //button_pressed_loop = 0;
  while(1)
  {
    
   // button_pressed_loop = Button_Pressed();
    if(button_pressed_loop > 0)
    {
      Serial.println("Existing the loop... Going to ready....");
      break;
    }
   
      for (e = 0 ; e < EEPROM.length() ; e++) {
                   value = EEPROM.read(e);
                   if(value == 0)
                      break;
                   action(value);    
                   button_pressed_loop += Button_Pressed(); 
                    if(button_pressed_loop > 0)
                    {
                       break;
                    }            
                   
                   delay(1000);
      } 
  }
  
}


/////////////////////////////////////////////
int Button_Pressed(){
  pressed =0;
 do {
  if(debounceButton(buttonState) == HIGH && buttonState == LOW)
  {
        pressed++;
        buttonState = HIGH;
        lastDebounceTime = millis();
        Serial.println(pressed);
  }
  else if(debounceButton(buttonState) == LOW && buttonState == HIGH)
  {
       buttonState = LOW;
     //  lastDebounceTime = millis();
  }
  }while((millis() - lastDebounceTime) < debounceDelay);
  
  lastDebounceTime=0;
  if(pressed >0){
      Serial.println("Button Pressed ");
      Serial.print(pressed);
      return pressed;
  }
 
}
/////////////////////////////////////////
 void buzzer()
{
  tone(6, 3322, 100);
 

  // turn off tone function for pin 6:
  noTone(6);
}
/////////////////////////////////////////////////////////////////
boolean debounceButton(boolean state)
{
  boolean stateNow = digitalRead(buttonpin);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(buttonpin);
  }
  return stateNow;
}
