#include <vector>

using namespace std;

//Algorithm 1:时间效率为O(n*n*n)  
int MaxSubsequenceSum1(const int A[],int N)  
{  
    int ThisSum=0 ,MaxSum=0,i,j,k;  
    for(i=0;i<N;i++)  
        for(j=i;j<N;j++)  
        {  
            ThisSum=0;  
            for(k=i;k<j;k++)  
                ThisSum+=A[k];  
              
            if(ThisSum>MaxSum)  
                MaxSum=ThisSum;  
        }  
        return MaxSum;  
}  
  
//Algorithm 2:时间效率为O(n*n)  
int MaxSubsequenceSum2(const int A[],int N)  
{  
    int ThisSum=0,MaxSum=0,i,j,k;  
    for(i=0;i<N;i++)  
    {  
        ThisSum=0;  
        for(j=i;j<N;j++)  
        {  
            ThisSum+=A[j];  
            if(ThisSum>MaxSum)  
                MaxSum=ThisSum;  
        }  
    }  
    return MaxSum;  
}  
  
//Algorithm 4:时间效率为O(n)  
//dp思想
int MaxSubArraySum(const int A[], int N) {
    int thisSum = 0, maxSum = A[0];  
    for (int j = 0; j < N; j++) {  
        thisSum += A[j];
        if (thisSum > maxSum)
            maxSum = thisSum;
        if (thisSum < 0)
            thisSum = 0;
    }
    return maxSum;
}
