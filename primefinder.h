//13413120 JBM HHERTZOG Question 4
#ifndef PRIMEFINDER_H
#define PRIMEFINDER_H

#include <QObject>

class PrimeFinder : public QObject
{
    Q_OBJECT
public:
    //Constructor
    explicit PrimeFinder(QObject *parent = nullptr);
    //Setters
    void setStart(int newStart);
    void setEnd(int newEnd);

signals:
    //Is emitted when a prime is calculated and is sent to a GUI slot
    void doneCalculating(int prime);
    //Is emitted when all primes for this PrimeFinder is calculated
    //so the GUI can terminate the thread
    void primesFinished();

public slots:
    //Is run when the thread is started
    void run();

private:
    //Number boundries for calculating primes
    int start;
    int end;
};

#endif // PRIMEFINDER_H
