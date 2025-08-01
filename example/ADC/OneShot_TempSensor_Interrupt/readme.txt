/**
 @page ADC_OneShot_TempSensor_Interrupt

 @verbatim
 * @file    ADC/OneShot_TempSensor_Interrupt/readme.txt
 * @version V1.00
 * @date    2024-03-20
 * @brief   Description of how to use the ADC of Temperature Sensor by interrupt mode.
 @endverbatim

@par Example Description:


This example shows how to measure the ADC of Temperature Sensor using ADC one shot mode trigger by software.

  <PRE>
  ====================     ===================     =================     ===============================
  =       Main()     =     = ADC ISR (TSRDY) =     = ADC ISR (EOC) =     =           Main()            =
  =    TempSensor    = --> = ADC SW Trigger  = --> = Save Value    = --> =     Print gADC_Result       =
  = start to operate =     =                 =     = gADC_Result   =     = TempSensor start to operate =
  ====================     ===================     =================     ===============================
                 TempSensor Ready            Cycle End        gADC_CycleEndOfConversion
  </PRE>


Temperture Sensor of ADC configuration:
  - The temperature sensor's optimal operation clock frequency (TSCLK) is around 250 kHz. Therefore,
    in this example, the system frequency is set to 48 MHz through system_ht32l5xxxx_xx.c, and the
    temperature divider (TSDIV) is setted to 8 (TSCLK = (48 MHz / 2^8) = 48 MHz / 256 = 187.5 kHz).

ADC configuration:
  - ADC clock frequency: CK_ADC = 48 MHz / 8 = 6 MHz
  - One Shot mode, sequence length = 1
  - Set ADST = 59, sampling time = 1 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1 + ADST + 13) / CK_ADC
  - Set ADC conversion sequence 0 as channel ADC_CH_VTS.

The cycle-end of conversion Polling is enabled. Each time the ADC cycle conversion is finished a "cycle-end
of conversion" Polling will be occurred. The ADC Polling service routine will display the ADC result.

If the USART/UART is connected to PC, the ADC result will be printed on the terminal.

@par Directory Contents:

- ADC/OneShot_TempSensor_Interrupt/main.c                             Main program
- ADC/OneShot_TempSensor_Interrupt/ht32lxxxxx_nn_it.c                 Interrupt handlers
- ADC/OneShot_TempSensor_Interrupt/ht32_board_config.h                Board configuration file

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
