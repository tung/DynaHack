---
title: DynaHack 0.6.0 Released
author: tungtn
date: 2016-02-18 13:55:55 +1100
tags: [dynahack, release]
---
[Download DynaHack 0.6.0](https://github.com/tung/DynaHack/releases/tag/v0.6.0)

DynaHack 0.6.0 marks a large departure from the 0.5.x series by introducing quite a few gameplay and content changes aimed at eliminating tedium, improving fairness, and increasing tactical and strategic variety.

As always, changes in DynaHack tend to lean in favor of the player more often than not, so players of all skill levels will find something to appreciate.

* New body armor and shield skills: grants bonus AC and MC; heavier suits of armor and shields get bigger bonuses and train the skills faster.
* Magic chests!  Any item put into a magic chest can be looted out of any other magic chest in the dungeon, placed at set locations.  This eliminates tedious stash consolidation and transporting of items to and from stashes and fixed dungeon resources like altars, shops and water.
* Mazes completely removed from Gehennom!
* New resistance system: resistances gained from corpses and crowning only provide partial protection.
* Reflection no longer reflects breaths (except disintegration).
* Instant petrification completely replaced with delayed petrification: you will always have a few turns to save yourself from instant death.
* Drawbridge instant death removed: drawbridges can only be destroyed by force bolts when closed, not open.
* Extra turn before drowning attack instant death.  Players upgrading from an older version of DynaHack should adjust their `msgtype` as described in the Configuration section of this changelog.
* Zombie corpses may revive (lower chance if playing a priest).
* Sokoban prizes moved to Mines End, making Sokoban much more optional.
* Nymph level moved into Town branch; Town shops are larger to compensate.
* Effect of skills on to-hit and damage raised in general.
* Items that spawn with a magical property have a much higher chance to spawn with additional properties.
* Slings now get damage bonuses from strength and enchantment.
* Spells can be aborted at direction, position and item prompts without using power or hunger.
* New `repeat_prefix` keymap and `repeat_num_auto` option for people accustomed to NetHack's classic number key movement scheme.
* New `msg_per_line` option: Shows each message on a new line in the message area when enabled.
* Potion color alchemy improved in favor of players, making it more of an alternative to NetHack's alchemy instead of a nerf.
* Curses on armor, jewelry and eyewear are now revealed when they are worn instead of when trying to take them off.
* More messages for things that used to happen silently: uncontrolled teleportation, finding secret doors/corridors while searching, items becoming randomly cursed.
* Iron bars can be destroyed by acid or eaten by certain monsters.

Read [changelog.txt](https://github.com/tung/DynaHack/blob/unnethack/doc/changelog.txt) for the full list of changes.

New to this release are 32-bit and 64-bit packages for both Windows and Linux (built on Ubuntu 15.10, but they should work in other distros).

Note: I (tungtn) will no longer be working on DynaHack after this release, so please do not email me bugs or feedback.  Instead, post them to <https://github.com/tung/DynaHack/issues> so that other people can see them.

**Update:** I wrote a post on [stepping down from maintaining DynaHack]({{ site.baseurl }}{% post_url 2016-02-18-stepping-down-from-maintaining-dynahack %}).
