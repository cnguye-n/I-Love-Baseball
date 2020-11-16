#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template<typename T>
class container
{
public:
    /*****************
    ** CONSTRUCTOR **
    ******************/
    container();
    container(vector<T> l);
    container(const container& c);

    /***************
    ** ACCESSORS **
    ****************/
    int size();
    int index_of(T entry);
    T& at(int index);

    /***************
    ** MUTATOR **
    ****************/
    container& insert(int index, T entry);
    container& attach(T entry);
    bool remove(T entry);
    bool remove_all(T entry);
    bool remove(int index, T entry);
    container& sort();
    void swap(int index, int index2);
    void clear();

private:
    vector <T> _l;  // list to store data
    int _size;      // size of the list
};

/****************************************************************
* Container : a container class that is able to store a list of
*   data and has the ability to modify, sort, insert, etc
*
***************************************************************/

/******************************
*******   CONSTRUCTOR  ********
******************************/

/****************************************************************
* container()
*
* This is the default constructor of container class that initialize
*   size variable
* --------------------------------------------------------------
* Parameters: none
* --------------------------------------------------------------
* Return: none
***************************************************************/
template<typename T>
container <T>::container():_size(0){}

/****************************************************************
* container(vector<T> l)
*
* This is the parametrized constructor of container class that
*   initialize size variable and list
* --------------------------------------------------------------
* Parameters: vector<T> l - given list to initialie with
* --------------------------------------------------------------
* Return: none
***************************************************************/
template<typename T>
container <T>::container(vector<T> l):_l(l), _size(l.size()){}

/****************************************************************
* container(const container& c)
*
* This is the copy constructor of container class that
*   initialize the class with given container class property
* --------------------------------------------------------------
* Parameters: const container& c - given container class to
*                                   initialie with
* --------------------------------------------------------------
* Return: none
***************************************************************/
template<typename T>
container <T>::container(const container& c):_l(c._l), _size(c._size){};

/****************************************************************
* size()
*
* This function returns the size of current list
* --------------------------------------------------------------
* Parameters: none
* --------------------------------------------------------------
* Return: the size of the list that stores data
***************************************************************/
template<typename T>
int container <T>::size()
{
    return _size;
}

/****************************************************************
* index_of(T entry)
*
* This function finds the index of a given data value
* --------------------------------------------------------------
* Parameters: T entry   -   given data value to find
* --------------------------------------------------------------
* Return: the index of given data value
***************************************************************/
template<typename T>
int container<T>::index_of(T entry)
{
    // search thru the list
    for(int i=0; i<_l.size(); i++)
        if(_l.at(i) == entry)
            return i;

    // if item is not found, return -1 instead
    return -1;
}

/****************************************************************
* insert(int index, T entry)
*
* This function inserts a given data value at a given position
* --------------------------------------------------------------
* Parameters: T entry   -   given data value to insert
*             int index -   given position to add to
* --------------------------------------------------------------
* Return: the container class itself
***************************************************************/
template<typename T>
container<T>& container <T>::insert(int index, T entry)
{
    // use the insert function of vector
    _l.insert(_l.begin()+index, entry);
    _size++;
    return *this;
}

/****************************************************************
* attach(T entry)
*
* This function attatch a given data value to the end of list
* --------------------------------------------------------------
* Parameters: T entry   -   given data value to attatch
* --------------------------------------------------------------
* Return: the container class itself
***************************************************************/
template<typename T>
container<T>& container <T>::attach(T entry)
{
    // use push back function of vector
    _l.push_back(entry);
    _size++;
    return *this;
}

/****************************************************************
* remove(T entry)
*
* This function remove the given data value from the list
* --------------------------------------------------------------
* Parameters: T entry   -   given data value to remove
* --------------------------------------------------------------
* Return: true if given data value is successfully removed
***************************************************************/
template<typename T>
bool container<T>::remove(T entry)
{
    // search for the given data value first
    int index = index_of(entry);

    if(index == -1)
        return false;
    else
    {
        // call remove function and shrink size by 1
        _l.erase(_l.begin()+index);
        _size--;
        return true;
    }
}

/****************************************************************
* remove_all(T entry)
*
* This function remove the all of thegiven data value that exist in
*  the list
* --------------------------------------------------------------
* Parameters: T entry   -   given data value to remove
* --------------------------------------------------------------
* Return: true if given data value is successfully removed
***************************************************************/
template<typename T>
bool container<T>::remove_all(T entry)
{
    return remove(0, entry);
}

/****************************************************************
* remove(int index, T entry)
*
* This function remove the all of thegiven data value that exist in
*  the list from a certain index
* --------------------------------------------------------------
* Parameters: T entry   -   given data value to remove
*             int index -   given starting index to remove
* --------------------------------------------------------------
* Return: true if given data value is successfully removed
***************************************************************/
template<typename T>
bool container<T>::remove(int index, T entry)
{
    int temp = _l.size();

    // start from the given index, and remove all found data value
    for(int i=index; i<_l.size(); i++)
    {
        if(entry == _l[i])
            _l.erase(i);
        i--;
    }

    // check if anything is removed
    return temp == _l.size() ? true : false;
}

/****************************************************************
* container<T>::sort()
*
* This function sorts the list using the method of selection sort
* --------------------------------------------------------------
* Parameters: none
* --------------------------------------------------------------
* Return: the class itself
***************************************************************/
template<typename T>
container<T>& container<T>::sort()
{
    // use method of selection sort to look for smaller value from current index
    for(int i=0; i<_l.size(); i++)
        for(int j=i; j<_l.size(); j++)
            if(*(_l.at(j)) < *(_l.at(i)))
                swap(i, j);
}

/****************************************************************
* at(int index)
*
* This function gives the access to the data value locates at
*   given index
* --------------------------------------------------------------
* Parameters: int index -   given index to access to
* --------------------------------------------------------------
* Return: reference to the desire data
***************************************************************/
template<typename T>
T& container<T>::at(int index)
{
    return _l.at(index);
}

template<typename T>
void container<T>::clear()
{
    _l.clear();
    _size = 0;
}

/****************************************************************
* swap(int index, int index2)
*
* This function swaps the data at given two index locations
* --------------------------------------------------------------
* Parameters: int index  -   given first index to swap
*             int index2 -   given second index to swap
* --------------------------------------------------------------
* Return: None
***************************************************************/
template<typename T>
void container<T>::swap(int index, int index2)
{
    assert(index < _l.size() && index2 < _l.size());
    T temp;

    // swapping algorithm
    temp = _l.at(index);
    _l.at(index) = _l.at(index2);
    _l.at(index2) = temp;
}

#endif // CONTAINER_H
