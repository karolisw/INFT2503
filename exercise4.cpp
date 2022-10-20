

int main() {

    // Original code with comments
/*
    int a = 5; // allowed
    int &b; // Not allowed, because &b is an adress, meaning that it cannot be declared (and should be on the right side of the "=")  
    int *c; // Allowed to declare a pointer that does not point to anything yet 
    c = &b; // C now points to the adress of the variable b, which has not yet been initialized, meaning this is wrong
    *a = *b + *c; // a is of type int, not pointer, and the pointer (and value) of b does not exist
                  // Also, a and b already exists as integer variables
    &b = 2; // This is wrong because while it is allowed to have a referanse point to a new adress, the "2" would have
            // had to be switched out with another variable (an initialized variable with an address)
            // and the &b would have had to not allready be initialized
*/
    // Rewritten code
    int a = 5; 
    int b = 3;
    int *c; 
    c = &b; // Because b is initialized here, this is allowed

    int *d = &a; // b-pointer points to the adress of a
    int *e = &b; // a-pointer points to the adress of b
    *d = *e + *c;
    int &f = a; // OK now because the ref f was not allready assigned to an address in memory
}