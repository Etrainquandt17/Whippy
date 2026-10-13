#ifndef SCN_STEP_BOSS_ANGRY_H
#define SCN_STEP_BOSS_ANGRY_H

#include "hel/common/FixedString.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class Angry {
public:
    Angry(Boss& boss);
    ~Angry();

    bool check();
    bool isAngry() const;
    void setChangeBrain(const char* name);
    void setAngryHpRate(float rate);
    float getAngryHpRate() const;

private:
    Boss& mBoss;
    bool mIsAngry;
    float mAngryHpRate;
    bool mIsChangeBrain;
    hel::common::FixedString<128> mBrainName;
};

}}}  // namespace scn::step::boss

#endif
