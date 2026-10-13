#ifndef SCN_STEP_GIMMICK_SHIPEVENT_SHIPEVENT_H
#define SCN_STEP_GIMMICK_SHIPEVENT_SHIPEVENT_H

#include "snd/SERequestor.h"
#include "types.h"

namespace scn {
namespace step {
namespace gimmick {
namespace shipevent {

class ShipEvent {
public:
    class SEFadeRequester {
    public:
        void request(u32 id);
        void mfRequestCommon(u32 id);

    private:
        bool _0;
        bool _1;
        snd::SERequestor mSE;
    };
};

}
}
}
}

#endif
