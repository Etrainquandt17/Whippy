# What a Failed Check Does
Most of the game's [MetaFortress](metafortress.md) checks stop the game when the code they guard has been changed. 149 functions do something else. 26 of them hang where they stand, and the other 123 carry on with a wrong value, as the comparison between the computed checksum and the stored one sits where the source had a plain `true` or `false`. This page goes through them one by one.

Each entry gives what the source had and what follows when the check fails. Nothing here has been tried in the game. It's all read from the code, and where an entry stops short of what a player would see, it says what's still open. To try one on its own, `--break` makes a DOL where only that function's check fails ([Modified Builds](metafortress.md#modified-builds)).

Names are shortened. `hero`, `gimmick`, `carryitem`, `camera` and the other stage namespaces are inside `scn::step`, and the scenes (`wmap`, `titlemenunew`, `arena`, `goalgame`, `subgame` and so on) are inside `scn`.

All 149 are matched. The status column says `matched` when the function has been decompiled and compiles to the original instructions in both supported versions.

## How the Constant Is Hidden
MetaFortress doesn't add logic of its own. It takes a constant the function already implies and hides it behind a condition. With `ok` for the comparison `expected == hash`:

| In the Game | Untampered | Check Fails |
|---|---|---|
| `f(ok)` | `f(true)` | `f(false)` |
| `flag = !ok` | `flag = false` | `flag = true` |
| `if (ok && x)` | `if (x)` | never |
| `if (!ok \|\| x)` | `if (x)` | always |

5 of the functions use an inverted check, where the stored word is the complement of the right sum, and the game's logic is written the other way round to suit. Damage to the checked code can't change their outcome. They only fire if someone rewrites the stored word to the sum it "should" have. They're marked *inverted* below.

## Save Data
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `app::BackupFileAccessor::updateUnlockState` | The theater room's completion state unlocks when both story modes are complete and both arenas are cleared. | The two "complete" tests are skipped. Clearing both arenas is enough. | matched |

## Kirby and the Other Heroes
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `hero::AbilityKindUtil::IsKirbyAbility` | `false` for Meta Knight, Dedede and Waddle Dee, `true` for every other kind. | The answer is inverted. Its one caller is `seq::SequenceLvMapRoot::onSceneEndForGameOver`, which sets each player's health to full and takes away the copy ability of whoever it says is a Kirby, when the game goes on after a game over. With the check failing, Kirby players keep their ability, and Meta Knight, Dedede and Waddle Dee lose theirs (it's set to 0, and we haven't followed what the hero setup makes of that). The stage's own death handling has already cleared the ability of player 1 outside challenge stages and of any other Kirby who isn't in play, so the one that shows is a second Kirby who is still in play when the game is over. Seen in the game that way. | matched |
| `hero::AbilityManager::initAbilityCore` | Skip the setup if the hero has an ability and a flag is set. Later, clear the other heroes' super abilities if the new ability is a super ability. | *Inverted.* The skip no longer asks whether the hero has an ability, so no ability is built while the flag is set, and gaining any ability clears the other players' super abilities. | matched |
| `hero::AbilityManager::initAbility` | `reserveChangeAbility(kind, false)` | Passes `true`, which means "forced". It's only read when the ability is being removed (kind 0), where a super ability then goes without releasing its effect, hiding its gauge, clearing the fade or dropping its music. For any other kind nothing changes. | matched |
| `hero::AbilityManager::startAbilitySilent` | `startAbilityCore(true)` | Passes `false`. By the name, the ability no longer starts silently. | matched |
| `hero::AbilityManager::tryToChangeStateOnDamage` | 3 early returns, each on its own condition. | Returns `false` at the first, so the ability never gets to react to damage. | matched |
| `hero::AbilityManager::setFuel` | Update the gauge if the maximum isn't zero. | Updates it always. With a maximum of zero the gauge is given 0/0. | matched |
| `hero::leaf::Leaf::tryToChangeState`, `hero::hammer::Hammer::tryToChangeState`, `hero::wing::Wing::tryToChangeState` | Try each of the ability's states in turn. | No state is tried, and the function reports that one was. | matched |
| `hero::hammer::Hammer::onStateEndCleanUp` | Clear the hammer's animation when a state ends. | It's never cleared. | matched |
| `hero::bomb::Bomb::onStateEndCleanUp` | Restore the arm animation and hide the bomb. | Nothing runs. | matched |
| `hero::crash::Crash::procAnim` | Request or release the hat's light. | Nothing runs. | matched |
| `hero::needle::Needle::resetNeedleBodyVisibility` | Hide one part of the needle model. | Nothing runs. | matched |
| `hero::stone::Stone::stoneBodyClear`, `hero::stone::Stone::~Stone` | Remove the stone body and free what it used. | The clean-up is skipped. | matched |
| `hero::Piggyback::getParentPadChan` | When riding piggyback, use the carrier's controller channel. | Always uses the hero's own. | matched |
| `hero::Piggyback::setChildHidDisable` | Pass the call on to the rider, if there is one. | Passes it on without the test, and dereferences a null pointer at the end of the chain. | matched |
| `hero::FinalBattleShadow::FinalBattleShadow` | Create the effect locator in the final battle. | Creates it for every hero in every stage. | matched |
| `hero::VacuumSoundCtrl::registerObj` | Add the hero to the list, set the volume. | Neither happens. | matched |
| `hero::FormationUtil::GetWarpStarRidePosKind` | Use the default seat for kinds that have one. | Takes that path for every kind, and for a kind without a default seat ends in the hang below. | matched |
| `hero::Heap::setUseHeapGear` | `mUseHeapGear = true` | Stores `false`. Ability gear (models, animations, Stone's own heap) is then allocated from the hero's general heap, and the 133,120-byte gear heap set aside inside it stays unused. We didn't work out whether the general heap has room for that. | matched |

## Stages
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `StageKindUtil::IsFinalStage` | `true` for the two final stages. | The answer is inverted for every stage. | matched |
| `carryitem::CarryItem::getThrowPowerRate` | The throw power, at most 1. | Always 1, so a carried item is always thrown at full power. | matched |
| `carryitem::CarryItem::put` | An item that may not be put down again, or a second copy of a unique item, disappears. | It stays. | matched |
| `carryitem::CarryItem::~CarryItem` | Tell the item's generator that one of its items is gone. | It's never told, and a generator makes nothing while its count is above zero, so it never produces another item. Only an item that removed itself in `put` gets this far with a generator, one that dies in play has already let go of it. | matched |
| `camera::CameraController::setLock` | Store the rectangle and set the lock flag. | The flag stays clear, so the camera lock presumably never takes hold. | matched |
| `camera::MainCamera::MainCamera` | Level maps get their own camera values. | Every stage gets the level-map values. | matched |
| `boss::lowper::BackEffectCtrl::release` | Release the boss's background effect if it was requested, and clear the request. | Releases it on every call and leaves the request set, so it's never requested again. | matched |
| `sfx::SpiralScreen::startAnim` | Set up the spiral effect and mark it as running. | It isn't marked, and presumably never plays. | matched |
| `core::PreLoadReq::checkRequest` | Report whether a preload has been requested. | Always "yes", so none is ever requested. | matched |
| `StorageAccessor::SetSphereUnlockExecutedDemo` | Book a save when the flag changes. | Books one on every call. | matched |
| `enemy::BrainBase::onLanding` | `return false` | Returns `true`, which tells the landing state that the brain chose the next state itself. For the 141 brains that don't override it, `StateLanding` and `StateSuperAppear` then never hand over to `StateWait`. We didn't follow whether something else moves an enemy like that on. | matched |
| `ContextChallenge::Create` | A flag in the new context is `false`. | It's `true`. We don't know what it means. | matched |

## Stage Objects
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `gimmick::switch_n::Switch::hitOn` | A flag that lets the switch take hits is set. | It stays clear, so the switch can't be hit. | matched |
| `gimmick::switch_n::Switch::searchAttackOff` | A flag is cleared. | It stays set. Probably nothing visible. | matched |
| `gimmick::switch_n::Switch::Switch` | `mModel.start(true)` for the switch's waiting animation. | Passes `false`, probably the loop flag. | matched |
| `gimmick::challengedoor::ChallengeDoor::ChallengeDoor` | The door's record starts with `true`. | It starts with `false`. The door manager looks for the first door whose record says `true`, so the door is never found and can't be entered. | matched |
| `gimmick::lvmapdoor::LvMapDoor::clearedDoorInit` | For a cleared door with a boss model, start the boss's waiting animation and the unlock effect. | Neither is started. | matched |
| `gimmick::lvmapdoor::LvMapDoor::setDoorWaitAnim` | Pick the door's animation by whether Kirby is near. | Every door on a level map behaves as if Kirby were near, so it's "KirbyNearWait" or "Open" plus an effect, never the plain waiting animation. | matched |
| `gimmick::lvmapdoor::LvMapDoor::setZoom` | `setZoom(position, a, b, false)` | Passes `true`. We don't know what the flag means. | matched |
| `gimmick::lvmapdoor::DoorUnlockStar::unsetZoom` | Undo the camera zoom if one was set. | Undoes it also with no zoom set. That asks the camera to remove zoom 0, which no zoom ever is, so nothing happens. | matched |
| `gimmick::warplowper::WarpLowper::mfStartDemo` | A "started" flag is set. | It stays clear, and the demo is started again on every frame. | matched |
| `gimmick::monitor::Monitor::viewNoise` | `mModel.start(true)` | Passes `false`, probably the loop flag of the noise animation. | matched |
| `gimmick::popflower::PopFlower::mfIsAttackBody` | `true` for 3 attack types. | `true` for every type. | matched |
| `gimmick::block::Block::getBreakSE` | One kind of block has its own breaking sound. | Every block uses that sound. | matched |
| `gimmick::shipevent::ShipEvent::SEFadeRequester::mfRequestCommon` | A "fading out" flag is cleared when a sound is requested. | It's set, so the sound is faded out as soon as it starts. | matched |
| `gimmick::cutropestep::CutRopeStep::RestRope::RestRope` | `GetPosMtx(position, false)` | Passes `true`, which adds a half turn, so the leftover rope is drawn upside down. | matched |

## Heads-up Display
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `scn::step::info::BossPanel::damage` | 4 conditions around the boss gauge's damage animation. | A rate of zero is no longer applied, the damage branch runs when it shouldn't, the animation is always "Damage" then "Wait", and every hit restarts the timer. | matched |
| `scn::step::info::lvmap::StageSphere::stateAppear` | Go on when the animation has ended. | Never goes on, so the stage's sphere display stays in its first state. | matched |
| `scn::step::info::lvmap::StageSphere::stateSphereGetWait` | Wait, then flash the next sphere. | The wait is skipped. | matched |
| `scn::step::info::lvmap::StageSphere::StageSphere` | The boss panel starts hidden. | It starts visible. | matched |
| `scn::step::info::WarpStarPanel::WarpStarPanel` | The panel starts hidden. | It starts visible. | matched |
| `scn::step::info::HeroStatusIcon::startDeadAnim` | `start(true)` for the "Dead" animation. | Passes `false`. | matched |
| `scn::step::info::InfoGameStatus::startAnimInS`, `startAnimOutS` | The flag behind `isInfoIn()` is set on the way in and cleared on the way out. | It's cleared on the way in and set on the way out, so the status display counts as hidden while it's shown. Code that should slide it out (the clear dance, a boss's death) skips that, code that wants it in plays "In" again, and a joining player's character select ignores its buttons while the flag reads "out". | matched |
| `scn::step::info::HeroStatus::setName` | Shrink a name to fit if it has a width. | Takes that path for a name of no width too. Nothing visible expected. | matched |

## Pause Menu
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `pause::PageAbility::pageIsBusy`, `pause::PageShip::pageIsBusy` | `return false` | The page always says it's busy. | matched |
| `pause::PageManager::changePage` | Animate one of two cursors, by direction. | Always the same one. | matched |
| `pause::FramePanel::FramePanel`, `pause::PageManager::PageManager` | `start(true)` for a "Wait" animation. | Passes `false`. | matched |
| `pause::PageDropout::PageDropout` | `freezeOnYes(true)` for the drop-out confirmation. | Passes `false`. | matched |

## Menus and Sequences
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `seq::SequenceTheaterRoomRoot::onSceneEnd` | After a movie or the credits, go back to the theater room. | The end of a movie or of the credits is handled as the end of the theater room itself, through a null pointer. Probably a crash. | matched |
| `seq::SequenceTitleMenuRoot::createChildSequence` | Start the opening in the chosen story mode, or the chosen kind of arena. | The second story mode starts the first, and the second kind of arena starts the first. | matched |
| `seq::SequenceChallengeRoot::createScene` | After a challenge, count the attempt and save the medal. Pass a flag to the tutorial and pick one of two dialogs. | The attempt isn't counted and the medal isn't saved, but the 3 ranked scores still are. The tutorial's flag is inverted and the dialog is always the same one. | matched |
| `seq::SequenceStep::nextAction` | 2 if a flag is set, else 0. | Always 2. | matched |
| `seq::SequenceChallengeRoot::branchHint` | 3 outcomes, by two flags. | Always the first. | matched |
| `info::common::AddWiiRemote::Remote::phaseOn` | If the remote isn't connected, play "ToOff". | Every remote is treated as not connected. | matched |
| `info::common::WiiButton::hold` | The "blinking" flag is cleared after "Hold" is played. | It's set. The next `waitNoShadow()` then doesn't play "Wait2" at once but waits until the button's animation frame is a multiple of 10, which may never come once "Hold" has stopped. Only the button help and the challenge tutorial call the two in that order. | matched |
| `info::sequence::Sequence::start` | A "running" flag is set. | It stays clear, and `update()` does nothing without it, so a scripted on-screen sequence starts its first command and never advances. | matched |
| `sfx::Wipe::checkAnimStart` | Start the wipe's animation when its counter has run out. | Starts it on every call, so a screen wipe never gets past its first frame. | matched |

## Title Screen and File Select
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `title::SceneTitle::updateMain` | In its first state, start the save and move on once nothing is busy and there's no error. | Never moves on, so the title scene stays in its first state. | matched |
| `titlemenunew::FileNumber::update` | Show the complete mark for a completed file. | The mark is always hidden. | matched |
| `titlemenunew::File::File` | Hide the Extra Mode status panel on a file that has no Extra Mode. | It stays visible. | matched |
| `titlemenunew::TheArena::enable` | Play "Enable" or "Disable". | Always "Enable", so The Arena looks available when it isn't. | matched |
| `titlemenunew::Option::cursorParent` | The cursor's parent is a sub-pane only when a flag is set. | Always the "SoundCursorN" or "TheaterCursorN" pane. | matched |
| `titlemenunew::ModePanel::ModePanel` | A `true` argument when a panel is added. | *Inverted.* | matched |
| `strap::SceneStrap::SceneStrap` | `setIgnore(true)` on the HOME menu. | Passes `false`, so the HOME menu isn't blocked on the wrist strap screen. | matched |

## World Map
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `wmap::info::LevelName::mfToOpen` | Start the level or ship panel without skipping its animation, and clear a flag. | The "Start" animation jumps to its last frame, and the flag is set. | matched |
| `wmap::info::LevelName::mfStartLevel` | Mark the panel as a level panel. | Marks it as the ship's, so every frame the level's name, text and sphere total are hidden and the ship's name and text panes are shown, with whatever text they last held. | matched |
| `wmap::info::LevelName::mfStartShip` | Mark the panel as the ship's. | Marks it as a level panel, so the ship's panes are hidden and the level's are shown. | matched |
| `wmap::info::LevelName::onMoveStart` | The "moving" flag is set, which closes the panel. | It's cleared, so the panel isn't closed when a move starts. It stays open over the item being left, closes and opens again on arrival, and stays open after 2 is pressed to enter a level. | matched |
| `wmap::info::LevelTitle::setTextType` | Mark the title as changed when the text type changes. | Marks it on every call. | matched |
| `wmap::MapModelRoute::mfStartWaitAnim` | Animate the second route model if the table has an entry for it, else hide it. | Animates it with whatever the table holds. That's a wrong animation or a crash, we didn't determine which. | matched |
| `wmap::MapModelRouteEffect::appear` | A flag is set before the effect starts, so that it's restarted with the others. | It's cleared. Each route effect plays once when it appears and is never restarted, where the game restarts all shown effects together each time they finish. | matched |
| `wmap::Ship::Ship` | `start(true)` on the ship model. | Passes `false`, so the ship's animation plays once and stops. | matched |
| `wmap::hero::InactiveHero::InactiveHero` | A flag is `true` for two kinds of context and `false` for the rest, and picks the hero's first state. | The hero always starts in its "select" state, so every player slot without a hero opens character select on entering the world map and again right after dropping out, without a button press and without the low-battery check. A slot whose remote isn't connected cancels it in the first frame. The inverted flag itself is overwritten at once. | matched |

## The Arena
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `arena::select::SelectPanel::decide` | Play "Push" on the panel or its button along with "Decide". | "Push" is dropped. | matched |
| `arena::select::ChoseData::cancel` | Reset the chosen character of a player who has entered. | Resets it for a player who hasn't, too. Probably harmless. | matched |
| `arena::SceneArena::result` | Use the component if there is one. | Uses it without the test. Only matters with no component, and then it's a null pointer. | matched |
| `arena::title::Title::Title` | A "preload done" flag by cursor position, and `setCameraAnimFlag(true)` for one game kind. | With the cursor on Start the title no longer preloads its 3 archives, and on the other choice it preloads them again. For the game kind with the "TitleArenaExtra" layout the camera is no longer left to the scene's "TitleCamera" animation but set every frame from the camera object's default position. | matched |

## Goal Game and Challenges
| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `goalgame::desc::gear::GearDesc::isUseGear` | `true` for Sword, Whip, Beam, Parasol, Spear and Hammer. | `false` for every ability, so the goal game shows no ability with its gear. | matched |
| `goalgame::JumpBoard::effectJumpBoard` | A flag is set, asking for effect 0x276 on the board at its next draw. | It's cleared, so that effect never starts. | matched |
| `goalgame::GGame::~GGame` | `setIsPlayEnable(false)` on the music controller. | Passes `true`, so the goal game's music isn't stopped when the game is torn down. | matched |
| `challengeresult::info::ResultLyt::updateFrame` | Skip the count-up when a button is pressed. | Skips it on every frame, so the result always appears at once. | matched |
| `challengeresult::SceneChallengeResult::updateMain` | Leave the first two states when their conditions hold. | *Inverted.* | matched |
| `challengetutorial::SceneChallengeTutorial::SceneChallengeTutorial` | One of two pieces of music, by the recipe. | Always the same one. | matched |
| `gameover::info::GameOverBase::cursorPos` | Mirror the cursor position in one layout only. | Always mirrors it, so the cursor is drawn on the wrong choice. | matched |
| `movie::SceneMovie::~SceneMovie` | Destroy the cut-in explicitly. | It's left to the member's own destructor a little later. Nothing visible expected. | matched |

## Sub-games
The two sub-games are `gunshoot` (Scope Shot) and `setsuna` (Ninja Dojo), with shared menu code in `common`.

| Function | The Source Had | When the Check Fails | Status |
|---|---|---|---|
| `gunshoot::chara::PlayerController::shot` | Stop if the enemy is already dead, else fire. | Always stops there, so a shot plays its animation and sound but fires nothing. | matched |
| `gunshoot::enemy::CollisionItem::addDamage` | Clamp the remaining life at zero. | Any hit sets the life and the shield value to zero, so the part breaks at once. | matched |
| `gunshoot::enemy::CollisionItem::recover` | The part becomes active again. | It gets its life back but stays inactive. | matched |
| `gunshoot::enemy::AnimParam::getDamageAnimName` | No animation for one kind of hit. | No damage animation for any hit. | matched |
| `gunshoot::enemy::DamageAnimator::startDamage` | `start(false)` for the second model's damage animation. | Passes `true`, so it loops. | matched |
| `gunshoot::info::Victory::startClear` | `start(false)` for "Clear1". | Passes `true`, so it loops, and a looping animation never reports its end. The victory sequence waits for that end, so after the enemy is destroyed the game stays on the clear animation, with pausing locked, and never reaches the result. | matched |
| `setsuna::chara::Blind::fadeOut` | Return early in two states. | Always returns, so the blind never fades out. | matched |
| `setsuna::chara::Aim::setResult` | Hide the aim. | It stays visible on the result screen. | matched |
| `setsuna::chara::GameResultChara::startWait` | Restart "InA" if a flag is set, looping. | Restarts it on every call, not looping. | matched |
| `setsuna::chara::GameResultChara::reset` | A flag is cleared. | It stays set, and the result layouts are shown as soon as a target lands. | matched |
| `setsuna::info::MatchResult::Create` | The all-targets bonus flag starts `false`. | It starts `true`, so every result carries the 50 point bonus. | matched |
| `setsuna::info::ResultTargetNumber::open` | The last number fades in with its own animation. | It uses the ordinary one. | matched |
| `setsuna::info::Evaluation::close` | Hide the "bad" layout. | It stays visible. | matched |
| `common::boxmenu::ClosableBox::close` | Return early in 3 cases. | Always returns, so a box can't be closed. | matched |
| `common::boxmenu::ClosableBox::fixToBeOpened` | Return early if already open. | Always returns, so it does nothing. | matched |
| `common::boxmenu::SelectUnit::suspendImpl` | A "suspended" flag is set. | It stays clear. | matched |
| `common::pause::PauseLockRequestor::request` | Remember that pausing is locked. | Not remembered, so the lock is never released. | matched |
| `common::pause::PauseLockRequestor::cancel` | Forget the lock. | Still remembered, so it's released a second time later. | matched |
| `common::pause::PauseLockRequestor::~PauseLockRequestor` | Release the sound lock if it was taken. | Releases it regardless. | matched |
| `common::util::BackButton::BackButton` | Blink if asked to. | Every back button blinks. | matched |
| `title::window::OnGameEndGuide::OnGameEndGuide` | Pick the guide's main layout by sub-game. | Always Ninja Dojo's, in Scope Shot too. The buttons' own layouts are still right. | matched |
| `SceneSubgameTitle::SceneSubgameTitle` | Preload the menu, or the stage and 4 hero files, by the recipe. | *Inverted.* The function also writes 1 to one of the hidden objects if either of the words at 0x80000060 and 0x80000064 is zero. | matched |

## Hangs in Place
These loop forever on a mismatch, without the response function, with `while (hash - expected != 0) {}`.

| Function | Where the Loop Is | Status |
|---|---|---|
| `app::AppImpl::run` | Before the root sequence is created, so at startup. | matched |
| `app::EntryPoint::Run` | After the application has returned. | matched |
| `font::FontLoader::FontLoader` | Before the font is fetched, so at the first font load. | matched |
| `util::AnimController::changeDoLoop` | Before the flag is stored. | matched |
| `scn::step::info::InfoGameStatus::bossPanel` | Before the panel is returned, so the first time a boss asks for its gauge. | matched |
| `seq::SequenceStep::createScene` | Before the stage scene is created, so on entering any stage. | matched |
| `seq::SequenceWMapRoot::nextAction`, `onChildSequenceEnd`, `onSceneEnd` | In the `default:` of a `switch` over the map mode, which no valid mode reaches. | matched |
| `seq::SequenceWMapRoot::createScene`, `createChildSequence`, `onChildSequenceEndForShipMap` | The same. | matched |
| `seq::SequenceTitleMenuRoot::createChildSequence`, `seq::SequenceChallengeRoot::createScene` | In the `default:` of their `switch`, next to the uses listed above. | matched |
| `hero::FormationUtil` `defaultPosKind` | In the `default:` of a `switch` over the hero kind. | matched |
| `goalgame::desc::hero::HeroDesc::ModelPath` | Before the table lookup, so the first time the goal game asks for a hero's model. | matched |
| `goalgame::GGame::checkAllUfoState` | Before the loop over the UFOs. | matched |
| `arena::ArenaData::BossSet::setAbility` | Before an ability is recorded, so the first time in The Arena. | matched |
| `titlemenunew::Option::cursorParent` | In the `default:` of its `switch`, next to the use listed above. | matched |
| `gunshoot::enemy::PlayListSetController::PlayListSetController`, `initPlayListSet` | Before the play lists are set up. | matched |
| `gunshoot::enemy::StepAnimator::resumeStep` | At the top of the block that resumes a step. | matched |
| `gunshoot::enemy::AnimParam::getStepData` | Before the step is looked up. | matched |
| `title::window::SelectSequence::nextSeq` | Before the next sequence is chosen. | matched |
| `item::GetInfo::subKind` | Before the value is returned, so the first time a hero picks up an item. | matched |
| `StorageAccessor::GetIsSphereGet` | Before the save data is read, so whenever the game asks whether an energy sphere was collected. | matched |
| `ChallengeKindUtil` `t_info` | Before the table lookup, so on any question about a challenge. | matched |
| `debug::ObjInfoRepos::~ObjInfoRepos` | In the destructor. We didn't check when that runs. | matched |
| `map::KindUtil::ToStageIndex` | In the `default:` of its `switch`. | matched |
| `map::KindUtil::IsFinalStageMap` | At the top, and *inverted*, so it loops when the sum equals the stored word. | matched |
