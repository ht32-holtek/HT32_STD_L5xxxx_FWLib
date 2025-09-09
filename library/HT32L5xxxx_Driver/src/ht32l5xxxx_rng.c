/*********************************************************************************************************//**
 * @file    ht32l5xxxx_rng.c
 * @version $Rev:: 1073         $
 * @date    $Date:: 2025-09-08 #$
 * @brief   This file provides all the Random Number Generator firmware functions.
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
#include "ht32l5xxxx_rng.h"

/** @addtogroup HT32L5xxxx_Peripheral_Driver HT32L5xxxx Peripheral Driver
  * @{
  */

/** @defgroup RNG RNG
  * @brief RNG driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup RNG_Private_Define RNG private definitions
  * @{
  */
#define CR_BYPASSAUCOTEST                       ((u32)0x00000400)

/* RNG enable mask                                                                                          */
#define CR_ENRNG_SET                            ((u32)0x00000001)
#define CR_ENRNG_RESET                          ((u32)0xFFFFFFFE)

#define IS_RNG(RNG)                             (RNG == HT_RNG)
#define IS_RNG_FLAG(FLAG)                       ((((FLAG) & 0xFFFFFFFE) == 0) && ((FLAG) != 0))
#define IS_RNG_INT(INT)                         ((((INT) & 0xFFFFFFFE) == 0) && ((INT) != 0))

/**
  * @}
  */

/* Private variables ---------------------------------------------------------------------------------------*/
static bool _RNG_Active = FALSE;

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup RNG_Exported_Functions RNG exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Initialize the RNG peripheral according to the specified parameters in the RNG_InitStruct.
 * @param HT_RNGn: Selected RNG peripheral.
 * @param RNG_InitStruct: pointer to a RNG_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void RNG_Init(HT_RNG_TypeDef* HT_RNGn, RNG_InitTypeDef RNG_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));

  HT_RNGn->CR    = (CR_BYPASSAUCOTEST   | \
                    RNG_InitStruct.invlen);
  HT_RNGn->OBIT  = RNG_InitStruct.cycnum;
}

/*********************************************************************************************************//**
 * @brief Deinitializes the RNG peripheral registers to their default reset values.
 * @param HT_RNGn: where RNG is the selected RNG from the RNG peripherals.
 * @retval None
 ************************************************************************************************************/
void RNG_DeInit(HT_RNG_TypeDef* HT_RNGn)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));

  if(HT_RNGn == HT_RNG)
  {
    RSTCUReset.Bit.RNG = 1;
  }
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the RNG timer.
 * @param HT_RNGn: where RNG is the selected RNG from the RNG peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RNG_Cmd(HT_RNG_TypeDef* HT_RNGn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    _RNG_Active = TRUE;
  }
  else
  {
    HT_RNGn->CR &= CR_ENRNG_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Generate the random number
 * @param HT_RNGn: where HT_RNGn is the selected RNG from the RNG peripherals.
 * @retval None
 ************************************************************************************************************/
void RNG_GenerateRandomNumber(HT_RNG_TypeDef* HT_RNGn)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));

  HT_RNGn->IER |= RNG_INT_VALID;
  if(_RNG_Active == TRUE)
  {
   _RNG_Active = FALSE;
   HT_RNGn->CR |= CR_ENRNG_SET;
  }
}

/*********************************************************************************************************//**
 * @brief Get the random number
 * @param HT_RNGn: where HT_RNGn is the selected RNG from the RNG peripherals.
 * @param randomNumber: Pointer to a structure that will store the random number.
 *        The result will be filled into both randomWord[6] (as 6x 32-bit words)
 *        and randomByte[24] (as 24 bytes) via a union.
 * @retval None
 ************************************************************************************************************/
void RNG_GetRandomNumber(HT_RNG_TypeDef* HT_RNGn, RNG_randomNumber* randomNumber)
{
  u8 i;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));

  HT_RNGn->IER &= (u32)~RNG_INT_VALID;
  for( i=0; i<6; i++)
  {
    randomNumber->randomWord[i] = *(&HT_RNG->DR0 + (i*1));
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable RNG interrupts.
 * @param HT_RNGn: where HT_RNGn is the selected RNG from the RNG peripherals.
 * @param RNG_Int: specify if the RNG interrupt source to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg RNG_INT_VALID
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void RNG_IntConfig(HT_RNG_TypeDef* HT_RNGn, u32 RNG_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));
  Assert_Param(IS_RNG_INT(RNG_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_RNGn->IER |= RNG_Int;
  }
   else
  {
    HT_RNGn->IER &= (u32)~RNG_Int;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the RNG Flag has occurred.
 * @param HT_RNGn: where RNG is the selected RNG from the RNG peripherals.
 * @param RNG_Flag: Specify the RNG interrupt source to be checked.
 *        This parameter can be one of the following values:
 *        @arg RNG_FLAG_VALID
 * @retval The new state of the RNG_Int(SET or RESET)
 ************************************************************************************************************/
FlagStatus RNG_GetFlagStatus(HT_RNG_TypeDef* HT_RNGn, u32 RNG_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));
  Assert_Param(IS_RNG_FLAG(RNG_Flag));

  if(HT_RNGn->ISR & RNG_Flag)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the RNG interrupt flag.
 * @param HT_RNGn: where RNG is the selected RNG from the RNG peripherals.
 * @param RNG_Flag: specify the RNG interrupt flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg RNG_FLAG_VALID
 * @retval None
 ************************************************************************************************************/
void RNG_ClearFlagStatus(HT_RNG_TypeDef* HT_RNGn, u32 RNG_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_RNG(HT_RNGn));
  Assert_Param(IS_RNG_FLAG(RNG_Flag));

  HT_RNGn->ISR |= RNG_FLAG_VALID;
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
