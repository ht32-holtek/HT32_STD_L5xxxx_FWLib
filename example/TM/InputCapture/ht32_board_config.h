/*********************************************************************************************************//**
 * @file    TM/InputCapture/ht32_board_config.h
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
#define HTCFG_PWM_TM_PCLK 4000   // Timer clock = 4 kHz

#if defined(USE_HT32L52241_SK)
  #define _HTCFG_CAP_GPIOX                        C
  #define _HTCFG_CAP_GPION                        5
  #define  HTCFG_CAP_IPN                          GPTM0
  #define _HTCFG_CAP_CHN                          1
  #define  HTCFG_CAP_CCR                          (TM_INT_CH1CC)

  #define _HTCFG_PWM_GPIOX                        C
  #define _HTCFG_PWM_GPION                        4
  #define  HTCFG_PWM_IPN                          SCTM0
  #define _HTCFG_PWM_CHN                          0
#endif

#define HTCFG_CAP_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_CAP_GPIOX)
#define HTCFG_CAP_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_CAP_GPION)
#define HTCFG_CAP_PORT                            STRCAT2(HT_,             HTCFG_CAP_IPN)
#define HTCFG_CAP_CH                              STRCAT2(TM_CH_,         _HTCFG_CAP_CHN)
#define HTCFG_CAP_AFIO_FUN                        STRCAT2(AFIO_FUN_,       HTCFG_CAP_IPN)

#define HTCFG_CAP_IRQn                            STRCAT2(HTCFG_CAP_IPN,  _IRQn)
#define HTCFG_CAP_IRQHandler                      STRCAT2(HTCFG_CAP_IPN,  _IRQHandler)

#define HTCFG_PWM_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_PWM_GPIOX)
#define HTCFG_PWM_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_PWM_GPION)
#define HTCFG_PWM_AFIO_FUN                        STRCAT2(AFIO_FUN_,       HTCFG_PWM_IPN)
#define HTCFG_PWM_PORT                            STRCAT2(HT_,             HTCFG_PWM_IPN)
#define HTCFG_PWM_CH                              STRCAT2(TM_CH_,         _HTCFG_PWM_CHN)

#ifdef __cplusplus
}
#endif

#endif
