/**
 @page ERTC_Calibration

 @verbatim
 * @file    ERTC/Calibration/readme.txt
 * @version V1.00
 * @date    2025-09-03
 * @brief   Description of ERTC Calibration example.
 @endverbatim

@par Example Description:

This example demonstrates how to configure the **Enhanced Real Time Clock (ERTC) calibration function**.
The Low Speed External (LSE) clock (32.768 kHz) is selected as the ERTC clock source, and the calibration
function is used to adjust the frequency error of the LSE.

The Low Speed External (LSE) clock (32.768 kHz) is used as the ERTC clock source.

The ERTC is in the VDD domain and powered by VDD when system reset,
the ERTC configuration will not be lost if VDD is not switched off.

The program behaves as follows:

1. On startup:
   - Enables AFIO and configures **PA9** as CKOUT pin.
   - Outputs the LSE clock (32768 Hz) to CKOUT pin for external measurement.
   - Configures the ERTC with LSE as the clock source.
   - Configures calibration settings.
   - Sets asynchronous prescaler = 0x7F, synchronous prescaler = 0xFF, to generate 1 Hz time base.
   - Initializes the calendar with Date = 2024/11/05 (Tuesday), Time = 12:00:00 AM.

2. Calibration configuration:
   - Measure CKOUT frequency or pulse count during a calibration window (8s / 16s / 32s).
   - Calculate error:
     - Expected = 32768 × window_seconds
     - Error = Measured – Expected
   - Apply correction:
     - If Error > 0: LSE is faster, remove pulses.
     - If Error < 0: LSE is slower, add pulses.
   - Example in code:
     `ERTC_CalibConfig(ERTC_CALIB_PERIOD_32, ERTC_CALIB_MASK_PULSES, 224);`
     → 32-second calibration window, removing 224 pulses.

3. Observation:
   - Probe **PA9 (CKOUT)** with oscilloscope or frequency counter.
   - Compare measured frequency before and after calibration.
   - Verify correction effect on RTC accuracy.

@par Directory Contents:

- ERTC/Calibration/main.c             Main program
- ERTC/Calibration/ht32lxxxx_nn_it.c  Interrupt handlers

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
