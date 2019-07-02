# Balanced_Symbol_Checker
### We will often use symbols together to specify the beginning and ending of an item, such as the use of parentheses in a mathematic expression or the use of curly braces in a C, C++ or Java program.

This program, will be checking the following symbol pairs:

• parentheses: ( )

• curly braces: { }

• square brackets: [ ]

• angle brackets: < >

This program will require the use of a stack implemented in a dynamic array. This dynamic array is to grow to a larger size when a push operation would be done to a full array causing an array overflow. 

The program runs till it reads 300 characters and only the letter q or Q, will quit the program.

Some examples:

( ( a a ) < > [ [ [ { [ x ] } ]]] <>)
Expression is balanced

( ( a a ) < > [ [ [ { [ x ] ]]] <>)
expecting }

( ( a a ) ) < > > [ [ [ { [ x ] } ]]] <>)
missing <
