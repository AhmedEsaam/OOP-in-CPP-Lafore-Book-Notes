// What will be the output of the following program?
#include <iostream>

using namespace std;


class Base
{
    public:
    char S, A, M; 
    Base(char x, char y)
    {
        S = y - y;
        A = x + x; 
        M = x * x;
    }
    Base(char, char y = 'A', char z = 'B')
    {
        S = y;
        A = y + 1 - 1; 
        M = z - 1;
    }
    void Display(void)
    {
        cout<< S << " " << A << " " << M << endl;
    }
};
class Derived : public Base
{
    char x, y, z; 
    public:
    Derived(char xx = 65, char yy = 66, char zz = 65): Base(x)
    {
        x = xx; 
        y = yy;
        z = zz;
    }
    void Display(int n)
    {
        if(n)
            Base::Display(); 
        else
            cout<< x << " " << y << " " << z << endl; 
    }
};
int main()
{
    Derived objDev; 
    objDev.Display(0-1); 
    return 0;
}

/*
File handling in C++ refers to the process of working with files, which involves reading data from files or writing data to files. C++ provides several classes and functions to perform file operations. Here's an overview of file handling in C++:


1. Include the necessary headers:
   To work with file handling in C++, you need to include the `<fstream>` header, which provides classes like `ifstream`, `ofstream`, and `fstream` for file input/output operations.


2. Opening a file:
   To perform file operations, you need to open a file. There are three main modes for opening a file:


  - `ifstream`: Used for reading input from a file.
   - `ofstream`: Used for writing output to a file.
   - `fstream`: Used for both reading and writing operations.


  You can open a file using the `open()` member function of the file stream objects or by passing the filename as a parameter to the constructor.


  ```cpp
   #include <fstream>
   using namespace std;


  int main() {
       ofstream outputFile;
       // Open a file for writing
       outputFile.open("example.txt");


      // Perform file operations


      // Close the file
       outputFile.close();


      return 0;
   }
   ```


3. Writing to a file:
   To write data to a file, you can use the `<<` operator or the `write()` function.


  ```cpp
   ofstream outputFile;
   outputFile.open("example.txt");


  // Writing using the << operator
   outputFile << "Hello, World!" << endl;


  // Writing using the write() function
   outputFile.write("Hello, World!", 13);


  outputFile.close();
   ```


4. Reading from a file:
   To read data from a file, you can use the `>>` operator or the `getline()` function.


  ```cpp
   ifstream inputFile;
   inputFile.open("example.txt");


  // Reading using the >> operator
   string data;
   inputFile >> data;


  // Reading using the getline() function
   string line;
   getline(inputFile, line);


  inputFile.close();
   ```


5. Error handling:
   It's important to check for errors during file operations. You can use the `fail()` function to check if an operation has failed, and the `good()` function to check if the file stream is in a good state.


  ```cpp
   ifstream inputFile;
   inputFile.open("example.txt");


  if (inputFile.fail()) {
       // File opening failed
       cout << "Failed to open the file." << endl;
   } else {
       // File opening succeeded


      // Perform file operations


      // Check if the file stream is in a good state
       if (inputFile.good()) {
           cout << "File operations completed successfully." << endl;
       } else {
           cout << "An error occurred during file operations." << endl;
       }
   }


  inputFile.close();
   ```


6. File position:
   You can manipulate the file position using functions like `seekg()` and `tellg()` for `ifstream` objects (for reading) and `seekp()` and `tellp()` for `ofstream` and `fstream` objects (for writing).


  ```cpp
   ifstream inputFile;
   inputFile.open("example.txt");


  // Get the current file position
   streampos position = inputFile.tellg();


  // Set the file position to the beginning
   inputFile.seekg(0);


  // Perform file operations


  inputFile.close();
   ```


These are some of the basic operations involved in file handling in C++. You can explore more advanced operations and techniques, such as working with binary files, error handling, and file manipulation functions provided by the `<fstream>` header, to suit your specific requirements.
*/