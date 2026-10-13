#ifndef SCN_STEP_CHARA_EFFECT_H
#define SCN_STEP_CHARA_EFFECT_H

#include "scn/step/core/DrawLayerKind.h"
#include "scn/step/effect/DrawPriority.h"
#include "scn/step/effect/Kind.h"
#include "types.h"

namespace g3d {
class NodeAccessor;
}

namespace gobj {
class NodeRepos;
}

namespace hel {
namespace math {

class Direction3;
class Vector3;

}
}

namespace scn {
namespace step {

class Component;

namespace chara {

class MintEffect;

class Effect {
public:
    Effect(Component& component, effect::DrawPriority priority);
    Effect(Component& component, const gobj::NodeRepos& nodes, effect::DrawPriority priority);
    ~Effect();

    void release();
    void releaseAndVanish();
    void requestPause();
    void requestUnpause();
    void changeLayer(core::DrawLayerKind kind);

    void requestP(effect::Kind kind, const hel::math::Vector3& pos);
    void requestP(effect::Kind kind, const hel::math::Vector3& pos, f32 scale);
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir);
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir, f32 scale);
    void requestN(effect::Kind kind, u32 node);
    void requestN(effect::Kind kind, u32 node, f32 scale);
    void requestN(effect::Kind kind, u32 node, const hel::math::Vector3& offset);
    void requestN(effect::Kind kind, u32 node, const hel::math::Vector3& offset, f32 scale);
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir);
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, f32 scale);
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset);
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset, f32 scale);
    MintEffect mint();
    void requestN(effect::Kind kind, const g3d::NodeAccessor& node);
    void requestN(effect::Kind kind, const g3d::NodeAccessor& node, f32 scale);
    void requestN(effect::Kind kind, const g3d::NodeAccessor& node, const hel::math::Vector3& offset);
    void requestN(effect::Kind kind, const g3d::NodeAccessor& node, const hel::math::Vector3& offset, f32 scale);
    void requestND(effect::Kind kind, const g3d::NodeAccessor& node, const hel::math::Direction3& dir);
    void requestND(effect::Kind kind, const g3d::NodeAccessor& node, const hel::math::Direction3& dir, f32 scale);
    void requestND(effect::Kind kind, const g3d::NodeAccessor& node, const hel::math::Direction3& dir, const hel::math::Vector3& offset);
    void requestND(effect::Kind kind, const g3d::NodeAccessor& node, const hel::math::Direction3& dir, const hel::math::Vector3& offset, f32 scale);

private:
    u32 _0[0x28 / 4];
};

}
}
}

#endif
