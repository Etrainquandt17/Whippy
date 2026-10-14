#include "scn/strap/SceneStrap.h"

#include "app/Application.h"
#include "app/Locale.h"
#include "app/ResidentFile.h"
#include "file/DNOption.h"
#include "file/FDGManager.h"
#include "gfx/GameScreen.h"
#include "gfx/Utility.h"
#include "gfx/VISetting.h"
#include "hbm/HomeButtonMenu.h"
#include "hel/common/Color.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/RuntimeTypeInfo.h"
#include "hid/HIDManager.h"
#include "hid/SimpleWRHID.h"
#include "lyt/LayoutContext.h"
#include "mem/Memory.h"
#include "metafortress.h"

using app::Application;
using hel::common::Color;
using hel::common::ExplicitSingleton;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

// TODO: hel/common/RuntimeTypeInfo.h does not define this yet; the unit holds its own copy.
namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::strap::SceneStrap>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::IScene>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace strap {

namespace {

#ifdef VERSION_SUKK01
const char* t_lytRes() {
    if (app::Locale::GetRegion() == 2 && app::Locale::GetSystemLanguage() == 6) {
        return "strap/Main.EU_NED";
    }
    return "strap/Main";
}
#else
const char* T_LYT_RES = "strap/Main";
#endif

}

#define MF_FUNCTION __ct__Q33scn5strap10SceneStrapFv
SceneStrap::SceneStrap()
    : _4((GXColor){0xFF, 0xFF, 0xFF, 0xFF})
#ifdef VERSION_SUKK01
    , _C(lyt::LayoutContext(t_lytRes(), "Strap", ExplicitSingleton<mem::Memory>::object_->sceneHeap()))
    , _19C(lyt::LayoutContext(t_lytRes(), "Sideways", ExplicitSingleton<mem::Memory>::object_->sceneHeap()))
#else
    , _C(lyt::LayoutContext(T_LYT_RES, "Strap", ExplicitSingleton<mem::Memory>::object_->sceneHeap()))
    , _19C(lyt::LayoutContext(T_LYT_RES, "Sideways", ExplicitSingleton<mem::Memory>::object_->sceneHeap()))
#endif
    , _32C(Color::BLACK)
    , _334(0)
    , _338()
    , _340(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0x811C9DDB;
    asm {
        bl      after1
#ifdef VERSION_SUKK01
        opword  MF_WORD(0xD0)
        opword  0x82A7FE09
        opword  MF_WORD(0xD8)
#else
        opword  MF_WORD(0xC0)
        opword  0x82A7FE09
        opword  MF_WORD(0xC8)
#endif
    after1:
        mflr    r26
        lwz     r18, 0x8(r26)
        lwz     r20, 0x0(r26)
        add     r20, r20, r26
        stw     r20, start
        add     r18, r18, r20
        stw     r18, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
        i += 2;
    }
    _338.reset(30);
    asm {
        bl      after2
#ifdef VERSION_SUKK01
        opword  MF_WORD(0x148)
#else
        opword  MF_WORD(0x138)
#endif
        opword  0x878BD8AE
    after2:
        mflr    r19
        lwz     r15, 0x0(r19)
        stw     r15, expected
    }
    if (!ExplicitSingleton<gfx::VISetting>::object_->_8) {
        ExplicitSingleton<Application>::object_->gameScreen().setScreenType(gfx::GameScreen::SCREEN_TYPE_0);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    ExplicitSingleton<hbm::HomeButtonMenu>::object_->setIgnore(expected == hash);
}
#undef MF_FUNCTION

#define MF_FUNCTION __dt__Q33scn5strap10SceneStrapFv
SceneStrap::~SceneStrap() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x3C)
        opword  0x7020000F
        opword  MF_WORD(0x44)
        opword  0xA4663F91
    after1:
        mflr    r14
        lwz     r24, 0x0(r14)
        add     r24, r24, r14
        stw     r24, start
        lwz     r26, 0x8(r14)
        add     r24, r24, r26
        stw     r24, end
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x70)
        opword  0x2FDAA2D9
    after2:
        mflr    r16
        lwz     r26, 0x0(r16)
        stw     r26, expected
    }
    last = end;
    word = start;
    for (; word != last; word += 2) {
        hash *= 61;
        hash += *(u16*)word;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash -= expected;
    if (hash == 0) {
        ExplicitSingleton<hbm::HomeButtonMenu>::object_->setIgnore(false);
    } else {
        asm {
            bl      after3
            opword  0x370BC702
            opword  0x70B87291
            opword  MF_WORD(0xFC)
        after3:
            mflr    r22
            lwz     r29, 0x8(r22)
            stw     r29, -0x4(r1)
            stw     r22, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r22, -0x8(r1)
            mtlr    r29
            bl      after4
            opword  MF_WORD(0x120)
            opword  MF_WORD(0x124)
        after4:
            mflr    r15
            lwz     r14, 0x4(r15)
            stw     r14, key
            lwz     r14, 0x0(r15)
            stw     r15, base
            stw     r14, offset
        }
        offset = offset + 0xAB;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    }
}
#undef MF_FUNCTION

void SceneStrap::updateUseGPU() {
}

void SceneStrap::updateMain() {
    _19C.updateFrame();
    if (!_340 && !ExplicitSingleton<Application>::object_->residentFile().isLoading()) {
        ExplicitSingleton<Application>::Object().fdgManager().preLoad("StepCommon.dn", file::DNOption());
        _340 = true;
    }
    switch (_334) {
    case 0:
        _338.advance();
        _32C.setAlpha(_338.inversedNormalizedFrame());
        if (_338.isEnd()) {
            _338.reset(60);
            _334 = 1;
            _32C.setColor(Color::WHITE);
        }
        break;
    case 1:
        _338.advance();
        if (_338.isEnd()) {
            _338.reset(1140);
            _334 = 2;
            ExplicitSingleton<hbm::HomeButtonMenu>::object_->setIgnore(false);
        }
        break;
    case 2:
        _338.advance();
        if (_338.isEnd() || isButtonReceived()) {
            _338.reset(30);
            _334 = 3;
        }
        break;
    case 3:
        _338.advance();
        _32C.setAlpha(_338.normalizedFrame());
        if (_338.isEnd()) {
            _338.reset(30);
            _334 = 4;
        }
        break;
    case 4:
        _338.advance();
        _32C.setAlpha(_338.inversedNormalizedFrame());
        if (_338.isEnd()) {
            _338.reset(1200);
            _334 = 6;
        }
        break;
    case 6:
        _338.advance();
        if (_338.isEnd() || isButtonReceived()) {
            _338.reset(30);
            _334 = 5;
        }
        break;
    case 5:
        _338.advance();
        _32C.setAlpha(_338.normalizedFrame());
        if (_338.isEnd()) {
            _334 = 7;
        }
        break;
    case 7:
        _334 = 8;
        break;
    }
    _C.updateMatrix();
    _19C.updateMatrix();
}

void SceneStrap::updateDebug() {
}

void SceneStrap::draw(const DrawReqInfo& info) {
    _4.draw();
    gfx::Utility::SetupGXForLayout2D(-100.0f, 100.0f);
    switch (_334) {
    case 0:
    case 1:
    case 2:
    case 3:
        _C.draw();
        break;
    case 4:
    case 5:
    case 6:
        _19C.draw();
        break;
    }
    _32C.draw();
}

bool SceneStrap::isSceneEnd() const {
    return _334 == 8;
}

bool SceneStrap::isButtonReceived() const {
    hid::SimpleWRHID wr = ExplicitSingleton<hid::HIDManager>::object_->gameWR(0);
    return wr.button().isTrigger(0x1F1F) || wr.buttonClassic().isTrigger(0xF6FF);
}

const RuntimeTypeInfo& SceneStrap::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<SceneStrap>();
}

}}  // namespace scn::strap
