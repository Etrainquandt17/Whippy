#ifndef SCN_STEP_ENEMY_LOWPERBULLET_VARIATIONKIND_H
#define SCN_STEP_ENEMY_LOWPERBULLET_VARIATIONKIND_H

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

// TODO: the other values, and confirm the names; these follow lowper's ShotBullet bindings.
enum VariationKind {
    VariationKind_Normal = 0,
    VariationKind_Homing = 4,
    VariationKind_Homing2 = 5,
    VariationKind_Still = 8,
};

}
}
}
}

#endif
