#pragma once
#include "Object.h"





class MovingObject
    :public Object {
protected:
    virtual void execthrd(GameMap* gamemap) {
        gamemap->gamemaplock[xpos][ypos]->lock();
        int nx = xpos + dirtoX(dir);
        int ny = ypos + dirtoY(dir);
        if (nx < 0 || ny < 0 || nx >= gamemap->scrx || ny >= gamemap->scry) {
            gamemap->gamemap[xpos][ypos] = NULL;
            gamemap->gamemaplock[xpos][ypos]->unlock();
            todelete.pushback(this);
            return;
        }
        gamemap->gamemaplock[nx][ny]->lock();
        if (gamemap->gamemap[nx][ny] == NULL) {
            gamemap->gamemap[xpos][ypos] = NULL;
            gamemap->gamemap[nx][ny] = this;

            gamemap->gamemaplock[xpos][ypos]->unlock();
            gamemap->gamemaplock[nx][ny]->unlock();

            xpos = nx;
            ypos = ny;
        }
        else {

            gamemap->gamemaplock[xpos][ypos]->unlock();
            gamemap->gamemaplock[nx][ny]->unlock();
        }
    }
public:
    MovingObject(int xpos, int ypos, Direction dir, int sleepTime = 1000)
        :Object(xpos, ypos, sleepTime) {
        symbol = '.';
        this->dir = dir;
    }
    virtual Object* clone(int xpos, int ypos, int sleepTime = 1000) {
        return new MovingObject(xpos, ypos, dir, sleepTime);
    }
};





