#include <iostream>
#include <iomanip>
#include <process.h> // for exit(0)
#include <conio.h>   // for getche()
using namespace std;

/* Why we need Loops & Decisions?
    • Most programs (like many humans) decide what to do in response to changing circumstances.
        The flow of control jumps from one part of the program to another, depending on calculations
        performed in the program.
    • Program statements that cause such jumps are called control statements.
    • There are two major categories: loops and decisions.
*/

int main(void)
{
    /* Displaying the results of relational operations, or even the values of type bool variables,
        with cout<< yields 0 or 1, not false or true.
        >> Historically this is because C++ started out with no bool type.
    */
    cout << (12 > 5) << endl; // 1

    /* FOR LOOPS ........................................................*/

    int j;                      // define a loop variable
    for (j = 0; j < 15; j++)    // loop from 0 to 14,
        (cout << j * j << " "); // displaying the square of j (single-statement body preferable to put in ())
    cout << endl;

    // You can put more than one expression in the initialization part and/or increment part of the for statement
    int alpha, beta = 10;
    for (j = 0, alpha = 100; j < 50; j++, beta--) // avoid this as it decreases readability
    {
        alpha--; // body of loop
    }

    // The expression ...
    // for(;;)
    // ... is the same as a while(true).

    /* WHILE LOOPS ........................................................*/

    int num = 99;
    while (num != 0)
    {
        cin >> num;
    }

    // 4th power
    int n = 1, res = 1;
    while (res < 9999)
    {
        cout << setw(2) << n << setw(5) << res << endl;
        n++;
        res = n * n * n * n;
    }
    cout << endl;

    // Fibonacci Series
    const unsigned long limit = 4294967295; // largest unsigned long
    unsigned long prev = 0, current = 1, sum;
    while (prev < limit / 2)
    {
        cout << current << ", ";
        sum = prev + current;
        prev = current;
        current = sum;
    }
    cout << endl;

    /* DO WHILE LOOPS ........................................................*/

    long dividend, divisor;
    char ch;
    do // start of do loop
    {  // do some processing
        cout << "Enter dividend: ";
        cin >> dividend;
        cout << "Enter divisor: ";
        cin >> divisor;
        cout << "Quotient is " << dividend / divisor;
        cout << ", remainder is " << dividend % divisor;
        cout << "\nDo another? (y/n): "; // do it again?
        cin >> ch;
    } while (ch != 'n'); // loop condition

    /* Decisions .............................................................*/

    int m;
    cin >> m;
    if (m == 0)
    {
        exit(0);
    }
    cout << "Ok" << endl;

    // Counts characters and words typed in:
    int chcount = 0; // counts non-space characters
    int wdcount = 1; // counts spaces between words
    ch = 'a';        // ensure it isn't '\r'
    cout << "Enter a phrase : ";
    while ((ch = getche()) != '\r') // loop until Enter typed
    {
        // 'getche' read one character (does not require an Enter to read input)
        // The getche() function echoes the character to the screen. That's why there's an e at the end of getche.
        // Another function, getch(), is similar to getche() but doesn't echo the character to the screen.

        if (ch == ' ') // if it's a space
            wdcount++; // count a word
        else           // otherwise,
            chcount++; // count a character
    }                  // display results
    
    cout << "\nWords =" << wdcount << endl
         << "Letters =" << (chcount - 1) << endl;

    /* ASSIGNMENT EXPRESSIONS HAVE A VALUE:
        //  while ((ch = getche()) != '\r')

        This works because the entire assignment expression takes on the value used in the assignment.
        That is, if getche() returns ‘a’, then not only does ch take on the value ‘a’, but the expression
        (ch=getche()) also takes on the value ‘a’
    */
    int x, y, z;
    x = y = z = 0; // '=' excutes from right to left
    // (z = 0) value is 0
    // then (y = 0) value is 0
    // then x = 0


    /* Control Statements ...................................................*/

    // Displaying the distribution of prime numbers in graphical form:
    const unsigned char WHITE = 219;    // Prime
    const unsigned char GRAY = 176;     // Not prime
    unsigned char cha;

    for (int i = 2; i < 80 * 25 - 1; i++)
    {
        cha = WHITE; // Prime
        if (i == 4) cha = GRAY;
        
        for (int j = 2; j < i / 2; j++)
        {
            if (!(i % j))
            {
                cha = GRAY; // Not prime
                break;
            }
        }
        cout << cha;
    }
    getche();

    
    return 0;
}
