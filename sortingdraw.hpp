#ifndef SORTINGDRAW_HPP_INCLUDED
#define SORTINGDRAW_HPP_INCLUDED

#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

/*
    Egy osztály amiben eltárolhatunk egy kirajzolandó oszlopot.
*/
template <typename T>
class Drawable final {
    T data; // Eltárolt adat
    unsigned int bottomleft_X; // Az oszlop bal alsó sarkának X koordinátája
    unsigned int topright_Y; // Az oszlop jobb felsõ sarkának Y koordinátája
    unsigned int column_width; // Az oszlop szélessége

    std::shared_ptr<SDL_Surface> screen; // SDL_Surface amire rajzolunk

public:

    Drawable(); // Alapértelmezett konstruktor
    Drawable(size_t number, unsigned int width, unsigned int value, T dat, std::shared_ptr<SDL_Surface> surface); // Paraméteres konstruktor

    T getData() const; // data getter

    bool operator<(Drawable& d);
    bool operator>(Drawable& d);
    Drawable& operator=(Drawable d);
    void draw(); // Kirajzoljuk az oszlopot
};

/*
    Alapértelmezett konstruktor, ami nem csinál semmit.
*/
template <typename T>
Drawable<T>::Drawable() {
}

/*
    Paraméteres konstruktor, ami a megadott paraméterek alapján kiszámolja, és feltölti az adattagokat.
*/
template <typename T>
Drawable<T>::Drawable(size_t number, unsigned int width, unsigned int value, T dat, std::shared_ptr<SDL_Surface> surface) {
    column_width = width;
    data = dat;
    bottomleft_X = number * column_width;
    topright_Y = 699 - value;
    screen = surface;
}

template <typename T>
T Drawable<T>::getData() const {
    return data;
}

/*
    Megnézzük, hogy két Drawable között melyikben nagyobb a tárolt adat.
    Emellett pirosra színezzük a vizsgált oszlopokat, majd vissza a régire.
*/
template <typename T>
bool Drawable<T>::operator<(Drawable<T>& d) {
    boxRGBA(screen.get(), bottomleft_X+1, 698, bottomleft_X+column_width-1, topright_Y+1, 255, 0, 0, 255);
    boxRGBA(screen.get(), d.bottomleft_X+1, 698, d.bottomleft_X+d.column_width-1, d.topright_Y+1, 255, 0, 0, 255);
    SDL_Flip(screen.get());
    //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    draw();
    d.draw();
    return data < d.data;
}

/*
    Megnézzük, hogy két Drawable között melyikben nagyobb a tárolt adat.
    Emellett pirosra színezzük a vizsgált oszlopokat, majd vissza a régire.
*/
template <typename T>
bool Drawable<T>::operator>(Drawable<T>& d) {
    boxRGBA(screen.get(), bottomleft_X+1, 698, bottomleft_X+column_width-1, topright_Y+1, 255, 0, 0, 255);
    boxRGBA(screen.get(), d.bottomleft_X+1, 698, d.bottomleft_X+d.column_width-1, d.topright_Y+1, 255, 0, 0, 255);
    SDL_Flip(screen.get());
    //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    draw();
    d.draw();
    return data > d.data;
}

/*
    Értékadó operátor, ami csak a data és topright_Y adattagokat adja értékül.
    Az összes többi adattag maradhat változatlanul.
    Ezután ki is rajzolja a megváltozott oszlopot.
*/
template <typename T>
Drawable<T>& Drawable<T>::operator=(Drawable<T> d) {
    data = d.data;
    topright_Y = d.topright_Y;
    draw();
    SDL_Flip(screen.get());
    return *this;
}

/*
    Kirajzoljuk az oszlopot.
    Először letöröljük azt ami eddig ott volt, aztán megrajzoljuk a fehér kitöltött téglalapot,
    majd megrajzoljuk feketével a keretet is.
*/
template <typename T>
void Drawable<T>::draw() {
    boxRGBA(screen.get(), bottomleft_X, 699, bottomleft_X+column_width, 0, 0, 0, 0, 255);
    boxRGBA(screen.get(), bottomleft_X, 699, bottomleft_X+column_width, topright_Y, 255, 255, 255, 255);
    rectangleRGBA(screen.get(), bottomleft_X, 699, bottomleft_X+column_width, topright_Y, 0, 0, 0, 255);
}

// --------------------------------------------------------------------------------------------------------------------

/*
    Egy osztály amiben Drawable objektumokat tárolunk.
*/
template <typename T>
class DrawableList final {
    std::vector<Drawable<T>> datas = {}; // Az eltárolt Drawable objektumok.

    std::shared_ptr<SDL_Surface> screen; // SDL_Surface rajzolunk.

public:
    DrawableList(std::shared_ptr<SDL_Surface> surface); // Konstruktor
    void add(Drawable<T>& data); // Hozzáadhatunk Drawable-t
    void clear(); // Törölhetjük az összes Drawable-t
    void drawAll() const; // Kirajzolhatjuk az eltárolt Drawable-öket
    size_t size() const; // Megmondja hány Drawable-t tárolunk
    Drawable<T>& operator[](int index); // Indexelő operátor
    void shuffle(); // Összekeveri véletlenszerűen a Drawable-öket
    auto begin() -> decltype(datas.begin()); // Eleje iterátor
    auto end() -> decltype(datas.end()); // Vége iterátor
};

/*
    Konstruktor, csak az SDL_Surface-t adjuk meg neki.
*/
template <typename T>
DrawableList<T>::DrawableList(std::shared_ptr<SDL_Surface> surface) : screen{surface} {}

/*
    Felvesszük a megadott Drawable objektumot a vector-ba.
*/
template <typename T>
void DrawableList<T>::add(Drawable<T>& data){
    datas.push_back(data);
}

/*
    Kiürítjük a vector-t.
*/
template <typename T>
void DrawableList<T>::clear(){
    datas.clear();
}

/*
    Kirajzoljuk az összes eltárolt Drawable-t.
*/
template <typename T>
void DrawableList<T>::drawAll() const{
    for (auto data : datas) {
        data.draw();
    }
    SDL_Flip(screen.get());
}

/*
    Visszatérünk a Drawable-ük darabszámával.
*/
template <typename T>
size_t DrawableList<T>::size() const {
    return datas.size();
}

/*
    Egyszerű indexelő operátor
*/
template <typename T>
Drawable<T>& DrawableList<T>::operator[](int index) {
    return datas[index];
}

/*
    Összekeverjük véletlenszerűen a Drawable-öket.
*/
template <typename T>
void DrawableList<T>::shuffle(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(datas.begin(), datas.end(), g);
}

/*
    Kezdő iterátor
*/
template <typename T>
auto DrawableList<T>::begin() -> decltype(datas.begin()) {
    return datas.begin();
}

/*
    Vége iterátor
*/
template <typename T>
auto DrawableList<T>::end() -> decltype(datas.end()) {
    return datas.end();
}

#endif // SORTINGDRAW_HPP_INCLUDED
