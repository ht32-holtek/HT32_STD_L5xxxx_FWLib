/*********************************************************************************************************//**
 * @file    CKCU/LSI_ManualTrim_By_HSI/main.c
 * @version $Rev:: 461          $
 * @date    $Date:: 2024-07-11 #$
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

/** @addtogroup CKCU_Examples CKCU
  * @{
  */

/** @addtogroup LSI_ManualTrim_By_HSI
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void LSIManualTrim_TestFun(void);

void LSIManualTrim_Configuration(void);
bool LSIManualTrim_MainRoutine(u32 ms, u32 *uResult);

void CKOUTConfig(void);
void UpdateStatus(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 guLSIReady = FALSE;
u32 guLSIReadyLast = FALSE;

u32 guTrimStartTime;
u32 guTrimEndTime;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  HT32_DVB_LEDInit(HT_LED1);

  #if 1
  CKOUTConfig();
  #endif

  LSIManualTrim_Configuration();

  while (1)
  {
    LSIManualTrim_TestFun();
  }
}

/*********************************************************************************************************//**
  * @brief  Manual Trim by HSI test function.
  * @retval None
  ***********************************************************************************************************/
void LSIManualTrim_TestFun(void)
{
  u32 uIsUpdate;

  uIsUpdate = LSIManualTrim_MainRoutine(10, &guLSIReady);  /* Call CKCU_LSIManualTrimIsReady() >= 2 ms      */

  if (uIsUpdate == TRUE)
  {
    UpdateStatus();
  }
}

/*********************************************************************************************************//**
  * @brief  Manual Trim by HSI configuration.
  * @retval None
  ***********************************************************************************************************/
void LSIManualTrim_Configuration(void)
{
  Time_Init();

  CKCU_LSIManualTrimInit();
  CKCU_LSIManualTrimCmd(ENABLE);

  #if 0 // Enable to shift the LSI frequency for verification
  HT_CKCU->LSITCR = 0x9b830000;
  HT_CKCU->LSITCR = 0x110;
  #endif
}

/*********************************************************************************************************//**
  * @brief  LSI Manual Trim main routine.
  * @param  ms: The check interval (in milliseconds, 0 is not allow).
  * @param  uResult: The pointer for save result
  * @retval TRUE or FALSE
  ***********************************************************************************************************/
bool LSIManualTrim_MainRoutine(u32 ms, u32 *uResult)
{
  static u32 guStartTime = 0;
  u32 uCurrentTime;
  bool uIsUpdated = FALSE;

  uCurrentTime = Time_GetTick();

  if (TIME_TICKDIFF(guStartTime, uCurrentTime) >= TIME_MS2TICK(ms))
  {
    *uResult = CKCU_LSIManualTrimIsReady(CKCU_LSITRIM_ACCURACY_0P5);
    guStartTime = uCurrentTime;

    uIsUpdated = TRUE;
  }

  return uIsUpdated;
}

/*********************************************************************************************************//**
  * @brief  Configure the LSI output clock through CKOUT.
  * @retval None
  ***********************************************************************************************************/
void CKOUTConfig(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Configure CKOUT                                                                                      */
    CKCU_CKOUTInitTypeDef CKOUTInit;
    CKOUTInit.CKOUTSRC = CKCU_CKOUTSRC_LSICK;
    CKCU_CKOUTConfig(&CKOUTInit);
  }

  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_9, AFIO_MODE_15);
}

/*********************************************************************************************************//**
  * @brief  Update LSI Trim status.
  * @retval None
  ***********************************************************************************************************/
void UpdateStatus(void)
{
  if (guLSIReadyLast != guLSIReady)
  {
    guLSIReadyLast = guLSIReady;

    if (guLSIReadyLast == TRUE)
    {
      guTrimEndTime = Time_GetTick();
      HT32_DVB_LEDOn(HT_LED1);
      printf("LSI Manual Trim Ready! Time = %d us\r\n", (u32)TIME_TICK2US(TIME_TICKDIFF(guTrimStartTime, guTrimEndTime)));
    }
    else
    {
      guTrimStartTime = Time_GetTick();
      HT32_DVB_LEDOff(HT_LED1);
      printf("LSI Manual Trim not Ready!\r\n");
    }
  }
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
