/**
 @page ADC_OneShot_PWMTrigger

 @verbatim
 * @file    ADC/OneShot_PWMTrigger/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of Timer PWM trigger ADC start of conversion example.
 @endverbatim

@par Example Description:

This example shows how to trigger ADC by Timer compare match of CH3 (CH3O).

  <PRE>
  ================     =================     =================     =================
  =              =     =               =     =    ADC ISR    =     =     Main()    =
  =    Timer     = --> =      ADC      = --> =   Save Value  = --> =     print     =
  =              =     = One Shot mode =     =  gADC_Result  =     =   gADC_Result =
  ================     =================     =================     =================
                  CH3O                Cycle End      gADC_CycleEndOfConversion
  </PRE>

ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - One Shot mode, sequence length = 3
  - Set ADST = 36, sampling time = 1 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1 + ADST + 13) / CK_ADC
  - Set ADC conversion sequence 0 ~ 2 as channel n.
  - Set Timer CH3O as ADC trigger source.

Timer configuration:
  - Timer clock   = 40 kHz (CK_AHB / (CK_AHB / 40000))
  - PWM reload    = 40000
  - PWM frequency = 40 kHz / 40000 = 1 Hz (Example: 48 MHz / (48 MHz / 40000) / 40000 = 1 Hz)
  - TM CH3O is configured as PWM2 mode, compare match value = 20000 (20000 / 40000 = 50% duty).

The cycle-end of conversion interrupt is enabled. Each time the ADC cycle conversion is finished (Three
channels are finished), a "cycle-end of conversion" interrupt will be occurred. The ADC interrupt service
routine will store the ADC result into the global variable, "gADC_Result[]".

If the USART/UART is connected to PC, the ADC result will be printed on the terminal. Besides, LED1 ~ LED3
represent to Timer CH3 compare match (trigger), single-end of conversion, and cycle-end of conversion.

@par Directory Contents:

- ADC/OneShot_PWMTrigger/main.c                             Main program
- ADC/OneShot_PWMTrigger/ht32lxxxxx_nn_it.c                 Interrupt handlers
- ADC/OneShot_PWMTrigger/ht32_board_config.h                Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word length = 8 Bits
  - One stop bit
  - No parity
  - BaudRate = 115200 baud
  - Flow control: None

@par Firmware Disclaimer Information

1. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
   proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
   other intellectual property laws.

2. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
   other than HOLTEK and the customer.

3. The program technical documentation, including the code, is provided "as is" and for customer reference
   only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
   the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
   the warranties of merchantability, satisfactory quality and fitness for a particular purpose.

 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 */
