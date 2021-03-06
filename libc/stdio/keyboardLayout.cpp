// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 04/10/2020.

#include "keyboardLayout.hpp"

#define _layoutAZERTY {\
        /*        0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F */\
        /* 0 */ '\0', 0x1b, '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '0' , ')' , '=' , 0x7f, '\t',\
        /* 1 */ 'a' , 'z' , 'e' , 'r' , 't' , 'y' , 'u' , 'i' , 'o' , 'p' , '^' , '$' , '\n', '\0', 'q' , 's' ,\
        /* 2 */ 'd' , 'f' , 'g' , 'h' , 'j' , 'k' , 'l' , 'm' , '%' , '2' , '\0', '*' , 'w' , 'x' , 'c' , 'v' ,\
        /* 3 */ 'b' , 'n' , ',' , ';' , ':' , '!' , '\0', '*' , '\0', ' ' , '\0', '\0', '\0', '\0', '\0', '\0',\
        /* 4 */ '\0', '\0', '\0', '\0', '\0', '\0', '\0',\
}

// https://wiki.osdev.org/Keyboard
/*
 * 00:
 * 01: ESC
 * 0e: BACKSPACE
 * 1d: left ctrl
 * 28: ù
 * 29: ²
 * 2a: SHIFT
 * 36: WIN ? (right shift)
 * 38: ALT
 * 3a: Caps Lock
 * 3b à 44: F1 à F10
 * 45: Pause
 * 46: Arrêt défil
 */

#define _layoutQWERTY {\
}

namespace stdio::keyboard {
    KeyboardLayout layouts[2] = {
        {
            _layoutAZERTY,
            0x01,
            0x0e,
            0x2a,
            0x38,
            0x1d,
            0x3a
        },
        {
            _layoutQWERTY,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00
        },
    };

    char VK_ESC;
    char VK_DEL;
    char VK_SHIFT;
    char VK_ALT;
    char VK_CTRL;
    char VK_CAPS_LOCK;

    void setLayoutSpecialChars(KeyboardLayoutType type) {
        KeyboardLayout layout = layouts[type];

        VK_ESC = layout.VK_ESC;
        VK_DEL = layout.VK_DEL;
        VK_SHIFT = layout.VK_SHIFT;
        VK_ALT = layout.VK_ALT;
        VK_CTRL = layout.VK_CTRL;
        VK_CAPS_LOCK = layout.VK_CAPS_LOCK;
    }
}

#undef _layoutAZERTY
#undef _layoutQWERTY
