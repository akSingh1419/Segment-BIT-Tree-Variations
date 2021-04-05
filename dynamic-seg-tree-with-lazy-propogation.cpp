// Link to Question: https://leetcode.com/problems/my-calendar-iii/submissions/
// Time Complexity: O(logn), Space Complexity: O(qlog(1e9)) where q is number of queries in this case)

class Node{
public:
    Node* left,* right;
    int val, lazy;
    Node(): left(NULL), right(NULL), val(0), lazy(0) {}
    
    void extend() {
        if(left==NULL) {
            left=new Node();
            right=new Node();
        }
    }
};

class Segtree {
public:
    Node* root;
    int n;
    
    Segtree(int n): n(n) {
        root = new Node();
    }
    
    void up(int l,int r, int val) {
        update(root,1,n,l,r,val);
    }
    
    int get(int l,int r) {
        return query(root,1,n,l,r);
    }
    
    void update(Node* p,int s,int e,int l,int r,int val) {
        if(p->lazy) {
            p->val+=p->lazy;
            if(s!=e) { 
                p->extend();
                p->left->lazy+=p->lazy;
                p->right->lazy+=p->lazy;
            }
            p->lazy=0;
        }
        
        if(s>r || e<l) return;
        
        if(s>=l && e<=r) {
            p->val+=val;
            if(s!=e) {
                p->extend();
                p->left->lazy+=val;
                p->right->lazy+=val;
            }
            return;
        }
        
        int m=(s+e)/2;
        p->extend();
        update(p->left,s,m,l,r,val);
        update(p->right,m+1,e,l,r,val);
        p->val=max(p->left->val, p->right->val);
    }
    
    int query(Node* p,int s,int e,int l, int r) {
        if(p->lazy) {
            if(s!=e) {
                p->val=p->val+p->lazy;
                if(s!=e) { 
                    p->extend();
                    p->left->lazy+=p->lazy;
                    p->right->lazy+=p->lazy;
                }
                p->lazy=0;
            }
        }
        
        if(s>r || e<l) return 0;
        
        if(s>=l && e<=r) {
            return p->val;
        }
        
        int m=(s+e)/2;
        p->extend();
        return max(query(p->left,s,m,l,r),query(p->right,m+1,e,l,r));
    }
};

class MyCalendarThree {
public:
    int n;
    Segtree* sg;
    MyCalendarThree() {
        n=1e9;
        sg=new Segtree(n);
    }
    
    int book(int start, int end) {
        sg->up(start,end-1,1);
        return sg->get(1,n);
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */
