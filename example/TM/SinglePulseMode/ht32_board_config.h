/*********************************************************************************************************//**
 * @file    TM/SinglePulseMode/ht32_board_config.h
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
#if defined(USE_HT32L52241_SK)
  #define _HTCFG_PULSE_GPIOX                      A
  #define _HTCFG_PULSE_GPION                      0
  #define  HTCFG_PULSE_IPN                        GPTM0
  #define _HTCFG_PULSE_CHN                        0
#endif

#define HTCFG_PLUSE_SYS_CLK                       (LIBCFG_MAX_SPEED) // Calculate with fix value (#define)
//#define HTCFG_PLUSE_SYS_CLK                       (SystemCoreClock)  // Calculate on the fly (variable)

#define HTCFG_PLUSE_FREQ_HZ                       (500)

#define HTCFG_PULSE_GPIO_ID                       STRCAT2(GPIO_P,         _HTCFG_PULSE_GPIOX)
#define HTCFG_PULSE_AFIO_PIN                      STRCAT2(AFIO_PIN_,      _HTCFG_PULSE_GPION)
#define HTCFG_PULSE_AFIO_FUN                      STRCAT2(AFIO_FUN_,       HTCFG_PULSE_IPN)
#define HTCFG_PULSE_PORT                          STRCAT2(HT_,             HTCFG_PULSE_IPN)
#define HTCFG_PULSE_CH                            STRCAT2(TM_CH_,         _HTCFG_PULSE_CHN)


#ifdef __cplusplus
}
#endif

#endif
