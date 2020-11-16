#include <iostream>
#include <cctype>
#include "date2.h"
using namespace std;

/*****************************************************************
 *
 *  DEFAULT CONSTRUCTOR Date: Class Date
 *________________________________________________________________
 *  This is the default constructor for the Date class, when
 *  there are no arguments passed into the object. The constructor
 *  will create a default date of 1/1/2000 or January 1, 2000.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function is called when a Date object is created and
 *     no arguments are passed in.
 *
 *  POST-CONDITIONS
 *     Sets default month to January(1), day to 1, and year to 2000.
 *****************************************************************/
Date2::Date2()
{
    // PROCESSING - sets default date of January 1, 2000.
    day = 1;
    month = 1;
    monthName = "January";
    year = 2000;

}

/*****************************************************************
 *
 *  CONSTRUCTOR Date (Unsigned int): Class Date
 *________________________________________________________________
 *  This is the constructor for the Date class that is called when
 *  there is an unsigned int argument passed in for the month.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function is called when a Date object is created and
 *     arguments are passed in for the month (unsigned int), day
 *     (unsigned int), and year (unsigned int). If a string is
 *     entered for the month, it will call a different constructor.
 *     The function uses helper function daysPerMonth to determine
 *     valid days in a month.
 *
 *  POST-CONDITIONS
 *     Sets month, day, and year to the arguments to the best of its
 *     ability. If an invalid date is entered, it will construct a
 *     valid date as close as possible to the date entered. It will
 *     also print out an error message if that happens.
 *****************************************************************/
Date2::Date2(unsigned m,      // IN - month (unsigned int), first argument
           unsigned d,      // IN - day (unsigned int), second argument
           unsigned y)      // IN - year (unsigned int), third argument
{
    // PROCESSING - create a bool variable for error status
    bool error;
    error = false;
    errorStatus = false;

    // PROCESSING - set year equal to the year entered
    //              since unsigned has to be positive, year will be
    //              technically valid
    year = y;

    // PROCESSING - checking for valid month
    //              if month entered is 0, automatically set month to 1
    //              because that's the closest and set error status to true
    if (m == 0)
    {
        month = 1;
        monthName = "January";
        error = true;
        errorStatus = true;
    }
    // PROCESSING - month is valid if between 1 and 12
    //              use helper function name() to get month name
    //              in case user enters month name in lowercase
    else if (m <= 12)
    {
        month = m;
        monthName = name(m);
    }
    // PROCESSING - if month is >12, set month to 12 since that will
    //              be closest number
    else
    {
        month = 12;
        monthName = "December";
        error = true;
        errorStatus = true;
    }

    // PROCESSING - checking for valid day
    //              if day passed in is 0, automatically convert to 1
    //              and later print error status
    if (d == 0)
    {
        day = 1;
        error = true;
        errorStatus = true;
    }
    // PROCESSING - call daysPerMonth() function to determine valid days
    //              for the month, if days entered is between 1 and max
    //              day, we set the day as the one passed in
    else if (d <= daysPerMonth(month, year))
    {
        day = d;
    // PROCESSING - if day entered is greater than max days, we set day
    //              to the last day as closest. again, need daysPerMonth's
    //              help. error status is true
    } else
    {
        day = daysPerMonth(month, year);
        error = true;
        errorStatus = true;
    }

    // OUT - if there is an error in the date entered, this error message
    //       will print. constructor sets date closest to the one entered.
    if (error == true)
    {
        cout << "Invalid date values: Date corrected to " << month << "/"
             << day << "/" << year << ".\n";
    }

}

/*****************************************************************
 *
 *  CONSTRUCTOR Date (string): Class Date
 *________________________________________________________________
 *  This is the constructor for the Date class that is called when
 *  there is a string argument passed in for the month.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function is called when a Date object is created and
 *     arguments are passed in for the month (string), day
 *     (unsigned int), and year (unsigned int). If an unsigned int is
 *     entered for the month, it will call a different constructor.
 *     The function uses helper function daysPerMonth to determine
 *     valid days in a month.
 *
 *  POST-CONDITIONS
 *     Sets month, day, and year to the arguments to the best of its
 *     ability. If an invalid day is entered, it will construct a
 *     valid date as close as possible to the date entered. It will
 *     also print out an error message if that happens. If an invalid
 *     month string is entered, it will set the date to 1/1/2000. This
 *     constructor recognizes "January" and "january" as valid month
 *     names, but not "Jan" or "jan."
 *****************************************************************/
Date2::Date2(const string &mn,  // IN - month (string), first argument
           unsigned d,        // IN - day (unsigned int), second argument
           unsigned y)        // IN - year (unsigned int), third argument
{
    // PROCESSING - create a bool variable for error status
    //              there are two different errors, so two different
    //              variables
    bool name_error;
    bool day_error;
    name_error = false;
    day_error = false;

    // PROCESSING - set year equal to the year entered
    //              since unsigned has to be positive, year will be
    //              technically valid
    year = y;

    // PROCESSING - checking for valid day
    //              if day passed in is 0, automatically convert to 1
    //              and later print error status
    if (d == 0)
    {
        day = 1;
        day_error = true;
    }
    // PROCESSING - call daysPerMonth() function to determine valid days
    //              for the month, if days entered is between 1 and max
    //              day, we set the day as the one passed in. calls
    //              number() function to convert string to int
    else if (d <= daysPerMonth(number(mn), year))
    {
        day = d;
    }
    // PROCESSING - if day entered is greater than max days, we set day
    //              to the last day as closest. again, need daysPerMonth's
    //              help. error status is true
    else
    {
        day = daysPerMonth(number(mn), year);
        day_error = true;
    }

    // PROCESSING - switch menu to set the month values
    //              number function accounts for capitalized or lowercase
    //              month names
    //              if month name invalid, set date to 1/1/2000
    switch(number(mn))
    {
        case 1:
            monthName = "January";
            month = 1;
            break;
        case 2:
            monthName = "February";
            month = 2;
            break;
        case 3:
            monthName = "March";
            month = 3;
            break;
        case 4:
            monthName = "April";
            month = 4;
            break;
        case 5:
            monthName = "May";
            month = 5;
            break;
        case 6:
            monthName = "June";
            month = 6;
            break;
        case 7:
            monthName = "July";
            month = 7;
            break;
        case 8:
            monthName = "August";
            month = 8;
            break;
        case 9:
            monthName = "September";
            month = 9;
            break;
        case 10:
            monthName = "October";
            month = 10;
            break;
        case 11:
            monthName = "November";
            month = 11;
            break;
        case 12:
            monthName = "December";
            month = 12;
            break;
        default:
            name_error = true;
            monthName = "January";
            month = 1;
            day = 1;
            year = 2000;
     }

    // OUT - if the program can't recognize the month name, this error
    //       prints and the date is set to 1/1/2000
    if (name_error == true)
    {
        cout << "Invalid month name: the Date was set to 1/1/2000.\n";
    }

    // OUT - if there is an error in the day entered, this error message
    //       will print. constructor sets date closest to the one entered.
    //       Name error has to be false for this to activate
    if (name_error == false && day_error == true)
    {
        cout << "Invalid date values: Date corrected to " << month << "/"
             << day << "/" << year << ".\n";
    }
}

/*****************************************************************
 *
 *  METHOD printNumeric: Class Date
 *________________________________________________________________
 *  This function prints out the date in numerical form:
 *      month/day/year
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function does not take in any arguments but accesses the
 *     class's private attributes month, day, and year.
 *
 *  POST-CONDITIONS
 *     The function prints out the date in the form of
 *         month/day/year (all variables unsigned).
 *****************************************************************/
void Date2::printNumeric() const
{
    // OUT - prints out date in numerical form
    cout << month << "/" << day << "/" << year;
}

/*****************************************************************
 *
 *  METHOD printAlpha: Class Date
 *________________________________________________________________
 *  This function prints out the date in form of:
 *      monthName day, year
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function does not take in any arguments but accesses the
 *     class's private attributes monthName, day, and year.
 *
 *  POST-CONDITIONS
 *     The function prints out the date in the form of
 *         monthName day, year
 *****************************************************************/
void Date2::printAlpha() const
{
    // OUT - prints out date in alpha form
    cout << monthName << " " << day << ", " << year;
}

/*****************************************************************
 *
 *  METHOD isLeap: Class Date
 *________________________________________________________________
 *  This function returns a bool indicating that current year
 *  as leap year or not.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function takes in y, a year (unsigned), as an argument.
 *
 *  POST-CONDITIONS
 *     The function returns true if the year is a leap year, and
 *     false if it's not.
 *****************************************************************/

Date2 Date2::addDays(int) const
{
    //TO FILL IN IF I HAVE TIME
}

bool Date2::isLeap(unsigned y) const     // IN - year(unsigned)
                                        //      that gets passed in
{
    // OUT - create bool called leap to be returned
    //       true if leap year, false if not
    bool leap;

    // PROCESSING - goes through if/else statements to determine leap year
    if (y % 400 == 0)
        leap = true;
    else if (y % 4 == 0 && y % 100 != 0)
        leap = true;
    else
        leap = false;

    // OUT - return bool
    return leap;
}

/*****************************************************************
 *
 *  METHOD daysPerMonth: Class Date
 *________________________________________________________________
 *  This function returns the number of days in the month, taking
 *  leap years into account.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function takes in y, a year (unsigned), as an argument.
 *
 *  POST-CONDITIONS
 *     The function returns true if the year is a leap year, and
 *     false if it's not.
 *****************************************************************/
unsigned Date2::daysPerMonth(unsigned m,        // IN - month (unsigned)
                            unsigned y) const  // IN - year (unsigned)
{
    // OUT - days (unsigned) to be returned from this function
    unsigned d;
    d = 0;

    // PROCESSING - Jan, March, May, Jul, Aug, Oct, or Dec
    //              there are 31 days in those months
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10
               || m == 12 )
        d = 31;
    // PROCESSING - in February, there are 29 days if it's a leap year
    //              we'll use the isLeap function
    //              there are only 28 days in non-leap years
    else if (m == 2)
    {
        if (isLeap(y) == true)
            d = 29;
        else {
            d = 28;
             }
    }
    // PROCESSING - for Apr, Jun, Sept, and Nov there are 30 days
    else if (m == 4 || m == 6 || m == 9 || m == 11)
        d = 30;

    // OUT - return number of days in that month
    return d;
}

/*****************************************************************
 *
 *  METHOD name: Class Date
 *________________________________________________________________
 *  This function returns string form of the month.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function takes in m, a month (unsigned int), as an argument.
 *
 *  POST-CONDITIONS
 *     The function returns the string form of the month.
 *****************************************************************/
string Date2::name(unsigned m) const      //IN - m (unsigned int), a month
{
    // OUT - create the string to be returned
    string mn;

    // PROCESSING - if/else statements to match month name
    if (m == 1)
        mn = "January";
    else if (m == 2)
        mn = "February";
    else if (m == 3)
        mn = "March";
    else if (m == 4)
        mn = "April";
    else if (m == 5)
        mn = "May";
    else if (m == 6)
        mn = "June";
    else if (m == 7)
        mn = "July";
    else if (m == 8)
        mn = "August";
    else if (m == 9)
        mn = "September";
    else if (m == 10)
        mn = "October";
    else if (m == 11)
        mn = "November";
    else if (m == 12)
        mn = "December";
    else if (m == 0 || m > 12)
        mn = "None";

    // OUT - return month name string
    return mn;
}

/*****************************************************************
 *
 *  METHOD number: Class Date
 *________________________________________________________________
 *  This function returns unsigned int form of the month.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     The function takes in mn, a month (string), as an argument.
 *     It accounts for both capitalized and uncapitalized first
 *     letters.
 *
 *  POST-CONDITIONS
 *     The function returns the unsigned int form of the month.
 *****************************************************************/
unsigned Date2::number(const string &mn) const
                                          // IN - mn (string), month name
{
    // OUT - create unsigned int to be returned
    unsigned m;

    // PROCESSING - if month name string matches the names we have,
    //              set the month unsigned int to corresponding number
    //              if it doesn't match, set m to 0
    if (mn == "January" || mn == "january")
        m = 1;
    else if (mn == "February" || mn == "february")
        m = 2;
    else if (mn == "March" || mn == "march")
        m = 3;
    else if (mn == "April" || mn == "april")
        m = 4;
    else if (mn == "May" || mn == "may")
        m = 5;
    else if (mn == "June" || mn == "june")
        m = 6;
    else if (mn == "July" || mn == "july")
        m = 7;
    else if (mn == "August" || mn == "august")
        m = 8;
    else if (mn == "September" || mn == "september")
        m = 9;
    else if (mn == "October" || mn == "october")
        m = 10;
    else if (mn == "November" || mn == "november")
        m = 11;
    else if (mn == "December" || mn == "december")
        m = 12;
    else
        m = 0;

    // OUT - return unsigned int form of the month
    return m;
}

/**************************************************************************
* Accessor getErrorStatus: Class Date
*__________________________________________________________________________
* Returns errorStatus, a bool that tracks whether input Date was valid
*__________________________________________________________________________
* PRE-CONDITIONS
*   None
*
* POST-CONDITIONS
*   Returns bool on whether or not input Date was valid
**************************************************************************/
bool Date2::getErrorStatus()
{
    // OUT - return errorStatus
    return errorStatus;
}

/**************************************************************************
* Accessor getDay: Class Date
*__________________________________________________________________________
* Returns day, numeric day value of Date
*__________________________________________________________________________
* PRE-CONDITIONS
*   None
*
* POST-CONDITIONS
*   Returns unsigned day number
**************************************************************************/
unsigned Date2::getDay()
{
    // OUT - return day
    return day;
}

/**************************************************************************
* Accessor getMonth: Class Date
*__________________________________________________________________________
* Returns day, numeric month value of Date
*__________________________________________________________________________
* PRE-CONDITIONS
*   None
*
* POST-CONDITIONS
*   Returns unsigned month number
**************************************************************************/
unsigned Date2::getMonth()
{
    // OUT - return month
    return month;
}

/**************************************************************************
* Accessor getYear: Class Date
*__________________________________________________________________________
* Returns day, numeric year value of Date
*__________________________________________________________________________
* PRE-CONDITIONS
*   None
*
* POST-CONDITIONS
*   Returns unsigned year number
**************************************************************************/
unsigned Date2::getYear()
{
    // OUT - return year
    return year;
}

/**************************************************************************
* Accessor operator==: Class Date
*__________________________________________________________________________
* Determines if current Date and other Date are equal
*__________________________________________________________________________
* PRE-CONDITIONS
*   other: other date number that will be compared
*          to date complex number
*
* POST-CONDITIONS
*   Returns bool on whether or not current date number
*   and passed through date number are equal
**************************************************************************/
bool Date2::operator==
              (const Date2& other) const  //IN-date num that will be
                                            //   compared to curr date
                                            //   number
{
    //OUTPUT--returns bool on whether or not curr datenumber and passed
    //        through date number are eaual
    return(this->month == other.month && this->day == other.day &&
           this->year == other.year);
}

/**************************************************************************
* Accessor operator>: Class Date
*__________________________________________________________________________
* Determines if current Date is later than other Date
*__________________________________________________________________________
* PRE-CONDITIONS
*   other: other date that will be compared to current date
*
* POST-CONDITIONS
*   Returns bool on whether or not current date is later than passed thru
*   date
**************************************************************************/
bool Date2::operator>
              (const Date2& other) const  //IN-date num that will be
                                            //   compared to curr date
{
    //OUTPUT--returns bool on whether or not curr datenumber and passed
    //        through date number are eaual
    if (this->year > other.year)
    {
        return true;
    }
    else if (this->year >= other.year && this->month > other.month)
    {
        return true;
    }
    else if (this->year >= other.year && this->month >= other.month
             && this->day > other.day)
    {
        return true;
    }
    else {
        return false;
    }
}

/**************************************************************************
* Accessor operator>=: Class Date
*__________________________________________________________________________
* Determines if current Date is later or equal to other Date
*__________________________________________________________________________
* PRE-CONDITIONS
*   other: other date that will be compared to current date
*
* POST-CONDITIONS
*   Returns bool on whether or not current date is later/same than passed thru
*   date
**************************************************************************/
bool Date2::operator>=
              (const Date2& other) const  //IN-date num that will be
                                            //   compared to curr date
{
    //OUTPUT--returns bool on whether or not curr datenumber and passed
    //        through date number are equal
    if (this->year > other.year)
    {
        return true;
    }
    else if (this->year >= other.year && this->month > other.month)
    {
        return true;
    }
    else if (this->year >= other.year && this->month >= other.month
             && this->day > other.day)
    {
        return true;
    }
    else if (this->year == other.year && this->month == other.month
             && this->day == other.day)
    {
        return true;
    }
    else {
        return false;
    }
}

/**************************************************************************
* Accessor operator<=: Class Date
*__________________________________________________________________________
* Determines if current Date is earlier or equal to other Date
*__________________________________________________________________________
* PRE-CONDITIONS
*   other: other date that will be compared to current date
*
* POST-CONDITIONS
*   Returns bool on whether or not current date is earlier/same than passed thru
*   date
**************************************************************************/
bool Date2::operator<=
              (const Date2& other) const  //IN-date num that will be
                                            //   compared to curr date
{
    //OUTPUT--returns bool on whether or not curr datenumber and passed
    //        through date number are equal or earlier
    if (this->year > other.year)
    {
        return false;
    }
    else if (this->year >= other.year && this->month > other.month)
    {
        return false;
    }
    else if (this->year >= other.year && this->month >= other.month
             && this->day > other.day)
    {
        return false;
    }
    else if (this->year == other.year && this->month == other.month
             && this->day == other.day)
    {
        return true;
    }
    else {
        return true;
    }
}


