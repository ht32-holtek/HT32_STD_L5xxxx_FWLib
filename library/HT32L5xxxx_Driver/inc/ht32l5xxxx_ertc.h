/*********************************************************************************************************//**
 * @file    ht32l5xxxx_ertc.h
 * @version $Rev:: 718          $
 * @date    $Date:: 2025-07-23 #$
 * @brief   The header file of the ERTC library.
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

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __ht32l5XXXX_ERTC_H
#define __ht32l5XXXX_ERTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32L5xxxx_Peripheral_Driver HT32L5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup ERTC
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup ERTC_Exported_Types ERTC exported types
  * @{
  */
/**
  * @brief  ERTC Time structure definition
  */
typedef struct
{
  u8 Hours;    /*!< Specifies the ERTC Time Hour.                 */
  u8 Minutes;  /*!< Specifies the ERTC Time Minutes.              */
  u8 Seconds;  /*!< Specifies the ERTC Time Seconds.              */
  u8 AMPM;     /*!< Specifies the ERTC AM/PM Time.                */
  u8 FMT;      /*!< Specifies the ERTC 12-hour or 24-hour Format. */
}ERTC_TimeTypeDef;

/**
  * @brief  ERTC Date structure definition
  */
typedef struct
{
  u8 WeekDay; /*!< Specifies the ERTC Date WeekDay. */
  u8 Month;   /*!< Specifies the ERTC Date Month.   */
  u8 Day;     /*!< Specifies the ERTC Date Day.     */
  u8 Year;    /*!< Specifies the ERTC Date Year.    */
}ERTC_DateTypeDef;

/**
  * @brief  ERTC Init structures definition
  */
typedef struct
{
  u8  AsynchPrediv;      /*!< Specifies the ERTC Asynchronous Predivider value. */
  u16 SynchPrediv;       /*!< Specifies the ERTC Synchronous Predivider value.  */
  ERTC_DateTypeDef Date;
  ERTC_TimeTypeDef Time;
}ERTC_InitTypeDef;

/**
  * @brief  ERTC Alarm Mask structure definition
  */
typedef struct
{
  u8 AlarmMask_Minute;
  u8 AlarmMask_Second;
  u8 AlarmMask_Day;
  u8 AlarmMask_Hour;
}ERTC_AlarmMaskTypeDef;

/**
  * @brief  ERTC Alarm structure definition
  */
typedef struct
{
  ERTC_TimeTypeDef AlarmTime;      /*!< Specifies the ERTC Alarm Time members.          */
  ERTC_AlarmMaskTypeDef AlarmMask; /*!< Specifies the ERTC Alarm Masks.                 */
  u16 AlarmDateWeekDaySel;         /*!< Specifies the ERTC Alarm is on Date or WeekDay. */
  u8  AlarmDateWeekDay;            /*!< Specifies the ERTC Alarm Date/WeekDay.          */
}ERTC_AlarmTypeDef;

/**
 * @brief Selection of ERTC LSE startup mode
 */
typedef enum
{
  ERTC_LSESM_SLOW    = 0,
  ERTC_LSESM_MEDIUM_SLOW,
  ERTC_LSESM_MEDIUM_FAST,
  ERTC_LSESM_SUPPER_FAST
} ERTC_LSESM_Enum;

/**
 * @brief Enumeration of ERTC HSE Prescaler Selection.
 */
typedef enum
{
  ERTC_HSE_DIV32 = 0x0,
  ERTC_HSE_DIV16 = 0x4,
  ERTC_HSE_DIV8  = 0x8,
  ERTC_HSE_DIV4  = 0xC,
} ERTC_HSEDIV_Enum;

/**
 * @brief Event selection of RTC output
 */
typedef enum
{
  ERTC_ROES_ALARM  = 0x0000,
  ERTC_ROES_WAKEUP = 0x1000,
  ERTC_ROES_SPRE   = 0x2000,
  ERTC_ROES_APRE   = 0x3000,
} ERTC_ROES_Enum;

/**
 * @brief Waveform mode of RTC output
 */
typedef enum
{
  ERTC_ROWM_TOGGLE = 0x0000,
  ERTC_ROWM_PULSE  = 0x0400,
  ERTC_ROWM_LEVEL  = 0x0800
} ERTC_ROWM_Enum;

/**
 * @brief Active polarity of RTC output
 */
typedef enum
{
  ERTC_ROAP_HIGH = 0x0000,
  ERTC_ROAP_LOW  = 0x4000
} ERTC_ROAP_Enum;

/**
 * @brief Selection of ERTC clock source
 */
typedef enum
{
  ERTC_SRC_NOCLOCK   = 0x00,
  ERTC_SRC_LSI       = 0x02,
  ERTC_SRC_LSE       = 0x04,
  ERTC_SRC_HSE_DIV32 = 0x06
} ERTC_SRC_Enum;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup ERTC_Exported_Constants ERTC exported constants
  * @{
  */
#define ERTC_UNPROTECT_KEY                        (0x5FA0)

/* Definitions of ERTC Hour Formats                                                                         */
#define ERTC_HOURFORMAT_MASK                      ((u8)0x40)
#define ERTC_HOURFORMAT_12                        ((u8)0x00)
#define ERTC_HOURFORMAT_24                        ((u8)0x40)

/* Definitions of ERTC AM PM                                                                                */
#define ERTC_AM                                   ((u8)0x00)
#define ERTC_PM                                   ((u8)0x40)

/* Definitions of ERTC WeekDay BCD                                                                          */
#define ERTC_WEEKDAY_MONDAY                       ((u8)0x01)
#define ERTC_WEEKDAY_TUESDAY                      ((u8)0x02)
#define ERTC_WEEKDAY_WEDNESDAY                    ((u8)0x03)
#define ERTC_WEEKDAY_THURSDAY                     ((u8)0x04)
#define ERTC_WEEKDAY_FRIDAY                       ((u8)0x05)
#define ERTC_WEEKDAY_SATURDAY                     ((u8)0x06)
#define ERTC_WEEKDAY_SUNDAY                       ((u8)0x07)

/* Definitions of ERTC AlarmDate WeekDay Selection                                                          */
#define ERTC_ALARMSEL_DATE                        ((u16)0x0000)
#define ERTC_ALARMSEL_WEEKDAY                     ((u16)0x4000)

/* Definitions of ERTC Alarm Sub Seconds Masks                                                              */
#define ERTC_ALARM_SUBSECOND_MASK_ALL             ((u8)0x00)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_1          ((u8)0x01)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_2          ((u8)0x02)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_3          ((u8)0x03)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_4          ((u8)0x04)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_5          ((u8)0x05)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_6          ((u8)0x06)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_7          ((u8)0x07)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_8          ((u8)0x08)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_9          ((u8)0x09)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_10         ((u8)0x0A)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_11         ((u8)0x0B)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_12         ((u8)0x0C)
#define ERTC_ALARM_SUBSECOND_MASK_SS14_13         ((u8)0x0D)
#define ERTC_ALARM_SUBSECOND_MASK_SS14            ((u8)0x0E)
#define ERTC_ALARM_SUBSECOND_MASK_NONE            ((u8)0x0F)

/* Definitions of Wakeup_Timer                                                                              */
#define ERTC_WUP_TM_ERTC_DIV16                    ((u8)0x00)
#define ERTC_WUP_TM_ERTC_DIV8                     ((u8)0x01)
#define ERTC_WUP_TM_ERTC_DIV4                     ((u8)0x02)
#define ERTC_WUP_TM_ERTC_DIV2                     ((u8)0x03)
#define ERTC_WUP_TM_SPRE                          ((u8)0x04)
#define ERTC_WUP_TM_SPRE_EXT                      ((u8)0x06)

/* Definitions of ERTC Calib Period                                                                         */
#define ERTC_CALIB_PERIOD_32                      ((u16)0x0000)
#define ERTC_CALIB_PERIOD_16                      ((u16)0x1000)
#define ERTC_CALIB_PERIOD_8                       ((u16)0x2000)

/* Definitions of ERTC Calib Plus pulses                                                                    */
#define ERTC_CALIB_ADD_PULSES                     ((u16)0x0000)
#define ERTC_CALIB_MASK_PULSES                    ((u16)0x0100)

/* Definitions of ERTC Shift Sign Parameter                                                                 */
#define ERTC_SHIFT_SIGN_ADD                       0
#define ERTC_SHIFT_SIGN_SUB                       1

/* Definitions of ERTC wakeup source Selection                                                              */
#define ERTC_WAKEUP_ALR                           0x00002000
#define ERTC_WAKEUP_WUT                           0x00004000

/* Definitions of ERTC flags                                                                                */
#define ERTC_FLAG_INITF                           0x00000001
#define ERTC_FLAG_CRSF                            0x00000002
#define ERTC_FLAG_SHPF                            0x00000008
#define ERTC_FLAG_ALRWF                           0x00000010
#define ERTC_FLAG_RTCOF                           0x00000020
#define ERTC_FLAG_ALRF                            0x00000100
#define ERTC_FLAG_TSF                             0x00000200
#define ERTC_FLAG_TSOVF                           0x00000400
#define ERTC_FLAG_WUTF                            0x00001000
#define ERTC_FLAG_WUTWF                           0x00002000

/* Definitions of ERTC Interrupts                                                                           */
#define ERTC_INT_ALR                              0x00000100
#define ERTC_INT_CRS                              0x00000400
#define ERTC_INT_WUT                              0x00001000

/* Definitions of Timestamp Event Source                                                                    */
#define ERTC_TS_WAKEUP0_EVT                       0x00000000
#define ERTC_TS_WAKEUP1_EVT                       0x00004000

/**
 * @brief Used to check parameter of the ERTC.
 */
#define IS_ERTC_HOUR_FORMAT(FORMAT)   (((FORMAT) == ERTC_HOURFORMAT_12) || ((FORMAT) == ERTC_HOURFORMAT_24))

#define IS_ERTC_ASYNCH_PREDIV(PREDIV) ((PREDIV) <= 0x7F)

#define IS_ERTC_SYNCH_PREDIV(PREDIV)  ((PREDIV) <= 0x7FFF)

#define IS_ERTC_HOUR12(HOUR)          (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_ERTC_HOUR24(HOUR)          ((HOUR) <= 23)
#define IS_ERTC_MINUTES(MINUTES)      ((MINUTES) <= 59)
#define IS_ERTC_SECONDS(SECONDS)      ((SECONDS) <= 59)

#define IS_ERTC_AMPM(PM)              (((PM) == ERTC_AM) || ((PM) == ERTC_PM))

#define IS_ERTC_YEAR(YEAR)            ((YEAR)  <= 99)

#define IS_ERTC_MONTH(MONTH)          (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_ERTC_DATE(DATE)            (((DATE) >= 1) && ((DATE) <= 31))

#define IS_ERTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == ERTC_WEEKDAY_MONDAY)    || \
                                  ((WEEKDAY) == ERTC_WEEKDAY_TUESDAY)   || \
                                  ((WEEKDAY) == ERTC_WEEKDAY_WEDNESDAY) || \
                                  ((WEEKDAY) == ERTC_WEEKDAY_THURSDAY)  || \
                                  ((WEEKDAY) == ERTC_WEEKDAY_FRIDAY)    || \
                                  ((WEEKDAY) == ERTC_WEEKDAY_SATURDAY)  || \
                                  ((WEEKDAY) == ERTC_WEEKDAY_SUNDAY))

#define IS_ERTC_ALARM_DATE_WEEKDAY_DATE(DATE) (((DATE) > 0) && ((DATE) <= 31))
#define IS_ERTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == ERTC_WEEKDAY_MONDAY)    || \
                                                     ((WEEKDAY) == ERTC_WEEKDAY_TUESDAY)   || \
                                                     ((WEEKDAY) == ERTC_WEEKDAY_WEDNESDAY) || \
                                                     ((WEEKDAY) == ERTC_WEEKDAY_THURSDAY)  || \
                                                     ((WEEKDAY) == ERTC_WEEKDAY_FRIDAY)    || \
                                                     ((WEEKDAY) == ERTC_WEEKDAY_SATURDAY)  || \
                                                     ((WEEKDAY) == ERTC_WEEKDAY_SUNDAY))

#define IS_ERTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == ERTC_ALARMSEL_DATE) || \
                                             ((SEL) == ERTC_ALARMSEL_WEEKDAY))

#define IS_ERTC_ALARM_SUB_SECOND_MASK(MASK) (((MASK) == ERTC_ALARM_SUBSECOND_MASK_ALL)     || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_1)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_2)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_3)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_4)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_5)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_6)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_7)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_8)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_9)  || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_10) || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_11) || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_12) || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14_13) || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_SS14)    || \
                                             ((MASK) == ERTC_ALARM_SUBSECOND_MASK_NONE))

#define IS_ERTC_LSESM(x) ((x == ERTC_LSESM_SLOW) || (x == ERTC_LSESM_MEDIUM_SLOW) || (x == ERTC_LSESM_MEDIUM_FAST) ||(x == ERTC_LSESM_SUPPER_FAST))

#define IS_ERTC_HSE_DIV(DIV) (((DIV) == ERTC_HSE_DIV32) || \
                              ((DIV) == ERTC_HSE_DIV16) || \
                              ((DIV) == ERTC_HSE_DIV8 ) || \
                              ((DIV) == ERTC_HSE_DIV4 ))

#define IS_ERTC_CLOCK_SRC(SOURCE) (((SOURCE) == ERTC_SRC_NOCLOCK) || \
                                   ((SOURCE) == ERTC_SRC_LSI)     || \
                                   ((SOURCE) == ERTC_SRC_LSE)     || \
                                   ((SOURCE) == ERTC_SRC_HSE_DIV32))

#define IS_ERTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == ERTC_WUP_TM_ERTC_DIV16) || \
                                     ((CLOCK) == ERTC_WUP_TM_ERTC_DIV8)  || \
                                     ((CLOCK) == ERTC_WUP_TM_ERTC_DIV4)  || \
                                     ((CLOCK) == ERTC_WUP_TM_ERTC_DIV2)  || \
                                     ((CLOCK) == ERTC_WUP_TM_SPRE)       || \
                                     ((CLOCK) == ERTC_WUP_TM_SPRE_EXT))

#define IS_ERTC_WAKEUP_COUNTER(COUNTER) ((COUNTER) <= 0xFFFF)

#define IS_ERTC_OUTPUT(OUTPUT) (((OUTPUT) == ERTC_ROES_ALARM)  || \
                                ((OUTPUT) == ERTC_ROES_WAKEUP) || \
                                ((OUTPUT) == ERTC_ROES_SPRE)   || \
                                ((OUTPUT) == ERTC_ROES_APRE))

#define IS_ERTC_OUTPUT_MODE(MODE) (((MODE) == ERTC_ROWM_TOGGLE) || \
                                   ((MODE) == ERTC_ROWM_PULSE)  || \
                                   ((MODE) == ERTC_ROWM_LEVEL))

#define IS_ERTC_OUTPUT_POL(POL)  (((POL) == ERTC_ROAP_HIGH) ||  \
                                  ((POL) == ERTC_ROAP_LOW))

#define IS_ERTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= 0x00007FFF)

#define IS_ERTC_CALIB_PERIOD(PERIOD) (((PERIOD) == ERTC_CALIB_PERIOD_32) || \
                                      ((PERIOD) == ERTC_CALIB_PERIOD_16) || \
                                      ((PERIOD) == ERTC_CALIB_PERIOD_8))

#define IS_ERTC_CALIB_PLUS(PLUS) (((PLUS) == ERTC_CALIB_ADD_PULSES) || \
                                  ((PLUS) == ERTC_CALIB_MASK_PULSES))

#define IS_ERTC_CALIB_VALUE(VALUE) ((VALUE) <= 0x000000FF)

#define IS_ERTC_SHIFT_SIGN(SEL) (((SEL) == ERTC_SHIFT_SIGN_ADD) || \
                                 ((SEL) == ERTC_SHIFT_SIGN_SUB))

#define IS_ERTC_SHIFT_VALUE(FS) ((FS) <= 0x00007FFF)

#define IS_ERTC_WAKEUP(SOURCE) (((SOURCE) == ERTC_WAKEUP_ALR) || \
                                ((SOURCE) == ERTC_WAKEUP_WUT))

#define IS_ERTC_GET_FLAG(FLAG) (((FLAG) == ERTC_FLAG_INITF) || ((FLAG) == ERTC_FLAG_CRSF)   || \
                                ((FLAG) == ERTC_FLAG_SHPF)  || ((FLAG) == ERTC_FLAG_ALRWF)  || \
                                ((FLAG) == ERTC_FLAG_RTCOF) || ((FLAG) == ERTC_FLAG_ALRF)   || \
                                ((FLAG) == ERTC_FLAG_TSF)   || ((FLAG) == ERTC_FLAG_TSOVF)  || \
                                ((FLAG) == ERTC_FLAG_WUTF)  || ((FLAG) == ERTC_FLAG_WUTWF))

#define IS_ERTC_CLEAR_FLAG(FLAG) ((FLAG) != RESET)

#define IS_ERTC_CONFIG_INT(INT) ((INT == ERTC_INT_ALR) || (INT == ERTC_INT_CRS) || (INT == ERTC_INT_WUT))

#define IS_ERTC_TS_EVT(FLAG) (((FLAG) == ERTC_TS_WAKEUP0_EVT) || ((FLAG) == ERTC_TS_WAKEUP1_EVT))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup ERTC_Exported_Functions ERTC exported functions
  * @{
  */
void ERTC_DeInit(void);
void ERTC_InitBCD(ERTC_InitTypeDef* ERTC_InitStruct);
void ERTC_Init(ERTC_InitTypeDef* ERTC_InitStruct);
void ERTC_StructInit(ERTC_InitTypeDef* ERTC_InitStruct);
void ERTC_Cmd(ControlStatus NewState);
void ERTC_SetUnProtectKey(u16 uUnProtectKey);
void ERTC_WriteProtectionCmd(ControlStatus NewState);

void ERTC_ClockSourceConfig(ERTC_SRC_Enum Source);
void ERTC_LSESMConfig(ERTC_LSESM_Enum Mode);
void ERTC_LSECmd(ControlStatus NewState);
void ERTC_LSEDIVConfig(ERTC_HSEDIV_Enum Div);

void ERTC_IntConfig(u32 ERTC_INT_x, ControlStatus NewState);
FlagStatus ERTC_GetFlagStatus(u32 ERTC_FLAG_x);
void ERTC_ClearFlag(u32 ERTC_FLAG_x);

void ERTC_SetTimeBCD(ERTC_TimeTypeDef* ERTC_TimeStruct);
void ERTC_SetDateBCD(ERTC_DateTypeDef* ERTC_DateStruct);
void ERTC_SetTime(ERTC_TimeTypeDef* ERTC_TimeStruct);
void ERTC_SetDate(ERTC_DateTypeDef* ERTC_DateStruct);
void ERTC_GetDateBCD(ERTC_DateTypeDef* ERTC_DateStruct);
void ERTC_GetTimeBCD(ERTC_TimeTypeDef* ERTC_TimeStruct);
void ERTC_GetDateTimeBCD(ERTC_DateTypeDef* ERTC_DateStruct, ERTC_TimeTypeDef* ERTC_TimeStruct);
void ERTC_GetDate(ERTC_DateTypeDef* ERTC_DateStruct);
void ERTC_GetTime(ERTC_TimeTypeDef* ERTC_TimeStruct);
void ERTC_GetDateTime(ERTC_DateTypeDef* ERTC_DateStruct, ERTC_TimeTypeDef* ERTC_TimeStruct);
u32 ERTC_GetSubSecond(void);
u32 ERTC_GetSubSecondms(void);
u32 ERTC_GetSubSecondus(void);

void ERTC_WakeupTimerClockConfig(u8 ERTC_WakeupClock);
void ERTC_SetWakeupTimerCompare(u32 Compare);
u32 ERTC_GetWakeupTimerCompare(void);
void ERTC_WakeupTimerCmd(ControlStatus NewState);
void ERTC_WakeupConfig(u32 ERTC_WAKEUP, ControlStatus NewState);

void ERTC_SetAlarmBCD(ERTC_AlarmTypeDef* ERTC_AlarmStruct);
void ERTC_SetAlarm(ERTC_AlarmTypeDef* ERTC_AlarmStruct);
void ERTC_AlarmSubSecondConfig(u16 ERTC_AlarmSubSecondValue, u8 ERTC_AlarmSubSecondMask);
void ERTC_AlarmCmd(ControlStatus NewState);

void ERTC_OutConfig(ERTC_ROWM_Enum WMode, ERTC_ROES_Enum EventSel, ERTC_ROAP_Enum Pol);
void ERTC_OutCmd(ControlStatus NewState);

void ERTC_CalibConfig(u16 ERTC_CalibPeriod, u16 ERTC_CalibPlusMask, u8 ERTC_CalibValue);
void ERTC_CalibCmd(ControlStatus NewState);

void ERTC_TimeStampCmd(ControlStatus NewState);
void ERTC_GetTimeStampBCD(ERTC_DateTypeDef* ERTC_StampDateStruct, ERTC_TimeTypeDef* ERTC_StampTimeStruct);
void ERTC_GetTimeStamp(ERTC_DateTypeDef* ERTC_StampDateStruct, ERTC_TimeTypeDef* ERTC_StampTimeStruct);
u32 ERTC_GetTimeStampSubSecond(void);
u32 ERTC_GetTimeStampSubSecondms(void);
u32 ERTC_GetTimeStampSubSecondus(void);
FlagStatus ERTC_GetTimestampEventSourceStatus(u32 ERTC_TS_EVT);

void ERTC_SynchroShiftConfig(u8 ERTC_ShiftSign, u16 ERTC_ShiftSubFS);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
