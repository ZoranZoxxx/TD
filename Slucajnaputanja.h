#ifndef SLUCAJNAPUTANJA_H
#define SLUCAJNAPUTANJA_H

#include <time.h>
#include <cstdlib>
#include <QDebug>
#include <vector>

class SlucajnaPutanja {
private:
    int duzina;
    int visina;
    int prvaX;
    int prvaY;
    int poslednjaX;
    int poslednjaY;
    int minimalnaDuzinaPuta;
    char** matrica;
    bool kraj;
    int brojac;
    int duzinaPuta;

    struct Tacka{
        int x;
        int y;
    };

public:
    std::vector<Tacka> niz;

    SlucajnaPutanja(int duz, int vis, int prX, int prY, int poX, int poY, int mDP);
    ~SlucajnaPutanja();
    int zauzeto(int x, int y);
    bool validno(int x, int y);
    bool obidji(int x, int y);
};

#endif // SLUCAJNAPUTANJA_H
