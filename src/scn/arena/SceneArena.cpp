#include "scn/arena/SceneArena.h"

#include "metafortress.h"

namespace scn {
namespace arena {

#define MF_FUNCTION result__Q33scn5arena10SceneArenaFv
SceneArena::Result SceneArena::result() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 size;
    u32 hash;
    ArenaState state;
    Result result = {};

    asm {
        bl      after1
        opword  MF_WORD(0x40)
        opword  MF_WORD(0x44)
        opword  0x388D1D81
        opword  0x04BB0D80
    after1:
        mflr    r27
        lwz     r30, 0x0(r27)
        lwz     r18, 0x4(r27)
        stw     r18, end
        stw     r30, start
        bl      after2
        opword  MF_WORD(0x68)
        opword  0x689A729B
    after2:
        mflr    r17
        lwz     r30, 0x0(r17)
        stw     r30, expected
    }
    base = start;
    size = end - base;
    result.next = 9;
    hash = 0x811C9DDB;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || mComponent.get() != 0) {
        mComponent->context()._B0 = mComponent->chose().getArenaDataPlayer();
        result.context = mComponent->context();
        state = mComponent->getState();
        switch (_254) {
        case 0:
            switch (state) {
            case ARENA_STATE_1:
                result.next = 6;
                break;
            case ARENA_STATE_6:
            case ARENA_STATE_7:
                result.next = 9;
                break;
            }
            break;
        case 4:
        case 5:
            result.next = 10;
            break;
        }
    }
    return result;
}
#undef MF_FUNCTION

}}  // namespace scn::arena
