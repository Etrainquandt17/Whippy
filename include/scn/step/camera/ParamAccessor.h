#ifndef SCN_STEP_CAMERA_PARAMACCESSOR_H
#define SCN_STEP_CAMERA_PARAMACCESSOR_H

#include "param/ParamAccessor.h"
#include "scn/step/camera/Param.h"

namespace scn {
namespace step {
namespace camera {

class ParamAccessor {
public:
    ParamAccessor() : mAccessor("step/camera/Camera") {}

    const Param& obj() const;

private:
    param::ParamAccessor mAccessor;
};

}
}
}

#endif
