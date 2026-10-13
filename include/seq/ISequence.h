#ifndef SEQ_ISEQUENCE_H
#define SEQ_ISEQUENCE_H

#include "std/auto_ptr.h"
#include "types.h"

namespace hel {
namespace common {
class RuntimeTypeInfo;
}
}

namespace scn {
class IScene;
}

namespace seq {

class ISequence {
public:
    static void* operator new(u32 size);
    static void operator delete(void* ptr);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const = 0;
    virtual ~ISequence() {}
    virtual int nextAction() const = 0;
    virtual std::auto_ptr<ISequence> createChildSequence() const = 0;
    virtual void onChildSequenceEnd(ISequence& child) = 0;
    virtual std::auto_ptr<scn::IScene> createScene() const = 0;
    virtual void onSceneEnd(scn::IScene& scene) = 0;
};

}

#endif
