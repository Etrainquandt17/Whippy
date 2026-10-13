#ifndef SCN_STEP_ENEMY_CAPPY_CUSTOM_H
#define SCN_STEP_ENEMY_CAPPY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();
    virtual void onCaptured();
    virtual void onDead();
    virtual void onProcFixPos();

    u32 throwCount() const;
    void setThrowCount(u32 count);
    bool cap() const;
    void setCap(bool cap);
    void setSearchHat(bool isSearch);
    void returnHat();
    void setValidTurn(bool isValid);
    bool isValidTurn();
    bool isLostHat();
    bool isCanHat();
    void enableCatch();
    void disableCatch();

private:
    bool mCap;
    bool mCanCatch;
    bool mIsValidTurn;
    u32 mThrowCount;
    bool mIsSearchHat;
    bool mIsLostHat;
    s32 mSearchHatFrame;
};

}
}
}
}

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::cappy::Custom>();

}
}

#endif
