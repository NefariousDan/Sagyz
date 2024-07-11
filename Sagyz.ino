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

float startingDrawTime, stoppingDrawTime = 0;

bool drawH2 = false;
bool drawCO2 = false;
bool drawTemperature = false;
bool drawColors = false;
bool drawPH = false;

float phValue = 0;


#include "Sagyz_GSLC.h"
#include "properties.h"
#include "drawy.h"
#include "graphy.h"
#include "thready.h"
#include <SPI.h>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pElemBox1       = NULL;
gslc_tsElemRef* m_pElemRBRadioButton= NULL;
gslc_tsElemRef* m_pElemRBRadioButton5= NULL;
gslc_tsElemRef* m_pElemRBRadioButton6= NULL;
gslc_tsElemRef* m_pElemSlider1    = NULL;
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

  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_BTN2:
          if (drawingGraph == false) {
            startingDrawTime = millis();
            // xTaskCreatePinnedToCore(
            //       detectH2,   /* Task function. */
            //       "Task2",     /* name of task. */
            //       10000,       /* Stack size of task */
            //       NULL,        /* parameter of the task */
            //       1,           /* priority of the task */
            //       &Task2,      /* Task handle to keep track of created task */
            //       1);          /* pin task to core 1 */                  
            // delay(1500);
            
            drawingGraph = true;
            drawTemperature = true;
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
            vTaskDelete(Task2);
            plotTemp.clear();
            plotTime.clear();
            
          }; 
          
          delay(100);
          break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
// Checkbox / radio callbacks
// - Creating a callback function is optional, but doing so enables you to
//   detect changes in the state of the elements.
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  if (pElemRef == NULL) {
    return false;
  }

  // Determine which element issued the callback
  switch (pElem->nId) {
//<Checkbox Enums !Start!>

    case E_ELEM_RADIO4:
      break;
    case E_ELEM_RADIO5:
      break;
    case E_ELEM_RADIO6:
      break;
//<Checkbox Enums !End!>
    default:
      break;
  } // switch
  return true;
}
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case E_ELEM_SLIDER1:
      // Fetch the slider position

      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1);
      Serial.print(nVal);
      delay(150);
      break;

//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}



void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(9600);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  tft.begin();
  tft.setRotation(3);

  flashImage();

  delay(2000);

  // tft.fillScreen(0x53da);

  startThreads();

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();
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

  if (drawPH){
    gslc_ElemXSliderSetPos(&m_gui, m_pElemSlider1, phValue);
  }

  if (drawColors) {
    gslc_ElemSetCol(&m_gui,m_pElemBox1,GSLC_COL_BLACK,((gslc_tsColor){r + 80, g + 80, b + 80}),((gslc_tsColor){240,240,240}));
  }

  // END TODO


  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
    
}

