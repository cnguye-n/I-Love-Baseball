#include "souvenir.h"


/**************************************************************
* CONSTRUCTOR souviner() : Class souviner
* ____________________________________________________________
* Constructs souviner class
* ___________________________________________________________
* Pre-Condition
* none
*
* Post-Condition
* Initalizes souviner object
*************************************************************/
souvenir::souvenir()
{
    //PROC - Initalizes souviner name, quantity, and price to 0
    _name = "";
    _quantity = 0;
    _price = 0;
}

/**************************************************************
* CONSTUCTOR souviner() : Class souviner
* ____________________________________________________________
* Constructs souviner class
* ___________________________________________________________
* Pre-Condition
* string name - name of souviner
* int quantity - quantity of souviner
* double price - price of souviner
*
* Post-Condition
* Initalizes souviner object
*************************************************************/
souvenir::souvenir(std::string name, // IN - souviner name
                   int quantity,     // IN - souviner quantity
                   double price)     // IN - souviner price
{
    //PROC - initalizing souviner name, quantity, and price
    _name = name;
    _quantity = quantity;
    _price = price;
}

/**************************************************************
* METHOD set_name() : Class souviner
* ____________________________________________________________
* Sets name of souviner with new name
* ___________________________________________________________
* Pre-Condition
* string name - new souviner name
*
* Post-Condition
* Changes souviner name
*************************************************************/
void souvenir::set_name(std::string name) // IN - new souviner name
{
    //PROC - name is changed
    _name = name;
}

/**************************************************************
* METHOD set_price() : Class souviner
* ____________________________________________________________
* Sets price of souviner with new price
* ___________________________________________________________
* Pre-Condition
* double price - new souviner price
*
* Post-Condition
* Changes souviner price
*************************************************************/
void souvenir::set_price(double price) // IN - new souviner price
{
    //PROC - price is changed
    _price = price;
}

/**************************************************************
* METHOD set_quantity() : Class souviner
* ____________________________________________________________
* Sets quantity of souviner to new quantity
* ___________________________________________________________
* Pre-Condition
* int quantity - new quantity
*
* Post-Condition
* Changes souviner quantity
*************************************************************/
void souvenir::set_quantity(int quantity) //IN - new souviner quantity
{
    //PROC - quantity is changed
    _quantity = quantity;
}

/**************************************************************
* METHOD add_one() : Class souviner
* ____________________________________________________________
* Increments quantity by one
* ___________________________________________________________
* Pre-Condition
* none
*
* Post-Condition
* souviner quantity is incremented by one
*************************************************************/
void souvenir::add_one()
{
    //PROC - quantity is incremented by one
    _quantity++;
}
