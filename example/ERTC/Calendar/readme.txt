/**
 @page ERTC_Calendar

 @verbatim
 * @file    ERTC/Calendar/readme.txt
 * @version V1.00
 * @date    2025-08-28
 * @brief   Description of ERTC Calendar example.
 @endverbatim

@par Example Description:

This example demonstrates how to use the Enhanced Real Time Clock (ERTC) peripheral
to keep track of calendar time, configure date/time via HyperTerminal, and adjust
time in sub-second resolution using push buttons.

The Low Speed External (LSE) clock (32.768 kHz) is used as the ERTC clock source.

The ERTC is in the VDD domain and powered by VDD when system reset,
the ERTC configuration will not be lost if VDD is not switched off. 

The program behaves as follows:

1. On startup, the user is prompted through HyperTerminal to enter the initial
   calendar settings (Year, Month, Day, Weekday, Hour Format, Hours, Minutes, Seconds).
   - Year range is defined relative to `YEAR_EPOCH` (2024 ~ 2123).
   - Supports both 12-hour and 24-hour time formats.
   - AM/PM selection available when in 12-hour format.

2. During runtime:
   - Press **KEY1** to decrease the current time by 0.5 seconds (using ERTC sync shift).
   - Press **KEY2** to increase the current time by 0.5 seconds.
   - The current date/time with sub-second precision is continuously displayed
     on HyperTerminal in the selected hour format (12HR/24HR).

@par Directory Contents:

- ERTC/Calendar/main.c                Main program
- ERTC/Calendar/ht32lxxxx_nn_it.c     Interrupt handlers

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
