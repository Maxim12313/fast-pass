#pragma once

#include <atomic>
#include <cstdint>
#include <iostream>
#include <string.h>

const int HEIGHT = 800;
const int WIDTH = 1200;

const int EVENT_WAIT = 0;
const int SERVER_PRECISION = 10;

const int MAX_PLAYERS = 3;

std::atomic<bool> running = true;

#define __FILENAME__                                                           \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef DEBUG
#define LOG(msg)                                                               \
    std::cerr << "[LOG] " << __FILENAME__ << ":" << __LINE__ << " ("           \
              << __func__ << ") - " << msg << std::endl;
#else
#define LOG(msg)                                                               \
    do {                                                                       \
    } while (0)
#endif
