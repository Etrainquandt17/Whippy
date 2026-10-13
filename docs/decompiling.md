# Decompiling
This page is about how you turn one of the split objects back into source, and how you can tell that it's right. If you haven't built the project yet, do [Getting Started](getting_started.md) first, as everything here needs a finished build.

It goes through one unit from picking it to linking it. 2 other pages go with it. [Code Merging](code_merging.md) explains why a call in the disassembly often names a function that has nothing to do with the code you're reading, and [Object Classes](object_classes.md) describes what the game's classes look like once you've seen one of them.

## Picking a Unit
A unit is one source file of the original. `config/<ID>/splits.txt` lists them all, and after a build the disassembly of each one is in `build/<ID>/asm/<unit>.s`.

```sh
python tools/unwritten.py scn/step/enemy/   # units with no source yet, smallest first
python tools/status.py src/scn/step/enemy   # every source that exists, with its state
```

Start small. Most of the game is made of small classes that repeat (a state of an enemy, the manager of a gimmick), and a directory that already has a few finished units is the easiest place to add one, as the unit next to yours usually shows what yours looks like.

## Setting Up the Class
You don't have to guess names. The symbols are mangled C++ names, so every function comes with its namespace, its class and the types of its arguments, and the original link map (`orig/<ID>/files/iuk.MAP`) lists a unit's functions in the order they were written in. Most of a header is just copying that down.

What the symbols don't give you is the members. You read those from the code, and a member whose purpose you don't know yet is named after its offset.

```cpp
class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual void procAnim();

private:
    u32 mFrame;
    u8 _C[0x10];
    f32 _1C;
};
```

A class that you only need the size of, as some other class holds one, can be a stand-in until somebody writes its unit. That's an array of the right size with a `// TODO:` above it. Get the size right though. A stand-in that's too small doesn't break anything you can see, it just makes a stack frame in some other unit a few bytes short, and that's a pain to trace back.

Game code is compiled with `-O4,s -ipa file -opt nopeephole,noschedule -func_align 4` (`cflags_game` in `configure.py`). The tools below take each unit's flags from there, so they work for library units too.

## Writing and Comparing
Write the functions in `src/<unit>.cpp`, in the order the map has them, and compare.

```sh
python tools/compare.py all src/scn/step/hero/Heap.cpp
python tools/compare.py SUKE01 src/scn/step/hero/Heap.cpp -f setUse
```

The first form compiles the file for every version and tells you, per function and per data section, whether it matches the original object. The second one adds a side-by-side listing of the functions whose symbol contains the text you gave it, with `!=` in front of every line that differs. It compiles to a temporary file, so it never touches the build.

You don't have to write a unit in one go. A source file can hold just some of its unit's functions, and the tool then tells you how far along the unit is. When nothing is left it says `the unit is complete`. Sometimes it adds `as far as this can tell`, which means every function matches and the data holds something only a link can check.

A source that exists is compiled by the build even before it's linked, so a file that doesn't compile breaks the build for everyone. Keep your files compiling.

## Calls That Name the Wrong Function
Sooner or later the disassembly calls something absurd, like `GKI_getfirst` or `DefaultSwitchThreadCallback` on one of your objects. That isn't a mistake. The original link folded identical functions into one copy, so every tiny accessor that loads the word at offset 4 goes by the name of whichever one survived. Read the body of the function that's called, and name yours for what it does to your class. `compare.py` knows about the folding and accepts any name of the same group.

[Code Merging](code_merging.md) has the whole story, and [Object Classes](object_classes.md) has a table of the names that come up most.

## Inline Functions
Most of the small functions in the headers are inline in the original, and the compiler decides per unit what to do with them. A function that a unit uses once is expanded in place. One that it uses twice or more is called, and the unit gets its own copy of it. So the same accessor shows up as 3 loose instructions in one unit and as a `bl` in the next, and both are right.

A partly written unit has too few uses, which is one reason a function can refuse to match until the rest of its unit is there. It's also why some shared headers have 2 forms of one function. A unit picks the other form by defining a macro ahead of its includes.

```cpp
#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/bonkers/Custom.h"
```

Each of those is a stand-in, and the TODO above it in the header says what it's for. If you change whether a function in a shared header is inline, run `python tools/status.py src` afterwards. A line that starts with `LINKED BUT` is a linked unit that no longer matches because of it.

## Protected Functions
About 1,300 functions begin with a checksum over some other part of the game. That's MetaFortress, the game's copy protection, and [MetaFortress](metafortress.md) explains what it does. What matters here is that a tool added those checks to the source, so they all look alike, and we have a tool that writes them back.

```sh
python tools/metafortress_c.py SUKE01 onLanding__Q43scn4step5enemy9BrainBaseFv
```

It prints the function with the check written out as C and the game's own instructions as comment lines between the check's steps. Those comments are what you replace with statements. The check always has this shape:

```cpp
void ChoseData::PlayerData::initPlayer(u32 player) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0x811C9E29;
    asm { ... }
    i = 1;
    last = end;
    limit = last - start + 1;
    asm { ... }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001AB;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0) {
        const Kind kinds[] = { ... };
        initKind(kinds[player]);
    } else {
        ...
    }
}
```

A few things about it aren't optional. The check's 4 locals are declared in that order behind the `volatile` ones, there are no copies of `this` or of the parameters, and the loop has no extra variables. The function is wrapped in `#define MF_FUNCTION <name>` and `#undef MF_FUNCTION`, the way the tool prints it. The data that the check reads differs per version, so always compare with `all`.

When a protected function has every instruction right and the registers wrong, it's usually the order of the declarations, and `python tools/compare.py SUKE01 <file> -p "Class::function"` tries every order for you.

26 of these functions don't checksum anything. They decode the address of a hidden object through a long run of bit mixing instead. `ChallengeDoor::isUnlockEnd` is the finished one to read before you try another.

## Fixing Small Differences
Most functions match once the logic is right. When one doesn't, the listing from `-f` usually shows one of a handful of things, and each has a usual cure. Change one thing at a time and count the lines that still differ.

### The Registers Are Swapped
The instructions are the same, with 2 values in each other's registers. The compiler hands out the saved registers by the order the locals are declared in, so reorder the declarations (`-p` does that search for you). If that doesn't do it, the other thing to try is whether a value has a name at all, as a named local and the same expression written in place get ranked differently.

### A Stack Slot Is Off
Named locals sit above temporaries on the stack, and the first one declared sits highest. So when 2 vectors trade places, one of them was a temporary in the original and has a name in yours, or the other way around.

```cpp
effect.requestP(kind, obj().location().pos() + hel::math::Vector3(0.0f, 0.5f, 0.0f));   // the offset gets the lowest slot

hel::math::Vector3 offset(0.0f, 0.5f, 0.0f);                                           // now it gets the highest one
effect.requestP(kind, obj().location().pos() + offset);
```

### 2 Things Happen in the Other Order
The compiler doesn't go left to right. In `a() - b()` it calls `b` first, and a call written inside a product comes second whichever side it's on. If the original has it the other way, give the value you want first a name.

```cpp
f32 sign = obj().target().getSign();
if (sign * diff > 0.0f) {
    changeStateWallHit();
}
```

### The Branches Have Another Shape
The same logic written 2 ways gives 2 shapes, and the original only has one of them.

- `if (a && b) return true; return false;` loads 1, branches and loads 0. `return a && b;` doesn't.
- `x = c ? f() : g();` stores once. An `if` with an `else` stores twice.
- A `switch` on an enum compares signed (`cmpwi`), and one on a `u32` compares unsigned (`cmplwi`).

### The Float Constants Are in Another Order
A unit's float constants go into `.sdata2` in the order the compiler first met them, so every function can match while the data doesn't. Giving a value a name moves its constant. `f32 t = a / b; SinDegF(90.0f * t)` and `SinDegF(90.0f * (a / b))` are the same code with 2 constants the other way round.

### The Stack Frame Is Too Small
If every instruction is right and the frame is a few bytes short, a class in some shared header is declared too small. The class to look at is usually the largest thing on that function's stack.

### Only One Version Differs
The versions really do differ in places. Effect numbers from about 0x62E up are one higher in the Korean build, and a few functions have code only one version has. `#ifdef VERSION_SUKK01` is how the source says so.

## Linking a Unit
A unit that compares complete in every version isn't done until the game is linked with it in place of the original object.

```sh
python tools/link_complete.py src/scn/step/hero   # test the complete units there and mark the good ones
python tools/check_all.py                         # build and check the DOL of every version
```

`link_complete.py` links the game with each candidate compiled from source, changes the ones that come out identical from `NonMatching` to `Matching` in `configure.py`, and remembers the others in `config/not_linkable.txt` (`--retry` tries those again). `check_all.py` is the proof, as the build fails when a DOL isn't byte for byte the original anymore.

When a complete unit doesn't link, `python tools/linktest.py SUKE01 -u <unit> --map` tells you where the link went another way. It's nearly always code merging again. Either the linker folded your function into a look-alike that the original kept apart, or the original folded it into a function whose unit isn't written yet. [Code Merging](code_merging.md) goes through the cases.

There's one failure that isn't your fault. `FAILED: [code=3221225477] build/SUKK01/main.elf` with no error text is the linker itself crashing. It has a fault that depends on the size of the environment it was started with, and nothing is wrong with the tree when it happens. Run the build again with one more environment variable set (any name, 20 characters or so of value) and it goes through. `check_all.py` and `linktest.py` do that by themselves, a plain `ninja` doesn't.

## Mint Bindings
Each library has an `AddOnMint.cpp` that registers its functions with Mint, the game's script engine. They're long, regular, and quick to write once one of them is right. A binding is `MINT_NATIVE_FUNCTION(core, module, declaration, name, function)` from `mintglue/WrapNative.h`, and the functions it generates come out behind the registration function, in reverse order of the bindings. `scn/step/enemy/como/AddOnMint.cpp` is the smallest one to read.

## Conventions
- Namespaces, class names and function signatures come from the mangled symbol names.
- Members whose purpose is unknown are named after their offset, like `u8 _4[0x60];` and `u32 _64;`.
- Anything that stands in for the real thing gets a `// TODO:` that says what the original has.
- Comments are for what a reader couldn't work out by themselves, which is a TODO, a surprise or a bug in the game. They aren't for what the code plainly does.

## Known Issues
### `SuperSword::tryToChangeState` doesn't match
It's the largest of the hidden-object functions, with 902 instructions of mixing. The best form we have has all of them, with 280 lines that still differ, nearly all of them in the registers. The 4 other super abilities are finished and can't be linked until it matches.

### Some one-argument Mint bindings have 2 registers swapped
Where a one-argument binding is expanded whole, the argument index and the register set come out in each other's registers (`scn/step/enemy/clayn`, `knucklejoe`, `pluid`, `scn/step/boss/kingsdoo`). One more level of inlining fixes those and breaks all the others, so we don't know what the original header looked like there.
