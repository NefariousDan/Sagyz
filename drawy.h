#include <PNGdec.h>
#include "SagyzLogo.h"

#define MAX_IMAGE_WIDTH 480 // Adjust for your images

PNG png; // PNG decoder inatance

int16_t xpos = 0;
int16_t ypos = 0;


void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}


void flashImage() {
    int16_t rc = png.openFLASH((uint8_t *)SagyzLogo, sizeof(SagyzLogo), pngDraw);
    
    if (rc == PNG_SUCCESS) {
        Serial.println("Successfully opened png file");
        Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
        tft.startWrite();
        uint32_t dt = millis();
        rc = png.decode(NULL, 0);
        Serial.print(millis() - dt); Serial.println("ms");
        tft.endWrite();
        // png.close(); // not needed for memory->memory decode
  }
}