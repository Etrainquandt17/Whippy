#ifndef HID_SIMPLEWRHID_H
#define HID_SIMPLEWRHID_H

#include "hid/Button.h"
#include "types.h"

namespace hid {

class SimpleWRHID {
public:
    Button button() const;
    Button buttonClassic() const;
    bool isConnected() const;

private:
    // TODO: names and types. The sizes are what the implicit copy constructor shows.
    u32 _0[0x4C];
    u32 _130[3];
    Button _13C;
    f32 _148;
    u32 _14C[2];
    u32 _154[2];
    bool _15C;
    Button _160;
};

}

#endif
