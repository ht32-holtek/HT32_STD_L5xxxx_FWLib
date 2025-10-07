/*********************************************************************************************************//**
 * @file    ERTC/ERTC_Out/main.c
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

/** @addtogroup ERTC_Out
  * @{
  */

/* Global Variables ----------------------------------------------------------------------------------------*/
char RTCOUT, OutputMode;

/* Private functions ---------------------------------------------------------------------------------------*/
void ERTC_Configuration(void);
void ERTC_Alarm_Configuration(void);
void ERTC_WakeupTimer_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  /* Retarget Related configuration                                                                         */
  RETARGET_Configuration();

  /* ERTC Configuration                                                                                     */
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  ERTC_Configuration();
  ERTC_Alarm_Configuration();
  ERTC_WakeupTimer_Configuration();
  ERTC_OutCmd(ENABLE); // ENABLE ERTC Out 
  ERTC_SetUnProtectKey(0);

  while (1)
  {
    printf("RTCOUT select:\n\r");
    printf("(1) Alarm (every 1s)\n\r");
    printf("(2) Wakeup Timer (every 2s)\n\r");
    printf("(3) CK_SPRE (1Hz clock)\n\r");
    printf("(4) CK_APRE (256Hz clock)\n\r");
    
    RTCOUT = getchar();
    OutputMode = 0;
    ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
    switch(RTCOUT)
    {
      case '1':
      {
        printf("Output Mode select:\n\r");
        printf("(1) Toggle Mode\n\r");
        printf("(2) Pulse Mode\n\r");
        printf("(3) Level Mode\n\r");
        OutputMode = getchar();
        switch(OutputMode)
        {
          case '1':
            ERTC_OutConfig(ERTC_ROWM_TOGGLE, ERTC_ROES_ALARM, ERTC_ROAP_HIGH);
            break;
          case '2':
            ERTC_OutConfig(ERTC_ROWM_PULSE, ERTC_ROES_ALARM, ERTC_ROAP_HIGH);
            break;
          case '3':
            ERTC_OutConfig(ERTC_ROWM_LEVEL, ERTC_ROES_ALARM, ERTC_ROAP_HIGH);
            break;
        }
      }
      break;
      case '2':
      {
        printf("Output Mode select:\n\r");
        printf("(1) Toggle Mode\n\r");
        printf("(2) Pulse Mode\n\r");
        printf("(3) Level Mode\n\r");
        OutputMode = getchar();
        switch(OutputMode)
        {
          case '1':
            ERTC_OutConfig(ERTC_ROWM_TOGGLE, ERTC_ROES_WAKEUP, ERTC_ROAP_HIGH);
            break;
          case '2':
            ERTC_OutConfig(ERTC_ROWM_PULSE, ERTC_ROES_WAKEUP, ERTC_ROAP_HIGH);
            break;
          case '3':
            ERTC_OutConfig(ERTC_ROWM_LEVEL, ERTC_ROES_WAKEUP, ERTC_ROAP_HIGH);
            break;
        }
      }
      break;
      case '3':
        ERTC_OutConfig(ERTC_ROWM_TOGGLE, ERTC_ROES_SPRE, ERTC_ROAP_HIGH);
        break;
      case '4':
        ERTC_OutConfig(ERTC_ROWM_TOGGLE, ERTC_ROES_APRE, ERTC_ROAP_HIGH);
        break;
    }
    ERTC_SetUnProtectKey(0);
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
  * @brief  Configure the ERTC ALARM (Every Second Mode).
  * @retval None
  ***********************************************************************************************************/
void ERTC_Alarm_Configuration(void){
  ERTC_AlarmTypeDef ERTC_AlarmStructure = {0};

  /* Set Alarm trigger time: 12:00:00 AM (ignored because masked)                                           */
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
}

/*********************************************************************************************************//**
  * @brief  Configure the ERTC WakeupTimer.
  * @retval None
  ***********************************************************************************************************/
void ERTC_WakeupTimer_Configuration(void)
{
  /* Wakeup timer configuration                                                                             */
  ERTC_WakeupTimerClockConfig(ERTC_WUP_TM_SPRE);

  /* Compare Match in 2 second                                                                              */
  ERTC_SetWakeupTimerCompare(2);

  ERTC_WakeupTimerCmd(ENABLE);
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
