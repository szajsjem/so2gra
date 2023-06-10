#pragma once
#include "commons.h"
#include <thread>

PushPopSafeList<Object*> todelete;
//std::thread* deleter_thread = new std::thread([&]() {
//    while (true) {
//        Sleep(1000);
//        if (todelete.size() > 1) {
//            Object* t = todelete.front();
//            todelete.popfront();
//            delete t;
//        }
//    }
//    });





class Object {
protected:
    char symbol = 'c';
    int xpos;
    int ypos;
    int sleepTime;
    Direction dir = N;

    std::thread* thrd = NULL;
    bool* thrdworking = NULL;
    std::mutex *blockdelete=NULL;

    GameMap* gamemap;

    virtual void timexec() {
        bool* working = new bool;
        std::mutex* blockdel = new std::mutex;
        thrdworking = working;
        blockdelete = blockdel;
        *working = true;
        blockdel->lock();
        while (*working) {
            if(*working)
                execthrd(gamemap);
            blockdel->unlock();
            Sleep(sleepTime);
            blockdel->lock();
        }
        blockdel->unlock();
        delete working;
        delete blockdel;
    }
    virtual void execthrd(GameMap* gamemap) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    gamemap->gamemaplock[xpos + i][ypos + j]->lock();
                    if (gamemap->gamemap[xpos + i][ypos + j] != NULL) {
                        printw("W poblizu %d,%d jest: %c                                                \n",
                            xpos, ypos, gamemap->gamemap[xpos + i][ypos + j]->symbol);
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
        if (blockdelete != NULL) {
            blockdelete->lock();
            if (thrdworking != NULL)
                *thrdworking = false;
            if (thrd != NULL) {
                thrd->join();
                delete thrd;
            }
            blockdelete->unlock();
        }
    }
    virtual void start(GameMap* gamemap) {
        if (thrd == NULL) {
            this->gamemap = gamemap;
            thrd = new std::thread([](Object*t) {t->timexec(); },this);
        }
    }
    char Symbol() {
        return symbol;
    }
    void rotate() {
        dir = nextdir(dir);
    }
    void setdir(Direction d) {
        dir = d;
    }
};