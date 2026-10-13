#include "scn/step/boss/fattybuffer/MapCollCtrl.h"

#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

MapCollCtrl::MapCollCtrl(Boss& boss) : mBoss(boss) {}

void MapCollCtrl::setDefault() {
    if (mBoss.angry().isAngry()) {
        mBoss.mapColl().setActorSetting(2.5f, 1.25f, 3.0f);
    } else {
        mBoss.mapColl().setActorSetting(1.4f, 0.49f, 0.99f);
    }
    mBoss.mapColl().reset();
}

void MapCollCtrl::setBalloon() {
    if (mBoss.angry().isAngry()) {
        mBoss.mapColl().setActorSetting(2.5f, 1.25f, 5.0f);
    } else {
        mBoss.mapColl().setActorSetting(1.4f, 0.49f, 3.49f);
    }
    mBoss.mapColl().reset();
}

}}}}  // namespace scn::step::boss::fattybuffer
