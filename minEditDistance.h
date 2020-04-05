/*
 * http://blog.unieagle.net/2012/09/19/leetcode%E9%A2%98%E7%9B%AE%EF%BC%9Aedit-distance%EF%BC%8C%E5%AD%97%E7%AC%A6%E4%B8%B2%E4%B9%8B%E9%97%B4%E7%9A%84%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB%EF%BC%8C%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/
 */

int minDistance(string word1, string word2) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > dists(word1.size() + 1, vector<int>(word2.size() + 1, 0));
    for(int i = 1; i <= word1.size(); ++i) {
        //by adding chars in sub-word1 to sub-word2 with zero length
        dists[i][0] = i;
    }
    for(int j = 1; j <= word2.size(); ++j) {
        dists[0][j] = j;
    }
    for(int i = 1; i <= word1.size(); ++i) {
        for(int j = 1; j <= word2.size(); ++j) {
            if(word1[i-1] == word2[j-1]) {
                dists[i][j] = dists[i-1][j-1];
            } else {
                //Substitution of word1[i] for word2[j]: dists[i-1][j-1] + 1
                int replacedist = dists[i-1][j-1] + 1;
                //delete word1[i]
                int adddist = dists[i-1][j] + 1;
                //insert word2[j]
                int deldist = dists[i][j-1] + 1;

                int mindist = replacedist;
                if(mindist>adddist) mindist = adddist;
                if(mindist>deldist) mindist = deldist;
                dists[i][j] = mindist;
            }
        }
    }
    return dists[word1.size()][word2.size()];
}

