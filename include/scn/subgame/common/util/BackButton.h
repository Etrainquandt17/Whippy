#ifndef SCN_SUBGAME_COMMON_UTIL_BACKBUTTON_H
#define SCN_SUBGAME_COMMON_UTIL_BACKBUTTON_H

#include "info/common/ButtonHelp.h"
#include "snd/SystemSERequestor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace util {

class BackButton : public info::common::ButtonHelp {
public:
    BackButton(const lyt::PaneAccessor& pane, bool blinks, bool isTwo, u32 seId);

    void push();

private:
    snd::SystemSERequestor mSE;
    u32 mSEId;
};

}
}
}
}

#endif
