/*********************************************************************************************************//**
 * @file    RNG/GenerateRandom_Interrupt/main.c
 * @version $Rev:: 276          $
 * @date    $Date:: 2025-07-11 #$
 * @brief   Main program.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup RNG_Examples RNG
  * @{
  */

/** @addtogroup GenerateRandom_Interrupt GenerateRandom_Interrupt
  * @{
  */

/* Global variables ----------------------------------------------------------------------------------------*/
typedef enum{
  GenRandom_STATE_IDLE = 0,
  GenRandom_STATE_WAIT,
  GenRandom_STATE_START
} GenRandom_STATE_Enum;
GenRandom_STATE_Enum gGenerateStart = GenRandom_STATE_IDLE;
RNG_randomNumber gRandomNumber;
u32 gGen_times = 0;
volatile bool gGenerateDone = FALSE;

/* Private function prototypes -----------------------------------------------------------------------------*/
void CKCU_Configuration(void);
void RNG_Configuration(void);
void GenRandom_MainRoutine(void);
void GenRandom_BlockingMode(void);
void print_RandomNumber(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  CKCU_Configuration();               /* System Related configuration                                       */
  RETARGET_Configuration();           /* Retarget Related configuration                                     */
  RNG_Configuration();

  RNG_Cmd(HT_RNG, ENABLE);

  GenRandom_BlockingMode();
  printf("#Generate random number in blocking mode.\r\nRandom Number:\r\n");
  print_RandomNumber();

  printf("#Generate random number in non-blocking mode.\r\n");
  while(1)
  {
    if(gGenerateStart == GenRandom_STATE_IDLE)
    {
      if(gGen_times < 10)
      {
        gGen_times++;
        gGenerateStart = GenRandom_STATE_START;
      }
    }

    GenRandom_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.RNG = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure the RNG initial setting.
  * @retval None
  ***********************************************************************************************************/
void RNG_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  RNG_InitTypeDef RNG_InitStructure;
  RNG_InitStructure.invlen = RNG_INVLEN;
  RNG_InitStructure.cycnum = RNG_CYCNUM;
  RNG_Init(HT_RNG, RNG_InitStructure);
  RNG_IntConfig(HT_RNG, RNG_INT_VALID, ENABLE);
  NVIC_EnableIRQ(RNG_IRQn);
}

/*********************************************************************************************************//**
  * @brief  Generate random number in blocking mode.
  * @retval None
  ***********************************************************************************************************/
void GenRandom_BlockingMode(void)
{
  RNG_GenerateRandomNumber(HT_RNG);

  while(gGenerateDone == FALSE)
  {
  }

  RNG_GetRandomNumber(HT_RNG, &gRandomNumber);

  gGenerateDone = FALSE;
}


/*********************************************************************************************************//**
  * @brief  Generate random number in non-blocking mode.
  * @retval None
  ***********************************************************************************************************/
void GenRandom_MainRoutine(void)
{
    if(gGenerateStart == GenRandom_STATE_START)
    {
      RNG_GenerateRandomNumber(HT_RNG);
      gGenerateStart = GenRandom_STATE_WAIT;
    }
    
    if(gGenerateStart == GenRandom_STATE_WAIT)
    {
      if(gGenerateDone == TRUE)
      {
        /* Clears RNG valid flag before reading the random number. */
        RNG_ClearFlagStatus(HT_RNG, RNG_FLAG_VALID);

        RNG_GetRandomNumber(HT_RNG, &gRandomNumber);
        gGenerateDone = FALSE;
        gGenerateStart = GenRandom_STATE_IDLE;

        printf("#%d, Random Number:\r\n", gGen_times);
        print_RandomNumber();
      }
    }
}

/*********************************************************************************************************//**
  * @brief  Print the random number.
  * @retval None
  ***********************************************************************************************************/
void print_RandomNumber(void)
{
  int i;
  for(i=0; i<6; i++)
  {
    printf("%04X", gRandomNumber.randomWord[i]);
  }
  printf("\r\n");
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
