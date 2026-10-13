#ifndef HBM_CONTEXT_RVL_H
#define HBM_CONTEXT_RVL_H


#include <key/revolution/MEM.h>
#include <key/revolution/ARC.h>
#include <key/revolution/AX.h>
#include <key/revolution/GX.h>
#include <key/revolution/KPAD.h>
#include <key/revolution/SC.h>
#include <key/revolution/WPAD.h>
#include <key/revolution/OS.h>

#define OSGetAlarmUserDataAny(type_, alarm_)	\
	((type_)(OSGetAlarmUserData(alarm_)))

#define OSSetAlarmUserDataAny(alarm_, data_)	\
	OSSetAlarmUserData(alarm_, (void *)(data_))

#if !defined(NDEBUG)
# define OSAssertMessage_FileLine(file_, line_, exp_, ...)	\
	(void)((exp_) || (OSPanic(file_, line_, __VA_ARGS__), 0))
#else
# define OSAssertMessage_FileLine(file_, line_, exp_, ...)	\
	((void)0)
#endif

// defined in terms of OSAssertMessage_FileLine
#define OSAssertMessage_Line(line_, exp_, ...)	\
	OSAssertMessage_FileLine(__FILE__, line_, exp_, __VA_ARGS__)
#define OSAssert_Line(line_, exp_)	\
	OSAssertMessage_FileLine(__FILE__, line_, exp_, "Failed assertion " #exp_)

typedef s64 OSTime;

typedef u32 AXVPBSyncFlags;
enum AXVPBSyncFlags_et
{
	AX_VPB_SYNC_FLAG_SRC_TYPE				= 1 <<  0,
	AX_VPB_SYNC_FLAG_MIXER_CTRL				= 1 <<  1,
	AX_VPB_SYNC_FLAG_STATE					= 1 <<  2,
	AX_VPB_SYNC_FLAG_TYPE					= 1 <<  3,
	AX_VPB_SYNC_FLAG_MIX					= 1 <<  4,
	AX_VPB_SYNC_FLAG_ITD					= 1 <<  5,
	AX_VPB_SYNC_FLAG_ITD_TARGET				= 1 <<  6,
	AX_VPB_SYNC_FLAG_DPOP					= 1 <<  7,
	AX_VPB_SYNC_FLAG_VE						= 1 <<  8,
	AX_VPB_SYNC_FLAG_VE_DELTA				= 1 <<  9,
	AX_VPB_SYNC_FLAG_ADDR					= 1 << 10,
	AX_VPB_SYNC_FLAG_ADDR_LOOP_FLAG			= 1 << 11,
	AX_VPB_SYNC_FLAG_ADDR_LOOP_ADDR			= 1 << 12,
	AX_VPB_SYNC_FLAG_ADDR_END_ADDR			= 1 << 13,
	AX_VPB_SYNC_FLAG_ADDR_CURRENT_ADDR		= 1 << 14,
	AX_VPB_SYNC_FLAG_ADPCM					= 1 << 15,
	AX_VPB_SYNC_FLAG_SRC					= 1 << 16,
	AX_VPB_SYNC_FLAG_SRC_RATIO				= 1 << 17,
	AX_VPB_SYNC_FLAG_ADPCM_LOOP				= 1 << 18,
	AX_VPB_SYNC_FLAG_LPF					= 1 << 19,
	AX_VPB_SYNC_FLAG_LPF_COEFS				= 1 << 20,
	AX_VPB_SYNC_FLAG_BIQUAD					= 1 << 21,
	AX_VPB_SYNC_FLAG_BIQUAD_COEFS			= 1 << 22,
	AX_VPB_SYNC_FLAG_RMT_ON					= 1 << 23,
	AX_VPB_SYNC_FLAG_RMT_MIXER_CTRL			= 1 << 24,
	AX_VPB_SYNC_FLAG_RMT_MIX				= 1 << 25,
	AX_VPB_SYNC_FLAG_RMT_DPOP				= 1 << 26,
	AX_VPB_SYNC_FLAG_RMT_SRC				= 1 << 27,
	AX_VPB_SYNC_FLAG_RMT_IIR				= 1 << 28,
	AX_VPB_SYNC_FLAG_RMT_IIR_LPF_COEFS		= 1 << 29,
	AX_VPB_SYNC_FLAG_RMT_IIR_BIQUAD_COEFS	= 1 << 30,
	AX_VPB_SYNC_FLAG_FULL_PB				= 1 << 31
};

#define OS_MESSAGE_NO_FLAGS			0
#define OS_MESSAGE_FLAG_PERSISTENT	OS_MSG_BLOCKING
#define OS_THREAD_NO_FLAGS			0

#define OSSendMessageAny(msgQueue_, msg_, flags_)	\
	OSSendMessage(msgQueue_, (OSMessage)(msg_), flags_)
#define OSJamMessageAny(msgQueue_, msg_, flags_)	\
	OSJamMessage(msgQueue_, (OSMessage)(msg_), flags_)

#define AX_MIXER_CTRL_A_L			AX_MIXER_CTRL_AL
#define AX_MIXER_CTRL_A_R			AX_MIXER_CTRL_AR
#define AX_MIXER_CTRL_A_DELTA		AX_MIXER_CTRL_DELTA_A
#define AX_MIXER_CTRL_A_S			AX_MIXER_CTRL_AS
#define AX_MIXER_CTRL_A_DELTA_S		AX_MIXER_CTRL_DELTA_AS
#define AX_MIXER_CTRL_B_L			AX_MIXER_CTRL_BL
#define AX_MIXER_CTRL_B_R			AX_MIXER_CTRL_BR
#define AX_MIXER_CTRL_B_DELTA		AX_MIXER_CTRL_DELTA_B
#define AX_MIXER_CTRL_B_S			AX_MIXER_CTRL_BS
#define AX_MIXER_CTRL_B_DELTA_S		AX_MIXER_CTRL_DELTA_BS
#define AX_MIXER_CTRL_C_L			AX_MIXER_CTRL_CL
#define AX_MIXER_CTRL_C_R			AX_MIXER_CTRL_CR
#define AX_MIXER_CTRL_C_DELTA		AX_MIXER_CTRL_DELTA_C
#define AX_MIXER_CTRL_C_S			AX_MIXER_CTRL_CS
#define AX_MIXER_CTRL_C_DELTA_S		AX_MIXER_CTRL_DELTA_CS

#define GX_TEV_SCALE_0				GX_CS_SCALE_1
#define MTXIdentity					PSMTXIdentity

#ifdef __cplusplus
extern "C" {
#endif

BOOL AXIsInit(void);
BOOL AICheckInit(void);
void AIInit(void *stack);
void GXSetDispCopyGamma(int gamma);

#ifdef __cplusplus
}
#endif
#endif
