#include "scn/movie/SceneMovie.h"

#include "hbm/HomeButtonMenu.h"
#include "hel/common/ExplicitSingleton.h"
#include "metafortress.h"

using hel::common::ExplicitSingleton;

// TODO: there is no header for the Mobiclip library yet.
extern "C" void MOUninit(void);

namespace scn {
namespace movie {

#define MF_FUNCTION __dt__Q33scn5movie10SceneMovieFv
SceneMovie::~SceneMovie() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0xC1;
    mPlayer.destruct();
    asm {
        bl      after1
        opword  MF_WORD(0x48)
        opword  MF_WORD(0x4C)
        opword  0x504C5780
    after1:
        mflr    r21
        lwz     r15, 0x0(r21)
        lwz     r30, 0x4(r21)
        add     r30, r15, r30
        stw     r15, start
        stw     r30, end
    }
    MOUninit();
    mAllocator.destruct();
    last = end;
    word = start;
    ExplicitSingleton<hbm::HomeButtonMenu>::object_->enableMenu();
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
        word += 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xB0)
        opword  0xDE5CD407
    after2:
        mflr    r16
        lwz     r23, 0x0(r16)
        stw     r23, expected
    }
    if (hash - expected == 0 && mCutIn.isConstruct()) {
        mCutIn.destruct();
    }
}
#undef MF_FUNCTION

}}  // namespace scn::movie
