/*********************************************************************************************************//**
 * @file    ERTC/Calibration/main.c
 * @version $Rev:: 1044         $
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

/** @addtogroup Calibration
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
  CKCU_CKOUTInitTypeDef CKOUTInit;

  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure PA9 as CKOUT pin                                                                             */
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_9, AFIO_FUN_SYSTEM);
  /* Select LSE as CKOUT source, used for external measurement                                              */
  CKOUTInit.CKOUTSRC = CKCU_CKOUTSRC_LSECK;
  CKCU_CKOUTConfig(&CKOUTInit);

  /* ERTC Configuration                                                                                     */
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  ERTC_Configuration();
  ERTC_SetUnProtectKey(0);

  while (1)
  {
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

  /*
     ERTC Calibration Configuration
     -------------------------------------------------------------------------
     1. Output LSE clock (32768 Hz) to CKOUT pin (PA9).
     2. Measure the CKOUT frequency or total pulses during calibration window
        (8s / 16s / 32s) using oscilloscope or frequency counter.
     3. Calculate:
        Expected = 32768 ?window_seconds
        Error    = Measured - Expected
     4. Apply correction:
        - If Error > 0: LSE is faster, remove pulses.
        - If Error < 0: LSE is slower, add pulses.
     5. Configure:
        ERTC_CalibConfig(window, mode, |Error|)
        Example:
          Window = 32s
          Expected = 32768 ?32 = 1,048,576
          Measured = 1,048,800
          Error    = +224 ? Remove 224 pulses
          ERTC_CalibConfig(ERTC_CALIB_PERIOD_32, ERTC_CALIB_MASK_PULSES, 224);
  */
  ERTC_CalibConfig(ERTC_CALIB_PERIOD_32, ERTC_CALIB_MASK_PULSES, 224); // Example only

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
