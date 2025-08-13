/*********************************************************************************************************//**
 * @file    ht32l5xxxx_lib.h
 * @version $Rev:: 812          $
 * @date    $Date:: 2025-08-01 #$
 * @brief   The header file includes all the header files of the libraries.
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
#ifndef __HT32L5XXXX_LIB_H
#define __HT32L5XXXX_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define HT32_FWLIB_VER                  (0x01002002)
#define HT32_FWLIB_SVN                  (0x837)

#if defined(USE_HT32L52231_41)
  #include "ht32l52231_41_libcfg.h"
#endif
#if defined(USE_HT50L3200U)
  #include "ht50l3200u_libcfg.h"
#endif
#if defined(USE_HT50L3200W)
  #include "ht50l3200w_libcfg.h"
#endif
#if defined(USE_HT50L3200X)
  #include "ht50l3200x_libcfg.h"
#endif
/* Includes ------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "ht32l5xxxx_conf.h"

#if (HT32_LIB_DEBUG == 1)
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed.
  *   If expr is true, it returns no value.
  * @retval None
  */
#define Assert_Param(expr) ((expr) ? (void)0 : assert_error((u8 *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- ------------------------------*/
void assert_error(u8* file, u32 line);
#else

#define Assert_Param(expr) ((void)0)

#endif /* DEBUG --------------------------------------------------------------------------------------------*/


#if _ADC
  #include "ht32l5xxxx_adc.h"
#endif

#if _BFTM
  #include "ht32l5xxxx_bftm.h"
#endif

#if _CKCU
  #include "ht32l5xxxx_ckcu.h"
#endif

#if _CRC && LIBCFG_CRC
  #include "ht32l5xxxx_crc.h"
#endif

#if _DIV && LIBCFG_DIV
  #include "ht32l5xxxx_div.h"
#endif

#if _EXTI
  #include "ht32l5xxxx_exti.h"
#endif

#if _FLASH
  #include "ht32l5xxxx_flash.h"
#endif

#if _GPIO
  #include "ht32l5xxxx_gpio.h"
#endif

#if _GPTM
  #include "ht32l5xxxx_tm_type.h"
  #include "ht32l5xxxx_tm.h"
#endif

#if _I2C
  #include "ht32l5xxxx_i2c.h"
#endif

#if _MCTM && LIBCFG_MCTM0
  #include "ht32l5xxxx_tm_type.h"
  #include "ht32l5xxxx_tm.h"
  #include "ht32l5xxxx_mctm.h"
#endif

#if _PDMA && LIBCFG_PDMA
  #include "ht32l5xxxx_pdma.h"
#endif

#if _PWRCU
  #include "ht32l5xxxx_pwrcu.h"
#endif

#if _RSTCU
  #include "ht32l5xxxx_rstcu.h"
#endif

#if _RTC
  #include "ht32l5xxxx_rtc.h"
#endif

#if _SCTM
  #include "ht32l5xxxx_tm_type.h"
  #include "ht32l5xxxx_tm.h"
#endif

#if _SPI
  #include "ht32l5xxxx_spi.h"
#endif

#if _USART
  #include "ht32l5xxxx_usart.h"
#endif
#if _WDT
  #include "ht32l5xxxx_wdt.h"
#endif

#if _MISC
  #include "ht32_cm0plus_misc.h"
#endif

#if _SERIAL
  #include "ht32_serial.h"
#endif

#if _SWDIV
  #include "ht32_div.h"
#endif

#if _SWRAND
  #include "ht32_rand.h"
#endif

#if (_RETARGET)
  #if defined (__GNUC__)
    #undef getchar
    #define getchar SERIAL_GetChar
  #endif
#endif

#ifdef HTCFG_TIME_IPSEL
#include "ht32_time.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
