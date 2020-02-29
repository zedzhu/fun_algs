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
  
//Algorithm 3:时间效率为O(n*log n)  
//算法3的主要思想：采用二分策略，将序列分成左右两份。  
//那么最长子序列有三种可能出现的情况，即  
//【1】只出现在左部分.  
//【2】只出现在右部分。  
//【3】出现在中间，同时涉及到左右两部分。  
//分情况讨论之。  
static int MaxSubSum(const int A[],int Left,int Right)  
{  
    int MaxLeftSum,MaxRightSum;              //左、右部分最大连续子序列值。对应情况【1】、【2】  
    int MaxLeftBorderSum,MaxRightBorderSum;  //从中间分别到左右两侧的最大连续子序列值，对应case【3】。  
    int LeftBorderSum,RightBorderSum;  
    int Center,i;  
    if(Left == Right)Base Case  
        if(A[Left]>0)  
            return A[Left];  
        else  
            return 0;  
        Center=(Left+Right)/2;  
        MaxLeftSum=MaxSubSum(A,Left,Center);  
        MaxRightSum=MaxSubSum(A,Center+1,Right);  
        MaxLeftBorderSum=0;  
        LeftBorderSum=0;  
        for(i=Center;i>=Left;i--)  
        {  
            LeftBorderSum+=A[i];  
            if(LeftBorderSum>MaxLeftBorderSum)  
                MaxLeftBorderSum=LeftBorderSum;  
        }  
        MaxRightBorderSum=0;  
        RightBorderSum=0;  
        for(i=Center+1;i<=Right;i++)  
        {  
            RightBorderSum+=A[i];  
            if(RightBorderSum>MaxRightBorderSum)  
                MaxRightBorderSum=RightBorderSum;  
        }  
        int max1=MaxLeftSum>MaxRightSum?MaxLeftSum:MaxRightSum;  
        int max2=MaxLeftBorderSum+MaxRightBorderSum;  
        return max1>max2?max1:max2;  
}  
  
//Algorithm 4:时间效率为O(n)  
//同上述第一节中的思路3、和4。  
int MaxSubsequenceSum(const int A[],int N)  
{  
    int thisSum = 0, maxSum = A[0];  
    for(int j=0;j<N;j++)
    {  
        thisSum+=A[j];  
        if (thisSum > maxSum)  
            maxSum = thisSum;  
        if (thisSum<0) 
            thisSum=0;  
    }  
    return maxSum;  
}
