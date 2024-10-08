# ADS1115 Voltage Reading Report

## Introduction

This report covers the process of reading differential voltage values using ADS1115 and ESP32C3. The measured voltages include 0, 100, 300, 500, 1000, -100, and -300 mV. The purpose of this experiment is to verify if the ADS1115 can accurately measure the differential voltages applied to its inputs. For example, if a differential input voltage of 100 mV is applied, the report will evaluate the output value read by the ADS1115.

## Methodology

The methodology involves generating predefined voltage signals at pins D0 and D1 of the ESP32C3 microcontroller. These voltages are then connected to the A2 and A3 inputs of the ADS1115, which operates in differential mode to measure the voltage difference. The process includes mapping values between a 0-3300 mV range and a 0-255 binary range, enabling the ESP32C3 to output specific voltages.

In the code, predefined arrays for D0 and D1 voltages are set to values such as 100, 300, 500, 1000 mV, and 0 mV for both pins. The ESP32C3 then writes the corresponding binary values to D0 and D1 using the `analogWrite` function. The differential voltage between D0 and D1 is calculated and printed to the serial monitor. The process repeats for each pair of voltages with a delay of 5 seconds between each iteration.

## Code Implementation

The full code implementation can be found on the GitHub repository at the following link:

[GitHub Repository: ADS1115 Voltage Reading on ESP32C3](https://github.com/Gingerman1996/ADS1115_PT1000.git)

This signal generation function was added to the code originally developed by Xin. It is used to generate specific voltage signals on pins D0 and D1 of the ESP32C3, which helps in testing the differential voltage reading of the ADS1115.

```c++
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

    return output_value;  // Return the mapped and rounded value in the range 0-255
}

void signal_generate(void *parameter) {
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
            Serial.printf("Generate signal D0: %.2f\t D1: %.2f\tdiff: %.2f\n", D0_V, D1_V, D0_V - D1_V);
            vTaskDelay(xDelay5000ms);
        }
    }
}
```
This function generates specific signal voltages to simulate different scenarios, which helps to test the accuracy of the ADS1115 in reading differential voltages.

## Results

The results of the experiment show the generated voltage signals on D0 and D1 pins of the ESP32C3 board. These voltages are measured in millivolts (mV). The "diff" column represents the differential voltage between D0 and D1, while the "CH2-3" column shows the corresponding voltage values as measured by the ADS1115 in millivolts (mV).

![Voltage Measurement Results]([images/Screenshot 2024-10-03 150956.png](.images/Screenshot%202024-10-03%20150956.png))

D0 and D1 are the voltages generated by the board, measured in millivolts (mV). "diff" is the differential voltage, and "CH2-3" shows the values read by ADS1115 in millivolts (mV).

As seen in the image, the generated signal voltages range from 0 mV to around 1000 mV, with the differential values between D0 and D1 corresponding to the readings from ADS1115, which are shown in the "CH2-3" values. The experiment confirms that ADS1115 accurately measures differential voltages.

## Conclusion

Based on the experiment, the ADS1115 demonstrates accuracy in reading differential voltages when integrated with ESP32C3.
