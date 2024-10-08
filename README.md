# Project: Connecting O-1PST Board to AFE: NO2, O3 Sensors using ADS1115 via I2C

## Project Objective

This project aims to connect the **O-1PST board** to an **AFE sensor** designed for detecting gases like **NO2** and **O3**. The project uses the **ADS1115** ADC (Analog-to-Digital Converter) to convert the analog signals from the sensors into digital data, which is then transmitted to the board via the **I2C protocol** for further processing and display.

Additionally, a **custom PCB** was designed to integrate the ADS1115 with the sensors. The PCB allows for a seamless connection between the sensors and the board, ensuring stable and efficient signal transmission. The PCB was also designed to fit within the **O-1PST** case, making the entire setup compact and robust for deployment.

## Components Used

- **O-1PST Board**: The main board for processing and control.
- **AFE (Analog Front-End) Sensor**: Sensors for detecting NO2 and O3 gases.
- **ADS1115**: A 16-bit ADC that converts analog signals to digital, communicating via I2C.
- **Custom PCB**: A printed circuit board designed for integrating ADS1115 with the sensors, compatible with the O-1PST case.

## Project Workflow

1. The **AFE sensor** measures the concentration of NO2 and O3 gases and outputs an analog signal.
2. The **ADS1115** converts the analog signal from the sensors into a digital format.
3. A **custom PCB** connects the ADS1115 to the sensors and the O-1PST board, ensuring proper signal routing.
4. The digital data is transmitted via the **I2C protocol** to the **O-1PST board**, where the data is processed and displayed.

## Reports

You can access the project reports from the links below:

- [ADS1115 Voltage Reading Report](./path_to_your_report/report_design.md)
- [PCB Design Report](./path_to_your_report/report_testing.md)
