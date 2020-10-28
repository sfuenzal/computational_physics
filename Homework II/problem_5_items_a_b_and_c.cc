#include <iostream>

int main()
{

    //Item a)

    int * ip;
    string s, *sp = 0;
    int i; double * dp = &i;
    int * ip, ip2;
    const int i = 0, *p = i;
    string *p = NULL;

    //item b)

    //In principle, pointers are meant to point to valid addresses, 
    //such as the address of a variable or the address of an element in an array. 
    //But pointers can actually point to any address, including addresses that do not 
    //refer to any valid element. Typical examples of this are uninitialized pointers
    //and pointers to nonexistent elements of an array:

    int * p;               // uninitialized pointer (local variable)
    int myarray[10];
    int * q = myarray+20;  // element out of bounds 

    //Neither p nor q point to addresses known to contain a value, 
    //but none of the above statements causes an error. 
    //In C++, pointers are allowed to take any address value, 
    //no matter whether there actually is something at that address or not. 
    //What can cause an error is to dereference such a pointer 
    //(i.e., actually accessing the value they point to). 
    //Accessing such a pointer causes undefined behavior, ranging from an error during 
    //runtime to accessing some random value.

    //item c)

    int i = 42;
    void *p = &i;
    long *lp = &i;

}