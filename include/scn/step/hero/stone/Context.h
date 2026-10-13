#ifndef SCN_STEP_HERO_STONE_CONTEXT_H
#define SCN_STEP_HERO_STONE_CONTEXT_H

#include "hel/common/NonCopyable.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class GearNodeRandomChanger;

class Context : private hel::common::NonCopyable {
public:
    Context(GearNodeRandomChanger& nodeChanger);
    ~Context();

    void resetFlag();
    void setIsScrew(bool isScrew);
    void setIsRun(bool isRun);
    void incRotFrame();
    void setMaxRotFrame(u32 frame);
    void setRotAngle(f32 angle);
    void setRotEnable(bool isEnable);
    GearNodeRandomChanger& nodeChanger();
    bool isScrew() const;
    bool isRun() const;
    u32 getRotFrame() const;
    u32 getMaxRotFrame() const;
    f32 getRotAngle() const;
    bool isRotEnable() const;

private:
    GearNodeRandomChanger& mNodeChanger;
    bool mIsScrew;
    bool mIsRun;
    bool _6;
    u32 mRotFrame;
    u32 mMaxRotFrame;
    f32 mRotAngle;
    bool mIsRotEnable;
};

}
}
}
}

#endif
