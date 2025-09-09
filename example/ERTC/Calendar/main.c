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

/** @addtogroup Calendar
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
static const char *WeekDayName[] = {
  "???", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
};
/* Private functions ---------------------------------------------------------------------------------------*/
void ERTC_Configuration(void);
void AP_Time_Init(ERTC_InitTypeDef* ERTC_InitStructure);

#define YEAR_EPOCH   2024 // must be multiple of 4

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  vu32 SubSecond = 0;
  ERTC_DateTypeDef ERTC_DateStructure = {0};
  ERTC_TimeTypeDef ERTC_TimeStructure = {0};
  /* Retarget Related configuration                                                                         */
  RETARGET_Configuration();

  /* ERTC Configuration                                                                                     */
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  ERTC_Configuration();
  ERTC_SetUnProtectKey(0);

  /* Initialize Button                                                                                      */
  HT32_DVB_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);
  HT32_DVB_PBInit(BUTTON_KEY2,BUTTON_MODE_GPIO);
  printf("\r\n");
  printf("Press KEY1 to decrease 0.5 second\n");
  printf("Press KEY2 to increase 0.5 second\n");

  while (1)
  {
    if(HT32_DVB_PBGetState(BUTTON_KEY1) == RESET)// Decrease 0.5 second
    {
      ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
      ERTC_SynchroShiftConfig(ERTC_SHIFT_SIGN_ADD, (HT_ERTC->SPSC & 0x7FFF) / 2);
      ERTC_SetUnProtectKey(0);
      printf("\n");
    }
    else if(HT32_DVB_PBGetState(BUTTON_KEY2) == RESET)// Increase 0.5 second
    {
      ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
      ERTC_SynchroShiftConfig(ERTC_SHIFT_SIGN_SUB, (HT_ERTC->SPSC & 0x7FFF) / 2);
      ERTC_SetUnProtectKey(0);
      printf("\n");
    }
    while(!HT32_DVB_PBGetState(BUTTON_KEY1) || !HT32_DVB_PBGetState(BUTTON_KEY2));

    ERTC_GetDateTime(&ERTC_DateStructure, &ERTC_TimeStructure);
    SubSecond = ERTC_GetSubSecondms();

    printf("\r[%sHR FMT] %2d/%02d/%02d (%s) %02d:%02d:%02d.%d ",
           (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12) ? "12" : "24",
           ERTC_DateStructure.Year + YEAR_EPOCH,
           ERTC_DateStructure.Month,
           ERTC_DateStructure.Day,
           WeekDayName[ERTC_DateStructure.WeekDay],
           ERTC_TimeStructure.Hours,
           ERTC_TimeStructure.Minutes,
           ERTC_TimeStructure.Seconds,
           SubSecond);

    if (ERTC_TimeStructure.FMT == ERTC_HOURFORMAT_12)
        printf("%s  \r", (ERTC_TimeStructure.AMPM == ERTC_AM) ? "AM" : "PM");
    else
        printf("    \r");
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

  /* Configure only if ERTC is not already clocked                                                          */
  if ((HT_ERTC->CR0 & 0x6) == 0)
  {
    /* Enable the LSE OSC                                                                                   */
    ERTC_LSESMConfig(ERTC_LSESM_MEDIUM_SLOW);
    ERTC_LSECmd(ENABLE);

    /* Set the ERTC time base to 1s                                                                         */
    ERTC_InitStructure.AsynchPrediv = 0x7F;
    ERTC_InitStructure.SynchPrediv  = 0xFF;

    AP_Time_Init(&ERTC_InitStructure);

    /* Select LSE as the ERTC clock source                                                                  */
    ERTC_ClockSourceConfig(ERTC_SRC_LSE);
    ERTC_Init(&ERTC_InitStructure);
  }
}

/*********************************************************************************************************//**
  * @brief  Initialize time by values entered on the Hyperterminal.
  * @param  ERTC_InitStructure: pointer to ERTC_InitTypeDef structure that will store the configuration values.
  * @retval None
  ***********************************************************************************************************/
void AP_Time_Init(ERTC_InitTypeDef* ERTC_InitStructure){
  u32 val;
  printf("\r\n");
  printf("------------------------------\r\n");
  printf("Time Settings\r\n");
  /* Year setting range: YEAR_EPOCH ~ YEAR_EPOCH + 99                                                       */
  while (1)
  {
    printf("Year (%d~%d) : ", YEAR_EPOCH, YEAR_EPOCH + 99);
    scanf("%d", &val);
    val %= YEAR_EPOCH;
    if (val <= 99)
    {
        ERTC_InitStructure->Date.Year = val;
        printf("%d\r\n", YEAR_EPOCH + ERTC_InitStructure->Date.Year);
        break;
    }
    else
    {
        printf("Invalid\r\n");
    }
  }

  /* Month setting range: 1 ~ 12                                                                            */
  while (1)
  {
    printf("Month : ");
    scanf("%d", &val);
    if ((val > 0) && (val <= 12) )
    {
      ERTC_InitStructure->Date.Month = val;
      printf("%d\r\n", ERTC_InitStructure->Date.Month);
      break;
    }
    else
    {
      printf("Invalid\r\n");
    }
  }

  /* Day setting range: 1 ~ 31                                                                              */
  while (1)
  {
    printf("Day   : ");
    scanf("%d", &val);
    if (val >= 1 && val <= 31)
    {
      ERTC_InitStructure->Date.Day = val;
      printf("%d\r\n", ERTC_InitStructure->Date.Day);
      break;
    }
    else
    {
      printf("Invalid\r\n");
    }
  }

  /* WeekDay setting range: 1 ~ 7                                                                           */
  while (1)
  {
    printf("WeekDay (1=Mon ... 7=Sun) : ");
    scanf("%d", &val);
    if (val >= 1 && val <= 7)
    {
      ERTC_InitStructure->Date.WeekDay = val;
      printf("%s\r\n", WeekDayName[ERTC_InitStructure->Date.WeekDay]);
      break;
    }
    else
    {
      printf("Invalid\r\n");
    }
  }

  /* Hour format setting range: 0 or 1                                                                      */
  while (1)
  {
    printf("hour format: 0 = 12-hour, 1 = 24-hour : ");
    scanf("%d", &val);
    if (val == 0)
    {
      ERTC_InitStructure->Time.FMT = ERTC_HOURFORMAT_12;
      printf("ERTC_HOURFORMAT_12\r\n");
      break;
    }
    else if(val == 1)
    {
      ERTC_InitStructure->Time.FMT = ERTC_HOURFORMAT_24;
      printf("ERTC_HOURFORMAT_24\r\n");
      break;
    }
    else
    {
      printf("Invalid\r\n");
    }
  }

  if(ERTC_InitStructure->Time.FMT == ERTC_HOURFORMAT_24)
  {
    /* Hour setting range: 0 ~ 23                                                                           */
    while (1)
    {
      printf("Hour  : ");
      scanf("%d", &val);
      if (val <= 23)
      {
        ERTC_InitStructure->Time.Hours = val;
        printf("%d\r\n", ERTC_InitStructure->Time.Hours);
        break;
      }
      else
      {
        printf("Invalid\r\n");
      }
    }
  }
  else
  {
    /* Hour setting range: 1 ~ 12                                                                           */

    while (1)
    {
      printf("Hour  : ");
      scanf("%d", &val);
      if (val >=1 && val <= 12)
      {
        ERTC_InitStructure->Time.Hours = val;
        printf("%d\r\n", ERTC_InitStructure->Time.Hours);
        break;
      }
      else
      {
        printf("Invalid\r\n");
      }
    }
    while (1)
    {
      printf("AM/PM (0 = AM, 1 = PM) : ");
      scanf("%d", &val);
      if (val == 0)
      {
        ERTC_InitStructure->Time.AMPM = ERTC_AM;
        printf("ERTC_AM\r\n");
        break;
      }
      else if(val == 1)
      {
        ERTC_InitStructure->Time.AMPM = ERTC_PM;
        printf("ERTC_PM\r\n");
        break;
      }
      else
      {
        printf("Invalid\r\n");
      }
    }
  }

  /* Minute setting range: 0 ~ 59                                                                           */
  while (1)
  {
    printf("Minute: ");
    scanf("%d", &val);
    if (val <= 59)
    {
      ERTC_InitStructure->Time.Minutes = val;
      printf("%d\r\n", ERTC_InitStructure->Time.Minutes);
      break;
    }
    else
    {
      printf("Invalid\r\n");
    }
  }

  /* Second setting range: 0 ~ 59                                                                           */
  while (1)
  {
    printf("Second: ");
    scanf("%d", &val);
    if (val <= 59)
    {
      ERTC_InitStructure->Time.Seconds = val;
      printf("%d\r\n", ERTC_InitStructure->Time.Seconds);
      break;
    }
    else
    {
      printf("Invalid\r\n");
    }
  }
  printf("\r\n");
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
