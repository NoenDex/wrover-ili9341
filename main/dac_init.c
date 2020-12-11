#include "dac_init.h"

#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "INIT_I2S";

esp_err_t init_i2s()
{
    if (i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL) != ESP_OK)
    {
        ESP_LOGE(TAG, "ERROR: Unable to install I2S drives");
        return false;
    }

    if (i2s_set_pin(I2S_NUM, &pin_config) != ESP_OK)
    {
        ESP_LOGE(TAG, "ERROR: Unable to set I2S pins");
        return false;
    }

    if (i2s_set_clk(I2S_NUM, SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO) != ESP_OK)
    {
        ESP_LOGE(TAG, "ERROR: Unable to set I2S clock");
        return false;
    }

    if (i2s_zero_dma_buffer(I2S_NUM) != ESP_OK)
    {
        ESP_LOGE(TAG, "ERROR: Unable to zeroize I2S DMA buffer");
        return false;
    }

    if (i2s_start(I2S_NUM) != ESP_OK)
    {
        ESP_LOGE(TAG, "ERROR: Unable to start I2S");
        return false;
    }

    ESP_LOGI(TAG, "I2S bus initialized");
    return ESP_OK;
}