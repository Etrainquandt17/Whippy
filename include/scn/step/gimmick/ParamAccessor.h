#ifndef SCN_STEP_GIMMICK_PARAMACCESSOR_H
#define SCN_STEP_GIMMICK_PARAMACCESSOR_H

#include "param/ParamAccessor.h"

namespace scn {
namespace step {
namespace gimmick {

template <class T>
class ParamAccessor {
public:
    ParamAccessor(const char* name) : mAccessor(name) {}
    // TODO: implicit in the original (92 bytes, like param::ParamAccessor's own, which param/ParamAccessor.h
    // does not declare yet).
    ~ParamAccessor();

    // TODO: 116 bytes, instantiated in every unit that uses it; the linker merged
    // them all into scn::step::camera::ParamAccessor::obj.
    const T& obj() const;
    const T* operator->() const { return &obj(); }

private:
    param::ParamAccessor mAccessor;
};

}}}  // namespace scn::step::gimmick

#endif
