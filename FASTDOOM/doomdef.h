//
// Copyright (C) 1993-1996 Id Software, Inc.
// Copyright (C) 1993-2008 Raven Software
// Copyright (C) 2016-2017 Alexey Khokholov (Nuke.YKT)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//  Internally used data structures for virtually everything,
//   key definitions, lots of other stuff.
//

#ifndef __DOOMDEF__
#define __DOOMDEF__

//
// Global parameters/defines.
//
// DOOM version
enum
{
    VERSION = 109
};

#define COMPLEVEL_DOOM              2
#define COMPLEVEL_ULTIMATE_DOOM     3
#define COMPLEVEL_FINAL_DOOM        4

// Game mode handling - identify IWAD version
//  to handle IWAD dependend animations etc.
typedef enum
{
  shareware,	// DOOM 1 shareware, E1, M9
  registered,	// DOOM 1 registered, E3, M27
  commercial,	// DOOM 2 retail, E1 M34
  retail,	    // DOOM 1 retail, E4, M36
  indetermined	// Well, no IWAD found.
} gamemode_t;

// Mission packs - might be useful for TC stuff?
typedef enum
{
  doom,		    // DOOM 1
  doom2,	    // DOOM 2
  pack_tnt,	    // TNT mission pack
  pack_plut,	// Plutonia pack
  none
} gamemission_t;

//
// For resize of screen, at start of game.
// It will not work dynamically, see visplanes.
//
#define BASE_WIDTH 320

// It is educational but futile to change this
//  scaling e.g. to 2. Drawing of status bar,
//  menues etc. is tied to the scale implied
//  by the graphics.
#define SCREEN_MUL 1
#define INV_ASPECT_RATIO 0.625 // 0.75, ideally

// Defines suck. C sucks.
// C++ might sucks for OOP, but it sure is a better C.
// So there.
#define SCREENWIDTH 320
//SCREEN_MUL*BASE_WIDTH //320
#define SCREENHEIGHT 200
//(int)(SCREEN_MUL*BASE_WIDTH*INV_ASPECT_RATIO) //200

// The maximum number of players, multiplayer/networking.
#define MAXPLAYERS 4

// State updates, number of tics / second.
#define TICRATE 35

// The current state of the game: whether we are
// playing, gazing at the intermission screen,
// the game final animation, or a demo.
typedef enum
{
    GS_LEVEL,
    GS_INTERMISSION,
    GS_FINALE,
    GS_DEMOSCREEN
} gamestate_t;

//
// Difficulty/skill settings/filters.
//

// Skill flags.
#define MTF_EASY 1
#define MTF_NORMAL 2
#define MTF_HARD 4

// Deaf monsters/do not react to sound.
#define MTF_AMBUSH 8

typedef enum
{
    sk_baby,
    sk_easy,
    sk_medium,
    sk_hard,
    sk_nightmare
} skill_t;

//
// Key cards.
//
typedef enum
{
    it_bluecard,
    it_yellowcard,
    it_redcard,
    it_blueskull,
    it_yellowskull,
    it_redskull,

    NUMCARDS

} card_t;

// The defined weapons,
//  including a marker indicating
//  user has not changed weapon.
typedef enum
{
    wp_fist,
    wp_pistol,
    wp_shotgun,
    wp_chaingun,
    wp_missile,
    wp_plasma,
    wp_bfg,
    wp_chainsaw,
    wp_supershotgun,

    NUMWEAPONS,

    // No pending weapon change.
    wp_nochange

} weapontype_t;

// Ammunition types defined.
typedef enum
{
    am_clip,  // Pistol / chaingun ammo.
    am_shell, // Shotgun / double barreled shotgun.
    am_cell,  // Plasma rifle, BFG.
    am_misl,  // Missile launcher.
    NUMAMMO,
    am_noammo // Unlimited for chainsaw / fist.

} ammotype_t;

// Power up artifacts.
typedef enum
{
    pw_invulnerability,
    pw_strength,
    pw_invisibility,
    pw_ironfeet,
    pw_allmap,
    pw_infrared,
    NUMPOWERS

} powertype_t;

//
// Power up durations,
//  how many seconds till expiration,
//  assuming TICRATE is 35 ticks/second.
//
typedef enum
{
    INVULNTICS = (30 * TICRATE),
    INVISTICS = (60 * TICRATE),
    INFRATICS = (120 * TICRATE),
    IRONTICS = (60 * TICRATE)

} powerduration_t;

//
// DOOM keyboard definition.
// This is the stuff configured by Setup.Exe.
// Most key data are simple ascii (uppercased).
//
#define KEY_RIGHTARROW 0xae
#define KEY_LEFTARROW 0xac
#define KEY_UPARROW 0xad
#define KEY_DOWNARROW 0xaf
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_TAB 9
#define KEY_F1 (0x80 + 0x3b)
#define KEY_F2 (0x80 + 0x3c)
#define KEY_F3 (0x80 + 0x3d)
#define KEY_F4 (0x80 + 0x3e)
#define KEY_F5 (0x80 + 0x3f)
#define KEY_F6 (0x80 + 0x40)
#define KEY_F7 (0x80 + 0x41)
#define KEY_F8 (0x80 + 0x42)
#define KEY_F9 (0x80 + 0x43)
#define KEY_F10 (0x80 + 0x44)
#define KEY_F11 (0x80 + 0x57)
#define KEY_F12 (0x80 + 0x58)

#define KEY_BACKSPACE 127
#define KEY_PAUSE 0xff

#define KEY_EQUALS 0x3d
#define KEY_MINUS 0x2d

#define KEY_RSHIFT (0x80 + 0x36)
#define KEY_RCTRL (0x80 + 0x1d)
#define KEY_RALT (0x80 + 0x38)

#define KEY_LALT KEY_RALT

typedef enum
{
    INVISIBLE_NORMAL,
    INVISIBLE_FLAT,
    INVISIBLE_FLAT_SATURN,
    INVISIBLE_SATURN,
    INVISIBLE_TRANSLUCENT,
    NUM_INVISIBLERENDER
} invisiblerender_t;

typedef enum
{
    VISPLANES_NORMAL,
    VISPLANES_FLAT,
    VISPLANES_FLATTER,
    NUM_VISPLANESRENDER
} invisiblerender_t;

typedef enum
{
    DETAIL_HIGH,
    DETAIL_LOW,
    DETAIL_POTATO,
    NUM_DETAIL
} detail_t;

typedef enum
{
    INTEL_386SX,
    INTEL_386DX,
    INTEL_486,
    CYRIX_486,
    UMC_GREEN_486,
    CYRIX_5X86,
    AMD_K5,
    INTEL_PENTIUM,
    NUM_CPU
} cpu_t;

#endif // __DOOMDEF__
