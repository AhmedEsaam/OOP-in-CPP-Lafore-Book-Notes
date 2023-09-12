#include <iostream>
using namespace std;

/*
    Uses of pointers?
    • Accessing array elements
    • Passing arguments to a function when the function needs to modify the original argument
    • Passing arrays and strings to functions
    • Obtaining memory from the system
    • Creating data structures such as linked lists
*/
/** Note:
    But almost all of those applications can be performed without the use of pointers,
    However, in some situations pointers provide an essential tool for increasing the power of C++, as in:
    ► The creation of data structures such as 'linked lists' and 'binary trees',
    ► virtual functions,
    ► the 'new' operator,
    ► and the 'this' pointer.
*/


int main()
{
    int v1 = 26;
    cout << &v1 << endl;        // & var : address of var

    int* ptr = &v1;             // int * : a pointer to int
    cout << ptr << endl;
    cout << *ptr << endl;       // * ptr : dereference ptr 

    char *ptr1, *ptr2, *ptr3;   // defining multible pointers on the same line

    int v2 = *ptr;
    cout << v2 << endl;

    /* Note:
        The pointer must be given some value, or it will point to an addresss we don’t want it to point to.
        >> Rogue pointer values can result in system crashes and are difficult to debug.
        So, Make sure you give every pointer variable a valid address value before using it.
    */

    ///* To assign one kind of pointer type to another ....................:
    float flovar = 98.6;
    // int* ptrint = &flovar;   //ERROR: can’t assign float* to int*
    int *ptrint = reinterpret_cast<int*>(&flovar); 
    // Static casts won’t work with pointers. 
    // Old-style C casts can be used, but are always a bad idea in C++.


    ///* void pointers ....................................
    void *vptr;     // vptr can point to any data type.
                    // • Can be used to pass pointers to functions that operate
                    //   independently of the data type pointed to.
    int ivar;
    float fvar;
    vptr = &ivar;   // Ok
    vptr = &fvar;   // Ok
    

    ///* A capsule summary ................................:
    int v;      // defines variable v of type int
    float f;    // defines variable f of type float
    int* p;     // defines p as a pointer to int
    p = &v;     // assigns address of variable v to pointer p
    v = 3;      // assigns 3 to v
    *p = 3;     // also assigns 3 to v
    void* vp;   // defines vp as a pointer to void 
    vp = &v;    // assigns address of variable v to pointer vp
    vp = &f;    // assigns address of variable f to pointer vp
    p = reinterpret_cast<int*>(&f);    // assigns address of float variable f to the pointer to int p

    
    ///* Pointers and Arrays ................................:
    int i;
    int intArr[5] = {56, 62, 96, 45, 12};
    for (i = 0; i < 5; i++)
    {   cout << endl << *(intArr + i); } cout << endl;     // the name of an array is its address
    // The C++ compiler is smart enough (using the pointer type) to take the size of the data into account when
    //   it performs arithmetic on data addresses (here it increments by the size of int.)
    /* Note:
        Array name is a pointer constant NOT a pointer variable,
        Which means that it is the address where the system has chosen to place your array.
        intArr++;  is like  0x36466631++;
    */

    int *iArrptr = intArr;
    for (i = 0; i < 5; i++)
    {   cout << endl << *(iArrptr++); } cout << endl;
    // because iArrptr is a variable and not a constant, it can be incremented. 

    
    
    return 0;
}
