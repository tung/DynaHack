---
title: About
nav: about
---
## What is DynaHack?
{:.no_toc}

DynaHack is a variant of NetHack that aims to modernize core aspects of its gameplay and interface.  It merges the new content and gameplay refinements of UnNetHack with the interface changes of NitroHack, along with the randomized equipment from GruntHack (e.g. you can find a "short sword of fire" or "speed boots of stealth") and a broad mixture of minor improvements to many other aspects of the game.

In NetHack, though the maps, items and monsters you encounter always change, the tactics and strategies are always the same; DynaHack was created as a response to this phenomenon.  The philosophy behind many design choices in DynaHack are **less stashing, backtracking and repetition**, and **more player experimentation and exploration**.

* table of contents
{:toc}


## Interface Changes

DynaHack makes better use of larger terminal sizes, showing a multi-line message box and inventory sidebar.

Unlike NetHack, options in DynaHack are set with an in-game menu, and changes are saved automatically.

<a href="{{ site.baseurl }}/images/screenshots/dynahack-title-full.png"><img src="{{ site.baseurl }}/images/screenshots/dynahack-title-small.png" title="DynaHack 0.5.0 title screen."></a>

Other interface changes include:

* Item action menus.
* New and improved quick command reference (type `??`).
* Colored status area and HP/Pw bars.
* Colors for walls and floors of dungeon branches and special rooms.
* `msgtype` option to force `--More--` prompts and hide messages.
* Menus for choosing floor items when eating and looting.

Some interface changes provide more information than in NetHack:

* Item weights and carrying capacity shown.
* Red/green highlights when attributes change.
* Highlighting for peacefuls, locked doors, item piles and covered stairs.
* `hp_notify` option to show messages when damage is taken.
* `delay_msg` option to show messages for multi-turn actions and delays.
* Corpses show rotten/very rotten when unsafe to eat.
* Required and remaining slots shown when viewing and enhancing skills.
* Remaining memory for spells shown.

Several changes have been made to make the game more convenient to play:

* `Ctrl-O` shows dungeon overview and previous levels.
* `Ctrl-X` shows intrinsic resistances and properties.
* `Ctrl-E` engraves `Elbereth`, which scares monsters.
* Auto-unlock for doors/containers, auto-loot after auto-unlocking containers.
* Resting and searching stop when HP/Pw fully recover.
* `ff` fires in the last direction fired in.

For those used to playing on <abbr title="nethack.alt.org">NAO</abbr>, automatic travel can target stairs even when covered, stops when becoming hungry or enemies come into view, routes around peacefuls and even works in Sokoban.

<a href="{{ site.baseurl }}/images/screenshots/dynahack-item-actions-full.png"><img src="{{ site.baseurl }}/images/screenshots/dynahack-item-actions-small.png" title="Select items in your inventory for a menu of possible actions."></a>

Autopickup in DynaHack is much smarter than in NetHack thanks to the new autopickup rules system, offering fine-grained control over what it picks up or leaves.  Autopickup in DynaHack also leaves dropped items alone, and grabs thrown and fired items.

Item class filters (e.g. when pressing `D` to drop multiple items) are smarter: choosing `cursed` and `armor` will match only cursed armor, unlike NetHack which shows all cursed items mixed with all armor.

DynaHack allows all controls to be remapped, which is especially useful for people with QWERTZ keyboards.


## New Content

DynaHack was originally a merge of UnNetHack's gameplay with NitroHack as its base, so all of this new content sources from UnNetHack 4.1.1:

* Over 80 new special levels.
* Lava caverns for Gehennom instead of endless mazes.
* New branches: Town, Black Market, Dragon Caves.
* New special rooms: nymph gardens, dilapidated armories.
* New shops: tin shops, instrument shops, pet stores.
* New items: rings of gain intellligence/wisdom/dexterity, potions of blood and vampire blood, scroll of flood, iron safe, tinfoil hat, striped shirt, Thiefbane, Luck Blade.
* New monsters: gold and chromatic dragons, snow ants, vorpal jabberwocks, disintegrators, giant turtles, wax golems, locusts, enormous rats, rodents of unusual size.


## New Challenges

Wishing in DynaHack is divided into magical and non-magical items, like in UnNetHack.  Only wands of wishing can grant wishes for magical items, while every other source can only provide non-magical items, such as shields of reflection and dragon scales (but not dragon scale mail).  Unlike NetHack, wands of wishing *cannot* be recharged.

<a href="{{ site.baseurl }}/images/screenshots/dynahack-interface-full.png"><img src="{{ site.baseurl }}/images/screenshots/dynahack-interface-small.png" title="DynaHack interface in a large terminal."></a>

Like UnNetHack, dragons in DynaHack are given random names and colors every game, thwarting attempts to wish for optimal varieties of dragon scale mail early.  Dragon armors are also heavier and grant less AC than in NetHack.

DynaHack introduces color alchemy from UnNetHack, meaning that potions will mix by their colors instead of by their type, e.g. mixing red and yellow potions makes orange potions.  This thwarts powerful alchemy combinations present in NetHack, but adds variety across games and can lead to interesting combinations.

With its roots in UnNetHack, DynaHack also adds these new challenges:

* `Elbereth` is ignored by quest nemeses, unique demons and Vlad the Impaler.
* The mysterious force has been removed (download levelport while ascending through Gehennom with the Amulet of Yendor); the Amulet of Yendor now prevents all forms of teleportation.
* Scrolls of gold detection can no longer be used to detect traps; crystal balls have been made easier to use to compensate.
* Scrolls of genocide only affect a single monster type when blessed, or the same on only the current level when uncursed.
* Fighting creates noise which wakes nearby monsters, depending on stealth and the size of the weapon.
* Unicorn horns no longer restore lost attributes.

DynaHack addresses two forms of farming in NetHack: pudding farming and throne farming.  Both of these are still possible in limited forms, but as in UnNetHack, puddings no longer split forever or drop items when killed.  Thrones take time to loot and may disappear in the process.


## More Fairness

DynaHack reduces the punishments for hazards players cannot or do not expect to have to defend themselves against:

* Warnings before walking into known traps, water and lava.
* Poison, the most common unavoidable instadeath, instead drains max HP.
* Floating eyes paralyze for half as long, capped further by wisdom.
* Scroll of flood replaces the scroll of amnesia, making reading random scrolls less game-ruining.

<a href="{{ site.baseurl }}/images/screenshots/dynahack-monster-description-full.png"><img src="{{ site.baseurl }}/images/screenshots/dynahack-monster-description-small.png" title="DynaHack can show detailed descriptions of monsters."></a>

DynaHack also reduces the spoiler advantage that long-time NetHack players have over novices by providing a newer and more informative database of item descriptions from NetHack4 and detailed monster descriptions from UnNetHackPlus (press `/` and target a monster with `;`, or enter its name).


## More Variety

DynaHack can generate randomized equipment: weapons, armor, rings and amulets with magical properties that freely mix and match with their base items.  Some examples:

* short sword **of fire**
* orcish helm **of cold resistance**
* **thirsty** battle-axe
* oilskin cloak **of reflection**
* amulet of life saving **and telepathy**
* speed boots **of hunger**
* ring of levitation **and aggravation**
* plate mail **of power**
* **vorpal** knife
* sling **of detonation**
* gauntlets of power **and displacement**

Twenty different magical powers can inhabit an item marked "magical"; see what you can find!

DynaHack encourages more weapon variety.  Weapons may reveal their enchantment when used, based on skill and race.  Weapon skills also cross-train, accelerating the training of related skills, allowing playesr to experiment with skills early without having to fully commit to them into the late game.  The weapon skill groups are:

* **Short Blades**: dagger, knife
* **Chopping Blades**: axe, pick-axe
* **Swords**: long sword, two-handed sword, scimitar, saber
* **Bludgeons**: club, mace, hammer
* **Flails**: whip
* **Polearms**: polearm, trident, lance, unicorn horn
* **Launchers**: bow, crossbow
* **Thrown**: dart, shuriken, boomerang

Some weapon skills (not listed above) belong to more than one group:


* *short sword*: Short Blades, Swords
* *broadsword*: Chopping Blades, Swords
* *morning star*: Bludgeons, Flails
* *quarterstaff*: Bludgeons, Polearms
* *javelin*: Polearms, Thrown
* *sling*: Launchers, Thrown

DynaHack introduces the new heavyshot mechanic, complementing multishot.  Certain fired or thrown weapons, rather than launching multiple volleys, will instead launch a single volley that inflicts mulitplied damage.  This makes crossbows more interesting than being merely heavier bows with rare ammo, and also applies to shuriken, spears, javelins and boomerangs.  Spears of matching race and javelins (for everybody) receive a bonus multiplier when thrown.

<a href="{{ site.baseurl }}/images/screenshots/dynahack-more-menu-full.png"><img src="{{ site.baseurl }}/images/screenshots/dynahack-more-menu-small.png" title="View all details about a particular square."></a>

Ranged combat is enhanced in DynaHack.  Items, especially ammo, stacks much more readily than in NetHack.  Further, switching main and alternate weapons with `x` no longer costs a turn, making launchers more viable.

* Polearms and lances can be used in melee, making them easier to train early and usable in dark corridors.
* Two-handed weapons double the strength damage bonus on hits.
* New `#tip` command for containers, so players with hands stuck to a cursed two-handed weapon can still reach their holy water without having to backtrack out of Gehennom.
* Hands stuck to a cursed quarterstaff can still cast spells unhindered.

DynaHack differentiates roles further than NetHack by improving their quest artifact.  The quest artifact cannot be stolen by the Wizard of Yendor in DynaHack, making it a reliable source of resistances.  It also grants magic resistance when carried by their role, giving most characters a good reason to make use of their unique powers.

DynaHack reduces incentives to stash and backtrack:

* Scrolls of identify work on 3-6 items regardless of their blessing.  The full inventory identify effect of these scrolls in NetHack was a big reason to hoard unidentified items until you could bless all of your scrolls of identify.  This change also allows scrolls of identify to be used earlier less wastefully in DynaHack, in turn making less useful items known earlier so they don't need to be hauled around.
* Wraiths can no longer be lured across levels.
