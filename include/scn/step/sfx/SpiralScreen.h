#ifndef SCN_STEP_SFX_SPIRALSCREEN_H
#define SCN_STEP_SFX_SPIRALSCREEN_H

#include "hel/common/Array.h"
#include "hel/math/Vector2.h"
#include "param/JITParam.h"
#include "scn/step/ostop/Flag.h"
#include "types.h"

namespace sfx {
class Manager;
}

namespace scn {
namespace step {

class Component;

namespace sfx {

class SpiralScreen {
public:
    struct Param {
        u32 _0;
        f32 _4;
        f32 _8;
        u32 _C;
    };

    SpiralScreen(Component& component, ::sfx::Manager& manager);
    ~SpiralScreen();

    void update();
    void draw() const;
    void startAnim(ostop::Flag flag);
    void startAnim(ostop::Flag flag, u32, f32, f32);
    void endAnim();
    void setCenter(const hel::math::Vector2& center);
    const Param& param() const;

private:
    Component& mComponent;
    ::sfx::Manager& mManager;
    param::JITParam mParam;
    bool mIsAnim;
    ostop::Flag mFlag;
    u32 _20;
    u32 _24;
    f32 _28;
    f32 _2C;
    hel::math::Vector2 mCenter;
    hel::common::Array<f32, 20> _38;
    hel::common::Array<f32, 20> _88;
    hel::common::Array<f32, 20> _D8;
    hel::common::Array<f32, 20> _128;
    mutable hel::common::Array<hel::common::Array<hel::math::Vector2, 40>, 20> _178;
    mutable hel::common::Array<hel::common::Array<hel::math::Vector2, 40>, 20> _1A78;
};

}}}  // namespace scn::step::sfx

#endif
