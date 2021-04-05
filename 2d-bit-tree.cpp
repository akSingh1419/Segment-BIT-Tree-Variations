//  Link: https://www.lintcode.com/problem/range-sum-query-2d-mutable/
//  Similarly can be extended to any number of dimensions
//  Space Complexity: O(n*m)
//  Time Complexity: 
//     1. Point Update O(logn*logm)
//     2. Range Query O(logn*logm)

class TwoDimensionBit {
public:
    vector<vector<int>> bit;
    int n,m;
    TwoDimensionBit(int n,int m): n(n), m(m) {
        bit=vector<vector<int>>(n+1,vector<int>(m+1));
    }

    void update(int x,int y,int val) {
        int i=x,j;
        for(i;i<=n;i+=i&(-i)) {
            int j=y;
            for(j;j<=m;j+=j&(-j)) {
                bit[i][j]+=val;
            }
        }
    }

    int get(int x,int y) {
        int i=x,j,sum=0;
        for(;i>0;i-=i&(-i)) {
            j=y;
            for(;j>0;j-=j&(-j)) {
                sum+=bit[i][j];
            }
        }
        return sum;
    }

    int query(int x1,int y1,int x2,int y2) {
        return get(x2,y2)-get(x1-1,y2)-get(x2,y1-1)+get(x1-1,y1-1);
    }
};


class NumMatrix {
public:
    TwoDimensionBit* bit;
    NumMatrix(vector<vector<int>> matrix) {
        int n=matrix.size(),m=matrix[0].size();
        bit=new TwoDimensionBit(n,m);
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                bit->update(i+1,j+1,matrix[i][j]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        int old=bit->query(row+1,col+1,row+1,col+1);
        bit->update(row+1,col+1,val-old);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return bit->query(row1+1,col1+1,row2+1,col2+1);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */
