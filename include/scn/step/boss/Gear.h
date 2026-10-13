#ifndef SCN_STEP_BOSS_GEAR_H
#define SCN_STEP_BOSS_GEAR_H

namespace gobj {

class GearAnim;
struct GearAnimDesc;
class GearModel;
class GearModelDesc;
class NodeRepos;

}

namespace scn {
namespace step {
namespace chara {

class Effect;

}
namespace boss {

class Gear {
public:
    gobj::GearAnim& anim();
    void setVisibility(bool isVisible);
    const gobj::NodeRepos& nodes() const;
    void set(const char* name, const gobj::GearModelDesc& desc);
    void setAnim(const char* name, const gobj::GearAnimDesc& desc);
    gobj::GearModel& model();
    chara::Effect& effect();
};

}}}  // namespace scn::step::boss

#endif
