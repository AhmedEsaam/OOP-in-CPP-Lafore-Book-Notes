#include <iostream>
#include <cstring>
#include <typeinfo>
using namespace std;

/// Polymorphism ///

/// Virtual functions /////////////////////////////////////////////////////////////////////:
// 'Virtual' means existing in appearance but not in reality. 
// they give the ability of polymorphism, which means different forms.

// • Using the same function name with different classes' objects that are descendant from a single class:
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


//-----------------------------------------------------------
/* Virtual functions:
    • Provide a way for a program to decide while it is running what function to call. 
        → Ordinarily such decisions are made at compile time. 
    • Make possible greater flexibility in performing the same kind of action on different kinds of objects. 
        → In particular, they allow the use of functions called from an array of type pointer-to-base that actually
            holds pointers (or references) to a variety of derived types.
        → They also allow for making generic functions that takes a number of pointers to the base class
            then you can pass child classes addresses in any order.
            
    ► This is an example of polymorphism. 
    • Plese maintain accessibility between Base Class and Child Class:
        Use same accessibility in the base class or increase it.
        - Example:  public in Base      → public in Child
                    protected in Base   → public or protected in Child
                    private in Base     → it's not seen anyway in Child, so it'll be a new function any way (not overriden)

*/

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
    virtual void getData() = 0;             // pure virtual function (1. make the class abstract. 2. this function cannot have body)
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

class Child_2 : public virtual SuperParent      // same: shares a copy of SuperParent with all virtual base classes
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
// Because there is exceptions to every rule, and because C++ always give you tools to shoot yourself in the foot!
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
class Beta;     // for forward referencing / forward declaration

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


/// 2• Friend func. to increase versatility of overloaded operators: ............................
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
    ► It is not in keeping with 'data hiding'. 
        The philosophy that only member functions can access a class's private data.

    ► Numerous friends muddy the clear boundaries between classes.
        So, friend functions are conceptually messy, and potentially lead to a spaghetti-code. 

    ■ However, as the friend function must be declared as such within the class which data it will access,
        → Thus a programmer who does not have access to the source code for the class 
            cannot make a function into a friend.
            - In this respect, the integrity of the class is still protected.

    It remains that friend functions should be used sparingly. 
        - If you find yourself using many friends, you may need to rethink the design of your program.

    ♦ CAUTION: if your class destructor deletes dynamic allocated memory, you should pass the class object to the friend function
                by reference; as passing it by value will make a new object which refers to the same allocated memory which 
                in turn will be deleted by the destructor as soon as the friend function terminates.
*/



/// Friend classes //////////////////////////////////////////////////////////////////////:
/*
    The member functions of a class can all be made friends to your class at the same time 
    → when you make the entire class a friend.
*/
class Delta;        // for forward referencing: for the two classes to be able to refer to each other 

class Gamma     
{
private:
    int data;
public:
    Gamma() : data(99) { }
    friend Delta;
    // Or:
    friend class Delta;     // handy if you did not write 'class Delta;' declaration before class 'Gamma' for forward referencing.
};

class Delta
{
public:
    void func1(Gamma g) { cout << "\nGamma data = " << g.data; }    // used 'g.data' although 'data' is a private member inside Gamma
    void func2(Gamma g) { cout << "\nGamma data = " << g.data; }
};



/// Static functions ////////////////////////////////////////////////////////////////////:
/*
    Static data members exist only once and relates to the entire class.
    → To make an interface for them to read/write it's not convenient to refer to a specific object
        when we’re doing something that relates to the entire class.
    • So, for a function that only deals with static members, we must declare them to be 'static member function'.
        Which we can invoke using the scope resolution operator (::) with the class name directly, ex: Class::fun().
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
    static void showTotal()     // it's not allowed to put 'const' in a static function declaration
    {
        cout << "\nTotal number of objects is " << total;
    }
    void showID()
    {
        cout << "\nObject ID is " << id;
    }
};

int Epsilon::total = 0;     // definition of the static data member


/* Note ► The 'this' pointer is not available in 'static' member functions, 
        since they are not associated with a particular object. 
*/


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


/* ♠ Initialization & Assignment ♠
    ------------------------------------
    ■ Assignment:       (used in the code listings after objects are already defined)
        ► invoke the Assignment operator '=':
            - obj2 = obj1;                  // invokes the assignment operator '='
            - obj = {data, ...};            // implicitly call the multi-arg constructor, then invoke the assignment operator '='
            - obj = data                    // same as above -if the data members are one, or there is a one-arg constructor used for type conversion
    ------------------------------------
    ■ Initialization:   (used when declaring a new object)
        ► invoke the 'no' or 'one-or-more' arg. constructors:
            - Type obj;                     // invoke no-arg constructor
            - Type obj(data, ...)           // invoke one-or-more arg constructor
    
        ► invoke the Copy Constructor:
            - Type obj = {data, ...};       // copy-list initialization
            - Type obj2 = obj1;             // copy object
            - Type obj2(obj1);              // copy object
    ------------------------------------
    ■ Temporary objects:
        ► invoke the Copy Constructor:
            - void func(Type obj);          // passing by value
            - Type func();                  // returning by value
        // the compiler uses the copy constructor to make a copy -temporary- object that is destroyed when the scope terminates. 
        //  → Remember: Always pass by reference the objects that has destructors, to avoid damaging the original object.
            

    * Without overloading these functions, the compiler just do a bit-wise copying which is not invoking any constructors (so, not recommended)
*/


// So, let's implement that:
#define CHAIN_EQUAL_OP  2       // 0: no chain, 
                                // 1: takes arg. by 'value'     and returns by 'value'
                                // 2: takes arg. by 'reference' and returns by 'reference' 

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
    ~Zeta() { total--; }




/// ■ Overloading the Assignment Operator =

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

    /* ► Why not make the function declarator as:       Zeta operator = (Zeta& z)       ?
        As this function returns an r-value: Zeta(data), which in the chain eventually becomes the new argument
        → it's not possible to bind non-const l-value (Zeta&) to an r-value of type 'Zeta'.
        In other words, you cannot reference an r-value. Only l-values can be referenced. 
    */

    /* ► Why not then make the function declarator as:  Zeta& operator = (Zeta z)       ?
        In the same sense, the function takes an r-vlaue,
        which the return type l-value (Zeta&) cannot be binded to.
    */   

#else
    /* ► Can we make the function declarator as:        Zeta& operator = (Zeta& z)      ? 
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
        → This is not correct neither, as we can’t use reference returns on variables that are local to a function.
            Because, the local vars (that are not designated 'static') will be destryoed when the function returns, 
            and the reference returns it's address which will become meaningless after the var is destroyed.
         
        The only possible solution is to return a pointer to 'this' object, like the following implementation:
        // You usually want to return by reference from overloaded assignment operators, using *this, to avoid the creation of extra objects. 
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
        When you overload the = operator you assume responsibility for doing whatever the default assignment operator does. 
        Often this involves copying data members from one object to another.
    */
   
   

/// ■ The Copy Contructor:

    // The default copy constructor, which is provided automatically by the compiler for every object, performs a member-by-member copy.
    // → This is similar to what the assignment operator does; the difference is that (the copy constructor also creates a new object.)

    // Overloading the copy constructor:
    Zeta(const Zeta& z)             // this is pronounced "Zeta of Zeta ref."   
    {
        data = z.data;
        total++;    id = total;     // give an id to the new object
        cout << "\nCopy constructor invoked"; 
    }

    /* Note: IMPORTANT
        We CANNOT pass the argument by value as:    Zeta(Zeta z)
        → Bacause when an argument is passed by value, a copy of it is constructed,
        → at which the copy constructor is invoked, (which is overrided by this very function).
        → So, it calls itself as its argument is still passed by value,
        → hence, it calls itself over and over until the compiler runs out of memory.

        ► So, in the copy constructor, the argument must be passed by reference, which creates no copies.
    */
};

int Zeta::total = 0;


/* When to overload the assignmnet operator and Copy constructor?

    • When you overload the assignment operator, you almost always want to overload the copy constructor as well (and vice versa).
        ► You don't want your custom scheme used in some situations and the default other scheme used in others.
        ► Even if you don’t think you’ll use one or the other, you may find the compiler using them in nonobvious situations,
            (such as passing an argument to a function by value, and returning from a function by value.)

    • if the constructor to a class involves the use of system resources such as memory (creating dynamically allocated memory) or disk files,
        and: - you pass the object as a parameter by value to a function (so you fear a bit-wise copying and destructing shared memory)
             - you construct new object from an old one (and you'd fear the same things)
             - your class object is returned by value from a function 
        ► In this case, you should almost always overload both the assignment operator and the copy constructor, and make sure they do what you want.
*/


/* How to Prohibit Copying?
    • You may want to prohibit the copying of an object using these operations.
        - For example, it might be essential for each object of a class to be created using only 'no' or 'one-or-more' argument constructors 
            with a unique value for some members such as arguments or static values of the class, 
        → If an object is copied -using the '=' op. or the copy contructor-, the copy will be given the same values. 

    ◘ To prohibit invoking those two schemes in non-member functions like main():
        ► Just overload the assignment operator and the copy constructor as private members.
        ► You don’t need to define the functions, since they will never be called.
*/
class Eta
{
private:
    Eta& operator = (Eta&);         // private assignment operator
    Eta(Eta&);                      // private copy constructor

public:
    Eta(){}                  
};



/// A Memory-Efficient String Class /////////////////////////////////////////////////////:
/*
    The problem with classes that only holds a pointer to the allocated memory, by which we conserve memory,
    so that when copying an object to another, only the pointer is copied and there'll still be only one allocated memory,
    is that when deleting one object, all other objects points to this memory become dangling.

    ► Solution:
        is to store a count of the pointers pointing to that allocated memory, so that not destroying it until destroying
        the last object that points to it.

        → And that is by expanding the principle type which is char pointer to also store the number of pointers points to it,
        by making a new type holds the two (the char pointer and the count) of which the 'String' class is a friend.
*/
class StrWithCount
{
private:
    int count;
    char* str;
    friend class String;                // now class 'String' has access to all class 'StrWithCount' members

    StrWithCount(char* s)               // one-arg constructor
    {
        int length = strlen(s);         // acquire string length
        str = new char[length + 1];     // allocate memory for the new string
        strcpy(str, s);                 // copy actual string provided as argument to that memory
        count = 1;                      // instantiate count at 1
    }

    ~StrWithCount()
    {   delete[] str; }                 // deallocate the string memory
};


class String
{
private:
    StrWithCount* pSWC;
public:
    String()                            // no-arg constructor
    {   pSWC = new StrWithCount((char*)"NULL"); }
    String(char* s)                     // one-arg constructor
    {   pSWC = new StrWithCount(s); }
    String(const String& S)             // Copy constructor
    {   
        pSWC = S.pSWC;                  // Both the new object and the argument points to the same allocated memory
        (pSWC->count)++;                // increment the count of pointers to that memory
    }
    ~String()
    {
        if(pSWC->count == 1)
            delete pSWC;                // (We don’t need brackets on delete because we’re deleting only a single strCount object.) 
        else
            (pSWC->count)--;
    }
    void display()
    { 
        cout << pSWC->str;
        cout << " (address = " << pSWC << ")";
    }
    String& operator = (const String& S)
    {
        // if(this == &S)                  // handles the situation where S = S; otherwise, (if this object is the only that points to the 'StrWithCount') then, the 'StrWithCount' will be deleted and the program may crash.
        //     return *this; 
        
        // OR:
        if(this != &S)
        {
            if(pSWC->count == 1)        // if this object is the last that points to a string
                delete pSWC;            // delete it (deallocate memory of 'StrWithCount')
            else
                (pSWC->count)--;
            
            pSWC = S.pSWC;              // assign the argument to this object
            (pSWC->count)++;            // increment the counter of the argument 'StrWithCount'
        }

        return *this;
    }
};

// ♦ The UML object diagram shows the relationship of a group of objects at a specific point in a program’s operation.


/// The 'this' pointer //////////////////////////////////////////////////////////////////:
class Theta
{
private:
    char charArr[10];
    int alpha;
public:
    void reveal()                       // see where this object is
    {   cout << "\nMy object's address is " << this; }
    // The member functions of every object have access to 'this' pointer, which points to the object itself.
    // When you call a member function, it comes into existence with the value of 'this' set to the address of the object for which it was called.
    void tester()
    {
        this->alpha = 11;
        cout << this->alpha;            // obviously there is no reason for this, you can put 'alpha' directly
    }

    // static Theta func() { return *this; }    // Error: 'this' may only be used in a non-static member function.
    /* ► We should note that the 'this' pointer is not available in 'static' member functions, 
        since they are not associated with a particular object. */
};



/// Dynamic Type Information ////////////////////////////////////////////////////////////:
// Check for the Type info:
class Base_Polymorphic
{
    virtual void vertFunc() {}              // needed for dynamic_cast
};

class Derv1_ : public Base_Polymorphic
{   };

class Derv2_ : public Base_Polymorphic
{   };

bool isDerv1_(Base_Polymorphic *pUnknown)   // unknown subclass of Base_Polymorphic
{
    return (dynamic_cast<Derv1_*>(pUnknown));
    // 'dynamic_cast' does type checking, it returns the Derv1_* pointer if the 'pUnknown' can be casted to Derv1_*
    // otherwise, it returns NULL 
}


// 'dynamic_cast' allows such casting only in limited ways: 
// Upcast and Downcast:
class Base__
{
protected:
    int ba;
public:
    Base__() : ba(0) {}
    Base__(int b) : ba(b) {}
    virtual void vertFunc() {}              // needed for 'Downcast' dynamic_cast
    void show()
    {   cout << "Base__: ba = " << ba << endl; }
};


class Derv__ : public Base__
{
private:
    int da;
public:
    Derv__(int b, int d) : Base__(b), da(d) {}
    void show()
    {   cout << "Derv__: ba = " << ba << ", da = " << da << endl; }
};

// ♠ Review static_cast, const_cast, dynamic_cast, reinterpret_cast
// ♠ and C-Style and Function-Style Cast.
// https://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used


// The 'typeid' Operator:
void displayName(Base_Polymorphic* pB)
{
    cout << "Pointer to an object of ";
    cout << typeid(*pB).name() << endl;
    // it uses the name member of the 'type_info' class along with the 'typeid' operator. 
    // .. to display the name of the class of the object passed to it.
}

// → 'dynamic_cast' and 'typeid' work equally well with references.



///////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    /// Virtual functions ///////////////////////////////////////////////////////////////:

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
            (Choosing functions in the normal way, during compilation, is called 'early binding' or 'static binding'.)
        ►  Late binding requires some overhead but provides increased power and flexibility.

        • *Although, that Base pointer cannot refer to any data field in the derived class.
            - As the compiler depends on the type of the pointer to determine the size it can move when incrementing the pointer for example.
                But, the class functions are only stored once.        
    */

    //  3. using pure virtual functions (true abstract classes):
    Deriv_1 driv1;
    Deriv_2 driv2;
    // Base3 base3Obj;          // Error - instantiating an object of an abstract class
    Base3* ptrBase3[2];         // just another style - pointers array instead of one pointer.
    ptrBase3[0]->func();        // normal function in the abstract class

    ptrBase3[0] = &driv1;
    ptrBase3[0]->show();
    driv1.func();               // normal function in the abstract class can be invoked by the derived class object.
    
    ptrBase3[1] = &driv2;
    ptrBase3[1]->show();

    cout << endl;

    /* The compiler executes different functions, depending on the contents of the pointer.
        • 'Base3' class is an abstract class with atleast one pure virtual function, hence we CANNOT create an object of it,
            only a pointer to it. However, we can put functions with definitions in its body where the BaseClass pointer can refer to.
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


    /// Virtual base classes ////////////////////////////////////////////////////////////:
    Grand_Child gc;
    cout << gc.getData() << endl;
    

    /// Friend functions ////////////////////////////////////////////////////////////////:
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
    

    /// Friend classes //////////////////////////////////////////////////////////////////:
    Gamma g;
    Delta d;

    d.func1(g);
    d.func2(g);
    cout << endl;


    /// Static functions ////////////////////////////////////////////////////////////////:
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


    /// Assignment operator and copy constructor ////////////////////////////////////////:
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

    /// The copy constructor may be invoked:

    // 1 ♦ When an object is defined ♦:
        Zeta z5 = z4;       // Copy initialization is not assignment (=operator function is not invoked)
        cout << "\nz5 = "; z5.display();

        Zeta z6(z4);        // has the same effect (alternative form of copy initialization)
        cout << "\nz6 = "; z6.display();

        cout << endl;
        // Note:    instantiating an object only invokes one cnstructor.
        //          So, these syntaxes do not invoke the 'no-arg constructor' or the 'one-arg constructor', only the copy constructor.

    // 2 ♦ When arguments are passed by 'value' to functions ♦:
        void func(Zeta);
        func(z6);
        // It creates the copy that the function operates on.
        // Remember, the copy constructor is not invoked if the argument is passed by reference or if a pointer to it is passed.
    
    // 3 ♦ When values are returned from functions ♦:
        Zeta func(void);
        z6 = func();

        // The copy constructor creates a temporary object when a value is returned from a function:
        // - The copy constructor would be invoked to create a copy of the value returned by func(), 
        // - and this value would be assigned (invoking the assignment operator) to z6.
        cout << endl;
    

    /* CAUTION:
        'Passing by value' and 'returning by value' invoke the destructor as well, 
        when the temporary objects created by the copy constructor are destroyed when the function returns.
        → This can cause considerable consternation if you’re not expecting it.
        -like giving a new id based on the total number of objects, as this will cause wrong ids when creating new objects-.

        ► So, when working with objects that require more than member-by-member copying (in the copy constructor) 
        Pass and return by reference —not by value— whenever possible.
    */

    // ------------------------------------------------
    // ■ Prohibiting Copying using the assignment operator or copy constructor:

    Eta et1, et2;
    // et1 = et2;               // Error: the assignment function is inaccessable
    // Eta et3(et1);            // Error: the copy constructor is inaccessable


    /// A Memory-Efficient String Class /////////////////////////////////////////////////:
    String s1 = (char*)"When the fox preaches, look to your geese.";            // one-arg constructor invoked
    cout << "\ns1 = ";  s1.display();

    String s2;                  // no-arg constructor invoked
    s2 = s1;                    // overloaded-assignment-operator function invoked
    cout << "\ns2 = ";  s2.display();

    String s3(s1);              // copy constructor invoked
    cout << "\ns3 = ";  s3.display();

    cout << endl;

    // chain equal operator:
    char str[] = "Say cheese!";
    s1 = str;                   // one-arg constructor invoked: String(char*)
    s3 = s2 = s1;               // overloaded-assignment-operator function invoked two times

    cout << "\ns1 = ";  s1.display();
    cout << "\ns2 = ";  s2.display();
    cout << "\ns3 = ";  s3.display();
    cout << endl;

    // String = String; where the count = 1 :
    s2 = (char*)"Hi";
    cout << "\ns2 = ";  s2.display();
    s2 = s2;
    cout << "\ns2 = ";  s2.display();
    cout << endl;


    /// The 'this' pointer //////////////////////////////////////////////////////////////////:
    Theta th1, th2, th3;
    th1.reveal();
    th2.reveal();
    th3.reveal();
    cout << endl;

    Theta th4;
    th4.tester();
    cout << endl;
    

    /// Dynamic Type Information ////////////////////////////////////////////////////////////:
    Derv1_* d1_ = new Derv1_;
    Derv2_* d2_ = new Derv2_;

    if(isDerv1_(d1_))
        cout << "d1_ is a member of the Derv1_ subclass\n";
    else
        cout << "d1_ is not a member of the Derv1_ subclass\n";
    
    if(isDerv1_(d2_))
        cout << "d2_ is a member of the Derv1_ subclass\n";
    else
        cout << "d2_ is not a member of the Derv1_ subclass\n";

    
    /// Upcast and Downcast: --------------------------------
    
    // ♦ Derived-to-Base (upcast): -- points to Base of Derv
        // Upcasts are fine if all you want is the base part of the object.
    Base__* pBase__ = new Base__(10);
    Derv__* pDerv__ = new Derv__(21, 22);

    pBase__ = dynamic_cast<Base__*>(pDerv__);

    cout << endl;
    pBase__->show();
    pDerv__->show();


    // ♦ Base-to-Derived (downcast): -- points to Derv Sub-object of Base
    pBase__ = new Derv__(31, 32);                   // normal

    pDerv__ = dynamic_cast<Derv__*>(pBase__);       // Base__ class must be polymorphic for Downcast dynamic_cast

    cout << endl;
    pBase__->show();
    pDerv__->show();

    cout << endl;

    
    /// The 'typeid' Operator: --------------------------------
    Base_Polymorphic* pB = new Derv1_;
    displayName(pB);

    pB = new Derv2_;
    displayName(pB);
    
    

    return 0;
}


void func(Zeta) {}

Zeta func(void) { return Zeta(0); }

/////////////////////////////////////////////////////////////////////////

/*
    Ad-hoc polymorphism is also known as        overloading.                    (Function overloading)
    Parametric polymorphism is also known as    compile-time polymorphism.      (Function overriding) (Static binding) 
    Subtype polymorphism is also known as       runtime polymorphism.           (Function overriding) (Dynamic binding)

    Coercion is also known as (implicit or explicit) casting.
*/
// Using Virtual tables
// why there is no virtual constructor? Because derived calsses must have their own constructors anyway