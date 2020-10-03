# Ex3
## workflow
the project divided to 7 modules, 4 modules for the 4 types of commands, one that parses the terminal and 
one module that binds them together with the terminal parser.

## SOLID
* **S:single responsibility** - each module has a distinct, well defined purpose. 
* **O:open-close** - each command is closed for modification, but you can add modules and methods so it's open for extension.
* **L:liskov substitution principle** - no inheritence, no problem.
* **I:interface segregation principle** - no interfaces, no problem.
* **D:dependency inversion principle** - the high level modules are dependent on the .hpp files, so it's up to the programer to choose its implementation.