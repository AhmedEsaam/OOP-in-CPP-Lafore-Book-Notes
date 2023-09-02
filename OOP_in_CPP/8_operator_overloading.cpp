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
public:
    Distance() : feet(0), inches(0.0)
    {   }
    Distance(int ft, float in) : feet(ft), inches(in)
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
};
        

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
    String(char s[])
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

    ch = s1[100];       // accessing index out of SIZE. 
                        // (will throw an error messgae then exit without actually accessing)
    s1[100] = 'a';

    
    return 0;
}
