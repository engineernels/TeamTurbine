  
    # include <Servo.h>
    # include <SPI.h>
    # include "Adafruit_MAX31855.h"
    # include "Adafruit_MAX6675.h"

    const int dstartbutton=21;
    const int dmasterswitch=1;
    const int dignitor=5;
    const int doilpump=9;
    const int dfuelpump=8;
    const int dfuel_start=10;
    const int dfuel_run=11;
    const int ap2=0;
    const int ap3=1;
    const int ap4=2;
    const int ap5=3;
    const int ap6=4;
    const int aoilpressure=5;
    const int afuelpressure=6;
    const int astrain=7;
    const int amassflow=14;
    const int cs1=22;
    const int clk1=23;
    const int do1=24;
    const int cs2=25;
    const int clk2=26;
    const int do2=27;
    const int cs3=28;
    const int clk3=29;
    const int do3=30;
    const int cs4=31;
    const int clk4=32;
    const int do4=33;
    const int cs5=34;
    const int clk5=35;
    const int do5=36;
    const int cs6=37;
    const int clk6=38;
    const int do6=39;
    const int vcc6=40;
    const int gnd6=41;
    float p2=((analogRead(ap2)*0.363)-3.6918); // 30=.0363x-3.6918
    float p3=((analogRead(ap3)*0.363)-3.6918); 
    float p4=((analogRead(ap4)*0.363)-3.6918);
    float p5=((analogRead(ap5)*0.363)-3.6918);
    float p6=((analogRead(ap6)*0.363)-3.6918);
    float oilpressure=((analogRead(aoilpressure)*0.1213)-11.999); //100=0.1213x-11.999
    float fuelpressure=((analogRead(afuelpressure)*0.1822)-18.268); //150=0.1822x-18.268
    float thrust=((analogRead(astrain)*23041.47)/604); //thrust=stain*Wconstant/gain
    Servo starter;
    int s_val=0;

    Adafruit_MAX31855 thermocouple1(cs1, clk1, do1);
    Adafruit_MAX31855 thermocouple2(cs2, clk2, do2);
    Adafruit_MAX31855 thermocouple3(cs3, clk3, do3);
    Adafruit_MAX31855 thermocouple4(cs4, clk4, do4);
    Adafruit_MAX31855 thermocouple5(cs5, clk5, do5);
    MAX6675 thermocouple6(cs6, clk6, do6);
    
       //starting procedure assumptions are: 
    //ignition happens between 5 and 10 psi in the combustor
    //oil pressure of 40 psi and higher must always be maintained
    //starter must run until engine reaches 300 degrees celcius
 
void setup() {

    while (!Serial);
    analogReference(DEFAULT);
    Serial.begin(9600);
    pinMode(vcc6, OUTPUT); digitalWrite(vcc6, HIGH);
    pinMode(gnd6, OUTPUT); digitalWrite(gnd6, HIGH);
    starter.attach(9);
    starter.writeMicroseconds(2000);
    while (!Serial.available());
    Serial.read();
    starter.writeMicroseconds(700);
    attachInterrupt(digitalPinToInterrupt(dstartbutton),start,RISING);
    
    delay(500)
  
}

void loop() {
  while(digitalRead(ddataswitch)==HIGH){
    Serial.print(p2);
    Serial.print(p3);
    Serial.print(p4);
    Serial.print(p5);
    Serial.print(p6);
    Serial.print(thermocouple1.readFarenheit());
    Serial.print(thermocouple2.readFarenheit());
    Serial.print(thermocouple3.readFarenheit());
    Serial.print(thermocouple4.readFarenheit());
    Serial.print(thermocouple5.readFarenheit());
    Serial.print(thermocouple6.readFarenheit());
    Serial.print(thrust);
    Serial.print(analogRead(amassflow));
    Serial.println(analogRead(aoxysensor));
    servo=analogRead(throttleservo);
    servo=map(throttleservo,0,1023,0,179);
    myservo.write(servo);
    delay(5000)
  }
  
  //this is where the safety features will go (overtemp, over pressure and runaway shutoff)
  
}
void start()
    {if(digitalRead(destop)=HIGH)
      Serial.Print("emergency stop is in effect");
    else
     
      
      Serial.print("Starting...");

      digitalWrite(doilpump,HIGH);
      digitalWrite(dfueilpump,HIGH);
      delay(2000);
          if(oilpressure >= 40) {
              
              starter.write(s_val);
              while (s_val < 90) {
                s_val=s_val+5;
                starter.write(s_val);
                delay(500)
              }
            

              if(t5 <= 150) {

                  digitalWrite(dstartservo,HIGH);
                  digitalWrite(dstarter,HIGH);
                  delay(5000);
                      if(ap4 > 5) {

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
