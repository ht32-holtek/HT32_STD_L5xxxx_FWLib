/*********************************************************************************************************//**
 * @file    ht32l5xxxx_rng.h
 * @version $Rev:: 1067         $
 * @date    $Date:: 2025-09-05 #$
 * @brief   The header file of the RNG library.
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

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32L5XXXX_RNG_H
#define __HT32L5XXXX_RNG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32L5xxxx_Peripheral_Driver HT32L5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup RNG
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup RNG_Exported_Types RNG exported types
  * @{
  */
/**
 * @brief  Definition of RNG Init Structure
 */
typedef struct
{
  u32 invlen;
  u32 cycnum;
} RNG_InitTypeDef;

/**
 * @brief  Data structure for storing and accessing a 192-bit random number as an array of bytes or words.
 */
typedef struct
{
  union{
    u8  randomByte[24];
    u32 randomWord[6];
  };
} RNG_randomNumber;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup RNG_Exported_Constants RNG exported constants
  * @{
  */
#define RNG_INVLEN_SHORTEST                     0x00000000
#define RNG_INVLEN_SHORT                        0x00000002
#define RNG_INVLEN_LONG                         0x00000004
#define RNG_INVLEN_LONGEST                      0x00000006

#define RNG_INVLEN                              RNG_INVLEN_LONG
#define RNG_CYCNUM                              0x0000015E

#define RNG_FLAG_VALID                          (0x00000001)
#define RNG_INT_VALID                           (0x00000001)
#define RNG_FLAG_AUCO                           (0x00000002)
#define RNG_INT_AUCO                            (0x00000002)
#define RNG_FLAG_CRNGT                          (0x00000004)
#define RNG_INT_CRNGT                           (0x00000004)
#define RNG_FLAG_VNE                            (0x00000008)
#define RNG_INT_VNE                             (0x00000008)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup RNG_Exported_Functions RNG exported functions
  * @{
  */
void RNG_Init(HT_RNG_TypeDef* HT_RNGn, RNG_InitTypeDef RNG_InitStruct);
void RNG_DeInit(HT_RNG_TypeDef* HT_RNGn);
void RNG_Cmd(HT_RNG_TypeDef* HT_RNGn, ControlStatus NewState);
void RNG_GenerateRandomNumber(HT_RNG_TypeDef* HT_RNGn);
void RNG_GetRandomNumber(HT_RNG_TypeDef* HT_RNGn, RNG_randomNumber* randomNumber);
void RNG_IntConfig(HT_RNG_TypeDef* HT_RNGn, u32 RNG_Flag, ControlStatus NewState);
FlagStatus RNG_GetFlagStatus(HT_RNG_TypeDef* HT_RNGn, u32 RNG_Flag);
void RNG_ClearFlagStatus(HT_RNG_TypeDef* HT_RNGn, u32 RNG_Flag);


/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
