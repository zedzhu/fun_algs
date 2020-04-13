#include <cstdio>
#include <cstring>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * 输入一个字符串，输出出该字符串中字符的所有排列。
 */
void calcPermRecursive(char* s, int from, int to, vector<string>& out) {
    if (from == to) {
        //找到一个排列
        out.push_back(s);
        return;
    }
    for (int i = from; i <= to; i++) {
        std::swap(s[i], s[from]);
        calcPermRecursive(s, from+1, to, out);
        std::swap(s[i], s[from]);
    }
}
void calcAllPermutation(const string& input, vector<string>& out) {
    if (input.empty()) return;
    if (input.size() == 1) {
        out.push_back(input);
        return;
    }
    char* chArr = new char[input.size()+1];
    strcpy(chArr, input.c_str());
    //Or: strcpy(chArr, &input[0]);
    //Or: input.copy(chArr, input.size()); chArr[input.size()] = '\0';
    //Or: std::copy(input.begin(), input.end(), chArr); chArr[input.size()] = '\0';
    calcPermRecursive(chArr, 0, input.size()-1, out);
    delete[] chArr;
}

void reverse(char* begin, char* end) {
    while (begin < end) {
        std::swap(*begin, *end);
        begin++;
        end--;
    }
}
//采用基于字典序的next permutation下一个排列算法
bool nextPerm(char* s, int len) {
    if (len <= 1) return false;
    for (int i = len - 1; i > 0; i--) {
        if (s[i-1] < s[i]) {
            //1. 找到排列中最后（最右）一个升序的首位位置i
            //2. 找到第i位右边[i,n-1]最后一个比s[i-1]大的位置j
            int j = len - 1;
            while (s[i-1] >= s[j]) j--;
            //3. 交换s[i-1]、s[j]
            std::swap(s[i-1], s[j]);
            //sort works as well
            //4. 把第i位到最后的部分翻转
            reverse(s+i, s+len-1);
            return true;
        }
        //edge case: d c b a
        if (i == 1) {
            //reverse(s, s+len-1); //如果希望接龙，又回到第一个全升序序列
            return false;
        }
    }
}
void calcAllPermutation2(const string& input, vector<string>& out) {
    if (input.empty()) return;
    if (input.size() == 1) {
        out.push_back(input);
        return;
    }
    char* chArr = new char[input.size()+1];
    strcpy(chArr, input.c_str());
    std::sort(chArr, chArr+input.size());
    out.push_back(chArr); //放入第一个全升序的序列，然后一直调用nextPerm方法
    while (nextPerm(chArr, input.size())) {
        out.push_back(chArr);
    }
    delete[] chArr;
}
