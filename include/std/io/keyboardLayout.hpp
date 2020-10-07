// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 04/10/2020.

#ifndef ROMAINOS_KEYBOARDLAYOUT_HPP
#define ROMAINOS_KEYBOARDLAYOUT_HPP

namespace std::io {
    struct KeyboardLayout {
        char layout[256];
        char VK_ESC;
        char VK_DEL;
        char VK_SHIFT;
        char VK_ALT;
        char VK_CTRL;
        char VK_CAPS_LOCK;
    };

    typedef enum {
        AZERTY = 0,
        QWERTY = 1
    } KeyboardLayoutType;

    extern KeyboardLayout layouts[2];
}

#endif //ROMAINOS_KEYBOARDLAYOUT_HPP