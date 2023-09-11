#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create(int val = 0, Node* l = NULL, Node* r = NULL) {
    Node* newnode = new Node;
    newnode->data = val;
    newnode->left = l;
    newnode->right = r;
    return newnode;
}

void preorder(Node* root){
    if(root != NULL){
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(Node* root){
    if(root != NULL){
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}
void postorder(Node* root){
    if(root != NULL){
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}
void levelorder(Node* root){
    queue<Node*> q;
    q.push(root);

    while(q.size()){
        Node* top = q.front(); q.pop();
        cout << top->data << " ";

        if(top->left){q.push(top->left);}
        if(top->right){q.push(top->right);}
    }
}
void levelorderwithnewline(Node* root){
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while(q.size()){
        Node *topnode = q.front(); q.pop();
        if(topnode == NULL){
            cout << endl;
            if(q.size()){q.push(NULL);}
        }
        else{
            cout << topnode->data << " ";
            if(topnode->left){q.push(topnode->left);}
            if(topnode->right){q.push(topnode->right);}
        }
    }
}

Node* insertion(Node* root, int val) {
    if (root == NULL) {
        return create(val);
    }
    
    if (val > root->data) {
        root->right = insertion(root->right, val);
    } 
    else if (val < root->data) {
        root->left = insertion(root->left, val);
    }
    else{
        root->left = insertion(root->left, val);
    }
    return root;
}

Node *searchRecur(Node *root, int val){
    if(root == NULL){return NULL;}

    if(root->data == val){return root;}

    if(root->data > val){
        return searchRecur(root->left,val);
    }
    else{
        return searchRecur(root->right,val);
    }
}
Node *searchIter(Node *root, int val){
    Node *temp = root;
    while(temp != NULL){
        if(temp->data == val){return temp;}
        else if(temp->data > val){temp = temp->left;}
        else{temp = temp->right;}
    }
    return NULL;
}

Node *greatestElement(Node *root){
    Node *temp = root;
    while (temp->right != NULL)
        temp = temp->right;
     
    return temp;
}
Node *leastElement(Node *root){
    Node *temp = root;
    while (temp->left != NULL)
        temp = temp->left;
     
    return temp;
}
Node *predecessor(Node *root){
    return greatestElement(root->left);
}
Node *successor(Node *root){
    return leastElement(root->right);
}

Node *deletion(Node *root, int val){
    if(root == NULL){return root;}
    
    if(root->data == val){
        if(root->left == NULL && root->right == NULL) {// 0 child 
            delete root;
            return NULL;
        }
        else if(root->left != NULL && root->right != NULL){ // 2 child
            Node *pred = predecessor(root);
            root->data = pred->data;
            root->left = deletion(root->left,pred->data);
            return root;
        }
        else {// 1 child 
            Node *temp;
            if(root->left){temp = root->left;}
            else{temp = root->right;}

            delete root;
            return temp;
        }
    }

    else if (val > root->data) {
        root->right = deletion(root->right, val);
        return root;
    } 
    else {
        root->left = deletion(root->left, val);
        return root;
    } 
}

bool validateBST(Node *root, long long rangeStart, long long rangeEnd){
    if(root == NULL){return true;}
        
    if(root->data > rangeStart && root->data < rangeEnd){
        bool leftans = validateBST(root->left, rangeStart, root->data);
        bool rightans = validateBST(root->right,root->data, rangeEnd);
        return leftans & rightans;
    }
    else{return false;}
}
bool isValidBST(Node* root) {
    return validateBST(root,LLONG_MIN,LLONG_MAX);
}

int kthSmallest(Node* root, int k) {
    if (root == NULL) {return -1;}

    Node* curr = root;
    int ans = -1;

    while (curr) {
        if (curr->left == NULL) {
            k--;
            if (k == 0) {ans = curr->data;}
            curr = curr->right;
        } 
        else {
            Node* pred = curr->left;
            while (pred->right != NULL && pred->right != curr) {
                pred = pred->right;
            }

            if (pred->right == NULL) {
                pred->right = curr;
                curr = curr->left;
            } 
            else {
                pred->right = NULL;
                k--;
                if (k == 0) {ans = curr->data;}
                curr = curr->right;
            }
        }
    }
    return ans;
}
int kthLargest(Node* root, int k) {
    if (root == NULL) {return -1;}

    Node* curr = root;
    int ans = -1;
    while(curr){
        if(curr->right == NULL){
            k--;
            if (k == 0) {ans = curr->data;}
            curr = curr->left;
        }
        else{
            Node *pred = curr->right;
            while(pred->left != NULL && pred->left != curr){
                pred = pred->left;
            }

            if(pred->left == NULL){
                pred->left = curr;
                curr = curr->right;
            }
            else{
                pred->left = NULL;
                k--;
                if (k == 0) {ans = curr->data;}
                curr = curr->left;
            }
        }
    }
    return ans;
}

Node *floorTree(Node* root, int key){
    Node *temp = root;
    Node *floor = NULL;
    while(temp != NULL){
        if(key <= temp->data){
            temp = temp->left;
        }
        else{
            floor = temp;
            temp = temp->right;
        }
    }
    return floor;
}

Node *ceilTree(Node* root, int key){
    Node *temp = root;
    Node *ceil = NULL;
    while(temp != NULL){
        if(key >= temp->data){
            temp = temp->right;
        }
        else{
            ceil = temp;
            temp = temp->left;
        }
    }
    return ceil;
}

Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        if(p->data > root->data && q->data > root->data){
            return lowestCommonAncestor(root->right, p, q);
        }
        else if(p->data < root->data && q->data < root->data){
            return lowestCommonAncestor(root->left, p, q);
        }
        else{
            return root;
        }
    }

// Class system for 'right' iterator
stack<Node *> snext;
void pushInNextStack(Node* root) {
    while(root != NULL){
        snext.push(root);
        root = root->left;
    }
}
int right() {
    Node *topnode = snext.top(); snext.pop();
    pushInNextStack(topnode->right);
    return topnode->data;
}
bool hasNext() {
    return !snext.empty();
}
// Class system for 'prev' iterator
stack<Node *> sprev;
void pushInPrevStack(Node* root) {
    while(root != NULL){
        sprev.push(root);
        root = root->right;
    }
}
int prev() {
    Node *topnode = sprev.top(); sprev.pop();
    pushInPrevStack(topnode->left);
    return topnode->data;
}
bool hasPrev() {
    return !sprev.empty();
}  
// Two Sum in BST
bool findTarget(Node* root, int target) {
    pushInNextStack(root);
    pushInPrevStack(root);
    
    int i = right();
    int j = prev();
    while(hasNext() && hasPrev()){
        if (i >= j) {return false;}
        
        int sum = i + j;
        if(sum == target){
            return true;
        }
        else if(sum < target){
            i = right();
        }
        else if(sum > target){
            j = prev();
        }
    }
    return false;
}

Node* firstMistake = NULL, *secondMistake = NULL, *pre;
void inorderForFixing(Node* root) {
	if(root == NULL) {return;}

	inorderForFixing(root->left);
    if(firstMistake == NULL && root->data < pre->data){firstMistake = pre;}
	if(firstMistake != NULL && root->data < pre->data){secondMistake = root;}
	pre = root;

	inorderForFixing(root->right);
}
void recoverTree(Node* root) {
	pre = create(INT_MIN);
	inorderForFixing(root);
	swap(firstMistake->data, secondMistake->data);
}

void inorder(Node* curr, Node*& prev){
    if (curr == NULL){return;}
    
    inorder(curr->left, prev);
    prev->left = NULL;
    prev->right = curr;
    prev = curr;
    inorder(curr->right, prev);
}
Node* flatteninorder(Node* parent){
    Node* dummy = create(-1);
    Node* prev = dummy;
 
    inorder(parent, prev);
 
    prev->left = NULL;
    prev->right = NULL;
    Node* ret = dummy->right;
 
    delete dummy;
    return ret;
}

void postorder(Node* curr, Node*& prev){
	if (curr == NULL) {return;}
	postorder(curr->left, prev);
	postorder(curr->right, prev);
	prev->left = NULL;
	prev->right = curr;
	prev = curr;
}
Node* flattenpostorder(Node* parent){
	Node* dummy = new Node(-1);

	Node* prev = dummy;

	postorder(parent, prev);

	prev->left = NULL;
	prev->right = NULL;
	Node* ret = dummy->right;

	delete dummy;
	return ret;
}

void inorder(Node *root, vector<Node *> &in){
    if(root == NULL){return ;}
    
    inorder(root->left,in);
    in.push_back(root);
    inorder(root->right,in);
}
Node *builderHelp(int s, int e, vector<Node *> &in){
    if(s > e){return NULL;}
    
    int m = (s+e)/2;
    Node *root = in[m];
    root->left = builderHelp(s, m-1, in);
    root->right = builderHelp(m+1, e, in);
    return root;
}
Node* buildBalancedTree(Node* root){
	vector<Node *> in;
	inorder(root,in);
	int n = in.size();
	root = builderHelp(0, n-1, in);
	return root;
}


void createPostOrder(vector<int> &pre,int n,int minval,int maxval, int& preIndex, vector<int> &post){
	if (preIndex == n){return ;}

	if (pre[preIndex] < minval || pre[preIndex] > maxval) {return ;}

	int val = pre[preIndex];
	preIndex++;
	createPostOrder(pre, n, minval, val, preIndex, post);
	createPostOrder(pre, n, val, maxval, preIndex, post);
    post.push_back(val);
}
vector<int> preToPost(vector<int> pre, int n){
	int preIndex = 0;
    vector<int> post;
    createPostOrder(pre, n, INT_MIN, INT_MAX, preIndex, post);
	return post;
}

void createPreOrder(vector<int> &post, int n, int minval, int maxval, int& postIndex, vector<int> &pre){
	if (postIndex < 0) {return;}

	if (post[postIndex] < minval || post[postIndex] > maxval) {return;}

	int val = post[postIndex];
	postIndex--;

	createPreOrder(post, n, val, maxval, postIndex, pre);
	createPreOrder(post, n, minval, val, postIndex, pre);
	pre.push_back(val);
}
vector<int> postToPre(vector<int> post, int n){
	int postIndex = n - 1;
    vector<int> pre;
	createPreOrder(post, n, INT_MIN, INT_MAX, postIndex,pre);
	reverse(pre.begin(),pre.end());
	return pre;
}


Node *makeTreeFromPre(vector<int> &pre,int n,int minval,int maxval, int& preIndex){
	if (preIndex == n){return NULL;}

	if (pre[preIndex] <= minval || pre[preIndex] >= maxval) {return NULL;}

	int val = pre[preIndex];
	Node *root = create(val);
    preIndex++;
    
	root->left = makeTreeFromPre(pre, n, minval, val, preIndex);
	root->right = makeTreeFromPre(pre, n, val, maxval, preIndex);
    return root;
}
Node *makeTreeFromPost(vector<int> &post, int n, int minval, int maxval, int& postIndex){
	if (postIndex < 0) {return NULL;}

	if (post[postIndex] <= minval || post[postIndex] >= maxval) {return NULL;}
    
    int val = post[postIndex];
	Node *root = create(val);
	postIndex--;
    
    root->right = makeTreeFromPost(post, n, val, maxval, postIndex);
	root->left = makeTreeFromPost(post, n, minval, val, postIndex);
	return root;
}

// SortedList => Balanced BST
// Naive approach
Node *builderHelp(int s, int e, unordered_map<int,Node *> &mp){
    if(s > e){return NULL;}
    
    int m = (s+e)/2;
    Node *root = mp[m];
    root->left = builderHelp(s, m-1, mp);
    root->right = builderHelp(m+1, e, mp);
    return root;
}
Node* sortedListToBST(Node* head) {
    unordered_map<int,Node *> mp;
    Node *temp = head;
    int i = 0;
    while(temp){
        mp[i++] = temp;
        temp = temp->right;
    }
    int n = i;
    Node *root = builderHelp(0, n-1, mp);
	return root;
}
// Optimized approach
Node* sortedListToBST(Node* head) {
    if(head == NULL){return NULL;}
    if(head->right == NULL){return create(head->data);}
        
    //Find mid and make it root
    Node* slow = head;
    Node* fast = head;
    Node* slow_prev = NULL;
    while(fast && fast->right) {
        slow_prev = slow;
        slow = slow->right;
        fast = fast->right->right;
    }
        
    Node* root = create(slow->data); //Make root
    slow_prev->right = NULL; //We only want left half of linked list for left subtree
        
    root->left  = sortedListToBST(head);       //Make left subtree
    root->right = sortedListToBST(slow->right); //Make right subtree
        
    return root; //return root   
}

// Naive Approach :- 
//      1. Convert Trees to vectors of inorder traversal
//      2. Merge the two sorted arrays 
//      3. Convert final merged array to Balanced BST
vector<Node *> mergeSortedVectors(vector<Node *>& vec1, vector<Node *>& vec2) {
    vector<Node *> mergedVector;
    int i = 0; 
    int j = 0; 

    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i]->data < vec2[j]->data) {
            mergedVector.push_back(vec1[i]);
            i++;
        } else {
            mergedVector.push_back(vec2[j]);
            j++;
        }
    }

    while (i < vec1.size()) {
        mergedVector.push_back(vec1[i]);
        i++;
    }

    while (j < vec2.size()) {
        mergedVector.push_back(vec2[j]);
        j++;
    }

    return mergedVector;
}
void inorder(Node *root, vector<Node *> &in){
    if(root == NULL){return ;}
    
    inorder(root->left,in);
    in.push_back(root);
    inorder(root->right,in);
}
Node *builderHelp(int s, int e, vector<Node *> &in){
    if(s > e){return NULL;}
    
    int m = (s+e)/2;
    Node *root = in[m];
    root->left = builderHelp(s, m-1, in);
    root->right = builderHelp(m+1, e, in);
    return root;
}
Node *mergeBSTs(Node *root1, Node *root2){
    vector<Node *> tree1, tree2;
    inorder(root1,tree1);
    inorder(root2,tree2);
    vector<Node *> treemerged = mergeSortedVectors(tree1, tree2);
    int n = treemerged.size();
	Node *root = builderHelp(0, n-1, treemerged);
    return root;
}
// Space Optimised Approach :- 
//      1. Convert Trees to Linked Lists of inorder traversal (In place)
//      2. Merge the two sorted linked lists 
//      3. Convert final merged linked lists to Balanced BST
// Since Linked Lists are used so space will be optimized



typedef struct Info{
    int mx, mn, sz;
    bool isBst;
} Info;        
Info checking(Node *root, int &mxsize){
    if(root == NULL){
        return {INT_MIN,INT_MAX,0,true};
    }
            
    Info leftans = checking(root->left,mxsize);
    Info rightans = checking(root->right,mxsize);
            
    Info ans;
    ans.mn = min(root->data,leftans.mn);
    ans.mx = max(root->data,rightans.mx);
    ans.sz = 1+leftans.sz+rightans.sz;
    if((leftans.isBst) && (rightans.isBst) && (root->data > leftans.mx) && (root->data < rightans.mn)){ans.isBst = 1;}
    else{ans.isBst = 0;}
            
    if(ans.isBst){mxsize = max(mxsize,ans.sz);}
           
    return ans;
}      
int largestBst(Node *root){
    int maxsize = INT_MIN;
    checking(root,maxsize);
    return maxsize;
}

int main() {
    Node* root = NULL;
    int data;
    cin >> data;
    while (data != -1) {
        root = insertion(root, data);
        cin >> data;
    }
    
}