# Code Merging
The game was linked with CodeWarrior's code merging optimization (`-code_merging`), which looks for functions with identical machine code and keeps only one copy. It changes what a matching build has to reproduce.

## What the Linker Did
The first 76,500 lines of `iuk.MAP` are the linker's own account of it:

```
--> duplicated code: symbol __dt__Q23std13bad_exceptionFv is duplicated by __dt__Q23std9exceptionFv, size = 64

--> the function __dt__Q23std13bad_exceptionFv will be replaced by a branch to __dt__Q23std9exceptionFv
```

10,978 functions were found to duplicate another one. If you compare those messages with the section layout further down the map, you'll see 3 outcomes:

- 4,798 were *replaced by a branch*. The symbol keeps its place in link order but shrinks to 4 bytes, so `__dt__Q23std13bad_exceptionFv` at `0x80008AF0` is a single `b 0x80006BD0`. Everything after it in its object moves up.
- 4,536 were *removed*. They don't show up in the section layout at all, and whatever referred to them uses the surviving copy. `OSGetArenaHi` is one of them, only `OSGetMEM1ArenaHi` exists in the DOL.
- 1,644 were reported and left as they were.

For 35 pairs the linker also notes that the two functions were "interchanged", meaning it swapped which of them survives.

Merging isn't limited to game code, or to functions that have anything to do with each other. 226 empty functions from all over the program were folded into the SDK's `DefaultSwitchThreadCallback`, and 310 identical destructors into `hel::geo::Rect::~Rect`.

The DOL contains 5,997 four-byte functions that are just one unconditional branch. Most of them are these stubs, the rest are ordinary tail calls.

## What It Means for This Project
`symbols.txt` describes the DOL after merging. A stub is recorded as a four-byte function, and a removed function isn't recorded at all, its name only survives in the messages at the top of the original map. That's all the split objects need, and the baseline links without code merging.

Once a translation unit is decompiled, the compiler produces every function at full size again and calls every function by its own name. There are 3 cases that follow from that, and all 3 of them link from source now.

### Removed Functions
A removed function has no name left in the DOL, so source that calls one can't link against the split objects, and source that defines one adds bytes the original doesn't have. The linker script solves both. It assigns each removed name the address of the copy that survived:

```
    __dt__Q33hel6common11NonCopyableFv = 0x801A79AC;
```

`python tools/aliases.py <ID> --write` builds `config/<ID>/ldscript.lcf` from `config/ldscript.lcf` with one of those lines for each of the 4,536 removed functions (4,537 in the Korean build). The list comes from the messages at the top of the original map, and every removed function has exactly one surviving copy of its size.

A call to a removed function resolves to the assigned address, which is what the original instruction holds. A unit that defines a removed function itself (an inline destructor for example) links too. The linker warns that the symbol "is also defined as a linker generated symbol", uses the assignment, and drops the compiled copy as unreferenced.

`mint::Manager` shows both. It calls `hel::common::NonCopyable::~NonCopyable` and emits `mint::ScriptArchive::~ScriptArchive`, and its unit is linked from source.

### Strings of Inline Functions
An inline function's string literals are weak, just like the function. Every unit that uses the function carries a copy, and the link keeps the first one. `symbols.txt` lists them as `@STRING@<function>`, and they have to be `scope:weak` there. As `scope:local` the copy in a split object is invisible to a compiled unit, which then uses its own copy where the original used the first one in link order. All 524 are weak now.

Keeping the first one doesn't remove the others. The symbol goes to the first copy and every unit refers to that one, but the bytes of a later copy stay where they were, in their own unit's `.data`, as data nothing refers to. The splitter shows them as an unnamed object at the end of the unit's `.data`. `lbl_8076C4C0` in `pause/PageAbility` is the two assertion strings of `nw4r::ut::LinkList`, and 86 game units have that pair. A unit compiled from source has to emit its copy, at the same place, in order to link identically. So a string of an inline function in the original object is evidence that the unit saw that function's body, and a missing one is evidence that it didn't.

Inline functions themselves don't need anything. The split object's copy is global, and it wins over the weak copy in a compiled unit.

### Functions Replaced by a Branch
The original keeps a four-byte `b` in the function's place, and only the linker's own merging can produce that. It takes two settings to make it do so:

- `-code_merging all` in the ldflags of `configure.py`.
- `noexport` on the surviving copy in `symbols.txt`. decomp-toolkit exports every symbol of a split object, and exported functions are neither merged nor merged into. With the survivor un-exported, the linker folds the compiled function into it and leaves a branch behind, just like the original link did.

`mintvm::IAllocator::~IAllocator` in `mintvm/MintSetting.cpp` was the first one. Its look-alike is `hel::geo::Rect::~Rect`, which is un-exported in both versions. You can find which function a branch goes to in the original map (`the function X will be replaced by a branch to Y`).

`tools/compare.py` shows a function like this as `replaced by a branch to a look-alike by the original link` when the compiled body has the size the map gives for it.

The look-alike isn't the same function in every version. `app::Locale::GetRegion` returns a constant that differs by region, so it's a branch to `nw4r::ut::DvdFileStream::CanCancel` in the US build and to `nw4r::ut::PairFont::GetType` in the Korean one. Each version's `symbols.txt` un-exports its own.

That's enough as long as the function calls nothing that was folded itself. Where it does, the look-alike has to be compiled from source as well. The linker compares two functions by the symbols they refer to, before it folds anything. A compiled destructor calls its base's destructor by its own name, and the same call in a split object names whatever survived at that address, so the two never look alike to it. Two compiled copies do.

Every `util::StateFactoryArg1`, `Arg2` and `Arg3` destructor in the game is a branch to the one in `scn/step/boss/CustomBase.cpp`, and each of them calls the folded `util::StateFactory<util::IState>` destructor. No unit that sets a state through `setNextState` linked until that one small unit was written. With it compiled from source, they all do.

Where the look-alike sits in a unit that's far from decompiled, the unit with the branch waits. `mem/HeapExp.cpp` was complete for a day and didn't link for that reason. `mem::HeapExp::AllocFromTailAllocator`'s destructor is a branch to the destructor of `util::Delegate<bool (), 64>::DelegateHeap` in `info/sequence/Sequence.cpp`, and both call the folded `mem::IAllocator` destructor. It linked when `Sequence.cpp` was written. We tried giving the split object the folded name back and it doesn't work, as decomp-toolkit keeps one symbol per address, so a second name for the survivor in `symbols.txt` replaces the first one in every object. `add_relocations` in `config.yml` (`type: rel24`, `target:` a symbol name) is accepted, but it can only name a symbol that `symbols.txt` has.

An earlier experiment showed a few things about the option. It used 3 compiled eight-byte functions, identical to each other and to `scn::step::camera::MainCamera::getNear`, linked after the split objects.

- It was most likely `-code_merging all`. In that mode the linker prints the same messages as the original map, including "was interchanged with", which it uses to keep the copy whose address is taken. With `all,aggressive` it prints no interchanges, and `safe` merges nothing here (it only merges multiple definitions of one function).
- Compiled objects merge with each other as soon as the option is on.
- Split objects stay out of it unless a function is un-exported. This is why the baseline links identically with the option on.

### Static Functions That Were Folded
The linker script can only stand in for a global name. A `static` function that the original link folded away (`round_decimal` in MSL's `wprintf.c`, a twin of the one in `printf.c`) is a local symbol in the compiled object, and its body stays, which moves everything behind it. The linker has to fold it itself, and that takes one of two things. Either the twin is compiled from source as well (compiled objects merge with each other), or the twin is un-exported in `symbols.txt`, same as for a branch.

`tools/link_complete.py` tries the second one when a unit with a function like that fails its link.

### Thunks
A this-adjusting thunk (`@180@InvalidateData__...`) is weak. Every unit that defines the class's virtual functions carries a copy, and the link keeps the first one. decomp-toolkit records them as `scope:local`, which hides the kept copy from a compiled unit further down the link, and that unit then keeps its own. All 47 are `scope:weak` in `symbols.txt` now, like the strings of inline functions.

### The Order of Functions
A unit only links identically if its functions come out in the original's order. Inline functions, template instances and implicit destructors are emitted where the compiler first needs them, so their place depends on the order of definitions and of first use. A destructor that the class declares is emitted earlier than an implicit one. `tools/compare.py` reports the first function that's out of place.

## Known Issues
### We don't know if the linker always picks the same survivor as the original link
This one is still open, nobody has checked it for every case.
### Un-exporting has side effects
Un-exporting makes a symbol eligible for dead-stripping and for merging with other un-exported functions. So far each un-exported look-alike was checked with a link of its own before it went into `symbols.txt`.
### A static function that survived the merging has no clean answer yet
This is the reverse of the folded static above. A `static` function that survived the merging is what every split object calls in place of its own folded copy, by name. `DefaultSwitchThreadCallback` in `OSThread.c` stands for 226 empty functions that way. A compiled unit keeps a static to itself, so the definition there has lost its `static` for now.
