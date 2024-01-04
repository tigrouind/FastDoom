//
// Copyright (C) 1993-1996 Id Software, Inc.
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
// 	The status bar widget code.
//

#ifndef __STLIB__
#define __STLIB__

// We are referring to patches.
#include "r_defs.h"

//
// Background and foreground screen numbers
//
#define BG 4
#define FG 0

//
// Typedefs of widgets
//

// Number widget

typedef struct
{
    // upper right-hand corner
    //  of the number (right-justified)
    int x;
    int y;

    // max # of digits in number
    int width;

    // last number value
    int oldnum;

    // pointer to current value
    int *num;

    // pointer to boolean stating
    //  whether to update number
    byte *on;

    // list of patches for 0-9
    patch_t **p;

    // user data
    int data;

} st_number_t;

// Percent widget ("child" of number widget,
//  or, more precisely, contains a number widget.)
typedef struct
{
    // number information
    st_number_t n;

    // percent sign graphic
    patch_t *p;

} st_percent_t;

// Multiple Icon widget
typedef struct
{
    // center-justified location of icons
    int x;
    int y;

    // last icon number
    int oldinum;

    // pointer to current icon
    int *inum;

    // pointer to boolean stating
    //  whether to update icon
    byte *on;

    // list of icons
    patch_t **p;

    // user data
    int data;

} st_multicon_t;

// Binary Icon widget

typedef struct
{
    // center-justified location of icon
    int x;
    int y;

    // pointer to boolean
    //  stating whether to update icon
    byte *on;

    patch_t *p; // icon
    int data;   // user data

} st_binicon_t;

//
// Widget creation, access, and update routines
//

// Initializes widget library.
// More precisely, initialize STMINUS,
//  everything else is done somewhere else.
//
void STlib_init(void);

// Number widget routines
void STlib_initNum(st_number_t *n, int x, int y, patch_t **pl, int *num, byte *on);

void STlib_updateNum(st_number_t *n, byte refresh);
void STlib_updateNum_Direct(st_number_t *n);

// Percent widget routines
void STlib_initPercent(st_percent_t *p, int x, int y, patch_t **pl, int *num, byte *on, patch_t *percent);

void STlib_updatePercent(st_percent_t *per, int refresh);
void STlib_updatePercent_Direct(st_percent_t *per);

// Multiple Icon widget routines
void STlib_initMultIcon(st_multicon_t *mi, int x, int y, patch_t **il, int *inum, byte *on);
void STlib_initMultIcon_Direct(st_multicon_t *mi, int x, int y, patch_t **il, int *inum, byte *on);

void STlib_updateMultIcon(st_multicon_t *mi, byte refresh);
void STlib_updateMultIcon_Direct(st_multicon_t *mi);

// Binary Icon widget routines

void STlib_initBinIcon(st_binicon_t *b, int x, int y, patch_t *i, byte *on);

void STlib_updateBinIcon(st_binicon_t *bi, byte refresh);
void STlib_updateBinIcon_Direct(st_binicon_t *bi);

void STlib_drawNumText(st_number_t *n, int x, int y);

#endif
