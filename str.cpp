#include <cstdio>
#include <cstring>
#include <iostream>

void reverse(char* s, int len) {
    if (s == NULL || len == 0) return;
    int i = 0, j = len -1;
    while (i < j) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
}

void reverse_words(char* s, int len) {
    if (s == NULL || len < 3) return;
    reverse(s, len-1);
    int i = 0, j = 0;
    for (i = 0; i < len-1;) {
        for (j = i; j < len-1; j++) {
            if (s[j]==' ' || j==len-2) {
                int rlen = (j==len-2 ? j-i+1 : j-i);
                reverse(s+i, rlen);
                i = j + 1;
                break;
            }
        }
    }
}

int main(int argc, char** argv) {
    printf("---原地反转句子，单词不反转，句尾标点符号不动。---\n");
    char s[] = "Hello all around the world!";
    reverse_words(s, strlen(s));
    printf("%s\n", s);
}
