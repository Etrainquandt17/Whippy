#ifndef HID_LIBINITIALIZER_H
#define HID_LIBINITIALIZER_H

#include "hel/common/PrivateSingleton.h"

namespace hid {

class LibInitializer : public hel::common::PrivateSingleton<LibInitializer> {
public:
    LibInitializer();
    ~LibInitializer();
};

}

#endif
