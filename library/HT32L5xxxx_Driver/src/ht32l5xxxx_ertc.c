/*********************************************************************************************************//**
 * @file    ht32l5xxxx_ertc.c
 * @version $Rev:: 422          $
 * @date    $Date:: 2024-06-19 $#
 * @brief   This file provides all the ERTC firmware functions.
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
#include "ht32l5xxxx_ertc.h"

/** @addtogroup HT32L5xxxx_Peripheral_Driver HT32L5xxxx Peripheral Driver
  * @{
  */

/** @defgroup ERTC ERTC
  * @brief ERTC driver modules
  * @{
  */

/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup ERTC_Private_Define ERTC private definitions
  * @{
  */
#define ERTC_YEAR_MASK                             0x0000FF00
#define ERTC_YEAR_MASK_SHIFT                       8
#define ERTC_MONTH_MASK                            0x0000001F
#define ERTC_MONTH_MASK_SHIFT                      0
#define ERTC_DAY_MASK                              0x00003F00
#define ERTC_DAY_MASK_SHIFT                        8
#define ERTC_WEEKDAY_MASK                          0x000000E0
#define ERTC_WEEKDAY_MASK_SHIFT                    5

#define ERTC_HOUR_MASK                             0x0000003F
#define ERTC_HOUR_MASK_SHIFT                       0
#define ERTC_MINUTE_MASK                           0x00007F00
#define ERTC_MINUTE_MASK_SHIFT                     8
#define ERTC_SECOND_MASK                           0x0000007F
#define ERTC_SECOND_MASK_SHIFT                     0
#define ERTC_AMPM_MASK                             0x00000040
#define ERTC_AMPM_MASK_SHIFT                       0

#define ERTC_ALARM_ALMINAE_SHIFT                   15
#define ERTC_ALARM_ALSECE_SHIFT                    7
#define ERTC_ALARM_ALDAY_SHIFT                     15
#define ERTC_ALARM_ALHOURAE_SHIFT                  7

#define ERTC_ALARM_DATEWEEKDAY_MASK_SHIFT          8
#define ERTC_ALARM_HOUR_MASK_SHIFT                 0
#define ERTC_ALARM_MINUTE_MASK_SHIFT               8
#define ERTC_ALARM_SECOND_MASK_SHIFT               0
#define ERTC_ALARM_AMPM_MASK_SHIFT                 0

#define ERTC_ROEN_MASK                             0x00008000
#define ERTC_FMT_MASK                              0x00000040
#define ERTC_PSCRST_POS                            0x00008000
#define ERTC_ERTCSRC_MASK                          0x00000006
#define ERTC_HSEPRESEL_MASK                        0x0000000C
#define ERTC_LSESM_MASK                            0x00000030
#define ERTC_LSESM_SHIFT                           4
#define ERTC_WUTEN_MASK                            0x00000010
#define ERTC_WUCLSEL_MASK                          0x000000E0
#define ERTC_WUCLSEL_SHIFT                         5
#define ERTC_CALEN_MASK                            0x00008000
#define ERTC_TSESR_MASK                            0x0000C000

#define Set_INIT          SetBit_BB((u32)&HT_ERTC->CR0, 0)
#define Reset_INIT        ResetBit_BB((u32)&HT_ERTC->CR0, 0)
#define Set_LSEEN         SetBit_BB((u32)&HT_ERTC->CR0, 3)
#define Reset_LSEEN       ResetBit_BB((u32)&HT_ERTC->CR0, 3)

#define Set_WUTEN         SetBit_BB((u32)&HT_ERTC->CR1, 4)
#define Reset_WUTEN       ResetBit_BB((u32)&HT_ERTC->CR1, 4)

#define Set_ALREN         SetBit_BB((u32)&HT_ERTC->CR1, 0)
#define Reset_ALREN       ResetBit_BB((u32)&HT_ERTC->CR1, 0)

#define Set_CALEN         SetBit_BB((u32)&HT_ERTC->CALR, 15)
#define Reset_CALEN       ResetBit_BB((u32)&HT_ERTC->CALR, 15)

#define Set_TSEN          SetBit_BB((u32)&HT_ERTC->CR1, 1)
#define Reset_TSEN        ResetBit_BB((u32)&HT_ERTC->CR1, 1)

#define Set_ROCLR         SetBit_BB((u32)&HT_ERTC->CR0, 8)
#define Reset_ROCLR       ResetBit_BB((u32)&HT_ERTC->CR0, 8)

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
static u32 gERTCUnProtectKey       = 0;
static u32 gERTCSubSecondms        = 0;
static u32 gERTCSubSecondus        = 0;

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief  Converts 2-digit decimal value to BCD value.
 * @param  Value: Decimal byte to be converted.
 * @retval Converted BCD byte
 ************************************************************************************************************/
static u8 _ERTC_ByteToBcd(u8 Value)
{
  u8 bcdhigh = 0;
  while (Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }
  return ((u8)(bcdhigh << 4) | Value);
}

/*********************************************************************************************************//**
 * @brief  Converts BCD value to 2-digit decimal value.
 * @param  Value: BCD value to be converted.
 * @retval Converted decimal value
 ************************************************************************************************************/
static u8 _ERTC_BcdToByte(u8 Value)
{
  u8 tmp = 0;
  tmp = ((u8)(Value & (u8)0xF0) >> 4) * 10;
  return (tmp + (Value & (u8)0x0F));
}

/*********************************************************************************************************//**
 * @brief  Converts Hour Input Format 24 to 12
 * @param  ERTC_TimeStruct: pointer to a ERTC_TimeTypeDef structure that contains
 *         the time configuration information for the ERTC.
 * @retval Converted decimal value
 ************************************************************************************************************/
static void _ERTC_HourInputFormat_24_to_12(ERTC_TimeTypeDef* ERTC_TimeStruct)
{
  vu32 tmpreg;
  tmpreg = _ERTC_BcdToByte(ERTC_TimeStruct->Hours);
  if(ERTC_TimeStruct->FMT == ERTC_HOURFORMAT_12)
  {
    Assert_Param(IS_ERTC_HOUR12(tmpreg));
    Assert_Param(IS_ERTC_AMPM(ERTC_TimeStruct->AMPM));
  }
  else
  {
    Assert_Param(IS_ERTC_HOUR24(tmpreg));
    if (tmpreg <= 11)
    {
      ERTC_TimeStruct->AMPM = ERTC_AM;
      if (tmpreg == 0)
      {
        ERTC_TimeStruct->Hours = 0x12;
      }
    }
    else
    {
      ERTC_TimeStruct->AMPM = ERTC_PM;
      if (tmpreg != 12)
      {
        ERTC_TimeStruct->Hours = _ERTC_ByteToBcd(tmpreg - 12);
      }
    }
  }
}

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup ERTC_Exported_Functions ERTC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief  De-initialize the ERTC peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void ERTC_DeInit(void)
{
  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  /* Switch clock source to LSI                                                                             */
  HT_ERTC->CR0 = (HT_ERTC->CR0 & ~ERTC_ERTCSRC_MASK) | ERTC_SRC_LSI;
  while((HT_ERTC->CR0 & ERTC_ERTCSRC_MASK) != ERTC_SRC_LSI); // Wait until clock switches to LSI 

  ERTC_Cmd(DISABLE);

  /* Clear CR0 except INIT and LSI                                                                          */
  HT_ERTC->CR0 &= 0x3;

  /* Reset TR, DR, CR and other related registers                                                           */
  HT_ERTC->CAR0    = 0x00000000;
  HT_ERTC->CAR1    = 0x00000112;
  HT_ERTC->CAR2    = 0x000000C1;
  HT_ERTC->CR1     = 0x00000000;
  /* Clear WUTF, TSOVF, TSF, ALRF and CRSF flags                                                            */
  HT_ERTC->SR      = 0x00001302;
  HT_ERTC->APSC    = 0x0000007F;
  HT_ERTC->SPSC    = 0x000080FF;
  HT_ERTC->WUTR    = 0x00000000;
  HT_ERTC->CALR    = 0x00000000;
  HT_ERTC->ALMR0   = 0x00000000;
  HT_ERTC->ALMR1   = 0x00000000;
  HT_ERTC->ALMSSMR = 0x00000000;
  HT_ERTC->ALMSSR  = 0x00000000;

  ERTC_Cmd(ENABLE);

  HT_ERTC->CR0 = 0;
  while((HT_ERTC->CR0 & ERTC_ERTCSRC_MASK) != RESET);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Initialize the ERTC registers according to the specified parameters
 *         in ERTC_InitStruct.
 * @param  ERTC_InitStruct: Pointer to an ERTC_InitTypeDef structure that contains
 *         the configuration information for the ERTC peripheral.
 * @note   The ERTC prescaler registers are write-protected and can be written in
 *         initialization mode only.
 * @retval None
 ************************************************************************************************************/
void ERTC_InitBCD(ERTC_InitTypeDef* ERTC_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_ASYNCH_PREDIV(ERTC_InitStruct->AsynchPrediv));
  Assert_Param(IS_ERTC_SYNCH_PREDIV(ERTC_InitStruct->SynchPrediv));
  Assert_Param(IS_ERTC_HOUR_FORMAT(ERTC_InitStruct->Time.FMT));

  Assert_Param(IS_ERTC_YEAR(_ERTC_BcdToByte(ERTC_InitStruct->Date.Year)));
  Assert_Param(IS_ERTC_MONTH(_ERTC_BcdToByte(ERTC_InitStruct->Date.Month)));
  Assert_Param(IS_ERTC_DATE(_ERTC_BcdToByte(ERTC_InitStruct->Date.Day)));

  Assert_Param(IS_ERTC_MINUTES(ERTC_InitStruct->Time.Minutes));
  Assert_Param(IS_ERTC_SECONDS(ERTC_InitStruct->Time.Seconds));

  _ERTC_HourInputFormat_24_to_12(&ERTC_InitStruct->Time);

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  ERTC_Cmd(DISABLE);
  /* Configure the hour format                                                                              */
  HT_ERTC->CR0 = (HT_ERTC->CR0 & ~ERTC_FMT_MASK) | ERTC_InitStruct->Time.FMT;

  /* Configure the prescalers                                                                               */
  HT_ERTC->APSC = ERTC_InitStruct->AsynchPrediv;
  HT_ERTC->SPSC = ERTC_PSCRST_POS | ERTC_InitStruct->SynchPrediv;

  /* Set the ERTC Date & Time                                                                               */
  HT_ERTC->CAR0 = (ERTC_InitStruct->Time.Minutes << ERTC_MINUTE_MASK_SHIFT) |
                  (ERTC_InitStruct->Time.Seconds << ERTC_SECOND_MASK_SHIFT);

  HT_ERTC->CAR1 = (ERTC_InitStruct->Date.Day   << ERTC_DAY_MASK_SHIFT)  | \
                  (ERTC_InitStruct->Time.Hours << ERTC_HOUR_MASK_SHIFT) | \
                  (ERTC_InitStruct->Time.AMPM  << ERTC_AMPM_MASK_SHIFT);

  HT_ERTC->CAR2 = (ERTC_InitStruct->Date.Year    << ERTC_YEAR_MASK_SHIFT)  | \
                  (ERTC_InitStruct->Date.Month   << ERTC_MONTH_MASK_SHIFT) | \
                  (ERTC_InitStruct->Date.WeekDay << ERTC_WEEKDAY_MASK_SHIFT);
  ERTC_Cmd(ENABLE);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Initialize the ERTC registers according to the specified parameters(binary format)
 *         in ERTC_InitStruct.
 * @param  ERTC_InitStruct: Pointer to an ERTC_InitTypeDef structure that contains
 *         the configuration information for the ERTC peripheral.
 * @retval None
 ************************************************************************************************************/
void ERTC_Init(ERTC_InitTypeDef* ERTC_InitStruct)
{
  ERTC_InitTypeDef tmpStruct = *ERTC_InitStruct;

  /* Convert to BCD before calling BCD init */
  tmpStruct.Date.Year  = _ERTC_ByteToBcd(ERTC_InitStruct->Date.Year);
  tmpStruct.Date.Month = _ERTC_ByteToBcd(ERTC_InitStruct->Date.Month);
  tmpStruct.Date.Day   = _ERTC_ByteToBcd(ERTC_InitStruct->Date.Day);

  tmpStruct.Time.Hours   = _ERTC_ByteToBcd(ERTC_InitStruct->Time.Hours);
  tmpStruct.Time.Minutes = _ERTC_ByteToBcd(ERTC_InitStruct->Time.Minutes);
  tmpStruct.Time.Seconds = _ERTC_ByteToBcd(ERTC_InitStruct->Time.Seconds);

  ERTC_InitBCD(&tmpStruct);
}

/*********************************************************************************************************//**
 * @brief  Enable or Disable ERTC
 * @param  NewState: DISABLE to enter initialization mode, ENABLE to exit.
 * @retval None
 ************************************************************************************************************/
void ERTC_Cmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if ((HT_ERTC->SR & ERTC_FLAG_INITF) == NewState)
  {
    if (NewState)
    {
      Reset_INIT;
    }
    else
    {
      Set_INIT;
    }
    while ((HT_ERTC->SR & ERTC_FLAG_INITF) == NewState);
  }
}

/*********************************************************************************************************//**
 * @brief  Fill each ERTC_InitStruct member with its default value.
 * @param  ERTC_InitStruct: Pointer to an ERTC_InitTypeDef structure which will be initialized.
 * @retval None
 ************************************************************************************************************/
void ERTC_StructInit(ERTC_InitTypeDef* ERTC_InitStruct)
{
  /* Initialize the asynchronous/synchronous prescaler                                                      */
  ERTC_InitStruct->AsynchPrediv = 0x7F;
  ERTC_InitStruct->SynchPrediv  = 0xFF;

  /* Default Date: Monday, January 01 xx01                                                                  */
  ERTC_InitStruct->Date.WeekDay = ERTC_WEEKDAY_MONDAY;
  ERTC_InitStruct->Date.Day     = 1;
  ERTC_InitStruct->Date.Month   = 1;
  ERTC_InitStruct->Date.Year    = 1;

  /* Default Time: 00h:00min:00sec                                                                          */
  ERTC_InitStruct->Time.AMPM    = ERTC_AM;
  ERTC_InitStruct->Time.Hours   = 1;
  ERTC_InitStruct->Time.Minutes = 0;
  ERTC_InitStruct->Time.Seconds = 0;
  ERTC_InitStruct->Time.FMT     = ERTC_HOURFORMAT_12;
}

/*********************************************************************************************************//**
 * @brief  Enables or disables the ERTC registers write protection.
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_WriteProtectionCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
  /* Enable the write protection for ERTC registers                                                         */
    HT_ERTC->WPR = 0xFFFF;
  }
  else
  {
    /* Disable the write protection for ERTC registers                                                      */
    HT_ERTC->WPR = gERTCUnProtectKey;
  }
}

/*********************************************************************************************************//**
 * @brief  Select the ERTC timer clock source.
 * @param  Source: Specifies the clock source of ERTC and VDD power domain.
 *   @arg  ERTC_SRC_NOCLOCK   : No clock.
 *   @arg  ERTC_SRC_LSI       : Low speed internal clock.
 *   @arg  ERTC_SRC_LSE       : Low speed external clock.
 *   @arg  ERTC_SRC_HSE_DIV32 : High speed external clock divided by 32.
 * @retval None
 ************************************************************************************************************/
void ERTC_ClockSourceConfig(ERTC_SRC_Enum Source)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_CLOCK_SRC(Source));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  HT_ERTC->CR0 = (HT_ERTC->CR0 & ~ERTC_ERTCSRC_MASK) | Source;
  while((HT_ERTC->CR0 & ERTC_ERTCSRC_MASK) != Source);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief Set CK_ERTC HSE division value.
 * @param Div: HSE Prescaler Selection bits [3:2].
 *   This parameter can be one of the following values:
 *     @arg ERTC_HSE_DIV32: HSE/32 clock is selected
 *     @arg ERTC_HSE_DIV16: HSE/16 clock is selected
 *     @arg ERTC_HSE_DIV8 : HSE/8  clock is selected
 *     @arg ERTC_HSE_DIV4 : HSE/4  clock is selected
 * @retval None
 ************************************************************************************************************/
void ERTC_LSEDIVConfig(ERTC_HSEDIV_Enum Div)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_HSE_DIV(Div));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  HT_ERTC->CR1 = (HT_ERTC->CR1 & ~ERTC_HSEPRESEL_MASK) | Div;
  while((HT_ERTC->CR1 & ERTC_HSEPRESEL_MASK) != Div);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Select the LSE startup mode.
 * @param  Mode: specify the LSE startup mode.
 *   This parameter can be one of the following values:
 *     @arg ERTC_LSESM_SLOW: Slow startup and requires least operating power
 *     @arg ERTC_LSESM_MEDIUM_SLOW: Medium-slow startup and requires less operating power
 *     @arg ERTC_LSESM_MEDIUM_FAST: Medium-fast startup and requires more operating power
 *     @arg ERTC_LSESM_FAST: Fast startup and requires high operating current.
 * @retval None
 ************************************************************************************************************/
void ERTC_LSESMConfig(ERTC_LSESM_Enum Mode)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_LSESM(Mode));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  HT_ERTC->CR0 = (HT_ERTC->CR0 & ~ERTC_LSESM_MASK) | ((u32)Mode << ERTC_LSESM_SHIFT);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Enable or Disable the LSE clock.
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_LSECmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if (NewState == DISABLE)
  {
    Reset_LSEEN;
    while (HT_CKCU->GCSR & CKCU_FLAG_LSERDY);
  }
  else
  {
    Set_LSEEN;
    while ((HT_CKCU->GCSR & CKCU_FLAG_LSERDY) == 0);
  }

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Set the ERTC current date.
 * @param  ERTC_DateStruct: pointer to a ERTC_DateTypeDef structure that contains
 *         the date configuration information for the ERTC.
 * @retval None
 ************************************************************************************************************/
void ERTC_SetDateBCD(ERTC_DateTypeDef* ERTC_DateStruct)
{
    /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_YEAR(_ERTC_BcdToByte(ERTC_DateStruct->Year)));
  Assert_Param(IS_ERTC_MONTH(_ERTC_BcdToByte(ERTC_DateStruct->Month)));
  Assert_Param(IS_ERTC_DATE(_ERTC_BcdToByte(ERTC_DateStruct->Day)));
  Assert_Param(IS_ERTC_WEEKDAY(ERTC_DateStruct->WeekDay));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  ERTC_Cmd(DISABLE);

  HT_ERTC->CAR1 = (HT_ERTC->CAR1 & ERTC_HOUR_MASK & ERTC_AMPM_MASK)    | \
                  ((ERTC_DateStruct->Day) << ERTC_DAY_MASK_SHIFT);
  HT_ERTC->CAR2 = (ERTC_DateStruct->Year    << ERTC_YEAR_MASK_SHIFT)    | \
                  (ERTC_DateStruct->Month   << ERTC_MONTH_MASK_SHIFT)   | \
                  (ERTC_DateStruct->WeekDay << ERTC_WEEKDAY_MASK_SHIFT);

  ERTC_Cmd(ENABLE);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Set the ERTC current date (binary format).
 * @param  ERTC_DateStruct: pointer to a ERTC_DateTypeDef structure that contains
 *         the date configuration information for the ERTC.
 * @retval None
 ************************************************************************************************************/
void ERTC_SetDate(ERTC_DateTypeDef* ERTC_DateStruct)
{
  ERTC_DateTypeDef tmpStruct = *ERTC_DateStruct;

  tmpStruct.Year  = _ERTC_ByteToBcd(ERTC_DateStruct->Year);
  tmpStruct.Month = _ERTC_ByteToBcd(ERTC_DateStruct->Month);
  tmpStruct.Day   = _ERTC_ByteToBcd(ERTC_DateStruct->Day);

  ERTC_SetDateBCD(&tmpStruct);
}

/*********************************************************************************************************//**
 * @brief  Set the ERTC current time.
 * @param  ERTC_TimeStruct: pointer to a ERTC_TimeTypeDef structure that contains
 *         the time configuration information for the ERTC.
 * @retval None.
 ************************************************************************************************************/
void ERTC_SetTimeBCD(ERTC_TimeTypeDef* ERTC_TimeStruct)
{
    /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_HOUR_FORMAT(ERTC_TimeStruct->FMT));
  Assert_Param(IS_ERTC_MINUTES(_ERTC_BcdToByte(ERTC_TimeStruct->Minutes)));
  Assert_Param(IS_ERTC_SECONDS(_ERTC_BcdToByte(ERTC_TimeStruct->Seconds)));

  _ERTC_HourInputFormat_24_to_12(ERTC_TimeStruct);

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  ERTC_Cmd(DISABLE);
  /* Set the ERTC Date & Time                                                                               */
  HT_ERTC->CAR0 = (ERTC_TimeStruct->Minutes << ERTC_MINUTE_MASK_SHIFT) | \
                  (ERTC_TimeStruct->Seconds << ERTC_SECOND_MASK_SHIFT);
  HT_ERTC->CAR1 = (HT_ERTC->CAR1 & ERTC_YEAR_MASK)                         | \
                  (ERTC_TimeStruct->Hours << ERTC_HOUR_MASK_SHIFT)    | \
                  (ERTC_TimeStruct->AMPM << ERTC_AMPM_MASK_SHIFT);
  ERTC_Cmd(ENABLE);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Set the ERTC current time.(binary format)
 * @param  ERTC_TimeStruct: pointer to a ERTC_TimeTypeDef structure that contains
 *         the time configuration information for the ERTC.
 * @retval None.
 ************************************************************************************************************/
void ERTC_SetTime(ERTC_TimeTypeDef* ERTC_TimeStruct)
{
  ERTC_TimeTypeDef tmpStruct = *ERTC_TimeStruct;
  tmpStruct.Hours   = _ERTC_ByteToBcd(ERTC_TimeStruct->Hours);
  tmpStruct.Minutes = _ERTC_ByteToBcd(ERTC_TimeStruct->Minutes);
  tmpStruct.Seconds = _ERTC_ByteToBcd(ERTC_TimeStruct->Seconds);
  ERTC_SetTimeBCD(&tmpStruct);
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC current date.
 * @param  ERTC_DateStruct: Pointer to an ERTC_DateTypeDef structure that will
 *         contain the returned current date configuration.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetDateBCD(ERTC_DateTypeDef* ERTC_DateStruct)
{
  u32 SSR1, SSR2, CAR1, CAR2;
  do
  {
    SSR1 = HT_ERTC->SSR;
    CAR1 = HT_ERTC->CAR1;
    CAR2 = HT_ERTC->CAR2;
    SSR2 = HT_ERTC->SSR;
  }while(SSR1 != SSR2);

  /* Fill the structure fields with the read parameters                                                     */
  ERTC_DateStruct->Year    = (CAR2 & ERTC_YEAR_MASK)    >> ERTC_YEAR_MASK_SHIFT;
  ERTC_DateStruct->Month   = (CAR2 & ERTC_MONTH_MASK)   >> ERTC_MONTH_MASK_SHIFT;
  ERTC_DateStruct->Day     = (CAR1 & ERTC_DAY_MASK)     >> ERTC_DAY_MASK_SHIFT;
  ERTC_DateStruct->WeekDay = (CAR2 & ERTC_WEEKDAY_MASK) >> ERTC_WEEKDAY_MASK_SHIFT;
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC current date.(binary format)
 * @param  ERTC_DateStruct: Pointer to an ERTC_DateTypeDef structure that will
 *         contain the returned current date configuration.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetDate(ERTC_DateTypeDef* ERTC_DateStruct)
{
  ERTC_GetDateBCD(ERTC_DateStruct);
  ERTC_DateStruct->Year  = _ERTC_BcdToByte(ERTC_DateStruct->Year);
  ERTC_DateStruct->Month = _ERTC_BcdToByte(ERTC_DateStruct->Month);
  ERTC_DateStruct->Day   = _ERTC_BcdToByte(ERTC_DateStruct->Day);
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC current time.
 * @param  ERTC_TimeStruct: Pointer to an ERTC_TimeTypeDef structure that will
 *         contain the returned current time configuration.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetTimeBCD(ERTC_TimeTypeDef* ERTC_TimeStruct)
{
  u32 SSR1, SSR2, CAR0, CAR1;
  do
  {
    SSR1 = HT_ERTC->SSR;
    CAR0 = HT_ERTC->CAR0;
    CAR1 = HT_ERTC->CAR1;
    SSR2 = HT_ERTC->SSR;
  }while(SSR1 != SSR2);

  /* Fill the structure fields with the read parameters                                                     */
  ERTC_TimeStruct->Hours   = (CAR1 & ERTC_HOUR_MASK)   >> ERTC_HOUR_MASK_SHIFT;
  ERTC_TimeStruct->Minutes = (CAR0 & ERTC_MINUTE_MASK) >> ERTC_MINUTE_MASK_SHIFT;
  ERTC_TimeStruct->Seconds = (CAR0 & ERTC_SECOND_MASK) >> ERTC_SECOND_MASK_SHIFT;
  ERTC_TimeStruct->AMPM    = (CAR1 & ERTC_AMPM_MASK)   >> ERTC_AMPM_MASK_SHIFT;
  ERTC_TimeStruct->FMT     = HT_ERTC->CR0 & ERTC_HOURFORMAT_MASK;
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC current time.(binary format)
 * @param  ERTC_TimeStruct: Pointer to an ERTC_TimeTypeDef structure that will
 *         contain the returned current time configuration.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetTime(ERTC_TimeTypeDef* ERTC_TimeStruct)
{
  ERTC_GetTimeBCD(ERTC_TimeStruct);
  ERTC_TimeStruct->Hours   = _ERTC_BcdToByte(ERTC_TimeStruct->Hours);
  ERTC_TimeStruct->Minutes = _ERTC_BcdToByte(ERTC_TimeStruct->Minutes);
  ERTC_TimeStruct->Seconds = _ERTC_BcdToByte(ERTC_TimeStruct->Seconds);
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC current date and time.
 * @param  ERTC_DateStruct: Pointer to an ERTC_DateTypeDef structure that will
 *         contain the returned current date configuration.
 * @param  ERTC_TimeStruct: Pointer to an ERTC_TimeTypeDef structure that will
 *         contain the returned current time configuration.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetDateTimeBCD(ERTC_DateTypeDef* ERTC_DateStruct, ERTC_TimeTypeDef* ERTC_TimeStruct)
{
  u32 SSR1, SSR2, CAR0, CAR1, CAR2;
  do
  {
    SSR1 = HT_ERTC->SSR;
    CAR0 = HT_ERTC->CAR0;
    CAR1 = HT_ERTC->CAR1;
    CAR2 = HT_ERTC->CAR2;
    SSR2 = HT_ERTC->SSR;
  }while(SSR1 != SSR2);

  /* Fill the date structure fields */
  ERTC_DateStruct->Year    = (CAR2 & ERTC_YEAR_MASK)    >> ERTC_YEAR_MASK_SHIFT;
  ERTC_DateStruct->Month   = (CAR2 & ERTC_MONTH_MASK)   >> ERTC_MONTH_MASK_SHIFT;
  ERTC_DateStruct->Day     = (CAR1 & ERTC_DAY_MASK)     >> ERTC_DAY_MASK_SHIFT;
  ERTC_DateStruct->WeekDay = (CAR2 & ERTC_WEEKDAY_MASK) >> ERTC_WEEKDAY_MASK_SHIFT;

  /* Fill the time structure fields */
  ERTC_TimeStruct->Hours   = (CAR1 & ERTC_HOUR_MASK)   >> ERTC_HOUR_MASK_SHIFT;
  ERTC_TimeStruct->Minutes = (CAR0 & ERTC_MINUTE_MASK) >> ERTC_MINUTE_MASK_SHIFT;
  ERTC_TimeStruct->Seconds = (CAR0 & ERTC_SECOND_MASK) >> ERTC_SECOND_MASK_SHIFT;
  ERTC_TimeStruct->AMPM    = (CAR1 & ERTC_AMPM_MASK)   >> ERTC_AMPM_MASK_SHIFT;

  ERTC_TimeStruct->FMT = HT_ERTC->CR0 & ERTC_HOURFORMAT_MASK;
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC current date and time.(binary format)
 * @param  ERTC_DateStruct: Pointer to an ERTC_DateTypeDef structure that will
 *         contain the returned current date configuration.
 * @param  ERTC_TimeStruct: Pointer to an ERTC_TimeTypeDef structure that will
 *         contain the returned current time configuration.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetDateTime(ERTC_DateTypeDef* ERTC_DateStruct, ERTC_TimeTypeDef* ERTC_TimeStruct)
{
  ERTC_GetDateTimeBCD(ERTC_DateStruct, ERTC_TimeStruct);

  ERTC_DateStruct->Year    = _ERTC_BcdToByte(ERTC_DateStruct->Year);
  ERTC_DateStruct->Month   = _ERTC_BcdToByte(ERTC_DateStruct->Month);
  ERTC_DateStruct->Day     = _ERTC_BcdToByte(ERTC_DateStruct->Day);
  ERTC_DateStruct->WeekDay = _ERTC_BcdToByte(ERTC_DateStruct->WeekDay);

  ERTC_TimeStruct->Hours   = _ERTC_BcdToByte(ERTC_TimeStruct->Hours);
  ERTC_TimeStruct->Minutes = _ERTC_BcdToByte(ERTC_TimeStruct->Minutes);
  ERTC_TimeStruct->Seconds = _ERTC_BcdToByte(ERTC_TimeStruct->Seconds);
}

/*********************************************************************************************************//**
 * @brief  Gets the ERTC current Calendar Subseconds value.
 * @note   This function freeze the Time and Date registers after reading the SSR register.
 * @retval ERTC current Calendar Subseconds value.
 ************************************************************************************************************/
u32 ERTC_GetSubSecond(void)
{
  u16 spsc = HT_ERTC->SPSC;
  return ((spsc & 0x7FFF) - HT_ERTC->SSR);
}

/*********************************************************************************************************//**
 * @brief  Gets the ERTC current Calendar Subseconds value in milliseconds.
 * @note   Calculates how many milliseconds per tick, then converts the elapsed ticks to milliseconds.
 * @retval ERTC current Calendar Subseconds value in milliseconds.
 ************************************************************************************************************/
u32 ERTC_GetSubSecondms(void)
{
  /* Compute and cache the conversion factor if not already calculated                                      */
  if (gERTCSubSecondms == 0)
  {
    gERTCSubSecondms = (1000 << 20) / ((HT_ERTC->SPSC & 0x7FFF) + 1);
  }

  /* Elapsed ticks * milliseconds per tick = elapsed milliseconds                                           */
  return ((ERTC_GetSubSecond() * gERTCSubSecondms) >> 20);
}

/*********************************************************************************************************//**
 * @brief  Gets the ERTC current Calendar Subseconds value in microseconds.
 * @note   Calculates how many microseconds per tick, then converts the elapsed ticks to microseconds.
 * @retval ERTC current Calendar Subseconds value in microseconds.
 ************************************************************************************************************/
u32 ERTC_GetSubSecondus(void)
{
  /* Compute and cache the conversion factor if not already calculated                                      */
  if (gERTCSubSecondus == 0)
  {
    gERTCSubSecondus = 1000000 << 10 / ((HT_ERTC->SPSC & 0x7FFF) + 1);
  }

  /* Elapsed ticks * microseconds per tick = elapsed microseconds                                           */
  return ((ERTC_GetSubSecond() * gERTCSubSecondus) >> 10);
}

/*********************************************************************************************************//**
 * @brief  Configures the ERTC Wakeup clock source.
 * @note   The Wakeup Clock source can only be changed when the ERTC Wakeup
 *         is disabled (Use the ERTC_WakeupTimerCmd(DISABLE)).
 * @param  ERTC_WakeupClock: Wakeup Clock source.
 *   This parameter can be one of the following values:
 *     @arg ERTC_WUP_TM_ERTC_DIV16 : ERTC Wakeup Counter Clock = RTCCLK/16
 *     @arg ERTC_WUP_TM_ERTC_DIV8  : ERTC Wakeup Counter Clock = RTCCLK/8
 *     @arg ERTC_WUP_TM_ERTC_DIV4  : ERTC Wakeup Counter Clock = RTCCLK/4
 *     @arg ERTC_WUP_TM_ERTC_DIV2  : ERTC Wakeup Counter Clock = RTCCLK/2
 *     @arg ERTC_WUP_TM_SPRE       : ERTC Wakeup Counter Clock = CK_SPRE Compare: 1~65536
 *     @arg ERTC_WUP_TM_SPRE_EXT   : ERTC Wakeup Counter Clock = CK_SPRE Compare: 65537~131072
 * @retval None
 ************************************************************************************************************/
void ERTC_WakeupTimerClockConfig(u8 ERTC_WakeupClock)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_WAKEUP_CLOCK(ERTC_WakeupClock));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if((HT_ERTC->CR1 & ERTC_WUTEN_MASK) != RESET)
  {
    Reset_WUTEN;
  }
  while(!(HT_ERTC->SR & ERTC_FLAG_WUTWF));

  /* Configure the clock source                                                                             */
  HT_ERTC->CR1 = (HT_ERTC->CR1 & ~ERTC_WUCLSEL_MASK) | (ERTC_WakeupClock << ERTC_WUCLSEL_SHIFT);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Configures the ERTC Wakeup Compare.
 * @note   The ERTC Wakeup counter can only be written when the ERTC Wakeup
 *         is disabled (Use the ERTC_WakeupTimerCmd(DISABLE)).
 * @param  Compare: specifies the Wakeup Timer.
 *         This parameter can be a value from 0x0001 to 0x10000.
 * @retval None
 ************************************************************************************************************/
void ERTC_SetWakeupTimerCompare(u32 Compare)
{
  Compare -= 1;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_WAKEUP_COUNTER(Compare));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if(HT_ERTC->CR1 & ERTC_WUTEN_MASK)
  {
    Reset_WUTEN;
    while(!(HT_ERTC->SR & ERTC_FLAG_WUTWF));
    HT_ERTC->WUTR = Compare & 0xFFFF;
    Set_WUTEN;
    while((HT_ERTC->SR & ERTC_FLAG_WUTWF));
  }
  else
  {
    Reset_WUTEN;
    while(!(HT_ERTC->SR & ERTC_FLAG_WUTWF));
    HT_ERTC->WUTR = Compare & 0xFFFF;
  }

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Configures the ERTC Wakeup Compare.
 * @retval Wakeup Compare
 ************************************************************************************************************/
u32 ERTC_GetWakeupTimerCompare(void)
{
  return HT_ERTC->WUTR + 1;
}

/*********************************************************************************************************//**
 * @brief  Enables or Disables the ERTC Wakeup timer.
 * @param  NewState: new state of the Wakeup timer.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_WakeupTimerCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if (NewState == ENABLE)
  {
    Set_WUTEN;
  }
  else
  {
    Reset_WUTEN;
    while((HT_ERTC->SR & ERTC_FLAG_WUTWF) == RESET);
  }
  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Enable or Disable the specified wakeup source.
 * @param  ERTC_WAKEUP Selection of Wakeup source.
 *   This parameter can be any combination of the following values:
 *     @arg  ERTC_WAKEUP_ALR : Waken up by alarm.
 *     @arg  ERTC_WAKEUP_WUT  : Waken up by wakeup timer.
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_WakeupConfig(u32 ERTC_WAKEUP, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_WAKEUP(ERTC_WAKEUP));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if (NewState != DISABLE)
  {
    HT_ERTC->CR1 |= ERTC_WAKEUP;
  }
  else
  {
    HT_ERTC->CR1 &= ~ERTC_WAKEUP;
  }

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Enables or disables the specified ERTC interrupts.
 * @param  ERTC_INT_x: specifies the ERTC interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ERTC_INT_CRS : Calendar Registers Synchronisation Interrupt mask
 *     @arg ERTC_INT_WUT : Wakeup Timer interrupt mask
 *     @arg ERTC_INT_ALR : Alarm interrupt mask
 * @param  NewState: new state of the specified ERTC interrupts.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_IntConfig(u32 ERTC_INT_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_CONFIG_INT(ERTC_INT_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR  = gERTCUnProtectKey;

  if (NewState == ENABLE)
  {
    HT_ERTC->CR1 |= ERTC_INT_x;
  }
  else
  {
    HT_ERTC->CR1 &= ~(ERTC_INT_x);
  }

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Set the specified ERTC Alarm.
 * @note   The Alarm register can only be written when the corresponding Alarm
 *         is disabled (Use the ERTC_AlarmCmd(DISABLE)).
 * @param  ERTC_AlarmStruct: pointer to a ERTC_AlarmTypeDef structure that
 *                           contains the alarm configuration parameters.
 * @retval None
 ************************************************************************************************************/
void ERTC_SetAlarmBCD(ERTC_AlarmTypeDef* ERTC_AlarmStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_ALARM_DATE_WEEKDAY_SEL(ERTC_AlarmStruct->AlarmDateWeekDaySel));
  Assert_Param(IS_ERTC_HOUR12(_ERTC_BcdToByte(ERTC_AlarmStruct->AlarmTime.Hours)));
  Assert_Param(IS_ERTC_MINUTES(_ERTC_BcdToByte(ERTC_AlarmStruct->AlarmTime.Minutes)));
  Assert_Param(IS_ERTC_SECONDS(_ERTC_BcdToByte(ERTC_AlarmStruct->AlarmTime.Seconds)));
  if (ERTC_AlarmStruct->AlarmDateWeekDaySel == ERTC_ALARMSEL_DATE)
  {
    Assert_Param(IS_ERTC_ALARM_DATE_WEEKDAY_DATE(_ERTC_BcdToByte(ERTC_AlarmStruct->AlarmDateWeekDay)));
  }
  else
  {
    Assert_Param(IS_ERTC_ALARM_DATE_WEEKDAY_WEEKDAY(_ERTC_BcdToByte(ERTC_AlarmStruct->AlarmDateWeekDay)));
  }
  _ERTC_HourInputFormat_24_to_12(&ERTC_AlarmStruct->AlarmTime);
  /* Disable the Alarm register                                                                             */
  ERTC_AlarmCmd(DISABLE);

  /* Disable the write protection for ERTC registers                                                        */
  HT_ERTC->WPR = gERTCUnProtectKey;

  while(!(HT_ERTC->SR  &  ERTC_FLAG_ALRWF));
  HT_ERTC->ALMR0 = (ERTC_AlarmStruct->AlarmMask.AlarmMask_Minute << ERTC_ALARM_ALMINAE_SHIFT) | \
                   (ERTC_AlarmStruct->AlarmMask.AlarmMask_Second << ERTC_ALARM_ALSECE_SHIFT)  | \
                   (ERTC_AlarmStruct->AlarmTime.Minutes << ERTC_ALARM_MINUTE_MASK_SHIFT)      | \
                   (ERTC_AlarmStruct->AlarmTime.Seconds << ERTC_ALARM_SECOND_MASK_SHIFT);
  HT_ERTC->ALMR1 = (ERTC_AlarmStruct->AlarmMask.AlarmMask_Day  << ERTC_ALARM_ALDAY_SHIFT)    | \
                   (ERTC_AlarmStruct->AlarmMask.AlarmMask_Hour << ERTC_ALARM_ALHOURAE_SHIFT) | \
                   ((ERTC_AlarmStruct->AlarmDateWeekDaySel                                        | \
                    (ERTC_AlarmStruct->AlarmDateWeekDay)   << ERTC_ALARM_DATEWEEKDAY_MASK_SHIFT)) | \
                   (ERTC_AlarmStruct->AlarmTime.AMPM  << ERTC_ALARM_AMPM_MASK_SHIFT)         | \
                   (ERTC_AlarmStruct->AlarmTime.Hours << ERTC_ALARM_HOUR_MASK_SHIFT);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Set the specified ERTC Alarm.(binary format)
 * @note   The Alarm register can only be written when the corresponding Alarm
 *         is disabled (Use the ERTC_AlarmCmd(DISABLE)).
 * @param  ERTC_AlarmStruct: pointer to a ERTC_AlarmTypeDef structure that
 *                           contains the alarm configuration parameters.
 * @retval None
 ************************************************************************************************************/
void ERTC_SetAlarm(ERTC_AlarmTypeDef* ERTC_AlarmStruct)
{
  ERTC_AlarmTypeDef tmpStruct = *ERTC_AlarmStruct;
  tmpStruct.AlarmTime.FMT     = _ERTC_ByteToBcd(ERTC_AlarmStruct->AlarmTime.FMT);
  tmpStruct.AlarmTime.Hours   = _ERTC_ByteToBcd(ERTC_AlarmStruct->AlarmTime.Hours);
  tmpStruct.AlarmTime.Minutes = _ERTC_ByteToBcd(ERTC_AlarmStruct->AlarmTime.Minutes);
  tmpStruct.AlarmTime.Seconds = _ERTC_ByteToBcd(ERTC_AlarmStruct->AlarmTime.Seconds);
  if(ERTC_AlarmStruct->AlarmDateWeekDaySel == ERTC_ALARMSEL_DATE)
  {
    tmpStruct.AlarmDateWeekDay = _ERTC_ByteToBcd(ERTC_AlarmStruct->AlarmDateWeekDay);
  }
  ERTC_SetAlarmBCD(&tmpStruct);
}

/*********************************************************************************************************//**
 * @brief  Configure the ERTC  Alarm Subseconds value and mask.*
 * @note   This function is performed  only when  the  Alarm is disabled.
 * @param  ERTC_AlarmSubSecondValue: specifies the Subseconds  value.
 *         This parameter  can  be a value from  0  to 0x00007FFF.
 * @param  ERTC_AlarmSubSecondMask: specifies the Subseconds  Mask.
 *   This parameter  can  be any combination of  the  following  values:
 *     @arg ERTC_ALARM_SUBSECOND_MASK_ALL    : All Alarm SS fields are masked.
 *                                             There is no comparison  on sub seconds for Alarm.
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_1 : SS[14:1] are don't care in Alarm comparison.
 *                                             Only SS[0] is compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_2 : SS[14:2] are don't care in Alarm comparison.
 *                                             Only SS[1:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_3 : SS[14:3] are don't care in Alarm comparison.
 *                                             Only SS[2:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_4 : SS[14:4] are don't care in Alarm comparison.
 *                                             Only SS[3:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_5 : SS[14:5] are don't care in Alarm comparison.
 *                                             Only SS[4:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_6 : SS[14:6] are don't care in Alarm comparison.
 *                                             Only SS[5:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_7 : SS[14:7] are don't care in Alarm comparison.
 *                                             Only SS[6:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_8 : SS[14:8] are don't care in Alarm comparison.
 *                                             Only SS[7:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_9 : SS[14:9] are don't care in Alarm comparison.
 *                                             Only SS[8:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_10: SS[14:10] are don't care in Alarm comparison.
 *                                             Only SS[9:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_11: SS[14:11] are don't care in Alarm comparison.
 *                                             Only SS[10:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_12: SS[14:12] are don't care in Alarm comparison.
 *                                             Only SS[11:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14_13: SS[14:13] are don't care in Alarm comparison.
 *                                             Only SS[12:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_SS14   : SS[14] is don't care in Alarm comparison.
 *                                             Only SS[13:0] are compared
 *     @arg ERTC_ALARM_SUBSECOND_MASK_NONE   : SS[14:0] are compared and must  match  to activate alarm
 * @retval None
 ************************************************************************************************************/
void ERTC_AlarmSubSecondConfig(u16 ERTC_AlarmSubSecondValue, u8 ERTC_AlarmSubSecondMask)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_ALARM_SUB_SECOND_VALUE(ERTC_AlarmSubSecondValue));
  Assert_Param(IS_ERTC_ALARM_SUB_SECOND_MASK(ERTC_AlarmSubSecondMask));

  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;

  while(!(HT_ERTC->SR  &  ERTC_FLAG_ALRWF));

  /* Configure the Alarm SubSecond registers                                                                */
  HT_ERTC->ALMSSMR = ERTC_AlarmSubSecondMask;
  HT_ERTC->ALMSSR  = ERTC_AlarmSubSecondValue;

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}


/*********************************************************************************************************//**
 * @brief Enables or disables the specified ERTC Alarm.
 * @param NewState: new state of the specified alarm.
 *        This parameter can be: ENABLE or DISABLE.
 ************************************************************************************************************/
void ERTC_AlarmCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if (NewState != DISABLE)
  {
    Set_ALREN;
  }
  else
  {
    Reset_ALREN;
    while((HT_ERTC->SR & ERTC_FLAG_ALRWF) == RESET);
  }
  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Checks whether the specified ERTC flag is set or not.
 * @param  ERTC_FLAG_x: specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ERTC_FLAG_WUTWF: Wakeup Timer write flag
 *     @arg ERTC_FLAG_WUTF : Wakeup Timer flag
 *     @arg ERTC_FLAG_TSOVF: Time Stamp Overflow flag
 *     @arg ERTC_FLAG_TSF  : Time Stamp event flag
 *     @arg ERTC_FLAG_ALRF : Alarm flag
 *     @arg ERTC_FLAG_RTCOF: ERTC output flag
 *     @arg ERTC_FLAG_ALRWF: Alarm write flag
 *     @arg ERTC_FLAG_SHPF : Shift operation pending flag
 *     @arg ERTC_FLAG_CRSF : Calendar Register Synchronisation flag
 *     @arg ERTC_FLAG_INITF: Initialisation flag
 * @retval The new state of  ERTC_FLAG (SET or RESET).
 ************************************************************************************************************/
FlagStatus ERTC_GetFlagStatus(u32 ERTC_FLAG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_GET_FLAG(ERTC_FLAG_x));
  if(HT_ERTC->SR & ERTC_FLAG_x)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief  Clears the ERTC's pending flags.
 * @param  ERTC_FLAG_x: specifies the ERTC flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg ERTC_FLAG_WUTF  : Wakeup Timer flag
 *     @arg ERTC_FLAG_TSOVF : Time Stamp Overflow flag
 *     @arg ERTC_FLAG_TSF   : Time Stamp event flag
 *     @arg ERTC_FLAG_ALRF  : Alarm flag
 *     @arg ERTC_FLAG_RTCOF : ERTC output flag
 *     @arg ERTC_FLAG_CRSF  : Registers Synchronized  flag
 * @retval None
 ************************************************************************************************************/
void ERTC_ClearFlag(u32 ERTC_FLAG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_CLEAR_FLAG(ERTC_FLAG_x));

  if(ERTC_FLAG_x & ERTC_FLAG_RTCOF)
  {
    Set_ROCLR; //write 1 to ROCLR to clear RTCOF
  }

  /* Clear the Flags in the ERTC_ISR register                                                               */
  HT_ERTC->SR = ERTC_FLAG_x;
}

/*********************************************************************************************************//**
 * @brief  Configures the ERTC output source.
 * @param  WMode: Specifies the output mode of the output signal.
 *     @arg ERTC_ROWM_TOGGLE
 *     @arg ERTC_ROWM_PULSE
 *     @arg ERTC_ROWM_LEVEL
 * @param  EventSel: Specifies which signal will be routed to the ERTC output.
 *   This parameter can be one of the following values:
 *     @arg ERTC_ROES_ALARM  : signal of Alarm mapped to output
 *     @arg ERTC_ROES_WAKEUP : signal of Wakeup mapped to output
 *     @arg ERTC_ROES_SPRE   : SPRE clock mapped to output
 *     @arg ERTC_ROES_APRE   : APRE clock mapped to output
 * @param  Pol: Specifies the polarity of the output signal.
 *   This parameter can be one of the following:
 *     @arg ERTC_ROAP_HIGH : The output pin is high when the ALRF/WUTF is high
 *     @arg ERTC_ROAP_LOW  : The output pin is low  when the ALRF/WUTF is high
 * @retval None
 ************************************************************************************************************/
void ERTC_OutConfig(ERTC_ROWM_Enum WMode, ERTC_ROES_Enum EventSel, ERTC_ROAP_Enum Pol)
{
  u16 ROEN;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_OUTPUT(EventSel));
  Assert_Param(IS_ERTC_OUTPUT_POL(Pol));

  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;

  ERTC_ClearFlag(ERTC_FLAG_RTCOF);
  ROEN = HT_ERTC->CR0 & ERTC_ROEN_MASK;

  //* Clear ROEN, ROAP, ROES, ROWM bits                                                                     */
  HT_ERTC->CR0 &= ~(0xFC00); 
  while(HT_ERTC->CR0 & ERTC_ROEN_MASK);

  /* Configure the output selection and polarity */
  if((EventSel & ERTC_ROES_SPRE) || (EventSel & ERTC_ROES_APRE))
  {
    HT_ERTC->CR0 |= (ROEN | WMode);
  }
  else
  {
    HT_ERTC->CR0 |= (ROEN | WMode | EventSel | Pol);
  }

  if(ROEN)
  {
    while(!(HT_ERTC->CR0 & ERTC_ROEN_MASK));
  }
  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Enables or Disables the ERTC Output.
 * @param  NewState: new state of the Wakeup timer.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_OutCmd(ControlStatus NewState)
{
  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if(NewState == ENABLE)
  {
    HT_ERTC->CR0 |= ERTC_ROEN_MASK;
    while(!(HT_ERTC->CR0 & ERTC_ROEN_MASK));
  }
  else
  {
    HT_ERTC->CR0 &= ~ERTC_ROEN_MASK;
    while(HT_ERTC->CR0 & ERTC_ROEN_MASK);
  }

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Configures the Calibration Settings.
 * @param  ERTC_CalibPeriod : Select the Smooth Calibration Period.
 *   This parameter can be can be one of the following values:
 *     @arg ERTC_CALIB_PERIOD_32 : The calibration periode is 32s.
 *     @arg ERTC_CALIB_PERIOD_16 : The calibration periode is 16s.
 *     @arg ERTC_CALIB_PERIOD_8  : The calibartion periode is  8s.
 * @param  ERTC_CalibPlusMask
 *   This parameter can be one of the following values:
 *     @arg ERTC_CALIB_ADD_PULSES
 *     @arg ERTC_CALIB_MASK_PULSES
 * @param  ERTC_CalibValue: Select the value of CALV[7:0] bits.
 *         This parameter can be one any value from 0 to 0x000000FF.
 * @retval None
 ************************************************************************************************************/
void ERTC_CalibConfig(u16 ERTC_CalibPeriod, u16 ERTC_CalibPlusMask, u8 ERTC_CalibValue)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_CALIB_PERIOD(ERTC_CalibPeriod));
  Assert_Param(IS_ERTC_CALIB_PLUS(ERTC_CalibPlusMask));

  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;
  if(ERTC_CalibPeriod == ERTC_CALIB_PERIOD_16)
  {
    ERTC_CalibValue = ERTC_CalibValue << 1;
  }
  else if(ERTC_CalibPeriod == ERTC_CALIB_PERIOD_8)
  {
    ERTC_CalibValue = ERTC_CalibValue << 2;
  }
  /* Configure the Smooth calibration settings */
  HT_ERTC->CALR = (HT_ERTC->CALR & ERTC_CALEN_MASK) | ERTC_CalibPeriod | ERTC_CalibPlusMask | ERTC_CalibValue;

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Enables or disables the calibration process.
 * @param  NewState: new state of the calibration.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_CalibCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));
  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;

  ERTC_Cmd(DISABLE);
  if (NewState != DISABLE)
  {
    Set_CALEN;
  }
  else
  {
    Reset_CALEN;
  }
  ERTC_Cmd(ENABLE);

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Enables or Disables the ERTC TimeStamp functionality.
 * @param  NewState: new state of the TimeStamp.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ERTC_TimeStampCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));
  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;

  if (NewState != DISABLE)
  {
    Set_TSEN;
  }
  else
  {
    Reset_TSEN;
  }

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC TimeStamp value and masks.
 * @param  ERTC_StampTimeStruct: pointer to a ERTC_TimeTypeDef structure that will
 *         contains the TimeStamp time values.
 * @param  ERTC_StampDateStruct: pointer to a ERTC_DateTypeDef structure that will
 *         contains the TimeStamp date values.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetTimeStampBCD(ERTC_DateTypeDef* ERTC_StampDateStruct, ERTC_TimeTypeDef* ERTC_StampTimeStruct)
{
  u32 TSR0, TSR1, TSR2;

  TSR0 = HT_ERTC->TSR0;
  TSR1 = HT_ERTC->TSR1;
  TSR2 = HT_ERTC->TSR2;

  ERTC_StampTimeStruct->Hours   = (TSR1 & ERTC_HOUR_MASK)   >> ERTC_HOUR_MASK_SHIFT;
  ERTC_StampTimeStruct->Minutes = (TSR0 & ERTC_MINUTE_MASK) >> ERTC_MINUTE_MASK_SHIFT;
  ERTC_StampTimeStruct->Seconds = (TSR0 & ERTC_SECOND_MASK) >> ERTC_SECOND_MASK_SHIFT;
  ERTC_StampTimeStruct->AMPM    = (TSR1 & ERTC_AMPM_MASK)   >> ERTC_AMPM_MASK_SHIFT;
  ERTC_StampTimeStruct->FMT     = HT_ERTC->CR0 & ERTC_HOURFORMAT_MASK;

  ERTC_StampDateStruct->Year    = 0;
  ERTC_StampDateStruct->Month   = (TSR2 & ERTC_MONTH_MASK)   >> ERTC_MONTH_MASK_SHIFT;
  ERTC_StampDateStruct->Day     = (TSR1 & ERTC_DAY_MASK)     >> ERTC_DAY_MASK_SHIFT;
  ERTC_StampDateStruct->WeekDay = (TSR2 & ERTC_WEEKDAY_MASK) >> ERTC_WEEKDAY_MASK_SHIFT;
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC TimeStamp value and masks.(binary format)
 * @param  ERTC_StampTimeStruct: pointer to a ERTC_TimeTypeDef structure that will
 *         contains the TimeStamp time values.
 * @param  ERTC_StampDateStruct: pointer to a ERTC_DateTypeDef structure that will
 *         contains the TimeStamp date values.
 * @retval None
 ************************************************************************************************************/
void ERTC_GetTimeStamp(ERTC_DateTypeDef* ERTC_StampDateStruct, ERTC_TimeTypeDef* ERTC_StampTimeStruct)
{
  ERTC_GetTimeStampBCD(ERTC_StampDateStruct, ERTC_StampTimeStruct);;

  ERTC_StampTimeStruct->Hours   = _ERTC_BcdToByte(ERTC_StampTimeStruct->Hours);
  ERTC_StampTimeStruct->Minutes = _ERTC_BcdToByte(ERTC_StampTimeStruct->Minutes);
  ERTC_StampTimeStruct->Seconds = _ERTC_BcdToByte(ERTC_StampTimeStruct->Seconds);

  ERTC_StampDateStruct->Month   = _ERTC_BcdToByte(ERTC_StampDateStruct->Month);
  ERTC_StampDateStruct->Day     = _ERTC_BcdToByte(ERTC_StampDateStruct->Day);
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC timestamp Subseconds value.
 * @retval ERTC current timestamp Subseconds value.
 ************************************************************************************************************/
u32 ERTC_GetTimeStampSubSecond(void)
{
  u16 spsc = HT_ERTC->SPSC;
  return ((spsc & 0x7FFF) - HT_ERTC->TSSSR);
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC timestamp Subseconds value in milliseconds.
 * @note   Calculates how many milliseconds per tick, then converts the elapsed ticks to milliseconds.
 * @retval ERTC current Calendar Subseconds value in milliseconds.
 ************************************************************************************************************/
u32 ERTC_GetTimeStampSubSecondms(void)
{
  /* Compute and cache the conversion factor if not already calculated                                      */
  if (gERTCSubSecondms == 0)
  {
    gERTCSubSecondms = (1000 << 20) / ((HT_ERTC->SPSC & 0x7FFF) + 1);
  }

  /* Elapsed ticks * milliseconds per tick = elapsed milliseconds                                           */
  return ((ERTC_GetTimeStampSubSecond() * gERTCSubSecondms) >> 20);
}

/*********************************************************************************************************//**
 * @brief  Get the ERTC timestamp Subseconds value in microseconds.
 * @note   Calculates how many microseconds per tick, then converts the elapsed ticks to microseconds.
 * @retval ERTC current Calendar Subseconds value in microseconds.
 ************************************************************************************************************/
u32 ERTC_GetTimeStampSubSecondus(void)
{
  /* Compute and cache the conversion factor if not already calculated                                      */
  if (gERTCSubSecondus == 0)
  {
    gERTCSubSecondus = 1000000 << 10 / ((HT_ERTC->SPSC & 0x7FFF) + 1);
  }

  /* Elapsed ticks * microseconds per tick = elapsed microseconds                                           */
  return ((ERTC_GetTimeStampSubSecond() * gERTCSubSecondus) >> 10);
}

/*********************************************************************************************************//**
 * @brief  Checks whether the specified ERTC Timestamp event source is set or not.
 * @param  ERTC_TS_EVT: specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ERTC_TS_WAKEUP0_EVT
 *     @arg ERTC_TS_WAKEUP1_EVT
 * @retval The new state of ERTC_TS_EVT (SET or RESET).
 ************************************************************************************************************/
FlagStatus ERTC_GetTimestampEventSourceStatus(u32 ERTC_TS_EVT)
{
  Assert_Param(IS_ERTC_TS_EVT(ERTC_TS_EVT));
  if((HT_ERTC->SR & 0xC000) == ERTC_TS_EVT)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief  Configures the Synchronization Shift Control Settings.
 * @note   When REFCKON is set, firmware must not write to Shift control register
 * @param  ERTC_ShiftSign : Select to add or substract Second Fractions to the time Calendar.
 *         This parameter can be one of the following values :
 *         @arg ERTC_SHIFT_SIGN_ADD : Add Second Fractions to the clock calendar.
 *         @arg ERTC_SHIFT_SIGN_SUB : Subtract Second Fractions to the clock calendar.
 * @param  ERTC_ShiftSubFS: Select the number of Second Fractions to Substitute.
 *         This parameter can be one any value from 0 to 0x7FFF.
 * @retval An ErrorStatus enumeration value:
 *         - SUCCESS: ERTC Shift registers are configured
 *         - ERROR: ERTC Shift registers are not configured
 ************************************************************************************************************/
void ERTC_SynchroShiftConfig(u8 ERTC_ShiftSign, u16 ERTC_ShiftSubFS)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_ERTC_SHIFT_SIGN(ERTC_ShiftSign));

  /* Disable the write protection for  ERTC registers                                                       */
  HT_ERTC->WPR = gERTCUnProtectKey;

  /* Wait until the shift is completed                                                                      */
  while (((HT_ERTC->SR & ERTC_FLAG_SHPF) != RESET));

  /* Configure the Shift settings                                                                           */
  if(ERTC_ShiftSign == ERTC_SHIFT_SIGN_ADD)
  {
    HT_ERTC->SHIFTCR = ERTC_ShiftSubFS;
  }
  else
  {
    HT_ERTC->SHIFTCR = ~ERTC_ShiftSubFS + 1; //2's compliment
  }

  /* Enable the write protection for ERTC registers                                                         */
  HT_ERTC->WPR = 0xFFFF;
}

/*********************************************************************************************************//**
 * @brief  Set the unprotect key.
 * @param  uUnProtectKey: protect key, shall be ERTC_UNPROTECT_KEY
 * @retval None
 ************************************************************************************************************/
void ERTC_SetUnProtectKey(u16 uUnProtectKey)
{
  gERTCUnProtectKey = uUnProtectKey;
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
