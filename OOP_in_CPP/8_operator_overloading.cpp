#include <iostream>
#include <cstring>
#include <stdlib.h>
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
        cout << "Enter feets: ";  cin >> feet;
        cout << "Enter inches: ";   cin >> inches;
    }
    void show_dist() const
    {   cout << feet << "\' " << inches << "\"" << endl; }
    
    Distance operator +(Distance) const;  
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

bool Distance::operator <(Distance d2) const
{
    return ((feet * 12 + inches) < (d2.feet * 12 + inches));
}



// + operator (to concatinate C-strings)
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
    void display() const
    {   cout << str; }

    String operator +(String str2) const;
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
        cout << "String overflow."; 
    }
    return temp;
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

    // < operator (compare English distances)
    if (d1 < d4)
    {   cout << "dist1 < dist4" << endl; }
    else
    {   cout << "dist1 >= dist4" << endl; }

    // + operator (concatinate C-strings)
    String s1("Hello, ");
    String s2 = "all!";
    String s3;
    s3 = s1 + s2;           // concatinate two C-strings
    cout << endl;
    s3.display();
    
    
    return 0;
}
