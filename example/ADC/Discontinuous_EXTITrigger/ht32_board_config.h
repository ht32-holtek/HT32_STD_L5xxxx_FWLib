/*********************************************************************************************************//**
 * @file    ADC/Discontinuous_EXTITrigger/ht32_board_config.h
 * @version $Rev:: 1008         $
 * @date    $Date:: 2025-08-28 #$
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
#define HTCFG_ADC_IPN                           ADC0

#if defined(USE_HT32L52241_SK)
  #define _HTCFG_KEY1_GPIOX                       C
  #define _HTCFG_KEY1_GPION                       2

  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       8

  #define _HTCFG_AD2_GPIOX                        A
  #define _HTCFG_AD2_GPION                        0
  #define _HTCFG_AD2_ADC_CHN                      2

  #define _HTCFG_AD3_GPIOX                        A
  #define _HTCFG_AD3_GPION                        1
  #define _HTCFG_AD3_ADC_CHN                      3
#endif

#if defined(USE_HT32L52353_SK)
  #define _HTCFG_KEY1_GPIOX                       B
  #define _HTCFG_KEY1_GPION                       7

  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6

  #define _HTCFG_AD2_GPIOX                        A
  #define _HTCFG_AD2_GPION                        0
  #define _HTCFG_AD2_ADC_CHN                      0

  #define _HTCFG_AD3_GPIOX                        A
  #define _HTCFG_AD3_GPION                        1
  #define _HTCFG_AD3_ADC_CHN                      1
#endif

#define HTCFG_VR_GPIO_ID                          STRCAT2(GPIO_P,         _HTCFG_VR_GPIOX)
#define HTCFG_VR_AFIO_PIN                         STRCAT2(AFIO_PIN_,      _HTCFG_VR_GPION)
#define HTCFG_VR_ADC_CH                           STRCAT2(ADC_CH_,        _HTCFG_VR_ADC_CHN)

#define HTCFG_AD2_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_AD2_GPIOX)
#define HTCFG_AD2_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_AD2_GPION)
#define HTCFG_AD2_ADC_CH                          STRCAT2(ADC_CH_,        _HTCFG_AD2_ADC_CHN)

#define HTCFG_AD3_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_AD3_GPIOX)
#define HTCFG_AD3_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_AD3_GPION)
#define HTCFG_AD3_ADC_CH                          STRCAT2(ADC_CH_,        _HTCFG_AD3_ADC_CHN)

#define HTCFG_ADC_PORT                            STRCAT2(HT_,            HTCFG_ADC_IPN)
#define HTCFG_ADC_AFIO_MODE                       STRCAT2(AFIO_FUN_,      HTCFG_ADC_IPN)
#define HTCFG_ADC_CKCU_ADCPRE                     STRCAT2(CKCU_ADCPRE_,   HTCFG_ADC_IPN)
#define HTCFG_ADC_IRQn                            STRCAT2(HTCFG_ADC_IPN, _IRQn)

#define HTCFG_ADC_IRQHandler                      ADC_IRQHandler

#define HTCFG_ADC_TRIG_EXTI                       STRCAT2(ADC_TRIG_EXTI_, _HTCFG_KEY1_GPION)

#define HTCFG_KEY1_GPIO_CK                        STRCAT2(P,              _HTCFG_KEY1_GPIOX)
#define HTCFG_KEY1_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_KEY1_GPIOX)
#define HTCFG_KEY1_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_KEY1_GPION)
#define HTCFG_KEY1_GPIO_PORT                      STRCAT2(HT_GPIO,        _HTCFG_KEY1_GPIOX)
#define HTCFG_KEY1_GPIO_PIN                       STRCAT2(GPIO_PIN_,      _HTCFG_KEY1_GPION)
#define HTCFG_KEY1_AFIO_EXTI_CH                   STRCAT2(AFIO_EXTI_CH_,  _HTCFG_KEY1_GPION)
#define HTCFG_KEY1_AFIO_ESS                       STRCAT2(AFIO_ESS_P,     _HTCFG_KEY1_GPIOX)
#define HTCFG_KEY1_EXTI_CH                        STRCAT2(EXTI_CHANNEL_,  _HTCFG_KEY1_GPION)


#ifdef __cplusplus
}
#endif

#endif
