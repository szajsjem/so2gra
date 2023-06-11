#include <curses.h>
#include <iostream>
#include <vector>
#include <type_traits>
#include <thread>
#include <mutex>
#include <list>

#include "commons.h"
#include "Object.h"
#include "GeneratorObject.h"
#include "MovingObject.h"
#include "SpecializedNonMoving.h"
#include "SpecializedMoving.h"

int cposx = 0, oldcx = 0;
int cposy = 0, oldcy = 0;
Direction lookingdir; int showdir = 0;

int selmenutab = 0;
int contime = 1000, otime = 1000, gtime = 1000, celltime = 1000;
Object* selectedCell = new MovingObject(0, 0, lookingdir, 1000);
int selcell = 0; Direction selceldir;

GameMap gamemap;
std::mutex screenlock;

void printmenu() {
    screenlock.lock();
    mvprintw(gamemap.scry, 0, "Obrot: %s ", dirTochar(lookingdir));
    mvprintw(gamemap.scry, 10, "Pozycja wskaznika: %d,%d\n", cposx, cposy);
    mvprintw(gamemap.scry + 1, 0, "| konsola | obracacz  | generator | cell:%2s|", dirTochar(selceldir));
    switch (selcell) {
    case(0):
        mvprintw(gamemap.scry + 1, 1, "*");
        break;
    case(1):
        mvprintw(gamemap.scry + 1, 11, "*");
        break;
    case(2):
        mvprintw(gamemap.scry + 1, 23, "*");
        break;
    case(3):
        mvprintw(gamemap.scry + 1, 35, "*");
        break;
    default:
        break;
    }
    mvprintw(gamemap.scry + 2, 0, "| t:%4d  | t:%4d    | t:%4d    | t:%4d |", contime, otime, gtime, celltime);
    mvprintw(gamemap.scry + 3, 0, "selected moving cell:'%c'", selectedCell != NULL ? selectedCell->Symbol() : ' ');
    mvprintw(gamemap.scry + 4, 0, "Zmiana ustawien: r-obracanie; + zwieksz czas; - zmniejsz czas; TAB - zmien cell\n");
    mvprintw(gamemap.scry + 5, 0, "Wystawianie:c-console; o-obracacz; g-generator; strzalki-poruszanie; \n");
    mvprintw(gamemap.scry + 6, 0, ">");
    screenlock.unlock();
}

void renderscreen() {
    screenlock.lock();
    for (int i = 0; i< gamemap.scrx; i++)
        for (int j = 0; j < gamemap.scry; j++) {
            mvprintw(j, i , "");
            gamemap.gamemaplock[i][j]->lock();
            if (gamemap.gamemap[i][j] != NULL) {
                printw("%c", gamemap.gamemap[i][j]->Symbol());
            } else {
                printw(" ");
            }
            gamemap.gamemaplock[i][j]->unlock();
        }
    screenlock.unlock();
}

void rendercursor() {
    if (cposy < 0)cposy = 0;
    if (cposy >= gamemap.scry)cposy = gamemap.scry - 1;
    if (cposx < 0)cposx = 0;
    if (cposx >= gamemap.scrx)cposx = gamemap.scrx - 1;
    oldcy = cposy;
    oldcx = cposx;
    screenlock.lock();
    mvprintw(oldcy , oldcx , "#");
    if (showdir == 0)
        mvprintw(oldcy+dirtoY(lookingdir), oldcx + dirtoX(lookingdir), "@");
    screenlock.unlock();
    showdir++;
    if (showdir > 2) showdir = 0;
}

void screenRefresh() {
    while (true) {
        Sleep(500);
        renderscreen();
        rendercursor();
        printmenu();
        refresh();
    }
}

int main(const char **args, int argv) {

    // todo get size from arguments -w %d -h %d



    gamemap.gamemap.resize(gamemap.scrx);
    gamemap.gamemaplock.resize(gamemap.scrx);
    for (auto& v : gamemap.gamemap)
        v.resize(gamemap.scry);
    for (auto& v : gamemap.gamemaplock) {
        v.resize(gamemap.scry);
        for (auto& l : v)
            l = new std::mutex;
    }
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    std::thread refresh(screenRefresh);
    while (1) {
        renderscreen();
        rendercursor();
        int litera = getch();
        switch (litera) {
        case(258):// arr d
            cposy++;
            break;
        case(259):// arr u
            cposy--;
            break;
        case(260):// arr l
            cposx--;
            break;
        case(261):// arr r
            cposx++;
            break;
        case(330):// del
            gamemap.gamemaplock[cposx][cposy]->lock();
            if (gamemap.gamemap[cposx][cposy] != NULL) {
                delete gamemap.gamemap[cposx][cposy];
                gamemap.gamemap[cposx][cposy] = NULL;
            }
            gamemap.gamemaplock[cposx][cposy]->unlock();
            break;
        case(99):// c
            gamemap.gamemaplock[cposx][cposy]->lock();
            if (gamemap.gamemap[cposx][cposy] == NULL) {
                gamemap.gamemap[cposx][cposy] = new Object(cposx, cposy, contime);
                gamemap.gamemap[cposx][cposy]->start(&gamemap);
            }
            gamemap.gamemaplock[cposx][cposy]->unlock();
            break;
        case(103):// g
            gamemap.gamemaplock[cposx][cposy]->lock();
            if (gamemap.gamemap[cposx][cposy] == NULL) {
                gamemap.gamemap[cposx][cposy] =
                    new GeneratorObject(cposx, cposy, lookingdir,
                        selectedCell->clone(cposx, cposy), celltime, gtime);
                gamemap.gamemap[cposx][cposy]->start(&gamemap);
            }
            gamemap.gamemaplock[cposx][cposy]->unlock();
            break;
        case(114):// r
            lookingdir = nextdir(lookingdir);
            break;
        case(67):// C
        case(111):// c
            gamemap.gamemaplock[cposx][cposy]->lock();
            if (gamemap.gamemap[cposx][cposy] == NULL) {
                gamemap.gamemap[cposx][cposy] = new Obracacz(cposx, cposy, lookingdir, otime);
                gamemap.gamemap[cposx][cposy]->start(&gamemap);
            }
            gamemap.gamemaplock[cposx][cposy]->unlock();
            break;
        case(9):// tab
            selcell++;
            if (selcell >= 4)selcell = 0;
            break;
        case(351):// shift + tab
            selceldir = lookingdir;
            selectedCell = new MovingObject(0, 0, selceldir, celltime);
            // todo
            break;
        case(465):// +
            switch (selcell) {
            case(0):
                contime++;
                break;
            case(1):
                otime++;
                break;
            case(2):
                gtime++;
                break;
            case(3):
                celltime++;
                break;
            default:
                break;
            }
            break;
        case(464):// -
            switch (selcell) {
            case(0):
                contime--;
                break;
            case(1):
                otime--;
                break;
            case(2):
                gtime--;
                break;
            case(3):
                celltime--;
                break;
            default:
                break;
            }
            break;
        default:
            printw("%d                               \n", litera);
            break;
        }
    }
    return 0;
}

