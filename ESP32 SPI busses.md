# ESP32 SPI busses

---

## M5Stack Fire TFT

---

| Name   | Pin                  | Wrover TFT | Wrover CS |
| ------ | -------------------- | ---------- | --------- |
| MOSI   | 23                   | 23 (VSPI)  | 13 (HSPI) |
| MISO   | 19 (not used by TFT) | 19 (VSPI)  | 12 (HSPI) |
| SCK    | 18                   | 18 (VSPI)  | 14 (HSPI) |
| TFT_CS | 14                   | 05 (VSPI)  | -         |
| SD_CS  | 04                   | -          | 15 (HSPI) |
| DC     | 27                   | 27         | -         |
| LED    | 32                   | 32         | -         |
| RST    | 33                   | 33         | -         |

---

## M5Stack Fire MMC SD

---

| Name  | Pin       |
| ----- | --------- |
| SD_CS | 4         |
| SCK   | 18 (CLK)  |
| MISO  | 19 (SDDO) |
| MOSI  | 23 (SDDI) |

| Pin      | GPIO23 | GPIO19 | GPIO18 | GPIO14 | GPIO27 | GPIO33 | GPIO32 | GPIO4 |
| -------- | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ----- |
| ILI9342C | MOSI   | -      | CLK    | CS     | DC     | RST    | BL     | -     |
| TF Card  | MOSI   | MISO   | CLK    | -      | -      | -      | -      | CS    |

---

## ESP32 Hardware SPI busses

---

| SPI BUS | SCLK | MISO | MOSI | SS  |
| ------- | ---- | ---- | ---- | --- |
| VSPI    | 18   | 19   | 23   | 5   |
| HSPI    | 14   | 12   | 13   | 15  |

---

## TTGO T8 v1.7.1

---

| Name            | Pin  |
| --------------- | ---- |
| CLK (SCK)       | IO14 |
| MISO (DAT0/SD0) | IO2  |
| MOSI (CMD)      | IO15 |
| CS (SD3/DAT3)   | IO13 |
| SD2             | IO12 |
| DAT1 (SD1/\*NC) | IO4  |

## ESP IDF SD MMC driver

---

- Slot 0 (SDMMC*HOST_SLOT_0) is an 8-bit slot. It uses HS1*\* signals in the PIN MUX.
- Slot 1 (SDMMC*HOST_SLOT_1) is a 4-bit slot. It uses HS2*\* signals in the PIN MUX.

---

| Signal | Slot 0   | Slot 1   |
| ------ | -------- | -------- |
| CMD    | GPIO11   | GPIO15   |
| CLK    | GPIO6    | GPIO14   |
| D0     | GPIO7    | GPIO2    |
| D1     | GPIO8    | GPIO4    |
| D2     | GPIO9    | GPIO12   |
| D3     | GPIO10   | GPIO13   |
| D4     | GPIO16   |          |
| D5     | GPIO17   |          |
| D6     | GPIO5    |          |
| D7     | GPIO18   |          |
| CD     | any GPIO | any GPIO |
| WP     | any GPIO | any GPIO |
