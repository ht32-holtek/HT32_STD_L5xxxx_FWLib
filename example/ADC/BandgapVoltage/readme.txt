/**
 @page ADC_BandgapVoltage

 @verbatim
 * @file    ADC/BandgapVoltage/readme.txt
 * @version V1.00
 * @date    2022-10-20
 * @brief   Description of ADC one shot mode by software trigger example.
 @endverbatim

@par Example Description:

!!! NOTICE !!!
   The VBG output to IO is for test purposes only, it is not recommended to use the VBG output with an
   external circuit.

This example shows how to use the ADC internal bandgap voltage (VBG) to calculate the voltage value of MVDDA
and another ADC input.

ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - One Shot mode, sequence length = 3
  - Set ADST = 36, sampling time = 1 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1 + ADST + 13) / CK_ADC
  - Set ADC conversion sequence 0 ~ 2 as channel n.
  - Set software as ADC trigger source.
  - Enable the internal VBG.
  - Enable MVDDA function.
  - Enable ADC single-end/cycle-end of conversion interrupt.

The ADC results are copied to the "gADC_Result[]" buffer by the ADC cycle-end interrupt. The ADC main routine
converts ADC results of the MVDDA, VBG, and another ADC input from 12-bit data to the voltage(mV).
If the USART is connected to PC, the ADC result will be printed on the terminal.

@par Directory Contents:

- ADC/BandgapVoltage/main.c                       Main program
- ADC/BandgapVoltage/ht32lxxxx_it.c               Interrupt handlers
- ADC/BandgapVoltage/ht32_board_config.h          Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word Length = 8 Bits
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
