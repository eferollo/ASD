#include <stdio.h>
#include <stdlib.h>
#include "H.h"

int main() {
    FILE *fp;
    fp=fopen("charset.txt", "r");
    if(fp==NULL) exit(-1);

    H h=Hinit();
    newHeap(h,fp);
    HuffHeapEncode(h);
    char *str;
    str=decode(h,"111110111101111011101001000");
    printf("%s", str);
    return 0;
}
