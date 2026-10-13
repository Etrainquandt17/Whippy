#ifndef EFFECT_REQUESTOR_H
#define EFFECT_REQUESTOR_H

namespace g3d {
class ModelAccessor;
class ModelAnimAccessor;
}

namespace effect {

namespace detail {
class RequestArg;
}

class Requestor {
public:
    void request(const detail::RequestArg& arg);
    void autoRequestOnUpdateFrame(const g3d::ModelAccessor& model, const g3d::ModelAnimAccessor& anim);
    void autoRequestOnSetFrame(const g3d::ModelAccessor& model, const g3d::ModelAnimAccessor& anim);
};

}

#endif
