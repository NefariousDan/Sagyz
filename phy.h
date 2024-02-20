int pHSense = 26;
int samples = 10;
float adc_resolution = 4096;
float voltage;

float ph (float voltage) {
    return 7 + ((2.5 - voltage) / 0.18);
}

void detectPH(void* pvParameters)
{

    while (1) {
      int measurings = 0;

      for (int i = 0; i < samples; i++)
      {
        measurings += analogRead(pHSense);
        delay(10);
      }

      voltage = 3.3 / adc_resolution * measurings/samples;
      Serial.print("pH= ");
      Serial.println(ph(voltage));
      Serial.println(analogRead(pHSense));
      delay(3000);
    }
}
