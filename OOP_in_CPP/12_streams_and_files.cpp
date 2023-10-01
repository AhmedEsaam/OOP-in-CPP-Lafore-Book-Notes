#include <iostream>
#include <fstream>
#include <iomanip>          // for manipulators
// #include <strstream>
#include <string>
#include <cstdlib>

using namespace std;

// A 'stream' is a general name given to a flow of data.

/** Advantages of Streams:
    ► There are no such formatting characters (like %d, %f, ...) in streams, 
        → since each object already knows how to display itself. This removes a major source of errors.

    ► You can overload existing operators and functions, 
        such as the insertion (<<) and extraction (>>) operators, to work with classes that you create.
        → Which makes programming easier and more error free (not to mention more aesthetically satisfying).
        
    ► They are the best way to write data to files.

    ► And also to format data in memory for later use in text input/output windows and other GUI elements.
*/


/** Header files for decalred Classes:
 * <iostream>   The classes used for input and output to the video display and keyboard are declared in this header file.
 * <fstream>    The classes used specifically for disk file I/O are declared in this file.  
 * 
 * <iomanip>    Also, some manipulators are declared in this header file.
 * <strstream>  and in-memory classes are declared in this header file. 
*/


/** Classes:
 * ___________________________________
 *  'ios' class:
 *      is the granddaddy of all the stream classes, and contains the majority of the features you need to operate C++ streams:
 *      The three most important features are:
 * 
 *      - The formatting flags:
 *          They are a set of enum definitions in ios. 
 *          : They act as on/off switches that specify choices for various aspects of input and output format and operation.
 * 
 *      - The error-status flags:
 * 
 *      - The file operation mode:
 * ___________________________________
 *  'istream' class contains:
 *      - get()
 *      - getline()
 *      - read()
 *      - the overloaded extraction (>>) operators
 * ___________________________________
 *  'ostream' class contains:
 *      - put()
 *      - write()
 *      - the overloaded insertion (<<) operators
 * ___________________________________
 *  'iostream' class:
 *      - derived from both istream and ostream by multiple inheritance. 
 *          Classes derived from it can be used with devices, 
 *          (such as disk files, that may be opened for both input and output at the same time.)
 * ___________________________________
 *  'istream_withassign', 'ostream_withassign', and 'iostream_withassign':
 *      - They add assignment operators to these classes.
 * 
*/



// Error-Free Distance Class:
int isFeet(string);

class Distance
{
private:
    int feet;
    float inches;
public:
    explicit Distance(int ft = 0, float in = 0.0) : feet(ft), inches(in)
    {   }
    Distance(float fltFeets)
    {
        feet = static_cast<int>(fltFeets);
        inches = 12 * (fltFeets - feet);
    }
    void show_dist() const
    {   cout << feet << "\' " << inches << "\""; }
    void get_dist();
};


void Distance::get_dist()
{
    string instr;                               // for input string

    while(true)
    {
        cout << "\nEnter feet: ";
        cin.unsetf(ios::skipws);                // do not skip white space
        cin >> instr;
        if(isFeet(instr))
        {
            cin.ignore(10, '\n');               // eat chars, including newline
            feet = stoi(instr);                 // ... or:  atoi(instr.c_str());
            break;
        }
        cin.clear();                            // clear all error states
        cin.ignore(10, '\n');
        cout << "Feet must be an integer less than 10000 and bigger than -1000\n";
    }   // end of feet

    while(true)
    {
        cout << "\nEnter inches: ";
        cin.unsetf(ios::skipws);
        cin >> inches;
        if(inches >= 12.0 || inches < 0.0)
        {
            cout << "Inches must be between 0.0 and 11.99\n";
            cin.clear(ios::failbit);            // this clears all flags except 'failbit' ("artificially" set fail bit)
        }
        if(cin.good())
        {
            cin.ignore(10, '\n');
            break;
        }
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Incorrect inches input\n";     // strat agian
    }   // end of inches
    

    // Another way:- - - - - - -
    // while(true)
    // {
    //     cout << "Enter distance in feet and inches: ";
    //     cin >> instr;
    //     if(instr.empty())
    //         break;
    //     else
    //     {
    //         istringstream iss(instr);
    //         iss >> feet >> inches;
    //         break;
    //     }
    // }   
}

int isFeet(string str)
{
    int slen = str.size();
    if(slen == 0 || slen > 5)       // feet in 4 places: between -999 and 9999
        return 0;
        
    for(int i = 0; i < slen; i++)
        if((str[i] < '0' || str[i] > '9') && str[i] != '-')
            return 0;

    long n = stoi(str);
    if(n < -999 || n > 9999)
        return 0;

    return 1;
}



/// Disk File I/O with Streams //////////////////////////////////////////////////////




int main()
{

    /// Classes //////////////////////////////////////////////////////////////////

    /// 'ios' class:______________________________________________________________
    
    // ---------------------------
    // ♦ Formatting Flags:

    /*
        Formatting flags are used to control the formatting of the output.
        They are a set of enum definitions in ios.
        They act as on/off switches that specify choices for various aspects of input and output format and operation.
    */
   
    /*
        skipws              \\ Skip (ignore) whitespace on input
        left                \\ Left-adjust output [12.34 ]
        right               \\ Right-adjust output [ 12.34]
        internal            \\ Use padding between sign or base indicator and number [+ 12.34]
        dec                 \\ Convert to decimal
        oct                 \\ Convert to octal
        hex                 \\ Convert to hexadecimal
        boolalpha           \\ Convert bool to "true" or "false" strings
        showbase            \\ Use base indicator on output (0 for octal, 0x for hex)
        showpoint           \\ Show decimal point on output
        uppercase           \\ Use uppercase X, E, and hex output letters (ABCDEF)—the default is lowercase
        showpos             \\ Display + before positive integers
        scientific          \\ Use exponential format on floating-point output [9.1234E2]
        fixed               \\ Use fixed format on floating-point output [912.34]
        unitbuf             \\ Flush all streams after insertion
        stdio               \\ Flush stdout, stderror after insertion
    */


    // Using functions //:-

    cout.setf(ios::left);                       // set ios::flag for left justifing output text (for the rest of code)
    cout << "This text is left-justified" << endl;
    cout.unsetf(ios::left);                     // unset ios::flag (return to default)
    
    /* A two-argument version of setf() 
        → uses the second argument to reset all the flags of a particular type or field. 
        → Then the flag specified in the first argument is set. 
        This makes it easier to reset the relevant flags before setting a new one.  
    */
    cout.setf(ios::left, ios::adjustfield);     // clears all the flags dealing with text justification and then sets the left flag for left-justified output.
    cout << "This text is left-justified" << endl;
    cout.unsetf(ios::left);

    cout.width(12);
    int ivar1 = 54;
    cout << ivar1 << endl;

    /* ios Functions:-------------
        ch = fill();            // Return the fill character (fills unused part of field; default is space)
        fill(ch);               // Set the fill character
        p = precision();        // Get the precision (number of digits displayed for floating-point)
        precision(p);           // Set the precision
        w = width();            // Get the current field width (in characters)
        width(w);               // Set the current field width
        setf(flags);            // Set specified formatting flags (for example, ios::left)
        unsetf(flags);          // Unset specified formatting flags
        setf(flags, field);     // First clear field, then set flags
            (flags to set):             (field to clear): 
            dec, oct, hex               basefield
            left, right, internal       adjustfield
            scientific,                 fixed floatfield
    */
    

    // Using manipalators //:-

    /*  Many formatting flags can be set using 'manipulators'.
        • Manipulators: are formatting instructions inserted directly into a stream: 
        Note that: 'manipulators' affect only the data that follows them in the stream, not the data that precedes them. 
    */
    cout << "To each his own." << endl;         // the no-arg manipulator 'endl', sends a newline to the stream and flushes it.

    int ivar2 = 55;
    cout << hex << ivar2 << endl;               // the no-arg manipulator 'hex', convert to hexadecimal
    cout.unsetf(ios::hex);
    
    float fvar = 5.25f;
    cout    << setiosflags(ios::fixed)          // 'setiosflags' manipulator takes one argument
            << setiosflags(ios::showpoint)
            << fvar << endl;

    cout    << resetiosflags(ios::fixed)        // reset specific flags
            << resetiosflags(ios::showpoint)
            << fvar << endl;
    
    /* No-Arg ios Manipulators:-----------
        ws           // Turn on whitespace skipping on input
        dec          // Convert to decimal
        oct          // Convert to octal
        hex          // Convert to hexadecimal
        endl         // Insert newline and flush the output stream
        ends         // Insert null character to terminate an output string
        flush        // Flush the output stream
        lock         // Lock file handle
        unlock       // Unlock file handle
    */

    /* Manipulators with Arguments:------------
        Manipulator             Argument                        Purpose
        -----------------------------------------------------------------------------------------------------------
        setw()                  field width (int)               Set field width for output
        setfill()               fill character (int)            Set fill character for output (default is a space)
        setprecision()          precision (int)                 Set precision (number of digits displayed)
        setiosflags()           formatting flags (long)         Set specified flags
        resetiosflags()         formatting flags (long)         Clear specified flags
    */


    /** Note: set, unset, setiosflags, and unseiosflags: they manipulate the ios formatting flags directly 
        (set or unset the flag for all the afterward code unless changed)
    */
    

    
    /// 'istream' class:___________________________________________________________________________
    
    /* istream function:---------
        >>                              // Formatted extraction for all basic (and overloaded) types.
        get(ch);                        // Extract one character into ch.
        get(str)                        // Extract characters into array str, until ‘\n’.
        get(str, MAX)                   // Extract up to MAX characters into array.
        get(str, DELIM)                 // Extract characters into array str until specified delimiter (typically ‘\n’). Leave delimiting char in stream.
        get(str, MAX, DELIM)            // Extract characters into array str until MAX characters or the DELIM character. Leave delimiting char in stream.
        getline(str, MAX, DELIM)        // Extract characters into array str, until MAX characters or the DELIM character. Extract delimiting character.
        putback(ch)                     // Insert last character read back into input stream.
        ignore(MAX, DELIM)              // Extract and discard up to MAX characters until (and including) the specified delimiter (typically ‘\n’).
        peek(ch)                        // Read one character, leave it in stream.
        count = gcount()                // Return number of characters read by a (immediately preceding) call to get(), getline(), or read().
        read(str, MAX)                  // For files—extract up to MAX characters into str, until EOF.
        seekg()                         // Set distance (in bytes) of file pointer from start of file.
        seekg(pos, seek_dir)            // Set distance (in bytes) of file pointer from specified place in file. seek_dir can be ios::beg, ios::cur, ios::end.
        pos = tellg(pos)                // Return position (in bytes) of file pointer from start of file.
    */
    
    
    /// 'ostream' class:____________________________________________________________________________
    /* ostream function:---------
        <<                              // Formatted insertion for all basic (and overloaded) types.
        put(ch)                         // Insert character ch into stream.
        flush()                         // Flush buffer contents and insert newline.
        write(str, SIZE)                // Insert SIZE characters from array str into file.
        seekp(position)                 // Set distance in bytes of file pointer from start of file.
        seekp(position, seek_dir)       // Set distance in bytes of file pointer, from specified place in file. seek_dir can be ios::beg, ios::cur, or ios::end.
        pos = tellp()                   // Return position of file pointer, in bytes.
    */


    /// 'iostream' class:____________________________________________________________________________
    /*
        'iostream' class derived from 'istream' and 'ostream'
        - Acts only as a base class from which other classes, specifically iostream_withassign, can be derived.  
        - Classes derived from iostream can perform both input and output.
        
    */
    
    
    ///  the '_withassign' Classes:____________________________________________________________________________
    /*
        - There are three _withassign classes:
            • istream_withassign        // derived from 'istream'
            • ostream_withassign        // derived from 'ostream'
            • iostream_withassign       // derived from 'iostream'

        - They are are much like those they’re derived from except that 
            → they include overloaded assignment operators so their objects can be copied.
        
        - In general, it’s not a good idea to copy stream class objects.
            But, as each such object is associated with a particular streambuf object, which includes an area in memory to hold the object’s actual data,
            If you copy the stream object, it causes confusion if you also copy the streambuf object.
            → However, in a few cases it’s important to be able to copy a stream.

        - The 'istream', 'ostream', and 'iostream' classes are made uncopyable 
            (by making their overloaded copy constructors and assignment operators private),
        - While the '_withassign' classes derived from them can be copied.

        - Two predefined stream objects that are derived from the '_withassign' classes: cin and cout. 
            These are normally connected to the keyboard and display, respectively
            • cin,      an object of istream_withassign, normally used for keyboard input
            • cout,     an object of ostream_withassign, normally used for screen display

        - The two other predefined objects are cerr and clog.
            • cerr,     an object of ostream_withassign, for error messages
                → is often used for error messages and program diagnostics.
                → Output sent to cerr is displayed immediately, rather than being buffered as cout is. Also, it cannot be redirected.
                → So, you have a better chance of seeing a final output message from cerr if your program dies prematurely. 
            • clog,     an object of ostream_withassign, for log messages
                →  is similar to cerr in that it is not redirected, but its output is buffered, while cerr’s is not.
    */
    


    /// Stream Errors ///////////////////////////////////////////////////////////////
    /*
        Errors can happen in input and output:
            • User can input string instead of integer.
            • Push the Enter key without entering anything.
            • Extra characters left in the input stream (like '\n') are then passed along to the next input operation.
            • Or a hardware failure.
    */    
    
    /// Error-Status Bits:________________________________________
    // The stream error-status flags constitute an ios enum member that reports errors that occurred in an input or output operation.
    
    /* Error-Status Flags:________________________________________
        goodbit             // No errors (no flags set, value = 0)
        eofbit              // Reached end of file
        failbit             // Operation failed (user error, premature EOF)
        badbit              // Invalid operation (no associated streambuf)
        hardfail            // Unrecoverable error
    */
    
    /* Functions for Error-Status Flags:__________________________
        int = eof();        // Returns true if EOF flag set
        int = fail();       // Returns true if failbit or badbit or hardfail flag set
        int = bad();        // Returns true if badbit or hardfail flag set
        int = good();       // Returns true if everything OK; no flags set
        clear(int=0);       // With no argument, clears all error bits; otherwise sets specified flags, as in clear(ios::failbit)
    */

    // ____________________________________
    /// ► Check Inputting Numbers:
    int n;
    while(true)
    {
        cout << "\nEnter an integer: ";
        cin >> n;
        if(cin.good())
        {
            cin.ignore(10, '\n');
            break;
        } 
        cin.clear();
        cout << "Incorrect input";
        cin.ignore(10, '\n');
    }
    cout << "integer is " << n << endl;
    
    // Floating-point numbers (float, double, and long double) can be analyzed for errors in the same way as integers.
    

    // ____________________________________
    /// ► Too many Characters:

    // Typically, extra characters are left in the input stream after the input is supposedly completed. 
    // →  They are then passed along to the next input operation, even though they are not intended for it. 
    // Often it’s a newline character that remains behind.

    // To get rid of these extraneous characters the ignore(MAX, DELIM) member function of istream is used
    // // It reads and throws away up to MAX characters, including the specified delimiter character.
    cin.ignore(10, '\n');       // causes cin to read up to 10 characters, including the ‘\n’, and remove them from the input.


    // ____________________________________
    /// ► Whitespace Characters when inputting Numbers:

    // Whitespace characters, such as tab space and ‘\n’, are normally ignored (skipped) wheninputting numbers. 

    /* This can have some undesirable side effects:
        - Users may simply press the Enter key without typing any digits. (Perhaps they think that this will enter 0),
            but, seeing no acknowledgment when they press Enter, they may assume the computer is broken.

        - Second, pressing Enter repeatedly normally causes the cursor to drop lower and lower until the entire screen begins to scroll upward. 
            However, in text-based graphics programs, scrolling the screen disarranges and eventually obliterates the display.
    */

    // Thus it’s important to be able to tell the input stream not to ignore whitespace.
    cin.unsetf(ios::skipws);        // don’t ignore whitespace
    while(true)
    {
        cout << "\nEnter an integer: ";
        cin >> n;
        if(cin.good())
        {
            cin.ignore(10, '\n');
            break;
        } 
        cin.clear();
        cout << "Incorrect input";
        cin.ignore(10, '\n');
    }
    cout << "integer is " << n << endl;

    cin.setf(ios::skipws);
    

    /* Note:
        Inputting Strings and Numbers coming from a disk file:
            Although in normal input operation The user can’t really make any serious errors inputting strings and characters, 
                since all input, even numbers, can be interpreted as a string.
            
            However, if coming from a disk file, characters and strings should still be checked for errors.
            • in case an 'EOF' (End Of File) or something worse is encountered.
                So, you often DO want to ignore whitespace when inputting strings and characters. (Unlike the situation with number.)
    */

    
    // ____________________________________
    /// ► Error-Free Distnace Class:

    Distance d;
    char ans;

    do
    {
        d.get_dist();
        cout << "\nDistance = ";
        d.show_dist();
        cout << "\nDo another (y/n): ";
        cin >> ans;
        cin.ignore(10, '\n');
    } while (ans != 'n');

    
    
    return 0;
}
