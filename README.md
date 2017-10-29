# WatchTrees

C++ Debugger extension for the Windows Debugging Tools (WinDBG, KD, CDB, NTSD). It add commands to manage watches.

## Why WatchTrees ?

In the CDB console, it is easy to display the value of a variable `foo` by typing `?? foo`. However, when `foo` has fields, it becomes difficult to query them by typing their full path `?? foo.bar.alpha.x`.

It is also tedious to query all the variables you're interested in by typing all of them after each step in CDB.

The WatchTrees commands below are quicker to type and manage. They can also be automated by editors such as vim or emacs.

## What is a watch ?

A watch starts with a C++ expression like the name of a variable. If the expression evaluates to a simple C++ type like `int` or `double`, it will display its value and type on a single line. If the expression evaluates to a pointer or an object with fields, it will offer to expand those fields on subsequent lines, giving a tree-like structure.

When `std` containers such as vectors, maps, lists, strings or iterators are expanded, the subwatches will pretty-print their contents.

Watches are reevaluated each time the `print_watches` command is invoked (see below).

## Commands

* `print_watches`: reevaluate and print watches. If the flag `--reevalExpr` is given, it will also revaluate the root C++ expressions defining the watches. Some variables may go out of scope when doing this, they will collapse during the print.
* `new_watch <expr>`: create new watch with expression `<expr>`. Call print_watches next to display it.
* `set_watch_value <watch path> <value>`: the watch path is a 0-based series of numbers, followed by the value that will be assigned to this watch.
* `rename_watch <number> <expr>`: replace watch `<number>` by C++ expression `<expr>`. Delete all its previous subwatches.
* `expand_watch <watch path>`: expand a subwatch. Call print_watches next to display the expanded watches.
* `collapse_watch <watch path>`: collapse a subwatch. Call print_watches next to display collapsed watches.
* `clear_watches`: delete all watches.
* `clear_watch <number>`: delete a single watch.

## Compile WatchTrees

This project was tested on Windows Kit 10 (dbgeng.dll version 10.0.16299.15) and developped on Visual Studio 2017 Community.

If you have Windows Kit 10 installed, CDB headers such as `dbgeng.h` and `dbghelp.h` become system headers and will be found by Visual Studio when compiling WatchTrees.sln.

## Use WatchTrees

From a CDB console, first call
`.load WatchTrees.dll`

Then the previous commands become known to CDB and you can invoke them with the exclamation mark, like
`!print_watches`