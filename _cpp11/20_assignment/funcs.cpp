int Add(int *a, int *b) {
    return *a + *b;
}

void AddVal(int *a, int *b, int *result) {
    *result = *a + *b;
}

void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Factorial(int *a, int *result) {
    for(int i=1; i<=*a; ++i) {
        *result *= i;
    }
}