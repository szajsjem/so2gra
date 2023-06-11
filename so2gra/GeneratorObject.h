#pragma once
#include "Object.h"




class GeneratorObject
    :public Object {
 protected:
    Object* produce = NULL;
    int childtime = 1000;
    virtual void execthrd(GameMap* gamemap) {
        int nx = xpos + dirtoX(dir);
        int ny = ypos + dirtoY(dir);
        gamemap->gamemaplock[nx][ny]->lock();
        if (gamemap->gamemap[nx][ny] == NULL) {
            gamemap->gamemap[nx][ny] = produce->clone(nx, ny, childtime);
            if (gamemap->gamemap[nx][ny] != NULL)
                gamemap->gamemap[nx][ny]->start(gamemap);
        }
        gamemap->gamemaplock[nx][ny]->unlock();
    }
 public:
    GeneratorObject(int xpos, int ypos, Direction dir, Object* objtospawn,
        int spawnedsleeptime = 1000, int sleepTime = 1000)
        :Object(xpos, ypos, sleepTime) {
        symbol = 'g';
        this->dir = dir;
        childtime = spawnedsleeptime;
        produce = objtospawn;
    }
    virtual Object* clone(int xpos, int ypos, int sleepTime = 1000) {
        return new GeneratorObject(xpos, ypos, dir, produce, childtime , sleepTime);
    }
};


