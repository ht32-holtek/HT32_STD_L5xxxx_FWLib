/*********************************************************************************************************//**
 * @file    ADC/OneShot_TMTrigger_PDMA/ht32_board_config.h
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
#if (LIBCFG_PDMA)
#else
  #error "This example code does not apply to the chip you selected."
#endif

  #define HTCFG_ADC_IPN                           ADC0

#if defined(USE_HT32L52241_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       8

  #define _HTCFG_LED_GPIOX                        B
  #define _HTCFG_LED_GPION                        6
  #define  HTCFG_LED_TM_IPN                       GPTM0
  #define  HTCFG_LED_TM_CHN                       3
#endif

#if defined(USE_HT32L52353_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6

  #define _HTCFG_LED_GPIOX                        C
  #define _HTCFG_LED_GPION                        14
  #define  HTCFG_LED_TM_IPN                       MCTM0
  #define  HTCFG_LED_TM_CHN                       3
#endif

#define HTCFG_VR_GPIO_ID                          STRCAT2(GPIO_P,         _HTCFG_VR_GPIOX)
#define HTCFG_VR_AFIO_PIN                         STRCAT2(AFIO_PIN_,      _HTCFG_VR_GPION)
#define HTCFG_VR_AFIO_MODE                        STRCAT2(AFIO_FUN_,       HTCFG_ADC_IPN)
#define HTCFG_VR_ADC_CH                           STRCAT2(ADC_CH_,        _HTCFG_VR_ADC_CHN)
#define HTCFG_ADC_PORT                            STRCAT2(HT_,             HTCFG_ADC_IPN)
#define HTCFG_ADC_CKCU_ADCPRE                     STRCAT2(CKCU_ADCPRE_,    HTCFG_ADC_IPN)

#define HTCFG_LED_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_LED_GPIOX)
#define HTCFG_LED_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_LED_GPION)
#define HTCFG_LED_AFIO_FUN                        STRCAT2(AFIO_FUN_,       HTCFG_LED_TM_IPN)
#define HTCFG_LED_TM_PORT                         STRCAT2(HT_,             HTCFG_LED_TM_IPN)
#define HTCFG_LED_TM_CH                           STRCAT2(TM_CH_,          HTCFG_LED_TM_CHN)
#define HTCFG_ADC_TRIG_TM                         STRCAT3(ADC_TRIG_,       HTCFG_LED_TM_IPN, _MTO)

#define HTCFG_DMA_PORT                            STRCAT2(PDMA_,          HTCFG_ADC_IPN)


#ifdef __cplusplus
}
#endif

#endif
