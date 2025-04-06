#include "stdio.h"
#include "spi_connect.h"
#include "driver/spi_master.h"
#include "esp_log.h"


spi_device_handle_t spi;

void SPI_Master_Init()
{
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .mosi_io_num = to_stm32_mosi,
        .miso_io_num = to_stm32_miso,
        .sclk_io_num = to_stm32_sclk,
        .quadwp_io_num = to_stm32_quadwp,
        .quadhd_io_num = to_stm32_quadhd,
    };
    ESP_LOGI("SPI", "Starting SPI bus initialization");
    ret= spi_bus_initialize(spi_host_id, &buscfg, SPI_DMA_DISABLED);
    ESP_LOGI("SPI", "spi_bus_initialize() ret = %s", esp_err_to_name(ret));

    if (ret != ESP_OK) {
        ESP_LOGE("SPI", "Failed to initialize SPI bus: %s", esp_err_to_name(ret));
        return;
    }

    spi_device_interface_config_t dev_config = {
        .mode = 0, // SPI mode 0
        .clock_speed_hz = 1000000, // 1 MHz
        .spics_io_num = to_stm32_cs,
        .flags =0,
        .queue_size = 7,
    };

    ret = spi_bus_add_device(spi_host_id,&dev_config,&spi); 
    if(ret != ESP_OK){
        ESP_LOGI("SPI","SPI device addition faild");
        return;
    }
    ESP_LOGI("SPI","SPI master initialized");
}

void SPI_Master_Receive(uint8_t *tx_data, uint8_t *rx_data, size_t lenth)
{
    esp_err_t ret;
    spi_transaction_t trans = {
        .length=lenth*8,
        .tx_buffer=tx_data,
        .rx_buffer=rx_data,
    };
    ESP_LOGI("SPI", "Start SPI transmit: tx=0x%02X", *tx_data);

    ret = spi_device_transmit(spi,&trans);
    if (ret != ESP_OK) {
        ESP_LOGE("SPI", "SPI transmit/receive failed: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI("SPI", "SPI transmit done");
    }
}

void SPI_Master_OnlySend()
{
    uint8_t tx = 0xAA;
    spi_transaction_t trans = {
        .length = 8,
        .tx_buffer = &tx,
        .rx_buffer = NULL,
    };

    esp_err_t ret = spi_device_transmit(spi, &trans);
    if (ret == ESP_OK) {
        ESP_LOGI("SPI", "Sent 0x%02X", tx);
    } else {
        ESP_LOGE("SPI", "Send failed: %s", esp_err_to_name(ret));
    }
}