#include "scn/step/chara/MintEffect.h"

#include "hel/common/PointerWrapper.h"
#include "hel/math/Direction3.h"
#include "hel/mint/AddOnMathDirection3.h"
#include "hel/mint/AddOnMathVector3.h"
#include "scn/step/chara/Effect.h"

using hel::common::PointerWrapper;
using hel::math::Direction3;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace chara {

namespace {

PointerWrapper<Effect> t_obj;

}

void MintEffect::RegisterForce(Effect& obj) {
    t_obj.set(obj);
}

void MintEffect::Unregister() {
    t_obj.reset();
}

Effect& MintEffect::Obj() {
    return t_obj.ref();
}

void MintEffect::RequestP(u32 kind) {
    t_obj->requestP(static_cast<effect::Kind>(kind), hel::mint::AddOnMathVector3::Get());
}

void MintEffect::RequestPS(u32 kind, f32 scale) {
    t_obj->requestP(static_cast<effect::Kind>(kind), hel::mint::AddOnMathVector3::Get(), scale);
}

void MintEffect::RequestPD(u32 kind) {
    t_obj->requestPD(static_cast<effect::Kind>(kind), hel::mint::AddOnMathVector3::Get(), hel::mint::AddOnMathDirection3::Get());
}

void MintEffect::RequestPDS(u32 kind, f32 scale) {
    t_obj->requestPD(static_cast<effect::Kind>(kind), hel::mint::AddOnMathVector3::Get(), hel::mint::AddOnMathDirection3::Get(), scale);
}

void MintEffect::RequestN(u32 kind, u32 node) {
    t_obj->requestN(static_cast<effect::Kind>(kind), node);
}

void MintEffect::RequestNS(u32 kind, u32 node, f32 scale) {
    t_obj->requestN(static_cast<effect::Kind>(kind), node, scale);
}

void MintEffect::RequestNO(u32 kind, u32 node) {
    t_obj->requestN(static_cast<effect::Kind>(kind), node, hel::mint::AddOnMathVector3::Get());
}

void MintEffect::RequestNOS(u32 kind, u32 node, f32 scale) {
    t_obj->requestN(static_cast<effect::Kind>(kind), node, hel::mint::AddOnMathVector3::Get(), scale);
}

void MintEffect::RequestND(u32 kind, u32 node) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, hel::mint::AddOnMathDirection3::Get());
}

void MintEffect::RequestNDS(u32 kind, u32 node, f32 scale) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, hel::mint::AddOnMathDirection3::Get(), scale);
}

void MintEffect::RequestNDO(u32 kind, u32 node) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, hel::mint::AddOnMathDirection3::Get(), hel::mint::AddOnMathVector3::Get());
}

void MintEffect::RequestNDOS(u32 kind, u32 node, f32 scale) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, hel::mint::AddOnMathDirection3::Get(), hel::mint::AddOnMathVector3::Get(), scale);
}

void MintEffect::Release() {
    t_obj->release();
}

void MintEffect::ReleaseAndVanish() {
    t_obj->releaseAndVanish();
}

void MintEffect::RequestP(u32 kind, const Vector3& pos) {
    t_obj->requestP(static_cast<effect::Kind>(kind), pos);
}

void MintEffect::RequestP(u32 kind, const Vector3& pos, f32 scale) {
    t_obj->requestP(static_cast<effect::Kind>(kind), pos, scale);
}

void MintEffect::RequestPD(u32 kind, const Vector3& pos, const Direction3& dir) {
    t_obj->requestPD(static_cast<effect::Kind>(kind), pos, dir);
}

void MintEffect::RequestPD(u32 kind, const Vector3& pos, const Direction3& dir, f32 scale) {
    t_obj->requestPD(static_cast<effect::Kind>(kind), pos, dir, scale);
}

void MintEffect::RequestN(u32 kind, u32 node, f32 scale) {
    t_obj->requestN(static_cast<effect::Kind>(kind), node, scale);
}

void MintEffect::RequestN(u32 kind, u32 node, const Vector3& offset) {
    t_obj->requestN(static_cast<effect::Kind>(kind), node, offset);
}

void MintEffect::RequestN(u32 kind, u32 node, const Vector3& offset, f32 scale) {
    t_obj->requestN(static_cast<effect::Kind>(kind), node, offset, scale);
}

void MintEffect::RequestND(u32 kind, u32 node, const Direction3& dir) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, dir);
}

void MintEffect::RequestND(u32 kind, u32 node, const Direction3& dir, f32 scale) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, dir, scale);
}

void MintEffect::RequestND(u32 kind, u32 node, const Direction3& dir, const Vector3& offset) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, dir, offset);
}

void MintEffect::RequestND(u32 kind, u32 node, const Direction3& dir, const Vector3& offset, f32 scale) {
    t_obj->requestND(static_cast<effect::Kind>(kind), node, dir, offset, scale);
}

}}}  // namespace scn::step::chara
