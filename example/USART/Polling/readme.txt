/**
 @page USART_Polling

 @verbatim
 * @file    USART/Polling/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of USART/UART Tx and Rx polling mode example.
 @endverbatim

@par Example Description:

This example describes how to send and receive data with USART/UART by the polling mode.

The PCLK_UxART frequency is equal to CK_AHB. The USART/UART is configured as 8-bit Word length, one stop bit,
no parity and baud rate is set to 115200 bps.

This example also shows the Blocking / Non-Blocking mode of USART/UART Rx data.

@par Directory Contents:

- USART/Polling/main.c                            Main program
- USART/Polling/ht32lxxxxx_nn_it.c                Interrupt handlers
- USART/Polling/ht32_board_config.h               Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
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
