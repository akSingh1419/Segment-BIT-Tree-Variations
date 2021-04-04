// Question link: https://leetcode.com/problems/range-sum-query-mutable/
// This question doesn't actually require Dynamic Segment Trees 

class Node{
public:
    Node* left,* right;
    int sum;
    Node(): left(NULL), right(NULL), sum(0){}
};

class Segtree {
public:
    Node* root;
    int n;
    
    Segtree(int n): n(n) {
        root = new Node();
    }
    
    void up(int idx,int val) {
        update(root,1,n,idx,val);
    }
    
    int get(int l,int r) {
        return query(root,1,n,l,r);
    }
    
    void update(Node* p,int s,int e,int idx,int val) {
        if(s>idx || e<idx) {
            return;
        }
        if(s==e) {
            p->sum=val;
            return;
        }
        int m=(s+e)/2;
        if(idx<=m) {
            if(p->left==NULL) {
                p->left=new Node();
            }
            update(p->left,s,m,idx,val);
        } else {
            if(p->right==NULL) {
                p->right=new Node();
            }
            update(p->right,m+1,e,idx,val);
        }
        int sum=0;
        if(p->left) sum+=p->left->sum;
        if(p->right) sum+=p->right->sum;
        p->sum=sum;
    }
    
    int query(Node* p,int s,int e,int l, int r) {
        if(p==NULL) return 0;
        if(s>r || e<l) return 0;
        if(s>=l && e<=r) {
            return p->sum;
        }
        int m=(s+e)/2;
        return query(p->left,s,m,l,r)+query(p->right,m+1,e,l,r);
    }
};

class NumArray {
public:
    Segtree* sg;
    int n;
    NumArray(vector<int>& nums) {
        n=nums.size();
        sg=new Segtree(n);
        for(int i=0;i<n;i++) {
            sg->up(i+1,nums[i]);
        }
    }
    
    void update(int index, int val) {
        sg->up(index+1,val);
    }
    
    int sumRange(int left, int right) {
        return sg->get(left+1,right+1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
