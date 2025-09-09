/*********************************************************************************************************//**
 * @file    ERTC/Calendar/main.c
 * @version $Rev:: 1046         $
 * @date    $Date:: 2025-09-03 #$
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

/** @addtogroup ERTC_Examples ERTC
  * @{
  */

/** @addtogroup Wakeup_Timer
  * @{
  */

/* Private functions ---------------------------------------------------------------------------------------*/
void ERTC_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  ERTC_TimeTypeDef ERTC_TimeStructure = {0};
  /* Retarget Related configuration                                                                         */
  RETARGET_Configuration();
  /* Initialize Button                                                                                      */
  HT32_DVB_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

  /* ERTC Configuration                                                                                     */
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  ERTC_Configuration();
  ERTC_SetUnProtectKey(0);

  printf("\rPress KEY1 Continue..\n");
  while(HT32_DVB_PBGetState(BUTTON_KEY1) == SET);
  while (1)
  {
    printf("\rMCU goes to DS2 and wait for wakeup.....\n");
    ERTC_ClearFlag(ERTC_FLAG_WUTF);
    PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_WFE);
    if(ERTC_GetFlagStatus(ERTC_FLAG_WUTF) == SET)
    {
      ERTC_ClearFlag(ERTC_FLAG_WUTF);
      printf("\rWAKEUP!! -> ");
      /* Use BIN (decimal) format                                                                           */
      ERTC_GetTime(&ERTC_TimeStructure);

      printf("%02d:%02d:%02d \n",
             ERTC_TimeStructure.Hours,
             ERTC_TimeStructure.Minutes,
             ERTC_TimeStructure.Seconds);
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the ERTC peripheral.
  * @retval None
  ***********************************************************************************************************/
void ERTC_Configuration(void)
{
  ERTC_InitTypeDef ERTC_InitStructure = {0};
  {
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.BKP = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Enable the LSE OSC                                                                                     */
  ERTC_LSESMConfig(ERTC_LSESM_MEDIUM_SLOW);
  ERTC_LSECmd(ENABLE);

  /* Select LSE as the ERTC clock source                                                                    */
  ERTC_ClockSourceConfig(ERTC_SRC_LSE);

  /* Set the ERTC time base to 1s                                                                           */
  ERTC_StructInit(&ERTC_InitStructure);
  ERTC_InitStructure.AsynchPrediv = 0x7F;
  ERTC_InitStructure.SynchPrediv  = 0xFF;

  ERTC_Init(&ERTC_InitStructure);

  /* Wakeup timer configuration                                                                             */
  ERTC_WakeupTimerClockConfig(ERTC_WUP_TM_SPRE);

  /* Compare Match in 5 second                                                                              */
  ERTC_SetWakeupTimerCompare(5);

  ERTC_WakeupTimerCmd(ENABLE);
  ERTC_WakeupConfig(ERTC_WAKEUP_WUT, ENABLE);
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
