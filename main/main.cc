#include <stdio.h>
#include "my_spi_connect/spi_connect.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#ifdef __cplusplus
extern "C" {
#endif

void app_main(void);  // 声明 app_main 函数

#ifdef __cplusplus
}
#endif


uint8_t txData = 0x55;  // 要发送的数据
uint8_t rxData = 0x00;  // 用来接收的数据

// 使用你已经定义好的 SPI_Master_Receive 函数
void SPI_Master_Receive_And_Respond()
{
   

    // 调用 SPI_Master_Receive 函数 
    SPI_Master_Receive(&txData, &rxData, 1);

    // 打印接收到的数据
    ESP_LOGI("SPI", "Received data: 0x%02X", rxData);

    // // 如果接收到的数据是 0x55，回复 0x66   
    // if (rxData == 0x88) {
    //     uint8_t responseData = 0x66;
    //     ESP_LOGI("SPI", "Sending response: 0x%02X", responseData);
        
    //     // 发送响应数据 0x66
    //     SPI_Master_Receive(&responseData, NULL, 1);
    // }
}



void app_main(void)
{   
    //uint8_t tx_data[]={0xAA,0xBB,0xCC};
    //uint8_t rx_data[3];
    SPI_Master_Init();
    //SPI_Master_Receive(tx_data,rx_data,sizeof(tx_data));
    printf("hello world! \n");
    printf("nothiing to see here \n");
    printf("这是一个spi的实现 \n");    
    while (1)
    {
        SPI_Master_Receive_And_Respond();
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 延时 1 秒
    }
    
}
