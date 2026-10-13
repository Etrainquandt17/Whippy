#ifndef INFO_SEQUENCE_SEQUENCE_H
#define INFO_SEQUENCE_SEQUENCE_H

#include "hel/common/MutableArray.h"
#include "mem/IAllocator.h"
#include "std/tr1/function.h"
#include "types.h"

namespace lyt {
class Layout;
}

namespace info {
namespace sequence {

class Command;

class Sequence {
public:
    Sequence(mem::IAllocator& allocator);
    ~Sequence();

    void update();
    Sequence& anim(lyt::Layout& layout, const char* name);
    Sequence& animAsync(lyt::Layout& layout, const char* name);
    Sequence& wait(u32 frame);
    Sequence& wait(const std::tr1::function<bool()>& function);
    Sequence& waitAnimEnd(lyt::Layout& layout);
    Sequence& call(const std::tr1::function<void()>& function);
    Sequence& flag(bool& flag);
    Sequence& proc(const std::tr1::function<bool()>& function);
    Sequence& interval(u32 interval, const std::tr1::function<bool()>& function);
    Sequence& checkPoint(const char* name);
    Sequence& run(Sequence& sequence);
    Sequence& branch(const std::tr1::function<bool()>& function, Sequence& onTrue, Sequence& onFalse);
    void start();
    void stop();
    bool running() const;
    bool isEnd() const;
    void clear();
    void nextCommand();

private:
    template <class T>
    void* alloc() {
        return mAllocator.allocatorAlloc(sizeof(T), 4);
    }

    mem::IAllocator& mAllocator;
    hel::common::MutableArray<Command*, 64> mCommands;
    int mIndex;
    bool mIsRunning;
};

}}  // namespace info::sequence

#endif
