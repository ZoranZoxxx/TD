#include "Slucajnaputanja.h"

SlucajnaPutanja::SlucajnaPutanja(int duz, int vis, int prX, int prY, int poX, int poY, int mDP) {
    duzina = duz;
    visina = vis;
    prvaX = prX;
    prvaY = prY;
    poslednjaX = poX;
    poslednjaY = poY;
    minimalnaDuzinaPuta = mDP;

    kraj = false;
    brojac = 0;

    while(true) {
        duzinaPuta = 0;

        matrica = new char*[duzina];
        for(int i = 0; i < duzina; i++) {
            matrica[i] = new char[visina];
            for(int j = 0; j < visina; j++) {
                matrica[i][j] = '*';
            }
        }

        Tacka prva;
        prva.x = prvaX;
        prva.y = prvaY;
        matrica[prvaX][prvaY] = '#';
        niz.push_back(prva);

        if(obidji(prva.x, prva.y) && duzinaPuta > minimalnaDuzinaPuta) {
            for(int j = 0; j < visina; j++) {
                for(int i = 0; i < duzina; i++) {
                    //cout << matrica[i][j];
                }
                //cout << endl;
            }
        }

        for(int i = 0; i < duzina; i++) {
            delete matrica[i];
        }
        delete matrica;

        if(kraj && duzinaPuta > minimalnaDuzinaPuta)
            break;
        else {
            kraj = false;
            niz.erase(niz.begin(), niz.end());
        }
    }
}

SlucajnaPutanja::~SlucajnaPutanja() {

}

int SlucajnaPutanja::zauzeto(int x, int y) {
    if(x < 0 || y < 0 || x >= duzina || y >= visina) {
        return 0;
    }
    if(matrica[x][y] != '*')
        return 1;
    return 0;
}

bool SlucajnaPutanja::validno(int x, int y) {
    if(x < 0 || y < 0 || x >= duzina || y >= visina || (x == prvaX && y == prvaY))
        return false;

    if(zauzeto(x - 1, y) + zauzeto(x, y - 1) + zauzeto(x + 1, y) + zauzeto(x, y + 1) == 1) {
        return true;
    }
    return false;
}

bool SlucajnaPutanja::obidji(int x, int y) {
    if(x == poslednjaX && y == poslednjaY)
        kraj = true;
    if(kraj)
        return true;
    brojac += rand() % 10000;
    srand(time(NULL) + brojac);

    Tacka pomocniNiz[4];
    int broj = 0;
    Tacka tacka;

    if(validno(x - 1, y)) {
        tacka.x = x - 1;
        tacka.y = y;
        pomocniNiz[broj++] = tacka;
    }
    if(validno(x, y - 1)) {
        tacka.x = x;
        tacka.y = y - 1;
        pomocniNiz[broj++] = tacka;
    }
    if(validno(x + 1, y)) {
        tacka.x = x + 1;
        tacka.y = y;
        pomocniNiz[broj++] = tacka;
    }
    if(validno(x, y + 1)) {
        tacka.x = x;
        tacka.y = y + 1;
        pomocniNiz[broj++] = tacka;
    }

    if(broj > 0) {
        int slucajanBroj = rand() % broj;
        matrica[pomocniNiz[slucajanBroj].x][pomocniNiz[slucajanBroj].y] = '#';
        Tacka pomocna;
        pomocna.x = pomocniNiz[slucajanBroj].x;
        pomocna.y = pomocniNiz[slucajanBroj].y;
        niz.push_back(pomocna);

        duzinaPuta++;
        if(obidji(pomocniNiz[slucajanBroj].x, pomocniNiz[slucajanBroj].y))
            return true;
    }
    return false;
}
