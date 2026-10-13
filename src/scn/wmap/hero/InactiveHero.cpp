#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE
#include "scn/wmap/hero/InactiveHero.h"

#include "metafortress.h"
#include "scn/wmap/Component.h"
#include "scn/wmap/SceneStateChecker.h"
#include "scn/wmap/hero/InactiveState.h"
#include "scn/wmap/hero/Manager.h"
#include "scn/wmap/info/Manager.h"
#include "std/tr1/reference_wrapper.h"

namespace scn {
namespace wmap {
namespace hero {

#define MF_FUNCTION __ct__Q43scn4wmap4hero12InactiveHeroFRQ33scn4wmap9ComponentRQ23mem12HeapExpArrayUlRCQ33scn4step17ContextHeroIndivi
// TODO: mem::HeapExp is a mem::IAllocator; its header does not say so yet.
InactiveHero::InactiveHero(Component& component, mem::HeapExpArray& heapArray, u32 index, const step::ContextHeroIndivi& context)
    : mComponent(component)
    , mHeapUser(heapArray)
    , mRumble(reinterpret_cast<mem::IAllocator&>(mHeapUser.obj()))
    , mSE(reinterpret_cast<mem::IAllocator&>(mHeapUser.obj()))
    , mStateCallback(reinterpret_cast<mem::IAllocator&>(mHeapUser.obj()))
    , mStateChanger(reinterpret_cast<mem::IAllocator&>(mHeapUser.obj()))
    , _2C(context._38)
    , mIndex(index)
    , _38(context._4)
    , _3C(context._0 != 1)
    , _3D(false)
    , _3E(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    hash = 0x811C9E07;
    if (_38 >= 7) {
        _38 = 0;
    }
    mRumble.construct(std::tr1::ref(mComponent.hidRumbleManager()), mIndex);
    asm {
        bl      after1
        opword  0x0072F491
        opword  0x28B60293
        opword  MF_WORD(0x10C)
        opword  0x6C963493
        opword  MF_WORD(0x114)
    after1:
        mflr    r23
        lwz     r28, 0x8(r23)
        lwz     r16, 0x10(r23)
        stw     r16, start
        stw     r28, end
    }
    mSE.construct();
    asm {
        bl      after2
        opword  MF_WORD(0x14C)
        opword  0x044FEDF0
    after2:
        mflr    r20
        lwz     r25, 0x0(r20)
        stw     r25, expected
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    mStateCallback.construct(std::tr1::ref(*this));
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
    }
    mStateChanger.construct(std::tr1::ref<util::IStateCallback>(mStateCallback.ref()));
    hash ^= hash >> 10;
    hash ^= hash << 20;
    switch (context._0) {
    case 2:
    case 4:
        _3C = expected == hash;
        break;
    case 1:
    case 3:
    default:
        _3C = hash - expected != 0;
        break;
    }
    if (hash - expected == 0 && !_3C) {
        mStateChanger->setNextState<inactive::StateInit, InactiveHero*>(this);
    } else {
        mStateChanger->setNextState<inactive::StateSelect, InactiveHero*, bool>(this, true);
    }
    mStateChanger->changeStateIfPossible();
}
#undef MF_FUNCTION

}}}  // namespace scn::wmap::hero

namespace util {

template <>
StateChanger<scn::wmap::hero::IInactiveState, 256>::~StateChanger() {
}

}

namespace scn {
namespace wmap {
namespace hero {

InactiveHero::~InactiveHero() {
    mStateChanger->reset();
    mRumble->stop();
}

void InactiveHero::proc() {
    mStateChanger->changeStateIfPossible();
    static_cast<IInactiveState&>(mStateChanger->currentStateRef()).proc();
    mStateChanger->changeStateIfPossible();
}

void InactiveHero::createHero() {
    step::ContextHeroIndivi context = step::ContextHeroIndivi::CreateDefault();
    context._4 = _38;
    context._38 = _2C;
    switch (_38) {
    case 0:
    case 1:
    case 2:
    case 3:
        context._8[0] = 0;
        break;
    case 4:
        context._8[0] = 0x20;
        break;
    case 5:
        context._8[0] = 0x21;
        break;
    case 6:
        context._8[0] = 0x22;
        break;
    }
    mComponent.heroManager().createHero(mIndex, context);
    if (mComponent.heroManager().shareData()._4 == 0) {
        mComponent.heroManager().setHitPointHalf(mIndex);
    }
    mComponent.heroManager().shareData().decRestPlayer();
    mComponent.infoManager().main().heroPanel(mIndex).charaDecideEffectAppear();
    _3E = true;
}

step::ContextHeroIndivi InactiveHero::createContext() const {
    step::ContextHeroIndivi context = step::ContextHeroIndivi::Create();
    context._4 = _38;
    context._0 = _3C ? 4 : 1;
    context._38 = _2C;
    return context;
}

info::HeroPanel& InactiveHero::infoHeroPanel() {
    return mComponent.infoManager().main().heroPanel(mIndex);
}

void InactiveHero::setIsConnected(bool isConnected) {
    _3C = isConnected;
}

bool InactiveHero::isConnected() const {
    return _3C;
}

void InactiveHero::setIsDecided(bool isDecided) {
    _3D = isDecided;
}

bool InactiveHero::isDecided() const {
    return _3D;
}

bool InactiveHero::isForbidSelect() {
    if (mComponent.sceneStateChecker()._0 || mComponent.sceneStateChecker()._1 || mComponent.sceneStateChecker()._2) {
        return true;
    }
    return false;
}

void InactiveHero::setKind(step::hero::Kind kind) {
    _38 = kind;
}

step::hero::Kind InactiveHero::kind() const {
    return static_cast<step::hero::Kind>(_38);
}

}}}  // namespace scn::wmap::hero
