;/*---------------------------------------------------------------------------------------------------------*/
;/* Holtek Semiconductor Inc.                                                                               */
;/*                                                                                                         */
;/* Copyright (C) Holtek Semiconductor Inc.                                                                 */
;/* All rights reserved.                                                                                    */
;/*                                                                                                         */
;/*-----------------------------------------------------------------------------------------------------------
;  File Name        : startup_ht32l5xxxx_iar_01.s
;  Version          : $Rev:: 1030         $
;  Date             : $Date:: 2025-09-02 #$
;  Description      : Startup code.
;-----------------------------------------------------------------------------------------------------------*/

;  Supported Device
;  ========================================
;   HT32L52231, HT32L52241
;   HT32L62141
;   HT50L3200U
;   HT32L59046
;   HT50L3200W
;   HT50L3200X
;   HT32L52343, HT32L52353
;   HT32L64041
;   HT32L64141

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */

;// <o>  HT32 Device
;//      <0=> By Project Asm Define
;//      <37=> HT32L52231/41
;//      <37=> HT32L62141
;//      <37=> HT50L3200U
;//      <37=> HT32L59046
;//      <37=> HT50L3200W
;//      <37=> HT50L3200X
;//      <42=> HT32L52343/53
;//      <37=> HT32L64041
;//      <37=> HT32L64141

USE_HT32_CHIP_SET   EQU     0

_HT32FWID           EQU     0xFFFFFFFF
;_HT32FWID           EQU     0x00152231
;_HT32FWID           EQU     0x00152241
;_HT32FWID           EQU     0x00162141
;_HT32FWID           EQU     0x0013200F
;_HT32FWID           EQU     0x00159046
;_HT32FWID           EQU     0x00152343
;_HT32FWID           EQU     0x00152353
;_HT32FWID           EQU     0x00164041
;_HT32FWID           EQU     0x00164141

HT32L52231_41       EQU     37
HT32L62141          EQU     37
HT50L3200U          EQU     37
HT32L59046          EQU     37
HT50L3200W          EQU     37
HT50L3200X          EQU     37
HT32L52343_53       EQU     42
HT32L64041          EQU     37
HT32L64141          EQU     37

  IF USE_HT32_CHIP_SET=0
  ELSE
  #undef  USE_HT32_CHIP
  #define USE_HT32_CHIP      USE_HT32_CHIP_SET
  ENDIF

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
                    DATA
_RESERVED           EQU  0xFFFFFFFF
__vector_table
                    DCD  sfe(CSTACK)                        ; ---, 00, 0x000, Top address of Stack
                    DCD  Reset_Handler                      ; ---, 01, 0x004, Reset Handler
                    DCD  NMI_Handler                        ; -14, 02, 0x008, NMI Handler
                    DCD  HardFault_Handler                  ; -13, 03, 0x00C, Hard Fault Handler
                    DCD  _RESERVED                          ; ---, 04, 0x010, Reserved
                    DCD  _RESERVED                          ; ---, 05, 0x014, Reserved
                    DCD  _RESERVED                          ; ---, 06, 0x018, Reserved
                    DCD  _RESERVED                          ; ---, 07, 0x01C, Reserved
                    DCD  _HT32FWID                          ; ---, 08, 0x020, Reserved
                    DCD  _RESERVED                          ; ---, 09, 0x024, Reserved
                    DCD  _RESERVED                          ; ---, 10, 0x028, Reserved
                    DCD  SVC_Handler                        ; -05, 11, 0x02C, SVC Handler
                    DCD  _RESERVED                          ; ---, 12, 0x030, Reserved
                    DCD  _RESERVED                          ; ---, 13, 0x034, Reserved
                    DCD  PendSV_Handler                     ; -02, 14, 0x038, PendSV Handler
                    DCD  SysTick_Handler                    ; -01, 15, 0x03C, SysTick Handler

                    ; External Interrupt Handler
                    DCD  LVD_BOD_IRQHandler                 ;  00, 16, 0x040,
                  IF (USE_HT32_CHIP=HT32L52343_53)
                    DCD  ERTC_IRQHandler                    ;  01, 17, 0x044,
                  ELSE
                    DCD  RTC_IRQHandler                     ;  01, 17, 0x044,
                  ENDIF
                    DCD  FLASH_IRQHandler                   ;  02, 18, 0x048,
                    DCD  EVWUP_IRQHandler                   ;  03, 19, 0x04C,
                    DCD  EXTI0_1_IRQHandler                 ;  04, 20, 0x050,
                    DCD  EXTI2_3_IRQHandler                 ;  05, 21, 0x054,
                    DCD  EXTI4_15_IRQHandler                ;  06, 22, 0x058,
                  IF (USE_HT32_CHIP=HT32L52343_53)
                    DCD  COMP_IRQHandler                    ;  07, 23, 0x05C,
                  ELSE
                    DCD  _RESERVED                          ;  07, 23, 0x05C,
                  ENDIF
                    DCD  ADC_IRQHandler                     ;  08, 24, 0x060,
                  IF (USE_HT32_CHIP=HT32L52343_53)
                    DCD  AES_RNG_IRQHandler                 ;  09, 25, 0x064,
                  ELSE
                    DCD  _RESERVED                          ;  09, 25, 0x064,
                  ENDIF
                    DCD  MCTM0_IRQHandler                   ;  10, 26, 0x068,
                  IF (USE_HT32_CHIP=HT32L52343_53)
                    DCD  GPTM1_IRQHandler                   ;  11, 27, 0x06C,
                  ELSE
                    DCD  _RESERVED                          ;  11, 27, 0x06C,
                  ENDIF
                    DCD  GPTM0_IRQHandler                   ;  12, 28, 0x070,
                    DCD  SCTM0_IRQHandler                   ;  13, 29, 0x074,
                    DCD  SCTM1_IRQHandler                   ;  14, 30, 0x078,
                    DCD  _RESERVED                          ;  15, 31, 0x07C,
                    DCD  _RESERVED                          ;  16, 32, 0x080,
                    DCD  BFTM0_IRQHandler                   ;  17, 33, 0x084,
                    DCD  BFTM1_IRQHandler                   ;  18, 34, 0x088,
                    DCD  I2C0_IRQHandler                    ;  19, 35, 0x08C,
                    DCD  I2C1_IRQHandler                    ;  20, 36, 0x090,
                    DCD  SPI0_IRQHandler                    ;  21, 37, 0x094,
                    DCD  SPI1_IRQHandler                    ;  22, 38, 0x098,
                    DCD  USART0_IRQHandler                  ;  23, 39, 0x09C,
                  IF (USE_HT32_CHIP=HT32L52343_53)
                    DCD  USART1_IRQHandler                  ;  24, 40, 0x0A0,
                  ELSE
                    DCD  _RESERVED                          ;  24, 40, 0x0A0,
                  ENDIF
                    DCD  UART0_IRQHandler                   ;  25, 41, 0x0A4,
                    DCD  UART1_IRQHandler                   ;  26, 42, 0x0A8,
                  IF (USE_HT32_CHIP=HT32L52343_53)
                    DCD  SCI_IRQHandler                     ;  27, 43, 0x0AC,
                  ELSE
                    DCD  _RESERVED                          ;  27, 43, 0x0AC,
                  ENDIF
                    DCD  _RESERVED                          ;  28, 44, 0x0B0,
                  IF (USE_HT32_CHIP=HT32L52343_53)
                    DCD  USB_IRQHandler                     ;  29, 45, 0x0B4,
                  ELSE
                    DCD  _RESERVED                          ;  29, 45, 0x0B4,
                  ENDIF
                    DCD  PDMA_CH0_1_IRQHandler              ;  30, 46, 0x0B8,
                    DCD  PDMA_CH2_5_IRQHandler              ;  31, 47, 0x0BC,

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                    LDR     R0, =SystemInit
                    BLX     R0
                    LDR     R0, =__iar_program_start
                    BX      R0
        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
                    B       .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
                    B       .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
                    B       .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
                    B       .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
                    B       .


        PUBWEAK LVD_BOD_IRQHandler
      IF (USE_HT32_CHIP=HT32L52343_53)
        PUBWEAK ERTC_IRQHandler
      ELSE
        PUBWEAK RTC_IRQHandler
      ENDIF
        PUBWEAK FLASH_IRQHandler
        PUBWEAK EVWUP_IRQHandler
        PUBWEAK EXTI0_1_IRQHandler
        PUBWEAK EXTI2_3_IRQHandler
        PUBWEAK EXTI4_15_IRQHandler
        PUBWEAK COMP_IRQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK AES_RNG_IRQHandler
        PUBWEAK MCTM0_IRQHandler
        PUBWEAK GPTM1_IRQHandler
        PUBWEAK GPTM0_IRQHandler
        PUBWEAK SCTM0_IRQHandler
        PUBWEAK SCTM1_IRQHandler
        PUBWEAK BFTM0_IRQHandler
        PUBWEAK BFTM1_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C1_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK USART0_IRQHandler
        PUBWEAK USART1_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK UART1_IRQHandler
        PUBWEAK SCI_IRQHandler
        PUBWEAK USB_IRQHandler
        PUBWEAK PDMA_CH0_1_IRQHandler
        PUBWEAK PDMA_CH2_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)

LVD_BOD_IRQHandler
  IF (USE_HT32_CHIP=HT32L52343_53)
ERTC_IRQHandler
  ELSE
RTC_IRQHandler
  ENDIF
FLASH_IRQHandler
EVWUP_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
COMP_IRQHandler
ADC_IRQHandler
AES_RNG_IRQHandler
MCTM0_IRQHandler
GPTM1_IRQHandler
GPTM0_IRQHandler
SCTM0_IRQHandler
SCTM1_IRQHandler
BFTM0_IRQHandler
BFTM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
SCI_IRQHandler
USB_IRQHandler
PDMA_CH0_1_IRQHandler
PDMA_CH2_5_IRQHandler
                    B       .

                    END
