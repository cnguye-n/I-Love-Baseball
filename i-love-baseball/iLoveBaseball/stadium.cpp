#include "stadium.h"


/**************************************************************
* Stadium::Stadium(){}
* ____________________________________________________________
* Constructor Stadium Object
* ___________________________________________________________
* PRE-CONDITIONS
* -None
* POST-CONDITIONS
* -Stadium object is created
* -Member values uninitialized
***************************************************************/
Stadium::Stadium(){}

/**************************************************************
* Stadium::Stadium(){}Stadium::Stadium(string stadium, string team, string address,
                 string phone,Date2 open, int capacity, string city,
                 string state, string zip, bool american, bool national,
                 bool grass, double latitude, double longitude):
                _stadium(stadium),_team(team),_address(address),
                _phone(phone),_open(open),_capacity(capacity),
                _city(city),_state(state),_zip(zip), _american(american),
                _national(national), _grass(grass), _lat(latitude),
                _long(longitude){}
 ____________________________________________________________
* Constructor Stadium Object with initialized values
* ___________________________________________________________
* PRE-CONDITIONS
* -Capacity is non negative
* -Team name is valid
* -Stadium name is valid
* -Address is valid
* -Phone number is valid
* -Latitude is valid
* -Longitude is valid
* -City name is Valid
* -State name is valid
* POST-CONDITIONS
* -Stadium object is created
* -Member values initialized
* -Capacity is non negative
* -Team name is initialized
* -Stadium name is initialized
* -Address is initialized
* -Phone number is initialized
* -Latitude is initialized
* -Longitude is initialized
* -City name is initialized
* -State name is initialized
***************************************************************/
Stadium::Stadium(string stadium, string team, string address,
                 string phone,Date2 open, int capacity, string city,
                 string state, string zip, bool american, bool national,
                 bool grass, double latitude, double longitude):
                _stadium(stadium),_team(team),_address(address),
                _phone(phone),_open(open),_capacity(capacity),
                _city(city),_state(state),_zip(zip), _american(american),
                _national(national), _grass(grass), _lat(latitude),
                _long(longitude){}

