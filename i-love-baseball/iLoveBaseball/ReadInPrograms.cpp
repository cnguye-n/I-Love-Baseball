#include <iostream>
#include <fstream>
#include <string>
#include "readinprograms.h"
#include "date2.h"

using namespace std;

/*****************************************************************
 *
 *  METHOD Stadiums()
 *________________________________________________________________
 * Reads allstadiumsreadin.txt file, converts appropriate variables
 * into appropriate types, and inserts stadium objects into Linked
 * List. Returns linked list of stadium objects sorted AZ
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns linked list of stadium objects sorted AZ
 *****************************************************************/
LinkedList<Stadium*> Stadiums()
{
    ifstream outs("allstadiumsreadin.txt");
    string team, stadium, address, city, state, zip, phone, month, day,
            year, capacity, american, national, grass, latitude, longitude;
    int dayNum, monthNum, yearNum, capacityNum;
    bool aBool, nBool, gBool;
    double latNum, longNum;
    LinkedList<Stadium*> list;

    // PROC - open file, read, assign variables
    if(outs.is_open())
    {
        while(!outs.eof())
        {
            getline(outs, stadium);
            getline(outs, team);
            getline(outs, address);
            getline(outs, city);
            getline(outs, state);
            getline(outs, zip);
            getline(outs, phone);
            getline(outs, month);
            getline(outs, day);
            getline(outs, year);
            getline(outs, capacity);
            getline(outs, american);
            getline(outs, national);
            getline(outs, grass);
            getline(outs, latitude);
            getline(outs, longitude);

            dayNum = stoi(day);
            monthNum = stoi(month);
            yearNum = stoi(year);
            capacityNum = stoi(capacity);
            latNum = stod(latitude);
            longNum = stod(longitude);

            aBool = (american == "1") ? true : false;
            nBool = (national == "1") ? true : false;
            gBool = (grass == "1") ? true : false;

            // PROC - create Date and Stadium objects, & insert
            Date2 open(monthNum, dayNum, yearNum);

            Stadium* s = new Stadium(stadium, team, address, phone, open, capacityNum,
                      city, state, zip, aBool, nBool, gBool, latNum, longNum);

            list.insert_sorted_stadium(s);
        }
        outs.close();
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    // OUT - return list
    return list;
}

/*****************************************************************
 *
 *  METHOD StadiumsbyTeamName()
 *________________________________________________________________
 * Reads allstadiumsreadin.txt file, converts appropriate variables
 * into appropriate types, and inserts stadium objects into Linked
 * List. Returns linked list of stadium objects sorted by team
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns linked list of stadium objects sorted by team
 *****************************************************************/
LinkedList<Stadium*> StadiumsByTeamName()
{
    ifstream outs("allstadiumsreadin.txt");
    string team, stadium, address, city, state, zip, phone, month, day,
            year, capacity, american, national, grass, latitude, longitude;
    int dayNum, monthNum, yearNum, capacityNum;
    bool aBool, nBool, gBool;
    double latNum, longNum;
    LinkedList<Stadium*> list;

    // PROC - open file, read, assign variables
    if(outs.is_open())
    {
        while(!outs.eof())
        {
            getline(outs, stadium);
            getline(outs, team);
            getline(outs, address);
            getline(outs, city);
            getline(outs, state);
            getline(outs, zip);
            getline(outs, phone);
            getline(outs, month);
            getline(outs, day);
            getline(outs, year);
            getline(outs, capacity);
            getline(outs, american);
            getline(outs, national);
            getline(outs, grass);
            getline(outs, latitude);
            getline(outs, longitude);

            dayNum = stoi(day);
            monthNum = stoi(month);
            yearNum = stoi(year);
            capacityNum = stoi(capacity);
            latNum = stod(latitude);
            longNum = stod(longitude);

            aBool = (american == "1") ? true : false;
            nBool = (national == "1") ? true : false;
            gBool = (grass == "1") ? true : false;

            // PROC - create Date and Stadium objects, & insert
            Date2 open(monthNum, dayNum, yearNum);

            Stadium* s = new Stadium(stadium, team, address, phone, open, capacityNum,
                      city, state, zip, aBool, nBool, gBool, latNum, longNum);

            list.insert_sorted_team(s);
        }
        outs.close();
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    // OUT - return list
    return list;
}

/*****************************************************************
 *
 *  METHOD StadiumsbyAmericanTeams()
 *________________________________________________________________
 * Reads allstadiumsreadin.txt file, converts appropriate variables
 * into appropriate types, and inserts stadium objects into Linked
 * List. Returns linked list of american stadium objects
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns linked list of american stadium objects
 *****************************************************************/
LinkedList<Stadium*> StadiumsByAmericanTeams()
{
    ifstream outs("allstadiumsreadin.txt");
    string team, stadium, address, city, state, zip, phone, month, day,
            year, capacity, american, national, grass, latitude, longitude;
    int dayNum, monthNum, yearNum, capacityNum;
    bool aBool, nBool, gBool;
    double latNum, longNum;
    LinkedList<Stadium*> list;

    // PROC - open file, read, assign variables
    if(outs.is_open())
    {
        while(!outs.eof())
        {
            getline(outs, stadium);
            getline(outs, team);
            getline(outs, address);
            getline(outs, city);
            getline(outs, state);
            getline(outs, zip);
            getline(outs, phone);
            getline(outs, month);
            getline(outs, day);
            getline(outs, year);
            getline(outs, capacity);
            getline(outs, american);
            getline(outs, national);
            getline(outs, grass);
            getline(outs, latitude);
            getline(outs, longitude);

            dayNum = stoi(day);
            monthNum = stoi(month);
            yearNum = stoi(year);
            capacityNum = stoi(capacity);
            latNum = stod(latitude);
            longNum = stod(longitude);

            aBool = (american == "1") ? true : false;
            nBool = (national == "1") ? true : false;
            gBool = (grass == "1") ? true : false;

            // PROC - create Date and Stadium objects, & insert
            if (aBool)
            {
                Date2 open(monthNum, dayNum, yearNum);

                Stadium* s = new Stadium(stadium, team, address, phone, open, capacityNum,
                          city, state, zip, aBool, nBool, gBool, latNum, longNum);

                list.insert_sorted_team(s);
            }

        }
        outs.close();
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    // OUT - return list
    return list;

}

/*****************************************************************
 *
 *  METHOD StadiumsbyNationalTeams()
 *________________________________________________________________
 * Reads allstadiumsreadin.txt file, converts appropriate variables
 * into appropriate types, and inserts stadium objects into Linked
 * List. Returns linked list of national stadium objects
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns linked list of national stadium objects
 *****************************************************************/
LinkedList<Stadium*> StadiumsByNationalTeams()
{
    ifstream outs("allstadiumsreadin.txt");
    string team, stadium, address, city, state, zip, phone, month, day,
            year, capacity, american, national, grass, latitude, longitude;
    int dayNum, monthNum, yearNum, capacityNum;
    bool aBool, nBool, gBool;
    double latNum, longNum;
    LinkedList<Stadium*> list;

    // PROC - open file, read, assign variables
    if(outs.is_open())
    {
        while(!outs.eof())
        {
            getline(outs, stadium);
            getline(outs, team);
            getline(outs, address);
            getline(outs, city);
            getline(outs, state);
            getline(outs, zip);
            getline(outs, phone);
            getline(outs, month);
            getline(outs, day);
            getline(outs, year);
            getline(outs, capacity);
            getline(outs, american);
            getline(outs, national);
            getline(outs, grass);
            getline(outs, latitude);
            getline(outs, longitude);

            dayNum = stoi(day);
            monthNum = stoi(month);
            yearNum = stoi(year);
            capacityNum = stoi(capacity);
            latNum = stod(latitude);
            longNum = stod(longitude);

            aBool = (american == "1") ? true : false;
            nBool = (national == "1") ? true : false;
            gBool = (grass == "1") ? true : false;

            // PROC - create Date and Stadium objects, & insert
            if (!aBool)
            {
                Date2 open(monthNum, dayNum, yearNum);

                Stadium* s = new Stadium(stadium, team, address, phone, open, capacityNum,
                          city, state, zip, aBool, nBool, gBool, latNum, longNum);

                list.insert_sorted_team(s);
            }

        }
        outs.close();
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    // OUT - return list
    return list;

}

/*****************************************************************
 *
 *  METHOD GrassStadiumsByTeamName()
 *________________________________________________________________
 * Reads allstadiumsreadin.txt file, converts appropriate variables
 * into appropriate types, and inserts stadium objects into Linked
 * List. Returns linked list of grass stadium objects
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns linked list of grass stadium objects
 *****************************************************************/
LinkedList<Stadium*> GrassStadiumsByTeamName()
{
    ifstream outs("allstadiumsreadin.txt");
    string team, stadium, address, city, state, zip, phone, month, day,
            year, capacity, american, national, grass, latitude, longitude;
    int dayNum, monthNum, yearNum, capacityNum;
    bool aBool, nBool, gBool;
    double latNum, longNum;
    LinkedList<Stadium*> list;

    // PROC - open file, read, assign variables
    if(outs.is_open())
    {
        while(!outs.eof())
        {
            getline(outs, stadium);
            getline(outs, team);
            getline(outs, address);
            getline(outs, city);
            getline(outs, state);
            getline(outs, zip);
            getline(outs, phone);
            getline(outs, month);
            getline(outs, day);
            getline(outs, year);
            getline(outs, capacity);
            getline(outs, american);
            getline(outs, national);
            getline(outs, grass);
            getline(outs, latitude);
            getline(outs, longitude);

            dayNum = stoi(day);
            monthNum = stoi(month);
            yearNum = stoi(year);
            capacityNum = stoi(capacity);
            latNum = stod(latitude);
            longNum = stod(longitude);

            aBool = (american == "1") ? true : false;
            nBool = (national == "1") ? true : false;
            gBool = (grass == "1") ? true : false;

            // PROC - create Date and Stadium objects, & insert
            if (gBool)
            {
                Date2 open(monthNum, dayNum, yearNum);

                Stadium* s = new Stadium(stadium, team, address, phone, open, capacityNum,
                          city, state, zip, aBool, nBool, gBool, latNum, longNum);

                list.insert_sorted_team(s);
            }

        }
        outs.close();
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    // OUT - return list
    return list;

}

/*****************************************************************
 *
 *  METHOD StadiumsByDate()
 *________________________________________________________________
 * Reads allstadiumsreadin.txt file, converts appropriate variables
 * into appropriate types, and inserts stadium objects into Linked
 * List. Returns linked list of stadium objects sorted by date
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns linked list of stadium objects sorted by date
 *****************************************************************/
LinkedList<Stadium*> StadiumsByDate()
{
    ifstream outs("allstadiumsreadin.txt");
    string team, stadium, address, city, state, zip, phone, month, day,
            year, capacity, american, national, grass, latitude, longitude;
    int dayNum, monthNum, yearNum, capacityNum;
    bool aBool, nBool, gBool;
    double latNum, longNum;
    LinkedList<Stadium*> list;

    // PROC - open file, read, assign variables
    if(outs.is_open())
    {
        while(!outs.eof())
        {
            getline(outs, stadium);
            getline(outs, team);
            getline(outs, address);
            getline(outs, city);
            getline(outs, state);
            getline(outs, zip);
            getline(outs, phone);
            getline(outs, month);
            getline(outs, day);
            getline(outs, year);
            getline(outs, capacity);
            getline(outs, american);
            getline(outs, national);
            getline(outs, grass);
            getline(outs, latitude);
            getline(outs, longitude);

            dayNum = stoi(day);
            monthNum = stoi(month);
            yearNum = stoi(year);
            capacityNum = stoi(capacity);
            latNum = stod(latitude);
            longNum = stod(longitude);

            aBool = (american == "1") ? true : false;
            nBool = (national == "1") ? true : false;
            gBool = (grass == "1") ? true : false;

            // PROC - create Date and Stadium objects, & insert
            Date2 open(monthNum, dayNum, yearNum);

            Stadium* s = new Stadium(stadium, team, address, phone, open, capacityNum,
                      city, state, zip, aBool, nBool, gBool, latNum, longNum);

            list.insert_sorted_date(s);
        }
        outs.close();
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    // OUT - return list
    return list;

}

/*****************************************************************
 *
 *  METHOD Souvenirs()
 *________________________________________________________________
 * Reads souvenirs.txt file, converts appropriate variables
 * into appropriate types, and inserts souvenir objects into container
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns linked list of souvenir objects into container
 *****************************************************************/
container<souvenir*> Souvenirs()
{
    ifstream outs("souvenirs.txt");
    string name, price;
    double priceNum;

    container<souvenir*> list;

    // PROC - open file, read, assign variables
    if(outs.is_open())
    {
        while(!outs.eof())
        {
            getline(outs, name);
            getline(outs, price);

            priceNum = stod(price);

            souvenir* s = new souvenir(name, 0,  priceNum);

            list.attach(s);
        }
        outs.close();
    }
    else {
        cout<<"Cannot open file"<<endl;
    }

    // OUT - return list
    return list;
}
