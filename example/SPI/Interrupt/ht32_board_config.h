/*********************************************************************************************************//**
 * @file    SPI/Interrupt/ht32_board_config.h
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
  #define HTCFG_SPI_MASTER_SEL_GPIO_ID             (HT_GPIOB)
  #define HTCFG_SPI_MASTER_SEL_GPIO_CLOCK(CK)      (CK.Bit.PB)

  #define HTCFG_SPI_MASTER_CLOCK(CK)               (CK.Bit.SPI0)
  #define HTCFG_SPI_MASTER                         (HT_SPI0)
  #define HTCFG_SPI_MASTER_IRQn                    (SPI0_IRQn)
  #define HTCFG_SPI_MASTER_SEL_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_MASTER_SCK_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_MASTER_MOSI_AFIO_PORT          (GPIO_PB)
  #define HTCFG_SPI_MASTER_MISO_AFIO_PORT          (GPIO_PB)
  #define HTCFG_SPI_MASTER_SEL_AFIO_PIN            (AFIO_PIN_2)
  #define HTCFG_SPI_MASTER_SCK_AFIO_PIN            (AFIO_PIN_3)
  #define HTCFG_SPI_MASTER_MOSI_AFIO_PIN           (AFIO_PIN_4)
  #define HTCFG_SPI_MASTER_MISO_AFIO_PIN           (AFIO_PIN_5)
  #define HTCFG_SPI_MASTER_IRQHandler              (SPI0_IRQHandler)

  #define HTCFG_SPI_SLAVE_CLOCK(CK)                (CK.Bit.SPI1)
  #define HTCFG_SPI_SLAVE                          (HT_SPI1)
  #define HTCFG_SPI_SLAVE_IRQn                     (SPI1_IRQn)
  #define HTCFG_SPI_SLAVE_SEL_AFIO_PORT            (GPIO_PA)
  #define HTCFG_SPI_SLAVE_SCK_AFIO_PORT            (GPIO_PA)
  #define HTCFG_SPI_SLAVE_MOSI_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_SLAVE_MISO_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_SLAVE_SEL_AFIO_PIN             (AFIO_PIN_14)
  #define HTCFG_SPI_SLAVE_SCK_AFIO_PIN             (AFIO_PIN_15)
  #define HTCFG_SPI_SLAVE_MOSI_AFIO_PIN            (AFIO_PIN_0)
  #define HTCFG_SPI_SLAVE_MISO_AFIO_PIN            (AFIO_PIN_1)
  #define HTCFG_SPI_SLAVE_IRQHandler               (SPI1_IRQHandler)
#endif

#if defined(USE_HT32L52353_SK)
  #define HTCFG_SPI_MASTER_SEL_GPIO_ID             (HT_GPIOB)
  #define HTCFG_SPI_MASTER_SEL_GPIO_CLOCK(CK)      (CK.Bit.PB)

  #define HTCFG_SPI_MASTER_CLOCK(CK)               (CK.Bit.SPI0)
  #define HTCFG_SPI_MASTER                         (HT_SPI0)
  #define HTCFG_SPI_MASTER_IRQn                    (SPI0_IRQn)
  #define HTCFG_SPI_MASTER_SEL_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_MASTER_SCK_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_MASTER_MOSI_AFIO_PORT          (GPIO_PB)
  #define HTCFG_SPI_MASTER_MISO_AFIO_PORT          (GPIO_PB)
  #define HTCFG_SPI_MASTER_SEL_AFIO_PIN            (AFIO_PIN_2)
  #define HTCFG_SPI_MASTER_SCK_AFIO_PIN            (AFIO_PIN_3)
  #define HTCFG_SPI_MASTER_MOSI_AFIO_PIN           (AFIO_PIN_4)
  #define HTCFG_SPI_MASTER_MISO_AFIO_PIN           (AFIO_PIN_5)
  #define HTCFG_SPI_MASTER_IRQHandler              (SPI0_IRQHandler)

  #define HTCFG_SPI_SLAVE_CLOCK(CK)                (CK.Bit.SPI1)
  #define HTCFG_SPI_SLAVE                          (HT_SPI1)
  #define HTCFG_SPI_SLAVE_IRQn                     (SPI1_IRQn)
  #define HTCFG_SPI_SLAVE_SEL_AFIO_PORT            (GPIO_PA)
  #define HTCFG_SPI_SLAVE_SCK_AFIO_PORT            (GPIO_PA)
  #define HTCFG_SPI_SLAVE_MOSI_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_SLAVE_MISO_AFIO_PORT           (GPIO_PB)
  #define HTCFG_SPI_SLAVE_SEL_AFIO_PIN             (AFIO_PIN_14)
  #define HTCFG_SPI_SLAVE_SCK_AFIO_PIN             (AFIO_PIN_15)
  #define HTCFG_SPI_SLAVE_MOSI_AFIO_PIN            (AFIO_PIN_0)
  #define HTCFG_SPI_SLAVE_MISO_AFIO_PIN            (AFIO_PIN_1)
  #define HTCFG_SPI_SLAVE_IRQHandler               (SPI1_IRQHandler)
#endif

#ifdef __cplusplus
}
#endif

#endif
