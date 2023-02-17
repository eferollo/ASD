#include <stdio.h>
#include "nTREE.h"

int main() {
    nTREE t=init();
    printf("Res: %d\n", countIf(t));

    return 0;
}
