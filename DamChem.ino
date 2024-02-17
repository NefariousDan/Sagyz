/*

  This program provides cartesian type graph function

  Revisions
  rev     date        author      description
  1       12-24-2015  kasprzak    initial creation

  Updated by Bodmer to be an example for the library here:
  https://github.com/Bodmer/TFT_eSPI

  Updated by Prashant to be used for Live Plot Sensor Data on TFT Display ILI9486 using ESP32
  https://blog.kamlatech.in/2023/11/live-plot-sensor-data-on-tft-display.html
  8/11/2023
  Additional Lib: https://www.arduino.cc/reference/en/libraries/circularbuffer/

*/

#include "properties.h"
#include "touchy.h"
#include "drawy.h"
#include "graphy.h"
#inlcude "pagy.h"

#include <SPI.h>


// Test data to creat a plot as no sensor is connected in this example
double initplotTemp[81] = {33.42, 33.42, 33.46, 33.55, 33.55, 33.57, 33.57, 33.73, 33.84, 33.96, 34.16, 34.4, 34.6, 34.88, 35.17, 35.45, 35.7, 35.89, 36.28, 36.59, 36.84, 37.2, 37.51, 37.74, 38.1, 38.35, 38.7, 39, 39.34, 39.57, 39.95, 40.23, 40.57, 40.91, 41.23, 41.5, 41.91, 42.21, 42.53, 42.96, 43.24, 43.59, 44.03, 44.28, 44.65, 45.03, 45.35, 45.65, 46.13, 46.48, 46.86, 47.23, 47.67, 48.01, 48.36, 48.76, 49.16, 49.55, 49.91, 50.31, 50.74, 51.07, 51.43, 51.83, 52.3, 52.63, 52.98, 53.34, 53.69, 53.98, 54.41, 54.77, 55.09, 55.5, 55.84, 56.11, 56.43, 56.73, 57.11, 57.45, 57.71};
double initplotTime[81] = {0.002, 0.063, 0.145, 0.227, 0.309, 0.392, 0.487, 0.569, 0.652, 0.734, 0.816, 0.899, 0.981, 1.063, 1.145, 1.228, 1.31, 1.392, 1.475, 1.557, 1.638, 1.721, 1.817, 1.899, 1.98, 2.063, 2.145, 2.227, 2.31, 2.392, 2.474, 2.557, 2.639, 2.721, 2.803, 2.886, 2.968, 3.05, 3.146, 3.228, 3.31, 3.393, 3.475, 3.556, 3.638, 3.721, 3.803, 3.885, 3.969, 4.05, 4.132, 4.215, 4.297, 4.379, 4.475, 4.557, 4.639, 4.721, 4.804, 4.886, 4.967, 5.05, 5.132, 5.214, 5.296, 5.379, 5.461, 5.543, 5.626, 5.708, 5.803, 5.886, 5.968, 6.05, 6.133, 6.215, 6.297, 6.379, 6.462, 6.543, 6.625};




void setup()
{

  tft.begin();
  // tft.fillScreen(0x53da);
  tft.setRotation(1);
  Serial.begin(115200);


  flashImage();


  // Graph(tft, xplot, yplot, 1, 20, 300, 300, 192, 0, 1, 1, 20, 60, 5, "", "Time(s)", "Temp(C)", display1, YELLOW, WHITE);

  // // Just a pause to have a look at graph layout
  // delay(2000);

  // In my case the Y axis is static so minY is not required. If you axis do not start at zero then you need minY declared, else it will start from 0
  // minY = 25.0; // for axis which do not need a 0 at start point - net needed for fix Y axis

  // In my case the X axis is dynamic but its starting value is not changing and is zero. if in you case its not zero then minX must be declared.
}

// Graph Plotting Function, This should be called as soon as you get a new sensor value, to update the graph.

void loop(void)
{

  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  bool pressed = tft.getTouch(&t_x, &t_y);

  // // / Check if any key coordinate boxes contain the touch coordinates
  // for (uint8_t b = 0; b < 15; b++) {
  //   if (pressed && key[b].contains(t_x, t_y)) {
  //     key[b].press(true);  // tell the button it is pressed
  //   } else {
  //     key[b].press(false);  // tell the button it is NOT pressed
  //   }
  // }

  // // Check if any key has changed state
  // for (uint8_t b = 0; b < 3; b++) {

  //   if (b < 3) tft.setFreeFont(LABEL1_FONT);
  //   else tft.setFreeFont(LABEL2_FONT);

  //   if (key[b].justReleased()) key[b].drawButton();     // draw normal

  //   if (key[b].justPressed()) {
  //     key[b].drawButton(true);  // draw invert

  //     switch (b) {
  //     case 0: firstPage();
  //     case 1: secondPage();
  //     case 2: thirdPage();
  //     default: ;

  //     }

  //     // Update the number display field
  //     tft.setTextDatum(TL_DATUM);        // Use top left corner as text coord datum
  //     tft.setFreeFont(&FreeSans18pt7b);  // Choose a nicefont that fits box
  //     tft.setTextColor(DISP_TCOLOR);     // Set the font colour

  //     // Draw the string, the value returned is the width in pixels
  //     int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);

  //     // Now cover up the rest of the line up by drawing a black rectangle.  No flicker this way
  //     // but it will not work with italic or oblique fonts due to character overlap.
  //     tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);

  //     delay(10); // UI debouncing
  //   }
  // }


  if (h < 81)
  {

    plotTemp.push(initplotTemp[h]);
    plotTime.push(initplotTime[h]);

    delay(40);    
    
    plotGraphP();
  }
  h++;
}