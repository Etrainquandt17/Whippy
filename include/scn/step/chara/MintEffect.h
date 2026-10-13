#ifndef SCN_STEP_CHARA_MINTEFFECT_H
#define SCN_STEP_CHARA_MINTEFFECT_H

#include "scn/step/chara/Effect.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// What a script holds as a "Scn.Step.Chara.Effect".
class MintEffect {
public:
    static void RegisterForce(Effect& obj);
    static void Unregister();
    static Effect& Obj();
    static void RequestP(u32 kind);
    static void RequestPS(u32 kind, f32 scale);
    static void RequestPD(u32 kind);
    static void RequestPDS(u32 kind, f32 scale);
    static void RequestN(u32 kind, u32 node);
    static void RequestNS(u32 kind, u32 node, f32 scale);
    static void RequestNO(u32 kind, u32 node);
    static void RequestNOS(u32 kind, u32 node, f32 scale);
    static void RequestND(u32 kind, u32 node);
    static void RequestNDS(u32 kind, u32 node, f32 scale);
    static void RequestNDO(u32 kind, u32 node);
    static void RequestNDOS(u32 kind, u32 node, f32 scale);
    static void Release();
    static void ReleaseAndVanish();
    static void RequestP(u32 kind, const hel::math::Vector3& pos);
    static void RequestP(u32 kind, const hel::math::Vector3& pos, f32 scale);
    static void RequestPD(u32 kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir);
    static void RequestPD(u32 kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir, f32 scale);
    static void RequestN(u32 kind, u32 node, f32 scale);
    static void RequestN(u32 kind, u32 node, const hel::math::Vector3& offset);
    static void RequestN(u32 kind, u32 node, const hel::math::Vector3& offset, f32 scale);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir, f32 scale);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset);
    static void RequestND(u32 kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset, f32 scale);

    void requestP(effect::Kind kind, const hel::math::Vector3& pos) const { mObj->requestP(kind, pos); }
    void requestP(effect::Kind kind, const hel::math::Vector3& pos, f32 scale) const { mObj->requestP(kind, pos, scale); }
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir) const { mObj->requestPD(kind, pos, dir); }
    void requestPD(effect::Kind kind, const hel::math::Vector3& pos, const hel::math::Direction3& dir, f32 scale) const { mObj->requestPD(kind, pos, dir, scale); }
    void requestN(effect::Kind kind, u32 node) const { mObj->requestN(kind, node); }
    void requestN(effect::Kind kind, u32 node, f32 scale) const { mObj->requestN(kind, node, scale); }
    void requestN(effect::Kind kind, u32 node, const hel::math::Vector3& offset) const { mObj->requestN(kind, node, offset); }
    void requestN(effect::Kind kind, u32 node, const hel::math::Vector3& offset, f32 scale) const { mObj->requestN(kind, node, offset, scale); }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir) const { mObj->requestND(kind, node, dir); }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, f32 scale) const { mObj->requestND(kind, node, dir, scale); }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset) const { mObj->requestND(kind, node, dir, offset); }
    void requestND(effect::Kind kind, u32 node, const hel::math::Direction3& dir, const hel::math::Vector3& offset, f32 scale) const { mObj->requestND(kind, node, dir, offset, scale); }
    void release() const { mObj->release(); }
    void releaseAndVanish() const { mObj->releaseAndVanish(); }

private:
    Effect* mObj;
};

}
}
}

#endif
