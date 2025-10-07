/*********************************************************************************************************//**
 * @file    ERTC/Alarm/main.c
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

/** @addtogroup Alarm
  * @{
  */

/* Global Variables-----------------------------------------------------------------------------------------*/
vu32 SubSecond = 0;

/* Weekday name table (index: 1 = Monday to 7 = Sunday, 0 = invalid)                                        */
static const char *WeekDayName[] = {
  "???", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
};

/* Private functions ---------------------------------------------------------------------------------------*/
void ERTC_Configuration(void);
void ERTC_Alarm_Configuration(void);

/* Define the Alarm trigger interval (select only one at a time)                                            */
#define ALARM_EVERY_SECOND
//#define ALARM_EVERY_MINUTE
//#define ALARM_EVERY_HOUR
//#define ALARM_EVERY_DAY
//#define ALARM_EVERY_WEDNESDAY

/* Time acceleration factor: x1 ~ x3600                                                                     */
#define TIME_SPEED_ACCEL    (1)

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
  printf("Press KEY1 Continue..\n");

  /* Wait until the user presses KEY1                                                                       */
  HT32_DVB_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
  while(HT32_DVB_PBGetState(BUTTON_KEY1) == SET);

  /* ERTC Configuration                                                                                     */
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  ERTC_Configuration();
  ERTC_Alarm_Configuration();
  ERTC_SetUnProtectKey(0);

  /* Read the current Date and Time                                                                         */
  ERTC_GetDateTime(&ERTC_DateStructure, &ERTC_TimeStructure);
  printf("[%s] 20%02d/%02d/%02d (%s) %02d:%02d:%02d",
         (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12) ? "12HR FMT" : "24HR FMT",
         ERTC_DateStructure.Year,
         ERTC_DateStructure.Month,
         ERTC_DateStructure.Day,
         WeekDayName[ERTC_DateStructure.WeekDay],
         ERTC_TimeStructure.Hours,
         ERTC_TimeStructure.Minutes,
         ERTC_TimeStructure.Seconds);

  if (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12)
  {
    printf(" %s\n", (ERTC_TimeStructure.AMPM == ERTC_AM) ? "AM" : "PM");
  }
  else
  {
    printf("\n");
  }

  while (1)
  {
    printf("\nMCU goes to DS2 and wait for wakeup.....\n");

    /* Enter DeepSleep2 mode, waiting for interrupt event (WFE)                                             */
    ERTC_ClearFlag(ERTC_FLAG_ALRF);// Clear Alarm flag before entering sleep 
    PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_WFE);

    /* Check if wakeup source was Alarm                                                                     */
    if(ERTC_GetFlagStatus(ERTC_WAKEUP_ALR) == SET)
    {
      ERTC_ClearFlag(ERTC_FLAG_ALRF);
      printf("WAKEUP!!  > ");

      /* Read current Date and Time after wakeup                                                            */
      ERTC_GetDateTime(&ERTC_DateStructure, &ERTC_TimeStructure);

      printf("[%s] 20%02d/%02d/%02d (%s) %02d:%02d:%02d",
             (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12) ? "12HR FMT" : "24HR FMT",
             ERTC_DateStructure.Year,
             ERTC_DateStructure.Month,
             ERTC_DateStructure.Day,
             WeekDayName[ERTC_DateStructure.WeekDay],
             ERTC_TimeStructure.Hours,
             ERTC_TimeStructure.Minutes,
             ERTC_TimeStructure.Seconds);

      if (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12)
      {
        printf(" %s\n", (ERTC_TimeStructure.AMPM == ERTC_AM) ? "AM" : "PM");
      }
      else
      {
        printf("\n");
      }
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
  ERTC_InitStructure.AsynchPrediv = 0x00;
  ERTC_InitStructure.SynchPrediv  = (0x8000 / TIME_SPEED_ACCEL) - 1;

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
  * @brief  Configure the ERTC ALARM (Every Second Mode).
  * @retval None
  ***********************************************************************************************************/
#ifdef ALARM_EVERY_SECOND
void ERTC_Alarm_Configuration(void){
  ERTC_AlarmTypeDef ERTC_AlarmStructure = {0};

  /* Set Alarm trigger time: 12:00:00 AM                                                                    */
  ERTC_AlarmStructure.AlarmTime.FMT     = ERTC_HOURFORMAT_12;
  ERTC_AlarmStructure.AlarmTime.AMPM    = ERTC_AM;
  ERTC_AlarmStructure.AlarmTime.Hours   = 12;
  ERTC_AlarmStructure.AlarmTime.Minutes = 00;
  ERTC_AlarmStructure.AlarmTime.Seconds = 00;

  /* Select Date for Alarm (ignored because masked)                                                         */
  ERTC_AlarmStructure.AlarmDateWeekDaySel = ERTC_ALARMSEL_DATE;
  ERTC_AlarmStructure.AlarmDateWeekDay    = 5;

  /* Alarm Mask: All fields masked ? trigger every second                                                   */
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Day    = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Hour   = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Minute = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Second = ENABLE;

  ERTC_SetAlarm(&ERTC_AlarmStructure);
  ERTC_AlarmCmd(ENABLE);
  ERTC_WakeupConfig(ERTC_WAKEUP_ALR, ENABLE);
}
#endif
#ifdef ALARM_EVERY_MINUTE
void ERTC_Alarm_Configuration(void){
  ERTC_AlarmTypeDef ERTC_AlarmStructure = {0};

  /* Set Alarm trigger time: 12:00:00 AM                                                                    */
  ERTC_AlarmStructure.AlarmTime.FMT     = ERTC_HOURFORMAT_12;
  ERTC_AlarmStructure.AlarmTime.AMPM    = ERTC_AM;
  ERTC_AlarmStructure.AlarmTime.Hours   = 12;
  ERTC_AlarmStructure.AlarmTime.Minutes = 00;
  ERTC_AlarmStructure.AlarmTime.Seconds = 00;

  /* Select Date for Alarm (ignored because masked)                                                         */
  ERTC_AlarmStructure.AlarmDateWeekDaySel = ERTC_ALARMSEL_DATE;
  ERTC_AlarmStructure.AlarmDateWeekDay    = 5;

  /* Alarm Mask: Day and Hour masked, Seconds not masked ? trigger every minute                             */
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Day    = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Hour   = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Minute = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Second = DISABLE;

  ERTC_SetAlarm(&ERTC_AlarmStructure);
  ERTC_AlarmCmd(ENABLE);
  ERTC_WakeupConfig(ERTC_WAKEUP_ALR, ENABLE);
}
#endif
#ifdef ALARM_EVERY_HOUR
void ERTC_Alarm_Configuration(void){
  ERTC_AlarmTypeDef ERTC_AlarmStructure = {0};

  /* Set Alarm trigger time: 12:00:00 AM                                                                    */
  ERTC_AlarmStructure.AlarmTime.FMT     = ERTC_HOURFORMAT_12;
  ERTC_AlarmStructure.AlarmTime.AMPM    = ERTC_AM;
  ERTC_AlarmStructure.AlarmTime.Hours   = 12;
  ERTC_AlarmStructure.AlarmTime.Minutes = 00;
  ERTC_AlarmStructure.AlarmTime.Seconds = 00;

  /* Select Date for Alarm (ignored because masked)                                                         */
  ERTC_AlarmStructure.AlarmDateWeekDaySel = ERTC_ALARMSEL_DATE;
  ERTC_AlarmStructure.AlarmDateWeekDay    = 5;

  /* Alarm Mask: Day masked, Minute and Second not masked ? trigger every hour                              */
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Day    = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Hour   = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Minute = DISABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Second = DISABLE;

  ERTC_SetAlarm(&ERTC_AlarmStructure);
  ERTC_AlarmCmd(ENABLE);
  ERTC_WakeupConfig(ERTC_WAKEUP_ALR, ENABLE);
}
#endif
#ifdef ALARM_EVERY_DAY
void ERTC_Alarm_Configuration(void){
  ERTC_AlarmTypeDef ERTC_AlarmStructure = {0};

  /* Set Alarm trigger time: 12:00:00 AM                                                                    */
  ERTC_AlarmStructure.AlarmTime.FMT     = ERTC_HOURFORMAT_12;
  ERTC_AlarmStructure.AlarmTime.AMPM    = ERTC_AM;
  ERTC_AlarmStructure.AlarmTime.Hours   = 12;
  ERTC_AlarmStructure.AlarmTime.Minutes = 00;
  ERTC_AlarmStructure.AlarmTime.Seconds = 00;

  /* Select Date for Alarm (ignored because masked)                                                         */
  ERTC_AlarmStructure.AlarmDateWeekDaySel = ERTC_ALARMSEL_DATE;
  ERTC_AlarmStructure.AlarmDateWeekDay    = 5;

  /* Alarm Mask: Only Day masked ? trigger every day at fixed time                                          */
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Day    = ENABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Hour   = DISABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Minute = DISABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Second = DISABLE;

  ERTC_SetAlarm(&ERTC_AlarmStructure);
  ERTC_AlarmCmd(ENABLE);
  ERTC_WakeupConfig(ERTC_WAKEUP_ALR, ENABLE);
}
#endif
#ifdef ALARM_EVERY_WEDNESDAY
void ERTC_Alarm_Configuration(void){
  ERTC_AlarmTypeDef ERTC_AlarmStructure = {0};

  /* Set Alarm trigger time: 12:00:00 AM                                                                    */
  ERTC_AlarmStructure.AlarmTime.FMT     = ERTC_HOURFORMAT_12;
  ERTC_AlarmStructure.AlarmTime.AMPM    = ERTC_AM;
  ERTC_AlarmStructure.AlarmTime.Hours   = 12;
  ERTC_AlarmStructure.AlarmTime.Minutes = 00;
  ERTC_AlarmStructure.AlarmTime.Seconds = 00;

  /* Select Weekday for Alarm (e.g. Wednesday)                                                              */
  ERTC_AlarmStructure.AlarmDateWeekDaySel = ERTC_ALARMSEL_WEEKDAY;
  ERTC_AlarmStructure.AlarmDateWeekDay    = ERTC_WEEKDAY_WEDNESDAY;

  /* Alarm Mask: No mask ? trigger once per week on specified weekday and time                              */
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Day    = DISABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Hour   = DISABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Minute = DISABLE;
  ERTC_AlarmStructure.AlarmMask.AlarmMask_Second = DISABLE;

  ERTC_SetAlarm(&ERTC_AlarmStructure);
  ERTC_AlarmCmd(ENABLE);
  ERTC_WakeupConfig(ERTC_WAKEUP_ALR, ENABLE);
}
#endif

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
