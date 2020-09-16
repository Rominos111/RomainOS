// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 09/09/2020.

#ifndef ROMAINOS_PRINTTEXT_HPP
#define ROMAINOS_PRINTTEXT_HPP

#include "types.hpp"
#include "string.hpp"

#include "IO/IO.hpp"
#include "IO/textColorModes.hpp"

/**
 * Emplacement VRAM
 */
#define VGA_MEMORY (byte*) 0xb8000

/**
 * Largeur d'une ligne VGA
 */
#define VGA_WIDTH 80

/**
 * Hauteur d'une colonne
 */
#define VGA_HEIGHT 25

/**
 * Largeur d'un tab
 */
#define TAB_LENGTH 4

/**
 * Position du curseur
 */
u16 _cursorPosition = 0;

/**
 * Set la position du curseur
 *
 * @param pos Position
 */
void setCursorPosition(u16 pos) {
    pos %= (VGA_WIDTH * VGA_HEIGHT);

    outb(0x3d4, 0x0f);
    outb(0x3d5, (byte)(pos & (u16) 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (byte)((u16) (pos >> (u16) 8) & (u16) 0xff));

    _cursorPosition = pos;
}

/**
 * Getter position curseur
 *
 * @return Position
 */
u16 getCursorPosition() {
    return _cursorPosition;
}

/**
 * Set la position du curseur
 *
 * @param row Ligne, -1 = dernière ligne, -2 = avant-dernière, etc
 * @param col Colonne, -1 = dernière colonne, -2 = avant-dernière, etc
 */
void setCursorPosition(i16 row, i16 col) {
    if (row < 0) {
        row = (row + VGA_HEIGHT) % VGA_HEIGHT;
    }

    if (col < 0) {
        col = (col + VGA_WIDTH) % VGA_WIDTH;
    }

    setCursorPosition(VGA_WIDTH*row + col);
}

/**
 * Affiche un caractère
 *
 * @param c Caractère
 * @param color Couleur
 */
void printChar(char c, uint8_t color = BG_DEFAULT | FG_DEFAULT) {
    switch (c) {
        case '\n':
            setCursorPosition(getCursorPosition() + VGA_WIDTH);
            [[fallthrough]]; // En cas de '\n' on veut aussi revenir à la ligne
        case '\r':
            setCursorPosition(getCursorPosition() - (getCursorPosition() %  VGA_WIDTH));
            break;

        case '\t':
            for (u8 i=0; i < (u8) (getCursorPosition() % VGA_WIDTH) % TAB_LENGTH; i++) {
                printChar(' ');
            }
            break;

        default:
            *(VGA_MEMORY + getCursorPosition()*2) = c;
            *(VGA_MEMORY + getCursorPosition()*2 + 1) = color;
            setCursorPosition(getCursorPosition()+1);
    }
}

/**
 * Affiche une chaine de caractères
 *
 * @param str String
 * @param color Couleur
 */
void printString(const char* str, uint8_t color = BG_DEFAULT | FG_DEFAULT) {
    byte* charPtr = (byte*) str;

    if (*charPtr == '\0') {
        setCursorPosition(-1, -1);
        printChar('*');
    }

    while (*charPtr != '\0') {
        printChar(*charPtr);
        charPtr++;
    }
}

/**
 * Clear l'écran VGA
 *
 * @param color Couleur
 */
void clearScreen(uint8_t color = BG_DEFAULT | FG_DEFAULT) {
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

#endif //ROMAINOS_PRINTTEXT_HPP