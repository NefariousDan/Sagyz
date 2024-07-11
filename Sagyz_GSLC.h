//<File !Start!>
// FILE: [Dam2_GSLC.h]
// Created by GUIslice Builder version: [0.17.b27]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
#include "elem/XRingGauge.h"
#include "elem/XSlider.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG2,E_PG_POPUP1};
enum {E_ELEM_BOX2,E_ELEM_BTN2,E_ELEM_RADIO4,E_ELEM_RADIO5,E_ELEM_RADIO6
      ,E_ELEM_RINGGAUGE1,E_ELEM_SLIDER1,E_ELEM_TEXT1,E_ELEM_TEXT10
      ,E_ELEM_TEXT12,E_ELEM_TEXT2,E_ELEM_TEXT3,E_ELEM_TEXT5
      ,E_ELEM_TEXT6,E_ELEM_TEXT7,E_ELEM_TEXT8,E_ELEM_TEXT9};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                3

#define MAX_ELEM_PG_MAIN 17 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG2 0 // # Elems total on page
#define MAX_ELEM_PG2_RAM MAX_ELEM_PG2 // # Elems in RAM

#define MAX_ELEM_PG_POPUP1 0 // # Elems total on page
#define MAX_ELEM_PG_POPUP1_RAM MAX_ELEM_PG_POPUP1 // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG2_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG2];
gslc_tsElem                     m_asPopup1Elem[MAX_ELEM_PG_POPUP1_RAM];
gslc_tsElemRef                  m_asPopup1ElemRef[MAX_ELEM_PG_POPUP1];
gslc_tsXRingGauge               m_sXRingGauge1;
gslc_tsXSlider                  m_sXSlider1;
gslc_tsXCheckbox                m_asXRadio4;
gslc_tsXCheckbox                m_asXRadio5;
gslc_tsXCheckbox                m_asXRadio6;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemBox1;
extern gslc_tsElemRef* m_pElemRBRadioButton;
extern gslc_tsElemRef* m_pElemRBRadioButton5;
extern gslc_tsElemRef* m_pElemRBRadioButton6;
extern gslc_tsElemRef* m_pElemSlider1;
extern gslc_tsElemRef* m_pElemXRingGauge1;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------

char* startText = "Start";

void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG2,m_asPage2Elem,MAX_ELEM_PG2_RAM,m_asPage2ElemRef,MAX_ELEM_PG2);
  gslc_PageAdd(&m_gui,E_PG_POPUP1,m_asPopup1Elem,MAX_ELEM_PG_POPUP1_RAM,m_asPopup1ElemRef,MAX_ELEM_PG_POPUP1);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,((gslc_tsColor){240,240,240}));

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create E_ELEM_TEXT1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT1,E_PG_MAIN,(gslc_tsRect){380,161,36,16},
    (char*)"CO2",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
   
  // Create E_ELEM_BOX2 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX2,E_PG_MAIN,(gslc_tsRect){409,41,50,50});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,((gslc_tsColor){240,240,240}),((gslc_tsColor){240,240,240}));
  m_pElemBox1 = pElemRef;
  
  // Create E_ELEM_TEXT2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT2,E_PG_MAIN,(gslc_tsRect){380,122,24,16},
    (char*)"H2",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MAIN,(gslc_tsRect){405,17,60,16},
    (char*)"Color",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);

  // Create ring gauge E_ELEM_RINGGAUGE1 
  static char m_sRingText1[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE1,E_PG_MAIN,&m_sXRingGauge1,
          (gslc_tsRect){324,14,60,80},
          (char*)m_sRingText1,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE_LT4, GSLC_COL_RED_DK2);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  m_pElemXRingGauge1 = pElemRef;
  
  // Create E_ELEM_TEXT5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT5,E_PG_MAIN,(gslc_tsRect){190,20,96,16},
    (char*)"PH meter",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  
  // create E_ELEM_BTN2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN2,E_PG_MAIN,
    (gslc_tsRect){350,240,100,60},(char*)"Start",0,E_BUILTIN10X16,&CbBtnCommon);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,((gslc_tsColor){0,139,139}),GSLC_COL_CYAN);

  // Create slider E_ELEM_SLIDER1 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_ELEM_SLIDER1,E_PG_MAIN,&m_sXSlider1,
          (gslc_tsRect){161,39,140,20},0,14,7,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,false,GSLC_COL_BLACK,14,5,GSLC_COL_BLUE_LT4);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_TEAL,((gslc_tsColor){240,240,240}),GSLC_COL_BLACK);
  m_pElemSlider1 = pElemRef;
  
  // Create E_ELEM_TEXT6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT6,E_PG_MAIN,(gslc_tsRect){140,62,36,8},
    (char*)"Acidic",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT7,E_PG_MAIN,(gslc_tsRect){270,62,30,8},
    (char*)"Based",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT8,E_PG_MAIN,(gslc_tsRect){20,20,132,16},
    (char*)"Temperature",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT9,E_PG_MAIN,(gslc_tsRect){345,50,18,8},
    (char*)"25C",0,E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  
  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT10,E_PG_MAIN,(gslc_tsRect){380,202,48,16},
    (char*)"Temp",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
  
  // Create radio button E_ELEM_RADIO4
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO4,E_PG_MAIN,&m_asXRadio4,
    (gslc_tsRect){349,116,25,25},true,GSLCX_CHECKBOX_STYLE_ROUND,((gslc_tsColor){0,139,139}),false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,((gslc_tsColor){240,240,240}),GSLC_COL_BLACK);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton = pElemRef;
  
  // Create radio button E_ELEM_RADIO5
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO5,E_PG_MAIN,&m_asXRadio5,
    (gslc_tsRect){349,156,25,25},true,GSLCX_CHECKBOX_STYLE_ROUND,((gslc_tsColor){0,139,139}),false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,((gslc_tsColor){240,240,240}),GSLC_COL_BLACK);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton5 = pElemRef;
  
  // Create radio button E_ELEM_RADIO6
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_ELEM_RADIO6,E_PG_MAIN,&m_asXRadio6,
    (gslc_tsRect){349,196,25,25},true,GSLCX_CHECKBOX_STYLE_ROUND,((gslc_tsColor){0,139,139}),false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,((gslc_tsColor){240,240,240}),GSLC_COL_BLACK);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pElemRBRadioButton6 = pElemRef;
  
  // Create E_ELEM_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT12,E_PG_MAIN,(gslc_tsRect){60,50,48,16},
    (char*)"",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG2
  

  // -----------------------------------
  // PAGE: E_PG_POPUP1
  
//<InitGUI !End!>

//<Startup !Start!>
  gslc_GuiRotate(&m_gui, 3);
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
