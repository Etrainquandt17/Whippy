#ifndef SCN_CHALLENGETUTORIAL_INFO_MANAGER_H
#define SCN_CHALLENGETUTORIAL_INFO_MANAGER_H

#include "lyt/Layout.h"
#include "mem/AutoHeapExp.h"
#include "scn/challengetutorial/info/Tutorial.h"
#include "snd/SERequestor.h"
#include "types.h"

namespace scn {
namespace challengetutorial {
namespace info {

class Manager {
public:
    Manager(bool isExtraMode);
    ~Manager();

    void procAnim();
    void procReadyToRender();
    void draw() const;
    bool isExtraMode() const;

    Tutorial& tutorial() { return mTutorial; }

private:
    mem::AutoHeapExp mHeap;
    lyt::Layout mLayout;
    bool mIsExtraMode;
    Tutorial mTutorial;
    snd::SERequestor mSE;
};

}
}
}

#endif
