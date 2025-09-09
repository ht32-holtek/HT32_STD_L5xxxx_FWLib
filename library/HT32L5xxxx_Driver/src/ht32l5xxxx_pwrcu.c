/*********************************************************************************************************//**
 * @file    ht32l5xxxx_pwrcu.c
 * @version $Rev:: 1074         $
 * @date    $Date:: 2025-09-08 #$
 * @brief   This file provides all the Power Control Unit firmware functions.
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
#include "ht32l5xxxx_pwrcu.h"

/** @addtogroup HT32L5xxxx_Peripheral_Driver HT32L5xxxx Peripheral Driver
  * @{
  */

/** @defgroup PWRCU PWRCU
  * @brief PWRCU driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Private_Define PWRCU private definitions
  * @{
  */
#if (LIBCFG_PWRCU_DEEPPOWERDOWN)
#define Set_DPWDN         SetBit_BB((u32)&HT_PWRCU->CR, 1)
#define Reset_DPWDN       ResetBit_BB((u32)&HT_PWRCU->CR, 1)
#endif

#define Set_VDDREN        SetBit_BB((u32)&HT_CKCU->APBCCR1, 6);
#define Reset_VDDREN      ResetBit_BB((u32)&HT_CKCU->APBCCR1, 6);
#define Get_VDDREN        GetBit_BB((u32)&HT_CKCU->APBCCR1, 6)

#define Set_LDOMODE       SetBit_BB((u32)&HT_PWRCU->CR, 2)
#define Reset_LDOMODE     ResetBit_BB((u32)&HT_PWRCU->CR, 2)

#define Set_LDOOFF        SetBit_BB((u32)&HT_PWRCU->CR, 3)
#define Reset_LDOOFF      ResetBit_BB((u32)&HT_PWRCU->CR, 3)

#define Set_WUP0EN        SetBit_BB((u32)&HT_PWRCU->CR, 8)
#define Reset_WUP0EN      ResetBit_BB((u32)&HT_PWRCU->CR, 8)

#if (LIBCFG_PWRCU_WAKEUP1)
#define Set_WUP1EN        SetBit_BB((u32)&HT_PWRCU->CR, 10)
#define Reset_WUP1EN      ResetBit_BB((u32)&HT_PWRCU->CR, 10)
#endif

#define Set_ULDOOFF       SetBit_BB((u32)&HT_PWRCU->CR, 20)
#define Reset_ULDOOFF     ResetBit_BB((u32)&HT_PWRCU->CR, 20)

#define Set_DS3SEL        SetBit_BB((u32)&HT_PWRCU->CR, 23)
#define Reset_DS3SEL      ResetBit_BB((u32)&HT_PWRCU->CR, 23)

#define Set_BODEN         SetBit_BB((u32)&HT_PWRCU->LVDCSR, 0)
#define Reset_BODEN       ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 0)

#define Set_BODRIS        SetBit_BB((u32)&HT_PWRCU->LVDCSR, 1)
#define Reset_BODRIS      ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 1)

#define Set_BODF          SetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)
#define Reset_BODF        ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)
#define Get_BODF          GetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)

#define Set_LVDEN         SetBit_BB((u32)&HT_PWRCU->LVDCSR, 16)
#define Reset_LVDEN       ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 16)

#define Set_LVDF          SetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)
#define Reset_LVDF        ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)
#define Get_LVDF          GetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)

#define Set_LVDIWEN       SetBit_BB((u32)&HT_PWRCU->LVDCSR, 20)
#define Reset_LVDIWEN     ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 20)

#define Set_LVDEWEN       SetBit_BB((u32)&HT_PWRCU->LVDCSR, 21)
#define Reset_LVDEWEN     ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 21)

#if (LIBCFG_PWRCU_WAKEUPBKUCLR)
#define Set_ERBKR         SetBit_BB((u32)&HT_PWRCU->CR1, 12)
#define Reset_ERBKR       ResetBit_BB((u32)&HT_PWRCU->CR1, 12)
#define Set_ERBKR1        SetBit_BB((u32)&HT_PWRCU->CR1, 13)
#define Reset_ERBKR1      ResetBit_BB((u32)&HT_PWRCU->CR1, 13)
#endif

#if (LIBCFG_PWRCU_WAKEUPTIMESTAMP)
#define Set_TMSTP         SetBit_BB((u32)&HT_PWRCU->CR1, 8)
#define Reset_TMSTP       ResetBit_BB((u32)&HT_PWRCU->CR1, 8)
#define Set_TMSTP1        SetBit_BB((u32)&HT_PWRCU->CR1, 9)
#define Reset_TMSTP1      ResetBit_BB((u32)&HT_PWRCU->CR1, 9)
#endif

#define SLEEPDEEP_SET     0x04      /*!< Cortex SLEEPDEEP bit                                               */

#define PWRRST_SET        0x1
#define PWRTEST_READY     0x27
#define TIME_OUT          24000000
#define WUP0TYPE_MASK     0xFFFCFFFF
#define WUP1TYPE_MASK     0xFFF3FFFF
#define LVDS_MASK         0xFFB9FFFF
#define VREG_V_MASK       0xF3FFFFFF
#define VREG_M_MASK       0xFCFFFFFF

#if (LIBCFG_PWRCU_WAKEUPFILTER)
#define WUP0FLT_Pos       4
#define WUP0FLT_MASK      0xFFFFFFCF
#define WUP1FLT_Pos       6
#define WUP1FLT_MASK      0xFFFFFF3F
#define WUPFREQ_MASK      0xFFFFFFFC
#endif
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Functions PWRCU exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize backup domain which contains PWRCU and RTC units.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeInit(void)
{
  HT_PWRCU->CR = PWRRST_SET;
  while(HT_PWRCU->CR & 0xFFFFEFFF); /* Skip Bit 12 because it isn't of valuable reference.                  */
  while (HT_PWRCU->SR);    /* Waits until the PWRPORF be cleared by read                                    */
}

#if (!LIBCFG_NO_PWRCU_TEST_REG)
/*********************************************************************************************************//**
 * @brief Waits, until the PWRCU can be accessed.
 * @retval PWRCU_TIMEOUT or PWRCU_OK
 ************************************************************************************************************/
PWRCU_Status PWRCU_CheckReadyAccessed(void)
{
  u32 wTimeOutCnt = TIME_OUT;

  while (--wTimeOutCnt)
  {
    if (HT_PWRCU->TEST == PWRTEST_READY)
    {
      return PWRCU_OK;
    }
  }
  return PWRCU_TIMEOUT;
}
#endif

/*********************************************************************************************************//**
 * @brief Return the flags of PWRCU.
 * @retval This function will return one of the following:
 *   - 0x0000                                   : There is no flag is set.
 *   - 0x0001 (PWRCU_FLAG_PWRPOR)               : VDD power domain power-on reset flag has been set.
 *   - 0x0002 (PWRCU_FLAG_PD)                   : Power-Down flag has been set.
 *   - 0x0004 (PWRCU_FLAG_LDONRDY)              : Main Regulator LDO not ready status flag.
 *   - 0x0010 (PWRCU_FLAG_POR)                  : Power-on reset flag has been set.
 *   - 0x0100 (PWRCU_FLAG_WUP0)                 : External WAKEUP0 pin flag has been set.
 *   - 0x0200 (PWRCU_FLAG_WUP1)                 : External WAKEUP1 pin flag has been set.
 *   - 0x1000 (PWRCU_FLAG_ERBKR0)               : WAKEUP0 pin Erase Backup Registers Flag has been set.
 *   - 0x2000 (PWRCU_FLAG_ERBKR1)               : WAKEUP1 pin Erase Backup Registers Flag has been set.
 ************************************************************************************************************/
u16 PWRCU_GetFlagStatus(void)
{
  #if defined(LIBCFG_PWRCU_STATUSREGWRITECLR)
  u16 uFlagStatus = HT_PWRCU->SR;
  HT_PWRCU->SR = uFlagStatus;
  return uFlagStatus;
  #else
  return HT_PWRCU->SR;
  #endif
}

#if (LIBCFG_BAKREG)
/*********************************************************************************************************//**
 * @brief Return the value of specified backup register.
 * @param BAKREGx: Number of backup register. Where x can be 0 ~ 9.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 PWRCU_ReadBackupRegister(PWRCU_BAKREG_Enum BAKREGx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BAKREG(BAKREGx));

  return HT_PWRCU->BAKREG[BAKREGx];
}

/*********************************************************************************************************//**
 * @brief Write the DATA to specified backup register.
 * @param BAKREGx : Number of backup registers. Where x can be 0 ~ 9.
 * @param DATA : Must between 0x0 ~ 0xFFFFFFFF.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WriteBackupRegister(PWRCU_BAKREG_Enum BAKREGx, u32 DATA)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BAKREG(BAKREGx));

  HT_PWRCU->BAKREG[BAKREGx] = DATA;
}
#endif

/*********************************************************************************************************//**
 * @brief Enter SLEEP mode.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_Sleep(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register                                                  */
  SCB->SCR &= ~(u32)SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }
}

/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 1.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_VDDREN;
  Set_VDDREN;

  Reset_LDOOFF;

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (uRTCStatus == 0)
  {
    Reset_VDDREN;
  }

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  SCB->SCR &= ~(u32)SLEEPDEEP_SET;
}

/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 2.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_VDDREN;
  Set_VDDREN;
  Reset_LDOOFF;

  if (uRTCStatus == 0)
  {
    Reset_VDDREN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  SCB->SCR &= ~(u32)SLEEPDEEP_SET;
}

#if (LIBCFG_PWRCU_DEEPSLEEP3)
/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 3.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_SLEEP_ENTRY_WFE : Enters SLEEP mode via WFE instruction
 *     @arg PWRCU_SLEEP_ENTRY_WFI : Enters SLEEP mode via WFI instruction
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep3(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_VDDREN;
  Set_VDDREN;

  Reset_LDOOFF;
  Set_DS3SEL;

  if (uRTCStatus == 0)
  {
    Reset_VDDREN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  SCB->SCR &= ~(u32)SLEEPDEEP_SET;

  Set_VDDREN;
  Reset_DS3SEL;
  if (uRTCStatus == 0)
  {
    Reset_VDDREN;
  }
}
#endif

#if (!LIBCFG_PWRCU_NO_PD_MODE)
/*********************************************************************************************************//**
 * @brief Enter POWER-DOWN Mode.
 * @retval None
 ************************************************************************************************************/
void PWRCU_PowerDown(void)
{
  u32 uRTCStatus = 0;

  uRTCStatus = Get_VDDREN;
  Set_VDDREN;

  Set_LDOOFF;

  if (uRTCStatus == 0)
  {
    Reset_VDDREN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  /* Enters power-down mode                                                                                 */
  __SEV();
  __WFE();
  __WFE();
}
#endif

#if (LIBCFG_PWRCU_DEEPPOWERDOWN)
/*********************************************************************************************************//**
 * @brief Enter DEEP-POWER-DOWN Mode.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepPowerDown(void)
{
  u32 uRTCStatus = 0;

  uRTCStatus = Get_VDDREN;
  Set_VDDREN;

  Set_DPWDN;
  Set_LDOOFF;

  if (uRTCStatus == 0)
  {
    Reset_VDDREN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  SCB->SCR |= SLEEPDEEP_SET;

  /* Enters power-down mode                                                                                 */
  __SEV();
  __WFE();
  __WFE();
}
#endif

/*********************************************************************************************************//**
 * @brief Configure LVD voltage level.
 * @param Level: Low voltage detect level.
 *   This parameter can be one of the following:
 *   VDD 1.65 ~ 3.6V version:
 *     @arg PWRCU_LVDS_1V75 : 1.75 V
 *     @arg PWRCU_LVDS_1V95 : 1.95 V
 *     @arg PWRCU_LVDS_2V15 : 2.15 V
 *     @arg PWRCU_LVDS_2V35 : 2.35 V
 *     @arg PWRCU_LVDS_2V55 : 2.55 V
 *     @arg PWRCU_LVDS_2V75 : 2.75 V
 *     @arg PWRCU_LVDS_2V95 : 2.95 V
 *     @arg PWRCU_LVDS_3V15 : 3.15 V
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetLVDS(PWRCU_LVDS_Enum Level)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LVDS(Level));

  HT_PWRCU->LVDCSR = (HT_PWRCU->LVDCSR & LVDS_MASK) | Level;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable LVD function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDEN;
  }
  else
  {
    Reset_LVDEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable BOD reset function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_BODEN;
  }
  else
  {
    Reset_BODEN;
  }
}

/*********************************************************************************************************//**
 * @brief Select when the BOD occurs, the action for the cause Reset or Interrupt.
 * @param Selection: BOD reset or interrupt selection.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_BODRIS_RESET : Reset the whole chip
 *     @arg PWRCU_BODRIS_INT   : Assert interrupt
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODRISConfig(PWRCU_BODRIS_Enum Selection)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BODRIS(Selection));

  if (Selection != PWRCU_BODRIS_RESET)
  {
    Set_BODRIS;
  }
  else
  {
    Reset_BODRIS;
  }
}

/*********************************************************************************************************//**
 * @brief Return the flag status of LVD.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetLVDFlagStatus(void)
{
  return (FlagStatus)Get_LVDF;
}

/*********************************************************************************************************//**
 * @brief Return the flag status of BOD.
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetBODFlagStatus(void)
{
  return (FlagStatus)Get_BODF;
}

/*********************************************************************************************************//**
 * @brief Configure the LDO operation mode.
 * @param Sel: Specify the LDO mode.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_LDO_NORMAL     : The LDO is operated in normal current mode
 *     @arg PWRCU_LDO_LOWCURRENT : The LDO is operated in low current mode
 * @retval None
 ************************************************************************************************************/
void PWRCU_LDOConfig(PWRCU_LDOMODE_Enum Sel)
{
  u32 uRTCStatus = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LDOMODE(Sel));

  uRTCStatus = Get_VDDREN;
  Set_VDDREN;

  if (Sel == PWRCU_LDO_NORMAL)
  {
    Reset_LDOMODE;
  }
  else
  {
    Set_LDOMODE;
  }

  if (uRTCStatus == 0)
  {
    Reset_VDDREN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the LVD interrupt wakeup function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDIntWakeupConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDIWEN;
  }
  else
  {
    Reset_LVDIWEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the LVD event wakeup function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDEventWakeupConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDEWEN;
  }
  else
  {
    Reset_LVDEWEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin function.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_WUP0EN;
  }
  else
  {
    Reset_WUP0EN;
  }
}

#if (LIBCFG_PWRCU_WAKEUP_V01)
/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin function.
 * @param Pin: specify the WAKEUP pin number.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WAKEUP_PIN_0 :
 *     @arg PWRCU_WAKEUP_PIN_1 :
 * @param Type: specify the WAKEUP pin type.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WUP_POSITIVE_EDGE :
 *     @arg PWRCU_WUP_NEGATIVE_EDGE :
 *     @arg PWRCU_WUP_HIGH_LEVEL    :
 *     @arg PWRCU_WUP_LOW_LEVEL     :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupMultiPinCmd(PWRCU_WUP_Enum Pin, PWRCU_WUPTYPE_Enum Type, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_WAKEUPPIN(Pin));
  Assert_Param(IS_PWRCU_TRIGGERTYPE(Type));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
    {
      HT_PWRCU->CR = (HT_PWRCU->CR & WUP0TYPE_MASK) | (Type << 16);
      Set_WUP0EN;
    }
    else
    {
      HT_PWRCU->CR = (HT_PWRCU->CR & WUP1TYPE_MASK) | (Type << 18);
      Set_WUP1EN;
    }
  }
  else
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
      Reset_WUP0EN;
    else
      Reset_WUP1EN;
  }
}
#endif

/*********************************************************************************************************//**
 * @brief Force the Ultra-low Power to turn off.
 * @retval None
 * @note !!! This bit ULDOOFF will be clear to 0 when the MCU is into the Power-Down or Deep Power-Down mode,
         VDD power domain reset.
 ************************************************************************************************************/
void PWRCU_ForceTurnOffULDO(void)
{
  Set_ULDOOFF;
}

#if (LIBCFG_PWRCU_WAKEUPBKUCLR)
/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin trigger the erase backup register function.
 * @param Pin: specify the WAKEUP pin number.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WAKEUP_PIN_0 :
 *     @arg PWRCU_WAKEUP_PIN_1 :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinEraseBakRegCmd(PWRCU_WUP_Enum Pin, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_WAKEUPPIN(Pin));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
      Set_ERBKR;
    else
      Set_ERBKR1;
  }
  else
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
      Reset_ERBKR;
    else
      Reset_ERBKR1;
  }
}
#endif

#if (LIBCFG_PWRCU_WAKEUPTIMESTAMP)
/*********************************************************************************************************//**
 * @brief Enable or Disable the external WAKEUP pin trigger the timestamp function.
 * @param Pin: specify the WAKEUP pin number.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WAKEUP_PIN_0 :
 *     @arg PWRCU_WAKEUP_PIN_1 :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinTimeStampCmd(PWRCU_WUP_Enum Pin, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_WAKEUPPIN(Pin));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
      Set_TMSTP;
    else
    {
      Set_TMSTP1;
    }
  }
  else
  {
    if (Pin == PWRCU_WAKEUP_PIN_0)
      Reset_TMSTP;
    else
      Reset_TMSTP1;
  }
}
#endif

#if (LIBCFG_PWRCU_WAKEUPFILTER)
/*********************************************************************************************************//**
 * @brief Set the external WAKEUP pin filter count.
 * @param Pin: specify the WAKEUP pin number.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WAKEUP_PIN_0   :
 *     @arg PWRCU_WAKEUP_PIN_1   :
 * @param Count: specify the WAKEUP pin signal filter count.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WUPFLT_COUNT2  :
 *     @arg PWRCU_WUPFLT_COUNT4  :
 *     @arg PWRCU_WUPFLT_COUNT8  :
 *     @arg PWRCU_WUPFLT_COUNT16 :
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetWakeupPinFilter(PWRCU_WUP_Enum Pin , PWRCU_WUPFLT_Enum Count)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_WAKEUPPIN(Pin));
  Assert_Param(IS_PWRCU_WUPFLT(Count));

  if (Pin == PWRCU_WAKEUP_PIN_0)
  {
    HT_PWRCU->CR = (HT_PWRCU->CR & WUP0FLT_MASK) | (Count << WUP0FLT_Pos);
  }
  else
  {
    HT_PWRCU->CR = (HT_PWRCU->CR & WUP1FLT_MASK) | (Count << WUP1FLT_Pos);
  }
}

/*********************************************************************************************************//**
 * @brief Set the external WAKEUP pin Sampling Frequency.
 * @param WAKEPRE: specify the WAKEUP pin sampling frequency prescaler.
 *   This parameter can be one of the following values:
 *     @arg PWRCU_WUPFREQ_DIV1 :
 *     @arg PWRCU_WUPFREQ_DIV2 :
 *     @arg PWRCU_WUPFREQ_DIV4 :
 *     @arg PWRCU_WUPFREQ_DIV8 :
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetWakeupPinFilterPrescaler(PWRCU_WUPFREQ_Enum WAKEPRE)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_WUPFREQ(WAKEPRE));

  HT_PWRCU->CR = (HT_PWRCU->CR & WUPFREQ_MASK) | WAKEPRE;
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
