#pragma once
#include <vector>
#include <list>
#include <mutex>
#ifdef _WIN32
#include <Windows.h>
#else  // funkcja sleep

#endif
#include <curses.h>

class Object;

template<class t>
class PushPopSafeList
    :public std::list<t> {
 public:
    std::mutex lock;
    void pushback(t const&  x) {
        lock.lock();
        this->push_back(x);
        lock.unlock();
    }
    void popfront() {
        lock.lock();
        this->pop_front();
        lock.unlock();
    }
};

template<class t>
class CustumVector
    :public std::vector<t> {
 public:
    t& operator[](const size_t indx) {
        static t help;
        if constexpr (std::is_same_v<t, Object*>) {
            help = NULL;
        } else if constexpr (std::is_same_v<t, std::mutex*>) {
            static std::mutex* border = new std::mutex;
            help = border;
        }
        if (indx < 0)return help;
        if (indx >= this->std::vector<t>::size())return help;
        return this->std::vector<t>::operator[](indx);
    }
};

struct GameMap {
    int scrx = 60, scry = 20;
    CustumVector<CustumVector<Object*>> gamemap;
    CustumVector<CustumVector<std::mutex*>> gamemaplock;
};


enum Direction {
    NE = 0,
    N = 1,
    NW = 2,
    W = 3,
    SW = 4,
    S = 5,
    SE = 6,
    E = 7,
    maxdir = 8
};
int dirtoX(Direction d) {
    switch (d) {
    case NW:
    case W:
    case SW:
        return 1;
    case NE:
    case SE:
    case E:
        return -1;
    default:
        return 0;
    }
}
int dirtoY(Direction d) {
    switch (d) {
    case NE:
    case N:
    case NW:
        return -1;
    case SW:
    case S:
    case SE:
        return 1;
    default:
        return 0;
    }
}
Direction nextdir(Direction d) {
    return (Direction)((d + 1) % maxdir);
}

const char* dirTochar(Direction d) {
    switch (d) {
    case NE:
        return "NE";
        break;
    case N:
        return "N ";
        break;
    case NW:
        return "NW";
        break;
    case W:
        return "W ";
        break;
    case SW:
        return "SW";
        break;
    case S:
        return "S ";
        break;
    case SE:
        return "SE";
        break;
    case E:
        return "E ";
        break;
    default:
        break;
    }
    return "??";
}

