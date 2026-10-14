#include "scn/step/camera/CameraController.h"

#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"

using hel::geo::Rect;

namespace scn {
namespace step {
namespace camera {

#define MF_FUNCTION setLock__Q43scn4step6camera16CameraControllerFRCQ33hel3geo4Rect
void CameraController::setLock(const Rect& rect) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  MF_WORD(0x24)
    after1:
        mflr    r27
        lwz     r18, 0x0(r27)
        lwz     r28, 0x4(r27)
        add     r18, r18, r27
        add     r28, r28, r18
        stw     r18, start
        stw     r28, end
    }
    mLockRect = rect;
    word = start;
    last = end;
    hash = 0x811C9E53;
    for (; word != last; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
    }
    mLockRect.transInternal(getDefaultWorldRect());
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    _674 = mComponent.mainCamera().getViewRect();
    hash ^= hash >> 17;
    hash += hash << 5;
    asm {
        bl      after2
        opword  MF_WORD(0x100)
        opword  0xF2C96A7A
    after2:
        mflr    r22
        lwz     r25, 0x0(r22)
        stw     r25, expected
    }
    mIsLock = expected == hash;
}
#undef MF_FUNCTION

}}}  // namespace scn::step::camera
