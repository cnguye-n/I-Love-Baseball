/**************************************************************************
*
*   AUTHORS         : Christine Nguyen, Jeremy Sabino, Kenneth Tiet,
*                     & Jennifer Yau
*   PROJECT         : I LOVE BASEBALL
*   CLASS           : CS 8A
*   SECTION         : MW(9:45-11:10AM), TR(9:45-11:50)
*   DUE DATE        : 6/4/2020
*
**************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickItem>
#include <QQuickView>
#include "linkedlist.h"
#include "stadium.h"
#include "souvenir.h"
#include "container.h"
#include "graph.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*******************************
    ** CONSTRUCTOR & DESTRUCTOR **
    ******************************/
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /***************
    ** MUTATORS  **
    ***************/

    void on_clearMap_clicked();
    void addMarkers(std::string teams = "all");
    void addSingleMarker(std::string stadium, double latitude, double longitude);
    void addAllEdges(std::string color = "black");
    void addSingleEdge(std::string stadium1, std::string stadium2);
    void removeMapItems();
    void readFiles();
    void addNamesToDestinationPickList();
    void setUpSouvenirList();
    void setUpAdminStuff();
    bool checkPassword();
    Stadium* get_stadium_by_name(string name);

    void on_addEdges_clicked();

    void on_addMarkers_clicked();

    void on_stadiumListDropDown_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_addStadiumToTrip_clicked();

    void on_clearDestinationList_clicked();

    void on_letsTravel_clicked();

    void on_displayMajorLeagueTrip_clicked();

    void on_displayNationalLeagueTrip_clicked();

    void on_displayAmericanLeagueTrip_clicked();

    void on_purchaseButton_clicked();

    void on_modifyTeamList_currentTextChanged(const QString &arg1);

    void on_modifyButton_clicked();

    void on_adminAddBox_clicked();

    void on_randomButton_clicked();

    void on_modifySouvButton_clicked();

    void on_addSouvButton_clicked();

    void on_deleteSouvButton_clicked();

    void on_distanceButton_clicked();

    void on_safecoButton_clicked();

private:

    /*******************************
    ** PRIVATE ATTRIBUTES       **
    ******************************/

    Ui::MainWindow *ui;
    // Linked list of all stadiums sorted by A-Z
    LinkedList<Stadium*> listAZ;

    // Linked list of all stadiums sorted by team name
    LinkedList<Stadium*> listTeam;

    // Linked list of national stadiums
    LinkedList<Stadium*> listNational;

    // Linked list of american stadiums
    LinkedList<Stadium*> listAmerican;

    // Linked list of grass stadiums
    LinkedList<Stadium*> listGrass;

    // List sorted by date opening
    LinkedList<Stadium*> listDate;

    // Linked list of stadiums user wants to visit
    LinkedList<Stadium*> pickYourOwn;

    // list of the old stadiums
    LinkedList<Stadium*> listOG;

    // Linked list of souvenirs
    container<souvenir*> souvenirs;

    // Table header
    QStringList souvenirHeader;

    // graph of stadiums
    Graph map;
};

#endif // MAINWINDOW_H

/*****************************************************************
 * MainWindow Class
 * ______________________________________________________________
 *  The MainWindow Class manages the widgets of the main window.
 *  In this case, it consists of all the widgets and functions
 *  needed for the Linked List GUI to work properly.
 ****************************************************************/

/*******************************
** CONSTRUCTOR & DESTRUCTOR **
******************************/

/****************************************************************
* explicit MainWindow(QWidget *parent = nullptr);
*   Constructor; Initialize class attributes
*   Parameters: QWidget *parent
*   Return: none
***************************************************************/

/****************************************************************
* ~MainWindow();
*   Destructor; deallocates memory
*   Parameters: None
*   Return: none
***************************************************************/

/***************
** MUTATORS  **
***************/

/****************************************************************
* void readFiles()
*   Mutator: Call read in programs to store stadiums in linked lists
 *  & container respectively
*   Parameters: None
*   Return: none
***************************************************************/

/****************************************************************
* void addNamesToDestinationPickList()
*   Mutator: Adds names to chooseDestinationsList widget
*   Parameters: None
*   Return: none
***************************************************************/

/****************************************************************
* void setUpSouvenirList()
*   Mutator: Sets up shop in the application - purchases, item list
*   Parameters: None
*   Return: none
***************************************************************/

/****************************************************************
* void setUpAdminStuff()
*   Mutator: Sets up admin drop down lists in admin tab
*   Parameters: None
*   Return: none
***************************************************************/

/****************************************************************
* void addMarkers(string type)
*   Mutator:
*   This method adds all stadium location markers onto the MapView,
*   unless a type of stadium is specified - "national", "american",
*   or "grass".
*   Reads in data from corresponding txt file, in which new
*   stadium location info could be saved.
*   Parameters: type (string)
*   Return: none
***************************************************************/

/****************************************************************
* void addAllEdges(string color)
*   Mutator:
*   This method adds all edges/lines onto MapView.
*   Parameters: color (string)
*   Return: none
***************************************************************/

/****************************************************************
* void removeMapItems()
*   Mutator:
*   This method removes all items from the MapView.
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_stadiumListDropDown_currentTextChanged(const QString &arg1)
*   Mutator:
*   This method displays the corresponding lists of Stadiums.
*   Calls read in programs from readinprograms.cpp to read from txt file
*   and displays stadium list in listwidget
*   Parameters: arg1 (QString)
*   Return: none
***************************************************************/

/****************************************************************
* void on_addStadiumToTrip_clicked()
*   Mutator:
*   This method adds a stadium to the build-your-own-trip
*   linked list
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_clearDestinationList_clicked()
*   Mutator:
*   Clears pickYourOwn linked list and also the destinationList QListWidget
*   linked list
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_letsTravel_clicked()
*   Mutator:
*   Calculates custom path and displays results
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void addSingleEdge()
*   Mutator:
*   Draws a single edge given vertices
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void addSingleMarker()
*   Mutator:
*   Draws a single marker on map given name of stadium and coordinates
*   Parameters: stadium (string), latitude(double), longitude(double)
*   Return: none
***************************************************************/

/****************************************************************
* void on_displayMajorLeagueTrip_clicked()
*   Mutator:
*   Calculates shortest path for all major league trip + draws path
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_displayNationalLeagueTrip_clicked()
*   Mutator:
*   Calculates shortest path for all national league trip + draws path
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_displayAmericanLeagueTrip_clicked()
*   Mutator:
*   Calculates shortest path for all american league trip + draws path
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_purchaseButton_clicked()
*   Mutator:
*   Adds quantity purchased of selected item and updates total
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_modifyTeamList_currentTextChanged()
*   Mutator:
*   Displays currently selected stadium information in adminStadiumInfo
*   box
*   Parameters: QString(arg1)
*   Return: none
***************************************************************/

/****************************************************************
* void on_modifyButton_clicked()
*   Mutator:
*   Modifies stadium information given valid input & password
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_adminAddBox_clicked()
*   Mutator:
*   Modifies team/stadium information given valid input & password
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_randomButton_clicked()
*   Mutator:
*   Retrieves and displays a random stadium on screen + info
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_modifySouvButton_clicked()
*   Mutator:
*   Modifies souvenir info given valid input and password
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_addSouvButton_clicked()
*   Mutator:
*   Adds souvenir given valid input and password
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_deleteSouvButton_clicked()
*   Mutator:
*   Deletes souvenir given valid password
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* void on_distanceButton_clicked()
*   Mutator:
*   Finds shortest distance between two stadiums and displays info
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* Stadium* get_stadium_by_name(string name)
*   Mutator:
*   Returns stadium object when passed in stadium name
*   Parameters: name (string)
*   Return: Stadium
***************************************************************/
