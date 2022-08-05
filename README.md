# cpp_graph
Practice C++ project, building a graph and extracting information.

Compile and run.
```
> g++ main.cpp -o main.exe
> main
No args passed
```
You can see what data is available by passing '--show' on the command line
```
> main --show

[4] reading data
[2] opened file data\people.txt
[4] building tree:
[2] opened file data\people\one.txt
[2] root is:Name: Jane, age: 29, with: 3 connections

----------------------------------------------------------

Available Data:

id: 10 Name: Nick, age: 46
id: 9 Name: Alice Jackson, age: 34
id: 8 Name: Lisa, age: 21
id: 7 Name: Tom X, age: 23
id: 6 Name: Caroline M, age: 48
id: 5 Name: Marcus, age: 37
id: 4 Name: Lara, age: 35
id: 3 Name: Jane, age: 29
id: 2 Name: Mark, age: 30
id: 1 Name: Tom, age: 28
```
You can search NAME by passing '--dfs=NAME' or '--bfs=NAME', which will either depth-first or breadth-first search, respectively.
```
> main --dfs=Marcus

[4] reading data
[2] opened file data\people.txt
[4] building tree:
[2] opened file data\people\one.txt
[2] root is:Name: Jane, age: 29, with: 3 connections
[4] Searching for Marcus :

----------------------------------------------------------

Found 1:

Name: Marcus, age: 37, with: 1 connections
```
You can set the logging level by passing an integer >= 0 as last argument, which will show you the order in which the names are checked.
```
> main --bfs="Caroline M" 1

[4] reading data
[2] opened file data\people.txt
[4] building tree:
[2] opened file data\people\one.txt
[2] root is:Name: Jane, age: 29, with: 3 connections
[4] Searching for Caroline M :
[1] checking Jane
[1] checking Marcus
[1] checking Mark
[1] checking Tom X
[1] checking Lara
[1] checking Tom
[1] checking Caroline M
[1] checking Nick
[1] checking Lisa
[1] checking Alice Jackson

----------------------------------------------------------

Found 1:

Name: Caroline M, age: 48, with: 0 connections
```



