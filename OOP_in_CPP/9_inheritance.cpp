#include <iostream>
#include <process.h>    //for exit()
#include <string>
using namespace std;

/* Why we need Inheritance?
    • It permits code reusability; Reusing existing code saves time and money and increases a program’s reliability. 
    • The ease of distributing class libraries; A programmer can use a class created by another 
        person or company, and, without modifying it, derive other classes from it that are 
        suited to particular situations.

        ► Programmer A creates a general-purpose programming tool (i.e. class).
        ► Programmer B creates a specialized version of this class (He may not have access to the source code for this class). 
            (B likes the class A, but thinks it could be improved, so he creates a new class 
            that is derived from class A but incorporates the extensions necessary.)
        ► Programmers C and D create applications (use the specialized version that B provided.) 
        
        - A is a tool developer, and C and D are applications developers. B is somewhere in between.
            (distinction between software tool developers and application writers is becoming blurred.)

    • Helps in the original conceptualization of a programming problem and in the overall design of the program.
    • Testing and Debugging becomes easier:
        In large and complex classes, if they work well and undergone many hours of testing and debugging,
        if we start fooling around with the source code for the class, the testing process will
        need to be carried out again, so it's better to make a derived class.
    • Code security: 
        We might not have access to the class source code any way, especially if it was distributed
        as part of a class library.
*/


class Counter
{
protected:  // members are still hidden but only give access within derived classes member functions
    unsigned int count;

public:
    Counter() : count(0)
    {   }
    Counter(int c) : count(c)
    {   }
    unsigned int get_count() const
    {   return count; }
    Counter operator ++()   // prefix
    {   return Counter(++count); }
};

// Derived class 
// (Takes a copy of all the Base class members. However accessibility to each one of them is specified according to what the Base class decided)
class CountDn : public Counter
{
public:
    // The compiler will substitute a no-argument constructor from the base class if it does not exist, 
    //  but it draws the line at more complex constructors; 
    //  (so the one-arg. constructor is not substituted. if not existed)
    //  So, we have to write a new set of constructors for the derived class:
    
    CountDn() : Counter(0)      // this constructor calls the Base class constructor (and also can be omitted)
    {   }                       // you want to initialize any vars (including private ones) whether thay are in the parent or the child.
    CountDn(int c) : Counter(c)
    {   }
    CountDn operator --()
    {   return CountDn(--count); }
};

/* ACCESS SPECIFIERS: ..........................................................................................
    private:    members can be accessed within the class, but not outside it (that includes derived classes).
    public:     members can be accessed outside the class (that includes derived classes members).
    protected:  members can be accessed within the class, but not outside it (exept for derived classes).
        (derived class member functions can access public or protected members of the base class.)
*/

/* TABLE: Inheritance and Accessibility:
_______________________________________________________________________________________
    Access          Accessible from         Accessible from         Accessible from
   Specifier           Own Class             Derived Class       Objects Outside Class
_______________________________________________________________________________________
    public                yes                     yes                    yes
    protected             yes                     yes                    no
    private               yes                     no                     no
_______________________________________________________________________________________
*/

/* Class being inheritance ready:
    If you are writing a class that you suspect might be used, at any point in the
        future, as a base class for other classes,
    >> then any member data that the derived classes might need to access should be made
        protected rather than private.
*/

/* Disadvantage of using 'protected' class members:
    - Any programmer who buys thi class library can access protected members of your classes
        simply by deriving other classes from them.
    >> This makes protected members considerably less secure and prone to corruption than private members.
    → So, it’s often safer to force derived classes to access data in the base class using only
        public functions in the base class. 
*/

/* Inheritance glossary:
    base class  ← derived class
    superclass  ← subclass
    parent      ← child
*/


/* OVERRIDING FUNCTIONS ..................................................................................*/
class Stack
{
protected:
    static const int MAX = 3;
    int st[MAX];
    int top;

public:
    Stack() : top(-1)
    {   }
    void push(int var)
    {   st[++top] = var; }
    int pop()
    {   return st[top--]; }
};


class Stack2 : public Stack
{
public:
    void push(int var)
    {
        if(top >= MAX-1)
        {   cout << "\nError: stack is full"; exit(1); }
        Stack::push(var);
    }
    int pop()
    {
        if(top < 0)
        {   cout << "\nError: stack is empty"; exit(1); }
        return Stack::pop();
    }
};


// the derived class private members:
class Distance
{
protected:
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
    void show_raw() const
    {   cout << feet << ", " << inches;}
};


// enum posneg {pos, neg};
class DistSign : public Distance
/* Note:
    If the derived class overrides all public member functins in Base classes, 
    then it makes no differnce in choosing a public or private derivation.
*/
{
public:
    enum posneg {pos, neg};
private:
    posneg sign;
public:
    DistSign() : Distance(), sign(pos)
    {   }
    // 2- or 3-arg constructor:
    DistSign(int ft, float in, posneg sg = pos) : Distance(ft, in), sign(sg)
    {   }
    void get_dist()
    {
        Distance::get_dist();
        char ch;
        cout << "Enter sign (+ or -): ";    cin >> ch;
        sign = (ch == '+') ? pos : neg;
    }
    void show_dist()
    {
        cout << ((sign == pos) ? "+ " : "- ");
        Distance::show_dist();
    }
};



/* Public and Private Inheritance ..............................................................*/
// C++ provides a wealth of ways to fine-tune access to class members.
/*
    • public:   specifies that objects of the derived class are able to access public member functions
                 of the base class.
    • private (default):  objects of the derived class cannot access public member functions of the base class.
*/

// When to ise what?
/*
    ■ public derivation is appropriate: for objects of the derived class to access the public
        functions of the base class if they want to perform a basic operation.
    
    ■ private derivation: would allow you to conceal all the Base class functions from objects of
        the derived class. That is if the derived class completely modifyies the operations of the base class, 
        hiding or disguising its original interface.
*/

/* INHERITANCE EXAMPLE (Employees)..............................................................*/
// here is an example where the inheritance helps in the overall design of the program.
// A class hierarchy results from generalizing common characteristics.
// "Abstract" base class:
class Employee
{
protected:
    static const int LEN = 80;
private:
    char name[LEN];
    unsigned long id;
public:
    void get_data()
    {
        cout << "Enter last name: ";    cin >> name;
        cout << "Enter ID: ";           cin >> id;
    }
    void put_data() const
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
    }
};

// Derived classes:
class Manager : private Employee
{
private:
    char title[LEN];
    double dues;
public:
    void getData()
    {
        Employee::get_data();
        cout << "Enter title: ";            cin >> title;
        cout << "Enter golf club dues: ";   cin >> dues;
    }
    void putData() const
    {
        Employee::put_data();
        cout << "Title: " << title << endl;
        cout << "Golf club dues: " << dues << endl;
    }
};

class Laborer : public Employee
{   };


/* MULTI_LEVEL INHERITANCE ..................................................................... */ 
// Foreman derived from Laborer (However, he oversees a group of laborers. He's like a laborers leader)
class Foreman : Laborer     // private by default (but it's better to put it anyway)   
{
private:
    float quotas;       // percent of quotas met successfully
public:
    void getData()
    {
        Laborer::get_data();
        cout << "Enter quotas: ";   cin >> quotas;
    }
    void putData() const
    {
        Employee::put_data();
        cout << "Quotas: " << quotas << endl;
    }
};

/* Class hierarchy is not necessarily the same as an organization chart;
    - for examle: As class hierarchy results from generalizing common characteristics.
        (The more general the class, the higher it is on the chart),

        >> Thus, a laborer is more general than a foreman, (who is a specialized kind of laborer).
        * So, laborer is shown above foreman in the class hierarchy, 
            although a foreman is probably paid more than a laborer (Above him in the organization chart).
*/


/* MULTIPLE INHERITANCE ..................................................................... */ 
class Student
{
private:
    static const int SIZE = 80;
    char school[SIZE];
    char degree[SIZE];
public:
    void get_edu()
    {
        cout << "Enter name of school or university: ";     cin >> school;
        cout << "Enter name of highest degree: ";           cin >> degree;
    }
    void put_edu() const
    {
        cout << "School or university: " << school << endl;
        cout << "Highest degree reveived: " << degree << endl;
    }
};

class Scientist : private Employee, private Student  
{
private:
    int pubs;
public:
    void getData()
    {
        Employee::get_data();
        cout << "Enter number of publications: ";   cin >> pubs;
        Student::get_edu();
    }
    void putData() const
    {
        Employee::put_data();
        cout << "Number of publications: " << pubs << endl;
        Student::put_edu();
    }
}; 


// Constructors in Multiple Inheritance:
class LumberType
{
private:
    string dimentions;
    string grade;
public:
    LumberType() : dimentions("N/A"), grade("N/A")
    {   }
    LumberType(string di, string gr) : dimentions(di), grade(gr)
    {   }
    void get_type()
    {
        cout << "Enter nominal dimensions (2x4 etc.): ";    cin >> dimentions;
        cout << "Enter grade (rough, const, etc.): ";       cin >> grade;
    }
    void show_type() const
    {
        cout << "Dimentions: " << dimentions << endl;
        cout << "Grade: " << grade << endl;
    }
    void show_raw() const
    {   cout << dimentions << ", " << grade; }
};


#define LUMBER_MULTIPLE_INHERITANCE     1       // (0 or 1)
#if LUMBER_MULTIPLE_INHERITANCE

class Lumber : public LumberType, public Distance
{
private:
    int quantity;
    double price;
public:
    Lumber() : LumberType(), Distance(), quantity(0), price(0)
    {   }
    Lumber  (   string di, string gr, 
                int ft, float in, 
                int qu, double pr 
            ) : 
            LumberType(di, gr), 
            Distance(ft, in), 
            quantity(qu), price(pr)
    {   }
    void getLumber()
    {
        LumberType::get_type();
        Distance::get_dist();
        cout << "Enter quantity: ";         cin >> quantity;
        cout << "Enter price per piece: ";  cin >> price;
    }
    void showLumber() const
    {
        LumberType::show_type();
        cout << "Length: ";
        Distance::show_dist();
        cout    << "\nPrice for " << quantity 
                << " pieces: $" << price * quantity
                << endl;
    }
    void show_raw() const       // overrides all functions with the same name in the Parent classes.
    {   
        LumberType::show_raw(); cout << ", ";
        Distance::show_raw();   cout << ", ";
        cout << quantity << ", " << price << endl;
    }
};


#else /* LUMBER_ASSOCIATED_WITH_DISTANCE */

/* ASSOCIATION ..................................................................... */

// It's better for the Distance of the Lumber to be an attribute in the Lumber class
// rather than being a Parent class.
class Lumber : public LumberType
{
private:
    Distance length;
    int quantity;
    double price;
public:
    Lumber() : LumberType(), length(0, 0.0), quantity(0), price(0)
    {   }
    Lumber  (   string di, string gr, 
                int ft, float in, 
                int qu, double pr 
            ) : 
            LumberType(di, gr), 
            length(ft, in), 
            quantity(qu), price(pr)
    {   }
    void getLumber()
    {
        LumberType::get_type();
        length.get_dist();
        cout << "Enter quantity: ";         cin >> quantity;
        cout << "Enter price per piece: ";  cin >> price;
    }
    void showLumber() const
    {
        LumberType::show_type();
        cout << "Length: ";
        length.show_dist();
        cout    << "\nPrice for " << quantity 
                << " pieces: $" << price * quantity
                << endl;
    }
    void show_raw() const       // overrides all functions with the same name in the Parent classes.
    {   
        LumberType::show_raw(); cout << ", ";
        length.show_raw();      cout << ", ";
        cout << quantity << ", " << price << endl;
    }
};
#endif


/* AGGREGATION ..................................................................... */
class Book
{
private:
    string name;
    string author;
};

class Library   // class 'Library' contains objects of class 'Book', and is organizationally superior to it.
{
private:
    Book books[50];
};



/* COMPOSITION ..................................................................... */
class Door      // Belong only to Car objects, we may not need to declare a 'Door' object separately in the main().  
{
private:
    string color;
    string size;
};

class Car       // class 'Car' "consists of" objects of class 'Door'.
{
private:
    Door doors[4];
};


/*  Classes Relationships /////////////////////////////////////////////////////////////////:
    //-----------------------------------------------------------------------
    ■ Inheritance: is often called a "kind of" relationship.
        like: "Scientist is a kind of Employee"; 
        >> As Scientist has all the characteristics of Employee, and in addition to some of its own.

        ♦ In UML: Sientist -► Employee

    //-----------------------------------------------------------------------
    ■ Association: When 'objects' of classes has some kind of relationship.

        Navigability in Association:
        • if each of the two classes objects call operations in the other class,
            → it's called 'bidirectional' association (there would be arrowheads on both ends of the line.)
        • if it only goes one way,
            → it's called 'unidirectional' association.

        like: "Time12 is associated with Time24" in: (t12 = t24;)
        >> As the Time12 object (t12) calls the opertator function of class Time24 object (t24).

        ♦ In UML: Time12 → Time24

        OR:
            - When one of the member functions of a class has an argument of the other class, 
            then, it must be calling this object member functions.

        OR:
            - When an attribute of one class is an object of another class:
            Like: "Lumber is associated with Distance" in the 2nd implementation of class Lumber;
            >> As class Lumber has an attribute of class Distance.

        ♦ In UML: Lumber → Distance
        
    //-----------------------------------------------------------------------
    ■ Aggregation: is is called a "has a" relationship, it is also called a "part-whole" relationship.
        * In the UML, aggregation is considered a special kind of association.
        
        like: "Library has a Book"; 
        >> As class Library contains objects of class Book, and is organizationally superior to class Book, 
            → then, it’s a good candidate for aggregation.

        ♦ In UML: Library <>- Book         (diamond-shaped arrowhead is open.)
    
    //-----------------------------------------------------------------------
    ■ Composition: is is called a "consists of" relationship.
        It's a stronger form of Aggregation. (It has all the characteristics of aggregation, plus two more):
        • The part may belong to only one whole.
        • The lifetime of the part is the same as the lifetime of the whole. 
        
        like: "Car consists of Door(s)"; 
        >> As The doors can’t belong to some other car, 
        >> and they are born and die along with the car
            (you may not need to declare a Door object separately in the main().)

        ♦ In UML: Car ♦─ Door             (diamond-shaped arrowhead is solid instead of open.)
*/


// Diamond class tree:  
// → an example prone to ambiguity
class A
{
public:
void func()
{   cout << "Hi" << endl; }
};
class B : public A 
{ };
class C : public A
{ };
class D : public B, public C
{ };



///////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Using 'protected' class specifier
    CountDn c1;     // the derived class uses an appropriate constructor from the base class
    ++c1; ++c1;
    cout << "c1 = " << c1.get_count() << endl;
    --c1;
    cout << "c1 = " << c1.get_count() << endl;
       
    // Derived class constructors
    CountDn c2(100);
    cout << "\nc2 = " << c2.get_count() << endl;
    --c2; --c2;
    CountDn c3 = --c2;
    cout << "c3 = " << c3.get_count() << endl;

    // Overriding member functions
    Stack2 s1;
    s1.push(54);
    cout << endl << s1.pop() << endl;;
        // cout << endl << s1.pop();   // Error: empty stack

    // Derived class private members
    DistSign alpha;
    cout << endl;
    alpha.get_dist();
    DistSign beta(15, 6.55);
    DistSign gamma(166, 4.15, DistSign::neg);
    cout << "\nalpha = ";   alpha.show_dist();
    cout << "\nbeta = ";    beta.show_dist();
    cout << "\ngamma = ";   gamma.show_dist();
    cout << endl;

    /// Employees example ..........:
    /* 
        • Public and private derived classes
        • Multi-level inheritance
        • Multiple inheritance
    */
    Manager m1, m2;
    Scientist sc1;  // multiple inheritance 
    Laborer l1;     
    Foreman f1;     // multi-level inheritance
    // get data
    cout << endl << "Enter manager 1 data:-" << endl;
    m1.getData();
        // m1.get_data();  // Manager is privately derived (Manager obj has no access to base class public members)
    cout << endl << "Enter manager 2 data:-" << endl;
    m2.getData();
    cout << endl << "Enter scientist 1 data:-" << endl;
    sc1.getData();
    cout << endl << "Enter laborer 1 data:-" << endl;
    l1.get_data();
    cout << endl << "Enter foreman 1 data:-" << endl;
    f1.getData();
    // display data
    cout << endl << "Manager 1 data:" << endl;
    m1.putData();
    cout << endl << "Manager 2 data:" << endl;
    m2.putData();
    cout << endl << "Sientist 1 data:" << endl;
    sc1.putData();
    cout << endl << "Laborer 1 data:" << endl;
    l1.put_data();  // Laborer is publicly derrived (Laborer obj can access base class public members)
    cout << endl << "Foreman 1 data:" << endl;
    f1.putData();


    // Constructors in Multiple Inheritance:
    Lumber siding;
    cout << "\nSiding data:-" << endl;
    siding.getLumber();
    Lumber studs("2x4", "const", 8, 6.0, 100, 4.75F);
    cout << "\nSiding:-" << endl;   siding.showLumber();
    cout << "\nStuds:-" << endl;    studs.showLumber();
    cout << endl;


    /// !!! Multible Inheritance Ambiguity !!!.............................................:
    
    //-------------------------------------------
    /** 1• When the base classes have the same-name functions
            and the child class has no function with this name and is derived publicly. */

    #if LUMBER_MULTIPLE_INHERITANCE
    // - if show_raw() is not defined in the derived class:
        // siding.show_raw();       // Error: Ambiguous ( which show_raw()? )
    siding.LumberType::show_raw();  cout << endl;
    siding.Distance::show_raw();    cout << endl;
    // - if show_raw() is defined in the derived class: (it overrides all same-name functions in Parent classes)
    siding.show_raw();              cout << endl;
    #endif
    
    //-------------------------------------------
    /** 2• If you derive a class from two classes that are each derived from the same class. 
            This creates a diamond-shaped inheritance tree.*/

    D objD;
        // objD.func();     // Error: Ambiguous 
                            // (Every Base class has a derived copy of the func() from their Base class, 
                            // which one do you invoke? )  
    objD.B::func();
    objD.C::func();
    
    //-------------------------------------------
    /*  Note: The fact that such ambiguities can arise causes many experts to recommend 
        avoiding multiple inheritance altogether!. 
        >>  You should certainly not use it in serious programs 
            unless you have considerable experience. 
    */

    // Coposition:
    Car car1;   // 'Door' objects has been declared and have the same lifetime of car1.


    return 0;
}
