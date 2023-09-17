#include <iostream>
using namespace std;

/*
    Placing data and functions together into a single entity is a central
        idea in object-oriented programming

    Classes are programming language definitions used by compiler to mount the code. 
        Only the class objects instantiated take a memory space on runtime.

    • The data is hidden so it will be safe from accidental manipulation,
    • while the functions that operate on the data are public so they can
        be accessed from outside the class
*/

class smallobj
{
private:
    int data;

public:
    void setData(int d)
    {
        data = d;
        // data is actually: (this->data) and 'this' is an object pointer
        //  that points to "this" object that is calling the function, and it is 
        //  passed to the function as an implicit argument. 
    }
    void showData()
    {
        cout << "Data is " << data << endl;
    }
};

/* Data Hiding (private):
     data is concealed within a class so that it cannot be accessed mistakenly
        by functions outside the class.
*/

/* Functions:
    • (The functions are not definitions in the sense that memory is set aside
        for the function code; this doesn’t happen until an object of the class is created.

    • Member functions defined inside a class this way are created as inline
        functions by default.

    • All the objects in a given class use the same member functions.
        The member functions are created and placed in memory only once
        —when they are defined in the class definition.
*/

/* CONSTRUCTORS and DESTRUCTORS */

class counter
{
private:
    unsigned int count;
    int id;

public:
    counter(int i) : count(0), id(i)
    { /*empty body*/
    }
    ~counter() // no argyments (there's only one way to destroy an object)
    {          /*empty body*/
    }
    void inc_count()
    {
        count++;
    }
    int get_count()
    {
        return count;
    }
};

/*
    • Why not Members in the body of the constructor?
        The reasons are complex, but have to do with the fact that members initialized
        in the initializer list are (given a value before the constructor even starts to execute).

        >> This is important in some situations:
            For example, the initializer list is the only way to initialize
            (const member data and references).

    • Actions more complicated than simple initialization must be carried out in the constructor
        body, as with ordinary functions
*/

class Distance
{
private:
    int feet;
    float inches;
    mutable int ID; 

public:
    // constructor with no arguments
    Distance() : feet(0), inches(0.0), ID(0)
    {
    }
    // constructor with arguments
    Distance(int ft, float in, int id) : feet(ft), inches(in), ID(id)
    {
    }
    // a way to enter values for data members
    void getdist()
    {
        cout << "\nEnter feet: ";
        cin >> feet;
        cout << "Enter inches: ";
        cin >> inches;
    }

    void setfeet(int f)
    {
        feet = f;
    }
    void setID(int id) const   
    {
        this->ID = id;
        // this function can be called with const Distance object.
        // Putting const means this function can be used with const objects,
        //      If const does not exist: we cannot pass const object as 'this' as an implicit argumnet.
        //      It must be passed as a const object ('const this'). 
    }

    void showdist() const
    {
        cout << feet << "\' " << inches << "\"" << endl;
    }

    void add_dist(Distance, Distance);         // declaration
    Distance add_dist(const Distance &) const; // declaration
};

void Distance::add_dist(Distance d1, Distance d2)
{
    feet = d1.feet + d2.feet;
    inches = d1.inches + d2.inches;
    if (inches >= 12.0)
    {
        inches -= 12.0;
        feet++;
    }
}

Distance Distance::add_dist(const Distance &d2) const
{
    Distance temp;
    temp.feet = feet + d2.feet;
    temp.inches = inches + d2.inches;
    if (temp.inches >= 12.0)
    {
        temp.inches -= 12.0;
        temp.feet++;
    }

    return temp;
}
/*
    This function has:
        >> Direct access    (Using the member names alone):
            → to all the members, whether private or public, of that object.
        >> Indirect access  (using the object name and the member name):
            → to other objects of the same class that are passed as arguments.
*/


/* CONST MEMBER FUNCTION */
/*
    Member functions that do nothing but acquire data from an object are obvious candidates
        for being made const, because they don’t need to modify any data

    Making a function const:
        >> helps the compiler flag errors.
        >> tells anyone looking at the listing that you intended the function not to modify
             anything in its object.
        >> makes possible the creation and use of const objects.

    ///////////////////////

    • If we want to declare an Ordinary function that cannot modify its arguments, we would say:
        →   int fun(const int a, const int b);

    • But class data members are all implicit arguments to member functions ('this' is an implicit argument),
            so when we want to declare a member function that cannot modify it's parent object fields we would say:
        →   int fun() const;    // means this functions has (const this) as an argument.

    ///////////////////////

    Note:
        >> If there is a separate function declaration, const must be used in both
            declaration and definition.
*/


/* STRUCTURES and CLASSES */
/*
    • The only formal difference between class and struct is that:-
        >> in a class: the members are private by default, while
        >> in a structure: they are public by default

    • In most situations programmers don’t use a struct this way.
        >> They use structures: to group only data,
        >> and classes: to group both data and functions.
*/

class foo
{
    int data1; // private by default

    // But, We like to include the private keyword because
    //  >> it offers an increase in clarity.
public:
    void func();
};

struct fooo
{
    void func(); // public by default

private:
    int data1;
};

/* STATIC CLASS DATA */
/*
    • If a data item in a class is declared as static,
         only one such item is created for the entire class.

    • It's useful when all objects of the same class must share
        a common item of informatio.
        .. while a normal static variable is used to retain information
            between calls to a function,
        .. static class member data is used to share information
            among the objects of a class.
        ex:. suppose an object needed to know how many other objects
            of its class were in the program.

    • It has characteristics similar to a normal static variable:
        >>  It is visible only within the class.
        >>  Its lifetime is the entire program.
        >>  It continues to exist even if there are no objects of the class
*/

class car
{
private:
    static int count; // one data item for all objects
                      // Note: *declaration only*

public:
    car()
    {
        count++;
    } // increments count when object created
    int getcount()
    {
        return count;
    }
};
int car::count = 0; // *definition* of count

// Static Class Data Separate Declaration and Definition:
/*
    Ordinary variables:
        • declared (the compiler is told about their name and type) and
        • defined (the compiler sets aside memory to hold the variable).
    Static member data:
        • The variable’s declaration appears in the class definition, but
        • the variable is actually defined outside the class.


    // Why is this two-part approach used?

        • If static member data were defined inside the class...
            >> it would violate the idea that a class definition is only a
                blueprint and does not set aside any memory.

        • Putting the definition of static member data outside the class also
            >> Serves to emphasize that the memory space for such data is allocated
                only once, before the program starts to execute.
            >> And that one static member variable is accessed by an entire class;

        • WARNING !!
            If you include the declaration of a static variable but forget its definition:
                >> there will be no warning from the compiler.
                    (Everything looks fine until you get to the linker, which will tell you that
                    you’re trying to reference an undeclared global variable).
*/

int main(void)
{
    smallobj s1, s2;

    s1.setData(50);
    s2.setData(80);

    s1.showData();
    s2.showData();

    ///////////

    counter c1(25), c2(30);

    cout << "c1 = " << c1.get_count() << endl;
    cout << "c2 = " << c2.get_count() << endl;

    c1.inc_count();
    c2.inc_count();
    c2.inc_count();

    cout << "c1 = " << c1.get_count() << endl;
    cout << "c2 = " << c2.get_count() << endl;

    ///////////

    Distance d1(11, 6.25, 0);
    Distance d2, d3;
    d2.getdist();

    d3.add_dist(d1, d2);

    cout << "\nDist1 = ";
    d1.showdist();
    cout << "Dist2 = ";
    d2.showdist();
    cout << "Dist3 = ";
    d3.showdist();
    cout << endl;

    d3 = d1.add_dist(d2);
    cout << "Dist3 = ";
    d3.showdist();
    cout << endl;

    ////////// Copy constructor

    Distance d4 = d3;
    Distance d5(d3);
    //  invoke the default copy constructor

    cout << "Dist4 = ";
    d4.showdist();
    cout << "Dist5 = ";
    d5.showdist();

    ///////////// static member data

    car car1, car2, car3;

    cout << "count is " << car1.getcount() << endl;
    cout << "count is " << car2.getcount() << endl;
    cout << "count is " << car3.getcount() << endl;

    //////////// const objects
    /*
        - These objects can use only any const member functions.
            (because they’re the only ones that guarantee not to modify it.)
        - And they cannot use any non-const function.
            (you can’t modify it.)

        * Remember, using const helps the compiler to help you.
    */

    const Distance football(300, 0, 1);

    // football.getdist(); //ERROR: getdist() not const

    cout << "Football = ";
    football.showdist();
    cout << endl;

    // const objects with mutable fields
    /*
        - But, the object encompasses a number if different data members, 
        and declaring a const object means that all its data members are const.
        • Creating an object where some of its data members are const and some are mutable 
            is not possible using only this syntax.
        • C++ provides the 'mutable' keyword to mark certain data members to still can be mutated
            when the oject containing it is const. 
    */
    const Distance mut(11, 5.2, 2);
    // mut.setfeet(5);      // error, mut is a const.
    mut.setID(3);           // this is ok.

    /*
        - This object is said to have 'logical constness'. 
        That means that in theory it can’t be modified, but in practice it can, in a limited way.
        
        - In a non-const object, of course, both attributes could be modified.
    */
    
    return 0;
}


/*
    Benefit of OOP:
        This makes it easy to conceptualize a programming problem. 
        • You figure out what parts of the problem can be most usefully represented as objects, 
        • and then put all the data and functions connected with that object into the class.
        • One advantage is that in an OO program the compiler can find many more
            conceptual errors than in a procedural program
    
    What to include in a class?:
        •  you put into this class the data items that represent the value of the object, 
        • and also the functions to set value, retrieve it, display it, compare it, and so on.
*/