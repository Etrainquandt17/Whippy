#ifndef G3D_MODELANIMACCESSOR_H
#define G3D_MODELANIMACCESSOR_H

#include "types.h"

namespace g3d {

class ModelAnim;
class IModelAnimAccessorEventReceiver;

class ModelAnimAccessor {
public:
    ModelAnimAccessor();
    ModelAnimAccessor(ModelAnim& anim, IModelAnimAccessorEventReceiver& receiver);

    // TODO: implicit in the original, which calls the compiler's own copy of it.
    // With -ipa file the compiler copies the two words in place instead, so it is
    // declared here to keep the call. Remove once game code is built without -ipa file.
    ModelAnimAccessor& operator=(const ModelAnimAccessor& other);

    void start(bool doLoop) const;
    void stop() const;
    bool isValid() const;
    bool isAnimating() const;
    bool isAnimEnd() const;
    f32 frame() const;
    int totalFrame() const;
    void setFrame(f32 frame) const;
    void setFrameToHead() const;
    void setFrameToTail() const;
    void setFrameRate(f32 rate) const;

private:
    ModelAnim* mAnim;
    IModelAnimAccessorEventReceiver* mReceiver;
};

}

#endif
