# PCB Design Report

## Introduction to PCB Design

This report covers the design process of the PCB for ADS1115 for AlphaSensor-NO2-O3. The purpose of this PCB is to create a compact design that allows it to be stacked with the NO2-CO3 sensor, optimizing space while maintaining full functionality with the sensor system. The key component in this design is the ADS1115 analog-to-digital converter, which interfaces directly with the NO2-CO3 sensor and connects to the controller for data processing.

## Schematic Design

The schematic design outlines the logical arrangement of components. The ADS1115 was chosen for its high-resolution analog-to-digital conversion, which is essential for accurately reading the output from the NO2-CO3 sensor. The design also ensures seamless communication with the controller, which processes the sensor data.

Below is the list of components used (Bill of Materials):

| Id  | Designator | Footprint          | Quantity | Designation        | Supplier and Reference |
| --- | ---------- | ------------------ | -------- | ------------------ | ---------------------- |
| 1   | U1         | SOP50P490X110-10N  | 1        | ADS1115IDGSR       |                        |
| 2   | R5, R4     | RESC1608X55N       | 2        | 1K                 |                        |
| 3   | R3, R2, R1 | RESC1608X55N       | 3        | 10K                |                        |
| 4   | J2         | AWHW210G0202TR     | 1        | AWHW2-10G-0202-T-R |                        |
| 5   | J1         | 53261-0871         | 1        | 53261-0871         |                        |
| 6   | FB2, FB1   | BEADC2012X105N     | 2        | MMZ2012Y152BT000   |                        |
| 7   | C1         | CAPC1608X90N       | 1        | CL10B105KP8NNNC    |                        |

The following figure shows the schematic diagram of the circuit:

![Schematic Diagram](images/Screenshot%202024-10-08%20101412.png)

The schematic diagram illustrates the connection between the ADS1115 analog-to-digital converter (U1), the NO2-CO3 sensor, and the controller.

**ADS1115 (U1):** The ADS1115 is used to read the analog signals from the NO2-CO3 sensor and PT1000. It is configured with its input pins AIN2 and AIN3 connected to the sensor outputs SN2_P and SN2_N, respectively. Additionally, AIN0 is connected to the PT1000 temperature sensor. The inputs receive differential voltage from the sensor for accurate data measurement.

**Connector J1 (53261-0871):** This connector serves as the interface between the sensor board and the controller. Pins 5 and 6 are connected to the I2C bus (SCL and SDA), which facilitates data communication between the ADS1115 and the controller.

**I2C Bus:** The I2C bus is used to transmit data between the ADS1115 and the controller. Resistors R1 and R2 (both 10KΩ) are used as pull-up resistors for the I2C lines.

**Voltage Dividers (R4 and R5):** These resistors (1KΩ each) are used to condition the signal from the sensor before it reaches the ADS1115.

**Power Supply:** The board operates on 3.3V and 5V power supplies, with the appropriate decoupling capacitors (C1) and ferrite beads (FB1, FB2) to filter out noise.

**Connector J2 (AWHW2-10G-0202-T-R):** This is the connector used to interface with the sensor board, ensuring proper signal transmission from the NO2-CO3 sensor to the ADS1115.

This schematic provides a clear view of how the ADS1115 is configured to read the NO2-CO3 sensor's output and relay the data via the I2C bus to the controller.

## PCB Layout Design

The PCB layout for this project was carefully designed to ensure efficient signal routing, minimal noise interference, and effective power management. The ADS1115 is placed near the sensor connector to minimize the length of signal paths and reduce the potential for noise. Special consideration was given to the differential pair routing, which is crucial for maintaining the integrity of the signals from the NO2-CO3 sensor.

![PCB Layout](images/Screenshot%202024-10-08%20125016.png)

As seen in the layout, the power filtering components (C1, FB1, FB2) are placed close to the power supply inputs to filter out high-frequency noise. The I2C bus for communication between the ADS1115 and the controller is also routed with care to ensure reliable signal transmission.

Additionally, grounding and thermal management were key considerations in this design. Heat-generating components are spaced appropriately, and ground planes are used to reduce noise and provide stable operation for the sensitive analog signals processed by the ADS1115.

This PCB layout is optimized for signal integrity, thermal management, and ease of manufacturing, ensuring the system's reliability and performance in real-world applications.

## Manufacturing Considerations

The following parameters were chosen to ensure that the PCB is manufactured with high precision and quality, taking into account the electrical and mechanical requirements of the design:

**Base Material:** The PCB is fabricated using **FR-4** material, which is a widely used standard in PCB manufacturing for its durability and flame-retardant properties.

**Layers:** A **2-layer** design is used for this project to separate the power and signal routing effectively. This helps reduce interference and maintains signal integrity.

**Dimensions:** The PCB dimensions are **52mm x 28mm**, allowing for a compact yet functional design suitable for its application.

**PCB Thickness:** The board is specified with a thickness of **1.6mm**, which provides sufficient strength and stability while accommodating standard component heights.

**Surface Finish:** The surface finish chosen is **HASL (with lead)**, which ensures good solderability during component assembly and prevents oxidation of exposed copper.

**Copper Weight:** The outer copper weight is **1 oz**, providing adequate current-carrying capacity for the signal and power traces on the PCB.

**Via Covering:** **Tented vias** are used to protect the via holes from contamination and ensure better reliability in signal transmission across layers.

**Hole Size and Board Tolerance:** The minimum via hole size is **0.3mm** with a board outline tolerance of **±0.2mm**, ensuring precision during drilling and cutting.

**Electrical Test:** A **Flying Probe Fully Test** is selected to verify the electrical connections and functionality of the PCB before assembly, ensuring that there are no open or short circuits.

**PCB Assembly:** The assembly of components will be done on the **top side** of the PCB, using an **economic** PCBA type to reduce costs while maintaining quality. **Five** boards are being manufactured and assembled in total.

These manufacturing specifications are chosen to balance cost, durability, and performance, ensuring that the PCB is suitable for both prototyping and final production. The choice of materials, finishes, and testing procedures ensures that the board meets both electrical and mechanical requirements for the application.
