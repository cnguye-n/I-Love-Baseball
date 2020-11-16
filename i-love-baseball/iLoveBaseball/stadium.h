#ifndef STADIUM_H
#define STADIUM_H
#include "date2.h"
#include <iostream>
#include <algorithm>
using namespace std;

/*
 sorted
 -major league stadiums in alphabetical order
 -list of major league stadiums sorted by team name
 -list of American League Stadiums sorted by team name
 -list of National League Stadiums sorted by team name
 -stadiums that have grass sorted by team name
 -list of stadiums in chronological order by date opened
 */
/*******************************************************************
 * Stadium Class
 *
 * Stadium Object that represents a vertex in the graph
 ******************************************************************/

class Stadium
{
public:
    //CONSTRUCTORS
    Stadium();
    Stadium(string,string,string,string,Date2,int,string,string,string,
            bool, bool, bool, double, double);

    //ACESSORS
    string get_stadium()const{return _stadium;}
    string get_team()const{return _team;}
    string get_address() const{return _address;}
    string get_city() const{return _city;}
    string get_state() const{return _state;}
    string get_zip() const{return _zip;}
    string get_phone() const{return _phone;}
    double get_long() const{return _long;}
    double get_lat() const{return  _lat;}
    Date2 get_date()const{return _open;}
    int get_capacity() const{return _capacity;}
    bool is_american() const{return _american;}   //true if it is american
    bool is_national() const{return _national;}   //true if it is national
    bool has_grass() const{return _grass;}        //true if it has grass

    //MUTATORS
    void set_stadium(string stadium){_stadium=stadium;}
    void set_team(string team){_team=team;}
    void set_address(string address){_address=address;}
    void set_city(string city){_city=city;}
    void set_state(string state){_state=state;}
    void set_zip(string zip){_zip=zip;}
    void set_phone(string phone){_phone=phone;}
    void set_date(Date2 date){_open=date;}
    void set_capacity(int capacity){_capacity=capacity;}
    void set_long(double longitude){_long=longitude;}
    void set_lat(double latitude){_lat=latitude;}

    void set_american(bool status){_american=status;}
    void set_national(bool status){_national=status;}
    void set_grass(bool status){_grass=status;}


    //INPUT-OUTPUT
    friend ostream& operator<<(ostream& outs, Stadium& info){
        outs << info.get_stadium() << endl << info.get_team() << endl
             << info.get_address() << endl << info.get_phone() << endl
             << "Capacity - " << info.get_capacity() << endl;
    }

    //not sure if we do this bc how we read in the file
    friend istream& operator >>(istream& ins, Stadium& info);

private:
    //everything set to false by default
    bool _american=0; //if it is American League Stadium
    bool _national=0; //if it is National League Stadium
    bool _grass=0;    //if it has grass turf


    string _stadium;  //name of stadium
    string _team;     //team that belong to stadium
    string _address;  //address of stadium
    string _city;     //city of stadium
    string _state;    //state of stadium
    string _zip;      //zip code of stadium
    string _phone;    //phone number
    Date2 _open;       //when the stadium opened
    int _capacity=0;  //capacity of stadium
    double _long;     //longitude coordinate of stadium
    double _lat;      //latitude coordinate of stadium

    //C comparator;  //what to compare the team by
};


/*
 how to add to text file
 */
//in order of stadiums.txt
/*
 ex.
Angels Stadium of Anaheim
Los Angeles Angels of Anaheim
2000 E Gene Autry Way,
Anaheim, CA 92806
(714)940-2000
Opened – April 19, 1966
Capacity – 45,483
 */
//Notes
/*
 -all stadium names include "Stadium, Field, Park, Coliseum, or Centre"
 -all addresses start with numbers
 -phone numbers start with ( but if user doesn't type ( we could have search for "-" "/"
  or count if the string has 10 numbers
  -address -> can't really tell
  -City -> every zip has 5 numbers
  -search in string for open or capacity
 */

//Comparator
/*
 * //TEMPLATE COMPARATORS
template <typename E>
class MinHeap{ //<=
public:
    bool priority(E& lhs, E& rhs){
        return lhs <=rhs;
    }
};

//if high priority item is greater than item being compared
template <typename E>
class MaxHeap{
public:
    bool priority(E& lhs, E& rhs){
        return lhs >=rhs;
    }
};

//CUSTOM COMPARISON
struct Grade{
    int grade; //1-12th grade
};

class CompareGrade{
    public:
    bool operator()(Grade& g1, Grade& g2){
        return(g1.grade < g2.grade);
    }

    bool Less(Grade& g1, Grade& g2){		  //Less(g1,g2) would
        return(g1.grade > g2.grade); //return true if g1 is greater than g2
    }
};
 */

/*******************************************
 * Stadium();
 * Constuctor : Builds stadium object
 * Parameters : None
 * Return     : None
 ******************************************/
/*******************************************
 * Stadium(string,string,string,string,Date2,int,string,string,string,
            bool, bool, bool, double, double);
 * Constuctor : Builds stadium object with parameters
 * Parameters : String, dates, integrs, specifications for the stadium
 * Return     : None
 ******************************************/
/*******************************************
 * string get_stadium()const{return _stadium;}
 * Accessor   : Returns Stadium Object
 * Parameters : None
 * Return     : String object
 ******************************************/
/*******************************************
 * string get_team()const{return _team;}
 * Accessor   : Returns team object
 * Parameters : None
 * Return     : string object
 ******************************************/
/*******************************************
 * string get_address() const{return _address;}
 * Accessor   : Returns address of stadium
 * Parameters : None
 * Return     : Address string object
 ******************************************/
/*******************************************
 * string get_city() const{return _city;}
 * Accessor   : Return city of stadium
 * Parameters : None
 * Return     : Returns string object
 ******************************************/
/*******************************************
 * string get_state() const{return _state;}
 * Accessor   : Returns state of stadium
 * Parameters : None
 * Return     : Returns string object
 ******************************************/
/*******************************************
 * string get_zip() const{return _zip;}
 * Accessor   : Return Zip of stadium
 * Parameters : None
 * Return     : Return string object
 ******************************************/
/*******************************************
 * string get_phone() const{return _phone;}
 * Accessor   : Return phone number of stadium
 * Parameters : None
 * Return     : String object
 ******************************************/
/*******************************************
 * double get_long() const{return _long;}
 * Accessor   : Returns Longitude of stadium
 * Parameters : None
 * Return     : Double type object
 ******************************************/
/*******************************************
 * double get_lat() const{return  _lat;}
 * Accessor   : Return latitude of stadium
 * Parameters : None
 * Return     : Double type object
 ******************************************/
/*******************************************
 * Date2 get_date()const{return _open;}
 * Accessor   : Returns hours of stadium
 * Parameters : None
 * Return     : Date2 type object
 ******************************************/
/*******************************************
 * int get_capacity() const{return _capacity;}
 * Accessor   : Return capacity of stadium
 * Parameters : None
 * Return     : Integer type object
 ******************************************/
/*******************************************
 * bool is_american() const{return _american;}
 * Accessor   : Checks if stadium is American
 * Parameters : None
 * Return     : Boolean Value
 ******************************************/
/*******************************************
 * bool is_national() const{return _national;}
 * Accessor   : Checks if stadium is National
 * Parameters : None
 * Return     : Boolean value
 ******************************************/
/*******************************************
 * bool has_grass() const{return _grass;}
 * Accessor   : Check if Stadium has grass
 * Parameters : None
 * Return     : Boolean value
 ******************************************/

/*******************************************
 * void set_stadium(string stadium){_stadium=stadium;}
 * Mutator    : Sets stadium
 * Parameters : String name
 * Return     : None
 ******************************************/
/*******************************************
 * void set_team(string team){_team=team;}
 * Mutator    : Sets team name
 * Parameters : String team name
 * Return     : None
 ******************************************/
/*******************************************
 * void set_address(string address){_address=address;}
 * Mutator    : Sets adress of stadium
 * Parameters : String object
 * Return     : None
 ******************************************/
/*******************************************
 * void set_city(string city){_city=city;}
 * Mutator    : Sets City of stadium
 * Parameters :  String type City Name
 * Return     : None
 ******************************************/
/*******************************************
 * void set_state(string state){_state=state;}
 * Mutator    : Sets state of Stadium
 * Parameters : String Name of State
 * Return     : None
 ******************************************/
/*******************************************
 * void set_zip(string zip){_zip=zip;}
 * Mutator    : Set Zip of Stadium
 * Parameters : String Zip Code of Area
 * Return     : None
 ******************************************/
/*******************************************
 * void set_phone(string phone){_phone=phone;}
 * Mutator    : Sets phone number of Stadium
 * Parameters : String phone number
 * Return     : None
 ******************************************/
/*******************************************
 * void set_date(Date2 date){_open=date;}
 * Mutator    : Sets opening times of stadium
 * Parameters : Date2 Date object
 * Return     : None
 ******************************************/
/*******************************************
 * void set_capacity(int capacity){_capacity=capacity;}
 * Mutator    : Sets capacity of Stadiums
 * Parameters : Integer amount
 * Return     : None
 ******************************************/
/*******************************************
 * void set_long(double longitude){_long=longitude;}
 * Mutator    : Sets longitude of Stadium
 * Parameters : Double longitude coordinates
 * Return     : None
 ******************************************/
/*******************************************
 * void set_lat(double latitude){_lat=latitude;}
 * Mutator    : Sets latitude of coordinates of stadium
 * Parameters : Double Latitude Coordinates
 * Return     : None
 ******************************************/
/*******************************************
 * void set_american(bool status){_american=status;}
 * Mutator    : Sets American Status of Stadium
 * Parameters : Boolean value
 * Return     : None
 ******************************************/
/*******************************************
 * void set_national(bool status){_national=status;}
 * Mutator    : Sets National Status of Stadium
 * Parameters : Boolean Value
 * Return     : None
 ******************************************/
/*******************************************
 * void set_grass(bool status){_grass=status;}
 * Mutator    : Sets grass status of stadium
 * Parameters : Boolean Value
 * Return     : None
 ******************************************/

#endif // STADIUM_H
