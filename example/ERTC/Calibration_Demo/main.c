/*********************************************************************************************************//**
 * @file    ERTC/Calibration_Demo/main.c
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

/** @addtogroup Calibration_Demo
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
  char sel;

  /* Retarget Related configuration                                                                         */
  RETARGET_Configuration();

  /* ERTC Configuration                                                                                     */
  ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
  ERTC_Configuration();
  ERTC_SetUnProtectKey(0);

  while (1)
  {
    printf("(0) Calibration Disable\n\r");
    printf("(1) Calibration 32s Windows Mask 255 CK_ERTC Clocks\n\r");
    printf("(2) Calibration 32s Windows Add 255 CK_ERTC Clocks\n\r");
    sel = getchar();
    switch(sel)
    {
      case '0':
        ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
        ERTC_CalibCmd(DISABLE);
        ERTC_SetUnProtectKey(0);
        break;
      case '1':
        ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
        ERTC_CalibConfig(ERTC_CALIB_PERIOD_32, ERTC_CALIB_MASK_PULSES, 255);
        ERTC_CalibCmd(ENABLE);
        ERTC_SetUnProtectKey(0);
        break;
      case '2':
        ERTC_SetUnProtectKey(ERTC_UNPROTECT_KEY);
        ERTC_CalibConfig(ERTC_CALIB_PERIOD_32, ERTC_CALIB_ADD_PULSES, 255);
        ERTC_CalibCmd(ENABLE);
        ERTC_SetUnProtectKey(0);
        break;
        
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
  ERTC_DeInit();
  ERTC_LSESMConfig(ERTC_LSESM_MEDIUM_SLOW);
  ERTC_LSECmd(ENABLE);
  ERTC_ClockSourceConfig(ERTC_SRC_LSE);

  /* Configure ERTC time base to 1 second                                                                   */
  ERTC_StructInit(&ERTC_InitStructure);
  ERTC_InitStructure.AsynchPrediv = 0x03;
  ERTC_InitStructure.SynchPrediv  = 0x1FFF;

  ERTC_Init(&ERTC_InitStructure);
  ERTC_OutConfig(ERTC_ROWM_TOGGLE, ERTC_ROES_APRE, ERTC_ROAP_HIGH);
  ERTC_OutCmd(ENABLE);
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
