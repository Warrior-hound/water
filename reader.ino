 #include "HX710B.h"
int waterLevelSensorPin = A0; 
const int DOUT = 4;
const int SCLK = 5;  
int pumpPin = 8;              
int solenoidValvePin = 10;     

int waterLevelReading;
int pressureReading;
bool pumpRunning = false;

HX710B pressure_sensor(DOUT, SCLK);

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(solenoidValvePin, OUTPUT);
  
  Serial.begin(9600);

  if (!pressure_sensor.init()) {
Serial.println("No pressure Sensor");
}
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
   
    if (pressure_sensor.read(&rawData, 1000UL) != HX710B_OK) Serial.println("Error in Sensor");
    else {
    Serial.println("Pressure is");
    Serial.println((unsigned long) rawData);
  }
    

    
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
  Serial.print("\t Pressure: ");
  Serial.println((unsigned long) rawData);
  

  
  delay(1000); 
}