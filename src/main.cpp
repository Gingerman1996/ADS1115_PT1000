/***************************************************************************
 * Example sketch for the ADS1115_WE library
 *
 * This sketch shows how to use the ADS1115 in single shot mode.
 *
 * Further information can be found on:
 * https://wolles-elektronikkiste.de/ads1115 (German)
 * https://wolles-elektronikkiste.de/en/ads1115-a-d-converter-with-amplifier
 *(English)
 *
 ***************************************************************************/
#include "main.h"

TaskHandle_t signal_generate_task = NULL;
const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);
const TickType_t xDelay5000ms = pdMS_TO_TICKS(5000);
void singal_generate(void *parameter);

int16_t readChannel(ADS1115_MUX channel);

/* There are several ways to create your ADS1115_WE object:
 * ADS1115_WE adc = ADS1115_WE(); -> uses Wire / I2C Address = 0x48
 * ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS); -> uses Wire / I2C_ADDRESS
 * ADS1115_WE adc = ADS1115_WE(&Wire); -> you can pass any TwoWire object / I2C
 * Address = 0x48 ADS1115_WE adc = ADS1115_WE(&Wire, I2C_ADDRESS); -> all
 * together
 */
ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);
// Lookup table for resistance-to-temperature conversion
float temperatureTable[] = {
    -40.0, -20.0, 0.0,   20.0, 40.0,
    60.0,  80.0,  100.0, 120};  // Corresponding temperature values
float resistanceTable[] = {
    842.7,  921.6, 1000,   1077.9, 1155.4,
    1232.4, 1309,  1385.1, 1460.7};  // Add more values as needed
// Linear interpolation function
float interpolate(float x, float xTable[], float yTable[], int size) {
  for (int i = 1; i < size; i++) {
    if (x <= xTable[i]) {
      // Linear interpolation
      float x0 = xTable[i - 1];
      float x1 = xTable[i];
      float y0 = yTable[i - 1];
      float y1 = yTable[i];
      return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
    }
  }
  // Extrapolation if x is outside the range of the table
  return yTable[size - 1];
}
#ifndef UNIT_TEST
void setup() {
  Wire.begin(7, 6);
  Serial.begin(9600);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);

  if (!adc.init()) {
    Serial.println("ADS1115 not connected!");
  }
  /* Set the voltage range of the ADC to adjust the gain
   * Please note that you must not apply more than VDD + 0.3V to the input pins!
   *
   * ADS1115_RANGE_6144  ->  +/- 6144 mV
   * ADS1115_RANGE_4096  ->  +/- 4096 mV
   * ADS1115_RANGE_2048  ->  +/- 2048 mV (default)
   * ADS1115_RANGE_1024  ->  +/- 1024 mV
   * ADS1115_RANGE_0512  ->  +/- 512 mV
   * ADS1115_RANGE_0256  ->  +/- 256 mV
   */
  adc.setVoltageRange_mV(ADS1115_RANGE_4096);  // we have 3.3V VDD
  /* Set the inputs to be compared
   *
   *  ADS1115_COMP_0_1    ->  compares 0 with 1 (default)
   *  ADS1115_COMP_0_3    ->  compares 0 with 3
   *  ADS1115_COMP_1_3    ->  compares 1 with 3
   *  ADS1115_COMP_2_3    ->  compares 2 with 3
   *  ADS1115_COMP_0_GND  ->  compares 0 with GND
   *  ADS1115_COMP_1_GND  ->  compares 1 with GND
   *  ADS1115_COMP_2_GND  ->  compares 2 with GND
   *  ADS1115_COMP_3_GND  ->  compares 3 with GND
   */
  adc.setCompareChannels(
      ADS1115_COMP_0_GND);  // uncomment if you want to change the default
  /* Set number of conversions after which the alert pin will assert
   * - or you can disable the alert
   *
   *  ADS1115_ASSERT_AFTER_1  -> after 1 conversion
   *  ADS1115_ASSERT_AFTER_2  -> after 2 conversions
   *  ADS1115_ASSERT_AFTER_4  -> after 4 conversions
   *  ADS1115_DISABLE_ALERT   -> disable comparator / alert pin (default)
   */
  // adc.setAlertPinMode(ADS1115_ASSERT_AFTER_1); //uncomment if you want to
  // change the default
  /* Set the conversion rate in SPS (samples per second)
   * Options should be self-explaining:
   *
   *  ADS1115_8_SPS
   *  ADS1115_16_SPS
   *  ADS1115_32_SPS
   *  ADS1115_64_SPS
   *  ADS1115_128_SPS (default)
   *  ADS1115_250_SPS
   *  ADS1115_475_SPS
   *  ADS1115_860_SPS
   */
  // adc.setConvRate(ADS1115_128_SPS); //uncomment if you want to change the
  // default
  /* Set continuous or single shot mode:
   *
   *  ADS1115_CONTINUOUS  ->  continuous mode
   *  ADS1115_SINGLE     ->  single shot mode (default)
   */
  // adc.setMeasureMode(ADS1115_CONTINUOUS); //uncomment if you want to change
  // the default
  /* Choose maximum limit or maximum and minimum alert limit (window) in volts -
   * alert pin will assert when measured values are beyond the maximum limit or
   * outside the window Upper limit first: setAlertLimit_V(MODE, maximum,
   * minimum) In max limit mode the minimum value is the limit where the alert
   * pin assertion will be be cleared (if not latched)
   *
   *  ADS1115_MAX_LIMIT
   *  ADS1115_WINDOW
   *
   */
  // adc.setAlertModeAndLimit_V(ADS1115_MAX_LIMIT, 3.0, 1.5); //uncomment if you
  // want to change the default
  /* Enable or disable latch. If latch is enabled the alert pin will assert
   * until the conversion register is read (getResult functions). If disabled
   * the alert pin assertion will be cleared with next value within limits.
   *
   *  ADS1115_LATCH_DISABLED (default)
   *  ADS1115_LATCH_ENABLED
   */
  // adc.setAlertLatch(ADS1115_LATCH_ENABLED); //uncomment if you want to change
  // the default
  /* Sets the alert pin polarity if active:
   *
   * ADS1115_ACT_LOW  ->  active low (default)
   * ADS1115_ACT_HIGH ->  active high
   */
  // adc.setAlertPol(ADS1115_ACT_LOW); //uncomment if you want to change the
  // default
  /* With this function the alert pin will assert, when a conversion is ready.
   * In order to deactivate, use the setAlertLimit_V function
   */
  // adc.setAlertPinToConversionReady(); //uncomment if you want to change the
  // default
  Serial.println("ADS1115 Example Sketch - Single Shot Mode");
  Serial.println("Channel / Voltage [V]: ");
  Serial.println();

  // Create a multi-task for generate voltage for testing diff-amp ADS1115
  // xTaskCreatePinnedToCore(singal_generate, "singal_generatet", 2048, NULL, 1,
  //                         &signal_generate_task, 1);
}

void loop() {
  int16_t val_0 = readChannel(ADS1115_COMP_0_GND);
  Serial.print("CH 0 value: ");
  Serial.println(val_0);
  Serial.print("CH 0 value: ");
  // Convert analog value to resistance
  float resistance = ((float)VCC_VOLTAGE * (float)PT1000_R_REF) /
                     ((float)VCC_VOLTAGE - (float)val_0);
  Serial.print("CH 0 resistance: ");
  Serial.println(resistance);
  // Convert resistance to temperature using linear interpolation
  float temperature =
      interpolate(resistance, resistanceTable, temperatureTable,
                  sizeof(resistanceTable) / sizeof(resistanceTable[0]));
  // Print temperature to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  int16_t val_23 = readChannel(ADS1115_COMP_2_3);
  Serial.print("CH 2-3 value: ");
  Serial.println(val_23);
  delay(1000);
}
#endif

int16_t readChannel(ADS1115_MUX channel) {
  int16_t result = 0;
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();
  while (adc.isBusy()) {
  }
  return adc.getResult_mV();
}

// Function to map a value from the range 0-255 to 0-3300
float map_255_to_3300(uint8_t input_value) {
  // Check if the input_value exceeds the upper limit of 255
  if (input_value > 255) {
    input_value = 255;  // Cap the value to 255
  }

  // Perform the scaling calculation with rounding
  float output_value = (float)(input_value * 3300) / 255.0;

  return output_value;  // Return the mapped value in the range 0-3300
}

// Function to map a value from the range 0-3300 to 0-255
uint8_t map_3300_to_255(uint16_t input_value) {
  // Check if the input_value exceeds the upper limit of 3300
  if (input_value > 3300) {
    input_value = 3300;  // Cap the value to 3300
  }

  // Perform the scaling calculation with rounding
  float scaled_value = (float)(input_value * 255) / 3300.0;

  // Add 0.5 to ensure proper rounding
  uint8_t output_value = (uint8_t)(scaled_value + 0.5);

  return output_value;  // Return the mapped and rounded value in the range
                        // 0-255
}

void singal_generate(void *parameter) {
  // Define arrays for the values to be written to D0 and D1
  uint16_t D0_values[] = {100, 100, 300, 500, 1000, 0, 0};
  uint16_t D1_values[] = {100, 0, 0, 0, 0, 100, 300};

  // Infinite loop
  while (true) {
    // Loop through the predefined values
    for (int i = 0; i < 7; i++) {
      // Write the mapped values to D0 and D1
      uint8_t D0_bin = map_3300_to_255(D0_values[i]);
      uint8_t D1_bin = map_3300_to_255(D1_values[i]);

      analogWrite(D0, D0_bin);
      analogWrite(D1, D1_bin);

      float D0_V = map_255_to_3300(D0_bin);
      float D1_V = map_255_to_3300(D1_bin);

      // Delay for 1000 milliseconds (1 second)
      Serial.printf("Generate signal D0: %.2f\t D1: %.2f\tdiff: %.2f\n", D0_V,
                    D1_V, D0_V - D1_V);
      vTaskDelay(xDelay1000ms);
    }
  }
}
