#include "scn/arena/select/SelectPanel.h"

#include "app/Message.h"
#include "lyt/LayoutContext.h"
#include "mem/HeapExp.h"
#include "metafortress.h"
#include "scn/arena/select/ChoseData.h"
#include "scn/arena/select/SelectSet.h"
#include "std/tr1/reference_wrapper.h"
#include "util/ObjList.h"

using app::Message;

namespace scn {
namespace arena {
namespace select {

#define MF_FUNCTION __ct__Q43scn5arena6select11SelectPanelFRQ43scn5arena6select9SelectSetQ53scn5arena6select11SelectPanel15SelectPanelType
SelectPanel::SelectPanel(SelectSet& set, SelectPanelType type)
    : mSet(set)
    , mLayout(lyt::LayoutContext("arena/Main", "SelectButton", set.heap().obj()))
    , mButton()
    , mWiiButton()
    , mType(type) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x74)
        opword  0x584FD789
    after1:
        mflr    r29
        lwz     r18, 0x0(r29)
        stw     r18, expected
        bl      after2
        opword  0xF1E2B467
        opword  0xD3C9FC70
        opword  0xA5EBA3B8
        opword  0x2483AA52
        opword  0x14758662
        opword  0x793602E6
        opword  0x6B1203AA
        opword  0x7D2E52BD
        opword  0x9BD19F2F
        opword  0xBF56BD22
        opword  0x1E227311
        opword  0x8FC4989A
        opword  0xE168448D
        opword  0xA6D73516
        opword  0xED77459F
        opword  0x5DCD080C
        opword  0x8A1E9E64
        opword  0x25809E25
        opword  0xF6ABD2B0
        opword  0x9D13BA04
        opword  0xD7554E5C
        opword  0xC1EF3893
        opword  0xFB9FE2FA
        opword  0x0FC286D2
        opword  0x4E4858C5
        opword  0x6C1F0E11
        opword  0xFFF4E72A
        opword  0x98DE94A4
        opword  0xF0C0F991
        opword  0xC2655D3E
        opword  0x558C5262
        opword  0xC5FF9FB6
        opword  0xB6127439
        opword  0x40ABFBC9
        opword  0x931D1C3B
        opword  0xEB7B928F
        opword  0x9B304EA9
        opword  0xF041E8B3
    after2:
        bl      after3
        opword  MF_WORD(0x128)
        opword  0xAECE440E
        opword  MF_WORD(0x130)
        opword  0x98C75392
    after3:
        mflr    r25
        lwz     r29, 0x8(r25)
        lwz     r19, 0x0(r25)
        stw     r19, end
        stw     r29, start
    }
    last = end;
    word = start;
    hash = 0;
    mLayout.setParent(mSet.getPanel(static_cast<ArenaCursor>(type)));
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    mLayout.pane("DecideN").hide();
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    mLayout.pane("AddN").hide();
    last = hash >> 17;
    hash ^= last;
    last = hash << 5;
    hash += last;
    last = expected;
    if (hash != last) {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 base2;
        volatile u32 addend;

        asm {
            bl      after4
            opword  0x34C97480
            opword  MF_WORD(0x230)
        after4:
            mflr    r15
            lwz     r14, 0x4(r15)
            stw     r14, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r14, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r14
            bl      after5
            opword  MF_WORD(0x254)
            opword  0x84553B81
            opword  MF_WORD(0x25C)
        after5:
            mflr    r21
            lwz     r26, 0x0(r21)
            lwz     r15, 0x8(r21)
            stw     r15, addend
            stw     r26, offset
            stw     r21, base2
        }
        offset = offset + 0xD3;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    } else {
        switch (type) {
        case SELECT_PANEL_TYPE_0:
            mLayout.pane("Text").setText(Message::TextArena("MemberSelectDecide"));
            mLayout.pane("DecideN").show();
            mLayout.play("NoChoiceGray");
            mButton.construct(lyt::LayoutContext("arena/Main", "Select2Button", set.heap().obj()));
            if (mButton.isConstruct()) {
                mButton->setParent(mLayout.pane("WiiButtonN"));
                mButton->play("Wait");
            }
            break;
        case SELECT_PANEL_TYPE_1:
            mLayout.pane("Text_00").setText(Message::TextArena("MemberSelectWiiRemoteAdd"));
            mLayout.pane("AddN").show();
            mLayout.play("Choice");
            mLayout.setFrame(static_cast<f32>(mSet.getFrame() % static_cast<u32>(mLayout.totalFrame())));
            mWiiButton.construct(std::tr1::ref(set.heap().obj()), mLayout.pane("PlusButtonN"),
                                 ::info::common::WiiButton::KIND_2);
            if (mWiiButton.isConstruct()) {
                mWiiButton->waitNoShadow();
            }
            break;
        }
    }
}
#undef MF_FUNCTION

SelectPanel::~SelectPanel() {
    if (mLayout.wasSetParent()) {
        mLayout.unsetParent();
    }
    if (mButton.isConstruct() && mButton->wasSetParent()) {
        mButton->unsetParent();
    }
}

void SelectPanel::updateFrame() {
    if (mButton.isConstruct()) {
        mButton->updateFrame();
    }
    if (mWiiButton.isConstruct()) {
        mWiiButton->updateFrame();
    }
    mLayout.updateFrame();
}

#define MF_FUNCTION decide__Q43scn5arena6select11SelectPanelFv
void SelectPanel::decide() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x74CA8680
        opword  0xFB1FCC04
        opword  MF_WORD(0x28)
        opword  0x1234F30B
    after1:
        mflr    r26
        lwz     r15, 0x0(r26)
        lwz     r17, 0xc(r26)
        add     r15, r15, r26
        add     r17, r17, r15
        stw     r15, start
        stw     r17, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0xB46B2858
    after2:
        mflr    r19
        lwz     r25, 0x0(r19)
        stw     r25, expected
    }
    hash = 0;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    switch (mType) {
    case SELECT_PANEL_TYPE_0:
        mLayout.play("Decide", "Choice");
        if (hash - expected == 0 && mButton.isConstruct()) {
            mButton->play("Push", "Wait");
        }
        break;
    case SELECT_PANEL_TYPE_1:
        if (hash - expected == 0 && mWiiButton.isConstruct()) {
            mWiiButton->push();
        }
        break;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION big__Q43scn5arena6select11SelectPanelFv
void SelectPanel::big() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    SelectPanel* self;
    u32 word;
    u32 last;

    self = this;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x5C3DF4FC
    after1:
        mflr    r28
        lwz     r22, 0x0(r28)
        stw     r22, expected
    }
    hash = 0xB5;
    asm {
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x9CCB5C81
        opword  MF_WORD(0x48)
        opword  0xF4771481
        opword  0x44779580
    after2:
        mflr    r16
        lwz     r15, 0x8(r16)
        lwz     r29, 0x0(r16)
        add     r29, r29, r16
        stw     r29, start
        add     r15, r15, r29
        stw     r15, end
    }
    last = end;
    word = start;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash = expected ^ hash;
    hash += hash * 44;
    if (hash == 0) {
        volatile u32 addend;
        volatile u32 response;
        volatile u32 base2;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0xE109D706
            opword  MF_WORD(0xD0)
        after3:
            mflr    r30
            lwz     r23, 0x4(r30)
            stw     r23, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0xF4)
            opword  0x2881EB93
            opword  0xBC050790
            opword  MF_WORD(0x100)
        after4:
            mflr    r16
            lwz     r23, 0x0(r16)
            lwz     r25, 0xc(r16)
            stw     r25, addend
            stw     r23, offset
            stw     r16, base2
        }
        offset = offset ^ 0x63;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        switch (self->mType) {
        case SELECT_PANEL_TYPE_0:
            if (self->mSet.chose().isAllDecide()) {
                self->mLayout.play("Choice");
                self->mLayout.setFrame(static_cast<f32>(self->mSet.getFrame() % static_cast<u32>(self->mLayout.totalFrame())));
                if (self->mButton.isConstruct()) {
                    self->mButton->play("Blink");
                    self->mButton->setFrame(static_cast<f32>(self->mSet.getFrame() % static_cast<u32>(self->mLayout.totalFrame())));
                }
            } else {
                self->mLayout.play("ChoiceGray");
                if (self->mButton.isConstruct()) {
                    self->mButton->play("Wait");
                }
            }
            break;
        case SELECT_PANEL_TYPE_1:
            if (self->mWiiButton.isConstruct()) {
                self->mWiiButton->waitNoShadow();
            }
            break;
        }
    }
}
#undef MF_FUNCTION

void SelectPanel::small() {
    switch (mType) {
    case SELECT_PANEL_TYPE_0:
        if (mSet.chose().isAllDecide()) {
            mLayout.play("NoChoice");
            if (mButton.isConstruct()) {
                mButton->play("Wait");
            }
        } else {
            mLayout.play("NoChoiceGray");
            if (mButton.isConstruct()) {
                mButton->play("Gray");
            }
        }
        break;
    case SELECT_PANEL_TYPE_1:
        mLayout.play("NoChoice");
        if (mWiiButton.isConstruct()) {
            mWiiButton->waitNoShadow();
        }
        break;
    }
}

}}}  // namespace scn::arena::select
