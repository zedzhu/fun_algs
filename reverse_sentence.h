#include <cstring>
#include <cstdio>
#include <cstddef>
#include <iostream>

using namespace std;

void reverse(char* begin, char* end) {
    while (begin < end) {
        std::swap(*begin, *end);
        begin++;
        end--;
    }
}
/*
 * I am a student. => student. a am I
 * 空格、标点符号啥的什么都不考虑。
 */
char* reverse_sentence(char* s) {
    if (!s) return s;
    char* begin = s;
    char* end = s + strlen(s) - 1;
    reverse(begin, end);
    begin = end = s;
    while (*begin != '\0') {
        if (*begin == ' ') {
            begin++;
            end++;
            continue;
        }
        if (*end == ' ' || *end == '\0') {
            reverse(begin, end-1);
            begin = end;
        }
        else
            end++;
    }
    return s;
}

/*
 * I am a student. => student a am I.
 * 最后标点符号不动。
 */
char* reverse_sentence(char* s) {
    int len;
    //长度为1则表示只有1个标点符号。
    if (!s || (len=strlen(s)) == 1) return s;
    char* begin = s;
    char* end = s + len - 1;
    char* mylast = end - 1; //标点符号前一个字符。
    reverse(begin, mylast);
    begin = end = s;
    while (begin != mylast) {
        if (*begin == ' ') {
            begin++;
            end++;
            continue;
        }
        if (*end == ' ' || end == mylast) {
            reverse(begin, end-1);
            begin = end;
        }
        else
            end++;
    }
    return s;
}

//保留最后一个标点符号在原始位置，并忽略开头空格。
char* reverse_sentence(char* s) {
    if (!s) return NULL;
    char* begin = s;
    char* end = s + strlen(s) - 1;
    reverse(begin, end - 1); //从头到倒数第2个（除去标点符号）先反转；如果要求标点符号也要反转，则是用end。
    char* p = s; //让p指向单词末尾
    while (p < end && *p == ' ') p++;//忽略开头的空格
    begin = p;
    while (p < end) {
        //找到一个单词结尾，如果要求最后标点符号也要反转，则是p<=end。
        while (p < end && *p != ' ') p++;
        reverse(begin, p-1);    //反转这个单词
        while (p < end && *p == ' ') p++;   //找到下一个单词开头
        if (p == end) break;
        begin = p; //begin指针后移到下一个单词开头
    }
    return s;
}

//去除首尾空格，中间2个及以上空格合并成1个。
char* reverse_sentence_remove_spaces(char* s) {
    if (!s) return s;
    char* p = s;
    char* last = s;
    while (*p != '\0' && *p == ' ') p++; //skip leading spaces
    char* begin = p;
    while (*p != '\0') {
        while (*p != '\0' && *p != ' ') p++; //find word end
        reverse(begin, p-1); //reverse the word, p-1 points to the last of the word
        memmove(last, begin, p-begin); //move the word backward to remove spaces between words, considering overlap
        //strncpy(last, begin, p-begin); //unsafe for overlapping
        last += (p-begin);
        while (*p != '\0' && *p == ' ') p++; //find next word start
        if (*p == '\0') break;
        begin = p;
        *last++ = ' '; //add only one space after an word
    }
    reverse(s, last-1); //note that the last pointer now point to ' ' or '\0'
    *last = '\0'; //add end mark for c-string
    return s;
}

//XY => YX, len(Y)=m
//根据(X^TY^T)^T = YX得到3步反转法：1）反转X；2）反转Y；3）整体反转
//Time:O(n), Space:O(1)
char* left_rotate(char* s, int m) {
    int len;
    if (!s || m <= 0 || (len=strlen(s)) < m) return s;
    reverse(s, s+len-m-1);
    reverse(s+len-m, s+len-1);
    reverse(s, s+len-1);
    return s;
}
