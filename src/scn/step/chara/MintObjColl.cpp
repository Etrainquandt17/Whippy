#include "scn/step/chara/MintObjColl.h"

#include "hel/common/PointerWrapper.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::PointerWrapper;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace chara {

namespace {

PointerWrapper<ObjColl> t_obj;

}

namespace MintObjColl {

void Register(ObjColl& obj) {
    t_obj.set(obj);
}

void Unregister(ObjColl&) {
    t_obj.reset();
}

void AddBodyColl(u32 id, f32 radius) {
    t_obj->addBodyColl(id, radius);
}

void AddBodyColl(u32 id, f32 radius, f32 x, f32 y) {
    t_obj->addBodyColl(id, radius, Vector2(x, y));
}

void AddBodyColl(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2) {
    t_obj->addBodyColl(id, radius, Vector2(x, y), Vector2(x2, y2));
}

void AddBodyColl(u32 id, f32 radius, const Vector2& offset) {
    t_obj->addBodyColl(id, radius, offset);
}

void AddBodyColl(u32 id, f32 radius, const Vector2& offset, const Vector2& offset2) {
    t_obj->addBodyColl(id, radius, offset, offset2);
}

void ClearBodyColl() {
    t_obj->clearBodyColl();
}

void AddAttack(u32 id, u32 attack, f32 radius) {
    t_obj->addAttack(id, attack, radius);
}

void AddAttack(u32 id, u32 attack, f32 radius, f32 x, f32 y) {
    t_obj->addAttack(id, attack, radius, Vector2(x, y));
}

void AddAttack(u32 id, u32 attack, f32 radius, f32 x, f32 y, f32 x2, f32 y2) {
    t_obj->addAttack(id, attack, radius, Vector2(x, y), Vector2(x2, y2));
}

void AddAttack(u32 id, u32 attack, f32 radius, f32 x, f32 y, f32 x2, f32 y2, bool flag) {
    t_obj->addAttack(id, attack, radius, Vector2(x, y), Vector2(x2, y2), flag);
}

void AddAttack(u32 id, u32 attack, f32 radius, const Vector2& offset) {
    t_obj->addAttack(id, attack, radius, offset);
}

void AddAttack(u32 id, u32 attack, f32 radius, const Vector2& offset, const Vector2& offset2) {
    t_obj->addAttack(id, attack, radius, offset, offset2);
}

void AddAttack(u32 id, u32 attack, f32 radius, const Vector2& offset, const Vector2& offset2, bool flag) {
    t_obj->addAttack(id, attack, radius, offset, offset2, flag);
}

void ClearAttack() {
    t_obj->clearAttack();
}

void ClearAttack(u32 id) {
    t_obj->clearAttack(id);
}

void SetAttackType(u32 id, u32 type) {
    t_obj->setAttackType(id, static_cast<ocoll::AttackType>(type));
}

void SetAttackCenter(u32 id, f32 x, f32 y) {
    t_obj->setAttackCenter(id, Vector2(x, y));
}

void RenewAttack() {
    t_obj->renewAttack();
}

void AddSearchHit(u32 id, f32 radius) {
    t_obj->addSearchHit(id, radius);
}

void AddSearchHit(u32 id, f32 radius, f32 x, f32 y) {
    t_obj->addSearchHit(id, radius, Vector2(x, y));
}

void AddSearchHit(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2) {
    t_obj->addSearchHit(id, radius, Vector2(x, y), Vector2(x2, y2));
}

void AddSearchHit(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2, bool flag) {
    t_obj->addSearchHit(id, radius, Vector2(x, y), Vector2(x2, y2), flag);
}

void AddSearchHit(u32 id, f32 radius, const Vector2& offset) {
    t_obj->addSearchHit(id, radius, offset);
}

void AddSearchHit(u32 id, f32 radius, const Vector2& offset, const Vector2& offset2) {
    t_obj->addSearchHit(id, radius, offset, offset2);
}

void AddSearchHit(u32 id, f32 radius, const Vector2& offset, const Vector2& offset2, bool flag) {
    t_obj->addSearchHit(id, radius, offset, offset2, flag);
}

void ClearSearchHit() {
    t_obj->clearSearchHit();
}

void SetSearchHitTeamXlu(u32 team) {
    t_obj->setSearchHitTeamXlu(team);
}

void AddSearchAttack(u32 id, f32 radius) {
    t_obj->addSearchAttack(id, radius);
}

void AddSearchAttack(u32 id, f32 radius, f32 x, f32 y) {
    t_obj->addSearchAttack(id, radius, Vector2(x, y));
}

void AddSearchAttack(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2) {
    t_obj->addSearchAttack(id, radius, Vector2(x, y), Vector2(x2, y2));
}

void AddSearchAttack(u32 id, f32 radius, f32 x, f32 y, f32 x2, f32 y2, bool flag) {
    t_obj->addSearchAttack(id, radius, Vector2(x, y), Vector2(x2, y2), flag);
}

void AddSearchAttack(u32 id, f32 radius, const Vector2& offset) {
    t_obj->addSearchAttack(id, radius, offset);
}

void AddSearchAttack(u32 id, f32 radius, const Vector2& offset, const Vector2& offset2) {
    t_obj->addSearchAttack(id, radius, offset, offset2);
}

void AddSearchAttack(u32 id, f32 radius, const Vector2& offset, const Vector2& offset2, bool flag) {
    t_obj->addSearchAttack(id, radius, offset, offset2, flag);
}

void ClearSearchAttack() {
    t_obj->clearSearchAttack();
}

bool IsSearchAttackCollide() {
    return t_obj->isSearchAttackCollide();
}

void SetBodyCollStateNormal() {
    t_obj->setBodyCollStateNormal();
}

void SetBodyCollStateInvincible() {
    t_obj->setBodyCollStateInvincible();
}

void SetBodyCollStateXlu() {
    t_obj->setBodyCollStateXlu();
}

void SetBodyCollStateHitOnly() {
    t_obj->setBodyCollStateHitOnly();
}

void SetBodyCollStateCaptureOnly() {
    t_obj->setBodyCollStateCaptureOnly();
}

}}}}  // namespace scn::step::chara::MintObjColl
