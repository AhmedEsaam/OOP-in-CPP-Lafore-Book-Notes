#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib> //for srand(), rand()
#include <ctime>   //for time for srand()

using namespace std;

/************************************* ARRAYS ***************************************/

/*
    • A structure usually groups items of different types, an array groups items of the same type.
    • More importantly, the items in a structure are accessed by name,
        while those in an array are accessed by an index number.
        (Using an index number to specify an item allows easy access to a large number of items.)
*/

/* FUNCTION DECLARATION WITH ARRAY ARGUMENTS */
const int DISTRICTS = 3;
const int MONTHS = 2;
void display(double[DISTRICTS][MONTHS]);
void display2(double[5][6]);

// you can skip the size of the first dimention:
void display3(double[][MONTHS]); // it can calculate where a particular element is ...
                                 // (by multiplying the bytes per element times the index.)

void display4(int[]);


void display(double funsales[DISTRICTS][MONTHS])
{
    int d, m;
    for (d = 0; d < DISTRICTS; d++)
    {
        cout << endl;
        for (m = 0; m < MONTHS; m++)
        {
            cout << setiosflags(ios::fixed) << setw(9)
                 << setiosflags(ios::showpoint) << setprecision(2)
                 << funsales[d][m];
        }
    }
}


/* ARRAYS AS CLASS MEMBERS */
class Stack
{
private:
    static const int MAX = 10; // some compilers doesn't allow this construction
    // enum { MAX = 10 };       // (non-standard syntax): makes 'MAX' definition contained
    //   entirely within the class.
    int st[MAX];
    int top;

public:
    Stack() : top(-1){};
    void push(int var)
    {
        st[++top] = var;
    }
    int pop()
    {
        return st[top--];
    }
    int get_top()
    {
        return top;
    }
};

/* Note:
    • There is no bounds-checking in C++ arrays.
        >> If the program inserts something beyond the end of the array,
            neither the compiler nor the runtime system will object.

        >> However, the renegade data will probably be written on top
            of other data or the program code itself.

        →  So, it is up to the programmer to deal with the array bounds-checking.
*/



/* EXAMPLE: Arrays of Cards */

enum Suit { clubs, diamonds, hearts, spades};
const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;

class Card
{
private:
    int number;     // 2 to 10, jack, queen, king, ace
    Suit suit;
public:
    void set(int n, Suit s)
    { suit = s; number = n; }

    void display();
};


void Card::display()
{
    if(number >= 2 && number <= 10)
        cout << number;
    else
        switch(number)
        {
        case jack:  cout << "J"; break;
        case queen: cout << "Q"; break;
        case king:  cout << "K"; break;
        case ace:   cout << "A"; break;
        }
    
    switch(suit)
    {
    case hearts:    cout << static_cast<char>(3); break;
    case diamonds:  cout << static_cast<char>(4); break;
    case clubs:     cout << static_cast<char>(5); break;
    case spades:    cout << static_cast<char>(6); break;
    }
}


/************************************* STRINGS ***************************************/
/*
    There are two kinds of strings are commonly used in C++:
    • C-strings (arrays of type char), (<cstring> library provides useful functions to handle these)
    • and strings that are objects of the standard C++ string class.
*/

/* C STRINGS */////////////////////////////////////
// here is a String class which simplifies copying and concatinating using <cstring> functions
class String
{
private:
    static const int SZ = 80;
    char str[SZ];
public:
    String()
        { str[0] = '\0'; }
    String(char s[])
        { strcpy(str, s); }
    void display()
        { cout << str; }
    void concat(String s2)
    { 
        if(strlen(str) + strlen(s2.str) < SZ)
            { strcat(str, s2.str); }
        else
            { cout << "\nString is too long"; }
    }
};



/* STANDARD C++ STRING CLASS */////////////////////
/*
    Although strings created with the string class have superseded C-strings in many situations, 
    C-strings are still important for a variety of reasons:
        • First:        they are used in many C library functions. 
        • Second:       they will continue to appear in legacy code for years to come. 
        • And third:    for students of C++, C-strings are more primitive and therefore
                            easier to understand on a fundamental level.
*/



int main(int argc, char const *argv[])
{
    const int SIZE = 6;
    double cars[SIZE]; // all-uppercase name reminds us that the variable cannot be modified in the program.
    /*
        Using a variable (instead of a number, such as the 6 used in the last example)
            >> makes it easier to change the array size:
                Only one program line needs to be changed to change the array size, loop limits,
                and anywhere else the array size appears.
    */


    /* Initializing Arrays */////////////////////////////////////
    int coins[6] = {1, 5, 10, 25, 50, 100};
    int shares[] = {50, 30, 5, 15}; // we don't need to use the array size (as the compiler can figure it out).

    // Note:
    int nums1[5] = {1, 2, 3}; // the missing elements will be set to 0
                              // int nums2[5] = {1, 2, 3, 4, 5, 6, 7}; // Error


    /* FUNCTION DECLARATION WITH ARRAY ARGUMENTS *///////////////
    double sales[DISTRICTS][MONTHS] = {{165.45, 664.2},
                                       {161.66, 516.6},
                                       {612.54, 622.9}};

    display(sales); // this is passing by address


    /* ARRAYS AS CLASS MEMBERS */////////////////////////////////
    Stack s1;
    s1.push(11);
    s1.push(22);

    cout << endl;
    cout << "s[" << s1.get_top() << "]: ";
    cout << s1.pop() << endl;
    cout << "s[" << s1.get_top() << "]: ";
    cout << s1.pop() << endl;

    s1.push(5);
    // cout << "s[" << s1.get_top() << "]: ";
    // cout << s1.pop() << endl;

    cout << "s[" << s1.get_top() << "]: " << s1.pop() << endl; // Left to right order of expression evaluation is present from C++17 (GCC7) onwards

    
    /* EXAMPLE: Arrays of Cards *////////////////////////////////
    Card deck[52];
    int i;
    cout << endl;

    // Make an ordered deck
    for (i = 0; i < 52; i++)
    {
        deck[i].set(((i % 13) + 2), Suit(i / 13));
    }

    // Display ordered deck
    cout << "\nOrdered deck:\n";
    for (i = 0; i < 52; i++)
    {
        deck[i].display(); cout << "  ";
        if( !((i+1) % 13) ) cout << endl;   // newline every 13 cards
    }

    // Shuffle cards
    srand(time(NULL));  // seed random numbers with time
    for (i = 0; i < 52; i++)
    {
        int k = rand() % 52;
        // swap cards: deck[k] with deck[i]
        Card temp;
        temp = deck[i];
        deck[i] = deck[k];
        deck[k] = temp;
    }

    // Display shuffled deck
    cout << "\nShuffled deck:\n";
    for (i = 0; i < 52; i++)
    {
        deck[i].display(); cout << "  ";
        if( !((i+1) % 13) ) cout << endl;   // newline every 13 cards
    }


    /* C STRINGS *///////////////////////////////////////////
    const int MAX = 80;
    char str[MAX];
    cout << "\nEnter a string: ";
    cin >> setw(MAX) >> str;    // no more than MAX chars (19 chars + the NUll)
                                // (as normally the compiler won't check if the size has been passed)
                                // Note: extraction operator >> considers a space to be a terminating character. 
    cout << "You entered: " << str << endl;

    // including entered spaces
    cout << "\nEnter a string: \n";
    cin.ignore();               // *flush the previous 'Newline' character
    cin.get(str, MAX);          // stops reading until entering '\n' (Newline) (default value) or exceeding 'MAX'
    cout << "You entered: " << str << endl;
    
    // Reading multiple lines
    cout << "\nEnter a string: \n";
    cin.ignore();
    cin.get(str, MAX, '$');     // stops reading until entering '$' or exceeding the size of the array 'MAX'
    cout << "You entered: " << str << endl;

    // Inirialization
    char str2[] =   "Farewell! thou art too dear for my possessing. ";

    char str3[] =   "Oh, Captain! "
                    "Our fearful trip is done.";
    /*  the compiler concatenates two adjacent string constants into a single one.
        ...( which allows us to write the quotation on two lines.)
    */
    char str1[MAX];

    // C-string library functions:
    /* 
        • There are no string operators built into C++.
        - But, C-strings are usually be manipulated using library functions.
            (Fortunately there are many such functions.)
    */
    int strLength = strlen(str3);   // string length (does not include the null.)

    strcat(str2, str3);     // add string to another.

    strcpy(str1, str3);     // copy str3 to str1 : strcpy(destination, source)

    int cmp = strcmp(str1, str2);   // compares str1 to str2 
                                    // (stops until they differ or a terminating char is reached.) 
                                    // On first char to differ, it returns: str1[i] - str2[i] , 
                                    //      or 0 when they are identical or null is reached

    char *pch = strchr(str1, 's');    // searches for the character in the array and returns a pointer at this char position. 
    int ch_indx = pch - str1;


    // String class (made up)
    String st1("Hi, ");
    String st2 = "all!";
    String st3;
    st3 = st1;
    st3.concat(st2);
    cout << "st3 = "; st3.display(); cout << endl;
    

    /* STANDARD C++ STRING CLASS *//////////////////////////
    

    
    return 0;
}



