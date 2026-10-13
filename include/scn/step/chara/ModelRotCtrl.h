#ifndef SCN_STEP_CHARA_MODELROTCTRL_H
#define SCN_STEP_CHARA_MODELROTCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: the members are unknown.
class ModelRotCtrl {
public:
    void setValid(bool valid);
    void resetRotTarget();
    void resetRotIntpRate();
    void resetRot();

    f32 getRotH() const;
    void initRotH(f32 rot);
    void setRotH(f32 rot);
    void setRotHTarget(f32 rot);
    void setRotHIntpRate(f32 rate);
    void setRotHIntoTarget();
    void setRotHTargetDefault(f32 rot);

    f32 getRotV() const;
    void initRotV(f32 rot);
    void setRotV(f32 rot);
    void setRotVTarget(f32 rot);
    void setRotVIntpRate(f32 rate);
    void setRotVIntoTarget();
    void setRotVTargetDefault(f32 rot);

    f32 getRotD() const;
    void initRotD(f32 rot);
    void setRotD(f32 rot);
    void setRotDTarget(f32 rot);
    void setRotDIntpRate(f32 rate);
    void setRotDIntoTarget();

    f32 calcChangedRot(f32 rot, bool isPlus, f32 delta);

    static const f32 ROT_H_TARGET_DEFAULT;
    static const f32 ROT_H_TARGET;
};

}
}
}

#endif
