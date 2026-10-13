#ifndef SCN_STEP_HERO_GEAR_H
#define SCN_STEP_HERO_GEAR_H

#include "gobj/GearAnim.h"
#include "types.h"

namespace dynamics {
class Desc;
}

namespace g3d {
class ResFileAccessor;
}

namespace gobj {
class GearModel;
class GearModelDesc;
class NodeRepos;
}

namespace scn {
namespace step {

namespace chara {
class Effect;
}

namespace hero {

class MintGear;

class Gear {
public:
    void set(const char* path);
    void set(const char* path, const gobj::GearModelDesc& desc);
    void set(const g3d::ResFileAccessor& resFile, const gobj::GearModelDesc& desc, bool);
    void setAnim(const char* path, const gobj::GearAnimDesc& desc);
    void addDynamics(const dynamics::Desc& desc);
    void procDispose();
    void clear();
    void setVisibility(bool visible);
    void setNodeVisibility(u32 node, bool visible);
    void setSubAnim(u32 slot, u32 index, u32);
    void startSubAnim(u32 slot, bool loop);
    bool isValid() const;
    bool isVisible();
    bool isAnimExist() const;
    gobj::GearAnim& anim();
    chara::Effect& effect();
    chara::Effect& effectWarp();
    MintGear mint();
    const gobj::NodeRepos& nodes() const;
    gobj::GearModel& model();
    u32 defaultParentNodeIndex() const;

private:
    u8 _0[0x4BC];
};

}
}
}

#endif
