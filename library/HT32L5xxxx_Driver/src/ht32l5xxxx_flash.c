/*********************************************************************************************************//**
 * @file    ht32l5xxxx_flash.c
 * @version $Rev:: 449          $
 * @date    $Date:: 2024-07-09 #$
 * @brief   This file provides all the FLASH firmware functions.
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
#include "ht32l5xxxx_flash.h"

/** @addtogroup HT32L5xxxx_Peripheral_Driver HT32L5xxxx Peripheral Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Define FLASH private definitions
  * @{
  */

/* Delay definition                                                                                         */
#define FLASH_TIMEOUT                 (0x000FFFFF)

/* FLASH OCMR                                                                                               */
#define FLASH_CMD_STADNBY             (0x00000000)
#define FLASH_CMD_PROGRAM             (0x00000004)
#define FLASH_CMD_PAGEERASE           (0x00000008)
#define FLASH_CMD_MASSERASE           (0x0000000A)

/* FLASH OPCR                                                                                               */
#define FLASH_READY                   (0x6UL << 1)
#define FLASH_SEND_MAIN               (0x00000014)

/* FLASH WSCR                                                                                               */
#define WSCR_WAIT_MASK                (0xFFFFFFF0)

#define FLASH_CACHE_ON                (0x00000001)
#define FLASH_CACHE_OFF               (0xFFFFFFFE)

#define FLASH_EATF_ON                 (0x1UL << 8)
#define FLASH_EATF_OFF                (~(0x1UL << 8))

/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macro FLASH private macros
  * @{
  */

/**
 * @brief Check parameter of the FLASH wait state.
 */
#if (LIBCFG_FMC_WAIT_STATE_2)
#define IS_WAIT_STATE2(x)   (x == FLASH_WAITSTATE_2)
#else
#define IS_WAIT_STATE2(x)   (0)
#endif

#define IS_FLASH_WAITSTATE(WAIT)      ((WAIT == FLASH_WAITSTATE_0) || \
                                       (WAIT == FLASH_WAITSTATE_1) || \
                                       (IS_WAIT_STATE2(WAIT)))
/**
 * @brief Check parameter of the FLASH vector mapping.
 */
#define IS_FLASH_VECTOR_MODE(MODE)    ((MODE == FLASH_BOOT_LOADER) || \
                                       (MODE == FLASH_BOOT_MAIN))
/**
 * @brief Check parameter of the FLASH address.
 */
#define IS_FLASH_ADDRESS(ADDRESS)     (ADDRESS < 0x20000000)  /* Code 0.5GB Area                            */

/**
 * @brief Check parameter of the FLASH interrupt status.
 */
#define IS_FLASH_WC_FLAG(FLAG)        ((FLAG & 0x0000001F) != 0)

/**
 * @brief Check parameter of the FLASH interrupt flag.
 */
#define IS_FLASH_FLAG(FLAG)           ((FLAG & 0x0003001F) != 0)

/**
 * @brief Check parameter of the FLASH interrupt.
 */
#define IS_FLASH_INT(IT)              ((IT & 0x0000001F) != 0)

/**
  * @}
  */

#if (LIBCFG_FMC_CACHE)
__ALIGN4 static u32 CacheData[] =
{
  0x28004908, 0xd0066908, 0x43102201, 0x69486108,
  0xd1fc2812, 0x08404770, 0x61080040, 0x07806948,
  0x4770d1fc, 0x40080200

/*
void pCacheFun(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    HT_FLASH->CCR |= FLASH_CACHE_ON;
    while (HT_FLASH->SR != 0x00000012);
  }
  else
  {
    HT_FLASH->CCR &= FLASH_CACHE_OFF;
    while ((HT_FLASH->SR & 3) != 0);
  }
}
*/
};
#endif

typedef void (*pCacheFun_TypeDef)(ControlStatus);

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Exported_Functions FLASH exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Configure the FLASH wait state.
 * @param FLASH_WAITSTATE_n: Setting of FLASH wait state.
 *   This parameter can be one of the following values:
 *     @arg \ref FLASH_WAITSTATE_0 : zero wait state
 *     @arg \ref FLASH_WAITSTATE_1 : one wait state
 *     @arg \ref FLASH_WAITSTATE_2 : two wait state
 * @retval None
 ************************************************************************************************************/
void FLASH_SetWaitState(u32 FLASH_WAITSTATE_n)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_WAITSTATE(FLASH_WAITSTATE_n));

  HT_FLASH->WSCR = (HT_FLASH->WSCR & WSCR_WAIT_MASK) | FLASH_WAITSTATE_n;
}

#if (LIBCFG_FMC_CACHE)
/*********************************************************************************************************//**
 * @brief Enable or Disable FLASH cache.
 * @param NewState: This parameter can be ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void FLASH_CacheCmd(ControlStatus NewState)
{
  pCacheFun_TypeDef pCacheFun = (pCacheFun_TypeDef)((u32)CacheData | 0x1);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  __disable_irq();

  pCacheFun(NewState);

  __enable_irq();
}
#endif

#if (LIBCFG_FMC_EATF)
/*********************************************************************************************************//**
 * @brief Enable or Disable Execute at Flash setting.
 * @param NewState: This parameter can be ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void FLASH_ExecuteAtCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_FLASH->CCR |= FLASH_EATF_ON;
  }
  else
  {
    HT_FLASH->CCR &= FLASH_EATF_OFF;
  }
}
#endif

/*********************************************************************************************************//**
 * @brief Set vector remapping mode.
 * @param FLASH_BOOT_x: Booting mode.
 *   This parameter can be one of the following values:
 *     @arg \ref FLASH_BOOT_LOADER : Boot loader mode
 *     @arg \ref FLASH_BOOT_MAIN   : Main FLASH mode
 * @retval None
 ************************************************************************************************************/
void FLASH_SetRemappingMode(FLASH_Vector FLASH_BOOT_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_VECTOR_MODE(FLASH_BOOT_x));

  HT_FLASH->VMCR = FLASH_BOOT_x;
}

/*********************************************************************************************************//**
 * @brief Erase a specific FLASH page.
 * @param PageAddress: Address of the erased page.
 * @retval FLASH_State
 *   - \ref FLASH_COMPLETE
 *   - \ref FLASH_TIME_OUT
 *   - \ref FLASH_ERR_WRITE_PROTECTED
 *   - \ref FLASH_ERR_ADDR_OUT_OF_RANGE
 * @note  HSI must keep turn on when doing the Flash operation (Erase/Program).
 ************************************************************************************************************/
FLASH_State FLASH_ErasePage(u32 PageAddress)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_ADDRESS(PageAddress));

  HT_FLASH->TADR = PageAddress;
  HT_FLASH->OCMR = FLASH_CMD_PAGEERASE;

  return FLASH_WaitForOperationEnd();
}

/*********************************************************************************************************//**
 * @brief Erase FLASH Option Byte page.
 * @retval FLASH_State
 *   - \ref FLASH_COMPLETE
 *   - \ref FLASH_TIME_OUT
 *   - \ref FLASH_ERR_WRITE_PROTECTED
 * @note  HSI must keep turn on when doing the Flash operation (Erase/Program).
 ************************************************************************************************************/
FLASH_State FLASH_EraseOptionByte(void)
{
  return FLASH_ErasePage(OPTION_BYTE_BASE);
}

/*********************************************************************************************************//**
 * @brief Erase the entire FLASH.
 * @retval FLASH_State
 *   - \ref FLASH_COMPLETE
 *   - \ref FLASH_TIME_OUT
 * @note  HSI must keep turn on when doing the Flash operation (Erase/Program).
 ************************************************************************************************************/
FLASH_State FLASH_MassErase(void)
{
  HT_FLASH->OCMR = FLASH_CMD_MASSERASE;

  return FLASH_WaitForOperationEnd();
}

/*********************************************************************************************************//**
 * @brief Program one word data.
 * @param Address: The specific FLASH address to be programmed.
 * @param Data: The specific FLASH data to be programmed.
 * @retval FLASH_State
 *   - \ref FLASH_COMPLETE
 *   - \ref FLASH_TIME_OUT
 *   - \ref FLASH_ERR_WRITE_PROTECTED
 *   - \ref FLASH_ERR_ADDR_OUT_OF_RANGE
 * @note  HSI must keep turn on when doing the Flash operation (Erase/Program).
 ************************************************************************************************************/
FLASH_State FLASH_ProgramWordData(u32 Address, u32 Data)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_ADDRESS(Address));

  HT_FLASH->TADR = Address;
  HT_FLASH->WRDR = Data;
  HT_FLASH->OCMR = FLASH_CMD_PROGRAM;

  return FLASH_WaitForOperationEnd();
}

/*********************************************************************************************************//**
 * @brief Program FLASH Option Byte page.
 * @param Option: Struct pointer of Option Bytes.
 * @retval FLASH_State
 *   - \ref FLASH_COMPLETE
 * @note  HSI must keep turn on when doing the Flash operation (Erase/Program).
 ************************************************************************************************************/
FLASH_State FLASH_ProgramOptionByte(FLASH_OptionByte *Option)
{
  s32 i;
  u32 CP = ~(Option->MainSecurity | Option->OptionProtect << 1);
  u32 checksum = 0;

  for (i = 3; i >= 0; i--)
  {
    FLASH_ProgramWordData(OB_PP0 + i * 4, ~(Option->WriteProtect[i]));
    checksum += ~(Option->WriteProtect[i]);
  }

  FLASH_ProgramWordData(OB_CP, CP);
  checksum += CP;

  FLASH_ProgramWordData(OB_CHECKSUM, checksum);

  return FLASH_COMPLETE;
}

/*********************************************************************************************************//**
 * @brief Return security status of the FLASH.
 * @param Option: Struct pointer of Option Bytes.
 * @retval None
 ************************************************************************************************************/
void FLASH_GetOptionByteStatus(FLASH_OptionByte *Option)
{
  s32 i;

  for (i = 3; i >= 0; i--)
  {
    Option->WriteProtect[i] = ~HT_FLASH->PPSR[i];
  }

  Option->MainSecurity = !(HT_FLASH->CPSR & 1);
  Option->OptionProtect = !((HT_FLASH->CPSR >> 1) & 1);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specific FLASH interrupts.
 * @param FLASH_INT_x: The specific FLASH interrupt.
 *   This parameter can be any combination (|) of the following values:
 *     @arg \ref FLASH_INT_ORFIEN
 *     @arg \ref FLASH_INT_ITADIEN
 *     @arg \ref FLASH_INT_OBEIEN
 *     @arg \ref FLASH_INT_IOCMIEN
 *     @arg \ref FLASH_INT_OREIEN
 *     @arg \ref FLASH_INT_ALL
 * @param Cmd: This parameter can be ENABLE or DISABLE
 * @retval None
 ************************************************************************************************************/
void FLASH_IntConfig(u32 FLASH_INT_x, ControlStatus Cmd)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_INT(FLASH_INT_x));
  Assert_Param(IS_CONTROL_STATUS(Cmd));

  if (Cmd != DISABLE)
  {
    HT_FLASH->OIER |= FLASH_INT_x;
  }
  else
  {
    HT_FLASH->OIER &= ~FLASH_INT_x;
  }
}

/*********************************************************************************************************//**
 * @brief Return flag status of the FLASH interrupt.
 * @param FLASH_FLAG_x: Flag of the FLASH interrupt.
 *   This parameter can be any combination (|) of the following values:
 *     @arg \ref FLASH_FLAG_OREF
 *     @arg \ref FLASH_FLAG_IOCMF
 *     @arg \ref FLASH_FLAG_OBEF
 *     @arg \ref FLASH_FLAG_ITADF
 *     @arg \ref FLASH_FLAG_ORFF
 *     @arg \ref FLASH_FLAG_PPEF
 *     @arg \ref FLASH_FLAG_RORFF
 * @retval FlagStatus
 *   - \ref SET
 *   - \ref RESET
 ************************************************************************************************************/
FlagStatus FLASH_GetIntStatus(u32 FLASH_FLAG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_FLAG(FLASH_FLAG_x));

  if ((HT_FLASH->OISR & FLASH_FLAG_x) != (u32)RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear specific interrupt flags of FLASH.
 * @param FLASH_FLAG_x: interrupt flag of FLASH.
 *   This parameter can be any combination (|) of the following values:
 *     @arg \ref FLASH_FLAG_OREF
 *     @arg \ref FLASH_FLAG_IOCMF
 *     @arg \ref FLASH_FLAG_OBEF
 *     @arg \ref FLASH_FLAG_ITADF
 *     @arg \ref FLASH_FLAG_ORFF
 * @retval None
 ************************************************************************************************************/
void FLASH_ClearIntFlag(u32 FLASH_FLAG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_FLASH_WC_FLAG(FLASH_FLAG_x));

  HT_FLASH->OISR = FLASH_FLAG_x;
}

/*********************************************************************************************************//**
 * @brief Wait untill the FLASH operation has finished or time-out has occurred.
 * @retval FLASH_State
 *   - \ref FLASH_COMPLETE
 *   - \ref FLASH_TIME_OUT
 *   - \ref FLASH_ERR_WRITE_PROTECTED
 *   - \ref FLASH_ERR_ADDR_OUT_OF_RANGE
 * @note  HSI must keep turn on when doing the Flash operation (Erase/Program).
 ************************************************************************************************************/
FLASH_State FLASH_WaitForOperationEnd(void)
{
  u32 Timeout = FLASH_TIMEOUT;
  u32 Status;
  #if (LIBCFG_FMC_CACHE_FLUSH == 1)
  u32 uCCR;
  pCacheFun_TypeDef pCacheFun = (pCacheFun_TypeDef)((u32)CacheData | 0x1);
  #endif

  #if (LIBCFG_FMC_ISPINT == 1)
  __disable_irq();
  #endif
  HT_FLASH->OIER |= (FLASH_INT_ITADIEN);
  #if (LIBCFG_FMC_CACHE_FLUSH == 1)
  uCCR = HT_FLASH->CCR;
  pCacheFun(DISABLE);
  #endif
  HT_FLASH->OPCR = FLASH_SEND_MAIN;

  /* Waits till the FLASH operation has finished or time-out has occurred                                   */
  while (Timeout--)
  {
    if ((HT_FLASH->OPCR & FLASH_READY) == FLASH_READY)
    {
      break;
    }
  }

  #if (LIBCFG_FMC_CACHE_FLUSH == 1)
  if (uCCR & 0x1)
  {
    pCacheFun(ENABLE);
  }
  #endif
  #if (LIBCFG_FMC_ISPINT == 1)
  __enable_irq();
  #endif

  Status = HT_FLASH->OISR;
  HT_FLASH->OISR &= ~(FLASH_INT_ITADIEN);

  if (Status & FLASH_FLAG_PPEF)
  {
    return FLASH_ERR_WRITE_PROTECTED;
  }
  if (Status & FLASH_FLAG_ITADF)
  {
    return FLASH_ERR_ADDR_OUT_OF_RANGE;
  }
  if (Timeout == 0)
  {
    return FLASH_TIME_OUT;
  }

  return FLASH_COMPLETE;
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
