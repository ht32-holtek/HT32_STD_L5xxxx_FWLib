/**
 @page NVIC_External_Interrupt

 @verbatim
 * @file    NVIC/External_Interrupt/readme.txt
 * @version V1.00
 * @date    2014-06-30
 * @brief   Description of NVIC External_Interrupt example.
 @endverbatim

@par Example Description:

This example describes how to configure the Nested Vectored Interrupt Controller
(NVIC)IRQ Channels:

- Enable the following external interrupts in NVIC: LVD_BOD, EXTI0_1, FLASH.
- Configure the priority of each external interrupt.
- Set each external interrupt pending bit during a lower priority ISR
  (Interrupt Service Routine).
- Show the order of interrupts by LEDs.

@par Directory Contents:

- NVIC/External_Interrupt/main.c               Main program
- NVIC/External_Interrupt/ht32lxxxx_it.c       Interrupt handlers

@par Hardware and Software Environment:

- This example shows the result by LEDs.
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
