---
title: FAQ
nav: faq
---
## Frequently Asked Questions
{:.no_toc}

* table of contents
{:toc}

## Can DynaHack be played with graphical tiles?

No.  For a flavor of NetHack with a similar interface as DynaHack but with support for graphical tiles, consider trying [NetHack 4](http://nethack4.org).


## How do I make the font bigger?

DynaHack runs under the console program (`cmd.exe` on Windows) or terminal emulator provided by your operating system.  You can change the font by going into settings or preferences of that program while DynaHack is running, either in a menu or by right-clicking the window title bar or the window itself.


## How do I make dark blue brighter?

As with changing your font, open your console program or terminal emulator's settings or preferences while DynaHack is running, find the dark blue palette entry and adjust to taste.


## How do I play DynaHack if I'm on Linux or OS X?

Download the source code and compile it.

* [How to compile DynaHack on Linux](https://github.com/tung/DynaHack/blob/unnethack/doc/build-linux.md)
* [How to compile DynaHack on OS X](https://github.com/tung/DynaHack/blob/unnethack/doc/build-osx.md)

You can download the source code of either the [latest stable version]({{ site.download_url }}) (choose one of the "source code" links) or download the bleeding edge version directly from the [GitHub project page]({{ site.project_url }}).

If you use Windows and you're interested in the bleeding edge version, the game can also be compiled with [MinGW](https://github.com/tung/DynaHack/blob/unnethack/doc/build-mingw.md) (no strings attached), or under [Cygwin](https://github.com/tung/DynaHack/blob/unnethack/doc/build-mingw.md) (requires Cygwin to play) for those who prefer it.


## Is there an online server for DynaHack?

As of August 2015, DynaHack can be played online at [`nethack.xd.cm`](https://nethack.xd.cm) via SSH using e.g. [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/).

**Important PuTTY note for numpad players:** By default, PuTTY sends number pad inputs in a way that is *not* recognized by `ncurses`, the library that DynaHack uses to handle terminal input and output.  To work around this:

1. Open the PuTTY configuration window.
2. From the left pane choose Terminal &gt; Features.
3. Put a checkmark next to "Disable application keypad mode".
4. From the left pane choose Session.
5. Save your settings.

Once done, DynaHack will pick up the number pad keys (you may need to enable Num Lock on your keyboard), and you can customize DynaHack's controls to recognize them as follows:

1. Connect to `nethack.xd.cm`, login and launch DynaHack.
2. Select "o - set options" from the main menu.
3. Scroll down the options menu and choose "keymap".
4. Customize the directions listed in the keymap, i.e. "east", "north", "north\_east", etc.
5. For vanilla style repeat counts, set "repeat\_num\_auto" to true, and set "repeat\_prefix" to 'n'.

You can spectate DynaHack games on `nethack.xd.cm`, but you can also sometimes catch people streaming DynaHack live on [termcast.org](http://termcast.org); in that case, you'll need to connect via `telnet termcast.org`.  (Windows users will need a telnet client such as PuTTY.)


## What is the font used in the screenshots on this site?

[GohuFont](http://font.gohu.org/).  The screenshots were taken in Linux; the Windows version of GohuFont unfortunately does not support many of the special Unicode characters used by DynaHack.
