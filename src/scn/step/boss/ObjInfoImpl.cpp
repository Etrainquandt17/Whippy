#include "scn/step/boss/ObjInfoImpl.h"

#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/debug/ObjInfoRepos.h"

namespace scn {
namespace step {
namespace boss {

ObjInfoImpl::ObjInfoImpl(Boss& boss) : mBoss(boss) {
    boss.comp().debugObjInfoRepos().registerObj(*this);
}

ObjInfoImpl::~ObjInfoImpl() {
    mBoss.comp().debugObjInfoRepos().unregisterObj(*this);
}

hel::common::FixedString<32> ObjInfoImpl::name() const {
    // "Boss" in Shift-JIS katakana.
    return hel::common::FixedString<32>("\x83\x7B\x83\x58");
}

const gobj::Anim& ObjInfoImpl::anim() const {
    return mBoss.model().anim();
}

const gobj::FootState& ObjInfoImpl::footState() const {
    return mBoss.footState();
}

const chara::HitPoint& ObjInfoImpl::hitPoint() const {
    return mBoss.hitPoint();
}

const gobj::Location& ObjInfoImpl::location() const {
    return mBoss.location().location();
}

const gobj::Move& ObjInfoImpl::move() const {
    return mBoss.move();
}

const gobj::Script& ObjInfoImpl::script() const {
    return mBoss.model().script();
}

const util::IState& ObjInfoImpl::state() const {
    return mBoss.stateChanger().currentStateRef();
}

}}}  // namespace scn::step::boss
