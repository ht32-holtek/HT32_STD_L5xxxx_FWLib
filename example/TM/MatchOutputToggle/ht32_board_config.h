/*********************************************************************************************************//**
 * @file    TM/MatchOutputToggle/ht32_board_config.h
 * @version $Rev:: 283          $
 * @date    $Date:: 2024-02-29 #$
 * @brief   The header file of board configuration.
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
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#define HTCFG_TM_PRESCALER 2000

#if defined(USE_HT32L52241_SK)
  #define _HTCFG_COMP_CH0_GPIOX                   A
  #define _HTCFG_COMP_CH1_GPIOX                   A
  #define _HTCFG_COMP_CH2_GPIOX                   A
  #define _HTCFG_COMP_CH3_GPIOX                   A
  #define _HTCFG_COMP_CH0_GPION                   0
  #define _HTCFG_COMP_CH1_GPION                   1
  #define _HTCFG_COMP_CH2_GPION                   2
  #define _HTCFG_COMP_CH3_GPION                   3

  #define HTCFG_COMP_IPN                          GPTM0
#endif

#define HTCFG_COMP_CH0_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_COMP_CH0_GPIOX)
#define HTCFG_COMP_CH1_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_COMP_CH1_GPIOX)
#define HTCFG_COMP_CH2_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_COMP_CH2_GPIOX)
#define HTCFG_COMP_CH3_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_COMP_CH3_GPIOX)

#define HTCFG_COMP_CH0_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_COMP_CH0_GPION)
#define HTCFG_COMP_CH1_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_COMP_CH1_GPION)
#define HTCFG_COMP_CH2_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_COMP_CH2_GPION)
#define HTCFG_COMP_CH3_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_COMP_CH3_GPION)

#define HTCFG_COMP_PORT                           STRCAT2(HT_,             HTCFG_COMP_IPN)
#define HTCFG_COMP_AFIO_FUN                       STRCAT2(AFIO_FUN_,       HTCFG_COMP_IPN)

#define HTCFG_COMP_IRQn                           STRCAT2(HTCFG_COMP_IPN,  _IRQn)
#define HTCFG_COMP_IRQHandler                     STRCAT2(HTCFG_COMP_IPN,  _IRQHandler)



#ifdef __cplusplus
}
#endif

#endif
