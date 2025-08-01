/*********************************************************************************************************//**
 * @file    SPI/PDMA/ht32_board_config.h
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
#if (LIBCFG_PDMA)
#else
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32L52241_SK)
  #define HTCFG_SPIM_SEL_GPIOX                    B
  #define HTCFG_SPIM_SEL_GPION                    2
  #define HTCFG_SPIM_SCK_GPIOX                    B
  #define HTCFG_SPIM_SCK_GPION                    3
  #define HTCFG_SPIM_MOSI_GPIOX                   B
  #define HTCFG_SPIM_MOSI_GPION                   4
  #define HTCFG_SPIM_MISO_GPIOX                   B
  #define HTCFG_SPIM_MISO_GPION                   5
  #define HTCFG_SPIM_IPN                          SPI0
  #define HTCFG_SPIM_PDMA_TX                      PDMA_SPI0_TX
  #define HTCFG_SPIM_PDMA_RX                      PDMA_SPI0_RX

  #define HTCFG_SPIS_SEL_GPIOX                    A
  #define HTCFG_SPIS_SEL_GPION                    14
  #define HTCFG_SPIS_SCK_GPIOX                    A
  #define HTCFG_SPIS_SCK_GPION                    15
  #define HTCFG_SPIS_MOSI_GPIOX                   B
  #define HTCFG_SPIS_MOSI_GPION                   0
  #define HTCFG_SPIS_MISO_GPIOX                   B
  #define HTCFG_SPIS_MISO_GPION                   1
  #define HTCFG_SPIS_IPN                          SPI1
  #define HTCFG_SPIS_PDMA_TX                      PDMA_SPI1_TX
  #define HTCFG_SPIS_PDMA_RX                      PDMA_SPI1_RX
#endif

#define HTCFG_SPIM_SEL_GPIO_PORT                  STRCAT2(HT_GPIO,   HTCFG_SPIM_SEL_GPIOX)
#define HTCFG_SPIM_SEL_GPIO_ID                    STRCAT2(GPIO_P,    HTCFG_SPIM_SEL_GPIOX)
#define HTCFG_SPIM_SEL_AFIO_PIN                   STRCAT2(AFIO_PIN_, HTCFG_SPIM_SEL_GPION)
#define HTCFG_SPIM_SCK_GPIO_ID                    STRCAT2(GPIO_P,    HTCFG_SPIM_SCK_GPIOX)
#define HTCFG_SPIM_SCK_AFIO_PIN                   STRCAT2(AFIO_PIN_, HTCFG_SPIM_SCK_GPION)
#define HTCFG_SPIM_MOSI_GPIO_ID                   STRCAT2(GPIO_P,    HTCFG_SPIM_MOSI_GPIOX)
#define HTCFG_SPIM_MOSI_AFIO_PIN                  STRCAT2(AFIO_PIN_, HTCFG_SPIM_MOSI_GPION)
#define HTCFG_SPIM_MISO_GPIO_ID                   STRCAT2(GPIO_P,    HTCFG_SPIM_MISO_GPIOX)
#define HTCFG_SPIM_MISO_AFIO_PIN                  STRCAT2(AFIO_PIN_, HTCFG_SPIM_MISO_GPION)
#define HTCFG_SPIM_PORT                           STRCAT2(HT_,       HTCFG_SPIM_IPN)

#define HTCFG_SPIS_SEL_GPIO_CLK                   STRCAT2(P,         HTCFG_SPIS_SEL_GPIOX)
#define HTCFG_SPIS_SEL_GPIO_PORT                  STRCAT2(HT_GPIO,   HTCFG_SPIS_SEL_GPIOX)
#define HTCFG_SPIS_SEL_GPIO_ID                    STRCAT2(GPIO_P,    HTCFG_SPIS_SEL_GPIOX)
#define HTCFG_SPIS_SEL_AFIO_PIN                   STRCAT2(AFIO_PIN_, HTCFG_SPIS_SEL_GPION)
#define HTCFG_SPIS_SCK_GPIO_ID                    STRCAT2(GPIO_P,    HTCFG_SPIS_SCK_GPIOX)
#define HTCFG_SPIS_SCK_AFIO_PIN                   STRCAT2(AFIO_PIN_, HTCFG_SPIS_SCK_GPION)
#define HTCFG_SPIS_MOSI_GPIO_ID                   STRCAT2(GPIO_P,    HTCFG_SPIS_MOSI_GPIOX)
#define HTCFG_SPIS_MOSI_AFIO_PIN                  STRCAT2(AFIO_PIN_, HTCFG_SPIS_MOSI_GPION)
#define HTCFG_SPIS_MISO_GPIO_ID                   STRCAT2(GPIO_P,    HTCFG_SPIS_MISO_GPIOX)
#define HTCFG_SPIS_MISO_AFIO_PIN                  STRCAT2(AFIO_PIN_, HTCFG_SPIS_MISO_GPION)
#define HTCFG_SPIS_PORT                           STRCAT2(HT_,       HTCFG_SPIS_IPN)

#ifdef __cplusplus
}
#endif

#endif
