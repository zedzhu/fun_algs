class Solution {
public:
    //20 ms, 6.7 MB
    bool isMatch(const char *s, const char *p) {
        for (char c=*p; c != '\0'; ++s, c=*p) {
            if (p[1] != '*') ++p;
            else if (isMatch(s, p+2)) return true;
            if (!(c == *s || (c == '.' && *s != '\0'))) return false;
        }
        return *s == '\0';
    }

    //372 ms, 15.2 MB
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        bool firstMatch = (!s.empty() && (s[0]==p[0] || (p[0]=='.')));
        if (p.size() >= 2 && p[1] == '*') {
            return isMatch(s, p.substr(2)) || 
                firstMatch && isMatch(s.substr(1), p);
        } else {
            return firstMatch && isMatch(s.substr(1), p.substr(1));
        }
    }

    //24 ms, 6.7 MB
    bool isMatch(const char *s, const char *p) {
        if (*p == '\0') return *s == '\0';
        bool firstMatch = (*s !='\0' && (*s == *p || *p == '.'));
        if (p[1] == '*') {
            return isMatch(s, p+2) ||
                firstMatch && isMatch(s+1, p);
        } else {
            return firstMatch && isMatch(s+1, p+1);
        }
    }

    bool isMatch(string s, string p) {

        if (p.empty()) return s.empty();
        bool firstMatch = (!s.empty() && (s[0]==p[0] || (p[0]=='.')));
        if (p.size() >= 2 && p[1] == '*') {
            return isMatch(s, p.substr(2)) || 
                firstMatch && isMatch(s.substr(1), p);
        } else {
            return firstMatch && isMatch(s.substr(1), p.substr(1));            
        }
    }

};
