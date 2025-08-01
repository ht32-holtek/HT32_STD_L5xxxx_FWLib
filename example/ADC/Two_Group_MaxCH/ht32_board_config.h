/*********************************************************************************************************//**
 * @file    ADC/Two_Group_MaxCH/ht32_board_config.h
 * @version $Rev:: 430          $
 * @date    $Date:: 2024-06-21 #$
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
#if ((LIBCFG_ADC_CH8_11 == 0) && (LIBCFG_ADC_CH8_9 == 0))
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32L52231_41)
  #define LIBCFG_ADC_CH_TYPE                     (0)
#endif

#if defined(USE_HT50L3200U)
  #define LIBCFG_ADC_CH_TYPE                     (0)
#endif

#if (LIBCFG_ADC_CH_TYPE==0)
  #define HTCFG_ADCCH0_GPIOX                      B
  #define HTCFG_ADCCH1_GPIOX                      B
  #define HTCFG_ADCCH2_GPIOX                      A
  #define HTCFG_ADCCH3_GPIOX                      A
  #define HTCFG_ADCCH4_GPIOX                      A
  #define HTCFG_ADCCH5_GPIOX                      A
  #define HTCFG_ADCCH6_GPIOX                      A
  #define HTCFG_ADCCH7_GPIOX                      A
  #define HTCFG_ADCCH8_GPIOX                      A
  #define HTCFG_ADCCH9_GPIOX                      A
  #define HTCFG_ADCCH10_GPIOX                     C
  #define HTCFG_ADCCH11_GPIOX                     C

  #define HTCFG_ADCCH0_AFION                      7
  #define HTCFG_ADCCH1_AFION                      8
  #define HTCFG_ADCCH2_AFION                      0
  #define HTCFG_ADCCH3_AFION                      1
  #define HTCFG_ADCCH4_AFION                      2
  #define HTCFG_ADCCH5_AFION                      3
  #define HTCFG_ADCCH6_AFION                      4
  #define HTCFG_ADCCH7_AFION                      5
  #define HTCFG_ADCCH8_AFION                      6
  #define HTCFG_ADCCH9_AFION                      7
  #define HTCFG_ADCCH10_AFION                     4
  #define HTCFG_ADCCH11_AFION                     5
#endif

#define HTCFG_ADCCH0_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH0_GPIOX)
#define HTCFG_ADCCH1_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH1_GPIOX)
#define HTCFG_ADCCH2_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH2_GPIOX)
#define HTCFG_ADCCH3_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH3_GPIOX)
#define HTCFG_ADCCH4_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH4_GPIOX)
#define HTCFG_ADCCH5_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH5_GPIOX)
#define HTCFG_ADCCH6_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH6_GPIOX)
#define HTCFG_ADCCH7_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH7_GPIOX)
#define HTCFG_ADCCH8_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH8_GPIOX)
#define HTCFG_ADCCH9_GPIO_ID                      STRCAT2(GPIO_P,   HTCFG_ADCCH9_GPIOX)
//#define HTCFG_ADCCH10_GPIO_ID                     STRCAT2(GPIO_P,   HTCFG_ADCCH10_GPIOX)
//#define HTCFG_ADCCH11_GPIO_ID                     STRCAT2(GPIO_P,   HTCFG_ADCCH11_GPIOX)
//#define HTCFG_ADCCH12_GPIO_ID                     STRCAT2(GPIO_P,   HTCFG_ADCCH12_GPIOX)
//#define HTCFG_ADCCH13_GPIO_ID                     STRCAT2(GPIO_P,   HTCFG_ADCCH13_GPIOX)
//#define HTCFG_ADCCH14_GPIO_ID                     STRCAT2(GPIO_P,   HTCFG_ADCCH14_GPIOX)
//#define HTCFG_ADCCH15_GPIO_ID                     STRCAT2(GPIO_P,   HTCFG_ADCCH15_GPIOX)

#define HTCFG_ADCCH0_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH0_AFION)
#define HTCFG_ADCCH1_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH1_AFION)
#define HTCFG_ADCCH2_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH2_AFION)
#define HTCFG_ADCCH3_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH3_AFION)
#define HTCFG_ADCCH4_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH4_AFION)
#define HTCFG_ADCCH5_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH5_AFION)
#define HTCFG_ADCCH6_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH6_AFION)
#define HTCFG_ADCCH7_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH7_AFION)
#define HTCFG_ADCCH8_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH8_AFION)
#define HTCFG_ADCCH9_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_ADCCH9_AFION)
//#define HTCFG_ADCCH10_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_ADCCH10_AFION)
//#define HTCFG_ADCCH11_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_ADCCH11_AFION)
//#define HTCFG_ADCCH12_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_ADCCH12_AFION)
//#define HTCFG_ADCCH13_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_ADCCH13_AFION)
//#define HTCFG_ADCCH14_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_ADCCH14_AFION)
//#define HTCFG_ADCCH15_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_ADCCH15_AFION)


#ifdef __cplusplus
}
#endif

#endif
