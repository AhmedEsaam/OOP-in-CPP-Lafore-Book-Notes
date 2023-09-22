#include <iostream>
#include <cmath> // for fmod()
using namespace std;

/* PASSING BY REFERENCE ............................................................ */

void intfrac(float num, float &intPart, float &fracPart);
//  &: the 'ampersand' is used to mean (reference to ...).
// arguments here are 'aliases'  (different names) to the origional ones.

#if 0
int main(void)
{
    float num, intPart, fracPart;
    cout << "Enter a real number: ";
    cin >> num;
    intfrac(num, intPart, fracPart);
    cout.precision(2);
    cout << "Integer part: " << fixed << intPart << endl
         << "Fraction part: " << fixed << fracPart << endl;

    return 0;
}
#endif

/**
 *@brief Finds integer and fractional parts of real number
 *
 *@param num
 *@param intPart
 *@param fracPart
 */
void intfrac(float num, float &intPart, float &fracPart)
{
    long temp = static_cast<int>(num);
    intPart = static_cast<float>(temp);
    // fracPart = num - intPart;
    fracPart = fmod(num, 1);
}

/*
    References don't exist in C, where pointers serve a somewhat similar purpose (pass by address),
    although often less conveniently. Reference arguments were introduced into C++ to provide flexibility
    in a variety of situations involving objects as well as simple variables.
*/

/* OVERLOADED FUNCTIONS ...............................................................*/

// Different Numbers of Arguments
void repchar();
void repchar(char);
void repchar(char, int);

// Different Kinds of Arguments
struct Distance
{
    int feet;
    float inches;
};
void engdisp(Distance);
void engdisp(float);

/*
Overloaded functions can simplify the programmer's life by reducing the number of function
names to be remembered.
*/

/* INLINE FUNCTIONS ..................................................................*/

/*
    When the program is compiled, the function body is actually inserted into the
    program wherever a function call occurs.
*/

inline float lbs2kg(float pounds);
/* You should be aware that the inline keyword is actually just a request to the compiler.*/

inline float lbs2kg(float pounds)
{
    return 0.453592 * pounds;
}

/*
 * Pros:
 --------
    • The source file remains well organized and easy to read,
        since the function is shown as a separate entity.

    • Making normal functions with short body imposes just as much time penalty as a larger function.
        In fact, if a function is very short, the instructions necessary to call it may take up as much
        space as the instructions within the function body.

    • Betters function-like macros in that the compiler checks the typrs of the arguments.

    • You don't need to care about the paranthesis too much as with macros.

 * Cons:
 --------
    • Increased code size.
*/

/* DEFAULT ARGUMENTS ....................................................... */

void repchar2(char = '*', int = 45); // declaration with

#if 0
int main()
{
    repchar2();        // prints 45 asterisks
    repchar2('=');     // prints 45 equal signs
    repchar2('+', 30); // prints 30 plus signs
    return 0;
}
#endif

void repchar2(char ch, int n)   // defaults supplied
{                               // if necessary
    for (int j = 0; j < n; j++) // loops n times
        cout << ch;             // prints ch
    cout << endl;
}

/*
    Remember that missing arguments must be the trailing arguments—those at the end of the
    argument list.
*/

/* Benefits:
    • Useful if you don’t want to go to the trouble of writing arguments that,
        for example, almost always have the same value

    • useful in cases where, after a program is written, the programmer decides to increase
        the capability of a function by adding another argument (to the right).
        >> Meaning that the existing function calls can continue to use the old number of arguments,
            while new function calls can use more.
*/

/* SCOPE (visibility) & STORAGE CLASS (lifetime) ...................................... */

/* Scope:
    • Local scope:  Variables with local scope are visible only within a block.
    • File scope:   Variables with file scope are visible throughout a file.
    • Program Scope: Variables wirh program scope are visible throughout the entire program.

    Note:
        - A local variable is not created until the function in which it is defined is called.
        (More accurately, we can say that variables defined within any block of code are not
        created until the block is executed.

        - Limiting the visibility of variables helps organize and modularize the program.
        You can be confident that the variables in one function are safe from accidental
        alteration by other functions because the other functions can’t see them.

        - This is an important part of structured programming, the methodology for organizing
        old-fashioned procedural programs. Limiting visibility is also an important part of
        object-oriented programming.

*/

/* Storage Class:
    • Automatic:    Variables with storage class automatic exist during the lifetime of the function.
    • Static:       Variables with storage class static exist for the lifetime of the program.

    Note: The name automatic is used because the variables are automatically created when a function is
        called and automatically destroyed when it returns.
*/

/*
In the case of variables declared within a function, storage class and scope coincide: These
variables exist only while the function in which they are defined is executing, and are only visible
within that function. For some kinds of variables, however, lifetime and visibility are not the same.
*/

/* GLOBAL VARIABLES ..................................................*/

char ch = 'a'; // global variable ch

void putachar() // putachar() accesses ch
{
    cout << ch;
}
/*
    • The next kind of variable is global. While local variables are defined within functions, global
    variables are defined outside of any function. (They’re also defined outside of any class).

    • A global variable is visible to all the functions in a file (and potentially in other files).
    More precisely, it is visible to all those functions that follow the variable’s definition in
    the listing. Usually you want global variables to be visible to all functions, so you put their
    declarations at the beginning of the listing.
*/

/*
    Global variables have storage class (static), which means they exist for the life of the program.
    - Memory space is set aside for them when the program begins, and continues to exist until the
        program ends.
    - You don’t need to use the keyword static when declaring global variables;
        they are given this storage class automatically.

*/

/*
    Warning:
        * Global variables create organizational problems because they can be accessed by any function.
        * The wrong functions may access them, or functions may access them incorrectly.
        * In an object-oriented program, there is much less necessity for global variables.
*/

/* Initialization */

//  If a global variable is initialized, as in ...
int exvar = 199;
/*  this initialization takes place when the program is first loaded.
    If a global variable is not initialized explicitly by the program—for example,
    if it is defined as ... */
int exvar2;
/*  then it is initialized automatically to 0 when it is created.
    (This is unlike local variables, which are not initialized and probably contain random
    or garbage values when they are created.)
*/

/* STATIC LOCAL VARIABLES ............................................... */

/*
    Static local variables are used when it’s necessary for a function to remember a value when it
    is not being executed;
*/
/* Initialization:
    When static variables are initialized, as total and count are in getavg(), the initialization
    takes place only once.
*/

/* local variables and function arguments are stored on the stack, while global and static variables
are stored on the heap */

/*
    Storage Types:
    =============================================================================
                    Local               Static Local        Global
                    ------------------------------------------------
    • Visibility:   function            function            file
    • Lifetime:     function            program             program
    • Initialized:  not initialized     0                   0
    • Storage:      stack               heap                heap

    • Purpose:      Variables used      Same as local,      Variables used by
                    by a single         but retains value   several functions
                    function            when function
                                        terminates.
*/

/* RETURNING BY REFERENCE ..................................................... */

/*
    Besides passing values by reference, you can also return a value by reference as in "Virtual Functions".
    *   One reason is to avoid copying a large object.
    *   Another reason is to allow you to use a function call on the left side of the equal sign.
        (indispensable technique when it comes to "Operator Overloading").
*/

int x;
int &setx();

#if 1
int main(void)
{
    setx() = 92;
    cout << "x = " << x << endl;

    return 0;
}
#endif

int &setx()
{
    // returns an alias (reference) to a variable : (lvalue)
    return x; // Must be a global variable.
}

/* CONST FUNCTION ARGUMENTS ...................................*/

/*
    Suppose you have a function that only read the argument.
    >> You want to pass an argument by reference for efficiency,
        but you want a guarantee that the function cannot modify it.
*/

// you can apply the const modifier:
void aFunc(int &a, const int &b); // declaration

void aFunc(int &a, const int &b) // definition
{
    a = 107;        // OK
    // b = 111;     // error: can’t modify constant argument
}

/* Why to use const if we were careful not to modify the variable anyway?

    >> One of the design philosophies in C++ is that it’s better for the compiler to find errors
    than to wait for them to surface at runtime. 
    
    - The use of const function arguments is an example of this approach in action/
*/

/* Note:
    As (const int) is a different type from (int), 
        >> you can overload a function by using both in different function definitions. 
*/

/* Note:
    If you want to pass a const variable to a function as a reference argument, you don’t have a
    choice: It must be declared const in the function declaration.
    
    (There’s no problem passing a const argument by value, because the function can’t modify
    the original variable anyway.)
*/



