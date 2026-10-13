#ifndef SCN_STEP_HERO_INTERFERENCE_STATEHANG_H
#define SCN_STEP_HERO_INTERFERENCE_STATEHANG_H

#include "hel/math/Vector3.h"
#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace interference {

class StateHang : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateHang(Hero* hero);
    virtual ~StateHang();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();

private:
    void release();

    hel::math::Vector3 mConstraintPos;
    hel::math::Vector3 mRootPos;
    f32 mRate;
    f32 _24;
    bool _28;
};

}
}
}
}

#endif
