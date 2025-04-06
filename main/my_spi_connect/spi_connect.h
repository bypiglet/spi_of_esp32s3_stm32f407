
#ifndef SPI_CONNECT_H
#define SPI_CONNECT_H

#include "driver/gpio.h"
#include "hal/spi_types.h"

#define spi_host_id         SPI2_HOST

#define to_stm32_miso       GPIO_NUM_12  //PB4
#define to_stm32_mosi       GPIO_NUM_13  //PB5
#define to_stm32_sclk       GPIO_NUM_14  //PB3
#define to_stm32_quadhd     GPIO_NUM_NC
#define to_stm32_quadwp     GPIO_NUM_NC

#define to_stm32_cs         GPIO_NUM_15

void SPI_Master_Init();
void SPI_Master_Receive(uint8_t *tx_data, uint8_t *rx_data, size_t lenth);

#endif
