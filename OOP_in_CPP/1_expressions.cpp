#include <iostream>
using namespace std;


//// ♣ Lvalue and Rvalue ♣ ///////////////////////////////////////////////////////////////////////////////////:

int x = 5, y = 4; 

int& set_var(int& x_ref)
{   return x_ref; }

int get_value(int x)
{   return x; }

struct st
{
    int feets;
    float inches;
};

union un
{
    int var1;
    float var2;
};

class number
{
public:
    int size;
    number(int i = 0) : value(i) {}
    operator int() const { return value; }
    number& operator=(const number& n);
private:
    int value;
};

number operator+(const number& x, const number& y);


int main()
{
    number arr[10], obj(42);
    number *ptr;
    int& ref = x;

/* ♣ Lvalue and Rvalue ------------------------------------------------------------------------------:
/*
    ■ L-value
        ► is an expression that yields an object reference.
        ► always has a defined region of storage, so you can take its address.
        ► may appear as either left hand or right hand side of an assignment operator(=).
*/
    
    obj;    ptr;    st;     un;         // identifier of any type, pointer, structure, or union
    arr;                                // arry name is a pointer constant (an unmodifiable l-value)

    arr[0];         ptr[0];             // array subscript [] that does not evaluate to an array
    *arr;           *ptr;               // dereference (unary *) that does not refer to an array, provided that it isn't a function pointer
    obj.size = 7;   ptr->size = 7;      // member access (.) or through a pointer (->)
    obj = arr[0];                       // assignnment (=, +=, ...etc.)
    x++; x--; ++x; --x;                 // increment ++, decrement -- (they require an lvalue as their operand)
    set_var(x) = 5;                     // a function call that returns a reference
    (arr[5]);   (x);                    // an lvalue expression in paranthesis ()
    (x < y ? y : x) = 0;                // ternary operator. It's valid because the ternary expression preserves the "lvalue-ness" of both its possible return values
    static_cast<int const &>(ref);      // type cast to a reference type

    // ♦ Non-modifiable lvalues include :-
    // array names
    // const objects
    // structs and unions that contain const objects


/* ............................................................
    ■ R-value
        ► is an expression that is not an l-value (cannot have a value assigned to it) and is capable of returning a constant expression or value.
        ► does not necessarily have any storage associated with it.
        ► has no identifiable location in memory (i.e. having an address).
        ► can appear only on right but not on left hand side of an assignment operator(=).
*/

    5;      "sifi";     0xF62C5605;     // literals: numbers, strings, addresses, ...etc.
    number(10);                         // unnamed object
    5 + 2;      arr[0] + obj;           // results of most operators
    &obj;       &arr[0];                // address-of operator (which s require an lvalue as its lefthand operand)
    get_value(x);                       // function call that returns by value
    int(5.2);                           // type cast



/* ............................................................
    ■ ↔ coversion between lvalue and rvalue :-

        • An lvalue is converted implicitly to an rvalue when necessary, 
        but an rvalue cannot be implicitly converted to an lvalue */
    
// _______________________
/* lvalue → to rvalue: */

    /// • that's something perfectly legit and it happens quite often.
        x + y;                      // '+' takes rvalues as its operands, but x, y has undergone an implicit lvalue-to-rvalue conversion

// _______________________
/* rvalue → to lvalue: */

    /// • the programming language has been designed to prohibit such conversions.
        // int& vref = 10;          // Error: does not work, as the reference should point to an existing object in memory, but 10 is a numeric constant without a memory address.


    /// → What if you want to make a function that can take a reference or a vlaue?
        void fnc(int& x);
        // fnc(10);                 // Error: This does not work. (invalid rvalue to lvalue)

        // but there is a workaround! :-
        int temp = 10;              // create a temporary variable where to store the rvalue
        fnc(temp);                  // then pass it to the function
            // → Quite inconvenient when you just want to pass a number to a function, isn't it?

        // That's what GCC would say about the last two Errors:
            //♦ error: invalid initialization of non-const reference of type 'int&' from an rvalue of type 'int'  ♦//
            /*  GCC complains about the reference not being const, namely a constant.
                According to the language specifications, you are allowed to bind a const lvalue to an rvalue. */


        /// ♦ Const lvalue reference ♦ \\\

        // The problem with rvalues is that they are volatile and cannot be modified and having a reference to them is meaningless.
        // → What about making the reference itself is 'const', so what it refers to cannot be modified? 
        const int& vref = 10;       // works well!

        // - This makes possible the very common C++ idiom of accepting values by constant references into functions.
        void fncc(const int& x);
        fncc(10);                   // works well! (without the need for a temp. variable)

        // Now your reference points to something that exists for real (until it goes out of scope) 
        // and you can use it as usual, except for modifying the value it points to.


        /* Under the hood,
            the compiler creates an hidden variable for you (i.e. an lvalue) where to store the original literal constant, 
            and then bounds that hidden variable to your reference.
        */

        // the following...
        const int& Vref = 10;

        // ... would translate to:
        int __internal_unique_name = 10;
        const int& _Vref = __internal_unique_name;


        // Reference:
        // https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c

    return 0;
}
