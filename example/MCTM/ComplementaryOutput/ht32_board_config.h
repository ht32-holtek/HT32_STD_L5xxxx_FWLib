/*********************************************************************************************************//**
 * @file    MCTM/ComplementaryOutput/ht32_board_config.h
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
#if defined(USE_HT32L52241_SK)
  #define  HTCFG_MCTM_CH0_GPIO_ID                      (GPIO_PA)
  #define  HTCFG_MCTM_CH0N_GPIO_ID                     (GPIO_PA)
  #define  HTCFG_MCTM_CH1_GPIO_ID                      (GPIO_PB)
  #define  HTCFG_MCTM_CH1N_GPIO_ID                     (GPIO_PB)
  #define  HTCFG_MCTM_CH2_GPIO_ID                      (GPIO_PB)
  #define  HTCFG_MCTM_CH2N_GPIO_ID                     (GPIO_PB)
  #define _HTCFG_MCTM_BREAK_GPIOX                      B

  #define  HTCFG_MCTM_CH0_AFIO_PIN                     (AFIO_PIN_14)
  #define  HTCFG_MCTM_CH0N_AFIO_PIN                    (AFIO_PIN_15)
  #define  HTCFG_MCTM_CH1_AFIO_PIN                     (AFIO_PIN_0)
  #define  HTCFG_MCTM_CH1N_AFIO_PIN                    (AFIO_PIN_1)
  #define  HTCFG_MCTM_CH2_AFIO_PIN                     (AFIO_PIN_2)
  #define  HTCFG_MCTM_CH2N_AFIO_PIN                    (AFIO_PIN_3)
  #define  HTCFG_MCTM_BREAK_AFIO_PIN                   (AFIO_PIN_4)

  #define  HTCFG_MCTM_RELOAD                           (48000000/2000)
  #define  HTCFG_MCTM_DEAD_TIME                        (72)
#endif

#if defined(USE_HT32L52353_SK)
  #define  HTCFG_MCTM_CH0_GPIO_ID                      (GPIO_PA)
  #define  HTCFG_MCTM_CH0N_GPIO_ID                     (GPIO_PA)
  #define  HTCFG_MCTM_CH1_GPIO_ID                      (GPIO_PB)
  #define  HTCFG_MCTM_CH1N_GPIO_ID                     (GPIO_PB)
  #define  HTCFG_MCTM_CH2_GPIO_ID                      (GPIO_PB)
  #define  HTCFG_MCTM_CH2N_GPIO_ID                     (GPIO_PB)
  #define _HTCFG_MCTM_BREAK_GPIOX                      B

  #define  HTCFG_MCTM_CH0_AFIO_PIN                     (AFIO_PIN_14)
  #define  HTCFG_MCTM_CH0N_AFIO_PIN                    (AFIO_PIN_15)
  #define  HTCFG_MCTM_CH1_AFIO_PIN                     (AFIO_PIN_0)
  #define  HTCFG_MCTM_CH1N_AFIO_PIN                    (AFIO_PIN_1)
  #define  HTCFG_MCTM_CH2_AFIO_PIN                     (AFIO_PIN_2)
  #define  HTCFG_MCTM_CH2N_AFIO_PIN                    (AFIO_PIN_3)
  #define  HTCFG_MCTM_BREAK_AFIO_PIN                   (AFIO_PIN_4)

  #define  HTCFG_MCTM_RELOAD                           (48000000/2000)
  #define  HTCFG_MCTM_DEAD_TIME                        (72)
#endif

#define  HTCFG_MCTM_BREAK_GPIO_ID                      STRCAT2(GPIO_P,    _HTCFG_MCTM_BREAK_GPIOX)
#define  HTCFG_MCTM_BREAK_GPIO_PORT                    STRCAT2(HT_GPIO,   _HTCFG_MCTM_BREAK_GPIOX)
#define  HTCFG_MCTM_BREAK_GPIO_CLOCK_ID                STRCAT2(P,         _HTCFG_MCTM_BREAK_GPIOX)

#ifdef __cplusplus
}
#endif

#endif
