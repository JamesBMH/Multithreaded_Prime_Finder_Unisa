//13413120 JBM HHERTZOG Question 4
#include "primefinder.h"
#include <QThread>
#include <QDebug>

PrimeFinder::PrimeFinder(QObject *parent)
    : QObject{parent}
{}

void PrimeFinder::run()
{
    bool prime{true};

    for (int current = start; current <= end; current++){
        if (!(current == 0 || current == 1)){
            //Zero and one are not prime numbers so we start at two
            for (int i = 2; i < current; i++){
                if (current % i == 0) prime=false;
            }
            if(prime) emit doneCalculating(current);
            prime = true;
        }
    }
    emit primesFinished();
}

void PrimeFinder::setEnd(int newEnd)
{
    end = newEnd;
}

void PrimeFinder::setStart(int newStart)
{
    start = newStart;
}
