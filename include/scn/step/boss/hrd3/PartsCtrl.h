#ifndef SCN_STEP_BOSS_HRD3_PARTSCTRL_H
#define SCN_STEP_BOSS_HRD3_PARTSCTRL_H

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

// TODO: members.
class PartsCtrl {
public:
    // TODO: name the kinds.
    enum ResidentEffectKind {
        RESIDENT_EFFECT_KIND_0,
        RESIDENT_EFFECT_KIND_1,
        RESIDENT_EFFECT_KIND_2
    };

    void addResidentEffect(ResidentEffectKind kind);
    void deleteResidentEffect(ResidentEffectKind kind);
    bool isExistHipNeedle() const;
    bool isExistOutsideBody() const;
    f32 getMaxRotV() const;
    f32 getFallOverHeightOffset() const;
    void updateDrillScale();
    void growDrill();
    void shrinkDrill();
    void shrinkDrillForce();
    void startDrillSubAnim();
    void startDrillSubAnimFast();
    void stopDrillSubAnim();
};

}
}
}
}

#endif
