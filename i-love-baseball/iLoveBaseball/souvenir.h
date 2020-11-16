#ifndef SOUVENIR_H
#define SOUVENIR_H
#include <iostream>
#include <string>
#include "vector.h"

class souvenir
{
public:
    /********************************
         **  CONSTRUCTOR  **
     ********************************/
    souvenir();
    souvenir(std::string name, int quantity, double price);


    /********************************
         **  ACCESSORS **
     ********************************/
    std::string return_name() {return _name;}
    int return_quantity() {return _quantity;}
    double return_price() {return _price;}

    /********************************
         ** MUTATORS **
     ********************************/
    void set_name(std::string name);
    void set_price(double price);
    void set_quantity(int quantity);
    void add_one();

private:
    std::string _name; // IN/OUT - the souvenir name
    int _quantity; // IN/OUT - the amount of souvenirs
    double _price; // IN/OUT - the price of the souvenir
};

/**************************************************************************
 *
 * Sovenir Class
 *   This class represents a souvenir object and manages
 *   name, price, and quantity.
 *
 **************************************************************************/

/********************************
     **  CONSTRUCTOR  **
 ********************************/

/*******************************************
* souvenir();
* Constructor: Constructs the sovenir object
* Parameters: None
* Return: none
*****************************************/

/*******************************************
* souvenir(std::string name, int quantity, double price);
* Constructor: Constructs the sovenir object
* Parameters: name (string), quantity (int), price(double)
* Return: none
*****************************************/

/********************************
     **  ACCESSORS **
 ********************************/

/*******************************************
* std::string return_name();
* Accessor: Returns name of souviner
* Parameters: none
* Return: name (string)
*****************************************/

/*******************************************
* int return_quantity();
* Accessor: returns quantity of souviner
* Parameters: none
* Return: quantity (int)
*****************************************/

/*******************************************
* double return_price();
* Accessor: returns price of souviner
* Parameters: none
* Return: price (double)
*****************************************/

/********************************
     ** MUTATORS **
 ********************************/

/*******************************************
* void set_name(std::string name);
* Mutator: Sets name of souviner to new name
* Parameters: name (string)
* Return: none
*****************************************/

/*******************************************
* void set_price(double price)
* Mutator: Sets price of souviner to new price
* Parameters: price (double)
* Return: none
*****************************************/

/*******************************************
* void set_quantity(int quantity)
* Mutator: Sets quantity of souviner to new quantity
* Parameters: quantity (int)
* Return: none
*****************************************/

/*******************************************
* void add_one();
* Mutator: Increments quantity by one
* Parameters: none
* Return: none
*****************************************/

#endif // SOUVENIR_H
