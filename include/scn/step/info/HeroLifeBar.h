#ifndef SCN_STEP_INFO_HEROLIFEBAR_H
#define SCN_STEP_INFO_HEROLIFEBAR_H

#include "types.h"

namespace lyt {
class PaneAccessor;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {
namespace info {

class HeroLifeBar {
public:
    HeroLifeBar(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);
    ~HeroLifeBar();

    void updateFrame(bool);
    void blank(bool isBlank);
    void setLength(f32 length);
    void set(f32 rate);
    f32 lifeBarRate() const;
    void damage(f32 rate, bool isPinch);
    void cure(f32 rate, bool isPinch, bool isInvincible);
    void normal();
    void pinch();
    void pinchWait();
    void invincibleStart();
    void invincibleLow();
    void invincibleEnd();
    void ignoreObjStop();

private:
    u32 _0[0x5B0 / 4];
};

}}}  // namespace scn::step::info

#endif
