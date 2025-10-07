/**
 @page ERTC_Alarm

 @verbatim
 * @file    ERTC/Alarm/readme.txt
 * @version V1.00
 * @date    2025-08-29
 * @brief   Description of ERTC Alarm example.
 @endverbatim

@par Example Description:

This example demonstrates how to configure the Enhanced Real Time Clock (ERTC) peripheral
to generate periodic alarms and wake up the MCU from DeepSleep2 mode.

The Low Speed External (LSE) clock (32.768 kHz) is used as the ERTC clock source.

The ERTC is in the VDD domain and powered by VDD when system reset,
the ERTC configuration will not be lost if VDD is not switched off. 

The program behaves as follows:

1. On startup:
   - User is prompted with message "Press KEY1 Continue.." via HyperTerminal.
   - After pressing **KEY1**, the ERTC is configured and initialized with a default
     date/time (2024/11/05, Tuesday, 12:00:00 AM).

2. Alarm configuration:
   - The example supports multiple alarm intervals (second, minute, hour, day, or weekday).
   - In the provided configuration, **ALARM_EVERY_SECOND** is enabled by default.
   - When the alarm triggers, the MCU wakes up from DeepSleep2 mode and prints
     the current date/time to HyperTerminal in either 12HR or 24HR format.

3. Power behavior:
   - MCU enters DeepSleep2 mode after each cycle, waiting for the next alarm event.
   - Upon wakeup, alarm flag is cleared and new date/time is displayed.

@par Directory Contents:

- ERTC/Alarm/main.c                Main program
- ERTC/Alarm/ht32lxxxx_nn_it.c     Interrupt handlers

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
