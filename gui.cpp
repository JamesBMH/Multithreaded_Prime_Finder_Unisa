//13413120 JBM HHERTZOG Question 4
#include "gui.h"
#include "primefinder.h"
#include <QLabel>
#include <QSpinBox>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QThread>
#include <QDebug>

Gui::Gui(QWidget *parent)
    : QWidget(parent),
    startLabel{new QLabel("Start number")},
    endLabel{new QLabel("End number")},
    threadLabel{new QLabel("Number of threads")},
    startSpinBox{new QSpinBox},
    endSpinBox{new QSpinBox},
    threadSpinBox{new QSpinBox},
    threadOneResults{new QLabel("Thread 1 results")},
    threadTwoResults{new QLabel("Thread 2 results")},
    threadThreeResults{new QLabel("Thread 3 results")},
    threadFourResults{new QLabel("Thread 4 results")},
    startButton{new QPushButton("Start")},
    threadOneList{new QListWidget},
    threadTwoList{new QListWidget},
    threadThreeList{new QListWidget},
    threadFourList{new QListWidget}
{
    threadOne.setObjectName("threadOne");
    threadTwo.setObjectName("threadTwo");
    threadThree.setObjectName("threadThree");
    threadFour.setObjectName("threadFour");

    firstFinder.moveToThread(&threadOne);
    secondFinder.moveToThread(&threadTwo);
    thirdFinder.moveToThread(&threadThree);
    fourthFinder.moveToThread(&threadFour);

    finderList.append(&firstFinder);
    finderList.append(&secondFinder);
    finderList.append(&thirdFinder);
    finderList.append(&fourthFinder);

    threadList.append(&threadOne);
    threadList.append(&threadTwo);
    threadList.append(&threadThree);
    threadList.append(&threadFour);

    listWidgetList.append(threadOneList);
    listWidgetList.append(threadTwoList);
    listWidgetList.append(threadThreeList);
    listWidgetList.append(threadFourList);

    startSpinBox->setRange(0, 10000);
    endSpinBox->setRange(1, 10000);
    threadSpinBox->setRange(1, 4);

    setup();

    //Connections
    connect(startButton, &QPushButton::clicked, this, &Gui::start);

    connect(&threadOne, &QThread::started, &firstFinder, &PrimeFinder::run);
    connect(&threadTwo, &QThread::started, &secondFinder, &PrimeFinder::run);
    connect(&threadThree, &QThread::started, &thirdFinder, &PrimeFinder::run);
    connect(&threadFour, &QThread::started, &fourthFinder, &PrimeFinder::run);

    connect(&firstFinder, &PrimeFinder::doneCalculating, this, &Gui::firstPrimes);
    connect(&secondFinder, &PrimeFinder::doneCalculating, this, &Gui::secondPrimes);
    connect(&thirdFinder, &PrimeFinder::doneCalculating, this, &Gui::thirdPrimes);
    connect(&fourthFinder, &PrimeFinder::doneCalculating, this, &Gui::fourthPrimes);

    connect(&firstFinder, &PrimeFinder::primesFinished, this, &Gui::terminateOne);
    connect(&secondFinder, &PrimeFinder::primesFinished, this, &Gui::terminateTwo);
    connect(&thirdFinder, &PrimeFinder::primesFinished, this, &Gui::terminateThree);
    connect(&fourthFinder, &PrimeFinder::primesFinished, this, &Gui::terminateFour);
}

Gui::~Gui()
{
    threadOne.terminate();
    threadTwo.terminate();
    threadThree.terminate();
    threadFour.terminate();
}

void Gui::start()
{
    //Clears list widgets
    threadOneList->clear();
    threadTwoList->clear();
    threadThreeList->clear();
    threadFourList->clear();

    //Gets values from Widgets
    int startNum = startSpinBox->value();
    int endNum = endSpinBox->value();
    int threadNum = threadSpinBox->value();
    int total = endNum - startNum;
    int split = total/threadNum;

    //Splits values between PrimeFinders
    for(int i=0; i < (threadNum-1); i++){
        finderList[i]->setStart(startNum);
        finderList[i]->setEnd(startNum+split);
        startNum = startNum + split + 1;
    }
    finderList[threadNum-1]->setStart(startNum);
    finderList[threadNum-1]->setEnd(endNum);

    //Starts threads
    for(int i=0; i < threadNum; i++){
        threadList[i]->start();
    }
}

void Gui::setup()
{
    QHBoxLayout *startLayout{new QHBoxLayout};
    startLayout->addWidget(startLabel);
    startLayout->addWidget(startSpinBox);

    QHBoxLayout *endLayout{new QHBoxLayout};
    endLayout->addWidget(endLabel);
    endLayout->addWidget(endSpinBox);

    QHBoxLayout *threadLayout{new QHBoxLayout};
    threadLayout->addWidget(threadLabel);
    threadLayout->addWidget(threadSpinBox);

    QVBoxLayout *spinBoxLayout{new QVBoxLayout};
    spinBoxLayout->addLayout(startLayout);
    spinBoxLayout->addLayout(endLayout);
    spinBoxLayout->addLayout(threadLayout);

    QHBoxLayout *buttonLayout{new QHBoxLayout};
    buttonLayout->addLayout(spinBoxLayout);
    buttonLayout->addSpacing(110);
    buttonLayout->addWidget(startButton);
    buttonLayout->addSpacing(110);

    QVBoxLayout *threadOneLayout{new QVBoxLayout};
    threadOneLayout->addWidget(threadOneResults);
    threadOneLayout->addWidget(threadOneList);

    QVBoxLayout *threadTwoLayout{new QVBoxLayout};
    threadTwoLayout->addWidget(threadTwoResults);
    threadTwoLayout->addWidget(threadTwoList);

    QVBoxLayout *threadThreeLayout{new QVBoxLayout};
    threadThreeLayout->addWidget(threadThreeResults);
    threadThreeLayout->addWidget(threadThreeList);

    QVBoxLayout *threadFourLayout{new QVBoxLayout};
    threadFourLayout->addWidget(threadFourResults);
    threadFourLayout->addWidget(threadFourList);

    QHBoxLayout *listLayout{new QHBoxLayout};
    listLayout->addLayout(threadOneLayout);
    listLayout->addLayout(threadTwoLayout);
    listLayout->addLayout(threadThreeLayout);
    listLayout->addLayout(threadFourLayout);

    QVBoxLayout *layout{new QVBoxLayout};
    layout->addLayout(buttonLayout);
    layout->addSpacing(25);
    layout->addLayout(listLayout);

    this->setLayout(layout);

    this->setMinimumHeight(500);
}


void Gui::firstPrimes(int newPrime)
{
    listWidgetList[0]->addItem(QString::number(newPrime));
}

void Gui::secondPrimes(int newPrime)
{
    listWidgetList[1]->addItem(QString::number(newPrime));
}

void Gui::thirdPrimes(int newPrime)
{
    listWidgetList[2]->addItem(QString::number(newPrime));
}

void Gui::fourthPrimes(int newPrime)
{
    listWidgetList[3]->addItem(QString::number(newPrime));
}

void Gui::terminateOne()
{
    threadOne.terminate();
}

void Gui::terminateTwo()
{
    threadTwo.terminate();
}

void Gui::terminateThree()
{
    threadThree.terminate();
}

void Gui::terminateFour()
{
    threadFour.terminate();
}
