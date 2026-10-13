#ifndef SFX_WIPE_H
#define SFX_WIPE_H

#include "types.h"
#include "util/FrameCounter.h"

namespace hel {
namespace math {
class Vector2;
}}  // namespace hel::math

namespace sfx {

// TODO: its own unit and its members; only what sfx::Wipe calls.
class FullScreenModel {
public:
    FullScreenModel(const char* name);
    ~FullScreenModel();

    void setModel(const char* name);
    void setAnim(const char* name);
    bool isExistModel() const;
    bool isAnimEnd() const;
    f32 totalFrame() const;
    f32 frameRate() const;
    void setFrameRate(f32 rate);
    void setFrameToTail();
    void setLayoutPos(const hel::math::Vector2& pos);
    void setVisibility(bool visible);
    void start(bool doLoop);
    void updateFrame();
    void updateMain();
    void updateUseGPU();
    void draw();
};

class Wipe {
public:
    Wipe();
    ~Wipe();

    void requestWipeIn(const char* name, unsigned long wait, unsigned long frame);
    void requestWipeOut(const char* name, unsigned long wait, unsigned long frame);
    bool isAnimEnd() const;
    bool isNeedToDraw() const;
    void setLayoutPos(const hel::math::Vector2& pos);
    void updateMain();
    void updateUseGPU();
    void draw();

private:
    void checkAnimStart();
    void modelSetup(const char* name, unsigned long frame);

    util::FrameCounter mCounter;
    FullScreenModel mModel;
};

}  // namespace sfx

#endif
