#ifndef SCN_STEP_ENEMY_NEEDLOUS_CUSTOM_H
#define SCN_STEP_ENEMY_NEEDLOUS_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "snd/SERequestor.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::needlous::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual void onDead();
    virtual void onProcFixPos();

    void updateMoveCount();
    bool isMaxMoveCountOver();
    void resetMoveCount(bool isTurn);
    void resetInitMoveCount();
    void setIdlingTurn(bool isIdlingTurn);
    void setAttack(bool isAttack);
    void runSE();
    bool isIdlingTurn();
    bool isAttack();
    void smoke();

private:
    u32 mSmokeFrame;
    bool mIsRunSE;
    bool mIsSEPlaying;
    bool mIsIdlingTurn;
    bool mIsAttack;
    snd::SERequestor mSE;
    u32 mMoveCount;
    u32 mMaxMoveCount;
    f32 mSpeed;
    f32 mAttackSpeed;
    f32 mCurSpeed;
};

}
}
}
}

#endif
