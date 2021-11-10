/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Memory buffer used directly by DMA for USART Rx*/
uint8_t bufferUSART2dma[DMA_USART2_BUFFER_SIZE];

/* Declaration and initialization of callback function */
static void (* USART2_ProcessData)(uint8_t data) = 0;

/* Register callback */
void USART2_RegisterCallback(void *callback)
{
	if(callback != 0)
	{
		USART2_ProcessData = callback;
	}
}

/* Space for global variables, if you need them */

	// type global variables here


/* USART2 init function */
void MX_USART2_UART_Init(void)
{
  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
  
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**USART2 GPIO Configuration  
  PA2   ------> USART2_TX
  PA15   ------> USART2_RX 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*
   * USART2 DMA configuration. Write configuration for DMA used by USART2 for data Rx/Tx with INTERRUPTS.
   * Rx memory buffer will be handled in normal mode, not circular!
   * You can use configuration from example program and modify it.
   * For more information about DMA registers, refer to reference manual.
   */
  
  /* USART2_RX Init */

  	  // type DMA USART Rx configuration here


  /* USART2_TX Init */

	  // type DMA USART Tx configuration here


  /* USART2 interrupt Init */
  NVIC_SetPriority(USART2_IRQn, 0);
  NVIC_EnableIRQ(USART2_IRQn);

  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_DisableIT_CTS(USART2);

  /* Enable USART2 peripheral and interrupts*/

  	  //type your code here:
}


// Send data stored in buffer with DMA
void USART2_PutBuffer(uint8_t *buffer, uint8_t length)
{
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_7, (uint32_t)buffer);

	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, length);

	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_7);

	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);
}


/*
 *	Function processing data received via USART2 with DMA and stored in bufferUSART2dma.
 *	Forwards data to callback function.
 *	Keeps track of pointer pointing to Rx memory buffer and resets the pointer if overflow is possible in next Rx.
 *	Refer to reference manual - "normal memory mode" and "increment memory mode".
 */
void USART2_CheckDmaReception(void)
{
	//type your implementation here
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
