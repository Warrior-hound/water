#include "HX711.h"
int waterLevelSensorPin = A0; 
const int DOUT = 4;
const int SCLK = 5;  
int pumpPin = 8;              
int solenoidValvePin = 10;     

int waterLevelReading;
int pressureReading;
bool pumpRunning = false;

HX711 scale;

void setup() {
  Serial.begin(9600);

 pinMode(pumpPin, OUTPUT);
  pinMode(solenoidValvePin, OUTPUT);
  scale.begin(DOUT, SCLK);

 Serial.println("Before setting up the scale:");

  Serial.print("read: \t\t");

  Serial.println(scale.read());                                  // print a raw reading from the ADC




  Serial.print("read average: \t\t");

  Serial.println(scale.read_average(20));              // print the average of 20 readings from the ADC




  Serial.print("get value: \t\t");

  Serial.println(scale.get_value(5));                        // print the average of 5 readings from the ADC minus the tare weight (not set yet)




  Serial.print("get units: \t\t");

  Serial.println(scale.get_units(5), 1);   // print the average of 5 readings from the ADC minus tare weight (not set) divided

                                                                                                // by the SCALE parameter (not set yet)




  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details

  scale.tare();                                                                   // reset the scale to 0




  Serial.println("After setting up the scale:");




  Serial.print("read: \t\t");

  Serial.println(scale.read());                 // print a raw reading from the ADC




  Serial.print("read average: \t\t");

  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC




  Serial.print("get value: \t\t");

  Serial.println(scale.get_value(5));                        // print the average of 5 readings from the ADC minus the tare weight, set with tare()




  Serial.print("get units: \t\t");

  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided

                                                                                                // by the SCALE parameter set with set_scale




  Serial.println("Readings:");
}

void loop() {
  waterLevelReading = analogRead(waterLevelSensorPin);

  uint32_t rawData = 0;
  if (waterLevelReading > 300) {
    if (!pumpRunning) {
      digitalWrite(solenoidValvePin, LOW);
      digitalWrite(pumpPin, HIGH);
      pumpRunning = true;
    }
   
     Serial.print("\t| average:\t");

     Serial.println(scale.get_units(10), 1);




     scale.power_down();                                                  // put the ADC in sleep mode

    delay(5000);

   scale.power_up();
    

    
    if (pressureReading >= 1000) {
     
      delay(1000);
      digitalWrite(pumpPin, LOW);
      pumpRunning = false;
    }
  } else {
   
    digitalWrite(pumpPin, LOW);
    pumpRunning = false;
  }
    if (waterLevelReading < 250)
    {
      digitalWrite(solenoidValvePin, HIGH);
      delay(1500);

    }
  
  
  Serial.print("Water Level: ");
  Serial.print(waterLevelReading);


  
  delay(1000); 
}
