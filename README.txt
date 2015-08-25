Final Frontier Plus v1.84 by TC01 and God-Emperor
------------------------------------------------

Final Frontier Plus is, as the name suggests, a modmod of Jon Shafer's Final 
Frontier mod/scenario included with Beyond the Sword. Unlike most of the 
existing Final Frontier modmods, it is not a total conversion; instead, it is
an expansion of Final Frontier itself. The goals of the project are threefold.

The first goal is to significantly improve the speed and reliability of Final 
Frontier. Through a handful of merged speed mods, as well as countless bug 
fixes accumulated over the last few years, we have mostly accomplished this 
goal. Final Frontier Plus runs at nearly the speed of unmodded Beyond the 
Sword and has fixed almost all outstanding issues with the original
mod-scenario. Future improvements will likely still occur over time, especially
as more bugs may be unwittingly introduced.

The second goal is to make Final Frontier Plus a richer and more immersive 
experience than the Final Frontier scenario. As anyone who has played Final
Frontier will likely realize, that mod is rather lacking in terms of content.
This is an open-ended goal. Through the work of God-Emperor, many new
features have been added to the game and the BUG interface has been overlaid
over the Final Frontier interface. More work in this area of things is to come
over time.

The third goal is to improve a modder's experience in modding Final Frontier. 
To do this, we have removed a number of hardcoded limitations from the Python
code of Final Frontier, created a number of new XML tags as a result of the 
removal of such hardcoding, and finally generally cleaned up the original 
Final Frontier code. This too is an open-ended goal that currently has 
received more focus than adding new content (as it goes along with improving
speed and reliability). 

Final Frontier Plus is most certainly a work in progress. If you have a bug 
report, suggestion, request for help, offer of help, complaint, or any other 
reason to contact us for any reason, our development forum on Civfanatics is
the place to do so: http://forums.civfanatics.com/forumdisplay.php?f=387

Changelog:
----------

Please see the CHANGELOG.txt file for full changelog history. The latest patch's
changelog is reproduced here:

Note that changelogs, these days, are mostly derived from git commit history.
https://github.com/FinalFrontierPlus/civ4ffplus/commits/master

v1.84 Changelog:
-Merged patch from DarkLunaPhantom to allow BUG to work in PitBoss mode.
-Added some new unique diplomacy text to all leaders, based on suggestions 
from the forums (http://forums.civfanatics.com/showthread.php?t=517635)
-Improved the efficiency of rushing via Slave State from 30 hammers to 50.
-Modified the AI to now forces a population reassignment every fifteen turns.
-The target minimum food surplus for the AI has been changed to vary over
the course of the game, as cities grow larger.
-All AI leaders are now slightly more likely to build ships and plan war.
-Fixed rare potential CTD that could happen if a unit withdrew off the map.
-Fixed Wormholes bug that would stop Wormholes from working if their x *or*
y coordinate happened to be the same.
-Fixed potential minor Python bug involving adding a planet to a solar syste.m
-Fixed PlotListEnhancements (BUG) crash when a starbase is built while the
construction ship building it is selected.
-Defined the TXT_KEYs for the (useless/hidden/ignored) Alien civilization
to clean up the pedia.
-Flavor change: adjusted land area computation to use lightyears as a unit.
-Flavor change: slightly adjusted average lifespan in demographics upwards.

Installing:
-----------

There are *three* ways to install Final Frontier Plus. If the first two options
(the standalone installers) do not work for you-- they are known to have issues
on the Steam version of Civ 4-- we recommend trying option 3, which is just
a zipfile of the mod's contents.

Please see http://forums.civfanatics.com/showthread.php?t=365908 this thread
on our forums for more information and download links.

Installations into your *user* My Games folder is *not recommended*. This
causes problems for lots of mods.

Running:
--------

Beyond the Sword 3.19 is, of course, required. If you are running on Windows
Vista or up, you should disable User Access Control, otherwise strange problems
may occur. This is a common problem with Civ 4 mods.

You can launch Beyond the Sword and use the Load Mod menu to load Final Frontier
Plus, once it's installed.

Alternatively, you can use a mod launcher, or the shortcut that gets generated
from this mod's installers, to launch the mod directly.

Building from Source:
----------------------

AKA "the fourth way" to install the mod.

Building FF+ from source is not something you should ever really have to do,
unless you are assembling a release or we aren't releasing patches often
enough (which, let's face it, we probably aren't).

First, you are going to want to compile the DLL, using these instructions and
repository: https://github.com/FinalFrontierPlus/CvGameCoreDLL

We do not (currently!) ship auto-compiled DLLs.

Second, you are going to want to build a FPK of the art, using this repository
and instructions: https://github.com/FinalFrontierPlus/civ4ffplus-art
For best results, call it FFPak1.fpk.

This repository only includes the changes to Final Frontier, so, you'll need
to find the "Final Frontier" folder in your Beyond the Sword/Mods directory
and rename it "Final Frontier Plus". Then copy the DLL and FFPak1.fpk file
into Final Frontier Plus/Assets.

Clone this repository and copy its contents into the "Final Frontier Plus"
folder you created.

At this point, everything should work.

If you like, also use PakBuild to compile the existing Assets/Art folder
into a "FFPak0.fpk" and land it alongside FFPak1.fpk. 

License:
--------

Final Frontier Plus is as "open source" as a mod of a proprietary video game
can get. In a nutshell that means you are welcome to use any assets (code,
art, etc.) created by Final Frontier Plus contributors in other Civilization
IV mods (or elsewhere, should you really want to).

Firaxis and 2K own Civilization 4.

"Final Frontier" is a scenario created by Jon Shafer for Civilization IV:
Beyond the Sword when he was employed by Firaxis Games.

"Final Frontier Plus" is an unofficial modification built by TC01 and God-Emperor, 
among other contributors (Please see the CREDITS.txt file for a full list).

None of the above parties are liable for any damages caused by any part of
Final Frontier Plus to your computer.