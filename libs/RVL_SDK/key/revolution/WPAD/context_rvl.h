#ifndef RVL_SDK_WPAD_CONTEXT_RVL_H
#define RVL_SDK_WPAD_CONTEXT_RVL_H

/* The SC part of the donor's src/revolution/WPAD/context_rvl.h, which is what
 * WUD is written against. This tree's SC headers describe the Bluetooth tables
 * with other member names, lack the table of complex device entries and the
 * game region, and declare the setters as returning nothing. Their versions are
 * renamed out of the way, so this header has to come before any other.
 */

#define SCBtDeviceInfo			SCBtDeviceInfo_
#define SCBtDeviceInfoArray		SCBtDeviceInfoArray_
#define SCGetBtDeviceInfoArray	SCGetBtDeviceInfoArray_
#define SCSetBtDeviceInfoArray	SCSetBtDeviceInfoArray_
#define SCSetWpadMotorMode		SCSetWpadMotorMode_
#define SCSetWpadSpeakerVolume	SCSetWpadSpeakerVolume_

#include <key/revolution/SC.h>
#include <key/revolution/NAND.h>

#undef SCBtDeviceInfo
#undef SCBtDeviceInfoArray
#undef SCGetBtDeviceInfoArray
#undef SCSetBtDeviceInfoArray
#undef SCSetWpadMotorMode
#undef SCSetWpadSpeakerVolume

#include <key/revolution/types.h>

#include <key/revolution/context_bte.h>

// OSTime, OSTick and the tick conversions
#include <key/revolution/WPADMem.h>

#if !defined(NDEBUG)
# define OSAssertMessage_FileLine(file_, line_, exp_, ...)		(void)((exp_) || (OSPanic(file_, line_, __VA_ARGS__), 0))
#else
# define OSAssertMessage_FileLine(file_, line_, exp_, ...)		((void)0)
#endif

// defined in terms of OSAssertMessage_FileLine
#define OSAssertMessage_Line(line_, exp_, ...)		OSAssertMessage_FileLine(__FILE__, line_, exp_, __VA_ARGS__)
#define OSAssert_Line(line_, exp_)		OSAssertMessage_FileLine(__FILE__, line_, exp_, "Failed assertion " #exp_)

// OSError
#define OSError_FileLine(file_, line_, ...)		OSPanic(file_, line_, __VA_ARGS__)

// defined in terms of OSError_FileLine
#define OSError_Line(line_, ...)		OSError_FileLine(__FILE__, line_, __VA_ARGS__)

#ifdef __cplusplus
	extern "C" {
#endif

typedef struct SCBtDeviceInfo // basic dev info?
{
	BD_ADDR					devAddr;	// size 0x06, offset 0x00
	struct small_dev_info	small;		// size 0x40, offset 0x06
} SCBtDeviceInfo; // size 0x46

typedef struct SCBtDeviceInfoArray
{
	u8				num;			// size 0x001, offset 0x000	/* name known from asserts */

	/* NOTE: contents of the devices member are actually
	 *
	 * SCBtDeviceInfo	registered[WUD_MAX_DEV_ENTRY_FOR_STD];
	 * SCBtDeviceInfo	active[WUD_MAX_CHANNELS];
	 *
	 * but functions in WUD act as if it's only one buffer (see
	 * __wudSecurityEventStackCallback, case BTA_DM_LINK_DOWN_EVT)
	 */
	SCBtDeviceInfo	devices[14];	// size 0x3d4, offset 0x001

	SCBtDeviceInfo	wbc;			// size 0x046, offset 0x3d5
	SCBtDeviceInfo	at_0x41b;		// size 0x046, offset 0x41b
} SCBtDeviceInfoArray; // size 0x461

typedef struct SCBtCmpDevInfo // complex dev info?
{
	BD_ADDR					devAddr;	// size 0x06, offset 0x00
	struct small_dev_info	small;		// size 0x40, offset 0x06
	LINK_KEY				linkKey;	// size 0x10, offset 0x30 // ? or just a buffer
} SCBtCmpDevInfo; // size 0x56

typedef struct SCBtCmpDevInfoArray
{
	u8				num;			// size 0x001, offset 0x000 /* name known from asserts */
	SCBtCmpDevInfo	devices[6];		// size 0x204, offset 0x001
} SCBtCmpDevInfoArray; // size 0x205

void SCGetBtDeviceInfoArray(SCBtDeviceInfoArray *array);
BOOL SCSetBtDeviceInfoArray(const SCBtDeviceInfoArray *array);
void SCGetBtCmpDevInfoArray(SCBtCmpDevInfoArray *array);
BOOL SCSetBtCmpDevInfoArray(const SCBtCmpDevInfoArray *array);
BOOL SCSetWpadMotorMode(u8 mode);
BOOL SCSetWpadSpeakerVolume(u8 vol);

typedef s8 SCProductGameRegion;
enum SCProductGameRegion_et
{
	SC_PRD_GAME_REG_JP,
	SC_PRD_GAME_REG_US,
	SC_PRD_GAME_REG_EU,
	SC_PRD_GAME_REG_DEBUG,

	SC_PRD_GAME_REG_KR,
	SC_PRD_GAME_REG_CN,

	SC_PRD_GAME_REG_MAX,
	SC_PRD_GAME_REG_NULL	= -1
};

SCProductGameRegion SCGetProductGameRegion(void);

// NAND, in the donor's names

// an enumeration in this tree, which a callback type does not convert from
#define NANDResult		s32

#define NAND_ESUCCESS	NAND_RESULT_OK
#define NAND_EFATAL		NAND_RESULT_FATAL_ERROR

#define NAND_OPEN_READ	NAND_ACCESS_READ
#define NAND_OPEN_WRITE	NAND_ACCESS_WRITE

#define NAND_SEEK_SET	NAND_SEEK_BEG

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_CONTEXT_RVL_H
