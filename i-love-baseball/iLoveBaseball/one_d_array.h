#ifndef ONE_D_ARRAY_H
#define ONE_D_ARRAY_H

#include <iostream>
#include <cassert>

using namespace std;
/*******************************************************************
 * One-D Array Class
 *
 * Functions for one-d arrays
 ******************************************************************/

template <class T>
T* allocate_oned(int size);

template <class T>
void init_oned(T* oned, int size, T init_item = T());

// allocate an oned array and initialize it with all default items
template <class T>
T* resize_oned(int size);

template <class T>
ostream& print_oned(T* oned, int size, ostream& outs);

template <class T>
T* search_oned(T* list, const T& find_me, int size);

template <class T>
void copy_list(T *dest, T* src, int many_to_copy);

template <class T>
T& get_oned(T* array, int index);

template <class T>
void append(T* array, int& size, const T& value);

template <class T>
void Swap(T &a, T &b);

// add at the end
template <class T>
T* add_entry(T* list, const T& new_entry,
                  int& size, int& capacity);

// remove at the end
template <class T>
T* remove_entry(T* list, int& size, int& capacity);

// insert at given index
template <class T>
T* insertElement(T* list, const T& new_entry,
                  int& size, int& capacity, int insert_here);

// delete at given index
template <class T>
T* deleteElement(T* list, int& size, int& capacity, int delete_here);

template <class T>
void shiftRight(T* list, int size, int startIndex);

template <class T>
void shiftLeft(T* list, int& size, int startIndex);

// check if the array capacity needs to be enlarged
template <class T>
T* checkToEnlarge(T* list, int& size, int& capacity);

// check if the array capacity needs to be reduced
template <class T>
T* checkToShorten(T* list, int& size, int& capacity);

/*******************************************
 * T* allocate_oned(int size);
 * Mutator    : Allocates size for the one-d array
 * Parameters : Size parameter
 * Return     : Returns pointer of array
 ******************************************/
/*******************************************
 * void init_oned(T* oned, int size, T init_item = T());
 * Mutator    : Initializes one-d array
 * Parameters : Pointer to array,
 *              Size of array,
 *              Item to initialize array
 * Return     : None
 ******************************************/
/*******************************************
 * T* resize_oned(int size);
 * Mutator    : Resize one-d array
 * Parameters : Integer size
 * Return     : Returns one-d array
 ******************************************/
/*******************************************
 * void append(T* array, int& size, const T& value);
 * Mutator    : Appends value to end of array
 * Parameters : Pointer to array,
 * Return     : None
 ******************************************/
/*******************************************
 * void Swap(T &a, T &b);
 * Mutator    : Swaps positions in the one-d array
 * Parameters : T type arguments
 * Return     : None
 ******************************************/
/*******************************************
 * T* add_entry(T* list, const T& new_entry,
                  int& size, int& capacity);
 * Mutator    : Adds entry into list
 * Parameters : Location of array,
 *              New item,
 *              size of array,
 *              capacity of array
 * Return     : Pointer to array
 ******************************************/
/*******************************************
 * T* remove_entry(T* list, int& size, int& capacity);
 * Mutator    : Removes an entry in the one-d array
 * Parameters : Pointer location to array,
 *              Size of array,
 *              Capacity of array
 * Return     : Pointer to location of array
 ******************************************/
/*******************************************
 * T* insertElement(T* list, const T& new_entry,
                  int& size, int& capacity, int insert_here);
 * Mutator    : Inserts element into array
 * Parameters : Pointer to array,
 *              Item that is to be inserted,
 *              Size of array,
 *              Capacity of array,
 *              Position of insertion
 * Return     : Pointer to array
 ******************************************/
/*******************************************
 * T* deleteElement(T* list, int& size, int& capacity, int delete_here);
 * Mutator    : Deletes element of array
 * Parameters : Pointer to array location,
 *              Size of array,
 *              Capacity of array,
 *              Position of deletion
 * Return     : Pointer to array location
 ******************************************/
/*******************************************
 * void shiftRight(T* list, int size, int startIndex);
 * Mutator    : Shifts elements to the right
 * Parameters : Pointer to location of array,
 *              Size of array,
 *              Start at which shifting starts
 * Return     : None
 ******************************************/
/*******************************************
 * void shiftLeft(T* list, int& size, int startIndex);
 * Mutator    : Shifts elements to the left
 * Parameters : Pointer to location of array,
 *              Size of array,
 *              Start at which shifting starts
 * Return     : None
 ******************************************/
/*******************************************
 * T* checkToEnlarge(T* list, int& size, int& capacity);
 * Mutator    : Checks if array needs to be enlarged
 * Parameters : Pointer to location of array,
 *              Size of array,
 *              Capacity of array
 * Return     : Pointer of location of array
 ******************************************/
/*******************************************
 * T* checkToShorten(T* list, int& size, int& capacity);
 * Mutator    : Checks if array needs to be shortened
 * Parameters : Pointer to location of array,
 *              Size of array,
 *              Capacity of array
 * Return     : Pointer of location of array
 ******************************************/
/*******************************************
 * ostream& print_oned(T* oned, int size, ostream& outs);
 * Accessor   : Prints array
 * Parameters : Pointer to location of array,
 *              Size of array,
 *              ostream object
 * Return     : Ostream
 ******************************************/
/*******************************************
 * T* search_oned(T* list, const T& find_me, int size);
 * Accessor   : Searches array for item
 * Parameters : Pointer to location of array,
 *              item that is desired,
 *              size of array
 * Return     : Pointer of array
 ******************************************/
/*******************************************
 * void copy_list(T *dest, T* src, int many_to_copy);
 * Accessor   : Copies list to another list
 * Parameters : Destination pointer,
 *              Source pointer,
 *              number of elements to copy
 * Return     : None
 ******************************************/

template <class T>
/**
 * @brief find the value if already exist in the array, if so return the
 * location of that character, if not return the nullptr
 * @param list
 * @param find_me the value to be found
 * @param size
 * @return the pointer consiting of the location of the value to be found in
 * the array, if not found, return the nullptr
 */

/**************************************************************
* T* search_oned(T* list, const T& find_me, int size)
* ____________________________________________________________
* Uses for-loop and checks with key
* ___________________________________________________________
* PRE-CONDITIONS
* -List is not null
* -List is not empty
* -Size does not equal 0
* POST-CONDITIONS
* -Location is returned
* -Array not altered
***************************************************************/
T* search_oned(T* list, const T& find_me, int size)
{
    for (int i = 0; i < size; i++)
    {
        // if found
        if (*list == find_me)
        {
            return list;
        }
        list++;

    }

    // if not found
    return nullptr;
}


template <class T>
/**
 * @brief print_oned array
 * @param oned array
 * @param size of the oned array
 * @param outs
 * @return outs
 */
/**************************************************************
* ostream& print_oned(T* oned, int size, ostream& outs)
* ____________________________________________________________
* Uses for-loop and returns to ostream object
* ___________________________________________________________
* PRE-CONDITIONS
* -list is not NULL
* -Size is greater than zero
* POST-CONDITIONS
* -Array not altered
* -Elements in array are printed
***************************************************************/
ostream& print_oned(T* oned, int size, ostream& outs)
{
    for (int i = 0; i < size; i++)
    {
        outs << *oned << " ";
        oned++;
    }

    return outs;
}

template <class T>
/**
 * @brief allocate_oned array
 * @param size to be allocated
 * @return the allocated oned array
 */
/**************************************************************
* T* allocate_oned(int size)
* ____________________________________________________________
* Returns array with new size
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -size is not zero
* POST-CONDITIONS
* -Array has junk values
* -Array with desired size is returned
***************************************************************/
T* allocate_oned(int size)
{
    return new T[size]();
}

template <class T>
/**
 * @brief init_oned array
 * @param oned
 * @param size
 * @param init_item to fill into the oned array
 */
/**************************************************************
* void init_oned(T* oned, int size, T init_item)
* ____________________________________________________________
* Initializes array with elements
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -size is not zero
* -Array is not NULL
* -element is the same type as array
* POST-CONDITIONS
* -Array is initialized with elements
* -All locations are set to the element
* -Array is altered
***************************************************************/
void init_oned(T* oned, int size, T init_item)
{
    for (int i = 0; i < size; i++)
    {
        *oned = init_item;
        oned++;
    }
}

template <class T>
/**
 * @brief add_entry adding a new value to the end of the array and re-allocate
 * the capacity if needed
 * @param list
 * @param new_entry to be added
 * @param size
 * @param capacity
 * @return the array with the value being added
 */
/**************************************************************
* T* add_entry(T* list, const T& new_entry,
                  int& size, int& capacity)
* ____________________________________________________________
* Checks if enlargement is necessary
* Then uses append function to add element into array
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* -element is the same type as array
* POST-CONDITIONS
* -Element is added to array
* -Array is altered
***************************************************************/
T* add_entry(T* list, const T& new_entry,
                  int& size, int& capacity)
{
    T* temp = checkToEnlarge(list, size, capacity);

    // add the new_entry to the end of the new array temp
    append(temp, size, new_entry);

    return temp;
}


template <class T>
/**
 * @brief insertElement to a specific index
 * @param list
 * @param new_entry
 * @param size
 * @param capacity
 * @param insert_here the index to insert new element
 * @return the new array with the new entry being inserted
 */
/**************************************************************
* T* insertElement(T* list, const T& new_entry,
*                 int& size, int& capacity, int insert_here)
* ____________________________________________________________
* Inserts by shifting right and inserting element into array
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* -element is the same type as array
* POST-CONDITIONS
* -Element is added to array
* -Array is altered
* -Element is added in specific location
***************************************************************/
T* insertElement(T* list, const T& new_entry,
                  int& size, int& capacity, int insert_here)
{
    assert(insert_here <= size);

    // check to see if needs to expand the capacity of the array
    T* temp = checkToEnlarge(list, size, capacity);

    // shift all the numbers from the insert_here index to the right up
    // 1 index
    shiftRight(temp, size, insert_here);

    T* indexToInsert = temp + insert_here;

    *indexToInsert = new_entry;

    return temp;
}

template <class T>
/**
 * @brief shiftRight shifts the numbers to right of 1 index starting
 * from the startIndex
 * @param list
 * @param size
 * @param startIndex to shift the numbers
 */
/**************************************************************
* void shiftRight(T* list, int size, int startIndex)
* ____________________________________________________________
* shifts elments by startindex
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* -element is the same type as array
* -Start index is not greater than size of array
* POST-CONDITIONS
* -Element is added to array
* -Array is altered
* -Element is added in specific location
* -size is incremented
***************************************************************/
void shiftRight(T* list, int size, int startIndex)
{
    for (T* i = list + size; i > list + startIndex; i--)
    {
        T* previousElement = i - 1;
        *i = *previousElement;
    }
}

template <class T>
/**
 * @brief checkToEnlarge check to see if the capacity needs to be
 * expanded, if so reallocate a new array with double the capacity
 * @param list
 * @param size
 * @param capacity
 * @return the array
 */
/**************************************************************
* T* checkToEnlarge(T* list, int& size, int& capacity)
* ____________________________________________________________
* Checks for size and capacity and enlarges array if needed
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* POST-CONDITIONS
* -capacity is enlarged to twice of the size
***************************************************************/
T* checkToEnlarge(T* list, int& size, int& capacity)
{
    T* temp = list;

    // check if the size exceeds the capacity
    if (size >= capacity)
    {
        // double the capacity
        capacity *= 2;

        // re-allocate a new array with doubled capacity
        temp = allocate_oned<T>(capacity);
        // copy all the value from the original list to the new array temp
        copy_list(temp, list, size);

        // deallocate the old array list
        delete[] list;
        list = nullptr;
    }

    return temp;
}


template <typename T>
/**
 * @brief append the value to the end of the array
 * @param array
 * @param size
 * @param value to be appended
 */
/**************************************************************
* void append(T* array, int& size, const T& value)
* ____________________________________________________________
* Adds element to end of array
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* POST-CONDITIONS
* -Element is added to end of array
* -size is incremented
* -Used in insertelement
***************************************************************/
void append(T* array, int& size, const T& value)
{
    // the pointer points to the end of the array which is the location one
    // after the last element
    T* endPointer = array + size;
    *endPointer = value;
    size++;
}

template <class T>
/**
 * @brief checkToShorten check to see if needs to decrease the capacity
 * if so reallocate a new array with half of the original capacity
 * @param list
 * @param size
 * @param capacity
 * @return the array
 */
/**************************************************************
* T* checkToShorten(T* list, int& size, int& capacity)
* ____________________________________________________________
* Compares size and capacity and divides capacity by two if needed
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* POST-CONDITIONS
* -Capacity is divided by two
* -Size is half of capacity
***************************************************************/
T* checkToShorten(T* list, int& size, int& capacity)
{
    T* temp = list;

    // to check if the size is less than or equal to one fourth of the capacity
    if(size <= capacity / 4)
    {
        // decrease the capcity by half
        capacity /= 2;

        // re-allocate a new array
        temp = allocate_oned<T>(capacity);
        // copy all the value from the old array list to the new one temp
        copy_list(temp, list, size);

        // deallocate the old array
        delete[] list;
        list = nullptr;
    }

    return temp;
}

template <class T>
/**
 * @brief shiftLeft shifts the elements within the array to left of 1
 * index
 * @param list
 * @param size
 * @param startIndex
 */
/**************************************************************
* void shiftLeft(T* list, int size, int startIndex)
* ____________________________________________________________
* shifts elments by startindex
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* -element is the same type as array
* -Start index is not greater than size of array
* POST-CONDITIONS
* -Element is added to array
* -Array is altered
* -Element is added in specific location
* -size is incremented
***************************************************************/
void shiftLeft(T* list, int& size, int startIndex)
{
    for (T* i = list + startIndex; i < list + size - 1; i++)
    {
        T* nextElement = i + 1;
        *i = *nextElement;
    }

    size--;
}

template <class T>
/**
 * @brief deleteElement from a specified index
 * @param list
 * @param size
 * @param capacity
 * @param delete_here the index to be deleted
 * @return the array
 */
/**************************************************************
* T* deleteElement(T* list, int& size, int& capacity, int delete_here)
* ____________________________________________________________
* Uses shift left function to delete an element
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* -element is the same type as array
* -Start index is not greater than size of array
* POST-CONDITIONS
* -Element is removed from array
* -Size is decremented
* -Uses check to shorten, and divides capacity if needed
***************************************************************/
T* deleteElement(T* list, int& size, int& capacity, int delete_here)
{
    assert(delete_here < size);

    shiftLeft(list, size, delete_here);

    // check to see if needs to decrease the capacity after shifting
    return checkToShorten(list, size, capacity);
}

template <class T>
/**
 * @brief remove_entry element within the array
 * @param list
 * @param size
 * @param capacity
 * @return the array
 */
/**************************************************************
* T* remove_entry(T* list, int& size, int& capacity)
* ____________________________________________________________
* Removes element from end of array
* ___________________________________________________________
* PRE-CONDITIONS
* -size is positive
* -Array is not NULL
* -size is not greater than capacity
* -element is the same type as array
* -Start index is not greater than size of array
* POST-CONDITIONS
* -Element is removed from end of array
* -Size is decremented
* -Uses check to shorten, and divides capacity if needed
***************************************************************/
T* remove_entry(T* list, int& size, int& capacity)
{
    size--;  // decrease the size to delete the last element

    // check to see if needs to decrease the capacity
    return checkToShorten(list, size, capacity);
}

template <class T>
/**
 * @brief swap the values of the two numbers
 * @param a the first number
 * @param b the second number
 */

/**************************************************************
* void Swap(T &a, T &b)
* ____________________________________________________________
* Swaps elements
* ___________________________________________________________
* PRE-CONDITIONS
* -a is a valid value
* -b is a valid value
* POST-CONDITIONS
* -Elements a and b are swapped
***************************************************************/
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
/**
 * @brief copy the content from the src array to dest array
 * @param dest array for the content to be copied to
 * @param src array for the content to b e copied from
 * @param many_to_copy of the array
 */
/**************************************************************
* void copy_list(T *dest, T* src, int many_to_copy)
* ____________________________________________________________
* Uses for-loop for destination and source
* ___________________________________________________________
* PRE-CONDITIONS
* -Destination is not NULL
* -Source is not NULL
* -sizes are not zero for source
* POST-CONDITIONS
* -Destination array is copied over
* -Source array is not altered
* -Destination size and capacity are the same as size
***************************************************************/
void copy_list(T *dest, T* src, int many_to_copy)
{
    for (int i = 0; i < many_to_copy; i++)
    {
        *dest = *src;

        // moves to the next element
        dest++;
        src++;
    }
}

template <class T>
/**
 * @brief get_oned
 * @param array
 * @param index
 * @return the element at the specified index
 */
/**************************************************************
* T& get_oned(T* array, int index)
* ____________________________________________________________
* Returns element at specified index
* ___________________________________________________________
* PRE-CONDITIONS
* -Array is not NULL
* -Index is within size
* POST-CONDITIONS
* -element of array is returned
* -element in array is not altered
* -size and capacity is not altered
***************************************************************/
T& get_oned(T* array, int index)
{
    return *(array + index);
}

/**************************************************************
* T* resize_oned(int size)
* ____________________________________________________________
* Resizse oned array by reallocating size and initilizing array
* ___________________________________________________________
* PRE-CONDITIONS
* -Array is not NULL
* -Index is within size
* POST-CONDITIONS
* -element in array is not altered
* -capacity of array is altered to size
***************************************************************/
template <class T>
T* resize_oned(int size)
{
    T* temp = allocate_oned<T>(size);
    init_oned(temp, size);

    return temp;
}






#endif // ONE_D_ARRAY_H
