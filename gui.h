//13413120 JBM HHERTZOG Question 4
#ifndef GUI_H
#define GUI_H

#include "primefinder.h"
#include "qthread.h"
#include <QWidget>

//Forward declarations
class QLabel;
class QSpinBox;
class QPushButton;
class QListWidget;
class QThread;
class PrimeFinder;

class Gui : public QWidget
{
    Q_OBJECT

public:
    //Constructor
    //Moves PrimeFinders to threads
    //Set thread names, this is more for testing purposes
    //Adds the threads, PrimeFinders, and list widgets to lists for easy
    //access during execution
    //Sets up connections
    Gui(QWidget *parent = nullptr);
    //Destructor
    //The destructor terminates the threads if they are not already terminated
    ~Gui();
    //Is called when the button is clicked
    //Clears the ListWidgets
    //Splits values appropriately between PrimeFinders
    //Starts appropriate threads
    void start();

private slots:
    //Sets up the Gui
    void setup();
    //Cross thread communication of data
    //Receives a prime from firstFinder and adds it to the first list widget
    void firstPrimes(int newPrime);
    //Receives a prime from secondFinder and adds it to the second list widget
    void secondPrimes(int newPrime);
    //Receives a prime from thirdFinder and adds it to the third list widget
    void thirdPrimes(int newPrime);
    //Receives a prime from fourthFinder and adds it to the fourth list widget
    void fourthPrimes(int newPrime);
    //Terminates the first thread
    void terminateOne();
    //Terminates the second thread
    void terminateTwo();
    //Terminates the third thread
    void terminateThree();
    //Terminates the fourth thread
    void terminateFour();

private:
    //Gui widgets
    QLabel *startLabel;
    QLabel *endLabel;
    QLabel *threadLabel;
    QLabel *threadOneResults;
    QLabel *threadTwoResults;
    QLabel *threadThreeResults;
    QLabel *threadFourResults;
    QSpinBox *startSpinBox;
    QSpinBox *endSpinBox;
    QSpinBox *threadSpinBox;
    QPushButton *startButton;
    QListWidget *threadOneList;
    QListWidget *threadTwoList;
    QListWidget *threadThreeList;
    QListWidget *threadFourList;

    //Threads
    QThread threadOne;
    QThread threadTwo;
    QThread threadThree;
    QThread threadFour;

    //PrimeFinders
    PrimeFinder firstFinder;
    PrimeFinder secondFinder;
    PrimeFinder thirdFinder;
    PrimeFinder fourthFinder;

    //Lists
    QList<PrimeFinder*> finderList;
    QList<QThread*> threadList;
    QList<QListWidget*> listWidgetList;
};
#endif // GUI_H
