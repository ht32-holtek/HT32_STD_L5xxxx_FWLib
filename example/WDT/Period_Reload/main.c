/*********************************************************************************************************//**
 * @file    WDT/Period_Reload/main.c
 * @version $Rev:: 248          $
 * @date    $Date:: 2024-02-27 #$
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

/** @addtogroup WDT_Examples WDT
  * @{
  */

/** @addtogroup Period_Reload
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void SysTick_Configuration(void);
void WDT_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  /* Initialize LEDs                                                                                        */
  HT32_DVB_LEDInit(HT_LED1);
  HT32_DVB_LEDInit(HT_LED2);

  SysTick_Configuration();

  WDT_Configuration();
  
  while (1)
  {
    /*A Watchdog timer underflow has occurred                                                               */
    if (WDT_GetFlagStatus(WDT_FLAG_UNDERFLOW))
    {
      SYSTICK_IntConfig(DISABLE);                    // Disable SysTick Interrupt
      HT32_DVB_LEDOn(HT_LED1);
      HT32_DVB_LEDOff(HT_LED2);
      while (1);
    }
    /*A Watchdog timer error has occurred                                                                  */
    else if (WDT_GetFlagStatus(WDT_FLAG_ERROR))
    {
      SYSTICK_IntConfig(DISABLE);                    // Disable SysTick Interrupt
      HT32_DVB_LEDOff(HT_LED1);
      HT32_DVB_LEDOn(HT_LED2);
      while (1);
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the Systick
  * @retval None
  ***********************************************************************************************************/
void SysTick_Configuration(void)
{
  SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);         // Default: CK_AHB/8 on chip
  SYSTICK_SetReloadValue(SystemCoreClock / 8 / 10);     // 1/10 Hz = 100ms
  SYSTICK_IntConfig(ENABLE);                            // Enable SysTick Interrupt
  /* Enable SYSTICK Counter                                                                                 */
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);          // Clear Initial Counter
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);         // Enable Systick Counter
}

/*********************************************************************************************************//**
  * @brief  Configure the Watchdog
  * @retval None
  ***********************************************************************************************************/
void WDT_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.WDT = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Enable WDT APB clock                                                                                   */
  /* Reset WDT                                                                                              */
  WDT_DeInit();
  /* Set Prescaler Value, 32K/64 = 500 Hz                                                                   */
  WDT_SetPrescaler(WDT_PRESCALER_64);
  /* Set Prescaler Value, 500 Hz/4000 = 0.125 Hz                                                            */
  WDT_SetReloadValue(4000);
  /* Set Delta Value, 500 Hz/4000 = 0.125 Hz                                                                */
  WDT_SetDeltaValue(4000);
  WDT_Restart();                    // Reload Counter as WDTV Value
  #if 0
  WDT_ResetCmd(ENABLE);             // Enable the WDT Reset when WDT meets underflow or error.
  #endif
  WDT_Cmd(ENABLE);                  // Enable WDT
  WDT_ProtectCmd(ENABLE);           // Enable WDT Protection
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
