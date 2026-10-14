#include "scn/step/boss/lowper/ItemCtrl.h"

#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/EnergySphereCtrl.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateAppear.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/state/StateLowperGather.h"
#include "scn/step/item/state/StateLowperGatherPair.h"
#include "scn/step/item/state/StateLowperHide.h"
#include "std/tr1/reference_wrapper.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

ItemCtrl::ItemCtrl(Boss& boss)
    : mBoss(boss), mItem(), mItemPair(), mGearModelDesc(), mRot(0.0f), mRotSpeed(0.0f), mScale(1.0f), mScaleTarget(1.0f),
      mIsGathered(false), mIsInit(false), mIsEnd(false) {}

ItemCtrl::~ItemCtrl() {}

void ItemCtrl::init() {
    mItem = mBoss.comp().bossManager().energySphereCtrl().pick();
    if (mBoss.comp().bossManager().getBossCount() < 2) {
        mItemPair = mBoss.comp().bossManager().energySphereCtrl().pick();
    }
    if (!mItem.isAlive()) {
        return;
    }
    if (mItem.isAlive()) {
        if (mBoss.comp().bossManager().getBossCount() >= 2) {
            item::Item* item = mItem.operator->();
            item->stateChanger().setNextState<item::state::StateLowperGatherPair, item::Item*>(item);
        } else {
            item::Item* item = mItem.operator->();
            item->stateChanger().setNextState<item::state::StateLowperGather, item::Item*, Vector3>(
                item, mBoss.location().pos());
        }
        mItem->stateChanger().changeStateIfPossible();
    }
    if (mItemPair.isAlive()) {
        item::Item* item = mItemPair.operator->();
        item->stateChanger().setNextState<item::state::StateLowperGather, item::Item*, Vector3>(item,
                                                                                              mBoss.location().pos());
        mItemPair->stateChanger().changeStateIfPossible();
    }
    mIsInit = true;
}

void ItemCtrl::update() {
    f32 speedRate = 1.0f;
    if (!mIsInit) {
        init();
    }
    checkItemGather();
    if (mScale >= 0.01f + mScaleTarget) {
        mScale -= 0.01f;
        speedRate = 4.0f;
    } else if (mScale <= mScaleTarget - 0.01f) {
        mScale += 0.01f;
        speedRate = 4.0f;
    } else {
        mScale = mScaleTarget;
    }
    mRot += mRotSpeed * speedRate;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    Vector3 offset = Vector3::BASIS_Y * 0.5f * (1.0f - mScale);
    Matrix34 rot = Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRot, 0.0f));
    Matrix34 trans = Matrix34::CreateTrans(offset);
    Matrix34 mtx = trans * rot;
    NodeAccessor node = mBoss.model().model().nodes().at(2);
    node.localMtx().setScale(Vector3::ALL_ONE * mScale);
    node.localMtx().setRTMtx(mtx);
}

bool ItemCtrl::isItemExist() const {
    return mItem.isAlive();
}

void ItemCtrl::checkItemGather() {
    if (!mItem.isAlive()) {
        return;
    }
    if (mIsEnd) {
        return;
    }
    item::Item* item = mItem.operator->();
    if (!mIsGathered && mItemPair.isAlive()) {
        item::Item* pair = mItemPair.operator->();
        if (isNearObj(item->location().pos(), pair->location().pos())) {
            mIsGathered = true;
            NodeAccessor node = item->model().model().g3dModel().nodeByName("RotControlL");
            item->effectBack().requestN(static_cast<effect::Kind>(0x340), node);
            pair->setVisibility(false);
        }
    }
    if (item->model().isVisible()) {
        return;
    }
    mBoss.model().setVisibility(true);
    mBoss.stateChanger().setNextState<StateAppear, Boss*>(&mBoss);
    mItem->stateChanger().setNextState<item::state::StateLowperHide, item::Item*, std::tr1::reference_wrapper<Boss> >(
        mItem.operator->(), std::tr1::ref(mBoss));
    mItem->stateChanger().changeStateIfPossible();
    if (mItemPair.isAlive()) {
        mItemPair->stateChanger().setNextState<item::state::StateLowperHide, item::Item*, std::tr1::reference_wrapper<Boss> >(
            mItemPair.operator->(), std::tr1::ref(mBoss));
        mItemPair->stateChanger().changeStateIfPossible();
    }
    setupGear();
    setupSRTTarget();
    mIsEnd = true;
}

bool ItemCtrl::isNearObj(Vector3 a, Vector3 b) const {
    if (a.x >= b.x - 0.1f && a.x <= 0.1f + b.x && a.y >= b.y - 0.1f && a.y <= 0.1f + b.y) {
        return true;
    }
    return false;
}

Vector3 ItemCtrl::getItemPos() const {
    if (isItemExist()) {
        return mItem->location().pos();
    }
    return mBoss.location().pos();
}

void ItemCtrl::setupGear() {
    if (!mItem.isAlive()) {
        return;
    }
    Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    item::Item* item = mItem.operator->();
    custom.gearCtrl().setup(item->kind(), item->subKind());
}

void ItemCtrl::setupSRTTarget() {
    if (!mItem.isAlive()) {
        return;
    }
    mScale = 1.0f;
    mScaleTarget = 1.0f;
    if (mItem->kind() == 7) {
        mScaleTarget = 0.75f;
        mRotSpeed = 6.0f;
    }
}

}}}}  // namespace scn::step::boss::lowper
