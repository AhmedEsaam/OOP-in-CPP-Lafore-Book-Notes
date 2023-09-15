#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/*
    Uses of pointers?
    • Accessing array elements
    • Passing arguments to a function when the function needs to modify the original argument
    • Passing arrays and strings to functions
    • Obtaining memory from the system
    • Creating data structures such as linked lists
    • when we sort person objects for example, we don’t move the objects themselves; 
        we move the pointers to the objects. 
        ► This eliminates the need to shuffle the objects around in memory,
            which can be very time-consuming if the objects are large.
        ► It could also, if we wanted, allow us to keep multiple sorts in memory at the same time
            without storing the objects multiple times 
*/
/** Note:
    But almost all of those applications can be performed without the use of pointers,
    However, in some situations pointers provide an essential tool for increasing the power of C++, as in:
    ► The creation of data structures such as 'linked lists' and 'binary trees',
    ► virtual functions,
    ► the 'new' operator,
    ► and the 'this' pointer.
*/

const int MAX = 5;      // Array Size


///* @brief String class using 'new'
// with not the same amount of memory for every object,
// using 'new' to obtain exactly the right amount of memory. 
class String
{
private:
    char *str;
public:
    String(char *s)
    { 
        int length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
        // There is no array within the object to hold the string.
        // >> The string is stored elsewhere; only the pointer to it is a member of 'String'.
    }
    ~String()
    {
        cout << "Deleting String." << endl;
        delete[] str;
        // It’s reasonable to deallocate the memory when the object is no longer needed.
        // Since this class allocates memory at run time which is not deallocated automatically by itself
        //  when scope terminates, unless it is deallocated deliperately.
    }
    void display()
        { cout << str << endl; }
};
/* Note:
    You can view Class Objects with 'new' (mostly that incorporates an array) 
        >> actually represents just a pointer to an allocated memory that holds data,
    obj1 = obj2; actually copies that pointer - so there is two pointers to the same allocated memory.
    - The problem is deleting one (deallocating that memory) actually leaves the other pointer dangling.
    = And this can be subtle, because objects can be deleted in nonobvious ways, 
        such as when a function in which a local object has been created returns.
*/


class Distance
{
private:    
    int feet;
    float inches;
public:
    void get_dist()
    {
        cout << "Enter feets: ";    cin >> feet;
        cout << "Enter inches: ";   cin >> inches;
    }
    void show_dist() const
    {   cout << feet << "\' " << inches << "\"" << endl; }
};


class Person
{
private:
    string name;
public:
    void setName()
    {   cout << "Enter name: "; cin >> name; }
    void printName()
    {   cout << name << endl;}
    string getName()
    {   return name; }
};



///* Linked list ............................................................:
/* 
    The linked list provides a more flexible storage system than fixed-size contiguous arrays in that: 
    • It doesn’t use arrays at all. Instead, space for each data item is obtained as needed with 'new', 
        (each item is connected, or linked, to the next data item using a pointer.) 
    • The individual items don’t need to be located contiguously in memory the way array elements are; 
        they can be scattered anywhere. 

    ☼ The disadvantage is that:
        finding a particular item on a linked list requires following the chain of links 
            from the head of the list until the desired link is reached.
            Unlike arrays where items can be accessed quickly provided the index.
*/

struct Link         // a list item
{
    int data;
    Link* next;
};


class Linklist
{
private:
    Link* head;
public:
    Linklist() : head(NULL)
    {   }
    void add_item(int);
    void display();
};

void Linklist::add_item(int d)
{
    Link* newlink = new Link;       // allocate memory for a new link
    newlink->data = d;              // set the data variable to the value passed as an argument
    newlink->next = head;           // A new link is inserted at the beginning of the list
    head = newlink;                 // head points to the newest link
}
/* The effect is to:
    ► uncouple the connection between head and the old head link, 
    ► insert the new link, 
    ► and move the old head link into the second position. 
*/

/* Note IMPORTANT:
    - While Classes and Structs can contain a 'pointer' to an object of their own type, 
    they cannot contain an object of their own type.
*/

/* Note:
    A structure is similar to a class in that: 
    >> when it is referred to by pointer rather than by name, 
        → its members are accessed using the -> member-access operator. 
*/


void Linklist::display()
{
    Link* current = head;
    // while(current != NULL)
    // {
    //     cout << current->data << endl;
    //     current = current->next;
    // }
    
    // another way of printing
    for( ; current != NULL; current = current-> next)
        {   cout << current->data << endl; }
}



///* Parsing Arithmetic Operations .....................................................:
// evaluates arithmetic expressions composed of 1-digit numbers.

class Stack
{
private:
    static const int SIZE = 40;
    char st[SIZE];
    int top;
public:
    Stack() : top(-1) { };
    void push(char var)
    {   st[++top] = var; }
    char pop()
    {   return st[top--]; }
    int get_top()
    {   return top; }
};

const int LEN = 80;

class Expr
{
private:
    Stack st;
    char* pStr;
    int len;
public:
    Expr(char* str)
    {
        pStr = str;
        len = strlen(pStr);
    }
    int evaluate();
    void solve_last_op();
};


int Expr::evaluate()
{
    char ch;
    char lastOp;

    for (int i = 0; i < len; i++)
    {
        ch = pStr[i];
        
        if(ch >= '0' && ch <= '9')
        {   st.push(ch - '0'); }

        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            // Solve last operation whenever it's possible
            if(st.get_top() > 1)
                // except if this operator is * or / AND last operator was + or -
                if(!((ch == '*' || ch == '/') && (lastOp == '+' || lastOp == '-')))
                {   solve_last_op(); }
            st.push(ch);
            lastOp = ch;
        }

        else
        {   cout << "\nUnknown input character"; exit(1); }
    }   

    while(st.get_top() > 0)     // evaluate the resulting stack
    {   solve_last_op(); }

    return int(st.pop());
}


void Expr::solve_last_op()
{
    char lastVal = st.pop();
    char lastOp = st.pop();
    switch(lastOp)
    {
    case '+': st.push(st.pop() + lastVal); break;
    case '-': st.push(st.pop() - lastVal); break;
    case '*': st.push(st.pop() * lastVal); break;
    case '/': st.push(st.pop() / lastVal); break;
    default: cout << "\nUnknown operator"; exit(1);
    }
} 

    
////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int v1 = 26;
    cout << &v1 << endl;        // & var : address of var

    int* ptr = &v1;             // int * : a pointer to int
    cout << ptr << endl;
    cout << *ptr << endl;       // * ptr : dereference ptr 

    char *ptr1, *ptr2, *ptr3;   // defining multible pointers on the same line

    int v2 = *ptr;
    cout << v2 << endl;

    /* Note:
        The pointer must be given some value, or it will point to an addresss we don’t want it to point to.
        >> Rogue pointer values can result in system crashes and are difficult to debug.
        So, Make sure you give every pointer variable a valid address value before using it.
    */

    ///* To assign one kind of pointer type to another ................................:
    float flovar = 98.6;
    // int* ptrint = &flovar;   //ERROR: can’t assign float* to int*
    int *ptrint = reinterpret_cast<int*>(&flovar); 
    // Static casts won’t work with pointers. 
    // Old-style C casts can be used, but are always a bad idea in C++.


    ///* void pointers ................................................................:
    void *vptr;     // vptr can point to any data type.
                    // • Can be used to pass pointers to functions that operate
                    //   independently of the data type pointed to.
    int ivar;
    float fvar;
    vptr = &ivar;   // Ok
    vptr = &fvar;   // Ok
    

    ///* A capsule summary ...........................................................:
    int v;      // defines variable v of type int
    float f;    // defines variable f of type float
    int* p;     // defines p as a pointer to int
    p = &v;     // assigns address of variable v to pointer p
    v = 3;      // assigns 3 to v
    *p = 3;     // also assigns 3 to v
    void* vp;   // defines vp as a pointer to void 
    vp = &v;    // assigns address of variable v to pointer vp
    vp = &f;    // assigns address of variable f to pointer vp
    p = reinterpret_cast<int*>(&f);    // assigns address of float variable f to the pointer to int p

    
    ///* Pointers and Arrays .........................................................:
    int i;
    int intArr[5] = {56, 62, 96, 45, 12};
    for (i = 0; i < 5; i++)
    {   cout << endl << *(intArr + i); } cout << endl;     // the name of an array is its address
    // The C++ compiler is smart enough (using the pointer type) to take the size of the data into account when
    //   it performs arithmetic on data addresses (here it increments by the size of int.)
    /* Note:
        Array name is a pointer constant (lvalue) NOT a pointer variable,
        Which means that it is the address where the system has chosen to place your array.
        intArr++;  is like  0x36466631++;
        But intArr[i] is an rvalue as it is *(intArr + i)
    */

    int *iArrptr = intArr;
    for (i = 0; i < 5; i++)
    {   cout << endl << *(iArrptr++); } cout << endl;
    // because iArrptr is a variable and not a constant, it can be incremented. 

    
    ///* Passing by pointer ..........................................................:
    void centimize(double*);
    
    double dist = 10.0;     // in inches
    cout << "\ndist = " << dist << " inches" << endl;
    
    centimize(&dist);
    cout << "dist = " << dist << " centimeters" << endl;
    

    ///* Passing Arrays ..............................................................:
    void centimizeArr(double*);
    
    double dblArr[MAX] = {10.0, 43.1, 95.9, 59.7, 87.3};
    centimizeArr(dblArr);
    
    for ( i = 0; i < MAX; i++)
    {   cout << "\ndblArr[" << i << "] = " << dblArr[i] << " cm"; } cout << endl;
    

    ///* Arry Bubble Sort ............................................................:
    void BubbleSort(int *, int);
    int intArr2[MAX] = {61, 46, 49, 32, 64};
    BubbleSort(intArr2, MAX);
    
    for (i = 0; i < MAX; i++)
    {   cout << endl << intArr2[i]; } cout << endl;
    

    ///* Pointers to string ..........................................................:
    char str1[] = "Defined as an array";
    char *str2 = "Defined as an pointer";
    
    cout << str1 << endl;
    cout << str2 << endl;
    
    //  str1++;         // can't do this; str1 is a constant
        str2++;         // this is ok, str2 is a pointer

    void dispStr(char*);
    dispStr(str1);
    dispStr(str2);

    void cpyStr(char*, const char*);
    char *str3 = "Self-conquest is the greatest victory.";
    char str4[50];
    cpyStr(str4, str3);
    cout << str4 << endl;

    
    ///* const modifiers and pointers ................................................:
    const int ciVar = 4;
    int iVar = 5;
    
    /// pointer to const int:
    const int * pcInt;                  // pointer to const int
    int const * pcInt2;                 // same thing ...
    pcInt = &ciVar;                     // points to const int
    pcInt = &iVar;                      // points to int
    ivar = 6;                           // ivar value stll can be changed (it's stll int not const int)
    // 'const int' must be pointed to by (pointers to const int),
    //  while 'int' can be pointed to by either a (ptr to int) or a (ptr to const int) [here it does not mean that the var int cannot be changed.]
    
    /// const pointer to int:
    int * const cpInt = &iVar;          // (const pointer) to int (you cannot change the value of the pointer.)
    // int * const cpInt2 = &ciVar;     // Error: cannot point to const int
    // cpInt = &v1;                     // Error: you cannot change const ptr value 

    /// const pointer to const int:
    const int * const cpcInt = &ciVar;
    

    ///* Arrays of strings ..........................................................:
    /* Note:
        There is a disadvantage to using an array of strings, 
        in that the subarrays that hold the strings must all be the same length. */
    // But we can use pointers to solve this problem:
    
    const int DAYS = 7;
    char* pDays[DAYS] = {"Saturday", "Sunday", "Monday", "Tuesday",
                        "Wedensday", "Thursday", "Friday"};
    for (i = 0; i < DAYS; i++)
    {   cout << endl << pDays[i]; } cout << endl;
    
    // • The char pointer holds the address of the head character in the string. 
    //      It is these addresses that are stored in the array. 
    //      (while actual strings' values are not part of the array.)
   
    // • When strings are not part of an array, C++ places them 'contiguously' in memory,
    //      So there is no wasted space.
    
    
    ///* Memory Management: 'new' and 'delete' ......................................:
    
    // The 'new' operator: obtains memory from the operating system
    //   and returns a pointer to its starting point (with the appropraite data type.) 
    char str5[] = "Idle hands are the devil's workshop.";
    int len = strlen(str5);
    
    char *pch;
    pch = new char[len + 1];    // sets aside memory: string + '\0' (dynamically allocated memory)

    strcpy(pch, str5);
    cout << "\npch = " << pch << endl;
    
    /* There is no C++ equivalent to 'realloc' where you can change the size of memory that has been alloctaed.
        - You’ll need to fall back on the ploy of creating a larger (or smaller) space with new, 
            and copying your data from the old area to the new one.  
    */
    
    delete[] pch;               // release pointer's memory

    /* Using new and delete in functions
        - If the function uses a local variable as a pointer to this memory, 
            the pointer will be destroyed when the function terminates.
        BUT: the memory will be left as an orphan, taking up space that is inaccessible to the rest of the program. 
            So, Thus it is always good practice, and often essential, to delete memory when you’re through with it.
    */
    // Note: Deleting the memory doesn’t delete the pointer that points to it.
    //       and doesn’t change the address value in the pointer. 
    //       However, this address is no longer valid (doesn't point to allocated memory.)

    // allocating a single object
    float * pFloat = new float;     // note that this var has name, only a pointer to it.
    delete pFloat;

    
    ///* String class using 'new' ...................................................:
    String s1  = "Who knows nothing, doubts every thing.";
    cout << "\ns1 = "; s1.display();

    String s2 = s1;     // only copies the char* ptr to the same allocated memory.
    cout << "s2 = "; s2.display();
    cout << endl;


    ///* Creating objects at run-time ...............................................:
    Distance dist1;             // normal nammed object
    dist1.get_dist();
    dist1.show_dist();
    cout << endl;

    Distance *pDist;            // pointer to Distance
    pDist = new Distance;       // allocate memory for a Distance at run-time
    pDist->get_dist();          // access the unnamed object members
    pDist->show_dist();         // using the membership-access operator -> 
    (*pDist).show_dist();       // this is ok as well but inelegant!
    cout << endl;

    // OR (for a less common approach):
    // You can refer to objects obtained with 'new' by an alias:
    Distance& dist2 = *(new Distance);
    dist2.get_dist();           // use the dot operator . normally
    dist2.show_dist();
    cout << endl;


    ///* Array of pointers to objects ...............................................:
    Person* pPer[100];
    int n = 0;
    char choice;

    do
    {
        pPer[n] = new Person;
        pPer[n]->setName();
        n++;
        cout << "Enter another (y/n)? "; cin >> choice;        
    } while (choice == 'y');
    

    for (i = 0; i < n; i++)
    {   pPer[i]->printName(); }
    cout << endl;


    ///* Pointers to pointers .......................................................:
    void Person_bsort(Person**, int);
    Person_bsort(pPer, n);

    cout << "\nList sorted: \n";
    for (i = 0; i < n; i++)
    {   pPer[i]->printName(); }     cout << endl;
    
    /* Sorting pointers:
        • when we sort person objects for example, we don’t move the objects themselves; 
            we move the pointers to the objects. 
            ► This eliminates the need to shuffle the objects around in memory,
                which can be very time-consuming if the objects are large.
            ► It could also, if we wanted, allow us to keep multiple sorts—one by name and another by phone number, for example—
                in memory at the same time without storing the objects multiple times.
                (and that can be done by creating another array of pointers which we can sort in another way.)
    */
   

    ///* Linked lists ...............................................................:
    Linklist lInt;        // make an int linked list
    lInt.add_item(25);
    lInt.add_item(56);
    lInt.add_item(89);
    lInt.add_item(46);

    lInt.display();


    ///* Parsing Arithmetic Operations: .............................................:
    char ans;
    char str[LEN];

    cout << "\nEnter an arithmetic expression of the form 2+3*4/3-2"
            "\nNo number may have more than one digit."
            "\nDont use any spaces or parantheses.";
    do
    {
        cout << "\nEnter expression:" << endl;
        cin >> str;
        Expr* pExpr = new Expr(str);     // make expression
        // pExpr->evaluate();
        cout << "= " << pExpr->evaluate();
        delete pExpr;

        cout << "\nDo another? (y/n): ";    cin >> ans;
    } while (ans =='y');
    
    


    
    return 0;
}



///* functions definitions ..........................................................:

void centimize(double* pDist)
{   *pDist *= 2.54; }


void centimizeArr(double* pArr)
{   
    for (int i = 0; i < MAX; i++)
    {   *pArr++ *= 2.54; }    
}


// Bubble Sort ....................................................:

#define SWAP(X, Y)      (X^=Y^=X^=Y)
#define ORDER(X, Y)     ((X > Y) ? SWAP(X, Y) : 1)

// Bubble sort variation: specifying minimums to the beginning of the list
void BubbleSort(int *arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            ORDER(arr[i], arr[j]);
}


// Bubble sort variation: specifying maximums to the end of the list
void BubbleSort2(int *arr, int n)
{
    int i, j, swpd = 0;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
            {   ORDER(arr[j], arr[j + 1]);  swpd = 1; }
        if(!swpd) break;
    }   
}


void BubbleSort3(int *arr, int size)
{
    int swapped = 0;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {   
                arr[j] ^= arr[j+1] ^= arr[j] ^= arr[j+1];   // swap
                swapped = 1;
            } 
        }
        if(swapped == 0) {cout << "\nswapped"; break;}   
    }
}


// String functions ................................................:
void dispStr(char* str)
{
    while(*str) 
        cout << *str++;
    cout << endl;
}

void cpyStr(char* dst, const char* src)
{
    while(*src)
        *dst++ = *src++;
    *dst = 0;
}


// Person Bubble Sort..............................................:
void Person_bsort(Person** pp, int n)
{
    void order(Person**, Person**);         // We will change the ptr to Person. So, we need to pass a ptr to it (ptr to ptr)
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            {   order(&pp[i], &pp[j]); }
        // or:  order(pp + i, pp + j); 
}

void order(Person** pp1, Person** pp2)
{
    if((*pp1)->getName() > (*pp2)->getName())
    {
        Person* temp = *pp1;
        *pp1 = *pp2;
        *pp2 = temp;
    }
}       

