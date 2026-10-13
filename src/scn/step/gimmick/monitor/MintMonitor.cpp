#include "scn/step/gimmick/monitor/MintMonitor.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace gimmick {
namespace monitor {

namespace {

hel::common::PointerWrapper<Monitor> t_obj;

}

void MintMonitor::Register(Monitor& obj) {
    t_obj.set(obj);
}

void MintMonitor::Unregister(Monitor&) {
    t_obj.reset();
}

Monitor& MintMonitor::Obj() {
    return t_obj.ref();
}

}}}}  // namespace scn::step::gimmick::monitor
