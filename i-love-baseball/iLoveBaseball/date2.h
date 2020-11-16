#ifndef DATE_H
#define DATE_H
#include <string>
using namespace std;

class Date2
{
    public:
        /******************************
         **      CONSTRUCTORS       **
        ******************************/

        Date2();                  // Default constructor, no arguments
                                 // Creates the date January 1, 2000

                                 // Constructor (below)
                                 // Takes unsigned month, day, and year
        Date2(unsigned m, unsigned d, unsigned y);
                                 // Constructor (below)
                                 // Takes month string, unsigned day & year
        Date2(const string &mn, unsigned d, unsigned y);

        /***************
         ** ACCESSORS **
         ***************/

        void printNumeric() const;
        void printAlpha() const;
        Date2 addDays(int) const;
        bool getErrorStatus();
        unsigned getDay();
        unsigned getMonth();
        unsigned getYear();
        string getMonthAlpha() const {return monthName;}
        bool operator==(const Date2 &) const;
        bool operator>(const Date2 &) const;
        bool operator>=(const Date2 &) const;
        bool operator<=(const Date2 &) const;

    private:
        /******************************
         **    CLASS ATTRIBUTES     **
        ******************************/
        unsigned day;                // IN - second argument in constructor
                                     // Unsigned int, represents day
        unsigned month;              // IN - first argument in constructor
                                     // Unsigned int version of month
        string monthName;            // IN - first argument in constructor
                                     // String version of month
        unsigned year;               // IN - third argument in constructor
                                     // Unsigned int, represents year
                                     // Class not designed to handle
                                     // BC (negative) years
        bool errorStatus;            // true if user entered invalid
                                     // parameters for date, false otherwise
        /***************
         ** ACCESSORS **
         ***************/
        bool isLeap(unsigned year) const;
        unsigned daysPerMonth(unsigned m, unsigned y) const;
        string name(unsigned m) const;
        unsigned number(const string &mn) const;
};

#endif // DATE_H

/*****************************************************************
 *
 * DATE CLASS
 * _______________________________________________________________
 * This program creates a class for verifying and creating valid
 * dates. It accepts 3 attributes: month (as an int or string),
 * day, and year.
 * _______________________________________________________________
 * INPUTS:
 *  - Users can enter a date consisting of a month (either as a
 *    string or unsigned int), a day (unsigned int), and year (also
 *    unsigned int). The program checks for invalid dates and also
 *    keeps track of leap years. As of now, it will only accept the
 *    correct and full spelling of a month (first letter can be
 *    capital or lowercase) if the user decides to enter the month
 *    name instead of number. The program does not handle BC years.
 *
 * OUTPUTS:
 *  - If an invalid month name or no information is passed into the
 *    class, the class will use the default date of January 1,
 *    2000. If an invalid date or month (int) is passed in, the
 *    class will try to get the date closest to the one entered.
 *    Program works as intended for valid dates.
 ******************************************************************/

/******************************
**        CONSTRUCTOR       **
******************************/

/****************************************************************
* Date ();
*   Constructor; Initialize class attributes: month, monthName, day
*                and year
*   Parameters: none
*   Return: none
***************************************************************/

/****************************************************************
* Date (unsigned, unsigned, unsigned);
*   Constructor; Initialize class attributes: month, monthName,
*                day and year
*   Parameters: three unsigned ints, for month, day, and year
*   Return: none
***************************************************************/

/****************************************************************
* Date (string, unsigned, unsigned);
*   Constructor; Initialize class attributes: month, monthName,
*                day and year
*   Parameters: one string (month name), two unsigned ints for
*               day and year
*   Return: none
***************************************************************/

/***************
 ** ACCESSORS **
***************/
/****************************************************************
* void printNumeric () const;
*
*   Accessor; This method prints out the date in numerical form:
 *      month/day/year
* -------------------------------------------------------------
*   Parameters: none, accesses the class's private attributes
* -------------------------------------------------------------
*   Return: none, only prints out a date in numeric form
***************************************************************/

/****************************************************************
* void printAlpha () const;
*
*   Accessor; This method prints out the date in the form of
*             monthName day, year
* -------------------------------------------------------------
*   Parameters: none, accesses the class's private attributes
* -------------------------------------------------------------
*   Return: none, only prints out a date in numeric form
***************************************************************/

/****************************************************************
* bool isLeap(unsigned year) const;
*
*   Accessor; This method returns a bool indicating that current year
 *            as leap year or not.
* -------------------------------------------------------------
*   Parameters: unsigned year, passed into constructor
* -------------------------------------------------------------
*   Return: bool - true if leap year, false if not
***************************************************************/

/****************************************************************
* unsigned daysPerMonth(unsigned m, unsigned y) const;
*
*   Accessor; This method returns the number of days in the month, taking
 *            leap years into account.
* -------------------------------------------------------------
*   Parameters: unsigned int month and year, passed into constructor
* -------------------------------------------------------------
*   Return: an unsigned int indicating days in that particular month
***************************************************************/

/****************************************************************
* string name(unsigned m) const;
*
*   Accessor; This method returns string form of the month.
* -------------------------------------------------------------
*   Parameters: unsigned int month, passed in from constructor
* -------------------------------------------------------------
*   Return: a string with the month name
***************************************************************/

/****************************************************************
* unsigned number(const string &mn) const;
*
*   Accessor; This method returns unsigned int form of the month.
* -------------------------------------------------------------
*   Parameters: mn, a month (string)
* -------------------------------------------------------------
*   Return: the unsigned int representation of the month
***************************************************************/
