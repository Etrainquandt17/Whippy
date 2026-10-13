#ifndef OSTOP_REQHANDLE_H
#define OSTOP_REQHANDLE_H

#include "types.h"

namespace ostop {

class ReqHandle {
public:
    ReqHandle();
    ReqHandle(u32 id);

    bool isValid() const;
    u32 id() const;

private:
    bool mIsValid;
    u32 mId;
};

}

#endif
