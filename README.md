# Dhrystone-Benchmark-Measurement-Calculation-ESP32

Dhrystone compares the performance of the processor under benchmark to that of a reference machine. Dhrystone has a number of attributes that have led to it being widely used in the past as a measure of CPU performance.
1. Widely available in the public domain
2. Simple to run. Significantly, there are no lengthy certification processes to go through before citing Dhrystone figures.

The Dhrystone figure is calculated by measuring the number of Dhrystones per second for the system, and dividing that by 1757. A DMIPS/MHz rating takes this normalization process one step further, enabling comparison of processor performance at different clock rates. In theory, Dhrystone should provide a basis for the comparison of processor performances.

The measurments conduct in this experiment is to cover the Dhrystone Benchmark measurement calculation for complexity of integer computation performed on ESP 32 WROVER DEVKIT (with LCD TFT).

ESP32 is a series of low-cost, low-power system on a chip microcontrollers with integrated Wi-Fi and dual-mode Bluetooth.

![ESP 32 WROVER DEVKIT](/Images/esp32_wrover_dev_kit.png)

ESP32 has multiprocessor setup:
1. Protocl Core (Core 0)
2. Application Core (Core 1)

Measurments conducted through the expreiment:
![Measurements](/Images/measurments.png)

Sample of the output:
![Application Core 1](/Images/screenshot1.jpg) ![Protocol Core 0](/Images/screenshot2.jpg)