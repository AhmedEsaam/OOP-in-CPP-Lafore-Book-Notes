#include <iostream>
using namespace std;


/// Virtual functions /////////////////////////////////////////////////////////////////////:
// 'Virtual' means existing in appearance but not in reality. 
// they give the ability of polymorphism, which means different forms.

// • Using the same function name with different classes objects that are descendant from a single class:
//-----------------------------------------------------------
//  1. using normal functions:
class Base
{
public:
    void show()                         // normal function
    {   cout << "Base" << endl; }
};


class Derived_1 : public Base
{
public:
    void show()
    {   cout << "Derived_1" << endl; }
};

class Derived_2 : public Base
{
public:
    void show()
    {   cout << "Derived_2" << endl; }
};


//-----------------------------------------------------------
//  2. using virtual functions:
class Base2
{
public:
    virtual void show()                 // virtual function
    {   cout << "Base" << endl; }
};


class Derv_1 : public Base2
{
public:
    void show()
    {   cout << "Derived_1" << endl; }
};

class Derv_2 : public Base2
{
public:
    void show()
    {   cout << "Derived_2" << endl; }
};


//-----------------------------------------------------------
//  3. using pure virtual functions (true abstract classes):
class Base3
{
public:
    virtual void show() = 0;            // (=0) pure virtual function - one is enough for the class to be abstract
    // The =0 syntax is simply how we tell the compiler that a virtual function will be pure
    // 'pure virtual functions' can't have definitions
    // ► this 'pure virtual function' should be overrided in all the derived classes
    //      otherwise, it'll be inherited, hence this derived class will be forced abstract as well 
    //      (which you can in turn make derived classes of and then override the pure virt. func.)

    void func()                         // normal function which can only be invoked by a pointer to the abstract class
    {   cout << "Normal function in the abstract class." << endl; }
    // not all functions in the abstract class need to be virtual 
    //  → it can be invoked by a pointer to the class object
    //  → and it can be refered to in the derived classes body or by their objects.
    // For consistency, you may want to make all the virtual functions in the base class pure.
};


class Deriv_1 : public Base3
{
public:
    void show()
    {   cout << "Derived_1" << endl; }
};

class Deriv_2 : public Base3
{
public:
    void show()
    {   cout << "Derived_2" << endl; }
};



/// Example: Person class ...............................................................................:
class Person                                // abstract class
{
private:
    char name[40];
public:
    void getName()
    {   cout << "Enter name: "; cin >> name; }
    void putName()
    {   cout << name; }
    virtual void getData() = 0;             // pure virtual function
    virtual bool isOutstanding() = 0;       // pure virtual function
};


class Student : public Person
{
private:
    float gpa;
public:
    void getData()
    {
        Person::getName();
        cout << "Enter stdent's GPA: "; cin >> gpa;
    }
    bool isOutstanding()
    {   return (gpa > 3.5); }
};

class Professor : public Person
{
private:
    int numPubs;
public:
    void getData()
    {
        Person::getName();
        cout << "Enter number of professor's publications: "; cin >> numPubs;
    }
    bool isOutstanding()
    {   return (numPubs > 100); }
};


/// Base class destructors should always be virtual ....................................................:
/*
    Destructors in derived classes may have extra work to do like deleting memory obtained with new.
    So, to ensure that derived-class objects are destroyed properly, 
    ► you should make destructors in all base classes virtual.
*/
class Parent
{
public:
    virtual void createInts()
    {   }

    // ~Parent()
    virtual ~Parent()
    {   cout << "Parent destoyed\n"; }
};


class Child : public Parent
{
private:
    int* pInt[100];
    int size;
public:
    Child(int n) : size(n)
    {   }
    void createInts()
    {   
        for (int i = 0; i < size; i++)
        {   pInt[i] = new int; }
    }
    ~Child()
    {   
        for (int i = 0; i < size; i++)
        {   delete pInt[i]; }
        cout << "Child destoyed\n";
        // Now both parts of the derived class object are destroyed properly.
    }
};



/// Virtual Base Classes //////////////////////////////////////////////////////////////////:

// Ambiguous diamond class tree
class SuperParent
{
protected:
    int baseData = 5;
};

class Child1 : public SuperParent
{   };

class Child2 : public SuperParent
{   };
 
class GrandChild : public Child1, public Child2
{   
public:
    int getData()
    {   
        // return baseData;         // Ambiguous: which of the two 'baseData' will be called?
        return 0;
    }
};

/*
    When the 'Child1' and 'Child2' classes are derived from 'SuperParent', 
        each inherits a copy of 'SuperParent'; this copy is called a subobject.
    Each of the two subobjects contains its own copy of Parent’s data, including 'baseData'.
    ► when Grandchild refers to basedata, which of the two copies will it access? 
*/


// To remove ambiguity, we make 'Child1' and 'Child2' into virtual base classes:
class Child_1 : virtual public SuperParent      // shares a copy of SuperParent with all virtual base classes
{   };  // what if this changed a private data member in SuperParent, will the other child take the change??

class Child_2 : public virtual SuperParent      // shares a copy of SuperParent with all virtual base classes
{   };
 
class Grand_Child : public Child_1, public Child_2
{   
public:
    int getData()
    {   
        return baseData;         // Ok, only one copy of SuperParent
    }
};

/*
    The use of the keyword 'virtual' in these two classes causes them to share a single common subobject 
        of their base class 'SuperParent' (only one copy of 'SuperParent' data/function members will be copied to / shared by 
        all the base classes that use 'virtual' base.) 
        - The 'SuperParent' is virtually inherited in class 'Child_1' and class 'Child_2'.
    ► Since there is only one copy of basedata, there is no ambiguity when it is referred to in Grandchild.

    • Virtual base classes offer a way to save space and avoid ambiguities in class hierarchies that use multiple inheritances. 
    • The need for virtual base classes may indicate a conceptual problem with your use of multiple inheritance, 
        so they should be used with caution.
*/



/// Friend functions //////////////////////////////////////////////////////////////////////:
/*
    Although the concepts of encapsulation and data hiding dictate that 
    nonmember functions should not be able to access an object’s private or protected data.
        - However, there are situations where such rigid discrimination leads to considerable inconvenience. 
*/
// A 'friend function' is a non-member function that has access to all class members.

/*  Friend functions use cases:
    1•  A frined function acts as a 'bridge' between more than one class private members.
    2•      → As a result to that, friend functions can be used to increase the versatility of overloaded operators.
    3•  A friend function allows a more 'obvious syntax' for calling a function than does a member function:
            → func(obj)  instead of  obj.func()
*/

/// 1• Friend functions as a bridge: ........................................................
class Beta;     // for forward referencing

class Alpha
{
private:
    int data;
public:
    Alpha() : data(3) { }
    friend int friFunc(Alpha, Beta);        // place the friend function declaration (gives it access to all members imcluding 'private' ones)
};

class Beta
{
private:
    int data;
public:
    Beta() : data(7) { }
    friend int friFunc(Alpha, Beta);        // place the friend function declaration
};
/*
    The declaration can be placed anywhere in the class; 
        it doesn’t matter whether it goes in the public or the private section
*/

int friFunc(Alpha a, Beta b)                // function definition which is a friend to two functions
{
    return (a.data + b.data);
}


// Example: Distance class
#define OVERLOADED_PLUS_OPERATOR_IS_FRIEND  1

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
    

#if ! OVERLOADED_PLUS_OPERATOR_IS_FRIEND
    // Normal overloaded +operator (only invoked when the left-side arg is a 'Distance'):
    Distance operator +(Distance) const;                // member function overloaded +operator takes 1 argument
#else
    // Overloaded +operator as a friend function 
    // (can be invoked when the left-side is 'Distance' or 'float' where it can be converted implicitly using the one-arg constructor)
    friend Distance operator +(Distance, Distance);     // friend overloaded +operator takes 2 argumnets
                                                        // → In general, the friend version of a function requires one more argument
                                                        //      than when the function is a member.
#endif

    float square();                     // called as dist.square()
    // for a more 'obvious syntax' for calling 'square' than does the member function:
    friend float square(Distance);      // called as sqaure(dist)
};



/// 2• Friend func. to increase versatility of overloaded operators: ........................
#if ! OVERLOADED_PLUS_OPERATOR_IS_FRIEND
Distance Distance::operator +(Distance d2) const        
{
    // This member function of the 'Distance' class 
    //  only operates on a 'Distance' object on its left side.
    int f = feet + d2.feet;
    float i = inches + d2.inches;
    if(i >= 12.0)
    {   i -= 12.0; f++; }
    return Distance(f, i);
}

#else
// Overloaded +operator definition:
Distance operator +(Distance d1, Distance d2)        
{
    // When a 'double' is on the right-side of the + operator, 
    //  it can be converted into 'Distance' using the one-arg constructor in the 'Distance' class. 
    int f = d1.feet + d2.feet;
    float i = d1.inches + d2.inches;
    if(i >= 12.0)
    {   i -= 12.0; f++; }
    return Distance(f, i);
}
#endif


/// 3• Friend func. as a more 'obvious syntax' for calling a function than does a member function:
// Normal member function:
float Distance::square()
{
    float fltFeet = feet + inches/12;
    float feetSqrd = fltFeet * fltFeet;
    return feetSqrd;
}
// friend version of it
float square(Distance d)
{
    float fltFeet = d.feet + d.inches/12;
    float feetSqrd = fltFeet * fltFeet;
    return feetSqrd;
}



/* Note:
    While 'friend function' feature adds flexibility to the language, 
    ► It is not in keeping with' data hiding'. 
        The philosophy that only member functions can access a class's private data.

    ► Numerous friends muddy the clear boundaries between classes.
        So, friend functions are conceptually messy, and potentially lead to a spaghetti-code. 

    ■ However, as the friend function must be declared as such within the class whose data it will access,
        → Thus a programmer who does not have access to the source code for the class 
            cannot make a function into a friend.
            - In this respect, the integrity of the class is still protected.

    It remains that friend functions should be used sparingly. 
        - If you find yourself using many friends, you may need to rethink the design of the program.
*/



/// Friend classes //////////////////////////////////////////////////////////////////////:
/*
    The member functions of a class can all be made friends to your class at the same time 
    → when you make the entire class a friend.
*/
class Delta;        // for forward referencing, to write: friend Delta 

class Gamma     
{
private:
    int data;
public:
    Gamma() : data(99) { }
    friend Delta;
    // Or:
    friend class Delta;     // if you did not write 'class Delta;' declaration before class 'Gamma' for forward referencing.
};

class Delta
{
public:
    void func1(Gamma g) { cout << "\nGamma data = " << g.data; }
    void func2(Gamma g) { cout << "\nGamma data = " << g.data; }
};



/// Static functions ////////////////////////////////////////////////////////////////////:
/*
    Static data members exist only once and relates to the entire class.
    → To make an interface for them to read/write it's not convenient to refer to a specific object
        when we’re doing something that relates to the entire class.
    • So, for a function that only deals with static members, we must declare them to be 'static member function'.
        Which we can invoke using the scope resolution operator with the class name directly, ex: Class::fun().
*/
class Epsilon
{
private:
    static int total;
    int id;
public:
    Epsilon()
    {
        total++;
        id = total;         // providing an ID number for each of its objects
        /*
            This allows you to query an object to find out which object it is
            — a capability that is sometimes useful in debugging a program, among other situations.
        */
    }
    ~Epsilon()
    {
        total--;
        cout << "\nDestroying Object #" << id;       
    }
    static void showTotal()
    {
        cout << "\nTotal number of objects is " << total;
    }
    void showID()
    {
        cout << "\nObject ID is " << id;
    }
};

int Epsilon::total = 0;     // definition of the static data member



/// Assignment operator and Copy constructor  ///////////////////////////////////////////:
 
/* 
    ■ Assignment operator =
        a2 = a1;    will cause the compiler to copy the data from a1, member by member, into a2. 
        → This is the default action of the assignment operator, =.

    ■ Copy contructor
        alpha a2(a1);   initializes a2 to the value of a1.
        This is the default action of the copy constructor.

    ► You can override these default functions, if you want assignment or initialization to do something more complex.
*/


/* ♠ Initialization & Assignment ♠ ...................................................
    ------------------------------------
    ■ Assignment:
        ► invoke the Assignment operator '=':
            - obj2 = obj1;                  // invoke the assignment operator '='
            - obj = {data, ...};            // implicitly call the multi-arg constructor, then invoke the assignment operator '='
            - obj = data                    // same as above -if the data members are one, or there is a one-arg constructor used for type conversion
    ------------------------------------
    ■ Initialization:
        ► invoke the no or one-or-more arg. constructors:
            - Type obj;                     // invoke no-arg constructor
            - Type obj(data, ...)           // invoke one-or-more arg constructor
    
        ► invoke the Copy Constructor:
            - Type obj = {data, ...};       // copy-list initialization
            - Type obj2 = obj1;             // copy object
            - Type obj2(obj1);              // copy object
*/



/// ■ Overloading the Assignment Operator =

#define CHAIN_EQUAL_OP  2       // 0: no chain, 
                                // 1: takes arg. by 'value'     and return by 'value'
                                // 2: takes arg. by 'reference' and return by 'reference' 

class Zeta
{
private:
    static int total;
    int id;
    int data;
public:
    Zeta() { total++; id = total; }
    Zeta(int d) : data(d) { total++; id = total; }
    void display() { cout << "#" << id << ": " << data << ", total = " << total; }

// verloading the = operator:
#if ! CHAIN_EQUAL_OP 
    void operator = (Zeta& z)       // • passing by reference conserves memory
    {
        data = z.data;
        cout << "\nAssignment operator invoked";
    }

#elif CHAIN_EQUAL_OP == 1
    // To make a chain of = operators, the function must return what it takes as an argument.
    // → for example: z3 = z2 = z1;  here, (z2 = z1) returns a Zeta obj. which will be an arg. to the (z3 = ) function.
    Zeta operator = (Zeta z)
    {
        data = z.data;
        cout << "\nAssignment operator invoked";
        return Zeta(data);              // this is an r-value
        // • Returning a value is what makes it possible to chain = operators.
        // Also returning by value generates new objects with new ID
        // → you may wind up with more objects than you expected.  
    }

    /* ► Why not make the function declarator as:   Zeta operator = (Zeta& z)       ?
        As this function returns an r-value: Zeta(data), 
        → it's not possible to bind non-const l-value (Zeta&) to an r-value f type 'Zeta'.
        In other words, you cannot reference an r-value. Only l-values can be referenced. 
    */

    /* ► Why not make the function declarator as:   Zeta& operator = (Zeta z)       ?
        In the same sense, the function returns an r-vlaue,
        which the return type l-value (Zeta&) cannot be binded to.
    */   

#else
    /* ► Can we make the function declarator as:    Zeta& operator = (Zeta& z)      ? 
        getting the best of both worlds:
        • passing by reference, hence conserving memory,
        • and returning by reference, hence not generating new objects which consumes memory and causes confusion like messing with static values like 'total'.
        
        This is possible only if the function returns an l-value.
        → But if you declare a new local 'Zeta' obj, initialize it and then return it, like:
            {   
                data = z.data;
                Zeta obj(data);
                return obj;     // an l-value but is destroyed after function terminates
            }
        → This is not correct either as we can’t use reference returns on variables that are local to a function.
            Because, the local vars (that are not designated 'static') will be destryoed when the function returns, 
            and the reference returns it's address which will become meaningless after the var is destroyed.
         
        The only possible solution is to return a pointer to 'this' object, like the following implementation: 
    */
    Zeta& operator = (const Zeta& z)
    {
        data = z.data;
        cout << "\nAssignment operator invoked";
        return *this;  
    }

#endif


    /* Note: IMPORTANT
        The assignment operator '=' is unique among operators in that 
        ► It is not inherited. 
        If you overload the assignment operator in a base class, you can’t use this same function in any derived classes. 
    */


    /* CAUTION:
        When you overload the = operator you assume responsibility for doing whatever the default assignment operator did. 
        Often this involves copying data members from one object to another.
    */
};

int Zeta::total = 0;



/// ■ The Copy Contructor

// The default copy constructor, which is provided automatically by the compiler for every object, performs a member-by-member copy.






///////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    /// Virtual functions /////////////////////////////////////////////////////////////////////:

    // accessing objects of different classes using the same statement:
    //  1. using normal functions:
    Derived_1 dv1;
    Derived_2 dv2;
    Base* ptrBase;

    ptrBase = &dv1;         // This is OK, as 'dv1' is of type (Derived_1) which is derived from type (Base)
    ptrBase->show();        // → The rule is that pointers to objects of a derived class
                            //  are typecompatible with pointers to objects of the base class.
    ptrBase = &dv2;
    ptrBase->show();

    cout << endl;
   
    /* What function is called? Is it Base::show() or Derived_1::show()? 
        The function in the 'Base' class is always executed.
        ► The compiler ignores the contents of the pointer 
            and chooses the member function that matches the type of the pointer.
    */

    //  2. using virtual functions:
    Derv_1 drv1;
    Derv_2 drv2;
    Base2* ptrBase2;

    ptrBase2 = &drv1;
    ptrBase2->show();       // At runtime, when it is known what class is pointed to by the pointer,
                            //  the appropriate version of show() will be called
    ptrBase2 = &drv2;
    ptrBase2->show();

    cout << endl;

    /* Now, the member functions of the derived classes, not the base class, are executed. 
        The compiler executes different functions, depending on the contents of the pointer.
        ► It selects the function based on the contents of the pointer at run-time, not on the type of the pointer.
            (This is called 'late binding' or 'dynamic binding'.)
            (Choosing functions in the normal way, during compilation, 
                is called 'early binding' or 'static binding'.)
        ►  Late binding requires some overhead but provides increased power and flexibility.

        • We don't need to create an object of the 'Base3' class, but it is allowed.
        
        • *Although, that Base pointer cannot refer to any data field in the derived class.
            - As the compiler depends on the type of the pointer 
            to determine the size it can move when incrementing the pointer for example.
            But, the class functions are only stored once.
    */

    //  3. using pure virtual functions (true abstract classes):
    Deriv_1 driv1;
    Deriv_2 driv2;
    // Base3 base3Obj;          // Error - instantiating an object of an abstract class
    Base3* ptrBase3[2];         // just another style - pointers array insttead of one pointer.
    ptrBase3[0]->func();        // normal function in the abstract class

    ptrBase3[0] = &driv1;
    ptrBase3[0]->show();
    driv1.func();               // normal function in the abstract class can be invoked by the derived class object.
    
    ptrBase3[1] = &driv2;
    ptrBase3[1]->show();

    cout << endl;

    /* The compiler executes different functions, depending on the contents of the pointer.
        • 'Base3' class is an abstract class with atleast one pure virtual function, hence we CANNOT create an object of it,
            only a pointer to it. However, we can put functions with definitions in its body where the pointer can refer to them.
    */

    /// Example: Person class: ----------------------------------------------
    Person* ptrPer[100];        // array of pointers to Persons
    int n = 0;                  // number of Persons on list
    char choice;

    int i;
    do
    {
        cout << "\nEnter student or professor (s/p): ";
        cin >> choice;
        if(choice == 's')
        {   ptrPer[n] = new Student; }      // allocate new Stuent
        else
        {   ptrPer[n] = new Professor; }    // allocate new Professor

        ptrPer[n++]->getData();

        cout << "Enter another? (y/n): "; cin >> choice;
    } while (choice == 'y');
    
    for ( i = 0; i < n; i++)
    {
        ptrPer[i]->putName();
        if(ptrPer[i]->isOutstanding())
        {   cout << "\t\t(This person is outstanding)"; }
        cout << endl;
    }
    
    
    /// Base class destructors: ---------------------------------------------
    Parent* ptrPar = new Child(3);
    ptrPar->createInts();
    delete ptrPar;


    /// Virtual base classes //////////////////////////////////////////////////////////////////:
    Grand_Child gc;
    cout << gc.getData() << endl;
    

    /// Friend functions //////////////////////////////////////////////////////////////////////:
    Alpha aa;
    Beta bb;
    cout << friFunc(aa, bb) << endl;

    /// Distance class overloaded +operator:
    Distance d1 = 2.5;          // implicit conversion from 'float feets' using a one-argument constructor in the destination
    Distance d2 = 1.25;
    Distance d3;
    cout << "\nd1 = "; d1.show_dist();
    cout << "\nd2 = "; d2.show_dist();
    
    d3 = d1 + 10.0;             // Distance + float : OK (either overloaded functions works fine)
    cout << "\nd3 = "; d3.show_dist();

    #if ! OVERLOADED_PLUS_OPERATOR_IS_FRIEND
    // d3 = 10.0 + d1;          // float + Distance : Error
    /*
        The overloaded '+ operator' function operates according to the type on its left side of which it is a member of.
            - In this situation the compiler will look for the overloaded '+ operator' of the 'double' data type,
                which the user-efined type 'Distance' doesn't match any of this operator's possible right-side arguments.
    */
    #else
    d3 = 10.0 + d1;
    cout << "\nd3 = "; d3.show_dist();
    #endif

    /// A friend function as a more obvious syntax for calling a function than does a member function.
    Distance dist(3, 6.0);
    float sqft;
    cout << "\nDistance = "; dist.show_dist();
    
    sqft = dist.square();
    cout << "\nSqaured = " << sqft << " square feet";

    // If we want to work with Distance objects 
    //  using the same syntax that we use with ordinary numbers:
    sqft = square(dist);      
    cout << "\nSqaured = " << sqft << " square feet";
    

    /// Friend classes //////////////////////////////////////////////////////////////////////:
    Gamma g;
    Delta d;

    d.func1(g);
    d.func2(g);
    cout << endl;


    /// Static functions ////////////////////////////////////////////////////////////////////:
    Epsilon e1;
    Epsilon::showTotal();

    Epsilon e2, e3;
    Epsilon::showTotal();

    Epsilon* pEp = new Epsilon;
    Epsilon::showTotal();

    delete pEp;
    Epsilon::showTotal();

    e1.showID();
    e2.showID();
    e3.showID();
    cout << "\n-------------- end of program ------------\n";
    /*
        The last object created, g3, is destroyed first. 
        → One can infer from this last-in-first-out approach that local objects are stored on the stack.
    */


    /// Assignment operator and copy constructor ////////////////////////////////////////////:
    // ------------------------------------------------
    // ■ Assignment operator =

    Zeta z1(37);
    Zeta z2, z3, z4;
    
    z2 = z1;
    cout << "\nz2 = "; z2.display();

    #if CHAIN_EQUAL_OP
        z4 = z3 = z1;           // operates from right-to-left
        cout << "\nz3 = "; z3.display();
        cout << "\nz4 = "; z4.display();
    #endif

    cout << endl;


    // ------------------------------------------------
    // ■ Copy constructor

    // Note:    instantiating an object only invokes one cnstructor.
    //  So, these syntaxes do not invoke the 'no-arg constructor' or the 'one-arg constructor', only the copy constructor.

    Zeta z5 = z4;       // Copy initialization is not assignment (=operator function is not invoked)
    cout << "\nz5 = "; z5.display();

    Zeta z6(z4);        // has the same effect (alternative form of copy initialization)
    cout << "\nz6 = "; z6.display();

    cout << endl;


        
    return 0;
}
