#ifndef PAUSE_RESULT_H
#define PAUSE_RESULT_H

namespace pause {

// TODO: name the values. They are what the pause menu's dropout page can end with: continue (0), three ways of
// leaving the stage (1, 2, 7), back to the mode selection (3), back to the world map (4), again (5, 6) and the
// arena's own exit (8).
enum Result {
    RESULT_0,
    RESULT_1,
    RESULT_2,
    RESULT_3,
    RESULT_4,
    RESULT_5,
    RESULT_6,
    RESULT_7,
    RESULT_8,
};

}

#endif
