#include <iostream>
#include <iomanip> // for cout<< manipulations
#include <cmath>

using namespace std;

namespace geo
{
    const double PI = 3.14159F;
    double circumf(double rad)
    {
        return 2 * PI * rad;
    }
} // namespace geo

int main(void)
{
    cout << "hello!" << endl;
    cout << geo::circumf(3.2) << endl;
    int var; // declaration (as we now know var) and definition (as var is assigned a memory space)
    long longvar0 = 74466L;
    __int16 xx = 5;
    __int32 yy = 7;
    __int64 zz = 9;
    int d = 5, e = 6, f = 7;
    wchar_t c[] = L"å"; // wchar_t size 4 bytes (32-bit)
    wcout << c << endl;
    cout << "jk\ba" << endl; // /b : backspace
    cout << "\xDC" << endl;  // /xFF : to put ASCII characters above 127
    // cin >> var >> x;
    cout << var << xx << endl;

    //** When two arithmetic operators have the same precedence, the one on the left is executed first
    int exp = (1 + 6) * 4 / 3;

    /* INTEGERS:
        ** types long and short have fixed sizes no matter what system is used.**
        Keyword     Low                 High                Memory (Bytes)
        -------------------------------------------------------------------
        char        -128                128                 1-byte
        short       –32,768             32,767              2-byte
        int                 (system dependent)
        long        –2,147,483,648      2,147,483,647       4-byte

        **(Type int, although twice as large, is accessed faster than type short in 32-bit systems)
    */
    const long LONGVAR = 74466L; // L: for 'long' when the number is integer (without a floating point)

    /* UNSIGNED INTEGERS
        Keyword             Low     High                Memory (Bytes)
        ----------------------------------------------------------------
        unsigned char       0       255                 1-byte
        unsigned short      0       65,535              2-byte
        unsigned int        0       4,294,967,295       4-byte (in 32-bit systems)
        unsigned long       0       4,294,967,295       4-byte
    */
    unsigned int ui = 1641646;

    /* FLOATING-POINT:
        ** double is the default type for constants
        Keyword     Low                 High                Memory (Bytes)      Precision
        ------------------------------------------------------------------------------------
        float       3.4x10^–38          3.4x10^38           4-byte              7 digits
        double      1.7x10^–308         1.7x10^308          8-byte              15 digits
        long double >> compiler dependent (but is often same as double)
    */
    const float PI = 3.141F;                  // F: for 'float'
    const double DOUBLEVAR = 5.545;           // constant floating point numbers are double by default
    const long double LONGDOUBLEVAR = 1.556L; // L: for 'long double'

    // exponential notation
    const float F1 = 1000000000;
    const float F1_ = 1.0E9; // *10^9

    const float F2 = 3652.4664;
    const float F2_ = 3.6524664E3;

    const float F3 = 0.0000635239;
    const float F3_ = 6.35239E-5;

    /* Floating-point Notation: */
    double db = 166.9476112;
    cout << db << endl;
    // fixed        : write floating-point values in fixed-point notation.
    cout << "fixed: " << fixed << db << endl; // 166.947611
    // scientific   : write floating-point values in scientific notation.
    cout << "scientific: " << scientific << db << endl; // 1.669476e+002
    // hexfloat     : write floating-point values in hexadecimal format.
    cout << "hexfloat: " << hexfloat << db << endl; // 0xa.6f296a5c952c8p+4
    // defaultfloat : write floating-point values in default floating-point notation.
    cout << "defaultfloat: " << defaultfloat << db << endl; // 166.948

    /* Precision Field:
        • The precision field specifies the maximum number of meaningful digits to display
            both before and after the decimal point,
        • while in both the 'fixed' and 'scientific' notations:
            the precision field specifies exactly how many digits to display
            after the decimal point, even if they are trailing decimal zeros.
    */
    std::cout << defaultfloat;
    std::cout.precision(2);
    cout << "defaultfault with precision (2): " << db << endl;             // 1.7e+002 (only 2 digits)
    cout << "fixed with precision (2): " << fixed << db << endl;           // 166.95 (2 digits after the '.')
    cout << "scientific with precision (2): " << scientific << db << endl; // 1.67e+002 (2 digits after the '.')

    // we can also use (must include <iomanip>):
    cout << fixed << setprecision(4) << db << endl;        // 4 dicimal places are displayed // 776.6988
    cout << defaultfloat << setprecision(4) << db << endl; // all digits displayed are 4 // 776.7

    // make it a function-like macro
#define FIXED_PREC(num, prec) std::fixed << std::setprecision(prec) << num
    cout << FIXED_PREC(166.9476112, 2) << endl;

    std::cout << defaultfloat; // return to the 'defaultfloat' format

    // another example:
    cout    << setiosflags(ios::fixed)          // not exponential
            << setiosflags(ios::showpoint)      // always use point
            << setprecision(2)                  // digits to right
            << setw(10)                         // field width
            << 166.9476112
            << endl;

    cout << resetiosflags; // to reset ios flags


    // sqrt : square root (include <cmath>)
    double number, answer;
    number = 1000;
    answer = sqrt(number); // sqrt require a double data type
    cout << answer << endl;

    /* BOOLEAN
        bool    >> 1-bit (but in practice compilers often store them as 1 byte because a byte can be quickly accessed)
    */
    bool b = true;

    /* TYPE CONVERSIONS ............................................*/

    /* Order of Data Types:

        long double         Highest
        double
        float

        long
        int
        short
        char                Lowest
    */

    /* IMPLICIT CASTING:

        In C/ C++ the compiler considers it normal that you want to perform any
        arithmetic operation on numbers of different types
    */
    int count = 2;
    float avgWeight = 1.2F;
    double totalWeight = count * avgWeight; // 2.4
    cout << "totalWeight= " << totalWeight << endl;
    /*
        When two operands of different types are encountered in the same expression:
            >> the lower-type variable is converted to the type of the higher-type variable.

        Thus in MIXED, the int value of 'count' is converted to type float and stored in
            a temporary variable before being multiplied by the float variable avgWeight.

        The result (still of type float) is then converted to double
            so that it can be assigned to the double variable totalWeight
    */

    /* EXPLICIT CASTING:

        They are a controlled way of evading type safety
         > (which means making sure that variables don’t change types by mistake)
    */
    int anIntVar = 105;
    char aCharVar0 = static_cast<char>(anIntVar);
    // you could say:
    char aCharVar1 = (char)anIntVar;
    // or alternatively:
    char aCharVar2 = char(anIntVar);
    /*
        • One problem with these last two approaches is that they are hard to see;
            >> the syntax blends into the rest of the listing.
        • They are also hard to search for using a Find operation with your source code editor.

        ► The new format solves this problem: static_cast is easy to see and easy to search for.
        ► These old casts still work, but their use is discouraged (or deprecated, to use the technical
        term).
    */

    int intVar = 1500000000;                          // 1,500,000,000
    intVar = (intVar * 10) / 10;                      // intermediate value: (intVar * 10) is too large
    cout << "intVar = " << intVar << endl;            // wrong answer
    intVar = 1500000000;                              // cast to double
    intVar = (static_cast<double>(intVar) * 10) / 10; // or <__int64>
    cout << "intVar = " << intVar << endl;            // right answer

    //................................................................

    /* MANIPULATORS */
    // endl:
    // new line and it flushes the output buffer.
    cout << "Hi!" << endl;

    // setw(n):
    /** must include <iomanip> */
    /* causes the number (or string) that follows it in the stream to be printed
        right-justified within a field n characters wide */
    cout << setw(4) << "Num1" << setw(12) << 64634634 << endl
         << setw(4) << "NUm2" << setw(12) << 5645 << endl;

    // setprecision(x):
    // for floating point numbers
    double db1 = 776.69878646;
    cout << fixed << setprecision(4) << db1 << endl;        // 4 dicimal places are displayed // 776.6988
    cout << defaultfloat << setprecision(4) << db1 << endl; // all digits displayed are 4 // 776.7

    /* HEADER FILES:
        Functions in your source file need to know ...
            the names and types of the functions and other elements in the library file.
        They are given this information in a header file.
            Each header file contains information for a particular group of functions.
    */

    /* PRECEDENCE OF OPERATORS ↓ .....................................................
        _______________________________
        ↓ Expression                L→R

            [   ]   (   )   .   ->  postfix(++/--)
        _______________________________
        ↓ Unary Operators           R→L

            sizeof      &             *              +/-              ~              !          (++/--)prefix
                    Address-of   De-reference    Number-sign    1's-complement  Logical-NOT

              (int)
            Typecasts
        _______________________________
        ↓ Arithmetic Operators      L→R

            *   /   %
            +   -
            <<  >>
        _______________________________
        ↓ Relational Operators      L→R

            <   >   <=  >=
            ==  !=
        _______________________________
        ↓ Logical Operaors          L→R

            &       ┐
            ^       │   Bitwise
            |       ┘

            &&      ┐   Logical
            ||      ┘
        _______________________________
        ↓ Conditional Expression    L→R

            (?   :)
        _______________________________
        ↓ Assignment Operators      R→L

            =   *=  /=  %=  +=  -=  <<= >>= &=  ^=  |=
        _______________________________
        ↓ Sequential Evaluation     L→R
            ,   (ex.: int x, y;)
        _______________________________


    // Summary:
        Expression > Unary > Arithmetic > Relational > Logical > Conditional > Assignment > Sequential

    //  Operators are divide into:
            Unary Operators:    like '!' NOT    : takes one operand.
            Binary Operators:   like '+' Plus   : takes two operands.
            Ternary Operator:   Only ( ? : )    : takes three operands.

    //  • If several operators appear on the same line → they have equal precedence.
        └ Evaluation proceeds according to the associativity of the operator:
            └ Either from (right to left) or from (left to right).
    */

    // example:
    int x, y;
    if (x % 7 == 0 && y % 7 == 0)
        ; // arithmetic > relational > logical

    // example (* and % : have equal precedence → from left to right):
    x = 2 * 3 % 4; // * before %   // x ← 2
    y = 2 % 3 * 4; // % before *   // y ← 8
    cout << "x = " << x << ",\ny = " << y << endl;

    // example:
    x = 100;
    y = x++; // postfix '++' has higher precedence than '='
             // → x is added to Accumlator (Acc = x = 100)
             // → x = x + 1  = 101
             // → y = Acc    = 100

    y = 100;
    y = y++; // postfix '++' has higher precedence than '='
             // → y is added to Accumlator (Acc = y = 100)
             // → y = y + 1  = 101
             // → y = Acc    = 100

    

    // Note: cout 
    int g = 0;

    cout << ++g << " " <<  ++g << endl;
    // Since C++17 (GCC 7) the functions are guaranteed to be called left-to-right,
    // Prior to C++17 the order of function calls was unspecified, meaning that
    //      they may be called in any order (and this order does not need to be the same 
    //      on repeated invocations).
    
    return 0;
}