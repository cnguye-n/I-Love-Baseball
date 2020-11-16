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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readinprograms.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include "linkedlist.h"
#include "stadium.h"
#include "add_all_prices.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <string>
using namespace std;

/*****************************************************************
 *
 *  CONSTRUCTOR MainWindow(QWidget *parent): Class MainWindow
 *________________________________________________________________
 *  This is the constructor for MainWindow widget - initializes
 *  and sets up the window
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     parent (QWidget) - parent widget
 *  POST-CONDITIONS
 *     None, but sets up window
 *****************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // OUT - set up items for viewing lists
    ui->stadiumListDropDown->addItem("Select a List to View");
    ui->stadiumListDropDown->addItem("Major League Stadiums (A-Z)");
    ui->stadiumListDropDown->addItem("Major League Stadiums (Team A-Z)");
    ui->stadiumListDropDown->addItem("Major League Stadiums (by Date Opened)");
    ui->stadiumListDropDown->addItem("Grass Surface Stadiums");
    ui->stadiumListDropDown->addItem("American League Stadiums");
    ui->stadiumListDropDown->addItem("National League Stadiums");

    // hide test buttons
    ui->addEdges->hide();
    ui->addMarkers->hide();
    ui->clearMap->hide();
    ui->singleEdge->hide();
    ui->redEdges->hide();

    // OUT - add items to grass input box
    ui->grassBox->addItem("No");
    ui->grassBox->addItem("Yes");

    // PROC - read in files and store stadiums in their respective linked lists
    readFiles();

    // PROC - add stadiums to choose destination list & find distance
    addNamesToDestinationPickList();

    // PROC - add items to souvenir table
    setUpSouvenirList();

    // PROC - set up defaults in admin tab
    ui->capacityBox->setMaximum(100000);
    ui->capacityBox->setValue(40000);
    ui->americanToggle->setChecked(true);

    // PROC - set up admin drop down lists
    setUpAdminStuff();

}

/*****************************************************************
 *
 *  DESTRUCTOR ~MainWindow: Class MainWindow
 *________________________________________________________________
 *  This is the destructor for MainWindow class - deallocates memory
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     None, deallocates memory
 *****************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/*****************************************************************
 *
 *  METHOD readFiles(): Class MainWindow
 *________________________________________________________________
 *  Call read in programs to store stadiums in linked lists
 *  & container respectively
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     None, but sets up sorted lists
 *****************************************************************/
void MainWindow::readFiles()
{
    // call read in programs to store stadiums in linked lists
    // & container respectively
    listAZ = Stadiums();                        // stadium AZ list
    listOG = Stadiums();
    listTeam = StadiumsByTeamName();            // original AZ list
    listNational = StadiumsByNationalTeams();   // national teams list
    listAmerican = StadiumsByAmericanTeams();   // american teams list
    listGrass = GrassStadiumsByTeamName();      // grass teams list
    listDate = StadiumsByDate();                // stadiums by date open
    souvenirs = Souvenirs();                    // souvenir list
}

/*****************************************************************
 *
 *  METHOD addNamesToDestinationPickList(): Class MainWindow
 *________________________________________________________________
 *  Adds names to chooseDestinationsList widget
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     None, but sets up chooseDestinationsList widget
 *****************************************************************/
void MainWindow::addNamesToDestinationPickList()
{
    // OUT - adds names to chooseDestinationsList widget
    for (int i = 0; i < listOG.length(); i++)
    {
        ui->chooseDestinationsList->addItem(
               QString::fromStdString(listOG.access(i)->get_stadium()));
        ui->findDistA->addItem(
               QString::fromStdString(listOG.access(i)->get_stadium()));
        ui->findDistB->addItem(
               QString::fromStdString(listOG.access(i)->get_stadium()));
    }
}

/*****************************************************************
 *
 *  METHOD setUpSouvenirList(): Class MainWindow
 *________________________________________________________________
 *  Sets up shop in the application - purchases, item list
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     None, but sets up/updates the shop in the application
 *****************************************************************/
void MainWindow::setUpSouvenirList()
{
    // OUT - clear table and list
    ui->souvenirsTable->clear();
    ui->makePurchaseList->clear();

    // PROCESSING - set rows and column for table
    ui->souvenirsTable->setRowCount(souvenirs.size());
    ui->souvenirsTable->setColumnCount(3);

    // PROCESSING - inserting column headers
    souvenirHeader.clear();
    souvenirHeader<<"Souvenir"<<"Price"<<"Quantity Purchased";
    ui->souvenirsTable->setHorizontalHeaderLabels(souvenirHeader);
    ui->souvenirsTable->setColumnWidth(0, 200);
    ui->souvenirsTable->horizontalHeader()->setStretchLastSection(true);

    // add souvenirs to table
    // add souvenirs to purchase list
    for (int i = 0; i < souvenirs.size(); i++)
    {
        ui->souvenirsTable->setItem(
           i,0, new QTableWidgetItem(
              QString::fromStdString(souvenirs.at(i)->return_name())));
        ui->souvenirsTable->setItem(
           i,1, new QTableWidgetItem(
              QString::number(souvenirs.at(i)->return_price(), 'f', 2)));
        ui->souvenirsTable->setItem(
           i,2, new QTableWidgetItem(
              QString::number(souvenirs.at(i)->return_quantity())));
        ui->makePurchaseList->addItem(
              QString::fromStdString(souvenirs.at(i)->return_name()));
    }
    ui->totalPurchasePriceLabel->setText("$" +
          QString::number(add_all_prices(souvenirs), 'f', 2));
}

/*****************************************************************
 *
 *  METHOD setUpAdminStuff(): Class MainWindow
 *________________________________________________________________
 *  Sets up admin drop down lists in admin tab
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     None, sets up admin drop down lists in admin tab
 *****************************************************************/
void MainWindow::setUpAdminStuff()
{
    // OUT - clear drop down lists
    ui->modifyTeamList->clear();
    ui->modifySouvenirList->clear();

    // OUT - loop thru lists and add teams/items
    for (int i = 0; i < listTeam.length(); i++)
    {
        ui->modifyTeamList->addItem(
                    QString::fromStdString(listTeam.access(i)->get_team()));
    }

    for (int i = 0; i < souvenirs.size(); i++)
    {
        ui->modifySouvenirList->addItem(
                    QString::fromStdString(souvenirs.at(i)->return_name()));
    }
}

/*****************************************************************
 *
 *  METHOD addMarkers: Class MainWindow
 *________________________________________________________________
 *  This method adds all stadium location markers onto the MapView,
 *  unless a type of stadium is specified - "national", "american",
 *  or "grass".
 *  Reads in data from corresponding txt file, in which new
 *  stadium location info could be saved.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     marker_coord_XXXXX.txt: stores all stadium location marker info
 *                            including stadium name, latitude and
 *                            longitude
 *  POST-CONDITIONS
 *     Adds markers onto Map -- invokes addMarker function found in
 *                              testQML.qml
 *****************************************************************/
void MainWindow::addMarkers(string type) // IN - string of which teams
                                          // to add, default "all"
{
    // set MapView object as "target"
    QObject *target =
            qobject_cast<QObject*>(ui->quickWidget->rootObject());

    LinkedList<Stadium*> l;

    // use appropriate stadium lists for each type
    if (type == "national")
    {
        l = listNational;
    }
    else if (type == "american")
    {
        l = listAmerican;
    }
    else if (type == "grass")
    {
        l = listGrass;
    }
    else {
        l = listAZ;
    }

    // function to call in QML
    QString functionName = "addMarker";

    for (int i = 0; i < l.length(); i++)
    {
        // call QML function in testQML.qml
        QMetaObject::invokeMethod(target, functionName.toUtf8().constData(),
                     Qt::AutoConnection,
                     Q_ARG(QVariant, QString::fromStdString(l.access(i)->get_stadium())),
                     Q_ARG(QVariant, l.access(i)->get_lat()),
                     Q_ARG(QVariant, l.access(i)->get_long()));
    }

}

/*****************************************************************
 *
 *  METHOD addAllEdges: Class MainWindow
 *________________________________________________________________
 *  This method adds all edges/lines onto MapView.
 *  Mostly a test function, will modify to accomodate project.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     color (string) : can modify color of the lines by passing in
 *                      a basic color like "red" or "gray"
 *  POST-CONDITIONS
 *     Adds edges onto Map -- invokes addLine function found in
 *                              testQML.qml
 *****************************************************************/
void MainWindow::addAllEdges(std::string color) // IN - color of edges
{
    // PROCESSING - adds all edges into display
    //              edges will be black by default
    /******************************************************************
     * MUST USE THESE CODES WHEN ADDING EDGES TO MAP
     * THERE ARE A TOTAL OF 47 POSSIBLE EDGES
     * -----------------------------------------------
     * safeco_ATT
     *      Safeco Field to AT&T Park / O.co Coliseum
     * safeco_rogers
     *      Safeco Field to Rogers Center
     * safeco_target
     *      Safeco Field to Target Field
     * ATT_angel
     *      AT&T Park / O.co Coliseum to Angel Stadium / Dodger Stadium
     * ATT_chase
     *      AT&T Park / O.co Coliseum to Chase Field
     * angel_petco
     *      Angel Stadium / Dodger Stadium to PETCO Park
     * angel_target
     *      Angel Stadium / Dodger Stadium to Target Field
     * petco_chase
     *      PETCO Park to Chase Field
     * petco_coors
     *      PETCO Park to Coors Field
     * chase_coors
     *      Chase Field to Coors Field
     * chase_globe
     *      Chase Field to Globe Park AKA Rangers Ballpark
     * chase_maid
     *      Chase Field to Minute Maid Park
     * coors_globe
     *      Coors Field to Globe Park AKA Rangers Ballpark
     * coors_kauffman
     *      Coors Field to Kauffman Stadium
     * target_miller
     *      Target Field to Miller Park
     * target_busch
     *      Target Field to Busch Stadium
     * kauffman_globe
     *      Kauffman Stadium to Globe Park AKA Rangers Ballpark
     * kauffman_wrigley
     *      Kauffman Stadium to Wrigley Field / US Cellular Field
     * globe_turner
     *      Globe Park AKA Rangers Ballpark to Turner Field
     * globe_maid
     *      Globe Park AKA Rangers Ballpark to Minute Maid Park
     * miller_rogers
     *      Miller Park to Rogers Center
     * miller_wrigley
     *      Miller Park to Wrigley Field / US Cellular Field
     * wrigley_comerica
     *      Wrigley Field / US Cellular Field to Comerica Park
     * wrigley_great
     *      Wrigley Field / US Cellular Field to Great American Ballpark
     * busch_great
     *      Busch Stadium to Great American Ballpark
     * busch_maid
     *      Busch Stadium to Minute Maid Park
     * rogers_fenway
     *      Rogers Center to Fenway Park
     * rogers_pnc
     *      Rogers Center to PNC Park
     * rogers_comerica
     *      Rogers Center to Comerica Park
     * comerica_progress
     *      Comerica Park to Progressive Field
     * progress_pnc
     *      Progressive Field to PNC Park
     * progress_great
     *      Progressive Field to Great American Ballpark
     * great_turner
     *      Great American Ballpark to Turner Field
     * great_tropicana
     *      Great American Ballpark to Tropicana Field
     * great_pnc
     *      Great American Ballpark to PNC Park
     * pnc_citi
     *      PNC Park to Citi Field / Yankee Stadium
     * pnc_camden
     *      PNC Park to Camden Yards / Nationals Park
     * turner_camden
     *      Turner Field to Camden Yards / Nationals Park
     * turner_marlins
     *      Turner Field to Marlins Park
     * fenway_citi
     *      Fenway Park to Citi Field / Yankee Stadium
     * fenway_marlins
     *      Fenway Park to Marlins Park
     * citi_citizens
     *      Citi Field / Yankee Stadium to Citizens Bank Park
     * citizens_camden
     *      Citizens Bank Park to Camden Yards / Nationals Park
     * camden_marlins
     *      Camden Yards / Nationals Park to Marlins Park
     * tropicana_marlins
     *      Tropicana Field to Marlins Park
     * maid_tropicana
     *      Minute Maid Park to Tropicana Field
     * maid_marlins
     *      Minute Maid Park to Marlins Park
     *
     * ***************************************************************/

    // set MapView object as target
    QObject *target =
            qobject_cast<QObject*>(ui->quickWidget->rootObject());

    // PROC - add all codes to vector
    Vector<std::string> v;
    v.push_back("safeco_ATT");
    v.push_back("safeco_rogers");
    v.push_back("safeco_target");
    v.push_back("ATT_angel");
    v.push_back("ATT_chase");
    v.push_back("angel_petco");
    v.push_back("angel_target");
    v.push_back("petco_chase");
    v.push_back("petco_coors");
    v.push_back("chase_coors");
    // -- 10
    v.push_back("chase_globe");
    v.push_back("chase_maid");
    v.push_back("coors_globe");
    v.push_back("coors_kauffman");
    v.push_back("target_miller");
    v.push_back("target_busch");
    v.push_back("kauffman_globe");
    v.push_back("kauffman_wrigley");
    v.push_back("globe_turner");
    v.push_back("globe_maid");
    // -- 20
    v.push_back("miller_rogers");
    v.push_back("miller_wrigley");
    v.push_back("wrigley_comerica");
    v.push_back("wrigley_great");
    v.push_back("busch_great");
    v.push_back("busch_maid");
    v.push_back("rogers_fenway");
    v.push_back("rogers_pnc");
    v.push_back("rogers_comerica");
    v.push_back("comerica_progress");
    // -- 30
    v.push_back("progress_pnc");
    v.push_back("progress_great");
    v.push_back("great_turner");
    v.push_back("great_tropicana");
    v.push_back("great_pnc");
    v.push_back("pnc_citi");
    v.push_back("pnc_camden");
    v.push_back("turner_camden");
    v.push_back("turner_marlins");
    v.push_back("fenway_citi");
    // -- 40
    v.push_back("fenway_marlins");
    v.push_back("citi_citizens");
    v.push_back("citizens_camden");
    v.push_back("camden_marlins");
    v.push_back("tropicana_marlins");
    v.push_back("maid_tropicana");
    v.push_back("maid_marlins");
    // -- TOTAL 47 EDGES

    // PROC - go thru vector to add all edges
    // we are calling the addLine function found in testQML.qml
    QString addLine = "addLine";

    for (int i = 0; i < v.size(); i++)
    {
        QMetaObject::invokeMethod(target, addLine.toUtf8().constData(),
                     Qt::AutoConnection,
                     Q_ARG(QVariant, QString::fromStdString(v.at(i))),
                     Q_ARG(QVariant, QString::fromStdString(color)));
    }

}

/*****************************************************************
 *
 *  METHOD removeMapItems: Class MainWindow
 *________________________________________________________________
 *  This method removes all items from the MapView.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Removes all items from MapView object.
 *****************************************************************/
void MainWindow::removeMapItems()
{
    // PROCESSING - calls clearAll function in testQML
    //              to remove all objects on map
    QObject *target =
            qobject_cast<QObject*>(ui->quickWidget->rootObject());

    QString clear = "clearAll";
    QMetaObject::invokeMethod(target, clear.toUtf8().constData(),
                              Qt::AutoConnection);
}

/*****************************************************************
 *
 *  METHOD on_stadiumListDropDown_currentTextChanged: Class MainWindow
 *________________________________________________________________
 *  This method displays the corresponding lists of Stadiums.
 *  Calls read in programs from readinprograms.cpp to read from txt file
 *  and displays stadium list in listwidget
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Stadium txt files
 *  POST-CONDITIONS
 *     Display stadium lists
 *****************************************************************/
void MainWindow::on_stadiumListDropDown_currentTextChanged(const QString &arg1)
                                              // IN - current text
{
    // create vector
    LinkedList<Stadium*> l;

    // clear display box and map
    ui->stadiumList->clear();
    removeMapItems();

    // Calls corresponding read in function which returns a linked list
    // Read linkedlist and display contents onto list widget
    // Add corresponding map markers
    if (arg1 == "Major League Stadiums (A-Z)")
    {
        l = listAZ;

        addMarkers();
    }
    else if (arg1 == "Major League Stadiums (Team A-Z)")
    {
        l = listTeam;

        addMarkers();
    }
    else if (arg1 == "American League Stadiums")
    {
        l = listAmerican;

        addMarkers("american");

    }
    else if (arg1 == "National League Stadiums")
    {
        l = listNational;

        addMarkers("national");

    }
    else if (arg1 == "Grass Surface Stadiums")
    {

        l = listGrass;

        addMarkers("grass");

    }
    else if (arg1 == "Major League Stadiums (by Date Opened)")
    {
        l = listDate;

        addMarkers();

    }

    // OUT - add info to stadium list
    for (int i = 0; i < l.length(); i++)
    {
        ui->stadiumList->addItem(QString::fromStdString(l.access(i)->get_stadium()));
        ui->stadiumList->addItem(QString::fromStdString(l.access(i)->get_team()));
        ui->stadiumList->addItem(QString::fromStdString(l.access(i)->get_address()));
        ui->stadiumList->addItem(QString::fromStdString(
                                     l.access(i)->get_city() + ", " +
                                     l.access(i)->get_state() + " " +
                                     l.access(i)->get_zip()));
        ui->stadiumList->addItem(QString::fromStdString(l.access(i)->get_phone()));
        ui->stadiumList->addItem("Opened - "
             + QString::fromStdString(l.access(i)->get_date().getMonthAlpha())
             + " "
             + QString::number(l.access(i)->get_date().getDay())
             + ", " + QString::number(l.access(i)->get_date().getYear()));
        ui->stadiumList->addItem("Capacity - " + QString::number(l.access(i)->get_capacity()));
        ui->stadiumList->addItem("");
    }

}

/*****************************************************************
 *
 *  METHOD on_addStadiumToTrip_clicked(): Class MainWindow
 *________________________________________________________________
 *  This method adds a stadium to the build-your-own-trip
 *  linked list
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI set up
 *  POST-CONDITIONS
 *     Adds stadium to build your own trip list if it's not already
 *     in it
 *****************************************************************/
void MainWindow::on_addStadiumToTrip_clicked()
{
    // PROC - adds selected stadium name from chooseDestinations widget
    // to destinationsList widget
    // also adds stadium to pickYourOwn linked list
    ui->planATripErrorLabel->clear();

    bool alreadyInList;

    alreadyInList = false;

    // PROC - check to see if stadium already in list, error if so
    for (int i = 0; i < pickYourOwn.length(); i++)
    {
        // checks if already in list
        // displays msg if so
        if (pickYourOwn.access(i)->get_stadium() == listOG.access(
                    ui->chooseDestinationsList->currentRow())->get_stadium())
        {
            ui->planATripErrorLabel->setText("Error: Already in list.");
            alreadyInList = true;
            break;
        }
    }

    if(ui->destinationList->count() >= 8)
    {
        ui->planATripErrorLabel->setText("Error: You may add a max of "
                                         "8 stadiums.");
        return;
    }

    // PROC - can't add to destination list if already in list, but will
    // add if it isnt
    if (!alreadyInList)
    {
        ui->destinationList->addItem(
                    QString::fromStdString(
                        listOG.access(
                            ui->chooseDestinationsList->currentRow())->get_stadium()));
        pickYourOwn.push_back(listOG.access(
                                  ui->chooseDestinationsList->currentRow()));
    }
}

/*****************************************************************
 *
 *  METHOD on_clearDestinationList_clicked(): Class MainWindow
 *________________________________________________________________
 *  Clears pickYourOwn linked list and also the destinationList QListWidget
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI set up
 *  POST-CONDITIONS
 *     Clears pickYourOwn linked list and also the destinationList QListWidget
 *****************************************************************/
void MainWindow::on_clearDestinationList_clicked()
{
    // PROC - clear map, error labels, destinationList and pickYourOwn
    ui->planATripErrorLabel->clear();
    ui->destinationList->clear();
    removeMapItems();
    pickYourOwn.clear();
}

/*****************************************************************
 *
 *  METHOD on_letsTravel_clicked(): Class MainWindow
 *________________________________________________________________
 *  Calculates custom path and displays results
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI set up
 *  POST-CONDITIONS
 *     Calculates custom path and displays results
 *****************************************************************/
void MainWindow::on_letsTravel_clicked()
{
    // PROC - remove map items and clear itinerary box
    removeMapItems();
    ui->itinerary->clear();

    // CONTINGENCY
    // if less than 2 in destinations list, error bc cant find path
    if(ui->destinationList->count() < 2)
    {
        ui->planATripErrorLabel->setText("Error. You must add at least"
                                         " 2 stadiums.");
        return;
    }

    // function to calculate shortest dist for selected stadiums
    // return list of stadiums visited in order

    vector<string> vDream;

    for (int i = 0; i < pickYourOwn.length(); i++)
    {
        vDream.push_back(pickYourOwn.access(i)->get_stadium());
    }

    vector<string> path;
    int min_cost;
    string edge, stadiumName;

    min_cost = map.dream(vDream);
    path  = map.getDream();

    // OUT - draw edges and markers
    for (size_t i = 0; i < path.size() - 1; i++)
        addSingleEdge(path[i], path[i+1]);
    for (size_t i = 0; i < path.size(); i++)
        addSingleMarker(path[i], get_stadium_by_name(path[i])->get_lat(),
                        get_stadium_by_name(path[i])->get_long());

    // OUT - add info to itinerary box
    ui->itinerary->addItem("START");
    ui->itinerary->addItem("");
    for (size_t i = 0; i < path.size(); i++)
        ui->itinerary->addItem(QString::fromStdString(path[i]));
    ui->itinerary->addItem("");
    ui->itinerary->addItem("END");
    ui->itinerary->addItem("TOTAL STADIUMS VISITED (NON-UNIQUE): "
                           + QString::number(path.size()));
    ui->itinerary->addItem("TOTAL DISTANCE TRAVELED: " + QString::number(min_cost));
}

/*****************************************************************
 *
 *  METHOD addSingleEdge(): Class MainWindow
 *________________________________________________________________
 *  Draws a single edge given vertices
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI set up
 *  POST-CONDITIONS
 *     Adds a single edge on map given the vertices names
 *****************************************************************/
void MainWindow::addSingleEdge(string stadium1, // IN - first stadium
                               string stadium2) // IN - second stadium
{
    string edge;
    // possible 48 edges ... MORE?

    // PROC - all possibilities for edges and their codes in QML
    if (
            (stadium1 == "SafeCo Field" &&
            (stadium2 == "At&T Park" || stadium2 == "O.co Coliseum"))
        ||
            ((stadium1 == "At&T Park" || stadium1 == "O.co Coliseum")
             && stadium2 == "SafeCo Field"))
    {
        edge = "safeco_ATT";
    }
    else if((stadium1 == "SafeCo Field" && stadium2 == "Rogers Centre")
            || (stadium1 == "Rogers Centre" && stadium2 == "SafeCo Field"))
    {
        edge = "safeco_rogers";
    }
    else if((stadium1 == "SafeCo Field" && stadium2 == "Target Field")
            || (stadium1 == "Target Field" && stadium2 == "SafeCo Field"))
    {
        edge = "safeco_target";
    }
    else if (
            ((stadium1 == "Angels Stadium of Anaheim"
              || stadium1 == "Dodger Stadium")
            && (stadium2 == "At&T Park" || stadium2 == "O.co Coliseum"))
        ||
            ((stadium1 == "At&T Park" || stadium1 == "O.co Coliseum")
             && (stadium2 == "Angels Stadium of Anaheim"
              || stadium2 == "Dodger Stadium")))
    {
        edge = "ATT_angel";
    }
    else if (
            (stadium1 == "Chase Field" &&
            (stadium2 == "At&T Park" || stadium2 == "O.co Coliseum"))
        ||
            ((stadium1 == "At&T Park" || stadium1 == "O.co Coliseum")
             && stadium2 == "Chase Field"))
    {
        edge = "ATT_chase";
    }
    else if (
            (stadium1 == "Petco Park" &&
            (stadium2 == "Angels Stadium of Anaheim"
            || stadium2 == "Dodger Stadium"))
        ||
            ((stadium1 == "Dodger Stadium"
             || stadium1 == "Angels Stadium of Anaheim")
             && stadium2 == "Petco Park"))
    {
        edge = "angel_petco";
    }
    else if (
            (stadium1 == "Target Field" &&
            (stadium2 == "Angels Stadium of Anaheim"
            || stadium2 == "Dodger Stadium"))
        ||
            ((stadium1 == "Dodger Stadium"
             || stadium1 == "Angels Stadium of Anaheim")
             && stadium2 == "Target Field"))
    {
        edge = "angel_target";
    }
    else if((stadium1 == "Petco Park" && stadium2 == "Chase Field")
            || (stadium1 == "Chase Field" && stadium2 == "Petco Park"))
    {
        edge = "petco_chase";
    }
    else if((stadium1 == "Petco Park" && stadium2 == "Coors Field")
            || (stadium1 == "Coors Field" && stadium2 == "Petco Park"))
    {
        edge = "petco_coors";
    }
    else if((stadium1 == "Chase Field" && stadium2 == "Coors Field")
            || (stadium1 == "Coors Field" && stadium2 == "Chase Field"))
    {
        edge = "chase_coors";
    }
    // -- 10 edges
    else if((stadium1 == "Globe Life Park in Arlington"
        && stadium2 == "Chase Field")
            || (stadium1 == "Chase Field"
         && stadium2 == "Globe Life Park in Arlington"))
    {
        edge = "chase_globe";
    }
    else if((stadium1 == "Minute Maid Park" && stadium2 == "Chase Field")
            || (stadium1 == "Chase Field" && stadium2 == "Minute Maid Park"))
    {
        edge = "chase_maid";
    }
    else if((stadium1 == "Globe Life Park in Arlington"
        && stadium2 == "Coors Field")
            || (stadium1 == "Coors Field"
         && stadium2 == "Globe Life Park in Arlington"))
    {
        edge = "coors_globe";
    }
    else if((stadium1 == "Kauffman Stadium" && stadium2 == "Coors Field")
            || (stadium1 == "Coors Field" && stadium2 == "Kauffman Stadium"))
    {
        edge = "coors_kauffman";
    }
    else if((stadium1 == "Miller Park" && stadium2 == "Target Field")
            || (stadium1 == "Target Field" && stadium2 == "Miller Park"))
    {
        edge = "target_miller";
    }
    else if((stadium1 == "Busch Stadium" && stadium2 == "Target Field")
            || (stadium1 == "Target Field" && stadium2 == "Busch Stadium"))
    {
        edge = "target_busch";
    }
    else if((stadium1 == "Kauffman Stadium"
        && stadium2 == "Globe Life Park in Arlington")
            ||(stadium1 == "Globe Life Park in Arlington"
         && stadium2 == "Kauffman Stadium"))
    {
        edge = "kauffman_globe";
    }
    else if (
            (stadium1 == "Kauffman Stadium" &&
            (stadium2 == "Wrigley Field" || stadium2 == "US Cellular Field"))
        ||
            ((stadium1 == "Wrigley Field" || stadium1 == "US Cellular Field")
             && stadium2 == "Kauffman Stadium"))
    {
        edge = "kauffman_wrigley";
    }
    else if((stadium1== "Turner Field"
        && stadium2 == "Globe Life Park in Arlington")
            ||
            (stadium1 == "Globe Life Park in Arlington"
         && stadium2 == "Turner Field"))
    {
        edge = "globe_turner";
    }
    else if((stadium1 == "Minute Maid Park"
        && stadium2 == "Globe Life Park in Arlington")
            ||
            (stadium1 == "Globe Life Park in Arlington"
         && stadium2 == "Minute Maid Park"))
    {
        edge = "globe_maid";
    }
    // -- 20 edges
    else if((stadium1 == "Miller Park" && stadium2 == "Rogers Centre")
            || (stadium1 == "Rogers Centre" && stadium2 == "Miller Park"))
    {
        edge = "miller_rogers";
    }
    else if (
            (stadium1 == "Miller Park" &&
            (stadium2 == "Wrigley Field" || stadium2 == "US Cellular Field"))
        ||
            ((stadium1 == "Wrigley Field" || stadium2 == "US Cellular Field")
             && stadium2 == "Miller Park"))
    {
        edge = "miller_wrigley";
    }
    else if (
            (stadium1 == "Kauffman Stadium" &&
            (stadium2 == "Busch Stadium"))
        ||
            (stadium1 == "Busch Stadium" && stadium2 == "Kauffman Stadium"))
    {
        edge = "kauff_busch";
    }
    else if (
            (stadium1 == "Comerica Park" &&
            (stadium2 == "Wrigley Field" || stadium2 == "US Cellular Field"))
        ||
            ((stadium1 == "Wrigley Field" || stadium1 == "US Cellular Field")
             && stadium2 == "Comerica Park"))
    {
        edge = "wrigley_comerica";
    }
    else if (
            (stadium1 == "Great America Ball Park"
            &&
            (stadium2 == "Wrigley Field" || stadium2 == "US Cellular Field"))
        ||
            ((stadium1 == "Wrigley Field" || stadium1 == "US Cellular Field")
             && stadium2 == "Great America Ball Park"))
    {
        edge = "wrigley_great";
    }
    else if((stadium1 == "Busch Stadium"
        && stadium2 == "Great America Ball Park")
            ||
            (stadium1 == "Great America Ball Park"
         && stadium2== "Busch Stadium"))
    {
        edge = "busch_great";
    }
    else if((stadium1 == "Busch Stadium" && stadium2 == "Minute Maid Park")
            ||
            (stadium1 == "Minute Maid Park" && stadium2 == "Busch Stadium"))
    {
        edge = "busch_maid";
    }
    else if((stadium1 == "Rogers Centre" && stadium2 == "Fenway Park")
            ||
            (stadium1 == "Fenway Park" && stadium2 == "Rogers Centre"))
    {
        edge = "rogers_fenway";
    }
    else if((stadium1 == "Rogers Centre" && stadium2 == "PNC Park")
            ||
            (stadium1 == "PNC Park" && stadium2 == "Rogers Centre"))
    {
        edge = "rogers_pnc";
    }
    else if((stadium1 == "Rogers Centre" && stadium2 == "Comerica Park")
            ||
            (stadium1 == "Comerica Park" && stadium2 == "Rogers Centre"))
    {
        edge = "rogers_comerica";
    }
    else if((stadium1 == "Progressive Field" && stadium2 == "Comerica Park")
            ||
            (stadium1 == "Comerica Park" && stadium2== "Progressive Field"))
    {
        edge = "comerica_progress";
    }
    // -- 30 edges
    else if((stadium1 == "Progressive Field" && stadium2 == "PNC Park")
            ||
            (stadium1 == "PNC Park" && stadium2 == "Progressive Field"))
    {
        edge = "progress_pnc";
    }
    else if((stadium1 == "Progressive Field" && stadium2 == "Great America Ball Park")
            ||
            (stadium1 == "Great America Ball Park" && stadium2 == "Progressive Field"))
    {
        edge = "progress_great";
    }
    else if((stadium1 == "Turner Field" && stadium2 == "Great America Ball Park")
            ||
            (stadium1 == "Great America Ball Park" && stadium2 == "Turner Field"))
    {
        edge = "great_turner";
    }
    else if((stadium1 == "Tropicana Field" && stadium2 == "Great America Ball Park")
            ||
            (stadium1 == "Great America Ball Park" && stadium2 == "Tropicana Field"))
    {
        edge = "great_tropicana";
    }
    else if((stadium1 == "PNC Park" && stadium2 == "Great America Ball Park")
            ||
            (stadium1 == "Great America Ball Park" && stadium2 == "PNC Park"))
    {
        edge = "great_pnc";
    }
    else if (
            (stadium1 == "PNC Park"
            &&
            (stadium2 == "Citi Field" || stadium2 == "Yankee Stadium"))
        ||
            ((stadium1 == "Citi Field" || stadium1 == "Yankee Stadium")
             && stadium2 == "PNC Park"))
    {
        edge = "pnc_citi";
    }
    else if (
            (stadium1 == "PNC Park"
            &&
            (stadium2 == "Oriole Park at Camden Yards" || stadium2 == "Nationals Park"))
        ||
            ((stadium1 == "Oriole Park at Camden Yards" || stadium1 == "Nationals Park")
             && stadium2 == "PNC Park"))
    {
        edge = "pnc_camden";
    }
    else if (
            (stadium1 == "Turner Field"
            &&
            (stadium2 == "Oriole Park at Camden Yards" || stadium2 == "Nationals Park"))
        ||
            ((stadium1 == "Oriole Park at Camden Yards" || stadium1 == "Nationals Park")
             && stadium2 == "Turner Field"))
    {
        edge = "turner_camden";
    }
    else if((stadium1 == "Turner Field"  && stadium2 == "Marlins Park")
            ||
            (stadium1 == "Marlins Park" && stadium2 == "Turner Field"))
    {
        edge = "turner_marlins";
    }
    else if (
            (stadium1 == "Fenway Park"
            &&
            (stadium2 == "Citi Field"|| stadium2 == "Yankee Stadium"))
        ||
            ((stadium1 == "Citi Field" || stadium1 == "Yankee Stadium")
             && stadium2 == "Fenway Park"))
    {
        edge = "fenway_citi";
    }
    // -- 40 edges
    else if((stadium1 == "Fenway Park"
        && stadium2 == "Marlins Park")
            ||
            (stadium1 == "Marlins Park"
         && stadium2 == "Fenway Park"))
    {
        edge = "fenway_marlins";
    }
    else if (
            (stadium1 == "Citizens Bank Park"
            &&
            (stadium2 == "Citi Field" || stadium2 == "Yankee Stadium"))
        ||
            ((stadium1 == "Citi Field" || stadium1 == "Yankee Stadium")
             && stadium2 == "Citizens Bank Park"))
    {
        edge = "citi_citizens";
    }
    else if (
            (stadium1 == "Citizens Bank Park"
            &&
            (stadium2 == "Oriole Park at Camden Yards" || stadium2 == "Nationals Park"))
        ||
            ((stadium1 == "Oriole Park at Camden Yards" || stadium1 == "Nationals Park")
             && stadium2 == "Citizens Bank Park"))
    {
        edge = "citizens_camden";
    }
    else if (
            (stadium1 == "Marlins Park"
            &&
            (stadium2 == "Oriole Park at Camden Yards" || stadium2 == "Nationals Park"))
        ||
            ((stadium1 == "Oriole Park at Camden Yards" || stadium1 == "Nationals Park")
             && stadium2 == "Marlins Park"))
    {
        edge = "camden_marlins";
    }
    else if((stadium1 == "Tropicana Field" && stadium2 == "Marlins Park")
            ||
            (stadium1 == "Marlins Park" && stadium2 == "Tropicana Field"))
    {
        edge = "tropicana_marlins";
    }
    else if((stadium1 == "Tropicana Field" && stadium2 == "Minute Maid Park")
            ||
            (stadium1 == "Minute Maid Park" && stadium2 == "Tropicana Field"))
    {
        edge = "maid_tropicana";
    }
    else if((stadium1 == "Minute Maid Park" && stadium2 == "Marlins Park")
            ||
            (stadium1 == "Marlins Park" && stadium2 == "Minute Maid Park"))
    {
        edge = "maid_marlins";
    }

    // PROC & OUT - invoke QML function to draw, line in RED
    QObject *target =
            qobject_cast<QObject*>(ui->quickWidget->rootObject());
    QString addLine = "addLine";

    QMetaObject::invokeMethod(target, addLine.toUtf8().constData(),
                     Qt::AutoConnection,
                     Q_ARG(QVariant, QString::fromStdString(edge)),
                     Q_ARG(QVariant, QString::fromStdString("red")));
}

/*****************************************************************
 *
 *  METHOD addSingleMarker(): Class MainWindow
 *________________________________________________________________
 *  Draws a single marker on map given name of stadium and coordinates
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI set up
 *  POST-CONDITIONS
 *     Draws a single marker on map given name of stadium and coordinates
 *****************************************************************/
void MainWindow::addSingleMarker(string stadium,  // IN - stadium name
                                 double latitude, // IN - latitude coord
                                 double longitude)// IN - longitude coord
{
    // set MapView object as "target"
    QObject *target =
            qobject_cast<QObject*>(ui->quickWidget->rootObject());

    // function to call in QML
    QString functionName = "addMarker";

    // call QML function in testQML.qml
    QMetaObject::invokeMethod(target, functionName.toUtf8().constData(),
               Qt::AutoConnection,
              Q_ARG(QVariant, QString::fromStdString(stadium)),
              Q_ARG(QVariant, latitude),
              Q_ARG(QVariant, longitude));

}

/*****************************************************************
 *
 *  METHOD on_displayMajorLeagueTrip_clicked(): Class MainWindow
 *________________________________________________________________
 *  Calculates shortest path for all major league trip + draws path
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and graph set up
 *  POST-CONDITIONS
 *     Calculates shortest path for all major league trip + draws path
 *****************************************************************/
void MainWindow::on_displayMajorLeagueTrip_clicked()
{
    // OUT - display map, clear itinerary box
    removeMapItems();
    addMarkers();
    ui->itinerary->clear();

    int d;

    // PROC - get distance of Major League trip, start in At&T Park (CA)
    d = map.major(map.search_index("At&T Park"));

    // PROC - get vector of stadiums visited in path
    vector<string> path = map.getMajor();

    // OUT - draw edges and markers
    for (size_t i = 0; i < path.size() - 1; i++)
        addSingleEdge(path[i], path[i+1]);

    // OUT - add info to itinerary box
    ui->itinerary->addItem("START");
    ui->itinerary->addItem("");
    for (size_t i = 0; i < path.size(); i++)
        ui->itinerary->addItem(QString::fromStdString(path[i]));
    ui->itinerary->addItem("");
    ui->itinerary->addItem("END");
    ui->itinerary->addItem("TOTAL STADIUMS VISITED (NON UNIQUE): "
                           + QString::number(path.size()));
    ui->itinerary->addItem("TOTAL DISTANCE TRAVELED: " + QString::number(d));
}

/*****************************************************************
 *
 *  METHOD on_displayNationalLeagueTrip_clicked(): Class MainWindow
 *________________________________________________________________
 *  Calculates shortest path for all nationl league trip + draws path
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and graph set up
 *  POST-CONDITIONS
 *     Calculates shortest path for all national league trip + draws path
 *****************************************************************/
void MainWindow::on_displayNationalLeagueTrip_clicked()
{
    // OUT - display map, clear itinerary box
    removeMapItems();
    ui->itinerary->clear();

    int d;

    // PROC - get distance of National trip, start in At&T Park (CA)
    d = map.national(map.search_index("At&T Park"));

    // PROC - get vector of stadiums visited in path
    vector<string> path = map.getNational();

    // OUT - draw edges and markers
    for (size_t i = 0; i < path.size() - 1; i++)
        addSingleEdge(path[i], path[i+1]);
    for (size_t i = 0; i < path.size(); i++)
        addSingleMarker(path[i], get_stadium_by_name(path[i])->get_lat(),
                        get_stadium_by_name(path[i])->get_long());

    // OUT - add info to itinerary box
    ui->itinerary->addItem("START");
    ui->itinerary->addItem("");
    for (size_t i = 0; i < path.size(); i++)
        ui->itinerary->addItem(QString::fromStdString(path[i]));
    ui->itinerary->addItem("");
    ui->itinerary->addItem("END");
    ui->itinerary->addItem("TOTAL STADIUMS VISITED (NON UNIQUE): "
                           + QString::number(path.size()));
    ui->itinerary->addItem("TOTAL DISTANCE TRAVELED: " + QString::number(d));
}

/*****************************************************************
 *
 *  METHOD on_displayAmericanLeagueTrip_clicked(): Class MainWindow
 *________________________________________________________________
 *  Calculates shortest path for all american league trip + draws path
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and graph set up
 *  POST-CONDITIONS
 *     Calculates shortest path for all american league trip + draws path
 *****************************************************************/
void MainWindow::on_displayAmericanLeagueTrip_clicked()
{
    // OUT - display map, clear itinerary box
    removeMapItems();
    ui->itinerary->clear();

    int d;

    // PROC - get distance of American trip, start in Angels Stadium (CA)
    d = map.american(map.search_index("Angels Stadium of Anaheim"));

    // PROC - get vector of stadiums visited in path
    vector<string> path = map.getAmerican();

    // OUT - draw edges and markers
    for (size_t i = 0; i < path.size() - 1; i++)
        addSingleEdge(path[i], path[i+1]);
    for (size_t i = 0; i < path.size(); i++)
        addSingleMarker(path[i], get_stadium_by_name(path[i])->get_lat(),
                        get_stadium_by_name(path[i])->get_long());

    // OUT - add info to itinerary box
    ui->itinerary->addItem("START");
    ui->itinerary->addItem("");
    for (size_t i = 0; i < path.size(); i++)
        ui->itinerary->addItem(QString::fromStdString(path[i]));
    ui->itinerary->addItem("");
    ui->itinerary->addItem("END");
    ui->itinerary->addItem("TOTAL STADIUMS VISITED (NON UNIQUE): "
                           + QString::number(path.size()));
    ui->itinerary->addItem("TOTAL DISTANCE TRAVELED: " + QString::number(d));
}

/*****************************************************************
 *
 *  METHOD on_purchaseButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Adds quantity purchased of selected item and updates total
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and souvenirs set up
 *  POST-CONDITIONS
 *     Adds quantity purchased of selected item and updates total
 *****************************************************************/
// when purchase button is clicked
void MainWindow::on_purchaseButton_clicked()
{
    // +1 quantity of selected item
    souvenirs.at(ui->makePurchaseList->currentRow())->add_one();

    // update purchases display
    setUpSouvenirList();
}

/*****************************************************************
 *
 *  METHOD on_modifyTeamList_currentTextChanged(): Class MainWindow
 *________________________________________________________________
 *  Displays currently selected stadium information in adminStadiumInfo
 *  box
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and stadiums set up
 *  POST-CONDITIONS
 *     Displays currently selected stadium information in adminStadiumInfo
 *  box
 *****************************************************************/
void MainWindow::on_modifyTeamList_currentTextChanged(const QString &arg1)
                                         // IN - current text of drop down
{
    // clear prev info
    ui->adminStadiumInfo->clear();

    LinkedList<Stadium*> v = listTeam;
    int index;
    index = ui->modifyTeamList->currentIndex();

    // PROC - grab info
    string grass, american;
    grass = v.access(index)->has_grass() ? "Yes" : "No";
    american = v.access(index)->is_american() ? "American" : "National";

    // OUT - display info on box
    ui->adminStadiumInfo->addItem(
                QString::fromStdString(v.access(index)->get_stadium()));
    ui->adminStadiumInfo->addItem(
                QString::fromStdString(v.access(index)->get_address()));
    ui->adminStadiumInfo->addItem(
                QString::fromStdString(v.access(index)->get_city())
                + ", " + QString::fromStdString(v.access(index)->get_state())
                + " " + QString::fromStdString(v.access(index)->get_zip()));
    ui->adminStadiumInfo->addItem(
                QString::fromStdString(v.access(index)->get_phone()));
    ui->adminStadiumInfo->addItem("Open Date - " +
                QString::number(v.access(index)->get_date().getMonth())
                + "/" +
                QString::number(v.access(index)->get_date().getDay())
                + "/" +
                QString::number(v.access(index)->get_date().getYear()));
    ui->adminStadiumInfo->addItem("Capacity - " +
                QString::number(v.access(index)->get_capacity()));
    ui->adminStadiumInfo->addItem("Grass - " +
                QString::fromStdString(grass));
    ui->adminStadiumInfo->addItem("League - " +
                QString::fromStdString(american));
}

/*****************************************************************
 *
 *  METHOD on_modifyButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Modifies stadium information given valid input & password
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and stadiums set up
 *  POST-CONDITIONS
 *     Modifies stadium information given valid input & password
 *****************************************************************/
void MainWindow::on_modifyButton_clicked()
{
    // clear error labels
    ui->adminPassError->clear();
    ui->adminStadiumError->clear();
    ui->adminSouvError->clear();

    int index, zip;
    long long phoneNum;
    index = ui->modifyTeamList->currentIndex();
    QDate dat = ui->openDateBox->date();
    QString qZip, qPhone;
    bool american, national, grass, canada, ok1, ok2, ok3, ok4;
    string teamName, phoneOG, phone1, phone2, phone3;
    double latitude, longitude;

    // PROC - grab team info that doesnt change
    teamName = listTeam.access(index)->get_team();
    grass = listTeam.access(index)->has_grass();
    american = listTeam.access(index)->is_american();
    national = listTeam.access(index)->is_national();
    canada = ui->canadaBox->isChecked() ? true : false;

    latitude = ui->latitudeBox->text().toDouble(&ok1);
    longitude = ui->longitudeBox->text().toDouble(&ok2);
    phoneNum = ui->phoneBox->text().toLongLong(&ok4);
    phoneOG = ui->phoneBox->text().toUtf8().constData();

    // CONTINGENCY HANDLING

    // PROC - error if any field is empty
    if (ui->stadiumBox->text().isEmpty() ||
        ui->addressBox->text().isEmpty() ||
        ui->cityBox->text().isEmpty() ||
        ui->stateBox->text().isEmpty() ||
        ui->zipBox->text().isEmpty() ||
        ui->latitudeBox->text().isEmpty() ||
        ui->longitudeBox->text().isEmpty() ||
        ui->phoneBox->text().isEmpty())
    {
        ui->adminStadiumError->setText("Error. Please fill out all fields.");
        return;
    }

    // PROC - check if latitude and longitude are doubles
    if (!ok1 || !ok2)
    {
        ui->adminStadiumError->setText("Error. Please enter in a number"
                                       " for latitude and longitude.");
        return;
    }

    // check that phone number is number
    if (!ok4 || phoneOG.length() != 10)
    {
        ui->adminStadiumError->setText("Error. Please enter 10 digit phone"
                                       " number without spaces or special"
                                       " characters.");
        return;
    }
    else {
        phone1 = phoneOG.substr(0,3);
        phone2 = phoneOG.substr(3,3);
        phone3 = phoneOG.substr(6,4);
    }

    // PROC - add  text to certain strings if Canada
    if (canada)
    {
        qZip = "Canada " + ui->zipBox->text();
        qPhone = QString::fromStdString("+1 " + phone1 + "-" + phone2 + "-"
                                        + phone3);
    }
    else
    {
        qPhone = QString::fromStdString("(" + phone1 + ") " + phone2 + "-"
                                        + phone3);
    }

    // PROC - if not canadian address, need number for zip
    if (!canada)
    {
        zip = ui->zipBox->text().toInt(&ok3);

        if (!ok3)
        {
            ui->adminStadiumError->setText("Error. Please enter in a "
                                           "number for zip code.");
            return;
        }
    }

    // PROC - if wrong admin pass, do nothing
    if (!checkPassword())
        return;

    // PROC - create new stadium object
    Stadium* newStadium = new Stadium(ui->stadiumBox->text().toUtf8().constData(),
                       listTeam.access(index)->get_team(),
                       ui->addressBox->text().toUtf8().constData(),
                       qPhone.toUtf8().constData(),
                       Date2(dat.month(), dat.day(), dat.year()),
                       ui->capacityBox->value(),
                       ui->cityBox->text().toUtf8().constData(),
                       ui->stateBox->text().toUtf8().constData(),
                       qZip.toUtf8().constData(),
                       american, national, grass,
                       latitude,
                       longitude);

    // PROCESSING - remove old stadium from lists and reinsert new into
    //              sorted lists

    // list sorted by teams
    listTeam.remove(index);
    listTeam.insert_sorted_team(newStadium);

    // american list sorted by teams
    for (int i = 0; i < listAmerican.length(); i++)
    {
        if (teamName == listAmerican.access(i)->get_team())
        {
            listAmerican.remove(i);
            listAmerican.insert_sorted_team(newStadium);
            break;
        }
    }

    // national list sorted by teams
    for (int i = 0; i < listNational.length(); i++)
    {
        if (teamName == listNational.access(i)->get_team())
        {
            listNational.remove(i);
            listNational.insert_sorted_team(newStadium);
        }
    }

    // list sorted by date opened
    for (int i = 0; i < listDate.length(); i++)
    {
        if (teamName == listDate.access(i)->get_team())
        {
            listDate.remove(i);
            listDate.insert_sorted_date(newStadium);
        }
    }

    // list of stadiums sorted AZ
    for (int i = 0; i < listAZ.length(); i++)
    {
        if (teamName == listAZ.access(i)->get_team())
        {
            listAZ.remove(i);
            listAZ.insert_sorted_stadium(newStadium);
        }
    }

    // list of grass stadiums sorted by team
    for (int i = 0; i < listGrass.length(); i++)
    {
        if (teamName == listGrass.access(i)->get_team())
        {
            listGrass.remove(i);
            listGrass.insert_sorted_team(newStadium);
            break;
        }
    }

    // update stadium info display
    on_modifyTeamList_currentTextChanged(ui->modifyTeamList->currentText());
}

/*****************************************************************
 *
 *  METHOD on_adminAddBox_clicked(): Class MainWindow
 *________________________________________________________________
 *  Modifies team/stadium information given valid input & password
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and stadiums set up
 *  POST-CONDITIONS
 *     Modifies team/stadium information given valid input & password
 *****************************************************************/
void MainWindow::on_adminAddBox_clicked()
{
    // PROC - clear error labels
    ui->adminPassError->clear();
    ui->adminStadiumError->clear();
    ui->adminSouvError->clear();

    QDate dat = ui->openDateBox->date();
    QString qZip, qPhone;
    bool american, national, grass, canada, ok1, ok2, ok3, ok4;
    string phoneOG, phone1, phone2, phone3;
    double latitude, longitude;
    int zip;
    long long phoneNum;

    phoneNum = ui->phoneBox->text().toLongLong(&ok4);
    phoneOG = ui->phoneBox->text().toUtf8().constData();

    // PROC - grab info from boxes
    grass = ui->grassBox->currentText() == "Yes" ? true : false;
    american = ui->americanToggle->isChecked() ? true : false;
    national = !american ? true : false;
    canada = ui->canadaBox->isChecked() ? true : false;

    latitude = ui->latitudeBox->text().toDouble(&ok1);
    longitude = ui->longitudeBox->text().toDouble(&ok2);

    // CONTINGENCY HANDLING

    // PROC - error if any field is empty
    if (ui->stadiumBox->text().isEmpty() ||
        ui->addressBox->text().isEmpty() ||
        ui->cityBox->text().isEmpty() ||
        ui->stateBox->text().isEmpty() ||
        ui->zipBox->text().isEmpty() ||
        ui->latitudeBox->text().isEmpty() ||
        ui->longitudeBox->text().isEmpty() ||
        ui->phoneBox->text().isEmpty() ||
        ui->teamNameBox->text().isEmpty())
    {
        ui->adminStadiumError->setText("Error. Please fill out all fields.");
        return;
    }

    // PROC - check if latitude and longitude are doubles
    if (!ok1 || !ok2)
    {
        ui->adminStadiumError->setText("Error. Please enter in a number"
                                       " for latitude and longitude.");
        return;
    }

    // PROC - check phone is 10 digits and no special char
    if (!ok4 || phoneOG.length() != 10)
    {
        ui->adminStadiumError->setText("Error. Please enter 10 digit phone"
                                       " number without spaces or special"
                                       " characters.");
        return;
    }
    else {
        phone1 = phoneOG.substr(0,3);
        phone2 = phoneOG.substr(3,3);
        phone3 = phoneOG.substr(6,4);
    }

    // PROC - add  text to certain strings if Canada
    // phone number processing
    if (canada)
    {
        qZip = "Canada " + ui->zipBox->text();
        qPhone = QString::fromStdString("+1 " + phone1 + "-" + phone2 + "-"
                                        + phone3);
    }
    else
    {
        qPhone = QString::fromStdString("(" + phone1 + ") " + phone2 + "-"
                                        + phone3);
    }

    // PROC - if not canadian address, need number for zip
    if (!canada)
    {
        zip = ui->zipBox->text().toInt(&ok3);

        if (!ok3)
        {
            ui->adminStadiumError->setText("Error. Please enter in a "
                                           "number for zip code.");
            return;
        }
    }

    // PROC - if wrong admin pass, do nothing
    if (!checkPassword())
        return;

    // PROC - create new stadium object
    Stadium* newStadium = new Stadium(ui->stadiumBox->text().toUtf8().constData(),
                       ui->teamNameBox->text().toUtf8().constData(),
                       ui->addressBox->text().toUtf8().constData(),
                       qPhone.toUtf8().constData(),
                       Date2(dat.month(), dat.day(), dat.year()),
                       ui->capacityBox->value(),
                       ui->cityBox->text().toUtf8().constData(),
                       ui->stateBox->text().toUtf8().constData(),
                       qZip.toUtf8().constData(),
                       american, national, grass,
                       latitude,
                       longitude);

    // PROC - insert into sorted lists
    listTeam.insert_sorted_team(newStadium);
    listAZ.insert_sorted_stadium(newStadium);
    listDate.insert_sorted_date(newStadium);
    if (grass)
        listGrass.insert_sorted_team(newStadium);
    if (american)
        listAmerican.insert_sorted_team(newStadium);
    if (national)
        listNational.insert_sorted_stadium(newStadium);


    // update drop down list with new stadium
    setUpAdminStuff();

}

/*****************************************************************
 *
 *  METHOD on_randomButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Retrieves and displays a random stadium on screen + info
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and stadiums set up
 *  POST-CONDITIONS
 *     Retrieves and displays a random stadium on screen + info
 *****************************************************************/
void MainWindow::on_randomButton_clicked()
{
    // PROC - clear map
    ui->randomDisplay->clear();
    removeMapItems();

    // PROC - get random number based on length of list
    // display data in randomDisplay box
    srand(time(NULL));
    int i = rand() % listAZ.length();

    ui->randomDisplay->addItem(QString::fromStdString(listAZ.access(i)->get_stadium()));
    ui->randomDisplay->addItem(QString::fromStdString(listAZ.access(i)->get_team()));
    ui->randomDisplay->addItem(QString::fromStdString(listAZ.access(i)->get_address()));
    ui->randomDisplay->addItem(QString::fromStdString(
                                     listAZ.access(i)->get_city() + ", " +
                                     listAZ.access(i)->get_state() + " " +
                                     listAZ.access(i)->get_zip()));
    ui->randomDisplay->addItem(QString::fromStdString(listAZ.access(i)->get_phone()));
    ui->randomDisplay->addItem("Opened - "
             + QString::fromStdString(listAZ.access(i)->get_date().getMonthAlpha())
             + " "
             + QString::number(listAZ.access(i)->get_date().getDay())
             + ", " + QString::number(listAZ.access(i)->get_date().getYear()));
    ui->randomDisplay->addItem("Capacity - " + QString::number(listAZ.access(i)->get_capacity()));
    ui->randomDisplay->addItem("");

    // PROC - add marker of location
    addSingleMarker(listAZ.access(i)->get_stadium(),
                        listAZ.access(i)->get_lat(),
                        listAZ.access(i)->get_long());

}

/*****************************************************************
 *
 *  METHOD on_modifySouvButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Modifies souvenir info given valid input and password
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and souvenirs set up
 *  POST-CONDITIONS
 *     Modifies souvenir info given valid input and password
 *****************************************************************/
void MainWindow::on_modifySouvButton_clicked()
{
    // PROC - clear error label
    ui->adminPassError->clear();
    ui->adminStadiumError->clear();
    ui->adminSouvError->clear();

    // CONTINGENCY HANDLING
    // if fields empty, do nothing

    if (ui->souvNameBox->text().isEmpty())
    {
        ui->adminSouvError->setText("Error. Please fill out all fields.");
        return;
    }

    if(ui->souvPriceBox->value() == 0.00)
    {
        ui->adminSouvError->setText("Error. Nothing is free.");
        return;
    }

    // PROC - if wrong admin pass, do nothing
    if (!checkPassword())
        return;

    // grab index of current souvenir
    int index;
    index = ui->modifySouvenirList->currentIndex();

    // change souvenir fields according to input field
    souvenirs.at(index)->set_name(ui->souvNameBox->text().toUtf8().constData());
    souvenirs.at(index)->set_price(ui->souvPriceBox->value());

    // refresh souvenir drop down lists and catalog
    setUpAdminStuff();
    setUpSouvenirList();

}

/*****************************************************************
 *
 *  METHOD on_addSouvButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Adds souvenir given valid input and password
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and souvenirs set up
 *  POST-CONDITIONS
 *     Adds souvenir given valid input and password
 *****************************************************************/
void MainWindow::on_addSouvButton_clicked()
{
    // PROC - clear error labels
    ui->adminPassError->clear();
    ui->adminStadiumError->clear();
    ui->adminSouvError->clear();

    // CONTINGENCY HANDLING
    // if fields empty, do nothing
    if (ui->souvNameBox->text().isEmpty())
    {
        ui->adminSouvError->setText("Error. Please fill out all fields.");
        return;
    }

    if(ui->souvPriceBox->value() == 0.00)
    {
        ui->adminSouvError->setText("Error. Nothing is free.");
        return;
    }

    // PROC - if wrong admin pass, do nothing
    if (!checkPassword())
        return;


    // PROC - create new souvenir
    souvenir* s = new souvenir(ui->souvNameBox->text().toUtf8().constData(),
                               0, ui->souvPriceBox->value());

    // PROC - add to end of list
    souvenirs.attach(s);

    // refresh souvenir drop down lists and catalog
    setUpAdminStuff();
    setUpSouvenirList();
}

/*****************************************************************
 *
 *  METHOD on_deleteSouvButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Deletes souvenir given valid password
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and souvenirs set up
 *  POST-CONDITIONS
 *     Deletes souvenir given valid password
 *****************************************************************/
void MainWindow::on_deleteSouvButton_clicked()
{
    // PROC - clear error labels
    ui->adminPassError->clear();
    ui->adminStadiumError->clear();
    ui->adminSouvError->clear();

    // PROC & OUT - if wrong admin pass, do nothing
    if (!checkPassword())
        return;

    // grab index of current souvenir
    int index;
    index = ui->modifySouvenirList->currentIndex();

    // PROC - remove souvenir from list
    souvenirs.remove(souvenirs.at(index));

    // refresh souvenir drop down lists and catalog
    setUpAdminStuff();
    setUpSouvenirList();
}

/*****************************************************************
 *
 *  METHOD on_distanceButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Finds shortest distance between two stadiums and displays info
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI, graph, stadiums set up
 *  POST-CONDITIONS
 *     Finds shortest distance between two stadiums and displays info
 *****************************************************************/
void MainWindow::on_distanceButton_clicked()
{
    // PROC - remove map items and clear itinerary box
    removeMapItems();
    ui->itinerary->clear();

    int index1, index2, d;
    vector<string> path;

    // index of stadium A in OG list
    index1 = ui->findDistA->currentRow();

    // index of stadium B in OG list
    index2 = ui->findDistB->currentRow();

    // PROC - get distance between stadium A and stadium B
    d = map.stadium_distance(listOG.access(index1)->get_stadium(),
                             listOG.access(index2)->get_stadium());

    // PROC - get vector of stadiums visited in path
    path = map.draw_distance(listOG.access(index1)->get_stadium(),
                             listOG.access(index2)->get_stadium());

    // OUT - draw edges and markers
    for (size_t i = 0; i < path.size() - 1; i++)
        addSingleEdge(path[i], path[i+1]);
    for (size_t i = 0; i < path.size(); i++)
        addSingleMarker(path[i], get_stadium_by_name(path[i])->get_lat(),
                        get_stadium_by_name(path[i])->get_long());

    // OUT - add info to itinerary box
    ui->itinerary->addItem("START");
    ui->itinerary->addItem("");
    for (size_t i = 0; i < path.size(); i++)
        ui->itinerary->addItem(QString::fromStdString(path[i]));
    ui->itinerary->addItem("");
    ui->itinerary->addItem("END");
    ui->itinerary->addItem("TOTAL DISTANCE TRAVELED: " + QString::number(d));
}

/*****************************************************************
 *
 *  METHOD checkPassword(): Class MainWindow
 *________________________________________________________________
 *  Checks if admin password entered is valid
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     GUI set up and password text file
 *  POST-CONDITIONS
 *     Checks if admin password entered is valid, returns true if yes,
 *     false otherwise
 *****************************************************************/
bool MainWindow::checkPassword()
{
    // PROCESSING - open file to save members to
    string pass;
    ifstream read;
    bool success;

    // PROC - read file
    read.open("adminpass.txt");

    if (!read)
        ui->adminPassError->setText("Please set up your password to continue.");

    // grab password
    getline(read, pass);

    // PROC - input text matches password --> SUCCESS
    // else, error
    if (pass == ui->passwordBox->text().toUtf8().constData())
    {
        ui->adminPassError->setText("Success!");
        success = true;
    }
    else {
        ui->adminPassError->setText("Error: Incorrect password.");
        success = false;
    }

    ui->passwordBox->clear();

    read.close();

    // OUT - return true if successful, false otherwise
    return success;
}

/*****************************************************************
 *
 *  METHOD get_stadium_by_name(): Class MainWindow
 *________________________________________________________________
 *  Returns stadium object when passed in stadium name
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     GUI set up and stadiums, linked lists
 *  POST-CONDITIONS
 *     Returns stadium object when passed in stadium name
 *****************************************************************/
Stadium* MainWindow::get_stadium_by_name(string name) // IN - stadium name
{
    // PROC & OUT - searches linked list for stadium and returns it
    for (size_t i = 0; i < listAZ.length(); i++)
    {
        if (name == listAZ.access(i)->get_stadium())
            return listAZ.access(i);
    }
}

/**************************************************
 *  EVERYTHING BELOW IS TEST ONLY
 * ***********************************************/
// test button to test removeMapItems()
void MainWindow::on_clearMap_clicked()
{
    removeMapItems();
}

// test button to test addAllEdges()
void MainWindow::on_addEdges_clicked()
{
    addAllEdges();
}

//test button to test addAllMarkers()
void MainWindow::on_addMarkers_clicked()
{
    addMarkers();
}

// test button to add red edges
void MainWindow::on_pushButton_clicked()
{
    addAllEdges("red");
}

// TEST PURPOSES ONLY - button to add one single edge
void MainWindow::on_pushButton_2_clicked()
{
    QObject *target =
            qobject_cast<QObject*>(ui->quickWidget->rootObject());

    QString addLine = "addLine";

    QMetaObject::invokeMethod(target, addLine.toUtf8().constData(),
                 Qt::AutoConnection,
                 Q_ARG(QVariant, QString::fromStdString("fenway_marlins")),
                 Q_ARG(QVariant, QString::fromStdString("blue")));
}


/*****************************************************************
 *
 *  METHOD on_safecoButton_clicked(): Class MainWindow
 *________________________________________________________________
 *  Calculates shortest path for all major league trip + draws path
 *  starting from SafeCO
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     Linked list and GUI and graph set up
 *  POST-CONDITIONS
 *     Calculates shortest path for all major league trip + draws path
 *     from SafeCo
 *****************************************************************/
void MainWindow::on_safecoButton_clicked()
{
    // OUT - display map, clear itinerary box
    removeMapItems();
    addMarkers();
    ui->itinerary->clear();

    int d;

    // PROC - get distance of Major League trip, start in SafeCo Field
    d = map.major(map.search_index("SafeCo Field"));

    // PROC - get vector of stadiums visited in path
    vector<string> path = map.getMajor();

    // OUT - draw edges and markers
    for (size_t i = 0; i < path.size() - 1; i++)
        addSingleEdge(path[i], path[i+1]);

    // OUT - add info to itinerary box
    ui->itinerary->addItem("START");
    ui->itinerary->addItem("");
    for (size_t i = 0; i < path.size(); i++)
        ui->itinerary->addItem(QString::fromStdString(path[i]));
    ui->itinerary->addItem("");
    ui->itinerary->addItem("END");
    ui->itinerary->addItem("TOTAL STADIUMS VISITED (NON UNIQUE): "
                           + QString::number(path.size()));
    ui->itinerary->addItem("TOTAL DISTANCE TRAVELED: " + QString::number(d));
}
