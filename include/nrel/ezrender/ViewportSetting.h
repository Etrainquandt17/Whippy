#ifndef NREL_EZRENDER_VIEWPORTSETTING_H
#define NREL_EZRENDER_VIEWPORTSETTING_H

#include "types.h"

namespace nrel {
namespace ezrender {

// TODO: the member names are guesses after GXSetViewport.
class ViewportSetting {
public:
    static ViewportSetting create(f32 left, f32 top, f32 width, f32 height, f32 nearZ, f32 farZ);

    void execute() const;

    f32 mLeft;
    f32 mTop;
    f32 mWidth;
    f32 mHeight;
    f32 mNear;
    f32 mFar;
};

}}  // namespace nrel::ezrender

#endif
