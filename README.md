# compiler-v2

This was my first real attempt at writing a compiler.

This compiler is only capable of compiling to three address code, and is probably filled with bugs,
but it was a successful project in that it taught me a lot in how compilers work.
If I continue studying compilers, I will probably create the next one in Rust instead of C++.

Here is an example program that this compiler can read, along with the three address code it creates for it.


Input:

var a int;  
var b int; 
 
while (a != b) { 
    if (a > b) { 
      a = a - b; 
    } else { 
      b = b - a; 
    } 
}  

Output:

LABEL 3   
t1 = i1 != i2   
IF t1 == 0 JUMP 4    
t2 = i1 > i2       
IF t2 == 0 JUMP 1  
t3 = i1 - i2    
i1 = t3  
JUMP 2  
LABEL 1  
t4 = i2 - i1   
i2 = t4   
LABEL 2 
JUMP 3   
LABEL 4
