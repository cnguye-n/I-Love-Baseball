#include "add_all_prices.h"

/**************************************************************
* double add_all_prices(container<souvenir*> v1)
* ____________________________________________________________
* Goes through the vector and adds up the prices
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector is not null
* POST-CONDITIONS
* -Vector is unaffected
* -Double sum is returned
***************************************************************/
double add_all_prices(container<souvenir*> v1) // IN - container of souv
{
    double sum;
    sum = 0.00;

    // PROC - loop thru souvenirs, add price
    for(int i = 0; i < v1.size(); i++){
        sum += v1.at(i)->return_price() * v1.at(i)->return_quantity();
    }
    //OUT - return sum
    return sum;
}
