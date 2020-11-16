#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>
#include "one_d_array.h"

using namespace std;

/*******************************************************************
 * VECTOR CLASS
 * This a customized vector class using arrays, includes the standard
 * vector functions + a few more, includes big 3
 *
 ******************************************************************/

template <class T>
class Vector
{

public:
    Vector(int capacity = 3);

    // big three:
    Vector(const Vector& other);
    ~Vector();
    Vector& operator =(const Vector& v);

    // push and pop functions:
    Vector& operator +=(const T& item);  // push_back
    void push_back(const T& item);       // append item at the end
    T pop_back();                        // remove the last item and return it
    void clear();

    //Insert and Erase:
    void insert(int insert_here, const T& insert_this); //insert at pos
    void erase(int erase_index);        //erase item at position
    int index_of(const T& item);        //search for item. retur index.

    // member access functions:
    const T& operator [](int index) const;
    T& operator [](int index);
    const T& at (int index) const;
    T& at (int index);
    const T& front() const;
    const T& back() const;


    // size and capacity:
    void set_size(int size);    // set the vecrot to desired size
    void set_capacity(int capacity);  // allocate this space

    int size() const {return _size;}
    int get_capacity() const {return _capacity;}
    T* get_vector() const {return _v;}

    bool empty() const;   // return true if the vector is empty

    template <class U>
    friend ostream& operator <<(ostream& outs, const Vector<U>& print_me);

private:
    int _size;
    int _capacity;
    T* _v;

};

/*******************************************
 * Vector(int capacity = 3);
 * Constuctor : Vector object constructed
 * Parameters : Integer capacity
 * Return     : none
 ******************************************/
/*******************************************
 * Vector(const Vector& other);
 * Constuctor : Object constructor
 * Parameters : Vector Object
 * Return     : None
 ******************************************/
/*******************************************
 * ~Vector();
 * Constuctor : Destructor object
 * Parameters : None
 * Return     : None
 ******************************************/
/*******************************************
 * Vector& operator =(const Vector& v);
 * Mutator    : Assignment Operator
 * Parameters : Vector object
 * Return     : Vector object
 ******************************************/
/*******************************************
 * Vector& operator +=(const T& item);
 * Mutator    : Adds item to vector
 * Parameters : T object
 * Return     : Vector object
 ******************************************/
/*******************************************
 * void push_back(const T& item);
 * Mutator    : Appends item to end
 * Parameters : T item
 * Return     : None
 ******************************************/
/*******************************************
 * T pop_back();
 * Mutator    : Removes item at end
 * Parameters : None
 * Return     : T object that was removed
 ******************************************
 * void insert(int insert_here, const T& insert_this);
 * Mutator    : Inserts object at specified location
 * Parameters : Location of insertion and object to be inserted
 * Return     : None
 ******************************************/
/*******************************************
 * void erase(int erase_index);
 * Mutator    : Erases item at index
 * Parameters : Location of erase
 * Return     : None
 ******************************************/
/*******************************************
 * int index_of(const T& item);
 * Mutator    : Returns location of item
 * Parameters : Item object
 * Return     : Index
 ******************************************/
/*******************************************
 * void set_size(int size);
 * Mutator    : Sets size of vector
 * Parameters : Size of vector
 * Return     : None
 ******************************************/
/*******************************************
 * void set_capacity(int capacity);
 * Mutator    : Sets capacity of vector
 * Parameters : Size of capacity
 * Return     : None
 ******************************************/
/*******************************************
 *const T& operator [](int index) const;
 * Accessor   : Bracket operator
 * Parameters : Index at vector
 * Return     : T Object
 ******************************************/
/*******************************************
 * T& operator [](int index);
 * Accessor   : Bracket operator
 * Parameters : Index at vector
 * Return     : T Object
 ******************************************/
/*******************************************
 * const T& at (int index) const;
 * Accessor   : at operator
 * Parameters : Index at vector
 * Return     : T Object
 ******************************************/
/*******************************************
 * T& at (int index);
 * Accessor   : at operator
 * Parameters : Index at vector
 * Return     : T Object
 ******************************************/
/*******************************************
 * const T& front() const;
 * Accessor   : Front operator
 * Parameters : Index at vector
 * Return     : T Object
 ******************************************/
/*******************************************
 * const T& back() const;
 * Accessor   : Back operator
 * Parameters : Index at vector
 * Return     : T Object
 ******************************************/
/*******************************************
 * int size() const {return _size;}
 * Accessor   : Size of vector
 * Parameters : None
 * Return     : Integer size
 ******************************************/
/*******************************************
 * int get_capacity() const {return _capacity};
 * Accessor   : Return capacity of vector
 * Parameters : None
 * Return     : Integer of capacity
 ******************************************/
/*******************************************
 * T* get_vector() const {return _v;}
 * Accessor   : Return vector
 * Parameters : None
 * Return     : Vector Object type T
 ******************************************/
/*******************************************
 * bool empty() const;
 * Accessor   : Checks if vector is empty
 * Parameters : None
 * Return     : Boolean Value
 ******************************************/


/**************************************************************
* Vector<T>::Vector(int capacity)
* ____________________________________________________________
* Constructs vector with set capacity
* ___________________________________________________________
* PRE-CONDITIONS
* -Capacity is nonnegative
* POST-CONDITIONS
* -Vector is not null
* -Vector's capacity is set
* -Size is set to 0
***************************************************************/
template <class T>
Vector<T>::Vector(int capacity)
{
    set_size(0);
    set_capacity(capacity);
}

/**************************************************************
* Vector<T>::Vector(const Vector& other)
* ____________________________________________________________
* Constructor Object
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size is set
* -Capcity is set
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
Vector<T>::Vector(const Vector& other)
{
    set_size(other.size());
    set_capacity(other.get_capacity());

    copy_list(_v, other._v, _size);
}

/**************************************************************
* Vector<T>::~Vector()
* ____________________________________________________________
* Destructor for vector
* ___________________________________________________________
* PRE-CONDITIONS
* -None
* POST-CONDITIONS
* -Vector is deleted
* -Pointer is NULL
***************************************************************/
template <class T>
Vector<T>::~Vector()
{
    delete[] _v;
    _v = nullptr;
}

/**************************************************************
* Vector<T>& Vector<T>::operator =(const Vector& v)
* ____________________________________________________________
* Assignment operator
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size is set
* -Capcity is set
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
Vector<T>& Vector<T>::operator =(const Vector& v)
{
    if(this == &v)
    {
        return *this;
    }

    delete [] _v;
    _v = nullptr;

    set_size(v.size());
    set_capacity(v.get_capacity());

    copy_list(_v, v._v, _size);

    return *this;
}

/**************************************************************
* Vector<T>& Vector<T>::operator +=(const T& item)
* ____________________________________________________________
* Uses add entry function
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size is incremented
* -Capcity is set
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
Vector<T>& Vector<T>::operator +=(const T& item)
{
    _v = add_entry(_v, item, _size, _capacity);
    return *this;
}

/**************************************************************
* void Vector<T>::push_back(const T& item)
* ____________________________________________________________
* Uses add_entry function to add to vector
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size is incremented
* -Capcity is set
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
void Vector<T>::push_back(const T& item)
{
    _v = add_entry(_v, item, _size, _capacity);
}

/**************************************************************
* T Vector<T>::pop_back()
* ____________________________________________________________
* Uses get oned and remove entry function
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size is decremented
* -Capcity is set
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
T Vector<T>::pop_back()
{

    T lastElement = get_oned(_v, _size - 1);
    _v = remove_entry(_v, _size, _capacity);

    return lastElement;
}

/**************************************************************
* void Vector<T>::clear()
* ____________________________________________________________
* Uses popback function in a forloop
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size is 0
* -Capcity is 0
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
void Vector<T>::clear()
{
    for (int i = 0; i < _size; i++)
        pop_back();
}

/**************************************************************
* void Vector<T>::insert(int insert_here, const T& insert_this)
* ____________________________________________________________
* Uses insert Element
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size is incremented
* -Capcity is set
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
void Vector<T>::insert(int insert_here, const T& insert_this)
{
    _v = insertElement(_v, insert_this, _size, _capacity, insert_here);
}

/**************************************************************
* void Vector<T>::erase(int erase_index)
* ____________________________________________________________
* Calls next element in a for lop
* ___________________________________________________________
* PRE-CONDITIONS
* -Erases item at index
*
* POST-CONDITIONS
* -Item erased
* -Size decremented
* -Items shifted left
***************************************************************/
template <class T>
void Vector<T>::erase(int erase_index)
{
    //_v = deleteElement(_v, _size, _capacity, erase_index);

    for (T* i = _v + erase_index; i < _v + _size - 1; i++)
    {
        T* nextElement = i + 1;
        *i = *nextElement;
    }

    _size--;
}

/**************************************************************
* int Vector<T>::index_of(const T& item)
* ____________________________________________________________
* Searches for item and returns index
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
int Vector<T>::index_of(const T& item)
{
    T* itemPosition = search_oned(_v, item, _size);

    if(itemPosition == nullptr)
    {
        return -1;
    }

    return itemPosition - _v;
}

/**************************************************************
* const T& Vector<T>::operator [](int index) const
* ___________________________________________________________
* Uses get_oned function to return item at index
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
const T& Vector<T>::operator [](int index) const
{
    assert(index < _size);
    return get_oned(_v, index);
}

/**************************************************************
* T& Vector<T>::operator [](int index)
* ____________________________________________________________
* Uses get_oned function to return item
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
T& Vector<T>::operator [](int index)
{
    assert(index < _size);
    return get_oned(_v, index);
}

/**************************************************************
* const T& Vector<T>::at (int index) const
* ____________________________________________________________
* Uses get_oned function to return item
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
const T& Vector<T>::at (int index) const
{
    assert(index < _size);
    return get_oned(_v, index);
}

/**************************************************************
* T& Vector<T>::at (int index)
* ____________________________________________________________
* Returns item at specific index
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector object is not null
* -Vector size is not greater than capacity
* -Vector capacity is nonnegative
* -Vector size is nonnegative
* POST-CONDITIONS
* -Vector object is initialized with other vector object
* -Size and capacity are nonnegative
* -Size is not greater than capacity
***************************************************************/
template <class T>
T& Vector<T>::at (int index)
{
    assert(index < _size);
    return get_oned(_v, index);
}

/**************************************************************
* const T& Vector<T>::front() const
* ____________________________________________________________
* Returns item at front of vector
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector not null
* -size is not greater than capacity
* -size and capacity are nonnegative
* POST-CONDITIONS
* -Item at end is returned
* -size and capacity are untouched
* -Vector remains unaltered
***************************************************************/
template <class T>
const T& Vector<T>::front() const
{
    //assert(index < _size);
    return get_oned(_v, 0);
}

/**************************************************************
* const T& Vector<T>::back() const
* ____________________________________________________________
* Returns item at end of vector
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector not null
* -size is not greater than capacity
* -size and capacity are nonnegative
* POST-CONDITIONS
* -Item at end is returned
* -size and capacity are untouched
* -Vector remains unaltered
***************************************************************/
template <class T>
const T& Vector<T>::back() const
{
    //assert(index < _size);
    return get_oned(_v, _size - 1);
}

/**************************************************************
* void Vector<T>::set_size(int size)
* ____________________________________________________________
* Changes size to input value
* ___________________________________________________________
* PRE-CONDITIONS
* -Capacity is greater than size
* -vector is not null
* POST-CONDITIONS
* -Size is set
* -Capacity is greather than size
* -Size and capacity are nonnegative
* -Vector items remain untouched
***************************************************************/
template <class T>
void Vector<T>::set_size(int size)
{
    _size = size;
}

/**************************************************************
* void Vector<T>::set_capacity(int capacity)
* ____________________________________________________________
* Rellocates space for vector
* ___________________________________________________________
* PRE-CONDITIONS
* -Vector not null
* POST-CONDITIONS
* -Capacity is reallocated
* -Size is set
* -Capacity is set
* -Size and capacity are nonnegative
* -Vector is unintialized
***************************************************************/
template <class T>
void Vector<T>::set_capacity(int capacity)
{
    _capacity = capacity;
    _v = allocate_oned<T>(_capacity);
}

/**************************************************************
* bool Vector<T>::empty() const
* ____________________________________________________________
* Compares size with 0
* ___________________________________________________________
* PRE-CONDITIONS
* -Size must be nonnegative
* -Vector object not null
* POST-CONDITIONS
* -Boolean value output
* -Nothing is changed
***************************************************************/
template <class T>
bool Vector<T>::empty() const
{
    if (_size == 0)
    {
        return true;
    }

    return false;
}

/**************************************************************
* ostream& operator <<(ostream& outs, const Vector<U>& print_me)
* ____________________________________________________________
* Extraction operator
* ___________________________________________________________
* PRE-CONDITIONS
* -None
* POST-CONDITIONS
* -Item output
* -Outs object
***************************************************************/
template <class U>
ostream& operator <<(ostream& outs, const Vector<U>& print_me)
{
    outs << "[ ";
    print_oned(print_me.get_vector(), print_me.size(), outs);
    outs << "]" << endl;

    return outs;
}

#endif // VECTOR_H
