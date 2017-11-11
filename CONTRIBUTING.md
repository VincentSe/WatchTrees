**Thanks for contributing to WatchTrees !**

When submitting a pull request, please specify the general category of what it improves, for example :

 - **Correctness :** the value of a watch path was wrong, as compared to what the C++ compiler would evaluate for the same path.
 - **Performance :** print (and re-evaluate) the watches faster.
 - **Crash :** a command sent to WatchTrees makes it crash or send an uncaught exception. This includes memory leaks.

Then please provide a detailed test case, which consists of

 1. a simple C++ file which produces an executable with no arguments
 2. the line number in that C++ file where to set the breakpoint with CDB
 3. when arrived at that breakpoint, the list of WatchTrees commands that make the problem appear

An English summary of what the test case does is also welcome, you can add it as a C++ comment :)

A huge effort that would be most approciated is managed watches for C# and other .NET languages. They could partly be implemented using SOS.dll.
