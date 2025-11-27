/*********************************************************************************************************//**
 * @file    ht50l3200w_libcfg.h
 * @version $Rev:: 1145         $
 * @date    $Date:: 2025-10-22 #$
 * @brief   The library configuration file.
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
#ifndef __HT50L3200W_LIBCFG_H
#define __HT50L3200W_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT50L3200W)
#define USE_MEM_HT50L3200W
#endif

#define LIBCFG_MAX_SPEED                  (48000000)

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT50L3200W
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 32)
  #define LIBCFG_RAM_SIZE                 (1024 * 4)
  #define LIBCFG_CHIPNAME                 (0x3200F)
#endif

#define LIBCFG_MAX_VREF_VOL                                (3600)     /* AD Converter Reference Max.        */
                                                                      /* Voltage. Unit: mV                  */

#define LIBCFG_ADC_TEMP_SENSOR_AVG_SLOPE                   (445)      /* The conversion value average slope */
                                                                      /* from temperature sensor voltage.   */
                                                                      /* Unit: 10uV/ Celsius                */

#define LIBCFG_ADC_TEMP_SENSOR_CALIBRATION_ADVREFP         (3000)     /* Unit: mV                           */

#define LIBCFG_BFTM1                      (1)
#define LIBCFG_SCTM0                      (1)
#define LIBCFG_SCTM1                      (1)
#define LIBCFG_MCTM0                      (1)

#define LIBCFG_PDMA                       (1)
#define LIBCFG_CRC                        (1)
#define LIBCFG_GPIOC                      (1)
#define LIBCFG_DIV                        (1)
#define LIBCFG_I2C1                       (1)
#define LIBCFG_MCTM0                      (1)
#define LIBCFG_SCTM0                      (1)
#define LIBCFG_SCTM1                      (1)
#define LIBCFG_SPI1                       (1)
#define LIBCFG_UART1                      (1)

#define LIBCFG_ADC_CH8_11                 (1)
#define LIBCFG_ADC_IVREF                  (1)
#define LIBCFG_ADC_MVDDA                  (1)
#define LIBCFG_ADC_TEMP_SENSOR            (1)
#define LIBCFG_ADC_VREFBUF                (1)
#define LIBCFG_ADC_FLEXIBLE_VREFVALR      (1)
#define LIBCFG_BAKREG                     (1)
#define LIBCFG_CKCU_PLLSRCDIV             (1)
#define LIBCFG_FMC_CACHE_FLUSH            (0)
#define LIBCFG_FMC_CACHE                  (1)
#define LIBCFG_FMC_EATF                   (1)
#define LIBCFG_FMC_ISPINT                 (1)
#define LIBCFG_FMC_WAIT_STATE_2           (1)
#define LIBCFG_USART_LIN                  (1)
#define LIBCFG_USART_SINGLE_WIRE          (1)
#define LIBCFG_PWRCU_WAKEUP1              (1)
#define LIBCFG_PWRCU_WAKEUP_V01           (1)
#define LIBCFG_PWRCU_DEEPSLEEP3           (1)
#define LIBCFG_PWRCU_DEEPPOWERDOWN        (1)
#define LIBCFG_CKCU_HSIRDYCR              (1)
#define LIBCFG_CKCU_LSI_LSE_STOP          (1)
#define LIBCFG_CKCU_LSI_TRIM              (1)
#define LIBCFG_CKCU_REFCLK_EXT_PIN        (1)
#define LIBCFG_CRC32_USERDEFINE           (1)
#endif
