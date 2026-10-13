#ifndef SCN_STEP_GIMMICK_EFFECT_H
#define SCN_STEP_GIMMICK_EFFECT_H

#include "scn/step/core/DrawLayerKind.h"
#include "scn/step/effect/Kind.h"
#include "types.h"

namespace g3d {
class NodeAccessor;
}

namespace hel {
namespace math {
class Vector3;
}
}

namespace effect {
class Requestor;
}

namespace scn {
namespace step {

class Component;

namespace gimmick {

class Effect {
public:
    Effect(Component& component);
    ~Effect();

    void requestP(effect::Kind kind, const hel::math::Vector3& pos, bool);
    void requestN(effect::Kind kind, const g3d::NodeAccessor& node, bool);
    void changeLayer(core::DrawLayerKind kind);
    ::effect::Requestor& native();
    void release();
    void releaseAndVanish();
    void requestPause();
    void requestUnpause();
    void procScreenIn();
    void procScreenOut();

private:
    u32 _0[0x39C / 4];
};

}
}
}

#endif
