#pragma once
#include "commons.h"
#include <thread>

PushPopSafeList<Object*> todelete;
std::thread* deleter_thread = new std::thread([&]() {
    while (true) {
        Sleep(1000);
        if (todelete.size() > 1) {
            Object* t = todelete.front();
            todelete.popfront();
            delete t;
        }
    }
    });





class Object {
protected:
    char symbol = 'c';
    std::thread* thrd = NULL;
    int xpos;
    int ypos;
    int sleepTime;
    bool* thrdworking = NULL;
    std::mutex blockdel;
    Direction dir = N;
    int childtime = 1000;
    GameMap* gamemap;

    virtual void timexec() {
        bool* working = new bool;
        thrdworking = working;
        *working = true;
        while (*working) {
            blockdel.lock();
            execthrd(gamemap);
            blockdel.unlock();
            Sleep(sleepTime);
        }
        delete working;
    }
    virtual void execthrd(GameMap* gamemap) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    gamemap->gamemaplock[xpos + i][ypos + j]->lock();
                    if (gamemap->gamemap[xpos + i][ypos + j] != NULL) {
                        printw("W poblizu %d,%d jest: %c                                                \n", xpos, ypos, gamemap->gamemap[xpos + i][ypos + j]->symbol);
                    }
                    gamemap->gamemaplock[xpos + i][ypos + j]->unlock();
                }
            }
        }
    }
public:
    Object(int xpos, int ypos, int sleepTime = 1000) {
        this->sleepTime = sleepTime;
        this->xpos = xpos;
        this->ypos = ypos;
    }
    virtual Object* clone(int xpos, int ypos, int sleepTime = 1000) {
        return new Object(xpos, ypos, sleepTime);
    }
    virtual ~Object() {
        blockdel.lock();
        if (thrdworking != NULL)
            *thrdworking = false;
        if (thrd != NULL) {
            thrd->detach();
            delete thrd;
        }
        blockdel.unlock();
    }
    virtual void start(GameMap* gamemap) {
        if (thrd == NULL) {
            this->gamemap = gamemap;
            thrd = new std::thread([&]() {this->timexec(); });
        }
    }
    char Symbol() {
        return symbol;
    }
    void setxy(int x, int y) {
        xpos = x;
        ypos = y;
    }
    void rotate() {
        dir = nextdir(dir);
    }
    void setdir(Direction d) {
        dir = d;
    }
};