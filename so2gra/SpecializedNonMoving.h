#pragma once
#include "Object.h"


class Obracacz
    : public Object {
protected:
    virtual void execthrd(GameMap* gamemap) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    gamemap->gamemaplock[xpos + i][ypos + j]->lock();
                    if (gamemap->gamemap[xpos + i][ypos + j] != NULL) {
                        gamemap->gamemap[xpos + i][ypos + j]->setdir(dir);
                    }
                    gamemap->gamemaplock[xpos + i][ypos + j]->unlock();
                }
            }
        }
    }
public:
    Obracacz(int xpos, int ypos, Direction d, int sleepTime = 1000)
        :Object(xpos, ypos, sleepTime) {
        symbol = 'o';
        dir = d;
    }
    virtual Object* clone(int xpos, int ypos, int sleepTime = 1000) {
        return new Obracacz(xpos, ypos, dir, sleepTime);
    }
};


class Fabryka
    :public Object {
protected:
    virtual void execthrd(GameMap* gamemap) {
        //todo test if two . at input
        //and output :
    }
public:
    Fabryka(int xpos, int ypos, Direction d, int sleepTime = 1000)
        :Object(xpos, ypos, sleepTime) {
        symbol = 'o';
        dir = d;
    }
    virtual Object* clone(int xpos, int ypos, int sleepTime = 1000) {
        return new Fabryka(xpos, ypos, dir, sleepTime);
    }
};



//portal in


//portal out

