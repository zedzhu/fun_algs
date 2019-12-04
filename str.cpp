#include <cstdio>
#include <cstring>
#include <cstddef>
#include <iostream>

void reverse(char* begin, char* end)
{
    while (begin < end)
    {
        char c = *begin;
        *begin = *end;
        *end = c;
        begin++;
        end--;
    }
}

//保留最后一个标点符号在原始位置。
char * reverse_sentence(char* s)
{
    if (!s) return NULL;
    char* begin = s;
    char* end = s + strlen(s) - 1;
    char* myend = end;
    reverse(begin, myend - 1);
    begin = end = s;
    while (begin < myend)
    {
        if (*begin == ' ')
        {
            begin++;
            end++;
            continue;
        }

        if (*end == ' ' || end == myend)
        {
            reverse(begin, end-1);
            begin = end;
        }
        else
        {
            end++;
        }
    }
}

//去除首尾空格，中间2个及以上空格合并成1个。
char * reverse_sentence_remove_spaces(char* s)
{
    if (!s) return NULL;
    char* end = s + strlen(s) - 1;
    char* p = s;
    char* last = s;
    while (*p != '\0' && *p == ' ')
        p++; //skip leading spaces
    char* begin = p;
    while (*p != '\0')
    {
        while (*p != '\0' && *p != ' ')
            p++; //find word end
        reverse(begin, p-1); //reverse the word
        memmove(last, begin, p-begin); //move the word backward to remove spaces between words, considering overlap
        //strncpy(last, begin, p-begin); //unsafe for overlapping
        last += (p-begin);
        while (*p != '\0' && *p == ' ')
            p++; //find next word start
        begin = p;
        if (*p == '\0') break;
        *last++ = ' '; //add only one space after an word
    }
    reverse(s, last-1);
    *last = '\0'; //add end mark for c-string
}


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
    printf("reverse_words:%s\n", s);
    char s2[] = "Hello all around the world Again!";
    reverse_sentence(s2);
    printf("reverse_sentence:%s\n", s2);

    char s3[] = "  Hello   all around the world    Again!  ";
    reverse_sentence_remove_spaces(s3);
    printf("reverse_sentence_remove_spaces:%s\n", s3);

}
