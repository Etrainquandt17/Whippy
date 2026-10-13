#include "gfx/TPLTexturePlate.h"

#include "gfx/Utility.h"
#include "gfx/VISetting.h"
#include "hel/math/Vector2.h"
#include "revolution/gx/GXBump.h"
#include "revolution/gx/GXGeometry.h"
#include "revolution/gx/GXLighting.h"
#include "revolution/gx/GXTev.h"
#include "revolution/gx/GXTexture.h"
#include "revolution/gx/GXTransform.h"
#include "revolution/gx/GXVert.h"

namespace gfx {

TPLTexturePlate::TPLTexturePlate(const char* path)
    : mTexture(path)
    , mTexObj(mTexture.texObj())
    , mRect(0.5f * -GXGetTexObjWidth(&mTexObj), 0.5f * GXGetTexObjHeight(&mTexObj), 0.5f * GXGetTexObjWidth(&mTexObj),
            0.5f * -GXGetTexObjHeight(&mTexObj))
    , mPos()
    , mAlpha(255)
    , mIsInitialized(true) {
    PSMTXIdentity(mPos);
}

void TPLTexturePlate::setAlpha(u8 alpha) {
    mAlpha = alpha & 0xFF;
}

void TPLTexturePlate::drawForHomeButtonIcon() const {
    if (mIsInitialized) {
        const VISetting& setting = *hel::common::ExplicitSingleton<VISetting>::object_;
        Utility::SetupGXForLayout2D(setting._4, setting._6, 0.0f, 1.0f);
        drawCore();
    }
}

void TPLTexturePlate::drawCore() const {
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXLoadTexObj(&mTexObj, GX_TEXMAP0);
    setupTevRenderModePlane();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXLoadPosMtxImm(mPos, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(mRect.left, mRect.top);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition2f32(mRect.right, mRect.top);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition2f32(mRect.right, mRect.bottom);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition2f32(mRect.left, mRect.bottom);
    GXTexCoord2f32(0.0f, 1.0f);
    GXTexModeSync();
}

void TPLTexturePlate::setupTevRenderModePlane() const {
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXColor color = {0, 0, 0, mAlpha};
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXColor material = color;
    GXSetChanAmbColor(GX_COLOR0A0, material);
    GXSetChanMatColor(GX_COLOR0A0, material);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

void TPLTexturePlate::setPos(const hel::math::Vector2& pos) {
    PSMTXTrans(mPos, pos.x, pos.y, 0.0f);
}

}
