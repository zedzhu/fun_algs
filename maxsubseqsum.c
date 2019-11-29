//Algorithm 1:ʱ��Ч��ΪO(n*n*n)  
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
  
//Algorithm 2:ʱ��Ч��ΪO(n*n)  
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
  
//Algorithm 3:ʱ��Ч��ΪO(n*log n)  
//�㷨3����Ҫ˼�룺���ö��ֲ��ԣ������зֳ��������ݡ�  
//��ô������������ֿ��ܳ��ֵ��������  
//��1��ֻ�������󲿷�.  
//��2��ֻ�������Ҳ��֡�  
//��3���������м䣬ͬʱ�漰�����������֡�  
//���������֮��  
static int MaxSubSum(const int A[],int Left,int Right)  
{  
    int MaxLeftSum,MaxRightSum;              //���Ҳ����������������ֵ����Ӧ�����1������2��  
    int MaxLeftBorderSum,MaxRightBorderSum;  //���м�ֱ�����������������������ֵ����Ӧcase��3����  
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
  
//Algorithm 4:ʱ��Ч��ΪO(n)  
//ͬ������һ���е�˼·3����4��  
int MaxSubsequenceSum(const int A[],int N)  
{  
    int thisSum = A[0], maxSum = 0;  
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
