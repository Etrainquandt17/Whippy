#ifndef SCN_STEP_CAMERA_MINTCAMERACONTROLLER_H
#define SCN_STEP_CAMERA_MINTCAMERACONTROLLER_H

namespace scn {
namespace step {
namespace camera {

class CameraController;

namespace MintCameraController {

void Register(CameraController& obj);
void Unregister(CameraController& obj);
CameraController& Obj();

}
}
}
}

#endif
