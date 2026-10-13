#ifndef SCN_SUBGAME_TITLE_WINDOW_ONGAMEENDGUIDE_H
#define SCN_SUBGAME_TITLE_WINDOW_ONGAMEENDGUIDE_H

#include "lyt/Layout.h"
#include "scn/subgame/Context.h"
#include "scn/subgame/common/boxmenu/ClosableBox.h"
#include "scn/subgame/common/pause/CursorContainedButtons.h"
#include "scn/subgame/common/util/BackButton.h"
#include "scn/subgame/title/window/Fade.h"
#include "scn/subgame/title/window/FlipGuide.h"
#include "scn/subgame/title/window/IGuide.h"
#include "scn/subgame/title/window/SelectSequence.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace title {
namespace window {

class OnGameEndGuide : public IGuide {
public:
    OnGameEndGuide(Context::Kind kind);

    virtual ~OnGameEndGuide();
    virtual void start();
    virtual void reset();
    virtual bool up();
    virtual bool down();
    virtual bool left() { return up(); }
    virtual bool right() { return down(); }
    virtual bool enterA();
    virtual bool enter2();
    virtual bool back();
    virtual bool select(const common::boxmenu::SelectableBox* box);
    virtual void updateMain();
    virtual void updateDebug();
    virtual void draw() const;
    virtual bool isEnd() const;
    virtual int nextSeq() const;
    virtual const common::pause::CursorContainedButtons& buttons() const;
    virtual bool isDisnableCursor() const;

    void startWithoutMenu();
    void startOnlyFade();
    bool isOpenedFlipGuide() const;

private:
    bool isBoxOpened() const { return mBox.is() == 3; }

    int _4;
    Fade mFade;
    lyt::Layout mLayout;
    common::boxmenu::ClosableBox mBox;
    common::pause::CursorContainedButtons mButtons;
    SelectSequence mSelectSequence;
    FlipGuide mFlipGuide;
    common::util::BackButton mBackButton;
    int _1BA4;
    bool _1BA8;
    bool _1BA9;
    int _1BAC;
};

}}}}  // namespace scn::subgame::title::window

#endif
