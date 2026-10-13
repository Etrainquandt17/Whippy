#include "scn/subgame/gunshoot/enemy/PlayListSetController.h"

#include "metafortress.h"
#include "scn/subgame/gunshoot/enemy/PlayListController.h"
#include "scn/subgame/gunshoot/param/PlayListSet.h"

extern "C" unsigned long strlen(const char* string);

namespace scn {
namespace subgame {
namespace gunshoot {
namespace enemy {

#define MF_FUNCTION __ct__Q53scn7subgame8gunshoot5enemy21PlayListSetControllerFRCQ53scn7subgame8gunshoot5param11PlayListSetRQ53scn7subgame6common6effect16RequestorBuilderQ23g3d12NodeAccessorRQ53scn7subgame6common4view13ModelAccessor
PlayListSetController::PlayListSetController(const param::PlayListSet& playListSet, common::effect::RequestorBuilder& builder, g3d::NodeAccessor node,
                                             common::view::ModelAccessor& model)
    : mPlayListSet(playListSet)
    , mController()
    , mIndex(-1) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    hash = 0xB3;
    asm {
        bl      after1
        opword  0xE4F03281
        opword  MF_WORD(0x50)
        opword  MF_WORD(0x54)
        opword  0x2076AB80
    after1:
        mflr    r21
        lwz     r15, 0x8(r21)
        lwz     r29, 0x4(r21)
        stw     r29, end
        stw     r15, start
    }
    i = 1;
    first = start;
    limit = end - first + 1;
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(first + i - 1);
    }
    asm {
        bl      after2
        opword  MF_WORD(0xB0)
        opword  0x4A38EB7D
    after2:
        mflr    r20
        lwz     r22, 0x0(r20)
        stw     r22, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    while (hash - expected != 0) {
    }
    initPlayListSet(builder, node, model);
}
#undef MF_FUNCTION

PlayListSetController::~PlayListSetController() {
}

#define MF_FUNCTION initPlayListSet__Q53scn7subgame8gunshoot5enemy21PlayListSetControllerFRQ53scn7subgame6common6effect16RequestorBuilderQ23g3d12NodeAccessorRQ53scn7subgame6common4view13ModelAccessor
void PlayListSetController::initPlayListSet(common::effect::RequestorBuilder& builder, g3d::NodeAccessor node, common::view::ModelAccessor& model) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 limit;
    u32 hash;
    u32 base;
    u32 i;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
    after1:
        mflr    r27
        lwz     r28, 0x0(r27)
        add     r28, r28, r27
        stw     r28, start
        bl      after2
        opword  MF_WORD(0x44)
        opword  0x683A9E0A
        opword  0xC7829308
    after2:
        mflr    r27
        lwz     r29, 0x0(r27)
        add     r28, r28, r29
        stw     r28, end
    }
    limit = end - start + 1;
    last = end;
    asm {
        bl      after3
        opword  MF_WORD(0x78)
        opword  0xAF660A86
    after3:
        mflr    r17
        lwz     r22, 0x0(r17)
        stw     r22, expected
    }
    i = -1;
    base = last - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(base - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    while (hash - expected != 0) {
    }
    for (u32 n = 0; n < 32; n++) {
        const char* name = mPlayListSet.str(mPlayListSet.playListData().name[n]);
        if (strlen(name) != 0) {
            hel::common::ScopedPtr<PlayListController>(new PlayListController(name, &builder, node, &model)).swap(mController);
            break;
        }
    }
}
#undef MF_FUNCTION

void PlayListSetController::updateMain() {
    if (mController) {
        mController->updateMain();
    }
}

void PlayListSetController::updateDebug() {
    if (mController) {
        mController->updateDebug();
    }
}

bool PlayListSetController::isValidIndex(int index) const {
    return strlen(mPlayListSet.str(mPlayListSet.playListData().name[index])) == 0;
}

bool PlayListSetController::isStarting() const {
    return mIndex != -1;
}

void PlayListSetController::start(int index) {
    mIndex = index;
    const char* name = mPlayListSet.str(mPlayListSet.playListData().name[index]);
    strlen(name);
    mController->resetPlayList(name);
    mController->start();
}

void PlayListSetController::end() {
    mIndex = -1;
    mController->end();
}

void PlayListSetController::endIfStarting() {
    if (isStarting()) {
        end();
    }
}

void PlayListSetController::pause() {
    mController->pause();
}

void PlayListSetController::unpause() {
    mController->unpause();
}

bool PlayListSetController::isPause() const {
    return mController->isPause();
}

}}}}  // namespace scn::subgame::gunshoot::enemy
