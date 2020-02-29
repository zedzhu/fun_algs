class Solution {
public:
    int lengthOfLastWord(const char *s) {
        int len{0};
        for (int beg = 0; *s; ++s)
            if (*s == ' ') beg = 0;
            else len = ++beg;
        return len;
    }

    int lengthOfLastWord2(const char *s) {
        if ( !s ||!*s ) return 0;
        int wordLen=0;
        int beg = 0;
        while (*s++ != '\0') {
            if (*s == ' ')
                beg =0;
            else
                wordLen = ++beg; 
        }
        return wordLen;
    }

    int lengthOfLastWord3(const char *s) {
        if ( !s ||!*s ) return 0;
        int wordLen=0;
        int cnt=0;
        for (;*s!='\0';s++) {
            if (isalpha(*s)){
                cnt++;
            }
            if (!isalpha(*s)){
                if (cnt>0){
                    wordLen = cnt;
                }
                cnt=0;
            }
        }

        return cnt>0 ? cnt : wordLen;
    }

};
