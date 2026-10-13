#ifndef SCN_SUBGAME_GUNSHOOT_ENEMY_ANIMPARAM_H
#define SCN_SUBGAME_GUNSHOOT_ENEMY_ANIMPARAM_H

#include "scn/subgame/gunshoot/enemy/HitAttribute.h"
#include "scn/subgame/gunshoot/param/DamageAnimList.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

class AnimParam {
public:
    struct StepData {
        int _0;
        int _4[3];
        int _10;
    };

    struct AnimData {
        u32 _0;
        u32 _4;
        const char* _8;
        u8 _C[0x14];
    };

    AnimParam(const char* name, unsigned long);
    ~AnimParam();

    int getStepNum() const;
    const StepData& getStepData(int index) const;
    const AnimData& getAnimData(int index) const;
    const char* getDamageAnimName(HitAttribute attribute) const;
    int getDamagePlayListIndex() const;
    const char* getStunDamageModelAnimName() const;
    const char* getStunDamageMotionAnimName() const;
    const char* getClimaxExDamageModelAnimName() const;

private:
    u32 _0;
    u8 _4[0x6E0];
    param::DamageAnimList mDamageAnimList;
    StepData mStepData[10];
    AnimData mAnimData[41];
    int mStepNum;
    int _D14;
};

}}}}  // namespace scn::subgame::gunshoot::enemy

#endif
