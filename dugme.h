#ifndef DUGME
#define DUGME

#include <QPushButton>
#include <QTimer>
#include <QBitmap>

class Dugme: public QPushButton
{
    Q_OBJECT
public:
    Dugme(QPixmap slika, int x, int y, QPushButton * parent = 0);

};


#endif // DUGME

