/**
 @page ERTC_Out

 @verbatim
 * @file    ERTC/ERTC_Out/readme.txt
 * @version V1.01
 * @date    2025-09-01
 * @brief   Description of ERTC Output example.
 @endverbatim

@par Example Description:

This example demonstrates how to configure the Enhanced Real Time Clock (ERTC) peripheral
to generate output signals from different ERTC sources such as Alarm, Wakeup Timer, or clock outputs.

The Low Speed External (LSE) clock (32.768 kHz) is used as the ERTC clock source.

The ERTC is in the VDD domain and powered by VDD when system reset,
the ERTC configuration will not be lost if VDD is not switched off. 

The program behaves as follows:

1. On startup:
   - The application initializes the ERTC with a default date/time (2024/11/05, Tuesday, 12:00:00 AM).
   - Configures ERTC Alarm and Wakeup Timer functions.
   - Enables ERTC output pin.

2. User selection via HyperTerminal:
   - The program displays a menu allowing the user to select the **ERTC output source**:
     - (1) Alarm (triggered every 1s)
     - (2) Wakeup Timer (triggered every 2s)
     - (3) CK_SPRE (1 Hz clock output)
     - (4) CK_APRE (256 Hz clock output)

3. Output mode configuration:
   - For Alarm and Wakeup Timer sources, the user can further select the **output mode**:
     - Toggle Mode
     - Pulse Mode
     - Level Mode
   - For CK_SPRE and CK_APRE, only Toggle Mode is available.

@par Directory Contents:

- ERTC/ERTC_Out/main.c                Main program
- ERTC/ERTC_Out/ht32lxxxx_nn_it.c     Interrupt handlers

@par Hardware and Software Environment:

- Connect a null-modem female/female RS232 cable between the COM1 DB9 connector and PC serial port.
  HyperTerminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - BaudRate = 115200 baud
  - Flow control: None
- This example can be run on HT32 Series development board.

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
