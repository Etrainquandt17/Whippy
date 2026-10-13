#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "scn/step/boss/WeakPointCtrl.h"

namespace scn {
namespace step {
namespace boss {

WeakPointCtrl::WeakPointCtrl() : mData() {}

WeakPointCtrl::~WeakPointCtrl() {}

f32 WeakPointCtrl::getDamageRate(u32 id) const {
    for (u32 i = 0; i < mData.count(); i++) {
        if (mData[i].mID == id) {
            return mData[i].mRate;
        }
    }
    return 1.0f;
}

void WeakPointCtrl::add(u32 id, f32 rate) {
    mData.add(WeakPointData(id, rate));
}

void WeakPointCtrl::clear() {
    mData.clear();
}

// TODO: the link dropped this function; the body is a guess. It is the second user that keeps the array's
// accessor and the assignment of an element calls in add().
void WeakPointCtrl::remove(u32 id) {
    for (u32 i = 0; i < mData.count(); i++) {
        if (mData[i].mID == id) {
            mData.removeAtIndex(i);
            return;
        }
    }
}

}
}
}
