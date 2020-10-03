// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 08/09/2020.

#include <io/printText.hpp>
#include <io/IDT.hpp>
#include <io/IO.hpp>
#include <memory.hpp>

/**
 * Point io'entrée de l'OS
 */
extern "C" void _start() {
    std::io::clearScreen();
    std::io::setCursorPosition(0, 0);
    std::io::idt::initIDT();
    std::io::setKeyboardLayout(std::io::AZERTY);
    std::memory::initHeap(0x100000, 0x100000);

    std::io::printString("Tout fonctionne !\n", nullptr, BG_RED | FG_WHITE);
}
