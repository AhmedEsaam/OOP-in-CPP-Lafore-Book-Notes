#include <iostream>

using namespace std;

/// <Templates>
/// TEMPLATE FUNCTIONS /////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------------------------------
/// A Simple Function Template ///....................................................:
// (the line starting with the keyword 'template' and the function definition following)
template <class T>      // T is called the template argument
T abs(T n)
{
    return (n < 0)? -n : n;
}

/// What Does The compiler Do ///
/*
    • The function template itself doesn’t cause the compiler to generate any code. 
        It can’t generate code because it doesn’t know yet what data Type the function will be working with.

    • Code generation doesn’t take place until the function is actually called (invoked) by a statement within the program.

    • Instantiating the function template:
        If the function is called with an int argument, it generates a specific version of the abs() function for this Type (int) 
        substituting int wherever it sees the name T in the function template. 
        This is called instantiating the function template.

    • The compiler is smart enough to generate only one version of abs() for each data Type.

*/

/// Simplifying the Listing ///
/*
    → The template approaches simply saves us from having to Type many separate functions into the source file. 
        This makes the listing shorter and easier to understand.
    → Also, if we want to change the way the function works, 
        we need to make the change in only one place in the listing instead of three places.

*/

/// Another Kind of Blueprint ///
/*
    Just like classes as blueprints for generating objects, 
    templete functions are blueprints for generating functions.

    They do not actually cause program code to be placed in memory.
*/

/// Does it work for all Types? ///
/*
    Does the template function find() works when using it to find a C-string in an array of C-strings?
    - well, the (==) operator does not work to compare two C-strings (you must use strcmp() library function), 
        so no, it does not. (However it will work for the 'string' class).

    • And, you must check if it works for the Types you intended to use it for.
*/  

/// when Writing a template Function, Start With a Normal Function ///
/*
    ... that works on a fixed Type (int. for example). 
    You can design and debug it without having to worry about template syntax and compatible data Types.
    Then, when everything works properly, you can turn the function definition into a template and check that it works for additional Types. 
*/ 


//-----------------------------------------------------------------------------------------------------
/// Function Templates With Multiple Arguments ///....................................................:
// this function returns index number of item, or -1 if not found
template <class aType>
int find(aType* array, int size, aType value)
{
    for(int j = 0; j < size; j++)
    {
        if(array[j] == value)
            return j;
    }
    return -1;
} 

/// Function Template Arguments Consistency ///
/*
    if you call this function, give all the same-template arguments only one Type.
    Because the compiler takes this one Type to generate the specific template function.
*/

/// Syntax Variation ///
//Some programmers put the template keyword and function declarator in the same line.
// but it's more forbidding and less clear.
template <class Typee> int find(Typee* arr, int size, Typee val);


//-----------------------------------------------------------------------------------------------------
/// Multi-Templates Arguments Function ///............................................................:
/* Suppose in the find() example the array could be large enough that
    you want to select the Type of the array size, 
    as well as the Type of data stored when you call the function. 
*/ 
template <class aType, class bType>
bType find(aType* array, bType size, aType value)
{
    for(bType j = 0; j < size; j++)
    {
        if(array[j] == value)
            return j;
    }
    return static_cast<bType>(-1);
}
/*
    • This can take up a lot of memory:
        if the functions are large. 
        
        - Note that multiple template arguments can lead to many functions being instantiated from a
        single template. Two such arguments, if there were six basic Types that could reasonably be
        used for each one, would allow the creation of 36 functions. 
        
        * But, you don’t instantiate a version of the function unless you actually call it.
*/

/// Why Not Macros?! ///
/*
    • There are several problems with them:
        One is that macros don’t perform any Type checking.

        → There may be several arguments to the macro that should be of the same Type, 
            but the compiler won’t check whether or not they are. 
        → Also, the Type of the value returned isn’t specified, 
            so the compiler can’t tell if you’re assigning it to an incompatible variable,
    

    • Avoid Macros:
        In any case, macros are confined to functions that can be expressed in a single statement. 
        There are also other, more subtle, problems with macros. On the whole it’s best to avoid them.
*/




/// CLASS TEMPLATES ////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
/// Abstracting the Data Storage (Containers) Classes ///....................................................:
/*
    If you made a Stack class to store int values, you need to make a new one for double values, and so on..
    So, you might want to abstract the idea of the specific data container (Stack for example).
*/
const int MAX = 100;
template <class Type>
class Stack
{
    private:
        Type st[MAX];                // stack array of any Type
        int top;                    // number of the top of the stack
    public:
        Stack()                     // constructor
            { top = -1; }
        void push(Type var)         // put a new object in stack         
            { st[++top] = var; }
        Type pop()                  // take number off the stack
            { return st[top--]; }
};

/* Class Templates Instantiating */
/*
    • Class templates differ from function templates in the way they are instantiated: 
        - To create an actual function from a function template, you call it using arguments of a specific Type.
        - Classes, however, are instantiated by defining an object using the template argument: Stack<float> s1; .

    • When instantiating a new class template: Stack<long> s2; 
        Compiler creates not only a different space for data, but also a new set of member functions that operate on Type long.
*/

/// If Class Template Member Functions Are Defined Externally ///
// The expression template<class Type> must precede not only the class definition, but each externally defined member function as well. 
template <class Type>
class Stack_2
{
     private:
        Type st[MAX];               // stack array of any Type
        int top;                    // number of the top of the stack
    public:
        Stack_2();                  // constructor
        void push(Type var);        // put a new object in stack
        Type pop();                 // take number off the stack
        Stack_2<Type> sorted();
};

template <class Type>
Stack_2<Type>::Stack_2()
{
    top = -1;
}

template <class Type>
void Stack_2<Type>::push(Type var)
{
    st[++top] = var;
}

template <class Type>
Type Stack_2<Type>::pop()
{
    return st[top--];
}

// If the externally defined member function is returning an object of this class class, you would write:
template <class Type>
Stack_2<Type> Stack_2<Type>::sorted()
{
    Type temp;
    for(int i = 0; i <= top; i++)
    {
        for(int j = 0; j <= top; j++)
        {
            if(st[i] > st[j])
            {
                temp = st[i];
                st[i] = st[j];
                st[j] = temp;
            }
        }
    }
    return *this;
}

/*
    Int<Type> Int<Type>::xfunc(Int arg)
    { }
    - The class name used as a type of a function argument, on the other hand, 
        doesn’t need to include the <Type> designation.
*/



/// A Linked list Class Using Templates ///
// Page 696 (722 / 1038) -to be continued ...


// main()
#if 0
//-----------------------------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    /// Template Functions //////////////////////////////////////////////////////////////
    /// A simple function template ///
    int int1 = 54;
    int int2 = -6;
    long lon1 = 70000L;
    long lon2 = -80000L;
    double dub1 = 9.45;
    double dub2 = -10.15;

    cout << "\nabs(" << int1 << " = \t" << abs(int1);
    cout << "\nabs(" << int2 << " = \t" << abs(int2);
    cout << "\nabs(" << lon1 << " = \t" << abs(lon1);
    cout << "\nabs(" << lon2 << " = \t" << abs(lon2);
    cout << "\nabs(" << dub1 << " = \t" << abs(dub1);
    cout << "\nabs(" << dub2 << " = \t" << abs(dub2);
    cout << endl;

    /// Function Templates With Multiple Arguments ///
    char chrArr[] = {1, 3, 5, 9, 11, 13};
    char ch = 5;

    int intArr[] = {1, 3, 5, 9, 11, 13};
    int in = 6;

    int lonArr[] = {1L, 3L, 5L, 9L, 11L, 13L};
    int lo = 11L;

    double dubArr[] = {1.0, 3.0, 5.0, 9.0, 11.0, 13.0};
    double db = 4.0;

    cout << "\n5 in chrArray: \t\tindex = " << find(chrArr, 6, ch);
    cout << "\n6 in intArray: \t\tindex = " << find(intArr, 6, in);
    cout << "\n11 in lonArray: \tindex = "  << find(lonArr, 6, lo);
    cout << "\n4 in dubArray: \t\tindex = " << find(dubArr, 6, db);
    cout << endl << endl;



    /// Template Classes //////////////////////////////////////////////////////////////
    Stack<float> s1;            // s1 is an object of class Stack<float>

    s1.push(1111.1F);           // push 3 floats, then pop them
    s1.push(2222.2F);
    s1.push(3333.3F);
    cout << "1: " << s1.pop() << endl;
    cout << "2: " << s1.pop() << endl;
    cout << "3: " << s1.pop() << endl;
    cout << endl;
    
    
    Stack<long> s2;

    s2.push(123123123L);           // push 3 longs, then pop them
    s2.push(234234234L);
    s2.push(345345345L);
    cout << "1: " << s2.pop() << endl;
    cout << "2: " << s2.pop() << endl;
    cout << "3: " << s2.pop() << endl;
    cout << endl;


    Stack_2<float> s3;
    
    s3.push(5.1F);
    s3.push(2.1F);
    s3.push(4.1F);

    Stack_2<float> s4;

    s4 = s3.sorted();               // sort s3 then pop its members 

    cout << "1: " << s4.pop() << endl;
    cout << "2: " << s4.pop() << endl;
    cout << "3: " << s4.pop() << endl;
    cout << endl;
    
    return 0;
}

#endif

//-----------------------------------------------------------------------------------------------------
/// <Exceptions>

/// Exceptions as a Finding-Errors Technique //////////////////////////////////////////////////////////////////
/*
    Exceptions are errors that occur at runtime. They are caused by a wide variety of exceptional circumstance, such as:
    • Running out of memory.
    • Not being able to open a file.
    • Trying to initialize an object to an impossible value.
    • Using an out-of-bounds index to a vector.

    → There is the problem of communicating errors from deep within class libraries
        (which is probably the most important problem solved by exceptions.)
*/

// How would C-language programs check for errors?
/*
    - You would make the function returns an enum value (like: Null, 0, OK, ERROR_ARGUMENT1_IS_WRONG, etc...) 
        and then make if-else statements on these returned values to check for correctness.

    But this leads to a lngthy code and in C++ cannot check for implicitly-called functions like constructors,
    and functions from class libraries which the end programmer did not write. 
*/

// So, in C++, how whould that go?
/*
    We'll play a throw-and-catch game:
        Any time the function finds an error it will 'throw' an exception,
        then, in the code you surround the call to this function with a 'try' block to 'catch' these exceptions they if happened.

    Meaning, we put an exception calss withing the public part of our class,
        - then, in our class member function, we throw an exception, using the keyword 'throw' followed by the exception class constructor function call,
        - then, in main() weenclose any statements that interact with objects of our class in a 'try' block,
        - if any of these statements causes an error, an exception will be thrown and catched in the 'catch' block.
*/

// I need to see an example:
#if 0
const int MAX_ = 3;

class Stack_3
{
private:
    int st[MAX_];
    int top;
public:
    class Range                 // exception class for Stack_3
    {                           // note: empty class body (in this example it's only needed to connect a throw statement with a catch block)

    };
    
    Stack_3()
    { top = -1; }
    
    void push(int var)
    {
        if(top >= MAX_ -1)      // if stack is full,
            throw Range();      // throw exception 
            /*
                The 'Range()' part:
                    → invokes the implicit constructor for the Range class, which creates an object of this class.
                The 'throw' part:
                    → transfers program control to the exception handler (catch block)                
            */
        st[++top] = var;        // put number on stack
    }

    int pop()
    {
        if(top < 0)             // if stack is empty,
            throw Range();      // throw exception
        return st[top--];
    }
};


int main(int argc, char const *argv[])
{
    Stack_3 stk;

    try
    {
        stk.push(11);
        stk.push(22);
        stk.push(33);
        stk.push(44);                           // oops: stack is full → control transfers to the exception handler (catch)
        cout << "1: " << stk.pop() << endl;
        cout << "2: " << stk.pop() << endl;
        cout << "3: " << stk.pop() << endl;
        cout << "4: " << stk.pop() << endl;     // oops: stack is empty → control transfers to the exception handler (catch)
    } 
    catch(Stack_3::Range)                       // the exception handler
    {
        cout << "Exception: Stack is Full or Empty" << endl;

        /* What happens then?
            • Program control falls through here, so you can continue processing at that point without an interruption despite the error occured, 
            • The exception handler may transfer control elsewher,
            • Or (often) terminates the program 
        */
    }

    cout << "Arrive here after catch (or normal exit)" << endl;
    
    
    return 0;
}

#endif



