//<App !Start!>
// FILE: [Dam2.ino]
// Created by GUIslice Builder version: [0.17.b27]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------

double initplotTemp[40] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double initplotTime[40] = {0.002, 0.063, 0.145, 0.227, 0.309, 0.392, 0.487, 0.569, 0.652, 0.734, 0.816, 0.899, 0.981, 1.063, 1.145, 1.228, 1.31, 1.392, 1.475, 1.557, 1.638, 1.721, 1.817, 1.899, 1.98, 2.063, 2.145, 2.227, 2.31, 2.392, 2.474, 2.557, 2.639, 2.721, 2.803, 2.886, 2.968, 3.05, 3.146, 3.228};

float startingDrawTime, stoppingDrawTime = 0;
int keeperSecond = 1000;

#include "Dam2_GSLC.h"
#include "properties.h"
//#include "touchy.h"
#include "drawy.h"
#include "graphy.h"
#include "pagy.h"
#include "thready.h"
#include <SPI.h>
#include "MQ8y.h"
#include "phy.h"

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemToggle1    = NULL;
gslc_tsElemRef* m_pElemXRingGauge1= NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_BTN3:
        if (drawingGraph == false) {
          startingDrawTime = millis();
          drawingGraph = true;
          Serial.print("Pressed! Drawing; The value of graphCounter: ");
          Serial.print(graphCounter);
          Serial.println(drawingGraph);
        }
        else { 
          stoppingDrawTime = millis();
          drawingGraph = false;
          Serial.print("Pressed! NOT Drawing; The value of graphCounter: ");
          Serial.print(graphCounter);
          Serial.println(drawingGraph);
        }; delay(100);
      case E_ELEM_TOGGLE1:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle1)) {
          ;
        }
        delay(150); break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(9600);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  tft.begin();
  // tft.fillScreen(0x53da);
  tft.setRotation(1);

  xTaskCreatePinnedToCore(
                    loopy2,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    2,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
  delay(500); 


  xTaskCreatePinnedToCore(
                    detectH2,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
  delay(500);

  xTaskCreatePinnedToCore(
                    detectPH,   /* Task function. */
                    "Task3",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task3,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
  delay(500); 


  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

}

void loopy2 (void* pvParameters) {
  plotTime.push(0);
  while (1) {
    if (drawingGraph) {
      Serial.println(valueOf_MQ8);

      plotTemp.push(ph(voltage));
      plotTime.push((stoppingDrawTime + millis() - startingDrawTime) / 1000);

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


// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  
  //TODO - Add update code for any text, gauges, or sliders



  // END TODO


  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
    
}

