/*********************************************************************************************************//**
 * @file    TM/PWMOut_PDMA/ht32_board_config.h
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


/* Settings ------------------------------------------------------------------------------------------------*/
#if (LIBCFG_PDMA == 0)
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32L52241_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       0
  #define _HTCFG_PWM0_CHN                         0

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#define HTCFG_PWM_PORT                            STRCAT2(HT_,             HTCFG_PWM_IPN)
#define HTCFG_PWM0_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_PWM0_GPIOX)
#define HTCFG_PWM0_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_PWM0_GPION)
#define HTCFG_PWM0_AFIO_FUN                       STRCAT2(AFIO_FUN_,       HTCFG_PWM_IPN)
#define HTCFG_PWM0_CH                             STRCAT2(TM_CH_,         _HTCFG_PWM0_CHN)


#ifdef __cplusplus
}
#endif

#endif
