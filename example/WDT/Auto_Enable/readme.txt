/**
 @page WDT_Auto_Enable

 @verbatim
 * @file    WDT/Auto_Enable/readme.txt
 * @version V1.00
 * @date    2021-01-28
 * @brief   This example describes how to enable/disable Auto WDT.
 @endverbatim

@par Example Description:

This example describes how to enable/disable auto watch dog timer and reload periodically in main function.

@par Directory Contents:

- WDT/Auto_Enable/main.c               Main program
- WDT/Auto_Enable/ht32lxxxx_it.c       Interrupt handlers

@par Hardware and Software Environment:

- This example use LED1, LED2.
- if WDT generates a reset request, then LED1 will turn off and LED2 will turne on.
- if WDT doesn't generate a reset request, then LED1 will turn on and LED2 will turne off.
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
