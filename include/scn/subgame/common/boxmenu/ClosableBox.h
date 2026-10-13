#ifndef SCN_SUBGAME_COMMON_BOXMENU_CLOSABLEBOX_H
#define SCN_SUBGAME_COMMON_BOXMENU_CLOSABLEBOX_H

#include "scn/subgame/common/boxmenu/Box.h"
#include "scn/subgame/common/util/AbstractSuspendableTree.h"
#include "scn/subgame/common/view/SystemSERequestor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace boxmenu {

class AbstractUpdatingBox {
public:
    virtual ~AbstractUpdatingBox() {}
    virtual void updateMain() {}
    virtual void updateDebug() {}
};

class ClosableBox : public util::AbstractSuspendableTree, public AbstractUpdatingBox {
public:
    ClosableBox(Box box, Box subBox, const char* openAnim, const char* closeAnim, const char* openedAnim, const char* closedAnim,
                const char* subOpenAnim, const char* subCloseAnim);

    virtual ~ClosableBox();
    virtual bool isSuspend() const;
    virtual void suspend();
    virtual void resume();
    virtual bool isExclusivelyResume() const;
    virtual void updateMain();

    int is() const;
    void open();
    bool isClosed() const;
    void close();
    bool isOpened() const;
    void openImmediate();
    void closeImmediate();
    void fixToBeOpened();
    void fixToBeClosed();
    void setOpenSELabel(unsigned long label);
    void setCloseSELabel(unsigned long label);
    void stopOpenSE();

private:
    void initialize();
    void setStatusOnOpening();
    void setStatusOnClosing();

public:
    const char* mOpenAnim;
    const char* mCloseAnim;

private:
    const char* mOpenedAnim;
    const char* mClosedAnim;
    const char* mSubOpenAnim;
    const char* mSubCloseAnim;
    Box mBox;
    Box mSubBox;
    int mStatus;
    bool _68;
    bool _69;
    bool mIsSuspend;
    view::SystemSERequestor mOpenSE;
    view::SystemSERequestor mCloseSE;
    u32 mOpenSELabel;
    u32 mCloseSELabel;
};

}
}
}
}

#endif
