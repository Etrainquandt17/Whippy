#ifndef EFFECT_REQUESTOR_H
#define EFFECT_REQUESTOR_H

#include "types.h"

namespace g3d {
class ModelAccessor;
class ModelAnimAccessor;
}

namespace effect {

class Group;
class Manager;

namespace detail {
class RequestArg;
}

// TODO: name the members.
class Requestor {
public:
    Requestor(Manager& manager);
    ~Requestor();

    void request(const detail::RequestArg& arg);
    void autoRequestOnUpdateFrame(const g3d::ModelAccessor& model, const g3d::ModelAnimAccessor& anim);
    void autoRequestOnSetFrame(const g3d::ModelAccessor& model, const g3d::ModelAnimAccessor& anim);
    void changeGroup(Group& group);
    void release();
    void releaseAndVanish();
    void pauseInc();
    void pauseDec();
    void pauseReset();

private:
    u32 _0[0x1C / 4];
};

}

#endif
