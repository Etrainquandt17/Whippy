#include "scn/step/hero/leaf/StateHideEnd.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/LeafParam.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/leaf/StateHide.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

StateHideEnd::StateHideEnd(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsUnsetXlu(false) {
    obj().model().script().start(0x9B);
    obj().objColl().setXlu();
}

StateHideEnd::~StateHideEnd() {
    if (!mIsUnsetXlu) {
        obj().objColl().unsetXlu();
    }
}

void StateHideEnd::procAnim() {
    mFrame++;
    if (!mIsUnsetXlu) {
        if (mFrame >= obj().param().leaf()._8C) {
            obj().objColl().unsetXlu();
            mIsUnsetXlu = true;
        }
    }
    if (mFrame > obj().param().leaf()._88 && StateHide::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateHideEnd::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateHideEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::leaf
