#ifndef PRELOAD_PRELOADMANAGER_H
#define PRELOAD_PRELOADMANAGER_H

#include "mem/MemBlock.h"
#include "types.h"

namespace preload {

class PreLoadManager {
public:
    class FindResult {
    public:
        FindResult();
        FindResult(const mem::MemBlock& block);

        bool isValid() const;
        mem::MemBlock block() const;

    private:
        bool mIsValid;
        mem::MemBlock mBlock;
    };

    PreLoadManager();
    ~PreLoadManager();

    void waitToFinishLoading();
    void reset();
    void cancel();
    FindResult find(const char* path);

private:
    u8 _0[0xBB64];
};

}  // namespace preload

#endif
