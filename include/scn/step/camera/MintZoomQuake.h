#ifndef SCN_STEP_CAMERA_MINTZOOMQUAKE_H
#define SCN_STEP_CAMERA_MINTZOOMQUAKE_H

namespace scn {
namespace step {
namespace camera {

class ZoomQuake;

namespace MintZoomQuake {

void Register(ZoomQuake& obj);
void Unregister(ZoomQuake& obj);
ZoomQuake& Obj();

}}}}  // namespace scn::step::camera::MintZoomQuake

#endif
