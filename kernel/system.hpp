// SPDX-License-Identifier: GPL-3.0-or-later
// Created by Romain on 26/09/2020.

#ifndef ROMAINOS_SYSTEM_HPP
#define ROMAINOS_SYSTEM_HPP

#include <cstdio>
#include <cstdlib>

#include "../libc/stdio/rawIO.hpp"

namespace std::system {
    /**
     * Shutdown
     */
    void shutdown();

    /**
     * Shutdown avec un message
     */
    void shutdownAndPrint();
}

#endif //ROMAINOS_SYSTEM_HPP
