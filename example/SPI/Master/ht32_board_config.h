/*********************************************************************************************************//**
 * @file    SPI/Master/ht32_board_config.h
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
  #define _HTCFG_INT_GPIOX                     B
  #define HTCFG_INT_GPION                      0

  #define HTCFG_SPI_IPN                        SPI0

  #define HTCFG_MASTER_SPI_SCK_GPIO_ID         (GPIO_PB)
  #define HTCFG_MASTER_SPI_SCK_AFIO_PIN        (AFIO_PIN_3)

  #define HTCFG_MASTER_SPI_MOSI_GPIO_ID        (GPIO_PB)
  #define HTCFG_MASTER_SPI_MOSI_AFIO_PIN       (AFIO_PIN_4)

  #define HTCFG_MASTER_SPI_MISO_GPIO_ID        (GPIO_PB)
  #define HTCFG_MASTER_SPI_MISO_AFIO_PIN       (AFIO_PIN_5)

  #define HTCFG_MASTER_SPI_SEL_GPIO_ID         (GPIO_PB)
  #define HTCFG_MASTER_SPI_SEL_AFIO_PIN        (GPIO_PIN_2)
#endif

#define HTCFG_INT_GPIO_ID                    STRCAT2(GPIO_P,        _HTCFG_INT_GPIOX)
#define HTCFG_INT_GPIO_PIN                   STRCAT2(GPIO_PIN_,      HTCFG_INT_GPION)
#define HTCFG_INT_CLK(CK)                    STRCAT2(CK.Bit.P,      _HTCFG_INT_GPIOX)
#define HTCFG_MASTER_SPI                     STRCAT2(HT_,              HTCFG_SPI_IPN)
#define HTCFG_MASTER_SPI_IRQ                 STRCAT2(HTCFG_SPI_IPN,            _IRQn)
#define HTCFG_SPI_IRQHandler                 STRCAT2(HTCFG_SPI_IPN,      _IRQHandler)

#ifdef __cplusplus
}
#endif

#endif
