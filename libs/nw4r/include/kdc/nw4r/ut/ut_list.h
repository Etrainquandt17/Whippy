#ifndef NW4R_UT_LIST_H
#define NW4R_UT_LIST_H
#include "kdc/nw4r/types_nw4r.h"

namespace nw4r {
namespace ut {

struct List {
    void *first; // at 0x0
    void *last;  // at 0x4
    u16 size;    // at 0x8
    u16 offset;  // at 0xA
};

struct Link {
    void *prev; // at 0x0
    void *next; // at 0x4
};

//NOTE: Is merged into MEMInitList
void List_Init(List *list, u16 offset);
//NOTE: Is merged into MEMAppendListObject
void List_Append(List *list, void *object);
void List_Prepend(List *list, void *object);
void List_Insert(List *list, void *next, void *object);
//NOTE: Is merged into MEMRemoveListObject
void List_Remove(List *list, void *object);
//NOTE: Is merged into MEMGetNextListObject
void *List_GetNext(const List *list, const void *object);
void *List_GetPrev(const List *list, const void *object);
void *List_GetNth(const List *list, u16 n);

inline void *List_GetFirst(const List *list) {
    return List_GetNext(list, NULL);
}

inline const void *List_GetFirstConst(const List *list) {
    return List_GetFirst(list);
}

inline void *List_GetLast(const List *list) {
    return List_GetPrev(list, NULL);
}

inline const void *List_GetLastConst(const List *list) {
    return List_GetLast(list);
}

inline const void *List_GetNextConst(const List *list, const void *object) {
    return List_GetNext(list, object);
}

inline const void *List_GetNthConst(const List *list, u16 n) {
    return List_GetNth(list, n);
}

inline u16 List_GetSize(const List *list) {
    return list->size;
}

/******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/
/**
 * Declares a member Link.
 */
#define NW4R_UT_LIST_LINK_DECL() nw4r::ut::Link link

/**
 * Initializes a List object for use with the specified type.
 *
 * @param LIST Reference to list
 * @param T List element type
 */
#define NW4R_UT_LIST_INIT(LIST, T)                                             \
    nw4r::ut::List_Init(&(LIST), offsetof(T, link))

/**
 * Gets the underlying Link within the specified object.
 *
 * @param LIST Reference to list
 * @param OBJ Pointer to list object
 */
#define NW4R_UT_LIST_GET_LINK(LIST, OBJ)                                       \
    reinterpret_cast<nw4r::ut::Link*>((u8*)(OBJ) + (LIST).offset)

/**
 * List for-each macro.
 *
 * @param TYPE Element type
 * @param NAME Element name
 * @param LIST Reference to list
 * @param ... Statement(s) to execute
 */
#define NW4R_UT_LIST_FOREACH(TYPE, NAME, LIST, ...)                            \
    {                                                                          \
        TYPE* NAME = NULL;                                                     \
                                                                               \
        while ((NAME = static_cast<TYPE*>(                                     \
                    nw4r::ut::List_GetNext(&(LIST), NAME))) != NULL) {         \
                                                                               \
            __VA_ARGS__;                                                       \
        }                                                                      \
    }
/**
 * List for-each macro (reverse order).
 *
 * @param TYPE Element type
 * @param NAME Element name
 * @param LIST Reference to list
 * @param ... Statement(s) to execute
 */
#define NW4R_UT_LIST_FOREACH_REV(TYPE, NAME, LIST, ...)                        \
    {                                                                          \
        TYPE* NAME = NULL;                                                     \
                                                                               \
        while ((NAME = static_cast<TYPE*>(                                     \
                    nw4r::ut::List_GetPrev(&(LIST), NAME))) != NULL) {         \
                                                                               \
            __VA_ARGS__;                                                       \
        }                                                                      \
    }

/**
 * List for-each macro, with robust iteration.
 *
 * @param TYPE Element type
 * @param NAME Element name
 * @param LIST Reference to list
 * @param ... Statement(s) to execute
 */
#define NW4R_UT_LIST_FOREACH_SAFE(TYPE, NAME, LIST, ...)                       \
    {                                                                          \
        TYPE* NAME;                                                            \
        TYPE* __next__;                                                        \
                                                                               \
        for (NAME = static_cast<TYPE*>(nw4r::ut::List_GetFirst(&(LIST)));      \
             NAME != NULL; NAME = __next__) {                                  \
                                                                               \
            __next__ =                                                         \
                static_cast<TYPE*>(nw4r::ut::List_GetNext(&(LIST), NAME));     \
                                                                               \
            __VA_ARGS__;                                                       \
        }                                                                      \
    }

} // namespace ut
} // namespace nw4r

#endif
