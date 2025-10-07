/*********************************************************************************************************//**
 * @file    PWRCU/PowerDown_ERTC/main.c
 * @version $Rev:: 1087         $
 * @date    $Date:: 2025-09-09 #$
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

/** @addtogroup PWRCU_Examples PWRCU
  * @{
  */

/** @addtogroup PowerDown_ERTC
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void ERTC_Configuration(void);
void LowPower_BootCheck(void);
void LowPower_Enter(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  vu32 i;

  RETARGET_Configuration();

  LowPower_BootCheck();

  HT32_DVB_LEDInit(HT_LED1);
  HT32_DVB_LEDInit(HT_LED2);
  HT32_DVB_LEDInit(HT_LED3);
  HT32_DVB_LEDOn(HT_LED1);
  HT32_DVB_LEDOn(HT_LED2);
  HT32_DVB_LEDOn(HT_LED3);

  while (1)
  {
    for (i = 0; i < 40000000; i++){};

    HT32_DVB_LEDOff(HT_LED1);
    HT32_DVB_LEDOff(HT_LED2);
    HT32_DVB_LEDOff(HT_LED3);
    LowPower_Enter();

    // Never reacher here. Since the system will be restart when wakeup from the Power Down mode.

  }
}

/*********************************************************************************************************//**
  * @brief  Configures ERTC clock source and prescaler.
  * @retval None
  * @details The ERTC configuration as following:
  *   - Enable the LSE OSC and wait till LSE is ready.
  *   - Select the ERTC Clock Source as LSE.
  *   - Set the ERTC time base to 1 second.
  *   - Set Wakeup Timer Clock
  *   - Set Wakeup Timer Time.
  *   - Enable the Wakeup Timer.
  *   - Enable the ERTC Wakeup Timer Compare Match wakeup event.
  ***********************************************************************************************************/
void ERTC_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.BKP          = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  if (PWRCU_CheckReadyAccessed() != PWRCU_OK)
  {
    while (1);
  }

  #if 0
  /* Enable the LSE OSC                                                                                     */
  ERTC_LSESMConfig(ERTC_LSESM_MEDIUM_SLOW);
  ERTC_LSECmd(ENABLE);

  /* Wait till LSE is ready                                                                                 */
  while (CKCU_GetClockReadyStatus(CKCU_FLAG_LSERDY) == RESET);

  /* Select LSE as the ERTC clock source                                                                    */
  ERTC_ClockSourceConfig(ERTC_SRC_LSE);
  #else
  /* Select LSE as the ERTC clock source                                                                    */
  ERTC_ClockSourceConfig(ERTC_SRC_LSI);
  #endif

  /* Set the ERTC time base to 1s                                                                           */
  {
    ERTC_InitTypeDef ERTC_InitStructure = {0};
    ERTC_StructInit(&ERTC_InitStructure);
    ERTC_InitStructure.AsynchPrediv = 0x7F;
    ERTC_InitStructure.SynchPrediv  = 0xFF;
    ERTC_Init(&ERTC_InitStructure);
  }

  /* Wakeup timer configuration                                                                             */
  ERTC_WakeupTimerClockConfig(ERTC_WUP_TM_SPRE);

  /* Enable Wakeup timer Wakeup                                                                             */
  ERTC_WakeupConfig(ERTC_WAKEUP_WUT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Related checking when bootup.
  * @retval None
  ***********************************************************************************************************/
void LowPower_BootCheck(void)
{
  u32 uBAKSR;
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};

  CKCUClock.Bit.BKP        = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  uBAKSR = PWRCU_GetFlagStatus();

  if (uBAKSR & PWRCU_FLAG_PWRPOR)
  {
    /* Configure ERTC clock source and prescaler                                                              */
    ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
    ERTC_Configuration();
    ERTC_SetUnProtectKey(0);
  }

  if (uBAKSR & PWRCU_FLAG_PD)
  {
    if (ERTC_GetFlagStatus(ERTC_FLAG_WUTF) == SET)
    {
      ERTC_ClearFlag(ERTC_FLAG_WUTF);

      ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
      /* Disable the Wakeup timer                                                                             */
      ERTC_WakeupTimerCmd(DISABLE);
      ERTC_SetUnProtectKey(0);

      // Means wakeup by RTC, do your own process here
      printf("WAKEUP!\r\n");
    }
  }

  /*
  // Since the flags read by PWRCU_GetFlagStatus() are read clear, you must check all the flag here
  if (uBAKSR & PWRCU_FLAG_XXXX)
  {

  }
  */

}

/*********************************************************************************************************//**
  * @brief  Enter low power mode.
  * @retval None
  ***********************************************************************************************************/
void LowPower_Enter(void)
{
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  /* Compare Match in 3 second                                                                              */
  ERTC_SetWakeupTimerCompare(3);
  /* Enable the Wakeup timer                                                                                */
  ERTC_WakeupTimerCmd(ENABLE);
  ERTC_SetUnProtectKey(0);


  PWRCU_PowerDown();
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
