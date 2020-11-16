#ifndef READINPROGRAMS_H
#define READINPROGRAMS_H
#include <vector>
#include <iostream>
#include "linkedlist.h"
#include "stadium.h"
#include "souvenir.h"
#include "container.h"

//All produce a list of stadiums

LinkedList<Stadium*> Stadiums();
LinkedList<Stadium*> StadiumsByTeamName();
LinkedList<Stadium*> StadiumsByAmericanTeams(); //done
LinkedList<Stadium*> StadiumsByNationalTeams(); //done
LinkedList<Stadium*> GrassStadiumsByTeamName();
LinkedList<Stadium*> StadiumsByDate();
container<souvenir*> Souvenirs();

#endif // READINPROGRAMS_H

/*****************************************************************
 *
 * Read In Programs
 * _______________________________________________________________
 * This is a collection of functions that reads in from allstadiumsreadin.txt
 * and inserts stadiums into respective linked lists.
 * For souvenir, it reads from souvenirs.txt and returns a container.
 ******************************************************************/
