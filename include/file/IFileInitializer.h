#ifndef FILE_IFILEINITIALIZER_H
#define FILE_IFILEINITIALIZER_H

#include "mem/MemBlock.h"

namespace file {

// TODO: the name of the second virtual function is not known.
class IFileInitializer {
public:
    virtual ~IFileInitializer();
    virtual void initialize(mem::MemBlock& block) const;
};

}

#endif
