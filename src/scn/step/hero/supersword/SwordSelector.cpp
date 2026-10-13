#include "scn/step/hero/supersword/SwordSelector.h"
#include "scn/step/Component.h"
#include "scn/step/core/MintManager.h"
#include "scn/step/hero/supersword/MintSwordSelector.h"

namespace scn {
namespace step {
namespace hero {
namespace supersword {

SwordSelector::SwordSelector(Component& component)
    : mRunner(component.mintManager().engine())
    , mKind(0)
    , mRareTryCount(1) {
    MintSwordSelector::Register(*this);
    mRunner.setEntryPoint("Scn.Step.Hero.SuperSword.SwordSelector.Exec()");
}

SwordSelector::~SwordSelector() {
    MintSwordSelector::Unregister(*this);
}

u32 SwordSelector::getKind(bool isRare) {
    if (isRare) {
        for (u32 i = 0; i < mRareTryCount; i++) {
            mRunner.execute();
            if (this->isRare(static_cast<GearSwordNodeKind>(mKind))) {
                return mKind;
            }
        }
        return mKind;
    }
    mRunner.execute();
    return mKind;
}

bool SwordSelector::isRare(GearSwordNodeKind kind) {
    switch (kind) {
    case 5:
    case 6:
        return true;
    default:
        return false;
    }
}

void SwordSelector::setKind(u32 kind) {
    mKind = kind;
}

void SwordSelector::setRareTryCount(u32 count) {
    mRareTryCount = count;
}

}
}
}
}
