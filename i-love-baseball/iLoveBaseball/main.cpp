/**************************************************
 * Author     : Jennifer Yau, Jeremy Sabino, Christine Nguyen, Kenneth Tiet
 * Assignment : I Love Baseball
 * Class      : CS8
 * Section    : MW 9:45am - 10:50 am
 *              TR 9:45am - 10:10 am
 * Due Date   : June 4, 2020
 * *************************************************/
#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
