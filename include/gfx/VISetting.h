#ifndef GFX_VISETTING_H
#define GFX_VISETTING_H

#include "hel/common/ExplicitSingleton.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace gfx {

class VISetting : public hel::common::ExplicitSingleton<VISetting> {
public:
    enum RenderModeNo {
        RENDER_MODE_NTSC_INT_4X3,
        RENDER_MODE_NTSC_INT_4X3_AA,
        RENDER_MODE_NTSC_PROG_4X3,
        RENDER_MODE_NTSC_PROG_4X3_AA,
        RENDER_MODE_PAL50_INT_4X3,
        RENDER_MODE_PAL60_INT_4X3,
        RENDER_MODE_PAL60_PROG_4X3,
        RENDER_MODE_NTSC_INT_16X9,
        RENDER_MODE_NTSC_INT_16X9_AA,
        RENDER_MODE_NTSC_PROG_16X9,
        RENDER_MODE_NTSC_PROG_16X9_AA,
        RENDER_MODE_PAL50_INT_16X9,
        RENDER_MODE_PAL60_INT_16X9,
        RENDER_MODE_PAL60_PROG_16X9,
        RENDER_MODE_RECOMMEND,
    };

    VISetting();
    ~VISetting();

    RenderModeNo recommendRenderModeNo() const;
    void set(u32 renderModeNo);
    void set(const _GXRenderModeObj& rmode, u16, u16, bool);
    const _GXRenderModeObj* rmode(u32 renderModeNo) const;

    u32 fbSize() const { return static_cast<u16>((mRenderMode->fbWidth + 15) & ~15) * mRenderMode->xfbHeight * 2; }

    // TODO: an inline accessor reads _8, the last argument of set(); its name is not known.
    const _GXRenderModeObj* mRenderMode;
    u16 _4;
    u16 _6;
    bool _8;
    u32 mRenderModeNo;
};

}

#endif
