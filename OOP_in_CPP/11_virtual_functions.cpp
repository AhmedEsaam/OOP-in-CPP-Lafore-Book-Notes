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
{   };

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







///////////////////////////////////////////////////////////////////////
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





    
    return 0;
}
