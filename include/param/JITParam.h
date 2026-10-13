#ifndef PARAM_JITPARAM_H
#define PARAM_JITPARAM_H

#include "param/ParamAccessor.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace param {

class JITParam {
public:
    JITParam(const char* name);
    ~JITParam();

    void loadCheck() const;

    template <typename T>
    const T& data() const {
        loadCheck();
        return *static_cast<const T*>(mAccessor->xdata().dataHeadAddress());
    }

private:
    const char* mName;
    mutable util::PlacementNew<ParamAccessor> mAccessor;
};

}

#endif
