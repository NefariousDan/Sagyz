//Include the library
#include <MQUnifiedsensor.h>

//Definitions
#define placa "ESP-32"
#define Voltage_Resolution 3.3
#define pin 26 //Analog input 0 of your arduino
#define type "MQ-8" //MQ8
#define ADC_Bit_Resolution 12 // For arduino UNO/MEGA/NANO
#define RatioMQ8CleanAir 70   //RS / R0 = 70 ppm  
//#define calibration_button 13 //Pin to calibrate your sensor

//Declare Sensor
MQUnifiedsensor MQ8(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

bool isPresent_MQ8 = false;

double valueOf_MQ8;

void detectH2(void* pvParameters){

  //Set math model to calculate the PPM concentration and the value of constants
  MQ8.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ8.setA(976.97); MQ8.setB(-0.688); // Configure the equation to to calculate H2 concentration

  MQ8.init();   
  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ8.setRL(10);
  */

  MQ8.setRL(10);
  MQ8.readSensor();
  float tempPPM = 0;
  bool isConnected = true;

  Serial.print("Calibrating please wait.");
  
  MQ8.update();

  float temp = MQ8.getVoltage();

  
  float calcR0 = 0;
  for(int i = 1; i<=20; i ++)
  {
    temp = MQ8.getRS();

    MQ8.update(); // Update data, the arduino will read the voltage from the analog pin
    
    calcR0 += MQ8.calibrate(RatioMQ8CleanAir);

    Serial.println(abs(MQ8.getRS() - temp));
    if (abs(MQ8.getRS() - temp) > 1) {
      isConnected = false;
    }
    delay(20);
  }

  MQ8.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0) {Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
  if(!isConnected) {Serial.println("Bad connection! Restart!"); while(1);}

  while (1) {
    float tempyT = MQ8.getVoltage();

    MQ8.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ8.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    valueOf_MQ8 = MQ8.readSensor();
    //MQ8.serialDebug(); // Will print the table on the serial port

    delay(700); //Sampling frequency

    if (abs(MQ8.getVoltage() - tempyT) > 0.5) {
      Serial.println("Disconnected, please connect again"); isConnected = false; 
    
      while (!isConnected) {
        tempyT = MQ8.getVoltage();
      
        MQ8.update();
        MQ8.readSensor();
      
        delay(700);

        if (abs(MQ8.getVoltage() - tempyT) > 0.5) {
          int loopCnt = 0, successCnt = 0;

          Serial.print("Connecting");
          while (loopCnt < 3) {
            tempyT = MQ8.getVoltage();
      
            MQ8.update();
            MQ8.readSensor();
      
            delay(700);

            if (abs(MQ8.getVoltage() - tempyT) < 0.5) {
              Serial.print(".");
              successCnt++;
            }
            loopCnt++;
          }

          if (successCnt == 3) {
            Serial.println("Connected!"); isConnected = true;
          }
          else {
            Serial.println("There was an error. Try again!!"); isConnected = false;
          }
        }
      }; 
    }
  }
}