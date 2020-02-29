#include <vector>

using namespace std;
#define MAX_NUM 2
void MatrixMultiply(int M[][MAX_NUM],int N[][MAX_NUM],int rs[][MAX_NUM],int m,int n,int p)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < p; j++)
        {
            rs[i][j] = 0;//初始化第行第j列的元素
            for(int k = 0;k < n;k++)
            {
                rs[i][j] += (M[i][k] * N[k][j]);//第i行与第j列相乘求和
            }
        }
    }
}

struct Triple
{
    int i; //非0元素行标
    int j; //非0元素列标
    float value; //非0元素值
};

//矩阵稀疏表示法
struct SparseMartrix 
{
    vector<Triple> elems; //非0元素Triple数组
    int rows; //行数
    int cols; //列数
    vector<int> row_start_pos; //每行第一个非0元素的位置，也就是截止到上一行结尾时非0元素的个数。
};

//将稀疏矩阵的二维数组表示形式转换为三元组稀疏矩阵表示
void transform(const vector<vector<float> >& matrix, SparseMartrix& out_sparse_matrix) {
    if (matrix.empty()) 
        return;
    out_sparse_matrix.rows = matrix.size();
    out_sparse_matrix.cols = matrix[0].size();
    out_sparse_matrix.row_start_pos.resize(out_sparse_matrix.rows);
    for (size_t i = 0; i < matrix.size(); i++) {
        out_sparse_matrix.row_start_pos[i] = out_sparse_matrix.elems.size();
        const vector<float> & row = matrix[i];
        for (size_t j = 0; j < row.size(); j++) {
            if (row[j] == 0)
                continue;
            Triple tr;
            tr.i = i; //行号
            tr.j = j; //列号
            tr.value = row[j];
            out_sparse_matrix.elems.push_back(tr);
        }
    }
}

/*
对A中的每个非零元素即(i,k,A[i][k])，找到B中所有相应的元素(k,j,B[k][j])相乘，
为此需在A中找到第k行的所有非零元，而row_start_pos[k]就是第k行的起始位置，row_start_pos[k+1]-1就是第k行的终止位置。
另外，由于两个稀疏矩阵相乘的结果矩阵不一定稀疏，所以结果矩阵的表示方式不一定要用稀疏矩阵表示，也可以用二维数组。
矩阵越稀疏，该算法时间复杂度越低，能达到O(A.rows*B.cols)数量级。
*/
void multipySparseMatrix(
    const vector<vector<float> >& matrix_a, const vector<vector<float> >& matrix_b, 
    SparseMartrix& res) {
    SparseMartrix sma, smb;
    transform(matrix_a, sma);
    transform(matrix_b, smb);
    
    res.rows = sma.rows;
    res.cols = smb.cols;
    res.row_start_pos.resize(res.rows, 0); //默认先初始化全为0，后续如果有非0元素则会调整。

    for (int i = 0; i < sma.rows; i++) {
        int next_row_a; //下一行非0元素的开始位置
        if (i < sma.rows) { //非最后一行
            next_row_a = sma.row_start_pos[i+1]; //下一行的开始
        } else {
            next_row_a = sma.elems.size(); //最后一行时下一行的起始位置边界
        }

        vector<float> row_result(smb.cols, 0); //初始化结果行，一共有smb.cols列，对这一行进行叠加计算
        for (int c = sma.row_start_pos[i]; c < next_row_a; c++) {
            int smb_row = sma.elems[c].j; //sma的第c个元素的列标就是要相乘的smb矩阵元素的行号
            int next_row_b;
            if (smb_row < smb.rows) {
                next_row_b = smb.row_start_pos[smb_row+1];
            } else {
                next_row_b = smb.elems.size();
            }

            for (int k = smb.row_start_pos[smb_row]; k < next_row_b; k++) {
                int res_col = smb.elems[k].j;
                row_result[res_col] += sma.elems[c].value * smb.elems[k].value;
            }
        }
        //记录这一行的非零元素起始位置，也就是截止上一行结尾时当前元素的个数。
        res.row_start_pos[i] = res.elems.size();
        for (int col = 0; col < row_result.size(); col++) {
            if (row_result[col] == 0) //0元素不处理
                continue;
            Triple tr;
            tr.i = i; //行号
            tr.j = col; //列号
            tr.value = row_result[col];
            res.elems.push_back(tr);
        }
    }
}
