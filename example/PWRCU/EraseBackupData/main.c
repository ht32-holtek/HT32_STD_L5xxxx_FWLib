/*********************************************************************************************************//**
 * @file    PWRCU/EraseBackupData/main.c
 * @version $Rev:: 862          $
 * @date    $Date:: 2025-08-08 #$
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
#include "ht32_board_config.h"
/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup PWRCU_Examples PWRCU
  * @{
  */

/** @addtogroup EraseBackupData
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
u8  bDataNum = 10;
u32 BackupData[10] = {
  0x00A5, 0x1111, 0x2222, 0x3333, 0x4444,
  0x5555, 0x6666, 0x7777, 0x8888, 0x9999
};
bool EraseBackupFlag;

/* Private function prototypes -----------------------------------------------------------------------------*/
void WAKEUPPin_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  * @note At this stage the microcontroller clock setting is already configured,
  *       this is done through SystemInit() function which is called from startup
  *       file (startup_ht32lxxxx.s) before branching to application main.
  *       To reconfigure the default setting of SystemInit() function, refer to
  *       system_ht32lxxxx.c file
  * @details Main program as following:
  *   - Enable RTC PCLK.
  *   - Wait till the backup domain could be accessed.
  *   - Set RTC for generating an interrupt per second to toggle LED1
  *   - Init LED1 and USART.
  *   - Enable NVIC RTC interrupt.
  *   - Check the PWRCU flags and PWRCU_BAKREG_0 register.
  *     - Print Backup Domain Power On Reset information
  *       when the first time the program is executed.
  *     - If PWRCU_BAKREG_0 register value is not correct or not yet programmed
  *       (when the first time the program is executed).
  *       - Write BackupData to PWRCU_BAKREG_0~9.
  *   - Print and Check the data of PWRCU_BAKREG_0~9.
  *
  ***********************************************************************************************************/
int main(void)
{
   int i;

  /* Enable RTC clock                                                                                       */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.BKP        = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Wait for De-isolation, then backup domain could be accessed                                            */
  if (PWRCU_CheckReadyAccessed() != PWRCU_OK)
  {
    while (1);
  }
  /* Init LED1 and USART                                                                                    */
  HT32_DVB_LEDInit(HT_LED1);
  HT32_DVB_LEDInit(HT_LED2);

  RETARGET_Configuration();           /* Retarget Related configuration                                     */
  WAKEUPPin_Configuration();

  /* Check if the Power On Reset flag is set                                                                */
  if (PWRCU_GetFlagStatus() == PWRCU_FLAG_PWRPOR)
  {
    printf("\r\n\n Backup domain Power On Reset occurred....");
  }

  if (PWRCU_ReadBackupRegister(PWRCU_BAKREG_0) != BackupData[0])
  {
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */
    for (i = 0; i < bDataNum; i++)
    {
      PWRCU_WriteBackupRegister((PWRCU_BAKREG_Enum)i, BackupData[i]);
    }
    EraseBackupFlag = FALSE;
    printf(" BackupData has been configured....");

    /* Turn on LED1                                                                                         */
    HT32_DVB_LEDOn(HT_LED1);
  }

  for (i = 0; i < bDataNum; i++)
  {
    printf("\r\n PWRCU_BAKREG_%u = 0x%x   ", i, (unsigned int)PWRCU_ReadBackupRegister((PWRCU_BAKREG_Enum)i));
    if (PWRCU_ReadBackupRegister((PWRCU_BAKREG_Enum)i)!= BackupData[i])
    {
      printf("(Wrong! It should be 0   x%x)\r\n", (unsigned int)BackupData[i]);

       /* Turn on LED2                                                                                      */
      HT32_DVB_LEDOn(HT_LED2);
    }
  }
  printf("\r\n");
  while (1)
  {
    /* Check Wakeup button. If pressed, erase Backup Register                                               */
    if (GPIO_ReadInBit(HT_GPIOB, WAKEUP_BUTTON_GPIO_PIN) == SET && EraseBackupFlag == FALSE)
    {
      EraseBackupFlag =TRUE;
      printf(" BackupData has been erased!!");
      for (i = 0; i < bDataNum; i++)
      {
        printf("\r\n PWRCU_BAKREG_%u = 0x%x   ", i, (unsigned int)PWRCU_ReadBackupRegister((PWRCU_BAKREG_Enum)i));
      }
      printf("\r\n");
      /* Turn off LED1                                                                                         */
      HT32_DVB_LEDOn(HT_LED1);
    }
  }
}

/*********************************************************************************************************//**
  * @brief  EXTI Wakeup configuration.
  * @retval None
  ***********************************************************************************************************/
void WAKEUPPin_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};

  /* Enable EXTI & GPIO IP clock                                                                            */
  CKCUClock.Bit.PB         = 1;
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure GPIO pull down, AFIO mode, and Input Enable                                                  */
  AFIO_GPxConfig(WAKEUP_BUTTON_GPIO_ID, WAKEUP_BUTTON_GPIO_PIN, AFIO_FUN_SYSTEM);
  GPIO_PullResistorConfig(GPIO_PORT[WAKEUP_BUTTON_GPIO_ID], WAKEUP_BUTTON_GPIO_PIN, GPIO_PR_DOWN);
  GPIO_InputConfig(GPIO_PORT[WAKEUP_BUTTON_GPIO_ID], WAKEUP_BUTTON_GPIO_PIN, ENABLE);

  /* Set wakeup pin filter counter and prescaler                                                            */
  #if (LIBCFG_PWRCU_WAKEUPFILTER)
  PWRCU_SetWakeupPinFilter(HTCFG_WAKEUP_BUTTON_PIN, PWRCU_WUPFLT_COUNT2);
  PWRCU_SetWakeupPinFilterPrescaler(PWRCU_WUPFREQ_DIV1);
  #endif

  PWRCU_WakeupPinCmd(ENABLE);

  /* Enable wakeup pin trigger to erase backup register                                                     */
  PWRCU_WakeupPinEraseBakRegCmd(HTCFG_WAKEUP_BUTTON_PIN, ENABLE);
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
