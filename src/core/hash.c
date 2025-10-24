#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/param.h>

int hash(char* name) {
    int k;
    int len;

    len = strlen(name);
    if (len <= 0) {
        printf("Invalid string size in %s\n", __func__);
    }

    k = (name[1] * 13) + (name[MIN(len, 2)] * 17) + (name[MIN(len, 3)] * 11) +
           (name[MAX(len - 2, 1)] * 3) + (name[MAX(len - 1, 1)] * 7) + (name[len] * 19);

    return k % 128;
}

#ifdef TEST_HASH
int main() {
  char buf[500];
   while (1) {
    scanf("%s", buf);
    unsigned int h = hash(buf);
    printf("Hash for %s is %d\n", buf, h);
  }
}

#endif
