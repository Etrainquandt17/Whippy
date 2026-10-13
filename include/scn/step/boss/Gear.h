#ifndef SCN_STEP_BOSS_GEAR_H
#define SCN_STEP_BOSS_GEAR_H

namespace gobj {

class GearAnim;
struct GearAnimDesc;
class GearModelDesc;
class NodeRepos;

}

namespace scn {
namespace step {
namespace boss {

class Gear {
public:
    gobj::GearAnim& anim();
    void setVisibility(bool isVisible);
    const gobj::NodeRepos& nodes() const;
    void set(const char* name, const gobj::GearModelDesc& desc);
    void setAnim(const char* name, const gobj::GearAnimDesc& desc);
};

}
}
}

#endif
