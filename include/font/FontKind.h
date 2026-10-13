#ifndef FONT_FONTKIND_H
#define FONT_FONTKIND_H

namespace font {

// The values are named after the font files; the original names are not known.
enum FontKind {
    FONT_KIND_0,
    FONT_KIND_COMMON_EB = FONT_KIND_0,
    FONT_KIND_COMMON_EBP,
    FONT_KIND_COMMON_EBOL,
    FONT_KIND_COMMON_EBOLP,
    FONT_KIND_EXTERNAL_CHAR,
#ifndef VERSION_SUKK01
    FONT_KIND_RUBY,
#endif
    FONT_KIND_MOVIE,
    FONT_KIND_STAFF_CREDITS,
    FONT_KIND_GUN_SHOOTING,
    FONT_KIND_SETSUNA1,
    FONT_KIND_SETSUNA2,
    FONT_KIND_SETSUNA3,
    FONT_KIND_NUM,
};

}  // namespace font

#endif
