#include "scn/step/camera/MintZoomQuake.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace camera {

namespace {

hel::common::PointerWrapper<ZoomQuake> t_obj;

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
