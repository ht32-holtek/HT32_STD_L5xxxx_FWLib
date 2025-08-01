/*********************************************************************************************************//**
 * @file    SPI/Master/main.c
 * @version $Rev:: 303          $
 * @date    $Date:: 2024-03-06 #$
 * @brief   Main program.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SPI_Examples SPI
  * @{
  */

/** @addtogroup Master
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void SPIINT_Configuration(void);
void SPI_Configuration(void);
void SPI_MainRoutine(void);
u32 SPI_Process(HT_SPI_TypeDef * SPIx, u8 *buffer, u32 length);

/* Global variables ----------------------------------------------------------------------------------------*/
vu32 guReceivedCount = 0;
u8 guReceiveBuffer[8];
vu32 gSPIINT = FALSE;
u32 gIndex = 0xA0;


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();           /* Retarget Related configuration                                     */

  SPIINT_Configuration();             /* SPI INT Related configuration                                      */

  SPI_Configuration();                /* SPI Related configuration                                          */

  while (1)
  {
    SPI_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the SPI INT ports.
  * @retval None
  ***********************************************************************************************************/
void SPIINT_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  EXTI_InitTypeDef EXTI_InitStruct;

  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO       = 1;
  CKCUClock.Bit.EXTI       = 1;
  HTCFG_INT_CLK(CKCUClock) = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  AFIO_GPxConfig(HTCFG_INT_GPIO_ID, HTCFG_INT_GPIO_PIN, AFIO_FUN_GPIO);
  GPIO_DirectionConfig(GPIO_PORT[HTCFG_INT_GPIO_ID], HTCFG_INT_GPIO_PIN, GPIO_DIR_IN);
  GPIO_PullResistorConfig(GPIO_PORT[HTCFG_INT_GPIO_ID], HTCFG_INT_GPIO_PIN, GPIO_PR_UP);
  GPIO_InputConfig(GPIO_PORT[HTCFG_INT_GPIO_ID], HTCFG_INT_GPIO_PIN, ENABLE);

  EXTI_InitStruct.EXTI_Channel = GPIO2EXTI(HTCFG_INT_GPION);
  EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
  EXTI_InitStruct.EXTI_DebounceCnt = 0;
  EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
  EXTI_Init(&EXTI_InitStruct);
  AFIO_EXTISourceConfig(HTCFG_INT_GPION, HTCFG_INT_GPIO_ID);

  EXTI_IntConfig(GPIO2EXTI(HTCFG_INT_GPION), ENABLE);
  NVIC_EnableIRQ(EXTI_GetIRQn(HTCFG_INT_GPION));
}

/*********************************************************************************************************//**
  * @brief  Configure the SPI ports.
  * @retval None
  ***********************************************************************************************************/
void SPI_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  SPI_InitTypeDef SPI_InitStructure;

  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO       = 1;
  CKCUClock.Bit.HTCFG_SPI_IPN = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  AFIO_GPxConfig(HTCFG_MASTER_SPI_SCK_GPIO_ID, HTCFG_MASTER_SPI_SCK_AFIO_PIN, AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_MASTER_SPI_SEL_GPIO_ID, HTCFG_MASTER_SPI_SEL_AFIO_PIN, AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_MASTER_SPI_MISO_GPIO_ID, HTCFG_MASTER_SPI_MISO_AFIO_PIN, AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_MASTER_SPI_MOSI_GPIO_ID, HTCFG_MASTER_SPI_MOSI_AFIO_PIN, AFIO_FUN_SPI);

  SPI_InitStructure.SPI_Mode = SPI_MASTER;
  SPI_InitStructure.SPI_FIFO = SPI_FIFO_ENABLE;
  SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
  SPI_InitStructure.SPI_SELMode = SPI_SEL_HARDWARE;
  SPI_InitStructure.SPI_SELPolarity = SPI_SELPOLARITY_LOW;
  SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_LOW;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_FIRST;
  SPI_InitStructure.SPI_RxFIFOTriggerLevel = 1;
  SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;
  SPI_InitStructure.SPI_ClockPrescaler = 4;
  SPI_Init(HTCFG_MASTER_SPI, &SPI_InitStructure);
  SPI_SELOutputCmd(HTCFG_MASTER_SPI, ENABLE);

  SPI_IntConfig(HTCFG_MASTER_SPI, SPI_INT_RXBNE, ENABLE);
  NVIC_EnableIRQ(HTCFG_MASTER_SPI_IRQ);

  SPI_Cmd(HTCFG_MASTER_SPI, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  SPI Main Routine.
  * @retval None
  ***********************************************************************************************************/
void SPI_MainRoutine(void)
{
  u8 SPIData[8];
  if (gSPIINT == TRUE)
  {
    gSPIINT = FALSE;

    SPIData[0] = gIndex++;
    SPIData[1] = gIndex++;
    SPIData[2] = gIndex++;
    SPIData[3] = gIndex++;
    SPIData[4] = gIndex++;
    SPIData[5] = gIndex++;
    SPIData[6] = gIndex++;
    SPIData[7] = gIndex++;

    if (SPI_Process(HTCFG_MASTER_SPI, SPIData, 8) != 8)
    {
      while (1); //Should not reached here. Means data overrun
    }
  }
  if (guReceivedCount == 8)
  {
    u32 i;
    printf("Received:");
    for (i = 0; i < 8; i++)
    {
      printf("%02x ", guReceiveBuffer[i]);
    }
    printf("\r\n");

    guReceivedCount = 0;
  }
}

/*********************************************************************************************************//**
  * @brief  Send SPI Data.
  * @param  SPIx: SPI port
  * @param  buffer: buffer for data.
  * @param  length: data length (must <= 8).
  * @retval length
  ***********************************************************************************************************/
u32 SPI_Process(HT_SPI_TypeDef * SPIx, u8 *buffer, u32 length)
{
  s32 i;
  if (length > 8)
  {
    return 0;
  }

  if (8 - SPI_GetFIFOStatus(SPIx, SPI_FIFO_TX) < length)
  {
    return 0;
  }

  for (i = length; i > 0; i--)
  {
    SPI_SendData(SPIx, *buffer++);
  }

  return length;
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
