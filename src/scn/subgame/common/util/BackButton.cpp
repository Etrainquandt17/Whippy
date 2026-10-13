#include "scn/subgame/common/util/BackButton.h"

#include "app/Message.h"
#include "hel/common/ExplicitSingleton.h"
#include "mem/Memory.h"
#include "metafortress.h"

namespace scn {
namespace subgame {
namespace common {
namespace util {

#define MF_FUNCTION __ct__Q53scn7subgame6common4util10BackButtonFRCQ23lyt12PaneAccessorbbUl
BackButton::BackButton(const lyt::PaneAccessor& pane, bool blinks, bool isTwo, u32 seId)
    : info::common::ButtonHelp(hel::common::ExplicitSingleton<mem::Memory>::object_->sceneHeap(), pane,
                               isTwo ? info::common::WiiButton::KIND_2 : info::common::WiiButton::KIND_0)
    , mSE()
    , mSEId(seId) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 hash;
    u32 tail;
    u32 rotated;
    u32 i;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x64)
        opword  0xAE6D3A77
    after1:
        mflr    r22
        lwz     r21, 0x0(r22)
        stw     r21, expected
    }
    hash = 0xC1;
    asm {
        bl      after2
        opword  MF_WORD(0x80)
        opword  0xE55DE10B
        opword  MF_WORD(0x88)
    after2:
        mflr    r21
        lwz     r25, 0x0(r21)
        add     r25, r25, r21
        lwz     r20, 0x8(r21)
        stw     r25, start
        add     r20, r20, r25
        stw     r20, end
    }
    limit = end - start + 1;
    tail = end;
    i = -1;
    base = tail - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        rotated = (hash << 4) ^ (hash >> 28);
        hash = rotated ^ *(u16*)(base - i);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || blinks) {
        blink();
    }
    setText(app::Message::TextCommon("Back"));
}
#undef MF_FUNCTION

void BackButton::push() {
    mSE.start(mSEId);
    ButtonHelp::push();
}

}}}}  // namespace scn::subgame::common::util
