==============================================
KINGPIN: Life of Crime (TM) - SDK
==============================================


This is a bare-bones compilation of the tools necessary to
create user modifications to Kingpin.

Kingpin uses the Quake2 engine as a base, and therefore
if you are familiar with Quake2 modifications, you will
find yourself in very familiar waters with the Kingpin
SDK.

This SDK consists of:

Game source-code		(sdk\gamesrc)
Kingpin Data conversion		(sdk\kpdata.exe)
Example files			(sdk\examples)

-----------------------------------------------------------

The source code is very similar to the Quake2 game source
that was released publicly. You'll need MS Visual C++ v5.0
or higher to use it (earlier versions may work, but have not
been tested).

We recommend that only experienced MSVC++ programmers attempt
to use the source code.

-----------------------------------------------------------

To build Kingpin model files (.mdx), you will need to use
the kpdata.exe tool that is included, along with a script
file. There is an example script file provided in the
"examples" folder. Open this in a text editor to see how it
works.

To execute the script, type the following at the dos prompt,
whilst inside the SDK folder:

kpdata examples\makemdx.qdt

It will most definately not work, due to the fact that the
example models don't exist. That's your task.

This utility will convert .md2 (Quake2 model) to .mdx (Kingpin
model) files. There are many Quake2 model editors and converters
out there, we recommend you search the internet for an
editor/convertor combination that works best for you.

Kingpin also supports .md2 files, however, so unless you are
creating Plugin Player Models (PPM) or characters that require
locational based damage, we recommend you use .md2 files.

-----------------------------------------------------------

There are a few maps provided in the "examples\maps" folder.
You will need KPradiant that comes on the Kingpin CD to use
these files.

Each map is provided for a different purpose:

bar_sy.map: how to build a bar level.

rival_teams.map: how to build a teamplay or deathmatch
level.

rtpv20.map: an unfinished example motorcycle level. You will
need to type "g_vehicle_test 3" before starting this level.
Keep in mind that the motorcycles are very rough and unfinished.
We decided to keep them in there, incase some mod authors wanted
to make a motorcycle-based mod, this gives you a head-start.

sr1.map: the first playable level in the game, this map shows
how to build a single player level, with various characters
assigned to different gangs, AI moral levels, etc.

-----------------------------------------------------------

This is an unsupported release. If you have problems using this
SDK, we recommend you visit one of several Kingpin fan sites,
changes are someone else has a solution to your problem.

A web-search for "Kingpin" should return several sites worth
visiting.


=================================================
SOFTWARE USE LIMITATIONS AND LIMITED LICENSE
=================================================

GENERAL PRODUCT LICENSE.

This SDK for Kingpin: Life of Crime (the "Software") is intended solely for
your personal noncommercial home entertainment use. You may not decompile,
reverse engineer, or disassemble the Software, except as permitted by law.
Interplay Productions, Xatrix, and Id Software retain[s] all right, title and
interest in the Software including all intellectual property rights embodied
therein and derivatives thereof.  The Software, including, without limitation,
all code, data structures, characters, images, sounds, text, screens, game
play, derivative works and all other elements of the Software may not be
copied, resold, rented, leased, distributed (electronically or otherwise),
used on pay-per-play, coin-op or other for-charge basis, or for any commercial
purpose. Any permissions granted herein are provided on a temporary basis and
can be withdrawn by Interplay Productions at any time. All rights not
expressly granted are reserved.

MODEM AND NETWORK PLAY.

If the Software contains modem or network play, you may play the Software via
modem transmission with another person or persons directly without
transmission through a third party service or indirectly through a third party
service only if such service is an authorized licensee of Interplay. For the
purposes of this license, a third party service refers to any third party
service which provides a connection between two or more users of the Software,
manages, organizes, or facilitates game play, translates protocols, or
otherwise provides a service which commercially exploits the Software, but
does not include a third party service which merely provides a telephonic
connection (and nothing more) for modem or network play. Authorized licensee
services are listed on the Interplay Productions World Wide Web Site located
at http://www.interplay.com. This limited right to transmit the Software
expressly excludes any transmission of the Software or any data streams
thereof on a commercial basis, including, without limitation, transmitting the
Software by way of a commercial service (excepting those specific commercial
services licensed by Interplay) which translates the protocols or manages or
organizes game play sessions. If you would like information about obtaining a
pay-for-play or commercial license to the Software, please call Interplay
Productions in the US at +(949) 553-6655.

ACCEPTANCE OF LICENSE TERMS.

By acquiring and retaining this Software, you assent to the terms and
restrictions of this limited license. If you do not accept the terms of this
limited license, you must return the Software together with all packaging,
manuals and other material contained therein to the store where you acquired
the Software for a full refund.

Kingpin: Life of Crime (c)1999 Xatrix Entertainment, Inc.  All rights
reserved. This product contains software technology licensed from Id Software,
Inc. ("Id Technology").  Id Technology c1996, 1997, 1998, 1999 Id Software,
Inc.  All rights reserved. Kingpin, Kingpin: Life of Crime, Interplay, the
Interplay logo, and "By Gamers. For Gamers." are trademarks of Interplay
Productions. Xatrix and the Xatrix logo are trademarks of Xatrix
Entertainment, Inc. All rights reserved.

All other trademarks and copyrights are the property of their respective
owners.

