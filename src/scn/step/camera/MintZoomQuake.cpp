#include "scn/step/camera/MintZoomQuake.h"

#include "hel/common/PointerWrapper.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace camera {

namespace {

PointerWrapper<ZoomQuake> t_obj;

}

namespace MintZoomQuake {

void Register(ZoomQuake& obj) {
    t_obj.set(obj);
}

void Unregister(ZoomQuake&) {
    t_obj.reset();
}

ZoomQuake& Obj() {
    return t_obj.ref();
}

}}}}  // namespace scn::step::camera::MintZoomQuake
