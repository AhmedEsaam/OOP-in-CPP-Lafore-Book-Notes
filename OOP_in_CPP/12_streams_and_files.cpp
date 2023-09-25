#include <iostream>
#include <fstream>
// #include <iomanip>
// #include <strstream>
using namespace std;

// A 'stream' is a general name given to a flow of data.

/** Advantages of Streams:
    ► There are no such formatting characters (like %d, %f, ...) in streams, 
        → since each object already knows how to display itself. This removes a major source of errors.

    ► You can overload existing operators and functions, 
        such as the insertion (<<) and extraction (>>) operators, to work with classes that you create.
        → Which makes programming easier and more error free (not to mention more aesthetically satisfying).
        
    ► They are the best way to write data to files.

    ► And also to format data in memory for later use in text input/output windows and other GUI elements.
*/


/** Header files for decalred Classes:
 * <iostream>   The classes used for input and output to the video display and keyboard are declared in this header file.
 * <fstream>    The classes used specifically for disk file I/O are declared in this file.  
 * 
 * <iomanip>    Also, some manipulators are declared in this header file.
 * <strstream>  and in-memory classes are declared in this header file. 
*/


/** Classes:
 *  'ios' class:
 *      is the granddaddy of all the stream classes, and contains the majority of the features you need to operate C++ streams:
 *      The three most important features are:
 *      - the formatting flags
 *      - the error-status flags
 *      - the file operation mode
 * 
 *  'istream' class contains:
 *      - get()
 *      - getline()
 *      - read()
 *      - the overloaded extraction (>>) operators
 * 
 *  'ostream' class contains:
 *      - put()
 *      - write()
 *      - the overloaded insertion (<<) operators
 * 
 * 'iostream' class:
 *      - derived from both istream and ostream by multiple inheritance. 
 *          Classes derived from it can be used with devices, 
 *          (such as disk files, that may be opened for both input and output at the same time.)
 * 
 * 'istream_withassign', 'ostream_withassign', and 'iostream_withassign':
 *      - They add assignment operators to these classes.
*/



int main()
{

    
    
    return 0;
}
