/* ------------------------------------------------------------------------------------------------
    A program fordításához (és futtatásához) SDL 1.2.14 függvénykönyvtár szükséges,
    illetve C++11 kompatibilis fordító.

    ( SDL 1.2.14 letöltő link: https://infoc.eet.bme.hu/sdl_telepito/SDL-1.2.14-infoc-1601.zip )

    A tesztben bemutatott algoritmusok sorban:
    -Selection sort
    -Insertion sort
    -Quick sort
    -Shell sort
    -std::sort
    -std::stable_sort

    Egy algoritmus végeztével az ablakban való kattintással haladhatunk tovább a következőre.

    Ha a program futása közben az ablakból kikattintunk, akkor előfordulhat, hogy utána az animációkat nem látjuk végig.

    Készítette: Csikós-Nagy Ákos
    2017        BME-VIK
------------------------------------------------------------------------------------------------ */

#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "sortingdraw.hpp"
#include "sortingalgs.hpp"

/*
    Egy függvény ami egy egér kattintásra vár (vagy az ablak X-ére való kattintásra :D).
    Ha a rendező algoritmusok futása alatt kattintuk azt is megjegyzi, és
    amikor ide érkezik akkor rögtön tovább megy.
*/
void waitForClick(SDL_Event& ev) {
    bool quit = false;

    while (!quit) {
        SDL_WaitEvent(&ev);
        switch (ev.type) {
            case SDL_MOUSEBUTTONDOWN:
                quit = true;
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Event ev;
    std::shared_ptr<SDL_Surface> screen;

    /* SDL inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen.reset(SDL_SetVideoMode(1000, 700, 0, SDL_ANYFORMAT)); // 1000x700-as ablak. Ez kifér minden 800x600-asnál nagyobb felbontású monitoron.
    if (!(screen.get())) {
        std::cout << "Nem sikerult megnyitni az ablakot!" << std::endl;
        exit(1);
    }
    SDL_WM_SetCaption("Sorting Visualized", "Sorting Visualized");

    srand (time(NULL)); // Random generátor setup

    /*
        Egy DrawableList inicializálása 125 db int-tel, amin kipróbálhatjuk az algoritmusokat.
    */
    DrawableList<int> teszt(screen);
    for (int i = 0; i < 125; ++i) {
        int tmp = rand() % 700 + 1;
        Drawable<int> tmpd(i, 8, tmp, tmp, screen);
        teszt.add(tmpd);
    }

    /*
        Selection sort (kiválasztásos rendezés?) kipróbálása
    */
    teszt.drawAll();
    waitForClick(ev);
    SelectionSort(teszt);
    teszt.drawAll();
    waitForClick(ev);

    /*
        Insertion sort (beszúrásos rendezés?) kipróbálása
    */
    teszt.shuffle();
    waitForClick(ev);
    InsertionSort(teszt);
    teszt.drawAll();
    waitForClick(ev);

    /*
        Kicseréljük az adatokat a DrawableList-ben.
        Mostantól 500 int lesz benne, mert gyorsabb algoritmusok következnek.
    */
    teszt.clear();
    for (int i = 0; i < 500; ++i) {
        int tmp = rand() % 700 + 1;
        Drawable<int> tmpd(i, 2, tmp, tmp, screen);
        teszt.add(tmpd);
    }

    /*
        Quick sort (gyorsrendezés?) kipróbálása
    */
    teszt.drawAll();
    waitForClick(ev);
    QuickSort(teszt);
    teszt.drawAll();
    waitForClick(ev);

    /*
        Shell sort (kagyló rendezés??? inkább feladom a magyarra fordítást) kipróbálása
    */
    teszt.shuffle();
    waitForClick(ev);
    ShellSort(teszt);
    teszt.drawAll();
    waitForClick(ev);

    /*
        std::sort kipróbálása
    */
    teszt.shuffle();
    waitForClick(ev);
    StdSort(teszt);
    teszt.drawAll();
    waitForClick(ev);

    /*
        std::stable_sort kipróbálása
    */
    teszt.shuffle();
    waitForClick(ev);
    StdStableSort(teszt);
    teszt.drawAll();
    waitForClick(ev);

    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}
