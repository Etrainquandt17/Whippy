#include "scn/subgame/title/window/OnGameEndGuide.h"

#include "hel/common/Color.h"
#include "lyt/LayoutContext.h"
#include "lyt/Utility.h"
#include "metafortress.h"
#include "util/ObjList.h"

using hel::common::Color;

namespace scn {
namespace subgame {
namespace title {
namespace window {

namespace {

const char* LAYOUT_FILENAME_COMMON = "subgame/common/Main";
const char* LAYOUT_FILENAME_SESTUNA = "subgame/setsuna/after_result/Main";
const char* LAYOUT_FILENAME_GUNSHOOT = "subgame/gunshoot/after_result/Main";

// The constructor is this helper's only caller and inlines it, so the words of
// the check are counted from the constructor's start.
#define MF_FUNCTION __ct__Q53scn7subgame5title6window14OnGameEndGuideFQ43scn7subgame7Context4Kind
SelectSequence::Context tSelectSequenceContext(Context::Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    SelectSequence::Context context = SelectSequence::Context::Create(kind);
    context.mCount = 3;
    hash = 0xB5;
    context._8[0] = 7;
    context._8[1] = 5;
    asm {
        bl      after1
        opword  MF_WORD(0x120)
    after1:
        mflr    r24
        lwz     r17, 0x0(r24)
        add     r17, r17, r24
        stw     r17, start
        bl      after2
        opword  MF_WORD(0x138)
        opword  0xA4DC7291
    after2:
        mflr    r24
        lwz     r30, 0x0(r24)
        add     r17, r17, r30
        stw     r17, end
    }
    context._8[2] = 0;
    asm {
        bl      after3
        opword  MF_WORD(0x15C)
        opword  0x7AF8378F
    after3:
        mflr    r18
        lwz     r29, 0x0(r18)
        stw     r29, expected
    }
    context._14[0] = "GameEndToPlayAgain";
    context._14[4] = "GameEndToSelectLevel";
    context._14[2] = "GameEndToMenu";
    base = start;
    limit = end - base + 1;
    const bool isSetsuna = kind == Context::KIND_SETSUNA;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    if (hash - expected != 0 || isSetsuna) {
        context._58 = LAYOUT_FILENAME_SESTUNA;
    } else {
        context._58 = LAYOUT_FILENAME_GUNSHOOT;
    }
    for (u32 n = 0; n < context.mCount; n++) {
        context._68[n] = isSetsuna ? 0x5D5 : 0x614;
        context._74[n] = isSetsuna ? 0x5D4 : 0x613;
        if (isSetsuna) {
            context._2C[n] = LAYOUT_FILENAME_SESTUNA;
        } else {
            context._2C[n] = LAYOUT_FILENAME_GUNSHOOT;
        }
    }
    return context;
}

}

OnGameEndGuide::OnGameEndGuide(Context::Kind kind)
    : _4(10)
    , mFade()
    , mLayout(lyt::LayoutContext(LAYOUT_FILENAME_COMMON, "TranslucentBg", lyt::LayoutContext::DefaultAllocator()))
    , mBox(common::boxmenu::Box(mLayout), common::boxmenu::Box(), "FadeIn", "FadeOut", 0, 0, 0, 0)
    , mButtons()
    , mSelectSequence(tSelectSequenceContext(kind), mLayout, mButtons)
    , mFlipGuide(FlipGuide::KIND_0, mLayout)
    , mBackButton(mLayout.pane("PauseCloseN"), false, true, 0x615)
    , _1BA4(9)
    , _1BA8(false)
    , _1BA9(false)
    , _1BAC(0) {
    mLayout.updateFrame();
    mLayout.updateMatrix();
    _4 = 0;
}
#undef MF_FUNCTION

OnGameEndGuide::~OnGameEndGuide() {
}

void OnGameEndGuide::start() {
    mBox.open();
    mLayout.updateFrame();
    mLayout.updateMatrix();
    _4 = 1;
    _1BA9 = false;
}

void OnGameEndGuide::reset() {
    _1BA4 = 9;
    mBox.fixToBeClosed();
    mLayout.pane("PauseCloseN").setVisibility(true);
    mSelectSequence.reset();
    _4 = 0;
    _1BA8 = false;
}

void OnGameEndGuide::startWithoutMenu() {
    mBox.close();
    mLayout.pane("PauseCloseN").setVisibility(false);
    _4 = 3;
    _1BA4 = 0;
    _1BA9 = false;
}

// TODO: hel::common::Color converts to a GXColor by value in its header; the original hands over its address.
void OnGameEndGuide::startOnlyFade() {
    mBox.close();
    mLayout.pane("PauseCloseN").setVisibility(false);
    mFade.setColor(reinterpret_cast<const GXColor&>(Color::BLACK));
    mFade.setFadeOut(45);
    _4 = 8;
    _1BA4 = 0;
}

bool OnGameEndGuide::enterA() {
    if (_4 != 2) {
        return false;
    }
    mSelectSequence.enter();
    return true;
}

bool OnGameEndGuide::enter2() {
    if (_4 != 4) {
        return false;
    }
    mFlipGuide.enter();
    return true;
}

bool OnGameEndGuide::back() {
    if (_4 != 2) {
        return false;
    }
    if (mSelectSequence.isFixed()) {
        return false;
    }
    _1BA4 = 8;
    _4 = 5;
    _1BAC = 0;
    mBackButton.push();
    return true;
}

bool OnGameEndGuide::up() {
    if (_4 != 2) {
        return false;
    }
    mSelectSequence.up();
    return true;
}

bool OnGameEndGuide::down() {
    if (_4 != 2) {
        return false;
    }
    mSelectSequence.down();
    return true;
}

bool OnGameEndGuide::select(const common::boxmenu::SelectableBox* box) {
    if (_4 != 2) {
        return false;
    }
    mSelectSequence.select(box);
    return true;
}

void OnGameEndGuide::updateMain() {
    switch (_4) {
    case 1:
        if (isBoxOpened()) {
            _4 = 2;
            mSelectSequence.start();
        }
        break;
    case 2:
        if (mSelectSequence.isEnd()) {
            _1BAC = 0;
            _1BA4 = mSelectSequence.nextSeq();
            if (_1BA4 == 0) {
                _4 = 3;
                mBox.mOpenAnim = "WindOpen";
                mBox.mCloseAnim = "WindClose";
                mBox.close();
                mLayout.pane("PauseCloseN").setVisibility(false);
            } else if (_1BA4 == 5) {
                mBox.mOpenAnim = "WindOpen";
                mBox.mCloseAnim = "WindClose";
                mBox.close();
                _1BA8 = true;
                _4 = 7;
            } else {
                mBox.mOpenAnim = "FadeIn";
                mBox.mCloseAnim = "FadeOut";
                mBox.close();
                _1BA8 = true;
                _4 = 6;
            }
        }
        break;
    case 5:
        if (mBackButton.isPushEnd()) {
            mSelectSequence.back();
            mBox.mOpenAnim = "FadeIn";
            mBox.mCloseAnim = "FadeOut";
            mBox.close();
            _1BA8 = true;
            _4 = 7;
        }
        break;
    case 7:
        if (mBox.isClosed()) {
            _4 = 9;
        }
        break;
    case 3:
        if (mBox.isClosed()) {
            _4 = 4;
            _1BA8 = true;
            mSelectSequence.hide();
            mBox.openImmediate();
            mFlipGuide.start();
            _1BA9 = true;
        }
        break;
    case 4:
        if (mFlipGuide.isEnd()) {
            _4 = 6;
            mBox.mCloseAnim = "FadeOut";
            mBox.close();
        }
        break;
    case 6:
        if (mBox.isClosed()) {
            _4 = 8;
            mFade.setColor(reinterpret_cast<const GXColor&>(Color::BLACK));
            mFade.setFadeOut(45);
        }
        break;
    case 8:
        if (mFade.isEnd()) {
            _4 = 9;
        }
        break;
    }
    mFade.update();
    mSelectSequence.updateMain();
    mFlipGuide.updateMain();
    mBox.updateMain();
    mBackButton.updateFrame();
    mLayout.updateFrame();
    mLayout.updateMatrix();
}

void OnGameEndGuide::updateDebug() {
    mSelectSequence.updateDebug();
    mFlipGuide.updateDebug();
}

void OnGameEndGuide::draw() const {
    lyt::Utility::SetupGX();
    mLayout.draw();
    mFade.draw();
}

bool OnGameEndGuide::isEnd() const {
    return _4 == 9;
}

int OnGameEndGuide::nextSeq() const {
    return _1BA4;
}

const common::pause::CursorContainedButtons& OnGameEndGuide::buttons() const {
    return mButtons;
}

bool OnGameEndGuide::isDisnableCursor() const {
    return _1BA8;
}

bool OnGameEndGuide::isOpenedFlipGuide() const {
    return _1BA9;
}

}}}}  // namespace scn::subgame::title::window
