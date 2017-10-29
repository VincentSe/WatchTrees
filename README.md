# WatchTrees

C++ Debugger extension for the Windows Debugging Tools (WinDBG, KD, CDB, NTSD). It add commands to manage watches.

## What is a watch ?

A watch starts with a C++ expression like the name of a variable. If the expression evaluates to a simple C++ type like int or double, it will display its value and type on a single line. If the expression evaluates to a pointer or an object with fields, it will offer the expand those fields on subsequent lines.

When std containers such as vectors, maps or strings are expanded, the subwatches will pretty-print their contents.

Watches are reevaluated each time the print_watches command is invoked (see below).

## Commands

* print_watches                          - reevaluate and print watches. If the flag --reevalExpr is given, it will also revaluate the root C++ expressions defining the watches. Some variables may become out of scope when doing this, they will collapse during the print.
* new_watch <expr>                       - create new watch with expression <expr>. Call print_watches next to display it.
* set_watch_value <watch path> <value>   - the watch path is a 0-based series of numbers, followed by the value that will be assigned to this watch.
* rename_watch <number> <new name>       - replace a watch by another C++ expression.
* expand_watch <watch path>              - expand a subwatch. Call print_watches next to display the expanded watches.
* collapse_watch <watch path>            - collapse a subwatch. Call print_watches next to display collapsed watches.
* clear_watches                          - delete all watches.
* clear_watch <number>                   - delete a single watch.

## Compile WatchTrees

This project was tested on Windows Kit 10 (dbgeng.dll version 10.0.16299.15) and developped on Visual Studio 2017 Community.

If you have Windows Kit 10 installed, CDB headers such as dbgeng.h and dbghelp.h become system headers and will be found by Visual Studio when compiling WatchTrees.sln.