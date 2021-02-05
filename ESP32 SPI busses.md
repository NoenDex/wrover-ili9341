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

## DAC CS4344

---

| Signal | GPIO   | Description                          |
| ------ | ------ | ------------------------------------ |
| MCLK   | GPIO0  | Master Clock (typically 256 x LRCLK) |
| SCBLK  | GPIO26 | Serial Bit Clock (Left/Right Clock)  |
| LRCLK  | GPIO25 | Word Select                          |
| SDIN   | GPIO2  | Data In                              |

example config:

```
i2s_config_t i2s_config = {
    .mode = I2S_MODE_MASTER | I2S_MODE_TX, // Only TX
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, //2-channels
    .communication_format = (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .dma_buf_count = 6,
    .dma_buf_len = 60,
    .intr_alloc_flags = 0, //Default interrupt priority
    .tx_desc_auto_clear = true, //Auto clear tx descriptor on underflow
    .use_apll = true // change to false if it sounds bad (rev0 chip - better set to false, newer chips - set to true)
};
i2s_driver_install(0, &i2s_config, 0, NULL);
i2s_pin_config_t pin_config = { .bck_io_num = CONFIG_I2S_BCK_PIN, .ws_io_num = CONFIG_I2S_LRCK_PIN, .data_out_num = CONFIG_I2S_DATA_PIN, .data_in_num = -1 // Not used };
i2s_set_pin(0, &pin_config);

// generate mclk on gpio0
REG_WRITE(PIN_CTRL, 0b111111110000);
PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0_CLK_OUT1);
```
