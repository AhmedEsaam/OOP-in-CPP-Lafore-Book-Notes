#include <iostream>
using namespace std;

int main(void)
{
    /* STRUCTURES: ..................................................................*/

    struct Part
    {
        int modelnum;
        int partnum;
        float cost;
    };

    Part part1; // no need to put 'struct' in the beginning like in C.

    // Initializaion:
    part1 = {164, 6464, 46.56F};
    Part part2;

    cout << "Part1:" << endl;
    cout << part1.modelnum << endl
         << part1.partnum << endl
         << part1.cost << endl;

    part2 = part1;
    cout << "\nPart2:" << endl;
    cout << part2.modelnum << endl
         << part2.partnum << endl
         << part2.cost << endl;

    // Or
    part1 = {.modelnum = 164, .partnum = 6466, .cost = 313.6464F};

    cout << "\nPart1:" << endl;
    cout << part1.modelnum << endl
         << part1.partnum << endl
         << part1.cost << endl
         << endl;

    /* Structures can't be added or compared: (because there can't be operator overloading with structures)
        part2 = part1 + part2;   → wrong
        if(part1 == part2)       → wrong
    */

    /* Structures and Classes:
        Most C++ programmers use structures exclusively for data.
        Classes are usually used to hold both data and functions.

            > However, in C++, structures can in fact hold both data and functions.
            The syntactical distinction between structures and classes in C++ is minimal,
                > so they can in theory be used almost interchangeably.
    */

    /* ENUMERATIONS ................................................................*/

    enum day_of_week
    {
        sat,
        sun,
        mun,
        tue,
        wed,
        thu,
        fri
    };

    day_of_week day1, day2; // no need to put 'enum' in the beginning like in C.
    day1 = fri;
    day2 = sun;

    int diff = day1 - day2; // can do arithmetic operations → Enumerations are treated internally as integers
    cout << diff << endl;

    if (day1 > day2)
    {
        cout << "day2 comes before day1" << endl;
    }

    return 0;
}


/* Note:
    Data constructs such as structures and classes end with a semicolon, 
    while control constructs such as functions and loops do not.)
*/