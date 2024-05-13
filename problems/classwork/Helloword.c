#include <stdio.h>

int add (int a, int b);
int add1 (int* a, int* b);
void add2 (int* a, int* b, int* c);

int main(int argc, char* argsv[]) {

    int x = 4;

    printf("x: %d\n", x);

    if (x == 4) {
        printf("x is 4\n");
    }

    for (int i = 0; i < x ; i++ ) {
        printf("i: %d\n", i);
    }

    //puntero int*  
    int* x_addr = &x;

    printf("x_addr: %p\n", x_addr);

    //funciones

    int y = 6;
    int z = add (x, y);

    printf("z: %d\n", z);

    int j = add1(&x, &y);

    printf("j: %d\n", j);

    int k = 0;
    add2(&x, &y, &k);

    printf("k: %d\n", k);
    return 0;
}

int add (int a, int b) {
    return a + b;
}

int add1 (int* a, int* b) {
    return *a + *b;
}

void add2(int* a, int* b, int* c) {
    *c = *a + *b;
}