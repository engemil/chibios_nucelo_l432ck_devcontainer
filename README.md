# ChibiOS NUCLEO-L432KC Example

Example project for ChibiOS utilizing the Nucleo-L432KC board (with STM32L432KC chip).

Links:
- NUCLEO-L432KC Board: https://www.st.com/en/evaluation-tools/nucleo-l432kc.html
- STM32L432KC Chip: https://www.st.com/en/microcontrollers-microprocessors/stm32l432kc.html
- STM32L4 series SVD files: https://www.st.com/en/microcontrollers-microprocessors/stm32-ultra-low-power-mcus.html#cad-resources

<img src="images/nucleo_l432kc_2017_10_09.png" alt="Alt text" width="600"/>



## Wire up VL53L1X module

| VL53L1X Module Pin | STM32F401RE Pin | NUCLEO64-F401RE Arduino Connector Pin | Function |
| --- | --- | --- | --- |
| VIN | - | 3V3 | 3.3V power source |
| GND | - | GND | Ground |
| SCL | PB6 | D5 | Serial Clock Line for I2C1 |
| SDA | PB7 | D4 | Serial Data (Line) for I2C1 |
| GPIO1 | PA8 | D9 | Configurable pin (Interrupt Pin?) |
| XSHUT | PA11 | D10 | Active-low Shutdown Pin. LOW (GND) Shutdown; HIGH (VIN) Active/enabled |

<img src="images/wiring.png" alt="Alt text" width="300"/>


