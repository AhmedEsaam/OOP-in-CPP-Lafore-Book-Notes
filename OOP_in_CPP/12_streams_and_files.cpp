#include <iostream>
#include <fstream>          // for file I/O
#include <iomanip>          // for manipulators
// #include <strstream>
#include <string>
#include <cstdlib>
#include <process.h>        // for exit()
#include <typeinfo>         // for typeid()

using namespace std;

// A 'stream' is a general name given to a flow of data.
/* 
    A stream is a sequence of bytes. 
    In the NTFS file system, streams contain 
    - the data that is written to a file, 
    - and that gives more information about a file than attributes and properties. 
        (For example, you can create a stream that contains search keywords, or the identity of the user account that creates a file.)
*/

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
/* Classes:
    • 'ifstream'    for input                   (is derived from 'istream')
    • 'ofstream'    for output                  (is derived from 'ostream')
    • 'fstream'     for both input and output   (is derived from 'iostream')

    // They are also derived, by multiple inheritance, from the 'fstreambase' class. 
    // The 'ifstream', 'ofstream', and 'fstream' classes are declared in the <fstream> file.
*/

/* CAUTION:
    ○   Disk I/O used in C++ is quite different from that in C.
    ○   The old C functions, such as fread() and fwrite(), will still work in C++.
    ○   Be careful about mixing the old C functions with C++ streams. They don’t always work together gracefully.
*/


/// ♦ Object I/O ♦ ///////////////////////////////////////////////////////////
// How user-defined objects can be written to and read from disk?

class Person                                
{
private:
    char name[40];
    short age;
public:
    void getData()
    {   
        cout << "Enter name: "; cin >> name; 
        cout << "Enter age: ";  cin >> age; 
    }
    void showData() const
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
    void diskIn(string, int);                       // read from file
    void diskOut(string);                           // write to file
    static int diskCount(string);                         // return number of persons in file
};  



/// ♦ File I/O with Member Functions ♦ ////////////////////////////////////////////////

// -------------------------------------------------------------------
/// ■ Member functons that allow objects to Read and Write Themselves:
void Person::diskIn(string fname, int perNum)
{
    ifstream infile;
    infile.open(fname, ios::binary);
    infile.seekg(perNum * sizeof(Person));          // move file 'get' pointer to the specific Person
    infile.read((char *)this, sizeof(*this));       // read one Person
}

void Person::diskOut(string fname)
{
    ofstream outfile;
    outfile.open(fname, ios::app | ios::binary);
    outfile.write((char *)this, sizeof(*this));      // write one Person
}

int Person::diskCount(string fname)
{
    ifstream infile;
    infile.open(fname, ios::binary);
    infile.seekg(0, ios::end);                      // move 'get' pointer to end of file
    return (int)infile.tellg() / sizeof(Person);    // calculate number of Person objects
}


// -------------------------------------------------------------------
/// ■ Classes That Read and Write Themselves:
// let’s make a further assumption: that the objects stored in memory are different sizes.
//  →  This situation typically arises when several classes are derived from a base class. 

const int LEN = 32;                                 // maximum length of the last names
const int MAXEM = 100; 

enum employee_type {t_manager, t_scientist, t_laborer};                             // maximum number of employees

class Employee
{
private:
    char name[LEN];                                 // employee name
    unsigned long number; 
protected:                          // employee number
    static int total;                               // current number of employees
    static Employee* arrpEmp[];                     // array of pointers to Employees
public:
    virtual void getData()
    {
        cin.ignore(10, '\n');
        cout << "\nEnter last name: ";          cin >> name;
        cout << "\nEnter employee number: ";    cin >> number;
    }
    virtual void putData()
    {
        cout << "\n Name: " << name;
        cout << "\n Employee number: " << number;
    }
    virtual employee_type getType();               // get type
    static void add();                              // add an employee
    static void display();                       // display all employee
    static void read(string);                             // read from disk file
    static void write(string);                            // write to disk file
};

// static variables
int Employee::total;                                // current number of employees
Employee* Employee::arrpEmp[MAXEM];                 // array of pointers to Employees


// Manager class
class Manager : public Employee
{
private:
    char title[LEN];                                // "Executive Manager" etc.
    double dues;                                    // golf club dues
public:
    Manager()
    { Employee::arrpEmp[Employee::total++] = this; }
    void getData()
    {
        Employee::getData();
        cout << "\nEnter title: ";              cin >> title;
        cout << "\nEnter golf club dues: ";     cin >> dues;
    }
    void putData()
    {
        Employee::putData();
        cout << "\nTitle: " << title;
        cout << "\nGolf club dues: " << dues;
    }
};


// Scientist class
class Scientist : public Employee
{
private:
    int pubs;                                       // Number of publication
public:
    Scientist()
    { Employee::arrpEmp[Employee::total++] = this; }
    void getData()
    {
        Employee::getData();
        cout << "\nEnter number of publications: ";     cin >> pubs;
    }
    void putData()
    {
        Employee::putData();
        cout << "\nNumber of publications: " << pubs;
    }
};


// Laborer class
class Laborer : public Employee
{ 
public:
    Laborer()
    { Employee::arrpEmp[Employee::total++] = this; }
};


///////////// Functions definitions ///////////

// return the type of 'this' object 
employee_type Employee::getType()
{
    if (typeid(*this) == typeid(Manager))
        return t_manager;
    else if (typeid(*this) == typeid(Scientist))
        return t_manager;
    else if (typeid(*this) == typeid(Laborer))
        return t_manager;
    else
        { cerr << "\nBad Employee type";    exit(1); }
    
    return t_manager;
}

// display all employees
void Employee::display()
{
    for (int i = 0; i < total; i++)
    {
        cout << (i+1);
        switch(arrpEmp[i]->getType())
        {
        case t_manager:     cout << ". Type: Mnager";       break;
        case t_scientist:   cout << ". Type: Scientist";    break;
        case t_laborer:     cout << ". Type: Laborer";      break;
        default:            cout << ". Unknown type";
        }
        arrpEmp[i]->putData();                      // display employee data
        cout << endl;
    }
}

// write all current memory objects to file
void Employee::write(string fname)
{
    int size;
    cout << "\nWriting " << total << " employees.";
    ofstream ouf;
    employee_type etype;
    
    ouf.open(fname, ios::trunc | ios::binary);
    if(!ouf)
        { cerr << "\nCould not open input file";   return; }

    // for every employee object ...
    for (int i = 0; i < total; i++)                 
    {
        // ... get it's type
        etype = arrpEmp[i]->getType();              
        // write its type to file
        ouf.write((char *)&etype, sizeof(etype));   

        // find it's size
        switch(etype)                               
        {
        case t_manager:     size = sizeof(Manager);     break;
        case t_scientist:   size = sizeof(Scientist);   break;
        case t_laborer:     size = sizeof(Laborer);     break;
        default:            cerr << "\nBad Employee type";
        }

        // then, write it to file
        ouf.write((char *)arrpEmp[i], size);        
        if(!ouf)
            { cerr << "\nCould write to file";  return; }
    }
}





//////////////////////////////////////////////////////////////////////////////////////////////
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
        seekg(position)                 // Set distance (in bytes) of file pointer from start of file.
        seekg(position, seek_dir)       // Set distance (in bytes) of file pointer from specified place in file. seek_dir can be ios::beg, ios::cur, ios::end.
        pos = tellg()                   // Return position (in bytes) of file pointer from start of file.
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
        goodbit             // 0: No errors (no flags set, value = 0)
        eofbit              // 2: Reached end of file (Note: it's only set when you attempt to read or write NOT when the stream objects reaches the EOF in a previous operation)
        failbit             // 4: Operation failed (user error, premature EOF)
        badbit              // 1: Invalid operation (no associated streambuf)
        hardfail            // Unrecoverable error
    */
    
    /* Functions for Error-Status Flags:__________________________
        int = eof();        // Returns true if EOF flag set (Note: it's only set when you attempt to read or write NOT when the stream objects reaches the EOF in a previous operation)
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

    Distance dist;
    char ans;

    do
    {
        dist.get_dist();
        cout << "\nDistance = ";
        dist.show_dist();
        cout << "\nDo another (y/n): ";
        cin >> ans;
        cin.ignore(10, '\n');
    } while (ans == 'y');

    

    /// ♦ Disk File I/O with Streams ♦ //////////////////////////////////////////////////////
    char ch = 'x';
    int i = 55;                                 // numbers stored as a series of characters
    double d = 6.06;
    string str1 = "disk";                       // strings without
    string str2 = "file";                       //      embedded spaces

    // ► Reading Data: - - - - - - - - - - 
    ofstream outfile("outfiles/fdata.txt");     // create 'ofstream' object
    // This initialization sets aside various resources for the file, and accesses or opens the file of that name on the disk. 
    // If the file doesn’t exist, it is created. If it does exist, it is truncated and the new data replaces the old.
    outfile << ch                               // insert (write) data into 'ofstream' object
            << i    
            << ' '                              // put delimeters ' ' to easily extract numbers and strings later on.
            << d
            << str1                             // a string after a number → the number can be extracted
            << ' ' 
            << str2;

    cout << "\nFile written\n";
    // We don’t need to close the file explicitly
    //  → because, When the program terminates, the outfile object goes out of scope. This calls its destructor, which closes the file


    // ► Writing Data: - - - - - - - - - - 
    ifstream infile("outfiles/fdata.txt");      // create ifstream object
    // The file is automatically opened when the object is created.
    infile >> ch >> i >> d >> str1 >> str2;     // extract (read) data from 'ifstream' object

    cout    << ch << endl
            << i << endl
            << d << endl
            << str1 << endl
            << str2 << endl;
    
    cout << endl;
    

    /// ■ Insertion/Extraction (char*) C-Style Strings: - - - - - -  
    
    // Many stream operations work more easily with char* strings.
    
    /* What if you need to extract a char* (C-Style) string with embedded blanks (spaces)?
        But the extraction operator only recognizes spaces as delimeters!
        → This is a benefit of 'getline()' where you can use another delimeter.
    */

    // Insertion (char* strings):
    ofstream outfile2("outfiles/fdata_c_style_strings.txt");
    
    outfile2 << "I fear three, ancient Mariner!\n";
    outfile2 << "I fear any skinny hand\n";
    outfile2 << "And thou art long, and lank, and brown,\n";
    outfile2 << "As is the ribbed sea sand.\n";
    outfile2.seekp(0);                          // set file pointer from start of file 
    //                                          // Or: outfile2.close();

    // Extraction (char* strings):
    const int MAX = 80;                         // size of buffer
    char buffer[MAX];                           // char array buffer
    ifstream infile2("outfiles/fdata_c_style_strings.txt");

    while(!infile2.eof())                       // until end-of-file (The EOF is a signal sent to the program from the operating system when there is no more data to read)
    {
        infile2.getline(buffer, MAX);           // read a line -without the delimiting character (typically '\n')
        cout << buffer << endl;
    }

    //or: while(infile2.good())                 // until any error encountered
    //or: while(infile2)                        // until any error encountered
    //  • Any stream object, such as infile, has a value that can be tested for the usual error conditions, including EOF.
    //  → If any such condition is true, the object returns a 'zero' value. 
    //  → If everything is going well, the object returns a 'nonzero' value.



    /// ♦ Character I/O ♦ ///////////////////////////////////////////////////////////
    // ► put(char) for writing:
    string str =    "Time is a great teacher, but unfortunately "
                    "it kills all its pupils.";

    ofstream outfilechar("outfiles/fdata_chars.txt");
    for (int i = 0; i < str.size(); i++)        // for each character
        outfilechar.put(str[i]);                // write it to file

    cout << "File written\n";
    outfilechar.seekp(0);
    

    // ► get(char) for reading:
    char _ch;
    ifstream infilechar("outfiles/fdata_chars.txt");
    while(infilechar)
    {
        infilechar.get(_ch);
        cout << _ch;
    }
    cout << endl;
    infilechar.close();                         //  closing stream explicitly: this invokes its destructor and closes the associated file (Note: streams are closed automatically when they go out of scope)
    

    // Another approach to reading is rdbuf():
    infilechar.open("outfiles/fdata_chars.txt");    // you must open the file from the beginning, seekg(0) will not work with rdbuf()!        
    cout << infilechar.rdbuf() << endl;
    /*
        rdbuf() is a member of the 'ios' class, it returns a pointer to the streambuf (or filebuf) object
        associated with the stream object (ifstream object). This object contains a buffer that holds the
        characters read from the stream, So you can use this pointer as a data object in its own right.  
        • The rdbuf() function knows that it should return when it encounters an EOF.
    */
    

    /// ♦ Binary I/O ♦ ///////////////////////////////////////////////////////////

    /* If you're storing a large amount of numerical data it's more efficient to use binary I/O, 
        → in which numbers are stored as they are in the computer's RAM memory, rather than as strings of charcters. 

        ex. An int is stored in 4 bytes, whereas its text version might be "12345", requiring 4 bytes.
            Similarly, a float is always stored in 4 bytes, while its formatted version might be “6.02314e13”, requiring 10 bytes. 

        ■ write() and read() functions think about data in terms of bytes. They on't care how the data is formatted.
            → They simply transfer a buffer full of bytes from and to a disk.
            → Their parameters:
                • The address of the data buffer    (must be cast, using reinterpret_cast, to type char*)
                • The length in bytes               (not the number of data items in the buffer) 
    */

    int buff[MAX];
    for (int i = 0; i < MAX; i++)
        buff[i] = i;                            // fill buffer with data


    // ► write:
    ofstream os("outfiles/bdata.dat", ios::binary);     // You must use the mode bit: 'ios::binary' argument when working with binary data 
                                                        // ... This is because the default, text mode, takes some liberties with the data which in turn makes a formatted text file more readable by DOS-based utilities such as TYPE.
                                                        //      For example, in text mode the ‘\n’ character is expanded into two bytes before being stored to disk —a carriagereturn and a linefeed— 
                                                        //      hence, every byte that happens to have the ASCII value 10 is translated into 2 bytes.
    os.write(reinterpret_cast<char*>(buff), MAX*sizeof(int));       
    // The reinterpret_cast operator: It changes the type of a section of memory without caring whether it makes sense, so it’s up to you to use it judiciously.
    // You can also use reinterpret_cast to change pointer values into integers and vice versa. This is a dangerous practice, but one which is sometimes necessary.
    os.close();                                 // must close the output stream

    for (int i = 0; i < MAX; i++)
        buff[i] = 0;                            // erase buffer
    

    // ► read:
    ifstream is("outfiles/bdata.dat", ios::binary);

    is.read(reinterpret_cast<char*>(buff), MAX*sizeof(int));

    for (int i = 0; i < MAX; i++)
        if (buff[i] != i)                       // check data
            { cerr << "Data is incorrect\n";    return 1; }
    
    cout << "Data is correct\n";
    cout << endl;
    


    /// ♦ Object I/O ♦ ///////////////////////////////////////////////////////////
    // To store objects' data into disk and read it.

    // When writing an object, we generally want to use binary mode
    // → This writes the same bit configuration to disk that was stored in memory.
    // → And ensures that numerical data contained in objects is handled properly.
    cin.setf(ios::skipws);
    
    Person per, _per;
    per.getData();

    // ► Write (store object):
    ofstream outfile_Person("outfiles/person.dat", ios::binary);
    outfile_Person.write(reinterpret_cast<char*>(&per), sizeof(per));

    outfile_Person.close();


    // ► Read (extract object):
    ifstream infile_Person("outfiles/person.dat", ios::binary);
    infile_Person.read(reinterpret_cast<char*>(&_per), sizeof(_per));

    _per.showData();
    
    /* Note:
        • It doesn’t matter what member functions you use, since they are not written to disk along with the object’s data.
            → The data must have the same format, but inconsistencies in the member functions have no effect.
        ◘ However, this is true only in simple classes that don’t use virtual functions.
    */

    /* CAUTIONS:
        • Make sure a class used to read an object is identical to the class used to write it.
            → With classes that use virtual funcions, objects derived from these classes include a mysterious number placed just before the object’s data in memory.
            → This number is called the vtable pointer. It helps identify the object’s class when virtual functions are used.
            → For every other class which have different member functions, this number changes as well.
            → So, If you write an object of one class to a file, and then read it back into an object of a class that has identical data but a different member function, 
                you’ll encounter big trouble if you try to use virtual functions on the object.

        • You should not attempt to perform disk I/O with objects that have pointer data members.
            → As the pointer values won’t be correct when the object is read back into a different place in memory.
    */



    /// ♦ I/O with Multiple Objects ♦ /////////////////////////////////////////////////////
    char ch_;
    Person per_;
    fstream file_;                               // input/output file stream

    // We create the file in one statement and open it in another, using the open() function.
    //  → This is a useful approach in situations where the open may fail.
    //      (You can create a stream object once, and then try repeatedly to open it, without the overhead of creating a new stream object each time.)
    file_.open("outfiles/group.dat", ios::app | ios::out | ios::in | ios::binary);

    /* ■ Mode Bits:
        • (Mode specifiers or flags). They are defined in 'ios'
        • Specify various aspects of how a stream object will be opened.
        • The vertical bars (Bit-wise OR) between the flags cause the bits representing these flags to be logically combined into a single integer, 
            → so that several flags can apply simultaneously

        TABLE: Mode Bits for the open() Function:
        _________________________________________________________________________________________________
        Mode Bit        Result
        _________________________________________________________________________________________________
        in              Open for reading (default for ifstream)
        out             Open for writing (default for ofstream) - but doesn't remove the old contents (So the new contents will overlay what's already there).
        ate             Start reading or writing at end of file (AT End)
        app             Start writing at end of file (APPend) (preserve whatever was in the file before)
        trunc           Truncate file to zero length if it exists (TRUNCate)
        nocreate        (Do not create the file if not existed) 
                        - Error when opening if file does not already exist.
        noreplace       (Do not replace file when writing if the file existed except if you append using 'ios::app' or 'ios::ate')
                        - Error when opening for output if file already exists, unless ate or app is set.
        binary          Open file in binary (not text) mode
    */  

    // ► Write:
    do
    {
        cout << "\nEnter person's data:\n";
        per_.getData();

        file_.write(reinterpret_cast<char*>(&per_), sizeof(per_));
        cout << "Enter another person (y/n)? ";
        cin >> ch_;
    } while (ch_ == 'y');

    file_.seekg(0);                              // reset 'get' pointer to start-of-file


    // ► Read:
    // file_.read(reinterpret_cast<char*>(&per_), sizeof(per_));
    // while(!file_.eof())
    // {
    //     cout << "\nPerson:\n";
    //     per_.showData();
    //     file_.read(reinterpret_cast<char*>(&per_), sizeof(per_));
    // }
    // cout << endl;
    
    while(file_.read(reinterpret_cast<char*>(&per_), sizeof(per_)))
    {   
        cout << "\nPerson:\n";
        per_.showData();
    }
    cout << endl;



    // file.close();
    
    /// ♦ File Pointers ♦ /////////////////////////////////////////////////////
    /*
        • They are not pointers used as address variables.
        • They are used as a means of referring to a specific location in a file.
            → They specify the byte number in the file where writing or reading will take place

        • Each file object has associated with it two integer values:
            ► 'get' pointer (current get position) - for reading
                seekg(position)                 // Set distance (in bytes) of file pointer from start of file.
                seekg(position, seek_dir)       // Set offset (in bytes) of file pointer from specified location in file. seek_dir can be ios::beg, ios::cur, ios::end.
                pos = tellg()                   // Return position (in bytes) of file pointer from start of file.

            ► 'put' pointer (current put position) - for writing
                seekp(position)                 // Set distance (in bytes) of file pointer from start of file. (Note: seekp() has no effect if the ios::app is used; then every write goes at the end of the file.)
                seekp(position, seek_dir)       // Set offset (in bytes) of file pointer from specified location in file. seek_dir can be ios::beg, ios::cur, ios::end.
                pos = tellp()                   // Return position of file pointer, in bytes.

                ex. seekp(-10, ios::end);
                // will set the 'put' pointer to 10 bytes before the end of the file.

        • The previous functions take one argument, which represents the absolute position in the file in bytes.
            (The start of the file is byte 0.)
        • There are times when you must take control of the file pointers yourself 
            so that you can read from and write to an arbitrary location in the file.
    */
    
    /// EXAMPLE: get number of objects in the file, and show specific object: - - - - - - - - - - -
    Person pers;
    ifstream in_file;
    in_file.open("outfiles/group.dat", ios::in | ios::binary);

    // Calculate number of Person objects in file:
    in_file.seekg(0, ios::end);                 // go to 0 bytes from end 
    int endposition = in_file.tellg();          // get current position (which is the end of file)
    int total = endposition / sizeof(Person);
    cout << "\nThere are " << total << " persons in file" << endl;

    // Show specific Person object:
    int num, position;
    do
    {
        cout << "\nEnter person number: ";      // starting from 1
        cin >> num;
        position = (num - 1) * sizeof(Person);
        in_file.seekg(position);
        in_file.read(reinterpret_cast<char*>(&pers), sizeof(pers));
        pers.showData();

        cout << "Enter another (y/n)? ";
        cin >> ch_;
    } while (ch_ == 'y');
    
    
    
    /// ♦ Error Handling in File I/O ♦ ////////////////////////////////////////////////

    /// ■ By checking the return value from the stream object itself to determine its error status.
    //      → it returns a pointer value if everything went well, but 0 if it didn’t.

    const int MAX_ = 1000;
    int buff_[MAX_];

    // fill buffer with data
    for (int i = 0; i < MAX_; i++)              
        buff_[i] = i;
    
    // ► writing an array to a file
    ofstream os_;
    os_.open("outfiles/a:edata.dat", ios::trunc | ios::binary);         // 'edata.dat' is a stream of the file 'a', refer to: https://stackoverflow.com/questions/77240735/using-a-file-path-with-a-colon-in-windows-file-system
    if(!os_)
        { cerr << "\nCould not open output file";   exit(1); }
    
    cout << "\nWriting...";
    os_.write(reinterpret_cast<char*>(buff_), MAX_ * sizeof(int));
    if(!os_)
        { cerr << "\nCould not write to file";   exit(1); }
    os_.close();


    // clear buffer
    for (int i = 0; i < MAX_; i++)
        buff_[i] = 0;


    // ► reading an array from a file
    ifstream is_;
    is_.open("outfiles/a:edata.dat", ios::binary);
    if(!is_)
        { cerr << "\nCould not open input file";   exit(1); }
    
    cout << "\nReading...";
    is_.read(reinterpret_cast<char*>(buff_), MAX_ * sizeof(int));
    if(!is_)
        { cerr << "\nCould not read from file";   exit(1); }
    is_.close();


    // check data
    for (int i = 0; i < MAX_; i++)
        if(buff_[i] != i)
            { cerr << "\nData is incorrect\n";  exit(1); }

    cout << "\nData is correct\n";


    // -----------------------------------------------------------------------------------------------------    
    /// ■ Using the 'ios' error-status flags to find out more specific information about a file I/O error:
    ifstream file;
    file.open("outfiles/a:test.dat");                   // 'test.dat' is another stream of the file 'a'

    if(!file)
        cout << "\nCan't open file";
    else
        cout << "\nFile opened successfully";

    cout << "\nfile = "         << &file;
    cout << "\nError state = "  << file.rdstate();      // returns 4 : returns the flag that is set to 1, here (failbit) which indicates that the file doesn’t exist.
    cout << "\ngood() = "       << file.good();         // returns 0 : the good bit is set to 1 (true) only when no bits are set, so it returns 0 (false)
    cout << "\neof() = "        << file.eof();          // returns 0 : we're not at EOF (end-of-file)
    cout << "\nfail() = "       << file.fail();         // returns a non-zero value : since an error occured; operation failed (if 'failbit' or 'badbit' or 'hardfail' flag set)
    cout << "\nbad() = "        << file.bad();          // returns 0 : it only return 1 if 'badbit' or 'hardfail' flag set
    cout << endl;
    file.close();

    // In a serious program, some or all of these functions should be used after every I/O operation to ensure that things went as expected.
    
    

    /// ♦ File I/O with Member Functions ♦ ////////////////////////////////////////////////

    /// ■ Objects That Read and Write Themselves: - - - - - - - - -
    // This is a simple approach, and works well if there aren’t many objects to be read or written at once. 
    Person per1;
    string fname = "outfiles/personFile.dat";

    // write to disk
    do
    {
        cout << "\nEnter person's data:\n";
        per1.getData();
        per1.diskOut(fname);

        cout << "\nDo another (y/n)? ";
        cin >> ch;
    } while(ch == 'y');

    // print number of Person objects in file
    int per_total = Person::diskCount(fname);
    cout << "\nThere are " << per_total << " persons in file.\n";
    
    // read from disk
    for (int i = 0; i < per_total; i++)
    {
        cout << "\nPerson " << i << endl;
        per1.diskIn(fname, i);
        per1.showData();
    }
    cout << endl;
    
    
    /// ■ Classes That Read and Write Themselves: - - - - - - - - -
    //  It’s much faster—and the more objects there are the truer this is—to open the file once, write all the objects to it, and then close it.

        
    
    
        
    return 0;
}
