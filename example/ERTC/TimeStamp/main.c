/*********************************************************************************************************//**
 * @file    ERTC/TimeStamp/main.c
 * @version $Rev:: 1043         $
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

/** @addtogroup TimeStamp
  * @{
  */

/* Global Variables ----------------------------------------------------------------------------------------*/
vu32 SubSecond = 0;

/* Weekday name table (index: 1 = Monday to 7 = Sunday, 0 = invalid)                                        */
static const char *WeekDayName[] = {
  "???", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
};

/* Private functions ---------------------------------------------------------------------------------------*/
void ERTC_Configuration(void);
void ERTC_TimeStamp_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  ERTC_DateTypeDef ERTC_DateStructure = {0};
  ERTC_TimeTypeDef ERTC_TimeStructure = {0};

  /* Retarget Related configuration                                                                         */
  RETARGET_Configuration();
  HT32_DVB_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

  /* ERTC Configuration                                                                                     */
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  ERTC_Configuration();
  ERTC_TimeStamp_Configuration();
  ERTC_SetUnProtectKey(0);
  /* Read the current Date and Time                                                                         */
  ERTC_GetDateTime(&ERTC_DateStructure, &ERTC_TimeStructure);
  printf("[%s] 20%02d/%02d/%02d (%s) %02d:%02d:%02d%s\n",
         (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12) ? "12HR FMT" : "24HR FMT",
         ERTC_DateStructure.Year,
         ERTC_DateStructure.Month,
         ERTC_DateStructure.Day,
         WeekDayName[ERTC_DateStructure.WeekDay],
         ERTC_TimeStructure.Hours,
         ERTC_TimeStructure.Minutes,
         ERTC_TimeStructure.Seconds,
         (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12) ? ((ERTC_TimeStructure.AMPM == ERTC_AM) ? " AM" : " PM"): "");

  while (1)
  {
    printf("MCU goes to DS2 and wait for wakeup.....\n\r");

    /* Enter DeepSleep2 mode, waiting for interrupt event (WFE)                                             */
    while(HT32_DVB_PBGetState(BUTTON_WAKEUP) == SET);
    PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_WFE);
    PWRCU_GetFlagStatus();

    while(ERTC_GetFlagStatus(ERTC_FLAG_TSF) != SET);

    if(ERTC_GetTimestampEventSourceStatus(ERTC_TS_WAKEUP0_EVT) == SET && ERTC_GetFlagStatus(ERTC_FLAG_TSOVF) == RESET)
    {
      if(HT32_DVB_PBGetState(BUTTON_KEY1) == SET)
      {
        ERTC_ClearFlag(ERTC_FLAG_TSF);
      }
      printf("Timestamp triggered by WAKEUP0!\n\r");
    }

    if(ERTC_GetFlagStatus(ERTC_FLAG_TSOVF) == SET)
    {
      printf("--> Timestamp overflow!\n\r");
      ERTC_ClearFlag(ERTC_FLAG_TSOVF);
      ERTC_ClearFlag(ERTC_FLAG_TSF);
    }
    else
    {
      /* Read current Date and Time after wakeup                                                            */
      ERTC_GetTimeStamp(&ERTC_DateStructure, &ERTC_TimeStructure);
      printf("--> Timestamp [%s] %02d/%02d (%s) %02d:%02d:%02d%s\n",
             (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12) ? "12HR FMT" : "24HR FMT",
             ERTC_DateStructure.Month,
             ERTC_DateStructure.Day,
             WeekDayName[ERTC_DateStructure.WeekDay],
             ERTC_TimeStructure.Hours,
             ERTC_TimeStructure.Minutes,
             ERTC_TimeStructure.Seconds,
             (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12) ? ((ERTC_TimeStructure.AMPM == ERTC_AM) ? " AM" : " PM"): "");
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

  /* Enable BKP (Backup domain) clock                                                                       */
  {
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.BKP = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Enable LSE oscillator (32.768 kHz)                                                                     */
  ERTC_LSESMConfig(ERTC_LSESM_MEDIUM_SLOW);
  ERTC_LSECmd(ENABLE);

  /* Select LSE as ERTC clock source                                                                        */
  ERTC_ClockSourceConfig(ERTC_SRC_LSE);

  /* Configure ERTC time base to 1 second                                                                   */
  ERTC_StructInit(&ERTC_InitStructure);
  ERTC_InitStructure.AsynchPrediv = 0x7F;
  ERTC_InitStructure.SynchPrediv  = 0xFF;

  /* Initialize Date: 2024/11/05 (Tuesday)                                                                  */
  ERTC_InitStructure.Date.Year    = 24;
  ERTC_InitStructure.Date.Month   = 11;
  ERTC_InitStructure.Date.Day     = 5;
  ERTC_InitStructure.Date.WeekDay = ERTC_WEEKDAY_TUESDAY;

  /* Initialize Time: 12:00:00 AM (12 hour format)                                                          */
  ERTC_InitStructure.Time.FMT     = ERTC_HOURFORMAT_12;
  ERTC_InitStructure.Time.AMPM    = ERTC_AM;
  ERTC_InitStructure.Time.Hours   = 12;
  ERTC_InitStructure.Time.Minutes = 00;
  ERTC_InitStructure.Time.Seconds = 00;

  ERTC_Init(&ERTC_InitStructure);
}

/*********************************************************************************************************//**
  * @brief  Configure the ERTC TimeStamp.
  * @retval None
  ***********************************************************************************************************/
void ERTC_TimeStamp_Configuration(void){
  {
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.PB  = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }
  /* Configure WAKEUP pin used to wakeup Deep Sleep Mode 2                                                  */
  AFIO_GPxConfig(GPIO_PB, GPIO_PIN_12, AFIO_FUN_SYSTEM);
  PWRCU_WakeupMultiPinCmd(PWRCU_WAKEUP_PIN_0,PWRCU_WUP_POSITIVE_EDGE, ENABLE);
  PWRCU_WakeupPinTimeStampCmd(PWRCU_WAKEUP_PIN_0, ENABLE);
  ERTC_TimeStampCmd(ENABLE);
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
