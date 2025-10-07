/**
 @page ERTC_Calibration_Demo

 @verbatim
 * @file    ERTC/Calibration_Demo/readme.txt
 * @version V1.00
 * @date    2025-09-03
 * @brief   Description of ERTC Calibration example.
 @endverbatim

@par Example Description:

This example demonstrates how to configure and adjust the **Enhanced Real Time Clock (ERTC) calibration function**.
It shows how to enable/disable calibration, configure calibration windows, and observe the difference in the
ERTC output clock (ERTC_OUT) before and after calibration.

The Low Speed External (LSE) clock (32.768 kHz) is used as the ERTC clock source.

The ERTC is in the VDD domain and powered by VDD when system reset,
the ERTC configuration will not be lost if VDD is not switched off. 

The program behaves as follows:

1. On startup:
   - Initializes the ERTC peripheral with LSE as the clock source.
   - Configures the asynchronous and synchronous prescalers to generate a 1 Hz time base.
   - Configures **ERTC_OUT** to output APRE signal

2. Calibration control (via UART menu):
   - **Option 0**: Disable calibration.  
   - **Option 1**: Calibration with 32-second window, mask 255 CK_ERTC pulses.
   - **Option 2**: Calibration with 32-second window, add 255 CK_ERTC pulses.

   Each option requires writing the **ERTC unprotect key** before modifying the calibration registers.

3. Observation:
   - By probing the **ERTC_OUT pin**, users can directly compare the output waveform frequency before and after calibration.
   - This allows verification of calibration impact on the real-time clock accuracy.

@par Directory Contents:

- ERTC/Calibration_Demo/main.c             Main program
- ERTC/Calibration_Demo/ht32lxxxx_nn_it.c  Interrupt handlers

@par Hardware and Software Environment:

- Connect a null-modem female/female RS232 cable between the COM1 DB9 connector and PC serial port.
  HyperTerminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - BaudRate = 115200 baud
  - Flow control: None
- This example can be run on HT32 Series development board.
- Use an oscilloscope to monitor the **ERTC_OUT pin** to observe calibration effects.

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
