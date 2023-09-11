#include <bits/stdc++.h>
using namespace std;

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}Node;

Node* create(int val = 0, Node* l = NULL, Node* r = NULL){
    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->data = val;
    newnode->left = l;
    newnode->right = r;
    return newnode;
}

Node* buildTree(){
    int val; cin >> val;
    if(val == -1){
        return NULL;
    }
    Node* root = create(val);

    root->left = buildTree();
    root->right = buildTree();

    return root;
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

vector<int> reverseLevelOrder(Node *root){
    queue<Node*> q;
    q.push(root);
    stack<int> S;
    while(q.size()){
        Node* top = q.front(); q.pop();
        S.push(top->data);
        
        if(top->right){q.push(top->right);}
        if(top->left){q.push(top->left);}
    }
    
    vector<int> ans;
    while(S.size()){
        int node = S.top(); S.pop();
        ans.push_back(node);
    }
    return ans;
}

void diagonalView(Node *root){
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    while(q.size()){
        Node *frontnode = q.front(); q.pop();
        if(frontnode == NULL){
            cout << endl;
            if(q.size()){q.push(NULL);}
        }
        else{
            while(frontnode){
                if(frontnode->left){q.push(frontnode->left);}
                cout << frontnode->data << " "; 
                frontnode = frontnode->right;
            }
        }
    }

    // BASIC CODE 
    // queue<Node *> q;
    // q.push(root);
    // while(q.size()){
    //     Node *frontnode = q.front(); q.pop();
    //     while(frontnode){
    //         if(frontnode->left){q.push(frontnode->left);}
    //         cout << frontnode->data << " ";
    //         frontnode = frontnode->right;
    //     }
    // }
}

// TODO : Learn iterative approach to preorder, postorder, inorder & reverse level order
void preorderiter(Node* root){
    if(root == NULL){return ;}

    stack<Node*> s;
    s.push(root);

    while(s.size()){
        Node* top = s.top(); s.pop();

        cout << top->data << " ";
        if(top->right){s.push(top->right);}
        if(top->left){s.push(top->left);}
    }
}
void inorderiter(Node* root){
    Node* node = root;
    stack<Node*> s;
    while(1){
        if(node != NULL){
            s.push(node);
            node = node->left;
        }
        else{
            if(s.empty()){break;}
            node = s.top(); s.pop();
            cout << node->data << " ";
            node = node->right;
        }
    }
}
void postorderiter(Node* root){
    if(root == NULL){return ;}

    stack<Node*> s1;
    stack<Node*> s2;
    s1.push(root);

    while(s1.size()){
        Node* top = s1.top(); s1.pop();
        s2.push(top);
        
        if(top->left){s1.push(top->left);}
        if(top->right){s1.push(top->right);}
    }
    while(s2.size()){
        cout << s2.top()->data << " "; s2.pop();
    }
}

int heightoftree(Node *root){
    if(root == NULL){return 0;}
    return 1+max(heightoftree(root->right),heightoftree(root->left));
}

int diameter(Node *root){
    if(root == NULL){return 0;}
    return max({diameter(root->left),diameter(root->right),heightoftree(root->right)+heightoftree(root->left)+1});
}

// pair.first : diameter & pair.second : height
pair<int,int> diameterfast(Node *root){
    if(root == NULL){return {0,0};}

    pair<int,int> left = diameterfast(root->left);
    pair<int,int> right = diameterfast(root->right);

    pair<int,int> ans = {max({left.first,right.first,1+left.second+right.second}),1+max(left.second,right.second)};
    return ans;
}

// Function to convert a binary tree into its mirror tree.
void mirror(Node* node) {
    if(node == NULL){return ;}
        
    mirror(node->left);
    mirror(node->right);
        
    Node *temp = node->left;
    node->left = node->right;
    node->right = temp;
}

pair<bool,int> balanceheight(Node *root){
    if(root == NULL){return {true,0};}
        
    pair<bool,int> ansleft = balanceheight(root->left);
    pair<bool,int> ansright = balanceheight(root->right);
        
    bool ansbalance = (ansleft.first)&(ansright.first)&(abs(ansleft.second-ansright.second)<=1);
    int ansheight = 1 + max(ansleft.second,ansright.second);
    pair<bool,int> ans = {ansbalance,ansheight};
    return ans;
}
bool isBalanced(Node *root){
    return balanceheight(root).first;
}

bool isIdentical(Node *r1, Node *r2){
    if(r1 == NULL && r2 == NULL){return true;}
    else if (r1 == NULL && r2 != NULL){return false;}
    else if (r1 != NULL && r2 == NULL){return false;}
        
    if(r1->data == r2->data){
        return isIdentical(r1->left,r2->left)&isIdentical(r1->right,r2->right);
    }
    else{return false;}
}

bool solver(Node* root1, Node* root2){
    if(root1 == NULL && root2 == NULL){return true;}
    else if(root1 == NULL && root2 != NULL){return false;}
    else if(root1 != NULL && root2 == NULL){return false;}
        
    if(root1->data == root2->data){
        return solver(root1->right,root2->left)&&solver(root1->left,root2->right);
    }
    else{return false;}
}
bool isSymmetric(Node* root){
    if(root == NULL){return true;}
    else{return solver(root->left,root->right);}
}

pair<int,bool> sumbool(Node *root){
    if(root == NULL){return {0,true};}
    if(root->left == NULL && root->right == NULL){return {root->data,true};}
        
    pair<int,bool> ansleft = sumbool(root->left);
    pair<int,bool> ansright = sumbool(root->right);
    int ansint = ansleft.first + ansright.first + root->data;
    bool ansbool = (ansleft.second)&(ansright.second)&(ansint==2*root->data);
    return {ansint,ansbool};
}    
bool isSumTree(Node* root){
    return sumbool(root).second;
}

vector <int> zigZagTraversal(Node* root){
    vector<int> ans;
    queue<Node *> q;
    q.push(root);
    bool flag = 0;
    while(q.size()){
        int levelSize = q.size();
        vector<int> currlvl;

        for (int i = 0; i < levelSize; i++) {
            Node* frontnode = q.front(); q.pop();
            currlvl.push_back(frontnode->data);
            if (frontnode->left) { q.push(frontnode->left); }
            if (frontnode->right) { q.push(frontnode->right); }
        }

        if(flag){
            reverse(currlvl.begin(),currlvl.end());
        }
        for(int val : currlvl){
            ans.push_back(val);
        }
        flag = !flag;
    }
    return ans;
}

void leafs(Node *root, vector<int> &leafnodes){
    if(root != NULL){
        leafs(root->left,leafnodes);
        if(root->right == NULL && root->left == NULL){leafnodes.push_back(root->data);}
         leafs(root->right,leafnodes);
    }
}
void leftsideview(Node *root, vector<int> &leftside){
    if(root == NULL || (root->left == NULL && root->right == NULL)){return ;}
    
    leftside.push_back(root->data);
    
    if(root->left){leftsideview(root->left,leftside);}
    else{leftsideview(root->right,leftside);}
}
void rightsideview(Node *root, vector<int> &rightside){
    if(root == NULL || (root->left == NULL && root->right == NULL)){return ;}
    
    if(root->right){rightsideview(root->right,rightside);}
    else{rightsideview(root->left,rightside);}
    
    rightside.push_back(root->data);
}
vector <int> boundary(Node *root){
    vector<int> ans;
    ans.push_back(root->data);
        
    vector<int> leftside;
    leftsideview(root->left,ans);
        
    vector<int> leaves;
    leafs(root->left,ans);
    leafs(root->right,ans);
        
    vector<int> rightside;
    rightsideview(root->right,ans);
        
    return ans;
}

vector<int> verticalOrder(Node *root){
    map<int,map<int,vector<int>>> mp;
        
    queue<pair<int,pair<int,Node *>>> q;
    q.push({0,{0,root}});
    while(q.size()){
        pair<int,pair<int,Node *>> p = q.front(); q.pop();
        int lvlnode = p.second.first;
        int vertheight = p.first;
        Node *node = p.second.second;
            
        mp[vertheight][lvlnode].push_back(node->data);
            
        if(node->left){q.push({vertheight-1,{lvlnode+1,node->left}});}
        if(node->right){q.push({vertheight+1,{lvlnode+1,node->right}});}
    }
        
    vector<int> ans;
    for (auto i : mp){
        for(auto j : i.second){
            for(int u : j.second){ans.push_back(u);}
        }
    }
    return ans;
}

vector<int> topView(Node *root){
    // {vertheight,nodedata} for mp
    map<int,int> mp;
    // {vertheight,node} for q
    queue<pair<int,Node *>> q;
    q.push({0,root});
    while(q.size()){
        pair<int,Node *> qfront = q.front(); q.pop();
        int nodevertheight = qfront.first;
        Node *node = qfront.second;
            
        if(mp[nodevertheight] == NULL){mp[nodevertheight] = node->data;}
            
        if(node->left){q.push({nodevertheight-1,node->left});}
        if(node->right){q.push({nodevertheight+1,node->right});}
    }
    vector<int> ans;
    for(auto i : mp){
        ans.push_back(i.second);
    }
    return ans;
}

vector <int> bottomView(Node *root) {
    // {vertheight,nodedata} for mp
    map<int,int> mp;
    // {vertheight,node} for q
    queue<pair<int,Node *>> q;
    q.push({0,root});
    while(q.size()){
        pair<int,Node *> qfront = q.front(); q.pop();
        int nodevertheight = qfront.first;
        Node *node = qfront.second;
                
        mp[nodevertheight] = node->data;
                
        if(node->left){q.push({nodevertheight-1,node->left});}
        if(node->right){q.push({nodevertheight+1,node->right});}
    }
    vector<int> ans;
    for(auto i : mp){
        ans.push_back(i.second);
    }
    return ans;
}

// Recursive wala
void leftsideview(Node *root, vector<int> &leftside, int lvl){
    if(root == NULL){return ;}
    
    if(lvl == leftside.size()){leftside.push_back(root->data);}
    
    if(root->left){leftsideview(root->left,leftside,lvl+1);}
    if(root->right){leftsideview(root->right,leftside,lvl+1);}
}
vector<int> leftView(Node *root){
   vector<int> leftside;
   leftsideview(root,leftside,0);
   return leftside;
}

// Iterative wala
void helperLeftView(Node* root, vector<int> &leftview){
	queue<Node*> q;
	q.push(root);

	while (q.size()){	
		int n = q.size();
		
		for(int i = 0; i < n; i++){
			Node* temp = q.front(); q.pop();
				
			if (i == 0){leftview.push_back(temp->data);}
			
			if (temp->left != NULL){q.push(temp->left);}
            if (temp->right != NULL){q.push(temp->right);}
		}
	}
}	
vector<int> leftView(Node *root){
   vector<int> leftside;
   helperLeftView(root,leftside);
   return leftside;
}

// Recursive wala
void rightsideview(Node *root, vector<int> &rightside, int lvl){
    if(root == NULL){return ;}
    
    if(lvl == rightside.size()){rightside.push_back(root->data);}
    
    if(root->right){rightsideview(root->right,rightside,lvl+1);}
    if(root->left){rightsideview(root->left,rightside,lvl+1);}
}
vector<int> rightView(Node *root){
   vector<int> rightside;
   rightsideview(root,rightside,0);
   return rightside;
}

// Iterative wala
void helperRightView(Node* root, vector<int> &rightview){
	queue<Node*> q;
	q.push(root);

	while (q.size()){	
		int n = q.size();
		
		for(int i = 0; i < n; i++){
			Node* temp = q.front(); q.pop();
				
			if (i == 0){rightview.push_back(temp->data);}
			
            if (temp->right != NULL){q.push(temp->right);}
			if (temp->left != NULL){q.push(temp->left);}
		}
	}
}	
vector<int> rightView(Node *root){
   vector<int> rightside;
   helperRightView(root,rightside);
   return rightside;
}

void convertToleftCloned(Node *root){
    if(root == NULL){return ;}
    if(root->right && root->left == NULL){
        Node *leftclone = create(root->data);
        root->left = leftclone;
    }
    
    convertToleftCloned(root->left);
    convertToleftCloned(root->right);

    Node *leftsubtree = root->left;
    Node *rootclone = create(root->data);
    root->left = rootclone;
    rootclone->left = leftsubtree;
}
Node *convertBackFromLeftCloned(Node *root){
    if(root == NULL){return NULL;}
    
    Node *lnormal = convertBackFromLeftCloned(root->left->left);
    Node *rnormal = convertBackFromLeftCloned(root->right);

    root->left = lnormal;
    root->right = rnormal;

    return root;
}

void convertToRightCloned(Node *root){
    if(root == NULL){return ;}
    
    if(root->right && root->left == NULL){
        Node *rightclone = create(root->data);
        root->right = rightclone;
    }

    convertToRightCloned(root->left);
    convertToRightCloned(root->right);

    Node *rightsubtree = root->right;
    Node *rootclone = create(root->data);
    root->right = rootclone;
    rootclone->right = rightsubtree;
}
Node *convertBackFromRightCloned(Node *root){
    if(root == NULL){return NULL;}
    
    Node *lnormal = convertBackFromRightCloned(root->left);
    Node *rnormal = convertBackFromRightCloned(root->right->right);

    root->left = lnormal;
    root->right = rnormal;

    return root;
}

void solver(Node *root, int len, int &maxlen, int sum, int &maxsum){
    if(root == NULL){
        if(len > maxlen || (len == maxlen && sum > maxsum)){
            maxlen = len;
            maxsum = sum;
        }
        return ;
    }
    
    sum += root->data;
    solver(root->left,len+1,maxlen,sum,maxsum);
    solver(root->right,len+1,maxlen,sum,maxsum);
}    
int sumOfLongRootToLeafPath(Node *root){
    int maxsum = INT_MIN;
    int maxlen = 0;
    solver(root,0,maxlen,0,maxsum);
    return maxsum;
}

Node* lca(Node* root ,int n1 ,int n2 ){
    if(root==NULL){return NULL;}
    if(root->data == n1 || root->data == n2){return root;}
    
    Node* ansleft = lca(root->left,n1,n2);
    Node* ansright = lca(root->right,n1,n2);
    if(ansleft != NULL && ansright != NULL){return root;}
    else if(ansleft == NULL && ansright != NULL){return ansright;}
    else if(ansleft != NULL && ansright == NULL){return ansleft;}
    else{return NULL;}
}

bool findPath(Node *root, int target, vector<int> &path) {
    if (root == NULL){return false;}

    path.push_back(root->data);
    if (root->data == target) {return true;}
    if (findPath(root->left, target, path) || findPath(root->right, target, path)) {return true;}
    path.pop_back();
    
    return false;
}
vector<int> printPathToNode(Node *root, int target) {
    vector<int> path;
    findPath(root, target, path);
    return path;
}

Node* solve(Node* root, int &k, int node){
    if(root == NULL){return NULL;}
    if(root->data == node) {return root;}
    
    Node* leftAns = solve(root->left,k,node);
    Node* rightAns = solve(root->right,k,node);
    
    if(leftAns != NULL && rightAns == NULL){
        k--;
        if(k<=0){
            k = INT_MAX;
            return root;
        }
        return leftAns;
    }
    if(leftAns == NULL && rightAns != NULL){
        k--;
        if(k<=0){
            k = INT_MAX;
            return root;
        }
        return rightAns;
    }
    if(leftAns == NULL && rightAns == NULL){return NULL;}
}
int kthAncestor(Node *root, int k, int node){
    Node* ans = solve(root,k,node);
    if(ans==NULL || ans->data==node){return -1;}
    else{return ans->data;}
}

pair<int,int> solve(Node *root){
    if(root == NULL){return {0,0};}
    
    pair<int,int> ansleft = solve(root->left);
    pair<int,int> ansright = solve(root->right);
    
    pair<int,int> ans;
    ans.first = root->data + ansright.second + ansleft.second;
    ans.second = max(ansright.first,ansright.second) + max(ansleft.first,ansleft.second);
    return ans;
}
int getMaxSum(Node *root){
    pair<int,int> res = solve(root);
    return max(res.first,res.second);
}

// Target Sum II
// Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum.
vector<vector<int>> ans; 
void dfs(Node* root, vector<int>& path, int remainingSum) {
    if (root == NULL) {return;}
    path.push_back(root->data);
    
    if (root->left == NULL && root->right == NULL && remainingSum == root->data) {ans.push_back(path);}
    
    dfs(root-> left, path, remainingSum - root->data);
    dfs(root-> right, path, remainingSum - root->data);
    
    path.pop_back();
}
vector<vector<int>> pathSum(Node* root, int targetSum) {
    vector<int> path;
    dfs(root, path, targetSum);
    return ans;  
}

// Target Sum III
// Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.
// Naive approach 
void solver(Node *root, int k, vector<int> &path, int &count){
    if(root == NULL){return ;}
    
    path.push_back(root->data);
    
    solver(root->left,k,path,count);
    solver(root->right,k,path,count);
    
    unsigned long long int sum = 0;
    for(int i = path.size()-1 ; i >= 0 ; i--){
        sum += path[i];
        if(sum == k){count++;}
    }
    
    path.pop_back();
}  
int pathSum(Node* root, int targetSum) {
    int ct = 0;
    vector<int> path;
    solver(root,targetSum,path,ct);
    return ct;
}
// Optimized approach
// Uses the principle of `Subarray Sum Equals K`
void solver(Node *root, int sum, int target, unordered_map<int,int> &mp, int &ans){
    sum += root->data;
    if(mp.count(sum-target) == 1){ans += mp[sum-target];}
    mp[sum]++;
    if(root->left){helper(root->left,sum,target,mp,ans);}
    if(root->right){helper(root->right,sum,target,mp,ans);}
    mp[sum]--;
    return ;
}
int pathSum(Node *root,int targetSum){
    int ans = 0;
    unordered_map<int,int> mp;
    mp[0] = 1;
    solver(root,0,targetSum,mp,ans);
    return ans;
}


// Target Sum IV
/*
If the depth of a tree is smaller than 5, then this tree can be represented by an array of three-digit integers. For each integer in this array:
The hundreds digit represents the depth `d` of this node where 1 <= d <= 4.
The tens digit represents the position `p` of this node in the level it belongs to where 1 <= p <= 8. The position is the same as that in a full binary tree.
The units digit represents the value `v` of this node where 0 <= v <= 9.
*/
// Given an array of ascending three-digit integers nums representing a binary tree with a depth smaller than 5, return the sum of all paths from the root towards the leaves.
void dfs(int node, int currsum, unordered_map<int, int> &mp, int &anssum) {
    if (mp.count(node) == 0) {return;}
    currsum += mp[node];
    int d = node / 10, p = node % 10;
    int left = (d+1)*10 + (2*p-1);
    int right = (d+1)*10 + (2*p);
    if ((mp.count(left) == 0) && (mp.count(right) == 0)) {
        anssum += currsum;
        return;
    }
    dfs(left, currsum, mp, anssum);
    dfs(right, currsum, mp, anssum);
}
int pathSum(vector<int>& nums) {
    int ans = 0;
    unordered_map<int, int> mp;
    for (int num : nums) {mp[num / 10] = num % 10;}
    dfs(11, 0, mp, ans);
    return ans;
}

// TODO : Construct Tree from Inorder & Preorder
int findElementinOrder(int in[], int start, int end, int element) {
    for(int i = start; i <= end; i++) {
        if(in[i] == element) {
            return i;
        }
    }
    return -1;
}
Node *tree(int in[], int pre[], int n, int inorderStart, int inorderEnd, int &index){
    if(index >= n || inorderStart > inorderEnd){return NULL;}
    
    int element = pre[index];
    index++;
    Node *root = new Node(element);
    int inorderpos = findElementinOrder(in, inorderStart, inorderEnd, element);
    root->left = tree(in,pre,n,inorderStart,inorderpos-1,index);
    root->right = tree(in,pre,n,inorderpos+1,inorderEnd,index);
    return root;
}
Node* constructFromInPre(int in[],int pre[], int n){
    int index = 0;
    Node *root = tree(in,pre,n,0,n-1,index);
    return root;
}

// TODO : Construct Tree from Postorder & Inorder
int findElementinOrder(int in[], int start, int end, int element) {
    for(int i = start; i <= end; i++) {
        if(in[i] == element) {
            return i;
        }
    }
    return -1;
}
Node *tree(int in[], int post[], int n, int inorderStart, int inorderEnd, int &index){
    if(index < 0 || inorderStart > inorderEnd){return NULL;}
    
    int element = post[index];
    index--;
    Node *root = new Node(element);
    int inorderpos = findElementinOrder(in, inorderStart, inorderEnd, element);
    root->right = tree(in,post,n,inorderpos+1,inorderEnd,index);
    root->left = tree(in,post,n,inorderStart,inorderpos-1,index);
    return root;
}
Node *constructFromInPost(int in[], int post[], int n) {
    int index = n-1;
    Node *root = tree(in,post,n,0,n-1,index);
    return root;
}

// TODO : Construct Tree from Postorder & Preorder
int findElementpostOrder(int post[], int start, int end, int element) {
    for (int i = start; i <= end; i++) {
        if (post[i] == element) {return i;}
    }
    return -1;
}   
Node* tree(int pre[], int post[], int n, int postorderStart, int postorderEnd, int &index){
    if (index >= n || postorderStart > postorderEnd) {return NULL;}

    int element = pre[index];
    Node* root = new Node(element);
    index++;

    if (index >= n || postorderStart > postorderEnd) {return root;}

    int postorderpos = findElementpostOrder(post,postorderStart,postorderEnd,pre[index]);
    
    if (postorderpos != -1) {
        root->left = tree(pre,post,n,postorderStart,postorderpos,index);
        root->right = tree(pre,post,n,postorderpos+1,postorderEnd-1,index);
    }
    return root;
}
Node* constructFromPrePost(int pre[], int post[], int n) {
    int index = 0;
    return tree(pre,post,n,0,n-1,index);
}

// Using level-order traversal
string serialize(Node* root) {
    string s;
    if(!root){return s;}
    queue <Node*> q;
    q.push(root);
    while(q.size()){
        Node *topnode = q.front(); q.pop();
        
        if(topnode == NULL){
            s.append("#,");
        }
        else{
            s.append(to_string(topnode->data)+','); 
            q.push(topnode->left);
            q.push(topnode->right);
        }
    }
    return s;
}
Node* deserialize(string data) {
    if(data.empty()){return NULL;}
    
    stringstream stream(data);
    string str;
	getline(stream, str, ',');
    Node *root = create(stoi(str));
	queue <Node *> q;
	q.push(root);
	while (q.size()) {
        Node *front = q.front(); q.pop();
        string left, right;
		getline(stream, left, ',');
		getline(stream, right, ',');
		
		if (left == "#") {
            front->left = NULL;
		} else {
            front->left = create(stoi(left));
			q.push(front->left);
		}
		
		if (right == "#") {
            front->right = NULL;
		} else {
            front->right = create(stoi(right));
			q.push(front->right);
		}
	}
	
	return root;
}

// Using pre-order
string serialize(Node* root) {
    if(!root) {return "#,";}
    return to_string(root->data)+","+serialize(root->left)+serialize(root->right);
}
Node* deserialize_helper(queue<string> &q) {
    string s = q.front(); q.pop();
    if(s == "#"){return NULL;}
    Node* root = create(stoi(s));
    root->left = deserialize_helper(q);
    root->right = deserialize_helper(q);
    return root;
}
Node* deserialize(string data) {
    queue<string> q;
    
    string s;
    for(int i = 0; i < data.size() ; i++){
        if(data[i]==','){
            q.push(s);
            s = "";
        } else{
            s += data[i];
        }
    }
    if(s.size() != 0){q.push(s);}
    
    return deserialize_helper(q);
}

int minTime(Node* root, int target) {
    unordered_map<Node *,Node *> parents;
    Node *tar = NULL;
    queue<Node *> q;
    q.push(root);
    while(q.size()){
        Node *curr = q.front(); q.pop();
        if(curr->data == target){tar = curr;}
        if(curr->left){
            parents[curr->left] = curr;
            q.push(curr->left);
        }
        if(curr->right){
            parents[curr->right] = curr;
            q.push(curr->right);
        }
    }
    parents[root] = NULL;
    
    unordered_map<Node *,bool> vis;
    vis[tar] = true;
    q.push(tar);
    int time = 0;
    while (q.size()) {
        bool flag = 0;
        int size = q.size();
        for (int i = 0; i < size ; i++) {
            Node *curr = q.front(); q.pop();
            if (curr->left != NULL && vis[curr->left] == false) {
                q.push(curr->left);
                vis[curr->left] = true;
                flag = 1;
            }
            if (curr->right != NULL && vis[curr->right] == false) {
                q.push(curr->right);
                vis[curr->right] = true;
                flag = 1;
            }
            if (parents[curr] != NULL && vis[parents[curr]] == false) {
                q.push(parents[curr]);
                vis[parents[curr]] = true;
                flag = 1;
            }
        }
        if(flag){time++;}
    }
    return time;
}

vector<int> distanceK(Node* root, Node* tar, int k) {
    vector<int> ans;
    unordered_map<Node *, Node *> parents;
    queue<Node *> q;
    q.push(root);
    while(q.size()){
        Node *curr = q.front(); q.pop();
        if(curr->left){
            parents[curr->left] = curr;
            q.push(curr->left);
        }
        if(curr->right){
            parents[curr->right] = curr;
            q.push(curr->right);
        }
    }
    parents[root] = NULL;
    
    unordered_map<Node *,bool> vis;
    vis[tar] = true;
    q.push(tar);
    int time = 0;
    while (q.size()) {
        bool flag = 0;
        int size = q.size();
        for (int i = 0; i < size ; i++) {
            Node *curr = q.front(); q.pop();
            if(time == k){ans.push_back(curr->data);}
            if (curr->left != NULL && vis[curr->left] == false) {
                q.push(curr->left);
                vis[curr->left] = true;
                flag = 1;
            }
            if (curr->right != NULL && vis[curr->right] == false) {
                q.push(curr->right);
                vis[curr->right] = true;
                flag = 1;
            }
            if (parents[curr] != NULL && vis[parents[curr]] == false) {
                q.push(parents[curr]);
                vis[parents[curr]] = true;
                flag = 1;
            }
        }
        if(flag){time++;}
    }
    return ans;
}

// Morris Traversal : Inorder
void morrisinorder(Node *root){
    Node *curr = root;
    while(curr){
        if(curr->left == NULL){
            cout << curr->data << " ";
            curr = curr->right;
        }
        else{
            Node *pred = curr->left;
            while(pred->right != NULL && pred->right != curr){
                pred = pred->right;
            }

            if(pred->right == NULL){
                pred->right = curr;
                curr = curr->left;
            }
            else{
                pred->right = NULL;
                cout << curr->data << " ";
                curr = curr->right;
            }
        }
    }
}

// Morris Traversal : Preorder
void morrispreorder(Node *root){
    Node *curr = root;
    while(curr){
        if(curr->left == NULL){
            cout << curr->data << " ";
            curr = curr->right;
        }
        else{
            Node *pred = curr->left;
            while(pred->right != NULL && pred->right != curr){
                pred = pred->right;
            }

            if(pred->right == NULL){
                cout << curr->data << " ";
                pred->right = curr;
                curr = curr->left;
            }
            else{
                pred->right = NULL;
                curr = curr->right;
            }
        }
    }
}

// Morris Traversal : Postorder
void morrispostorder(Node* root){
    vector<int> res;
    Node* curr = root;
    while (curr) {
        if (curr->right == NULL) {
            res.push_back(curr->data);
            curr = curr->left;
        }
        else {
            Node* pred = curr->right;
            while (pred->left != NULL && pred->left != curr) {
                pred = pred->left;
            }
            
            if (pred->left == NULL) {
                res.push_back(curr->data);
                pred->left = curr;
                curr = curr->right;
            }
            else {
                pred->left = NULL;
                curr = curr->left;
            }
        }
    }
    
    reverse(res.begin(), res.end());
    for(int i : res){cout << i << " ";}
}

void flattenRecursive(Node *root){
    if(root == NULL || root->left == NULL && root->right == NULL){return ;}
        
    if(root->left){
        flattenRecursive(root->left);
        
        Node *temp = root->right;
        root->right = root->left;
        root->left = NULL;
        
        Node *t = root->right;
        while(t->right){
            t = t->right;
        }
            
        t->right = temp;
    }
    
    flattenRecursive(root->right);
}
void flattenMorris(Node *root){
    Node *curr = root;
    while(curr){
        if(curr->left){
            Node *pred = curr->left;
            while(pred->right){
                pred = pred->right;
            }
            pred->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL; // Making the left nodes to NULL
        }
        curr = curr->right;
    }
        
    // Making left ptrs equal to NULL
    // curr = root;
    // while(curr){
    //     curr->left = NULL;
    //     curr = curr->right;
    // }
    }

// Complete Binary tree => MinHeap
void traversal(Node* root, vector<int>& arr){
	if (root == NULL){return;}
    
	traversal(root->left, arr);
	arr.push_back(root->data);
	traversal(root->right, arr);
}
void BTToMinHeap(Node* root, vector<int> arr, int &ind){
	if (root == NULL){return;}
    
    root->data = arr[ind];
    ind++;
	
	BTToMinHeap(root->left, arr, ind);
	BTToMinHeap(root->right, arr, ind);
}
void convertToMinHeap(Node* root){
	vector<int> arr;
	int i = 0;

	traversal(root, arr);
    // this is for in case the (in-order) traversal is not sorted
    sort(arr.begin(),arr.end()); 
	BTToMinHeap(root, arr, i);
}

// check if binary tree is min-heap or not
// first check if complete binary tree by checking indexing of each node 
// if any index goes out of total-nodes then it means left subtree was missing somewhere  
// and then after that check heap property
int countNodes(Node *root){
    if(root == NULL){return 0;}
    
    return 1 + countNodes(root->left) + countNodes(root->right);
}
bool isCBT(Node *root, int ind, int totalnodes){
    if(root == NULL){return true;}
    if(ind >= totalnodes){return false;}
    else{
        return isCBT(root->left,2*ind+1,totalnodes) && isCBT(root->right,2*ind+2,totalnodes);
    }
}
bool hasHeapProp(Node *root){
    if(root->left == NULL && root->right == NULL){return true;}
    if(root->right ==  NULL){return root->data <= root->left->data;}
    
    bool leftans = hasHeapProp(root->left);
    bool rightans = hasHeapProp(root->right);
    if(leftans && rightans && (root->data <= root->left->data) && (root->data <= root->right->data)){
        return true;
    }
    else{return false;}
}
bool isHeap(Node* root) {
    int totcount = countNodes(root);
    if(isCBT(root,0,totcount) && hasHeapProp(root)){
        return true;
    } 
    else{return false;}
}

// TODO : (Leetcode 1932 - Hard) Merge BSTs to Create Single BST (https://leetcode.com/problems/merge-bsts-to-create-single-bst/)
// TODO : Flip Binary Tree towards the right direction that is clockwise (https://www.geeksforgeeks.org/flip-binary-tree/?ref=lbp)
// TODO : Check if given inorder and preorder traversals are valid for any Binary Tree without building the tree
// TODO : Print Postorder traversal from given Inorder and Preorder traversals
// TODO : Construct a tree from Inorder and Level order traversals
// TODO : Minimum swap required to convert binary tree to binary search tree
// TODO : Succinct Encoding of Binary Tree
// TODO : Construct Binary Tree from String with bracket representation
// TODO : Convert a Binary Tree into Doubly Linked List in spiral fashion
// TODO : Convert Ternary Expression to a Binary Tree
// TODO : Merge Two Binary Trees by doing Node Sum

int main(){  
    // 1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
    Node* root = buildTree();
    // preorder(root); 
    // cout << endl;
    // inorder(root);
    // cout << endl;
    // postorder(root);
    // cout << endl;
    // levelorder(root);
    // cout << endl;
    // levelorderwithnewline(root);
    // cout << endl;
    // preorderiter(root); 
    // cout << endl;
    // inorderiter(root);
    // cout << endl;
    // postorderiter(root);
    // cout << endl;
}