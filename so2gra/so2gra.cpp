#include <iostream>
#include <vector>
#include <type_traits>
#include <thread>
#include <mutex>
#ifdef _WIN32
#include <Windows.h>
#else//funkcja sleep

#endif
#include <curses.h>
#include <list>

class Object;

std::list<Object*> todelete;

template<class t>
class CustumVector
    :public std::vector<t> {
public:
    t& operator[](const size_t indx) {
        t help;
        if constexpr (std::is_same_v<t,Object*>) {
            help = NULL;
        }
        if (indx < 0)return help;
        if (indx >= std::vector<t>::size())return help;
        return std::vector<t>::operator[](indx);
    }
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
    switch (d)
    {
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
    switch (d)
    {
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

class Object {
protected:
    char symbol = 'c';
    std::thread* thrd = NULL;
    int xpos;
    int ypos;
    int sleepTime;
    bool* thrdworking=NULL;
    std::mutex blockdel;
    Direction dir = N;
    int childtime = 1000;

    virtual void timexec(CustumVector<CustumVector<Object*>>& gamemap, std::mutex& maplock) {
        bool* working = new bool;
        thrdworking = working;
        *working = true;
        while (*working) {
            blockdel.lock();
            execthrd(gamemap, maplock);
            blockdel.unlock();
            Sleep(sleepTime);
        }
        delete working;
    }
    virtual void execthrd(CustumVector<CustumVector<Object*>>& gamemap, std::mutex& maplock) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    maplock.lock();
                    if (gamemap[xpos + i][ypos + j] != NULL) {
                        printw("W poblizu %d,%d jest: %c                                                \n", xpos, ypos, gamemap[xpos + i][ypos + j]->symbol);
                    }
                    maplock.unlock();
                }
            }
        }
    }
public:
    Object(int xpos,int ypos, int sleepTime = 1000) {
        this->sleepTime = sleepTime;
        this->xpos = xpos;
        this->ypos = ypos;
    }
    virtual ~Object() {
        if(thrdworking!=NULL)
            *thrdworking = false;
        if (thrd != NULL) {
            thrd->detach();
            delete thrd;
        }
        blockdel.lock();
        blockdel.unlock();
    }
    virtual void start(CustumVector<CustumVector<Object*>>& gamemap, std::mutex& maplock) {
        if (thrd == NULL) {
            thrd = new std::thread([&]() {this->timexec(gamemap, maplock); });
        }
    }
    void printSymbol() {
        printw("%c", symbol);
    }
    void setxy(int x,int y) {
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

class MovingObject
    :public Object {
protected:
    virtual void execthrd(CustumVector<CustumVector<Object*>>& gamemap, std::mutex& maplock) {
        maplock.lock();
        int nx = xpos + dirtoX(dir);
        int ny = ypos + dirtoY(dir);
        if (nx < 0 || ny < 0 || nx >= gamemap.size() || ny >= gamemap[0].size()) {
            gamemap[xpos][ypos] = NULL;
            maplock.unlock();
            todelete.push_back(this);
            return;
        }
        if (gamemap[nx][ny] == NULL) {
            gamemap[xpos][ypos] = NULL;
            gamemap[nx][ny] = this;
            xpos = nx;
            ypos = ny;
        }
        maplock.unlock();
    }
public:
    MovingObject(int xpos, int ypos,Direction dir, int sleepTime = 1000)
    :Object(xpos,ypos,sleepTime){
        symbol = '.';
        this->dir = dir;
    }
};

template<class Produces>
class GeneratorObject
    :public Object {
protected:
    virtual void execthrd(CustumVector<CustumVector<Object*>>& gamemap, std::mutex& maplock) {
        maplock.lock();
        int nx = xpos + dirtoX(dir);
        int ny = ypos + dirtoY(dir);
        if (gamemap[nx][ny] == NULL) {
            gamemap[nx][ny] = new Produces(nx, ny, dir);
            if (gamemap[nx][ny] != NULL) gamemap[nx][ny]->start(gamemap, maplock);
        }
        maplock.unlock();
    }
public:
    GeneratorObject(int xpos, int ypos, Direction dir,int spawnedsleeptime=1000, int sleepTime = 1000)
        :Object(xpos, ypos, sleepTime) {
        static_assert(std::is_base_of<MovingObject, Produces>::value, "Spawning a non moving object!");
        symbol = 'g';
        this->dir = dir;
        childtime = spawnedsleeptime;
    }
};


class Obracacz
    : public Object {
protected:
    virtual void execthrd(CustumVector<CustumVector<Object*>>& gamemap, std::mutex& maplock) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    maplock.lock();
                    if (gamemap[xpos + i][ypos + j] != NULL) {
                        gamemap[xpos + i][ypos + j]->setdir(dir);
                    }
                    maplock.unlock();
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
};




std::mutex screenlock,maplock;
int scrx = 60, scry = 20;;
int cposx = 0, oldcx = 0;
int cposy = 0, oldcy = 0;
Direction lookingdir; int showdir = 0;
CustumVector<CustumVector<Object*>> gamemap;

void printsupplemental() {
    screenlock.lock();
    mvprintw(scry, 0, "Pozycja wskaznika: %d,%d\n", cposx, cposy);
    switch (lookingdir)
    {
    case NE:
        mvprintw(scry + 1, 0, "Obrot: NE ");
        break;
    case N:
        mvprintw(scry + 1, 0, "Obrot: N  ");
        break;
    case NW:
        mvprintw(scry + 1, 0, "Obrot: NW ");
        break;
    case W:
        mvprintw(scry + 1, 0, "Obrot: W  ");
        break;
    case SW:
        mvprintw(scry + 1, 0, "Obrot: SW ");
        break;
    case S:
        mvprintw(scry + 1, 0, "Obrot: S  ");
        break;
    case SE:
        mvprintw(scry + 1, 0, "Obrot: SE ");
        break;
    case E:
        mvprintw(scry + 1, 0, "Obrot: E  ");
        break;
    default:
        break;
    }
    mvprintw(scry + 1, 9, "; generator robi: ");
    mvprintw(scry + 2, 0, "c-console; r-obracanie; strzalki-poruszanie; o-obracacz; g-generator\n");
    mvprintw(scry + 3, 0, ">");
    screenlock.unlock();
}

void renderscreen() {
    maplock.lock();
    for(int i=0;i<gamemap.size();i++)
        for (int j = 0; j < gamemap[i].size(); j++) {
            screenlock.lock();
            mvprintw(j, i , "");
            if (gamemap[i][j] != NULL)gamemap[i][j]->printSymbol();
            else printw(" ");
            screenlock.unlock();
        }
    maplock.unlock();
}

void rendercursor() {
    if (cposy < 0)cposy = 0;
    if (cposy >= scry)cposy = scry - 1;
    if (cposx < 0)cposx = 0;
    if (cposx >= scrx)cposx = scrx - 1;
    oldcy = cposy;
    oldcx = cposx;
    screenlock.lock();
    mvprintw(oldcy , oldcx , "#");
    if (showdir == 0) {
        mvprintw(oldcy+dirtoY(lookingdir), oldcx + dirtoX(lookingdir), "@");
    }
    screenlock.unlock();
    showdir++; if (showdir > 3)showdir = 0;
    printsupplemental();
}

void screenRefresh() {
    while (true)
    {
        Sleep(500);
        renderscreen();
        rendercursor();
        refresh();
    }
}

int main(){
    //getmaxyx(stdscr, scry, scrx);
    gamemap.resize(scrx);
    for (auto& v : gamemap)
        v.resize(scry);
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    std::thread refresh(screenRefresh);
    while (1) {
        renderscreen();
        rendercursor();
        int litera = getch();
        switch (litera)
        {
        case(258)://arr d
            cposy++;
            break;
        case(259)://arr u
            cposy--;
            break;
        case(260)://arr l
            cposx--;
            break;
        case(261)://arr r
            cposx++;
            break;
        case(330)://del
            maplock.lock();
            if (gamemap[cposx][cposy] != NULL) {
                delete gamemap[cposx][cposy];
                gamemap[cposx][cposy] = NULL;
            }
            maplock.unlock();
            break;
        case(99)://c
            maplock.lock();
            if (gamemap[cposx][cposy] == NULL) {
                gamemap[cposx][cposy] = new Object(cposx, cposy);
                gamemap[cposx][cposy]->start(gamemap, maplock);
            }
            maplock.unlock();
            break;
        case(103)://g
            maplock.lock();
            if (gamemap[cposx][cposy] == NULL) {
                gamemap[cposx][cposy] = new GeneratorObject<MovingObject>(cposx, cposy, lookingdir);
                gamemap[cposx][cposy]->start(gamemap, maplock);
            }
            maplock.unlock();
            break;
        case(114):
            lookingdir = nextdir(lookingdir);
            break;
        case(111)://c
            maplock.lock();
            if (gamemap[cposx][cposy] == NULL) {
                gamemap[cposx][cposy] = new Obracacz(cposx, cposy,lookingdir);
                gamemap[cposx][cposy]->start(gamemap, maplock);
            }
            maplock.unlock();
            break;
        default:
            printw("%d                               \n", litera);
            break;
        }
    }
    return 0;
}