#include "gfx/VISetting.h"

#include "gfx/RenderSetting.h"
#include "revolution/gx/GXFrameBuf.h"
#include "revolution/sc.h"
#include "revolution/vi.h"

namespace gfx {

namespace {

struct RenderModeSet {
    _GXRenderModeObj rmode;
    u16 _3C;
    u16 _3E;
    bool _40;
};

const RenderModeSet NtscInt4x3 = {
    {0, 640, 456, 456, 25, 12, 670, 456, 1, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {7, 7, 12, 12, 12, 7, 7}},
    608,
    456,
    false,
};

const RenderModeSet NtscInt4x3AA = {
    {0, 640, 230, 456, 25, 12, 670, 456, 1, 0, 1,
     {{3, 2}, {9, 6}, {3, 10}, {3, 2}, {9, 6}, {3, 10}, {9, 2}, {3, 6}, {9, 10}, {9, 2}, {3, 6}, {9, 10}},
     {4, 8, 12, 16, 12, 8, 4}},
    608,
    456,
    false,
};

const RenderModeSet NtscProg4x3 = {
    {2, 640, 456, 456, 25, 12, 670, 456, 0, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {0, 0, 21, 22, 21, 0, 0}},
    608,
    456,
    false,
};

const RenderModeSet NtscProg4x3AA = {
    {2, 640, 230, 456, 25, 12, 670, 456, 0, 0, 1,
     {{3, 2}, {9, 6}, {3, 10}, {3, 2}, {9, 6}, {3, 10}, {9, 2}, {3, 6}, {9, 10}, {9, 2}, {3, 6}, {9, 10}},
     {4, 8, 12, 16, 12, 8, 4}},
    608,
    456,
    false,
};

const RenderModeSet Pal50Int4x3 = {
    {4, 640, 456, 542, 27, 16, 666, 542, 1, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {7, 7, 12, 12, 12, 7, 7}},
    608,
    456,
    false,
};

const RenderModeSet Pal60Int4x3 = {
    {20, 640, 456, 456, 25, 12, 670, 456, 1, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {7, 7, 12, 12, 12, 7, 7}},
    608,
    456,
    false,
};

const RenderModeSet Pal60Prog4x3 = {
    {22, 640, 456, 456, 25, 12, 670, 456, 0, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {0, 0, 21, 22, 21, 0, 0}},
    608,
    456,
    false,
};

const RenderModeSet NtscInt16x9 = {
    {0, 640, 456, 456, 17, 12, 686, 456, 1, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {7, 7, 12, 12, 12, 7, 7}},
    832,
    456,
    true,
};

const RenderModeSet NtscInt16x9AA = {
    {0, 640, 230, 456, 17, 12, 686, 456, 1, 0, 1,
     {{3, 2}, {9, 6}, {3, 10}, {3, 2}, {9, 6}, {3, 10}, {9, 2}, {3, 6}, {9, 10}, {9, 2}, {3, 6}, {9, 10}},
     {4, 8, 12, 16, 12, 8, 4}},
    832,
    456,
    true,
};

const RenderModeSet NtscProg16x9 = {
    {2, 640, 456, 456, 17, 12, 686, 456, 0, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {0, 0, 21, 22, 21, 0, 0}},
    832,
    456,
    true,
};

const RenderModeSet NtscProg16x9AA = {
    {2, 640, 230, 456, 17, 12, 686, 456, 0, 0, 1,
     {{3, 2}, {9, 6}, {3, 10}, {3, 2}, {9, 6}, {3, 10}, {9, 2}, {3, 6}, {9, 10}, {9, 2}, {3, 6}, {9, 10}},
     {4, 8, 12, 16, 12, 8, 4}},
    832,
    456,
    true,
};

const RenderModeSet Pal50Int16x9 = {
    {4, 640, 456, 542, 19, 16, 682, 542, 1, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {7, 7, 12, 12, 12, 7, 7}},
    832,
    456,
    true,
};

const RenderModeSet Pal60Int16x9 = {
    {20, 640, 456, 456, 17, 12, 686, 456, 1, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {7, 7, 12, 12, 12, 7, 7}},
    832,
    456,
    true,
};

const RenderModeSet Pal60Prog16x9 = {
    {22, 640, 456, 456, 17, 12, 686, 456, 0, 0, 0,
     {{6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}, {6, 6}},
     {0, 0, 21, 22, 21, 0, 0}},
    832,
    456,
    true,
};

const RenderModeSet* StandardRenderModeSets[14] = {
    &NtscInt4x3,
    &NtscInt4x3AA,
    &NtscProg4x3,
    &NtscProg4x3AA,
    &Pal50Int4x3,
    &Pal60Int4x3,
    &Pal60Prog4x3,
    &NtscInt16x9,
    &NtscInt16x9AA,
    &NtscProg16x9,
    &NtscProg16x9AA,
    &Pal50Int16x9,
    &Pal60Int16x9,
    &Pal60Prog16x9,
};

}

VISetting::VISetting()
    : mRenderMode(0)
    , _4(0)
    , _6(0)
    , _8(false)
    , mRenderModeNo(0) {
    SetInstance(*this);
    set(RENDER_MODE_RECOMMEND);
}

VISetting::~VISetting() {
    UnsetInstance();
}

VISetting::RenderModeNo VISetting::recommendRenderModeNo() const {
    u32 format = VIGetTvFormat();
    while (SCCheckStatus() != 0) {
    }
    bool progressive = SCGetProgressiveMode() == 1;
    bool rgb60 = SCGetEuRgb60Mode() == 1;
    bool is4x3 = SCGetAspectRatio() == 0;
    bool dtv = VIGetDTVStatus() == 1;
    bool ntsc = format != 1 && format != 5;
    if (dtv && progressive) {
        if (ntsc) {
            return is4x3 ? RENDER_MODE_NTSC_PROG_4X3 : RENDER_MODE_NTSC_PROG_16X9;
        } else {
            return is4x3 ? RENDER_MODE_PAL60_PROG_4X3 : RENDER_MODE_PAL60_PROG_16X9;
        }
    } else if (ntsc) {
        return is4x3 ? RENDER_MODE_NTSC_INT_4X3 : RENDER_MODE_NTSC_INT_16X9;
    } else if (rgb60) {
        return is4x3 ? RENDER_MODE_PAL60_INT_4X3 : RENDER_MODE_PAL60_INT_16X9;
    } else {
        return is4x3 ? RENDER_MODE_PAL50_INT_4X3 : RENDER_MODE_PAL50_INT_16X9;
    }
}

void VISetting::set(u32 renderModeNo) {
    if (renderModeNo == RENDER_MODE_RECOMMEND) {
        renderModeNo = recommendRenderModeNo();
    }
    if (hel::common::ExplicitSingleton<RenderSetting>::IsExist()) {
        if (hel::common::ExplicitSingleton<RenderSetting>::object_->mType == RenderSetting::TYPE_AA) {
            switch (renderModeNo) {
            case 0:
                renderModeNo = 1;
                break;
            case 2:
                renderModeNo = 3;
                break;
            case 7:
                renderModeNo = 8;
                break;
            case 9:
                renderModeNo = 10;
                break;
            }
        } else {
            switch (renderModeNo) {
            case 1:
                renderModeNo = 0;
                break;
            case 3:
                renderModeNo = 2;
                break;
            case 8:
                renderModeNo = 7;
                break;
            case 10:
                renderModeNo = 9;
                break;
            }
        }
    }
    const RenderModeSet* modeSet = StandardRenderModeSets[renderModeNo];
    set(modeSet->rmode, modeSet->_3C, modeSet->_3E, modeSet->_40);
    mRenderModeNo = renderModeNo;
}

void VISetting::set(const _GXRenderModeObj& rmode, u16 arg1, u16 arg2, bool arg3) {
    if (&rmode != mRenderMode) {
        mRenderMode = &rmode;
        _4 = arg1;
        _6 = arg2;
        _8 = arg3;
        VISetBlack(true);
        VIConfigure(&rmode);
        VIFlush();
        GXSetDispCopySrc(0, 0, rmode.fbWidth, rmode.efbHeight);
        GXSetDispCopyDst(rmode.fbWidth, rmode.xfbHeight);
        GXSetDispCopyYScale(1.0f);
        GXSetDispCopyGamma(GX_GM_1_0);
        VIWaitForRetrace();
        VIWaitForRetrace();
    }
}

const _GXRenderModeObj* VISetting::rmode(u32 renderModeNo) const {
    return &StandardRenderModeSets[renderModeNo]->rmode;
}

}
