#ifndef SCN_TITLEMENUNEW_OPTION_H
#define SCN_TITLEMENUNEW_OPTION_H

#include "info/sequence/Sequence.h"
#include "lyt/Layout.h"
#include "scn/titlemenunew/IModeButton.h"
#include "types.h"

namespace info {
class AnimSyncer;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace titlemenunew {

class Option : public IModeButton {
public:
    // TODO: name the values.
    enum Kind {
        KIND_0,
        KIND_1,
        KIND_2,
    };

    Option(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Kind kind, info::AnimSyncer& animSyncer);

    void updateFrame();
    void enable(bool flag);
    void complete();
    void unlockComplete();
    void selectPanel(Kind kind, bool flag);

    virtual lyt::PaneAccessor parent();
    virtual void setParent(const lyt::PaneAccessor& parent);
    virtual lyt::PaneAccessor cursorParent();
    virtual void focus();
    virtual void unfocus();
    virtual void decide();
    virtual void unlock();
    virtual bool isAnimEnd() const;

private:
    lyt::Layout mLayout;
    lyt::Layout _194;
    int _324;
    bool _328;
    info::sequence::Sequence mSequence;
    info::AnimSyncer* mAnimSyncer;
};

}}  // namespace scn::titlemenunew

#endif
