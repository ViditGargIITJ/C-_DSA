#include<iostream>
using namespace std;
#include<string>
class node{
    public:
    int data;
    int lh;
    int rh;
    node* left;
    node* right;
    node(int val){
        data = val;
        lh = 0;rh = 0;
        left = right = NULL;
    }
};
class AVL{
    public:
    node* head;
    AVL(){
        head = NULL;
    }
    private:
    node* balance(node* head,int x){
        node* temp = head;node* n2 = NULL;node* n3 = NULL;node* newhead = NULL;
        // right
        if(x>head->data){
            n2 = head->right; temp = n2;
            //RR rotation
            if(x>n2->data){
                n3 = n2->right;
                newhead = n2;
                head->right = newhead->left;
                head->rh = newhead->lh;
                newhead->left = head;
                newhead->lh = 1 + max(head->rh,head->lh);
                return newhead;
            }
            //RL rotation
            else{
                n3 = n2->left;
                newhead = n3;
                head->right = newhead->left;
                head->rh = newhead->lh;
                n2->left = newhead->right;
                n2->lh = newhead->rh;
                newhead->left = head;
                newhead->right = n2;
                newhead->lh = max(head->lh,head->rh);
                newhead->rh = max(n2->lh,n2->rh);
                return newhead;
            }
        }
        //left
        else{
            n2 = head->left; temp = n2;
            //LR rotation
            if(x>n2->data){
                n3 = n2->right;
                newhead = n3;
                head->left = newhead->right;
                head->lh = newhead->rh;
                n2->right = newhead->left;
                n2->rh = newhead->lh;
                newhead->left = n2;
                newhead->right = head;
                newhead->rh = max(head->lh,head->rh);
                newhead->lh = max(n2->lh,n2->rh); 
                return newhead;
            }
            //LL rotation
            else{
                n3 = n2->left;
                newhead = n2;
                head->left = newhead->right;
                head->lh = newhead->rh;
                newhead->right = head;
                newhead->rh = 1 + max(head->lh,head->rh);
                return newhead;
            }
        }
    }
    node* ins(node* head,int d){
        if(head==NULL)return new node(d);
        if(d>head->data){
            head->right = ins(head->right,d);
            head->rh = 1 + max(head->right->lh,head->right->rh);
        }else{
            head->left = ins(head->left,d);
            head->lh = 1 + max(head->left->lh,head->left->rh);
        }

        if(abs(head->lh-head->rh)>1){
            // cout<<"for balancing"<<endl;
            head = balance(head,d);
        }
        return head;
    }
    node* remove(node* head,int x){
        if(head->data==x && head -> right==NULL){
            return head->left;
        } 
        if(head->data==x){
            node* minnode = mini(head->right);
            int minnum = minnode->data;
            minnode->data = head->data;
            head->data = minnum;
            head->right = remove(head->right,x);
            if(head->right == NULL) head->rh = 0; 
            head->rh = 1 + max(head->right->lh,head->right->rh);
        }else if(head->data>x){
            head->left = remove(head->left,x);
            if(head->left==NULL)head->lh = 0;
            else head->lh = 1 + max(head->left->lh,head->left->rh);
        }else{
            head->right = remove(head->right,x);
            if(head->right==NULL) head->rh = 0;
            else head->rh = 1 + max(head->right->lh,head->right->rh);
        }
        if(abs(head->lh-head->rh)>1){
            // cout<<"for balancing"<<endl;
            head = balance(head,x);
        }
        return head;
    }
    node* mini(node* head){
        node* it = head;
        while(it->left!=NULL) it = it->left;
        return it;
    }
    void pre(node* head){
        if(head==NULL)return ;
        cout<<head->data<<" ";
        pre(head->left);
        pre(head->right);
    }
    public:
    bool find(int x){
        node* it = this->head;
        while(it!=NULL){
            if(it->data ==x) return true;
            else if(it->data>x) it = it->left;
            else it = it->right;
        }
        return false;
    }
    void push(int x){
        if(find(x))return ;
        this->head = ins(this->head,x);
    }
    void del(int x){
        if(!find(x)) return ;
        this->head = remove(this->head, x);
    }
    void print(){
        pre(this->head);
    }
};

int main(){
    
    // int x;cin>>x;
    AVL* t1 = new AVL;
    while(true){
        string n;
        getline(cin,n);
        int x = n[0] - '0';
        if(x==4) break;
        else if(x==1){
            // cout<<"in 1"<<endl;
            // cout<<n<<endl;
            int j = 2;
            while(j<n.length()){
                int x = 0;
                while(j<n.length() && n[j]!=' '){
                    x = (x*10) + (n[j]-'0'); 
                    j++;
                }
                // cout<<j<<" "<<x<<endl;
                t1->push(x);
                j++;
            }
        }
        else if(x ==3){
            t1->print();
            cout<<endl;
            // cout<<"in 3"<<endl;
        } 
        else{
            // cout<<"in 2"<<endl;
            int j = 2;int x = 0;
            while(j<n.length()){
                x = (x*10) + (n[j]-'0');
                j++;
            }
            // cout<<x<<endl;
            t1->del(x);
        }
    }
}
