/*********************************************************************************************************//**
 * @file    GPIO/Output/main.c
 * @version $Rev:: 749          $
 * @date    $Date:: 2025-07-25 #$
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup GPIO_Examples GPIO
  * @{
  */

/** @addtogroup Output
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void GPIO_Configuration(void);
void GPIO_OutputBit(void);
void GPIO_OutputData(void);

static void __Delay(u32 count);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  GPIO_Configuration();

  while (1)
  {

    GPIO_OutputBit();

    GPIO_OutputData();

  }
}

/*********************************************************************************************************//**
  * @brief  Configure the GPIO as output mode.
  * @retval None
  ***********************************************************************************************************/
void GPIO_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.PB = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Configure GPIO as output mode                                                                        */

    /* Configure AFIO mode as GPIO                                                                          */
    AFIO_GPxConfig(GPIO_PB, AFIO_PIN_1, AFIO_FUN_GPIO);

    /* Configure GPIO pull resistor                                                                         */
    GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_1, GPIO_PR_DOWN);

    /* Default value RESET/SET                                                                              */
    GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_1, RESET);

    /* Configure GPIO direction as output                                                                   */
    GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_1, GPIO_DIR_OUT);
  }
}

/*********************************************************************************************************//**
  * @brief  GPIO Output bit test
  * @retval None
  ***********************************************************************************************************/
void GPIO_OutputBit(void)
{
  GPIO_SetOutBits(HT_GPIOB, GPIO_PIN_1); // GPIO = HIGH
  __Delay(500000);

  GPIO_ClearOutBits(HT_GPIOB, GPIO_PIN_1); // GPIO = LOW
  __Delay(5000000);
}

/*********************************************************************************************************//**
  * @brief  GPIO Output data test
  * @retval None
  ***********************************************************************************************************/
void GPIO_OutputData(void)
{
  u16 uOutputData;

  uOutputData = GPIO_ReadOutData(HT_GPIOB);
  uOutputData |= GPIO_PIN_1; // GPIO = HIGH
  GPIO_WriteOutData(HT_GPIOB, uOutputData);
  __Delay(500000);

  uOutputData = GPIO_ReadOutData(HT_GPIOB);
  uOutputData &= ~(GPIO_PIN_1); // GPIO = LOW
  GPIO_WriteOutData(HT_GPIOB, uOutputData);
  __Delay(5000000);
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

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  delay function
  * @param  count: delay count for loop
  * @retval None
  ***********************************************************************************************************/
static void __Delay(u32 count)
{
  while (count--)
  {
    __NOP(); // Prevent delay loop be optimized
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
