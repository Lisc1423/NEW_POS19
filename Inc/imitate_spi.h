#ifndef __imitate_spi_H
#define __imitate_spi_H
#ifdef __cplusplus
 extern "C" {
#endif
/*iSPI1*/
#define iSPI1_CSN_Pin GPIO_PIN_15
#define iSPI1_CSN_GPIO_Port GPIOC
#define iSPI1_MOSI_Pin GPIO_PIN_7
#define iSPI1_MOSI_GPIO_Port GPIOA
#define iSPI1_MISO_Pin GPIO_PIN_6
#define iSPI1_MISO_GPIO_Port GPIOA
#define iSPI1_SCK_Pin GPIO_PIN_5
#define iSPI1_SCK_GPIO_Port GPIOA
#define iSPI1_CS_Enable() 	HAL_GPIO_WritePin(iSPI1_CSN_GPIO_Port, iSPI1_CSN_Pin, GPIO_PIN_RESET)
#define iSPI1_CS_Disable() 	HAL_GPIO_WritePin(iSPI1_CSN_GPIO_Port, iSPI1_CSN_Pin, GPIO_PIN_SET)
#define iSPI1_CLK_Enable() 	HAL_GPIO_WritePin(iSPI1_SCK_GPIO_Port, iSPI1_SCK_Pin, GPIO_PIN_SET                                                                                                                 )
#define iSPI1_CLK_Disable() 	HAL_GPIO_WritePin(iSPI1_SCK_GPIO_Port, iSPI1_SCK_Pin, GPIO_PIN_RESET)
/*iSPI3*/
#define iSPI3_CSN_Pin GPIO_PIN_14
#define iSPI3_CSN_GPIO_Port GPIOC
#define iSPI3_MOSI_Pin GPIO_PIN_12
#define iSPI3_MOSI_GPIO_Port GPIOC
#define iSPI3_MISO_Pin GPIO_PIN_11
#define iSPI3_MISO_GPIO_Port GPIOC
#define iSPI3_SCK_Pin GPIO_PIN_10
#define iSPI3_SCK_GPIO_Port GPIOC
#define iSPI3_CS_Enable() 	HAL_GPIO_WritePin(iSPI3_CSN_GPIO_Port, iSPI3_CSN_Pin, GPIO_PIN_RESET)
#define iSPI3_CS_Disable() 	HAL_GPIO_WritePin(iSPI3_CSN_GPIO_Port, iSPI3_CSN_Pin, GPIO_PIN_SET)
#define iSPI3_CLK_Enable() 	HAL_GPIO_WritePin(iSPI3_SCK_GPIO_Port, iSPI3_SCK_Pin, GPIO_PIN_SET                                                                                                                 )
#define iSPI3_CLK_Disable() 	HAL_GPIO_WritePin(iSPI3_SCK_GPIO_Port, iSPI3_SCK_Pin, GPIO_PIN_RESET)

void ispi1_write_read(uint8_t* writeBuffer, uint8_t* readBuffer, int len);  
void ispi3_write_read(uint8_t* writeBuffer, uint8_t* readBuffer, int len);
   
   
#ifdef __cplusplus
}
#endif
#endif