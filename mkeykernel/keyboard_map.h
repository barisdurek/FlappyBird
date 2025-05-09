#ifndef _KEYBOARD_MAP_H
#define _KEYBOARD_MAP_H

#include <stdbool.h>

static const unsigned char keyboard_map[128] = {
    0,   27,  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  /* 0x00 - 0x09: ESC (27) */
    '9', '0',  '-',  '=',  0,    0,    'q',  'w',  'e',  'r',  /* 0x0A - 0x13 */
    't', 'y',  'u',  'i',  'o',  'p',  '[',  ']',  0,    0,    /* 0x14 - 0x1D */
    'a', 's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  /* 0x1E - 0x27 */
    '\'', '`', 0,    '\\', 'z',  'x',  'c',  'v',  'b',  'n',  /* 0x28 - 0x31 */
    'm', ',',  '.',  '/',  0,    '*',  0,    32,   0,    0,    /* 0x32 - 0x3B: Spacebar (32) */
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x3C - 0x45 */
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x46 - 0x4F */
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x50 - 0x59 */
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x5A - 0x63 */
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x64 - 0x6D */
    0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x6E - 0x77 */
    0,   0,    0,    0,    0,    0,    0,    0                 /* 0x78 - 0x7F */
};

#define SPACEBAR 32  
#define ESCAPE   27  

static inline bool is_game_key(unsigned char keycode) {
    return keycode == SPACEBAR || keycode == ESCAPE;
}

#endif 