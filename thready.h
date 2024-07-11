//Include the library
#include <MQUnifiedsensor.h>
#include "Adafruit_TCS34725.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 33
//Definitions
#define placa "ESP-32"
#define Voltage_Resolution 3.3
#define pinH2 25 //Analog input 0 of your arduino
#define pinCO2 26 //TODOTODTODOAnalog input 0 of your arduino
#define typeH2 "MQ-8" //MQ8
#define typeCO2 "MQ-135" //MQ135
#define ADC_Bit_Resolution 12 // For arduino UNO/MEGA/NANO
#define RatioMQ8CleanAir 70   //RS / R0 = 70 ppm  
#define RatioMQ135CleanAir 3.6
//#define calibration_button 13 //Pin to calibrate your sensor



//*** PH_VALUES_START

const int phPin = 32;

// Calibration values
const float voltageStep = 3.3/4095.0;
const float neutralVoltage = 2.20; // Voltage at pH 7
const float alkalineVoltage = 2.30;   // Voltage at pH 2

int phSensorValue = 0;

//*** PH_VALUES_END


//Declare Sensor
MQUnifiedsensor MQ8(placa, Voltage_Resolution, ADC_Bit_Resolution, pinH2, typeH2);
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pinCO2, typeCO2);

bool isPresent_MQ8 = false;
bool isPresent_MQ135 = false;

double valueOf_MQ8;
double valueOf_MQ135;
double valueOf_Temperature;

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;
TaskHandle_t Task5;
TaskHandle_t Task6;

float r, g, b;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

void drawGraph(void* pvParameters) {
  plotTime.push(0);
  while (1) {
    if (drawingGraph) {

      if (drawH2) {
        Serial.print("H2: "); Serial.println(valueOf_MQ8);
        plotTemp.push(valueOf_MQ8);
        plotTime.push((stoppingDrawTime + millis() - startingDrawTime) / 1000);
      }
      else if (drawCO2) {
        Serial.print("CO2: "); Serial.println(valueOf_MQ135);
        plotTemp.push(valueOf_MQ135);
        plotTime.push((stoppingDrawTime + millis() - startingDrawTime) / 1000);
      }
      else if (drawTemperature) {
        Serial.print("Temperature: "); Serial.println(valueOf_Temperature);
        plotTemp.push(valueOf_Temperature);
        plotTime.push((stoppingDrawTime + millis() - startingDrawTime) / 1000);
      }

      if ((stoppingDrawTime + millis() - startingDrawTime) / 1000 > 20) {
        plotTime.shift();
        plotTemp.shift();
        xinc = 5;
        minX += 1;
      }

      delay(100);
      plotGraphP();
    }
    else {
      delay(50);
    }
  }
}


void detectH2(void* pvParameters){

  startText = "Loading";

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
    if (abs(MQ8.getRS() - temp) > 3) {
      isConnected = false;
    }
    delay(20);
  }

  MQ8.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0) {Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
  if(!isConnected) {Serial.println("Bad connection! Restart!"); startText = "Failed, try again!"; vTaskDelete(NULL);}



  while (1) {
    isPresent_MQ8 = true;
    float tempyT = MQ8.getVoltage();

    MQ8.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ8.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    valueOf_MQ8 = MQ8.readSensor();
    //MQ8.serialDebug(); // Will print the table on the serial port

    delay(700); //Sampling frequency

    // if (abs(MQ8.getVoltage() - tempyT) > 0.5) {
    //   Serial.println("Disconnected, please connect again"); isConnected = false; 
    //   isPresent_MQ8 = false;
    //   while (!isConnected) {
    //     tempyT = MQ8.getVoltage();
      
    //     MQ8.update();
    //     MQ8.readSensor();
      
    //     delay(700);

    //     if (abs(MQ8.getVoltage() - tempyT) > 0.5) {
    //       int loopCnt = 0, successCnt = 0;

    //       Serial.print("Connecting");
    //       while (loopCnt < 3) {
    //         tempyT = MQ8.getVoltage();
      
    //         MQ8.update();
    //         MQ8.readSensor();
      
    //         delay(700);

    //         if (abs(MQ8.getVoltage() - tempyT) < 0.5) {
    //           Serial.print(".");
    //           successCnt++;
    //         }
    //         loopCnt++;
    //       }

    //       if (successCnt == 3) {
    //         Serial.println("Connected!"); isConnected = true; isPresent_MQ8 = true;
    //       }
    //       else {
    //         Serial.println("There was an error. Try again!!"); isConnected = false;
    //       }
    //     }
    //   }; 
    // }
  }
}

void detectCO2(void* pvParameters){

  //Set math model to calculate the PPM concentration and the value of constants
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setA(110.47); MQ135.setB(-2.862); // Configure the equation to to calculate CO2 concentration

  MQ135.init();   
  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ135.setRL(10);
  */

  MQ135.setRL(10);
  MQ135.readSensor();
  float tempPPM = 0;
  bool isConnected = true;

  Serial.print("Calibrating please wait.");
  
  MQ135.update();

  float temp = MQ135.getVoltage();

  
  float calcR0 = 0;
  for(int i = 1; i<=20; i ++)
  {
    temp = MQ135.getRS();

    MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
    
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);

    Serial.println(abs(MQ135.getRS() - temp));
    if (abs(MQ135.getRS() - temp) > 1) {
      isConnected = false;
    }
    delay(20);
  }

  MQ135.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0) {Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
  if(!isConnected) {Serial.println("Bad connection! Restart!"); while(1);}

  while (1) {
    isPresent_MQ135 = true;
    float tempyT = MQ135.getVoltage();

    MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    valueOf_MQ135 = MQ135.readSensor();

    delay(700); //Sampling frequency

    if (abs(MQ135.getVoltage() - tempyT) > 0.5) {
      Serial.println("Disconnected, please connect again"); isConnected = false; 
      isPresent_MQ135 = false;
      while (!isConnected) {
        tempyT = MQ135.getVoltage();
      
        MQ135.update();
        MQ135.readSensor();
      
        delay(700);

        if (abs(MQ135.getVoltage() - tempyT) > 0.5) {
          int loopCnt = 0, successCnt = 0;

          Serial.print("Connecting");
          while (loopCnt < 3) {
            tempyT = MQ135.getVoltage();
      
            MQ135.update();
            MQ135.readSensor();
      
            delay(700);

            if (abs(MQ135.getVoltage() - tempyT) < 0.5) {
              Serial.print(".");
              successCnt++;
            }
            loopCnt++;
          }

          if (successCnt == 3) {
            Serial.println("Connected!"); isConnected = true; isPresent_MQ135 = true;
          }
          else {
            Serial.println("There was an error. Try again!!"); isConnected = false;
          }
        }
      }; 
    }
  }
}

//TODO
void detectPH(void* pvParameters) {

  while(1) {
    // Read the sensor value
    phSensorValue = analogRead(phPin);
    // Convert the analog value to voltage
    float voltage = phSensorValue * voltageStep;
    // Calculate the pH value using linear interpolation
    phValue = 7.0 + ((voltage - neutralVoltage) / (neutralVoltage - alkalineVoltage) * (7.0 - 8.4));
    // Print the pH value to the Serial Monitor
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(" V, pH Value: ");
    Serial.println(phValue);
    // Delay before the next reading
    delay(1000);
  }
}

void detectColor(void* pvParameters) {
  
  //ADD INFINITE CHECK LOOP TODO

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  while (1) {
    
    tcs.getRGB(&r, &g, &b);
    // colorTemp = tcs.calculateColorTemperature(r, g, b);

    Serial.print("R: "); Serial.print(r + 20, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g - 20, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.println(" ");

  }

}

void detectTemperatureNew(void* pvParameters) {

  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);

  sensors.begin();

  while(1) {
    sensors.requestTemperatures();
    valueOf_Temperature = sensors.getTempCByIndex(0);
  
    Serial.print("Temperature: ");
    Serial.print(valueOf_Temperature);
    Serial.println(" °C");

    delay(1000);      
  }

}


void startThreads() {

  xTaskCreatePinnedToCore(
                    drawGraph,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
  delay(500);


  // xTaskCreatePinnedToCore(
  //                   detectH2,   /* Task function. */
  //                   "Task2",     /* name of task. */
  //                   10000,       /* Stack size of task */
  //                   NULL,        /* parameter of the task */
  //                   1,           /* priority of the task */
  //                   &Task2,      /* Task handle to keep track of created task */
  //                   1);          /* pin task to core 1 */                  
  // delay(500);

  // xTaskCreatePinnedToCore(
  //                   detectCO2,   /* Task function. */
  //                   "Task3",     /* name of task. */
  //                   10000,       /* Stack size of task */
  //                   NULL,        /* parameter of the task */
  //                   1,           /* priority of the task */
  //                   &Task3,      /* Task handle to keep track of created task */
  //                   1);          /* pin task to core 1 */                  
  // delay(500); 

  xTaskCreatePinnedToCore(
                    detectPH,   /* Task function. */
                    "Task4",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task4,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
  delay(500); 

  // xTaskCreatePinnedToCore(
  //                   detectColor,   /* Task function. */
  //                   "Task5",     /* name of task. */
  //                   10000,       /* Stack size of task */
  //                   NULL,        /* parameter of the task */
  //                   1,           /* priority of the task */
  //                   &Task5,      /* Task handle to keep track of created task */
  //                   1);          /* pin task to core 1 */                  
  // delay(500);

  xTaskCreatePinnedToCore(
                    detectTemperatureNew,   /* Task function. */
                    "Task6",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task6,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 1 */                  
  delay(500);

}