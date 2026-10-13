#ifndef PAUSE_IPAGE_H
#define PAUSE_IPAGE_H

#include "types.h"

namespace lyt {
class Layout;
}

namespace pause {

class IPage {
public:
    virtual ~IPage();
    virtual const wchar_t* pageFrameTitle() const = 0;
    virtual lyt::Layout& pageMainLayout() = 0;
    virtual void pageProcAnim() = 0;
    virtual void pageProcHID() = 0;
    virtual bool pageIsBusy() const = 0;
};

}

#endif
