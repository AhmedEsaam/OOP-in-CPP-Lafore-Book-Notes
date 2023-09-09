#include <iostream>
#include <cstring>
#include <stdlib.h>     // for exit() or #include <process.h>
using namespace std;

/* Here is where the exciting lands ☻ */

// It can transform complex, obscure program listings into intuitively obvious ones. 
// By giving operators additional meanings when applied to user-defined data types.


/* Unary Operators .....................................*/
// ++(prefix) and (postfix)++
class Counter
{
private:
    unsigned int count;
public:
    Counter() : count(0)
    { }
    Counter(int c) : count(c)
    { }
    unsigned int get_count()
    {   return count; }
    Counter operator ++()           // this member func. always has access to the object data, so it doesn't need an argument.
    {
        return Counter(++count);    // nameless object
        // Or:
        // return *this;            // this: is a pointer to the self object (in hand).
    }
    Counter operator ++(int)        // This int isn’t really an argument, and it doesn’t mean integer. 
    {                               // → It’s simply a signal to the compiler to create the postfix version of the operator.   
        return Counter(count++); 
        // Or:
        // Counter temp = *this;
        // count++;
        // return temp;
    }
};


/* Binary Operators ....................................*/
// + operator (to add distances in English format)
// += operator (Arithmetic assign)
// and < operaor (to compare two English Distances)
class Distance
{
private:
    int feet;
    float inches;
    constexpr static const float METER_TO_FEET = 3.280833F;
public:
    // Distance() : feet(0), inches(0.0)
    // {   }
    explicit Distance(int ft = 0, float in = 0.0) : feet(ft), inches(in)
    {   }
    void get_dist()
    {
        cout << "Enter feets: ";    cin >> feet;
        cout << "Enter inches: ";   cin >> inches;
    }
    void show_dist() const
    {   cout << feet << "\' " << inches << "\""; }
    
    Distance operator +(Distance) const;  
    void operator +=(Distance);
    bool operator <(Distance) const;

    /* Data Conversions ____________________*/
    // Convert from meters to Distance. 
    explicit Distance(float meters)      // Distance d = meters;   // Also called conversion constructor
    {
        float fltFeets = meters * METER_TO_FEET;
        feet = static_cast<int>(fltFeets);
        inches = 12 * (fltFeets - feet);
    }

    // Convert from Distance to meters. 
    operator float() const
    {
        float fltFeets = static_cast<float>(feet) + inches / 12;
        return fltFeets/METER_TO_FEET;
    }
};

/* The problem of constructors -that can be called with a single argument- and implicit conversions:
    - Compiler uses that constructor to perform implcit conversions whenever it's necessary Like 
        (Distance == 5) here the compiler convert 5 into a Distance type to make the comparison.
        >> Or when it's in an argumnet like fun(Distance) if the user inputs 
        an integer number instead of a Distance in the argument, the compiler ues the constructor to convert it to a Distance. 
    
    - 'explicit' keyword prevents the compiler from making an implicit conversions using this constructor 
        (that the constructor must be used explicitly not implicitly).

    - As a side effect of the explicit constructor, note that you can’t use the form of object initialization
        that uses an equal sign.
*/


        
Distance Distance::operator +(Distance d2) const        
{
    // the operand in the leftside in (op1 + op2) is the one that the operator is a member of.
    // → so it already have access to its members.
    int f = feet + d2.feet;
    float i = inches + d2.inches;
    if(i >= 12.0)
    {
        i -= 12.0;
        f++;
    }
    return Distance(f, i);
}

void Distance::operator +=(Distance d2)        
{
    feet += d2.feet;
    inches += d2.inches;
    if(inches >= 12.0)
    {
        inches -= 12.0;
        feet++;
    }
}

bool Distance::operator <(Distance d2) const
{
    return ((feet * 12 + inches) < (d2.feet * 12 + inches));
}



// + operator (to concatinate C-strings)
// == operator (to comapre C-strings)
// and [] subscript operator (for safe accessing of C-strings)
class String
{
private:
    static const int SIZE = 80;
    char str[SIZE];
public:
    String()
    {   strcpy(str, ""); }
    String(char s[])    // convert from C-string to String object.
    {   strcpy(str, s); }
    void get_str()
    {   
        cin.ignore();
        cin.get(str, SIZE); 
    }
    void display() const
    {   cout << str; }

    String operator +(String) const;
    bool operator ==(String) const;
    char& operator [](int);

    /* Data Conversions ____________________*/
    // Convert from String object to a C-string.
    operator char*()
    {
        return str;
    }

};


String String::operator +(String s2) const
{
    String temp;
    if(strlen(str) + strlen(s2.str) < SIZE)
    {
        strcpy(temp.str, str);
        strcat(temp.str, s2.str);
    }
    else
    {
        cout << "String overflow."; exit(1); 
    }
    return temp;
}

bool String::operator ==(String s2) const
{   
    return (strcmp(str, s2.str) == 0);
}

char& String::operator [](int i)    // An obj[i] can be used as L-value or R-value, so return by reference.
{
    if(i < 0 || i >= SIZE)
    {   cout << "\nIndex out of bounds"; exit(1); }     // safe array: dosn't allow reading or inserting out of array size.
    return str[i];
}


// Conversions between objects of user-defined types
class Time12;       // forward declaration
class Time24;
#define dest    1   // conversion routines in destination classes 

class Time12
{
private:
    int hrs;
    int mins;
    bool pm;
public:
    // Time12() : hrs(12), mins(0), pm(false)
    // {   }
    explicit Time12(int h = 12, int m = 0, bool p = false) : hrs(h), mins(m), pm(p)
    {   }
    int get_hrs()
    {   return hrs; }
    int get_mins()
    {   return mins; }
    bool get_pm()
    {   return pm; }
    void display() const
    {
        if(hrs < 10) cout << "0";   // extra 0 for 01
        cout << hrs << ":";
        if(mins < 10) cout << "0";
        string am_pm = pm ? " PM" : " AM";
        cout << mins << am_pm;
    }
    
    #if dest
    // Conversion routone: Time12 as destination, from Time24
    Time12(Time24);
    #else
    // Conversion routone: Time12 as source, from Time24
    operator Time24() const;
    #endif
};


class Time24
{
private:
    int hrs;
    int mins;
public:
    Time24() : hrs(0), mins(0)
    {   }
    Time24(int h, int m) : hrs(h), mins(m)
    {   }
    int get_hrs()
    {   return hrs; }
    int get_mins()
    {   return mins; }
    void display() const
    {
        if(hrs < 10) cout << "0";   // extra 0 for 01
        cout << hrs << ":";
        if(mins < 10) cout << "0";
        cout << mins;
    }
    
    #if dest
    // Conversion routone: Time24 as destination from Time12
    Time24(Time12);
    #else
    // Conversion routone: Time24 as source, from Time12
    operator Time12() const;
    #endif
}; 

#if dest
// Coversion routines in Destinations:
Time12::Time12(Time24 t24)      // Time12 ← Time24
{
    int hrs24 = t24.get_hrs();

    hrs =  hrs24 % 12 + ((hrs24 % 12) ? 0 : 12);
    mins = t24.get_mins();
    pm = hrs24 >= 12;
}

Time24::Time24(Time12 t12)      // Time24 ← Time12
{
    hrs = t12.get_hrs() % 12 + (t12.get_pm() ? 12 : 0);
    mins = t12.get_mins();
}


#else
// Coversion routines in Source:
Time12::operator Time24() const     // Time24 ← Time12
{
    int hrs24 = hrs % 12 + (pm ? 12 : 0);
    return Time24(hrs24, mins);
}

Time24::operator Time12() const     // Time12 ← Time24
{
    int hrs12 = hrs % 12 + (hrs % 12 ? 0 : 12);
    bool pm = hrs >= 12;
    return Time12(hrs12, mins, pm);
}
#endif


/* When to put Conversion routines in Destinations, Sources, or both in one class?
    Mostly you can take your pick, However, sometimes the choice is made for you. 
    >> If you have purchased a library of classes, you may not have access
        to their source code. So, you have to put the from and to your class conversion routines in your defined class.
*/

int main()
{
    /* Unary Operators .............................. */
    Counter c1, c2;
    cout << "c1 = " << c1.get_count() << endl;
    cout << "c2 = " << c2.get_count() << endl;
    cout << endl;
    // ++(prefix)    
    ++c1;
    ++c1;
    c2 = ++c1;
    // (postfix)++
    c1++;
    c2 = c1++;
    cout << "c1 = " << c1.get_count() << endl;
    cout << "c2 = " << c2.get_count() << endl;
    cout << endl;


    /* Binary Operators ............................. */
    // + operator (add two English distances)
    // Distance fg = {5, 3.2}; // copy-list initialization (implicitly use copy constructors)
    // fg.show_dist(); cout << endl;

    Distance d1, d2(11, 6.25), d3, d4;
    d1.get_dist();
    d3 = d1 + d2;           // single operator
    d4 = d1 + d2 + d3;      // multible operator
    cout << "d1 = "; d1.show_dist(); cout << endl;
    cout << "d2 = "; d2.show_dist(); cout << endl;
    cout << "d3 = "; d3.show_dist(); cout << endl;
    cout << "d4 = "; d4.show_dist(); cout << endl;

    // += operator (arithmetic add assign)
    d4 += d3;
    cout << "d4 = "; d4.show_dist(); cout << endl;

    // < operator (compare English distances)
    cout << endl;
    if (d1 < d4)
    {   cout << "dist1 < dist4" << endl; }
    else
    {   cout << "dist1 >= dist4" << endl; }

    // + operator (concatinate C-strings)
    String s1("Hello, ");
    String s2 = "all!";
    String s3;
    s3 = s1 + s2;           // concatinate two C-strings
    cout << endl; s3.display(); cout << endl;

    // == operator (compare C-strings)
    String s4 = "Hi", s5;
    cout << "\nEnter string: ";
    s5.get_str();
    if(s4 == s5)
    {   cout << "You entered \"Hi\"." << endl; }
    else
    {   cout << "You did not enter \"Hi\"." << endl; }
    
    // [] operator (safe accessing)
    char ch = s1[0];    // right-value
    cout << "s1[0] = " << ch << endl;

    s1[1] = 'a';        // left-value
    s1.display();
    cout << endl;

    // ch = s1[100];       // accessing index out of SIZE. 
                        // (will throw an error messgae then exit without actually accessing)
    // s1[100] = 'a';



    /* Data Conversion ............................. */

    /*  The compiler doesn’t need any special instructions to use = operator:
        → Normally, when the value of one object is assigned to another of the same type,
          the values of all the member data items are simply copied into the new object.

        When a compiler converts between types implicitly or explicitly, it has internal routines to do so.
        ... But when converting between basic types and user-defined types, we must write these routines ourselves.
    */

    // From meters to English Distance
    Distance d5;
    d5 = static_cast<Distance>(43.59F);
    cout << "\nEnglish Distance = "; d5.show_dist(); cout << endl;;
    // From English Distance to meters
    float meters = static_cast<float>(d5);
    cout << "Float meters = " << meters << endl;
    meters = d5;    // compiler automatically invoke the provided conversion routine
    cout << "Float meters = " << meters << endl;    

    // From C-string to a String object
    char* cs = "Look ";
    String ss = cs;
    // From a String object to a C-string
    cout << endl;
    String ss2 = "who's there!";
    cout << ss << static_cast<char*>(ss2) << endl;
        // ↑ emplicit conversion: the compiler looks for a way to convert ss2 to a type that << does know about, 
        // ... and it finds the operator cast (char*) we provided.
    cs = ss2;       // emplicit conversion: compiler automatically invoke the provided conversion routine
    cout << ss << cs << endl;
    
    
    // Data conversions between user-defined types
    // Time12 ← Time24
    int h, m;
    cout << "\nEnter 24-hour time: "; cin >> h;
    cout << "minutes: "; cin >> m;
    Time24 t24(h, m);
    cout << "You entered: "; t24.display();

    Time12 t12 = t24;
    cout << "\n12-hour time: "; t12.display();
    cout << endl;
    
    // Time24 ← Time12
    char pm_ch;
    cout << "\nEnter 12-hour time: "; cin >> h;
    cout << "minutes: "; cin >> m;
    cout << "p/a: "; cin >> pm_ch;
    Time12 tt12(h, m, pm_ch == 'p');
    cout << "You entered: "; tt12.display();

    Time24 tt24 = tt12;
    cout << "\n24-hour time: "; tt24.display();    

    return 0;
}


/*
    Operator overloading and Type conversions:
        >> give you the opportunity to create what amounts to an entirely new language. 
        -   it can make your listing more intuitive and readable,
            It can also have the opposite effect, making your listing more obscure and hard to understand
    
       - Guidelines to use them in a convenient way:
        • Use Similar Meanings for Similar Syntax:
            >> Use overloaded operators to perform operations that are as similar as possible 
            to those performed on basic data types. (ex: a = b + c; + operator must be used to perform operation like or close to addition.)

            >> Use overloaded operators in the same way you use basic types.
            If you overload one arithmetic operator, you may for consistency want to overload all of them. This will prevent confusion.
        
        •  Show Restraint and Avoid Ambiguity:
            >> Use overloaded operators sparingly, and only when the usage is obvious. 
            When the meaning is not close enough to any operator, use a function instead, as its name would provide the meaning.
            >> Use the operator overloading sparingly as anyone unfamiliar with your listing will need to do considerable research
            to find out what a statement means.

        - In data converion if you wrote the conversion routine from one data type to another twice,
            one in the Destination (as a one-arg. constructor) and one in the Source (as a conversion operator.),
            >> The compiler will signal an error (as the compiler does not like to be placed in a situation where 
                it doesn’t know what to do, )

        - You can’t overload a binary operator to be a unary operator, or vice versa.

        - Not all operators can be overloaded.
            (. , :: , ?: , -> , creating new operators) cannot be overloaded.

        

 
*/