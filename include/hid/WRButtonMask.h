#ifndef HID_WRBUTTONMASK_H
#define HID_WRBUTTONMASK_H

namespace hid {

// TODO: the names are guesses. The values are the remote's button bits, as hid::Button::isHold takes them.
enum WRButtonMask {
    WR_BUTTON_MASK_PLUS = 0x10,
    WR_BUTTON_MASK_2 = 0x100,
    WR_BUTTON_MASK_1 = 0x200,
    WR_BUTTON_MASK_B = 0x400,
    WR_BUTTON_MASK_A = 0x800,
};

}  // namespace hid

#endif
