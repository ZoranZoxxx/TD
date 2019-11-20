#include "Poeni.h"
#include <QFont>
#include "Igra.h"

extern Igra* igra;

Poeni::Poeni(QGraphicsItem *parent,QString resurs):QGraphicsTextItem(parent){
    poeni = 0;
    zlato = 5;
    zivotBaze = 10;

    if(resurs==QString("Poeni"))
    {

        setPlainText(" " + resurs + QString(": ") + QString::number(poeni));
        setDefaultTextColor("#663300");
        setFont(QFont("times",14,QFont::Bold));

    }

    if(resurs==QString("Zlato"))
    {
        setPlainText(" " + resurs + QString(": ") + QString::number(zlato));
        setDefaultTextColor("#663300");
        setFont(QFont("times",14,QFont::Bold));
    }

    if(resurs==QString("ZivotBaze"))
    {
        setPlainText(" " + resurs + QString(": ") + QString::number(zivotBaze));
        setDefaultTextColor("#663300");
        setFont(QFont("times",14,QFont::Bold));
    }

    if(resurs==QString("Poruka"))
    {
        poruka = QString("");
        setPlainText(poruka);
        setDefaultTextColor("#663300");
        setFont(QFont("times",14,QFont::Bold));
    }

    if(resurs==QString("Nivo"))
    {
        QString porukaNivo = QString(" Nivo: " + QString::number(igra->nivo));
        setPlainText(porukaNivo);
        setDefaultTextColor("#663300");
        setFont(QFont("times",14,QFont::Bold));
    }
}

void Poeni::povecajPoene(){
    poeni++;
    setPlainText(" " + QString("Poeni: ") + QString::number(poeni));
    setDefaultTextColor("#663300");
    setFont(QFont("times",14,QFont::Bold));

}

void Poeni::povecajZlato(int z){//m
    zlato+=z;//ms
    setPlainText(" " + QString("Zlato: ") + QString::number(zlato));
    setDefaultTextColor("#663300");
    setFont(QFont("times",14,QFont::Bold));

}

void Poeni::smanjiZlato(int s){
    zlato-=s;
    setPlainText(" " + QString("Zlato: ") + QString::number(zlato));
    setDefaultTextColor("#663300");
    setFont(QFont("times",14,QFont::Bold));
}

void Poeni::smanjiZivotBaze(){
    zivotBaze--;
    setPlainText(" " + QString("Zivot Baze: ") + QString::number(zivotBaze));
    setDefaultTextColor("#663300");
    setFont(QFont("times",14,QFont::Bold));

}

void Poeni::novaPoruka(QString p){
    poruka = p;
    setPlainText(" " + poruka);
    setDefaultTextColor("#663300");
    setFont(QFont("times",14,QFont::Bold));

}

void Poeni::izbrisiPoruku()
{

    poruka = QString("");
    setPlainText(poruka);
    setDefaultTextColor("#663300");
    setFont(QFont("times",14,QFont::Bold));
}

void Poeni::povecajNivo()
{
    QString porukaNivo = QString(" Nivo: " + QString::number(igra->nivo));
    setPlainText(porukaNivo);
    setDefaultTextColor("#663300");
    setFont(QFont("times",14,QFont::Bold));
}

int Poeni::getZlato()
{
    return zlato;
}

int Poeni::getPoeni()
{
    return poeni;
}

int Poeni::getZivotBaze()
{
    return zivotBaze;
}
