#include "gfx/RenderSetting.h"

#include "gfx/IDrawer.h"
#include "gfx/Utility.h"
#include "gfx/VISetting.h"
#include "nrel/ezrender/ViewportSetting.h"
#include "nw4r/g3d/g3d_camera.h"
#include "nw4r/g3d/g3d_state.h"
#include "revolution/gx/GXFrameBuf.h"
#include "revolution/gx/GXGeometry.h"
#include "revolution/gx/GXPixel.h"
#include "revolution/gx/GXTexture.h"
#include "revolution/gx/GXTransform.h"

namespace {

static const f32 VIEWPORT_NEAR = 0;

// The copy of the two lines above the bottom half goes here and is never read.
u32 garbage[640] __attribute__((aligned(32)));

void t_setCopyClear() {
    GXColor color = {128, 128, 128, 255};
    GXSetCopyClear(color, 0xFFFFFF);
}

}

namespace gfx {

RenderSetting::RenderSetting()
    : mVISetting(hel::common::ExplicitSingleton<VISetting>::object_)
    , mType(TYPE_NORMAL)
    , mPass(0)
    , mIsDirty(true)
    , mIsViewportSet(false)
    , mViewport(0.0f, 0.0f, rmode()->fbWidth, rmode()->xfbHeight)
    , mScissor(0.0f, 0.0f, rmode()->fbWidth, rmode()->xfbHeight)
    , mCallback(0) {
    SetInstance(*this);
}

RenderSetting::Rect::Rect(f32 left, f32 top, f32 width, f32 height)
    : mLeft(left)
    , mTop(top)
    , mWidth(width)
    , mHeight(height) {}

RenderSetting::~RenderSetting() {
    UnsetInstance();
}

const _GXRenderModeObj* RenderSetting::rmode() const {
    u32 no = mVISetting->mRenderModeNo;
    Type type = mType;
    switch (type) {
    case TYPE_AA:
        switch (no) {
        case VISetting::RENDER_MODE_NTSC_INT_4X3:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_INT_4X3_AA);
        case VISetting::RENDER_MODE_NTSC_PROG_4X3:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_PROG_4X3_AA);
        case VISetting::RENDER_MODE_NTSC_INT_16X9:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_INT_16X9_AA);
        case VISetting::RENDER_MODE_NTSC_PROG_16X9:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_PROG_16X9_AA);
        }
        break;
    case TYPE_NORMAL:
    case TYPE_1:
        switch (no) {
        case VISetting::RENDER_MODE_NTSC_INT_4X3_AA:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_INT_4X3);
        case VISetting::RENDER_MODE_NTSC_PROG_4X3_AA:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_PROG_4X3);
        case VISetting::RENDER_MODE_NTSC_INT_16X9_AA:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_INT_16X9);
        case VISetting::RENDER_MODE_NTSC_PROG_16X9_AA:
            return mVISetting->rmode(VISetting::RENDER_MODE_NTSC_PROG_16X9);
        }
        break;
    }
    return mVISetting->mRenderMode;
}

void RenderSetting::render(IDrawer& drawer, void* xfb) {
    nw4r::g3d::G3DState::SetRenderModeObj(*rmode());
    Rect viewport = Rect(0.0f, 0.0f, rmode()->fbWidth, rmode()->xfbHeight);
    mViewport.mLeft = viewport.mLeft;
    mViewport.mTop = viewport.mTop;
    mViewport.mWidth = viewport.mWidth;
    mViewport.mHeight = viewport.mHeight;
    GXSetViewport(mViewport.mLeft, mViewport.mTop, mViewport.mWidth, mViewport.mHeight, VIEWPORT_NEAR, 1.0f);
    GXInvalidateVtxCache();
    GXInvalidateTexAll();
    if (mIsDirty) {
        mIsDirty = false;
        reset();
        renderImpl(drawer, xfb);
    }
    renderImpl(drawer, xfb);
}

void RenderSetting::renderImpl(IDrawer& drawer, void* xfb) {
    switch (mType) {
    case TYPE_NORMAL:
    case TYPE_1:
        mPass = 0;
        beginNormal();
        drawer.drawerExecDraw();
        if (mCallback != 0) {
            mCallback(mPass);
        }
        endNormal(xfb);
        break;
    case TYPE_AA:
        mPass = 1;
        beginAATopHalf();
        drawer.drawerExecDraw();
        if (mCallback != 0) {
            mCallback(mPass);
        }
        endAATopHalf(xfb);
        mPass = 2;
        beginAABottomHalf();
        drawer.drawerExecDraw();
        if (mCallback != 0) {
            mCallback(mPass);
        }
        endAABottomHalf(xfb);
        break;
    }
}

void RenderSetting::type(Type type) {
    if (type == mType) {
        return;
    }
    mType = type;
    dirty();
}

void RenderSetting::setupG3DCamera(nw4r::g3d::Camera camera) {
    if (mIsViewportSet) {
        camera.SetViewport(mViewport.mLeft, mViewport.mTop, mViewport.mWidth, mViewport.mHeight);
        camera.SetScissor(mScissor.mLeft, mScissor.mTop, mScissor.mWidth, mScissor.mHeight);
        camera.SetScissorBoxOffset(0, 0);
        return;
    }
    switch (mPass) {
    case 0:
        camera.SetViewport(mViewport.mLeft, mViewport.mTop, mViewport.mWidth, mViewport.mHeight);
        camera.SetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
        camera.SetScissorBoxOffset(0, 0);
        break;
    case 1:
        camera.SetViewport(mViewport.mLeft, mViewport.mTop, mViewport.mWidth, mViewport.mHeight);
        camera.SetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
        camera.SetScissorBoxOffset(0, 0);
        break;
    case 2:
        camera.SetViewport(mViewport.mLeft, mViewport.mTop, mViewport.mWidth, mViewport.mHeight);
        camera.SetScissor(0, 226, rmode()->fbWidth, rmode()->efbHeight);
        camera.SetScissorBoxOffset(0, 226);
        break;
    }
}

void RenderSetting::resetViewportValue() {
    setViewportValue(0.0f, 0.0f, rmode()->fbWidth, rmode()->xfbHeight);
    mIsViewportSet = false;
}

void RenderSetting::setViewportValue(f32 left, f32 top, f32 width, f32 height) {
    mViewport.mLeft = mScissor.mLeft = left;
    mViewport.mTop = mScissor.mTop = top;
    mViewport.mWidth = mScissor.mWidth = width;
    mViewport.mHeight = mScissor.mHeight = height;
    GXSetViewport(mViewport.mLeft, mViewport.mTop, mViewport.mWidth, mViewport.mHeight, VIEWPORT_NEAR, 1.0f);
    GXSetScissor(mScissor.mLeft, mScissor.mTop, mScissor.mWidth, mScissor.mHeight);
    mIsViewportSet = true;
}

f32 RenderSetting::getViewPortLeft() {
    return mViewport.mLeft;
}

f32 RenderSetting::getViewPortTop() {
    return mViewport.mTop;
}

f32 RenderSetting::getViewPortWidth() {
    return mViewport.mWidth;
}

f32 RenderSetting::getViewPortHeight() {
    return mViewport.mHeight;
}

nrel::ezrender::ViewportSetting RenderSetting::nrelViewportSetting() const {
    return nrel::ezrender::ViewportSetting::create(mViewport.mLeft, mViewport.mTop, mViewport.mWidth, mViewport.mHeight, VIEWPORT_NEAR, 1.0f);
}

void RenderSetting::reset() {
    switch (mType) {
    case TYPE_NORMAL:
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
        GXSetCopyFilter(GX_FALSE, rmode()->sample_pattern, GX_TRUE, rmode()->vfilter);
        break;
    case TYPE_1:
        GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
        GXSetCopyFilter(GX_FALSE, rmode()->sample_pattern, GX_TRUE, rmode()->vfilter);
        break;
    case TYPE_AA:
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_FAR);
        GXSetCopyFilter(GX_TRUE, rmode()->sample_pattern, GX_TRUE, rmode()->vfilter);
        break;
    }
    Utility::SetZBufferRange(0.0f, 1.0f);
}

void RenderSetting::beginNormal() {
    GXSetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
    GXSetScissorBoxOffset(0, 0);
}

void RenderSetting::beginAATopHalf() {
    GXSetScissor(0, 0, rmode()->fbWidth, rmode()->efbHeight);
    GXSetScissorBoxOffset(0, 0);
}

void RenderSetting::beginAABottomHalf() {
    GXSetScissor(0, 226, rmode()->fbWidth, rmode()->efbHeight);
    GXSetScissorBoxOffset(0, 226);
}

void RenderSetting::endNormal(void* xfb) {
    t_setCopyClear();
    GXSetCopyClamp(static_cast<GXFBClamp>(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetDispCopySrc(0, 0, rmode()->fbWidth, rmode()->efbHeight);
    GXSetDispCopyDst(rmode()->fbWidth, rmode()->xfbHeight);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXCopyDisp(xfb, GX_TRUE);
}

void RenderSetting::endAATopHalf(void* xfb) {
    t_setCopyClear();
    GXSetCopyClamp(static_cast<GXFBClamp>(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetDispCopySrc(0, 0, rmode()->fbWidth, rmode()->efbHeight);
    GXSetDispCopyDst(rmode()->fbWidth, rmode()->efbHeight);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXCopyDisp(xfb, GX_TRUE);
}

void RenderSetting::endAABottomHalf(void* xfb) {
    t_setCopyClear();
    GXSetCopyClamp(GX_CLAMP_BOTTOM);
    GXSetDispCopySrc(0, 2, rmode()->fbWidth, 228);
    GXSetDispCopyDst(rmode()->fbWidth, rmode()->efbHeight);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXCopyDisp(static_cast<u8*>(xfb) + ((static_cast<u16>((rmode()->fbWidth + 15) & ~15) * 228) << 1), GX_TRUE);
    GXSetCopyClamp(static_cast<GXFBClamp>(GX_CLAMP_TOP | GX_CLAMP_BOTTOM));
    GXSetDispCopySrc(0, 0, rmode()->fbWidth, 2);
    GXCopyDisp(garbage, GX_TRUE);
}

void RenderSetting::dirty() {
    mIsDirty = true;
}

}  // namespace gfx
