#pragma once

#include <driver/i2s.h>

#define SAMPLE_RATE (CONFIG_DAC_SAMPLE_RATE_VALUE)
#define I2S_NUM (I2S_NUM_0)
#define I2S_DO_IO (CONFIG_DAC_DO_GPIO)
#define I2S_WS_IO (CONFIG_DAC_WS_GPIO)
#define I2S_BCK_IO (CONFIG_DAC_BCK_GPIO)
#define I2S_DI_IO (I2S_PIN_NO_CHANGE)

#define I2SWRITE_DELAY portMAX_DELAY

static const i2s_port_t i2s_num = I2S_NUM_0;

static const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S | I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL3,
    .dma_buf_count = 8,  // max buffers
    .dma_buf_len = 1024, // max value
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0 //
};

static const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCK_IO,
    .ws_io_num = I2S_WS_IO,
    .data_out_num = I2S_DO_IO,
    .data_in_num = I2S_DI_IO};

esp_err_t init_i2s();