  
    const int dstartbutton=21;
    const int dmasterswitch=1;
    const int doilpump=2;
    const int dfuelpump=3;
    const int dfuel1=4;
    const int dfuel2=5;
    const int ap1=0;
    const int ap2=1;
    const int ap3=2;
    const int ap5=4;
    const int ap4=3;
    const int aoilpressure=5;
    const int afuelcontrol=6;
    const int at1=7;
    const int at2=8;
    const int at3=9;
    const int at4=10;
    const int at5=11;
    const int aoiltemperature=12;
    const int afueltemperature=13;
    const int amassflow=14;
    const int aoxysensor=15;
    const int dstartservo=6;
    const int dstarter=7;
    const int destop=8;
    const int dignitor=9;
    const int ddataswitch=10;
    const int throttleservo=16;
    const int servo
    float t1=((analogRead(at1)-1.25)/.005);
    float t2=((analogRead(at2)-1.25)/.005);
    float t3=((analogRead(at3)-1.25)/.005);
    float t4=((analogRead(at4)-1.25)/.005);
    float t5=((analogRead(at5)-1.25)/.005);
    float p1=(analogRead(ap1)/.008);
    float p2=(analogRead(ap2)/.008);
    float p3=(analogRead(ap3)/.008);
    float p4=(analogRead(ap4)/.008);
    float p5=(analogRead(ap5)/.008);
    float oilpressure=analogRead(aoilpressure)/.008;
    float oiltemperature=(analogRead(aoiltemperature)-1.25)/.005;
  
       //starting procedure assumptions are: 
    //ignition happens between 5 and 10 psi in the combustor
    //oil pressure of 40 psi and higher must always be maintained
    //starter must run until engine reaches 300 degrees celcius
 
void setup() {

    
    analogReference(DEFAULT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(dstartbutton),start,RISING);
   myservo.attach(13);
}

void loop() {
  while(digitalRead(ddataswitch)==HIGH){
    Serial.print(analogRead(ap1));
    Serial.print(analogRead(ap2));
    Serial.print(analogRead(ap3));
    Serial.print(analogRead(ap4));
    Serial.print(analogRead(ap5));
    Serial.print(analogRead(at1));
    Serial.print(analogRead(at2));
    Serial.print(analogRead(at3));
    Serial.print(analogRead(at4));
    Serial.print(analogRead(at5));
    Serial.print(analogRead(aoiltemperature));
    Serial.print(analogRead(afueltemperature));
    Serial.print(analogRead(amassflow));
    Serial.println(analogRead(aoxysensor));
    servo=analogRead(throttleservo);
    servo=map(throttleservo,0,1023,0,180);
    myservo.write(servo);
    delay(50)
  }
  
  //this is where the safety features will go (overtemp, over pressure and runaway shutoff)
  
}
void start()
    {if(digitalRead(destop)=HIGH)
      Serial.Print("emergency stop is in effect");
    else
     
      
      Serial.print("Starting...");

      digitalWrite(doilpump,HIGH);
          delay(2000);
          if(oilpressure >= 40) {

              if(t5 <= 150) {

                  digitalWrite(dstartservo,HIGH);
                  digitalWrite(dstarter,HIGH);
                  delay(5000);
                      if(ap4 > 5) {

                              digitalWrite(dfuelpump,HIGH);
                              digitalWrite(dfuel1,HIGH);
                              analogWrite(afuelcontrol,10);
                          while(p4 > 5 || p4 < 10) {
                              analogWrite(dignitor,200);
                         
                          }

                      
                      }

                      if(at5>=300){

                          digitalWrite(dfuel2,HIGH);
                          digitalWrite(dfuel1,LOW);

                        }

                      Serial.print("Engine is running and waiting for steady state");
                  }
              }    
    }
//higgy
