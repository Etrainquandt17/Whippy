#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE
#include "scn/wmap/info/LevelName.h"

#include "app/Application.h"
#include "app/Message.h"
#include "hel/math/Matrix44.h"
#include "hel/math/Vector2.h"
#include "hel/debug/Print.h"
#include "info/common/WiiButton.h"
#include "lyt/Layout.h"
#include "lyt/LayoutContext.h"
#include "lyt/PaneAccessor.h"
#include "lyt/Utility.h"
#include "mem/AutoHeapExp.h"
#include "metafortress.h"
#include "scn/wmap/Component.h"
#include "scn/wmap/UnlockManager.h"
#include "scn/wmap/Util.h"
#include "storage/BackupFileData.h"
#include "storage/StorageManager.h"
#include "storage/StoryData.h"
#include "util/ObjList.h"
#include "std/tr1/reference_wrapper.h"

// TODO: the headers of these classes do not declare these members yet.
// Replace the declarations with the members once they do.
extern "C" storage::StoryData* storyData__Q27storage14BackupFileDataFQ27storage9StoryMode(storage::BackupFileData* data, storage::StoryMode mode);
extern "C" u32 sphereGetCountAtLevel__Q27storage9StoryDataCFQ33scn4step9LevelKind(const storage::StoryData* data, scn::step::LevelKind level);
extern "C" u32 SphereTotalNum__Q33scn4step13StageKindUtilFQ33scn4step9LevelKind(scn::step::LevelKind level);
extern "C" void appearBlink__Q34info6common9WiiButtonFv(info::common::WiiButton* button);

using hel::debug::Print;

namespace scn {
namespace wmap {
namespace info {

#define MF_FUNCTION __ct__Q43scn4wmap4info9LevelNameFRQ33scn4wmap9Component
LevelName::LevelName(Component& component)
    : mComponent(component)
    , _4(component.heap().obj())
    , _C(component.heap().obj())
    , _14(component.heap().obj())
    , _1C(component.heap().obj())
    , _24(component.heap().obj())
    , _2C(component.heap().obj())
    , _34(hel::math::Vector3::ZERO)
    , _40(false)
    , mItemKind(static_cast<ItemKind>(11))
    , _48(hel::math::Vector3::ZERO)
    , _54(false)
    , _58(0)
    , _5C(false)
    , _5D(false)
    , _5E(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 key;
    u32 word;
    u32 hash;
    u32 last;

    _4.construct(lyt::LayoutContext("wmap/Main", "LvNameBase", component.heap().obj()));
    asm {
        bl      after1
        opword  MF_WORD(0x15C)
        opword  0x5FF70CC5
    after1:
        mflr    r27
        lwz     r29, 0x0(r27)
        stw     r29, expected
    }
    _4->play("End");
    asm {
        bl      after2
        opword  MF_WORD(0x184)
        opword  0xEF587B09
    after2:
        mflr    r22
        lwz     r26, 0x0(r22)
        add     r26, r26, r22
        stw     r26, start
        bl      after3
        opword  MF_WORD(0x1A0)
        opword  0x709A1406
        opword  0xA56E0404
    after3:
        mflr    r22
        lwz     r24, 0x0(r22)
        add     r26, r26, r24
        stw     r26, end
    }
    _4->setFrameToTail();
    _4->reflectFrameToAnim();
    hash = 0xC5;
    _C.construct(lyt::LayoutContext("wmap/Main", "LvName", component.heap().obj()));
    word = start;
    last = end;
    _C->setParent(_4->pane("LvnameN"));
    _14.construct(std::tr1::ref(component.heap().obj()), _C->pane("WiiButtonN01"), ::info::common::WiiButton::KIND_0);
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    _1C.construct(std::tr1::ref(component.heap().obj()), _C->pane("WiiButtonN02"), ::info::common::WiiButton::KIND_1);
    _24.construct(std::tr1::ref(component.heap().obj()), _C->pane("WiiButtonN03"), ::info::common::WiiButton::KIND_1);
    hash -= expected;
    hash = __cntlzw(hash);
    word = hash >> 5;
    hash = word * 15;
    hash = word + hash;
    if (hash == 0) {
        asm {
            bl      after4
            opword  0xBF56CC00
            opword  MF_WORD(0x3A4)
        after4:
            mflr    r26
            lwz     r27, 0x4(r26)
            stw     r27, -0x4(r1)
            stw     r26, 0x0(r1)
            stw     r27, -0x4(r1)
            stw     r26, -0x8(r1)
            mtlr    r27
            bl      after5
            opword  MF_WORD(0x3C8)
            opword  MF_WORD(0x3CC)
        after5:
            mflr    r15
            lwz     r16, 0x0(r15)
            lwz     r17, 0x4(r15)
            stw     r17, key
            stw     r16, offset
            stw     r15, base
        }
        offset = offset ^ 0xAC;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        _2C.construct(std::tr1::ref(component.heap().obj()), _C->pane("WiiButtonN04"), ::info::common::WiiButton::KIND_1);
    }
}
#undef MF_FUNCTION

void LevelName::procAnim() {
    _4->updateFrame();
    _C->updateFrame();
    _14->updateFrame();
    _1C->updateFrame();
    _24->updateFrame();
    _2C->updateFrame();
    switch (_58) {
    case 1:
        if (_4->isAnimEnd()) {
            if (!_5C || _5E) {
                mfToClose();
            } else {
                _4->setAnimByName("Wait");
                _4->start(true);
                _58 = 2;
            }
        }
        break;
    case 2:
        if (!_5C || _5D || _5E) {
            mfToClose();
        }
        break;
    case 3:
        if (_4->isAnimEnd()) {
            if (_5C && !_5E) {
                mfToOpen();
            } else {
                _58 = 0;
            }
        }
        break;
    case 0:
        if (_5C && !_5E) {
            mfToOpen();
        }
        break;
    }
}

void LevelName::updateScreenPos(const hel::math::Matrix44& view) {
    hel::math::Matrix44 proj = hel::math::Matrix44::CreatePerspective(40.0f, 1.7777778f, 0.1f, 1000.0f);
    hel::math::Matrix44 viewCopy(view);
    hel::math::Matrix44 viewProj = proj.mulMtx(viewCopy);
    hel::math::Vector3 projected = viewProj.mulVec(_34);
    hel::math::Vector2 screen(projected.x, projected.y);
    hel::math::Vector2 pos(screen.x * lyt::Utility::ScreenHalfWidth(), screen.y * lyt::Utility::ScreenHalfHeight());
    _4->rootPane().setTrans(pos.toVector3());
}

void LevelName::procReadyToRender() {
    _4->updateMatrix();
    mfUpdateVisibility();
}

void LevelName::draw() {
    _4->draw();
}

void LevelName::init(ItemKind item, const hel::math::Vector3& pos) {
    mItemKind = item;
    _48 = pos;
    _40 = true;
}

void LevelName::setItem(ItemKind item, const hel::math::Vector3& pos) {
    if (mItemKind != item) {
        mItemKind = item;
        _48 = pos;
        _5D = true;
    }
}

#define MF_FUNCTION open__Q43scn4wmap4info9LevelNameFv
void LevelName::open() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 base;
    volatile u32 key;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0x811C9E53;
    asm {
        bl      after1
        opword  0x3D9EB500
        opword  0xF4F11480
        opword  MF_WORD(0x34)
        opword  0x0BF5B20E
        opword  0x02D5700F
        opword  MF_WORD(0x40)
    after1:
        mflr    r21
        lwz     r14, 0x8(r21)
        stw     r14, end
        lwz     r14, 0x14(r21)
        stw     r14, start
    }
    last = end;
    word = start;
    for (;;) {
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
        word += 2;
    }
    hash += hash << 3;
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0x36504440
    after2:
        mflr    r15
        lwz     r24, 0x0(r15)
        stw     r24, expected
    }
    hash ^= hash >> 11;
    hash += hash << 15;
    hash -= expected;
    if (hash == 0) {
        _5C = true;
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0xD4)
        after3:
            mflr    r17
            lwz     r14, 0x0(r17)
            stw     r14, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r14, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r14
            bl      after4
            opword  MF_WORD(0xF8)
            opword  MF_WORD(0xFC)
        after4:
            mflr    r19
            stw     r19, base
            lwz     r20, 0x0(r19)
            stw     r20, offset
            lwz     r17, 0x4(r19)
            stw     r17, key
        }
        offset = offset - 0xC0;
        key = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION onMoveStart__Q43scn4wmap4info9LevelNameFv
void LevelName::onMoveStart() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xC44A7180
        opword  0x00C20D81
    after1:
        mflr    r21
        lwz     r27, 0x0(r21)
        add     r27, r27, r21
        stw     r27, start
        bl      after2
        opword  MF_WORD(0x44)
        opword  0xF4BE0D01
        opword  0x14466581
    after2:
        mflr    r21
        lwz     r26, 0x0(r21)
        add     r27, r27, r26
        stw     r27, end
    }
    last = end;
    word = start;
    hash = 0xB5;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    asm {
        bl      after3
        opword  MF_WORD(0x98)
        opword  0x1216BE44
    after3:
        mflr    r26
        lwz     r28, 0x0(r26)
        stw     r28, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    _5E = expected == hash;
}
#undef MF_FUNCTION

void LevelName::onMoveEnd() {
    _5E = false;
}

#define MF_FUNCTION on1Pushed__Q43scn4wmap4info9LevelNameFv
void LevelName::on1Pushed() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 key;
    u32 i;
    u32 first;
    u32 hash;
    u32 limit;

    asm {
        bl      after1
        opword  0x45838700
        opword  0xDC3A5381
        opword  MF_WORD(0x2C)
        opword  MF_WORD(0x30)
    after1:
        mflr    r18
        lwz     r26, 0x8(r18)
        stw     r26, start
        lwz     r26, 0xC(r18)
        stw     r26, end
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0xB475E652
    after2:
        mflr    r23
        lwz     r29, 0x0(r23)
        stw     r29, expected
    }
    hash = 0x811C9E07;
    i = 1;
    first = start;
    limit = end - first + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001A7;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0x315C4A08
            opword  0x84FBA790
            opword  0x1C163380
            opword  MF_WORD(0xDC)
        after3:
            mflr    r18
            lwz     r21, 0xC(r18)
            stw     r21, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r21
            bl      after4
            opword  MF_WORD(0x100)
            opword  MF_WORD(0x104)
        after4:
            mflr    r16
            lwz     r15, 0x0(r16)
            lwz     r14, 0x4(r16)
            stw     r14, key
            stw     r15, offset
            stw     r16, base
        }
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    } else {
        _14->hold();
    }
}
#undef MF_FUNCTION

void LevelName::on2Pushed() {
    _1C->hold();
    _24->hold();
    _2C->hold();
}

#define MF_FUNCTION mfStartLevel__Q43scn4wmap4info9LevelNameFQ33scn4step9LevelKindb
void LevelName::mfStartLevel(step::LevelKind level, bool skip) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    Component& component = mComponent;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;
    u32 count;
    u32 total;

    count = sphereGetCountAtLevel__Q27storage9StoryDataCFQ33scn4step9LevelKind(
        storyData__Q27storage14BackupFileDataFQ27storage9StoryMode(
            &hel::common::ExplicitSingleton<app::Application>::object_->storageManager().selectedBackupFileData(), component.mStoryMode),
        level);
    total = SphereTotalNum__Q33scn4step13StageKindUtilFQ33scn4step9LevelKind(level);
    asm {
        bl      after1
        opword  MF_WORD(0x5C)
        opword  0x84EE8990
    after1:
        mflr    r19
        lwz     r20, 0x0(r19)
        add     r20, r20, r19
        stw     r20, start
        bl      after2
        opword  MF_WORD(0x78)
        opword  0xBCD58D0E
        opword  0xDA7E8201
    after2:
        mflr    r19
        lwz     r22, 0x0(r19)
        add     r20, r20, r22
        stw     r20, end
    }
    _4->play("Start");
    if (skip) {
        _4->setFrameToTail();
        _4->reflectFrameToAnim();
    }
    hash = 0x811C9E53;
    _C->paneByName("MapName").setText(app::Message::TextWMap(Print::HelSPrintfImpl("Lv%uTitle", level + 1)));
    asm {
        bl      after3
        opword  MF_WORD(0x11C)
        opword  0x366FA26A
    after3:
        mflr    r16
        lwz     r22, 0x0(r16)
        stw     r22, expected
    }
    _C->pane("Count").setText(Print::HelSPrintfImpl("%d", count));
    limit = end - start + 1;
    i = 1;
    base = start;
    _C->paneByName("Max").setText(Print::HelSPrintfImpl("%d", total));
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001D1;
        i += 2;
    }
    _C->play(Print::HelSPrintfImpl("Lv%02d", level + 1));
    hash += hash << 13;
    hash ^= hash >> 7;
    _C->paneByName("LevelInfo").setText(app::Message::TextWMap("LevelToEnter"));
    hash += hash << 3;
    appearBlink__Q34info6common9WiiButtonFv(_2C.operator->());
    hash ^= hash >> 17;
    hash += hash << 5;
    _54 = hash - expected != 0;
    _58 = 1;
}
#undef MF_FUNCTION

#define MF_FUNCTION mfStartShip__Q43scn4wmap4info9LevelNameFb
void LevelName::mfStartShip(bool skip) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0xD8799F91
        opword  0xA051AF91
        opword  MF_WORD(0x3C)
        opword  0xE4B51708
    after1:
        mflr    r26
        lwz     r30, 0x0(r26)
        lwz     r16, 0xc(r26)
        add     r16, r30, r16
        stw     r30, start
        stw     r16, end
    }
    hash = 0;
    _4->play("Start");
    word = start;
    last = end;
    if (skip) {
        _4->setFrameToTail();
        _4->reflectFrameToAnim();
    }
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash *= 37;
        hash += *(u16*)word;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xC0)
        opword  0xF8821A3F
    after2:
        mflr    r20
        lwz     r27, 0x0(r20)
        stw     r27, expected
    }
    hash += hash << 13;
    _C->paneByName("ShipName").setText(app::Message::TextWMap("ShipTitle"));
    hash ^= hash >> 7;
    if (mfCanMoveToHalcandra()) {
        if (Util::GetMapKind(mItemKind) == MAP_KIND_0) {
            _C->paneByName("ShipInfo01").setText(app::Message::TextWMap("ShipToHalcandra"));
        } else {
            _C->paneByName("ShipInfo01").setText(app::Message::TextWMap("ShipToPopstar"));
        }
        _C->paneByName("ShipInfo02").setText(app::Message::TextWMap("ShipToEnter"));
        _C->paneByName("ShipInfo01N").setVisibility(true);
        _C->paneByName("ShipInfo02N").setVisibility(true);
        appearBlink__Q34info6common9WiiButtonFv(_14.operator->());
        appearBlink__Q34info6common9WiiButtonFv(_1C.operator->());
        _C->play("Ship");
    } else {
        _C->paneByName("ShipInfo03").setText(app::Message::TextWMap("ShipToEnter"));
        _C->play("ShipBefoe");
        _C->paneByName("ShipInfo03N").setVisibility(true);
        appearBlink__Q34info6common9WiiButtonFv(_24.operator->());
    }
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    _54 = expected == hash;
    _58 = 1;
}
#undef MF_FUNCTION

void LevelName::mfUpdateVisibility() {
    if (_58 != 0) {
        if (_54) {
            _C->paneByName("LevelText").setVisibility(false);
            _C->paneByName("MapName").setVisibility(false);
            _C->paneByName("ShipName").setVisibility(true);
            if (mfCanMoveToHalcandra()) {
                _C->paneByName("ShipInfo01N").setVisibility(true);
                _C->paneByName("ShipInfo02N").setVisibility(true);
                _C->paneByName("ShipInfo03N").setVisibility(false);
            } else {
                _C->paneByName("ShipInfo01N").setVisibility(false);
                _C->paneByName("ShipInfo02N").setVisibility(false);
                _C->paneByName("ShipInfo03N").setVisibility(true);
            }
            _C->paneByName("LMapTotalSpheN").setVisibility(false);
        } else {
            _C->paneByName("LevelText").setVisibility(true);
            _C->paneByName("MapName").setVisibility(true);
            _C->paneByName("ShipName").setVisibility(false);
            _C->paneByName("ShipInfo01N").setVisibility(false);
            _C->paneByName("ShipInfo02N").setVisibility(false);
            _C->paneByName("ShipInfo03N").setVisibility(false);
            _C->paneByName("LMapTotalSpheN").setVisibility(true);
        }
    }
}

#define MF_FUNCTION mfToOpen__Q43scn4wmap4info9LevelNameFv
void LevelName::mfToOpen() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 i;
    u32 size;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0xA025C16E
    after1:
        mflr    r15
        lwz     r20, 0x0(r15)
        stw     r20, expected
        bl      after2
        opword  MF_WORD(0x38)
        opword  0xC4551D90
        opword  0x6459EB80
        opword  MF_WORD(0x44)
    after2:
        mflr    r24
        lwz     r27, 0xc(r24)
        lwz     r22, 0x0(r24)
        add     r27, r22, r27
        stw     r27, end
        stw     r22, start
    }
    last = end;
    size = last - start;
    i = -1;
    last--;
    while (i != size - 1) {
        i += 2;
        hash *= 193;
        hash += *(u16*)(last - i);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    switch (mItemKind) {
    case ITEM_KIND_0:
    case ITEM_KIND_1:
    case ITEM_KIND_2:
    case ITEM_KIND_3:
    case ITEM_KIND_4:
    case ITEM_KIND_7:
    case ITEM_KIND_8:
        mfStartLevel(Util::GetLevelKindFromItemKind(mItemKind), hash - expected != 0);
        break;
    case ITEM_KIND_5:
    case ITEM_KIND_9:
        mfStartShip(hash - expected != 0);
        break;
    case ITEM_KIND_6:
    case ITEM_KIND_10:
        break;
    }
    _34 = _48;
    _5D = hash - expected != 0;
}
#undef MF_FUNCTION

#define MF_FUNCTION mfToClose__Q43scn4wmap4info9LevelNameFv
void LevelName::mfToClose() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 key;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
    after1:
        mflr    r19
        lwz     r17, 0x0(r19)
        add     r17, r17, r19
        stw     r17, start
        bl      after2
        opword  0x0CC29E92
        opword  0xC4EB9680
        opword  MF_WORD(0x44)
        opword  0x1054C390
    after2:
        mflr    r19
        lwz     r14, 0x8(r19)
        add     r17, r17, r14
        stw     r17, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    hash = 0x811C9DDB;
    asm {
        bl      after3
        opword  MF_WORD(0x80)
        opword  0xF2033875
    after3:
        mflr    r14
        lwz     r22, 0x0(r14)
        stw     r22, expected
    }
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x01000193;
    }
    _4->play("End");
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash -= expected;
    if (hash == 0) {
        _58 = 3;
    } else {
        asm {
            bl      after4
            opword  0xD9B7560C
            opword  MF_WORD(0x11C)
        after4:
            mflr    r30
            lwz     r16, 0x4(r30)
            stw     r16, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r16
            bl      after5
            opword  MF_WORD(0x140)
            opword  0x20B06F91
            opword  0x7862580F
            opword  MF_WORD(0x14C)
        after5:
            mflr    r29
            stw     r29, base
            lwz     r27, 0x0(r29)
            stw     r27, offset
            lwz     r22, 0xC(r29)
            stw     r22, key
        }
        offset = offset + 0xE7;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    }
}
#undef MF_FUNCTION

bool LevelName::mfCanMoveToHalcandra() const {
    return mComponent.unlockManager().canMove(ITEM_KIND_7);
}

}
}
}
