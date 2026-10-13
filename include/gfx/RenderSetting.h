#ifndef GFX_RENDERSETTING_H
#define GFX_RENDERSETTING_H

#include "hel/common/ExplicitSingleton.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace nrel {
namespace ezrender {
class ViewportSetting;
}}  // namespace nrel::ezrender

namespace nw4r {
namespace g3d {
class Camera;
}}  // namespace nw4r::g3d

namespace gfx {

class IDrawer;
class VISetting;

class RenderSetting : public hel::common::ExplicitSingleton<RenderSetting> {
public:
    enum Type {
        TYPE_NORMAL,
        TYPE_1,
        TYPE_AA,
    };

    class Rect {
    public:
        Rect(f32 left, f32 top, f32 width, f32 height);

        f32 mLeft;
        f32 mTop;
        f32 mWidth;
        f32 mHeight;
    };

    RenderSetting();
    ~RenderSetting();

    const _GXRenderModeObj* rmode() const;
    void render(IDrawer& drawer, void* xfb);
    void type(Type type);
    void setupG3DCamera(nw4r::g3d::Camera camera);
    void resetViewportValue();
    void setViewportValue(f32 left, f32 top, f32 width, f32 height);
    f32 getViewPortLeft();
    f32 getViewPortTop();
    f32 getViewPortWidth();
    f32 getViewPortHeight();
    nrel::ezrender::ViewportSetting nrelViewportSetting() const;
    void dirty();

private:
    void renderImpl(IDrawer& drawer, void* xfb);
    void reset();
    void beginNormal();
    void endNormal(void* xfb);
    void beginAATopHalf();
    void endAATopHalf(void* xfb);
    void beginAABottomHalf();
    void endAABottomHalf(void* xfb);

public:
    VISetting* mVISetting;
    Type mType;
    s32 mPass;
    bool mIsDirty;
    bool mIsViewportSet;
    Rect mViewport;
    Rect mScissor;
    void (*mCallback)(s32 pass);
};

}  // namespace gfx

#endif
