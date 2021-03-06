// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#include "printText.hpp"
#include "rawIO.hpp"

namespace stdio {
    namespace {
        /**
         * Emplacement VRAM
         */
        byte* VGA_MEMORY = (byte*) 0xb8000;

        /**
         * Position du curseur
         */
        u16 _cursorPosition = 0;
    }

    void setCursorPosition(u16 pos) {
        pos %= (VGA_WIDTH * VGA_HEIGHT);

        stdio::outb(0x3d4, 0x0f);
        stdio::outb(0x3d5, (byte) (pos & (u16) 0xff));
        stdio::outb(0x3d4, 0x0e);
        stdio::outb(0x3d5, (byte) ((u16) (pos >> (u16) 8) & (u16) 0xff));

        _cursorPosition = pos;
    }

    u16 getCursorPosition() {
        return _cursorPosition;
    }

    u16 getCursorPositionRow() {
        return getCursorPosition() / VGA_WIDTH;
    }

    u16 getCursorPositionCol() {
        return getCursorPosition() % VGA_WIDTH;
    }

    void setCursorPosition(i16 row, i16 col) {
        if (row < 0) {
            row = (row + VGA_HEIGHT) % VGA_HEIGHT;
        }

        if (col < 0) {
            col = (col + VGA_WIDTH) % VGA_WIDTH;
        }

        setCursorPosition(VGA_WIDTH * row + col);
    }

    char getChar(u16 pos) {
        return *(VGA_MEMORY + pos*2);
    }

    void printChar(char c, uint8_t color) {
        switch (c) {
            case '\0':
                break;

            case '\n':
                setCursorPosition(getCursorPosition() + VGA_WIDTH);
                [[fallthrough]]; // En cas de '\n' on veut aussi revenir à la ligne
            case '\r':
                setCursorPosition(getCursorPosition() - (getCursorPosition() % VGA_WIDTH));
                break;

            case '\t': {
                // Accolades pour utiliser une variable dans un case
                u8 i = 0;
                do {
                    printChar(' ');
                    ++i;
                } while (i <= (u8) (getCursorPosition() % VGA_WIDTH) % TAB_LENGTH);
            }
                break;

            case 0x7f: {
                // DEL
                if (getCursorPosition() == 0) {
                    break;
                }

                u16 row = getCursorPositionRow();

                if (getCursorPositionCol() == 0) {
                    do {
                        setCursorPosition(getCursorPosition()-1);
                    }
                    while (getChar(getCursorPosition()) == ' ' && getCursorPositionCol() > 0);
                }
                else {
                    setCursorPosition(getCursorPosition()-1);
                    printChar(' ');
                    setCursorPosition(getCursorPosition()-1);
                }

                if (getCursorPositionRow() == row) {
                    printChar(' ');
                    setCursorPosition(getCursorPosition()-1);
                }
                else {
                    if (getCursorPositionCol() != 0) {
                        setCursorPosition(getCursorPosition()+1);
                    }
                }
            }
                break;

            default:
                if (c >= 0x20 && c < 0x7f) {
                    // de ' ' à DEL (exclus)
                    *(VGA_MEMORY + getCursorPosition() * 2) = c;
                    *(VGA_MEMORY + getCursorPosition() * 2 + 1) = color;
                    setCursorPosition(getCursorPosition() + 1);
                }
        }
    }

    void printString(_In_ const char *str, _In_ const char* end, uint8_t color) {
        if (str == nullptr) {
            u16 c = getCursorPosition();
            setCursorPosition(-1, -1);
            printChar('*', color);
            setCursorPosition(c);
        }
        else {
            byte* charPtr = (byte*) str;

            while (*charPtr != '\0') {
                printChar(*charPtr, color);
                ++charPtr;
            }

            if (end != nullptr) {
                charPtr = (byte *) end;
                while (*charPtr != '\0') {
                    printChar(*charPtr, color);
                    ++charPtr;
                }
            }
        }
    }

    void clearScreen(uint8_t color) {
        // Fonctionne toujours
        /*
        uint64_t value = 0;
        value += (uint64_t) color << 8;
        value += (uint64_t) color << 24;
        value += (uint64_t) color << 40;
        value += (uint64_t) color << 56;

        for (uint64_t *i = (u64 *)VGA_MEMORY; i < (u64 *)(VGA_MEMORY + 4000); i++) {
            *i = value;
        }
         */

        // Fonctionne ssi setCursorPosition loop à 0

        setCursorPosition(0);

        do {
            printChar(' ', color);
        } while (getCursorPosition() != 0);
    }
}
