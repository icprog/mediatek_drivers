////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2014 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (??MStar Confidential Information??) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 *
 * @file    mstar_drv_common.h
 *
 * @brief   This file defines the interface of touch screen
 *
 * @version v2.3.0.0
 *
 */

#ifndef __MSTAR_DRV_COMMON_H__
#define __MSTAR_DRV_COMMON_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/earlysuspend.h>
#include <linux/i2c.h>
#include <linux/proc_fs.h>
#include <asm/irq.h>
#include <asm/io.h>
//#include "tpd_custom_msg2238_pixi4global.h"
/*--------------------------------------------------------------------------*/
/* TOUCH DEVICE DRIVER RELEASE VERSION                                      */
/*--------------------------------------------------------------------------*/

#define DEVICE_DRIVER_RELEASE_VERSION   ("2.3.0.0")


/*--------------------------------------------------------------------------*/
/* COMPILE OPTION DEFINITION                                                */
/*--------------------------------------------------------------------------*/

/*
 * Note.
 * The below compile option is used to enable the specific device driver code handling for distinct smart phone developer platform.
 * For running on Spreadtrum platform, please define the compile option CONFIG_TOUCH_DRIVER_RUN_ON_SPRD_PLATFORM.
 * For running on Qualcomm platform, please define the compile option CONFIG_TOUCH_DRIVER_RUN_ON_QCOM_PLATFORM.
 * For running on MediaTek platform, please define the compile option CONFIG_TOUCH_DRIVER_RUN_ON_MTK_PLATFORM.
 */
//#define CONFIG_TOUCH_DRIVER_RUN_ON_SPRD_PLATFORM
//#define CONFIG_TOUCH_DRIVER_RUN_ON_QCOM_PLATFORM
#define CONFIG_TOUCH_DRIVER_RUN_ON_MTK_PLATFORM

/*
 * Note.
 * The below compile option is used to enable the specific device driver code handling for distinct touch ic.
 * Please enable the compile option depends on the touch ic that customer project are using and disable the others.
 */
//#define CONFIG_ENABLE_CHIP_MSG21XXA
#define CONFIG_ENABLE_CHIP_MSG22XX
//#define CONFIG_ENABLE_CHIP_MSG26XXM

/*
 * Note.
 * The below compile option is used to enable the specific device driver code handling to make sure main board can supply power to touch ic for some specific BB chip of MTK(EX. MT6582)/SPRD(EX. SC7715)/QCOM(EX. MSM8610).
 * By default, this compile option is disabled.
 */
#define CONFIG_ENABLE_REGULATOR_POWER_ON

/*
 * Note.
 * The below compile option is used to distinguish different workqueue scheduling mechanism when firmware report finger touch to device driver by IRQ interrupt.
 * For MTK platform, there are two type of workqueue scheduling mechanism available.
 * Please refer to the related code which is enclosed by compile option CONFIG_USE_IRQ_INTERRUPT_FOR_MTK_PLATFORM in mstar_drv_platform_porting_layer.c for more detail.
 * This compile option is used for MTK platform only.
 * By default, this compile option is disabled.
 */

//#define CONFIG_USE_IRQ_INTERRUPT_FOR_MTK_PLATFORM

/*
 * Note.
 * The below compile option is used to apply DMA mode for read/write data between device driver and firmware by I2C.
 * The DMA mode is used to reslove I2C read/write 8 bytes limitation for specific MTK BB chip(EX. MT6589/MT6572/...)
 * This compile option is used for MTK platform only.
 * By default, this compile option is disabled.
 */
#define CONFIG_ENABLE_DMA_IIC

/*
 * Note.
 * The below compile option is used to enable the output log mechanism while touch device driver is running.
 * If this compile option is not defined, the function for output log will be disabled.
 * By default, this compile option is enabled.
 */
#define CONFIG_ENABLE_TOUCH_DRIVER_DEBUG

/*
 * Note.
 * The below compile option is used to enable the specific device driver code handling when touch panel support virtual key(EX. Menu, Home, Back, Search).
 * If this compile option is not defined, the function for virtual key handling will be disabled.
 * By default, this compile option is enabled.
 */
#define CONFIG_TP_HAVE_KEY  

/*
 * Note.
 * Since specific MTK BB chip report virtual key touch by using coordinate instead of key code, the below compile option is used to enable the code handling for reporting key with coordinate.
 * This compile option is used for MTK platform only.
 * By default, this compile option is disabled.
 */
#define CONFIG_ENABLE_REPORT_KEY_WITH_COORDINATE 

/*
 * Note.
 * The below compile option is used to enable debug mode data log for firmware.
 * By default, this compile option is disabled.
 */
//#define CONFIG_ENABLE_FIRMWARE_DATA_LOG

/*
 * Note.
 * The below compile option is used to enable gesture wakeup.
 * By default, this compile option is disabled.
 */
//#define CONFIG_ENABLE_GESTURE_WAKEUP

/*
 * Note.
 * The below compile option is used to enable phone level MP test handling.
 * By the way, phone level MP test is ready for MSG21XXA/MSG22XX(support Open Test&Short Test) and MSG26XXM(support Open Test only).
 * By default, this compile option is disabled.
 */
#define CONFIG_ENABLE_ITO_MP_TEST

/*
 * Note.
 * The below compile option is used to enable the specific short test item of 2R triangle pattern for self-capacitive touch ic.
 * This compile option is used for MSG21XXA/MSG22XX only.
 * Please enable the compile option if the ITO pattern is 2R triangle pattern for MSG21XXA/MSG22XX.
 * Please disable the compile option if the ITO pattern is H(horizontal) triangle pattern for MSG21XXA/MSG22XX.
 * By default, this compile option is enabled.
 */
#define CONFIG_ENABLE_MP_TEST_ITEM_FOR_2R_TRIANGLE

/*
 * Note.
 * The below compile option is used to change the permission of the sysfs virtual file system for CTS test.
 * If this compile option is enabled, the permission 0644 will be used. 
 * If this compile option is disabled, the permission 0777 will be used. 
 * By default, this compile option is disabled.
 */
//#define SYSFS_AUTHORITY_CHANGE_FOR_CTS_TEST

/*
 * Note.
 * If this compile option is not defined, the SW ID mechanism for updating firmware will be disabled.
 * By default, this compile option is disabled.
 */
#define CONFIG_UPDATE_FIRMWARE_BY_SW_ID

/*
 * Note.
 * If this compile option is defined, the update firmware bin file shall be stored in a two dimensional array format.
 * Else, the update firmware bin file shall be stored in an one dimensional array format.
 * Be careful, MSG22XX only support storing update firmware bin file in an one dimensional array format, it does not support two dimensional array format.
 * By default, this compile option is disabled.
 */
//#define CONFIG_UPDATE_FIRMWARE_BY_TWO_DIMENSIONAL_ARRAY 


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

#define u8   unsigned char
#define u16  unsigned short
#define u32  unsigned int
#define s8   signed char
#define s16  signed short
#define s32  signed int


#if defined(CONFIG_ENABLE_CHIP_MSG21XXA) || defined(CONFIG_ENABLE_CHIP_MSG26XXM)
#define SLAVE_I2C_ID_DBBUS         (0xC4>>1) //0x62 // for MSG21XX/MSG21XXA/MSG26XXM
#elif defined(CONFIG_ENABLE_CHIP_MSG22XX)
#define SLAVE_I2C_ID_DBBUS         (0xB2>>1) //0x59 // for MSG22XX
#endif
#define SLAVE_I2C_ID_DWI2C         (0x4C>>1) //0x26 


#define CHIP_TYPE_MSG21XX   (0x01) // EX. MSG2133
#define CHIP_TYPE_MSG21XXA  (0x02) // EX. MSG2133A/MSG2138A(Besides, use version to distinguish MSG2133A/MSG2138A, you may refer to _DrvFwCtrlUpdateFirmwareCash()) 
#define CHIP_TYPE_MSG26XXM  (0x03) // EX. MSG2633M
#define CHIP_TYPE_MSG22XX   (0x7A) // EX. MSG2238/MSG2256

#define PACKET_TYPE_TOOTH_PATTERN   (0x20)
#define PACKET_TYPE_GESTURE_WAKEUP  (0x50)

#define TOUCH_SCREEN_X_MIN   (0)
#define TOUCH_SCREEN_Y_MIN   (0)
/*
 * Note.
 * Please change the below touch screen resolution according to the touch panel that you are using.
 */
#define TOUCH_SCREEN_X_MAX   (480) //LCD_WIDTH
#define TOUCH_SCREEN_Y_MAX   (800) //LCD_HEIGHT
/*
 * Note.
 * Please do not change the below setting.
 */
#define TPD_WIDTH   (2048)
#define TPD_HEIGHT  (2048)


#define BIT0  (1<<0)  // 0x0001
#define BIT1  (1<<1)  // 0x0002
#define BIT2  (1<<2)  // 0x0004
#define BIT3  (1<<3)  // 0x0008
#define BIT4  (1<<4)  // 0x0010
#define BIT5  (1<<5)  // 0x0020
#define BIT6  (1<<6)  // 0x0040
#define BIT7  (1<<7)  // 0x0080
#define BIT8  (1<<8)  // 0x0100
#define BIT9  (1<<9)  // 0x0200
#define BIT10 (1<<10) // 0x0400
#define BIT11 (1<<11) // 0x0800
#define BIT12 (1<<12) // 0x1000
#define BIT13 (1<<13) // 0x2000
#define BIT14 (1<<14) // 0x4000
#define BIT15 (1<<15) // 0x8000


#define MAX_DEBUG_REGISTER_NUM     (10)


#ifdef SYSFS_AUTHORITY_CHANGE_FOR_CTS_TEST
#define SYSFS_AUTHORITY (0644)
#else
#define SYSFS_AUTHORITY (0777)
#endif

#ifdef CONFIG_ENABLE_GESTURE_WAKEUP
#define GESTURE_WAKEUP_MODE_DOUBLE_CLICK_FLAG     0x0001    //0000 0000 0000 0001
#define GESTURE_WAKEUP_MODE_UP_DIRECT_FLAG        0x0002    //0000 0000 0000 0010
#define GESTURE_WAKEUP_MODE_DOWN_DIRECT_FLAG      0x0004    //0000 0000 0000 0100
#define GESTURE_WAKEUP_MODE_LEFT_DIRECT_FLAG      0x0008    //0000 0000 0000 1000
#define GESTURE_WAKEUP_MODE_RIGHT_DIRECT_FLAG     0x0010    //0000 0000 0001 0000
#define GESTURE_WAKEUP_MODE_m_CHARACTER_FLAG      0x0020    //0000 0000 0010 0000
#define GESTURE_WAKEUP_MODE_W_CHARACTER_FLAG      0x0040    //0000 0000 0100 0000
#define GESTURE_WAKEUP_MODE_C_CHARACTER_FLAG      0x0080    //0000 0000 1000 0000
#define GESTURE_WAKEUP_MODE_e_CHARACTER_FLAG      0x0100    //0000 0001 0000 0000
#define GESTURE_WAKEUP_MODE_V_CHARACTER_FLAG      0x0200    //0000 0010 0000 0000
#define GESTURE_WAKEUP_MODE_O_CHARACTER_FLAG      0x0400    //0000 0100 0000 0000
#define GESTURE_WAKEUP_MODE_S_CHARACTER_FLAG      0x0800    //0000 1000 0000 0000
#define GESTURE_WAKEUP_MODE_Z_CHARACTER_FLAG      0x1000    //0001 0000 0000 0000

#define GESTURE_WAKEUP_PACKET_LENGTH    (6)
#endif //CONFIG_ENABLE_GESTURE_WAKEUP


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

#ifdef CONFIG_ENABLE_TOUCH_DRIVER_DEBUG
//#define DBG(fmt, arg...) pr_info(fmt, ##arg)
#define DBG(fmt, arg...) printk(fmt, ##arg)
#else
#define DBG(fmt, arg...)
#endif

/*--------------------------------------------------------------------------*/
/* DATA TYPE DEFINITION                                                     */
/*--------------------------------------------------------------------------*/

typedef enum
{
    EMEM_ALL = 0,
    EMEM_MAIN,
    EMEM_INFO
} EmemType_e;

typedef enum
{
    ITO_TEST_MODE_OPEN_TEST = 1,
    ITO_TEST_MODE_SHORT_TEST = 2
} ItoTestMode_e;

typedef enum
{
    ITO_TEST_OK = 0,
    ITO_TEST_FAIL,
    ITO_TEST_GET_TP_TYPE_ERROR,
    ITO_TEST_UNDEFINED_ERROR,
    ITO_TEST_UNDER_TESTING

} ItoTestResult_e;

typedef enum
{
    ADDRESS_MODE_8BIT = 0,
    ADDRESS_MODE_16BIT = 1
} AddressMode_e;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DECLARATION                                              */
/*--------------------------------------------------------------------------*/

extern u8 DrvCommonCalculateCheckSum(u8 *pMsg, u32 nLength);
extern u32 DrvCommonConvertCharToHexDigit(char *pCh, u32 nLength);
extern u32 DrvCommonCrcDoReflect(u32 nRef, s8 nCh);
extern u32 DrvCommonCrcGetValue(u32 nText, u32 nPrevCRC);
extern void DrvCommonCrcInitTable(void);

#ifdef CTP_PSENSOR_SUPPORT
extern int g2238ps_state;
extern int msg2238_tp_resume_flag;
extern int mstar2238_pls_opened;
#endif

#define MSG_TP_IC_NAME "MSG2238" //"msg21xxA" or "msg22xx" or "msg26xxM" /* Please define the mstar touch ic name based on the mutual-capacitive ic or self capacitive ic that you are using */
#define I2C_BUS_ID   (1)       // i2c bus id : 0 or 1
#define TPD_OK (0)

#define TPD_BUTTON_HEIGH        (60)
#define TPD_KEY_COUNT           3
#define TPD_KEYS                { KEY_BACK,KEY_HOMEPAGE,KEY_MENU}  // KEY_BACK,KEY_HOME,RECENTAPP,key 229   MENU,key 139   MENU,key 59    MENU
#define TPD_KEYS_DIM            {{60,870,50,TPD_BUTTON_HEIGH},{170,870,50,TPD_BUTTON_HEIGH},{300,870,50,TPD_BUTTON_HEIGH}}

#endif  /* __MSTAR_DRV_COMMON_H__ */
