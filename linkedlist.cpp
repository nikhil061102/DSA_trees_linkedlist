#include <bits/stdc++.h>
using namespace std;

typedef struct node{
    int data;
    struct node *next;
} Node;

Node* create(int val = 0, Node* nxt = NULL) {
    Node* newnode = new Node;
    newnode->data = val;
    newnode->next = nxt;
    return newnode;
}

void printList(Node* &head){
    Node *temp = head;
    while(temp){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Insertion in single linked list
Node *insertAtHead(Node* &head, int d){
    Node *node = create(d,head);
    head = node;
    return head;
}
Node *insertAtTail(Node* &head, int d){
    Node *node = create(d);
    Node *temp = head;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = node;
    return head;
}
Node *insertAtPos(Node* &head, int d, int pos){
    if(pos == 1){return insertAtHead(head,d);}

    Node *node = create(d);
    Node *prev = head;
    int i = 1;
    while(i < pos-1){
        prev = prev->next;
        i++;
    }
    Node *prevKaNext = prev->next;

    prev->next = node;
    node->next = prevKaNext;
    return head;
}

// Deletion in single linked list
Node *deleteAtHead(Node* &head){
    Node *temp = head->next;
    free (head);
    return head = temp;
}
Node *deleteAtTail(Node* &head){
    Node *temp = head;
    while(temp->next){
        temp = temp->next;
    }
    delete temp;
}
Node *deleteAtPos(Node* &head, int pos){
    Node *temp = head;
    if(pos == 1){
        head = temp->next;
        delete temp;
        return head;
    }
    Node *tempprev = NULL; 
    while(--x){
        tempprev = temp;
        temp = temp->next;
    }
    tempprev->next = temp->next;
    delete temp;
    return head;
}

// Reverses a linked list and returns new head
Node* reverse(Node *head){
    // Approach 1 (Iterative)
    Node *curr = head;
    Node *prev = NULL;
    while(curr){
        Node *forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
        
    // Approach 2 (Recursive)
    if(head == NULL || head->next == NULL){return head;}
        
    Node *newhead = reverse(head->next);
    Node *headnext = head->next;
    headnext->next = head;
    head->next = NULL;
    return newhead;  
}

// Reverses every k nodes in linked list and returns new head
Node *reverseKGroups(Node *head, int k){
    if (head == NULL || head->next == NULL){return head;}
    
    // Step1 : Reverse first k nodes
    Node *curr = head;
    Node *prev = NULL;
    Node *nxt = NULL;
    int count = 0;
    while(curr != NULL && count < k){
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
        count++;
    }
    // Step2 : Recursive Call
    if(nxt){head->next = reverseKGroups(nxt,k);}
    // Step3 : Return head of reversed list
    return prev;
}

// Checks if a LL is circular or not
bool isCircular(Node *head){
   Node *temp = head;
   while(temp->next != NULL){
       temp = temp->next;
       if(temp == head){return true;}
   }
   return false;
}

// Checks if any loop exists in LL
bool detectLoop(Node* head){
    Node *slow = head;
    Node *fast = head;
    while (slow != NULL && fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){return true;}
    }
    return false;
}

// Removes loop in a LL (if any exists)
Node* detectLoop(Node* head){
    Node* slow = head;
    Node* fast = head;
        
    while(slow != NULL && fast != NULL && fast->next != NULL){
        slow = slow -> next;
        fast = fast -> next->next;
        if(slow == fast){return slow;}
    }
    return NULL;
}
Node* getStartingNodeOfLoop(Node* head){
    Node* intersection = detectLoop(head);
    if(intersection == NULL){return NULL;}
            
    Node* slow = head;
    while(slow != intersection){
        slow = slow->next;
        intersection = intersection->next;
    }
    return slow;
}
void removeLoop(Node* head){
    if(head==NULL){return ;}
    
    Node* startNodeOfLoop= getStartingNodeOfLoop(head);
    if(startNodeOfLoop == NULL){return;}
            
    Node* curr = startNodeOfLoop;
    while(curr->next != startNodeOfLoop){
        curr=curr->next;
    }
    curr->next=NULL;
}

// Remove duplicates from an sorted LL
Node *removeDuplicates(Node *head){
    Node *curr = head;
    while(curr){
        if((curr->next != NULL) && (curr->data == curr->next->data)){
            Node *nextKaNext = curr->next->next; 
            Node *toDelete = curr->next;
            curr->next = nextKaNext;
            delete toDelete;
        }
        else{
            curr =  curr->next;
        }
    }
    return head;
}

// Remove duplicates from an unsorted LL
Node *removeDuplicates( Node *head) {
    unordered_map<int,bool> mp;
    Node *temp = head;
    Node *tempprev = NULL;
    while(temp){
        if(mp.count(temp->data)){
            tempprev->next = temp->next;
            delete temp;
            temp = tempprev->next;
        }
        else{
            mp[temp->data] = true;
            tempprev = temp;
            temp = temp->next;
        }
    }
    return head;
}

// Check if palindrome or not
bool isPalindrome(Node *head){
    Node *slow = head;
    Node *fast = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *end = reverseList(slow);
    Node *start = head;
    while(start && end){
        if(start->data != end->data){return false;}
        start = start->next;
        end = end->next;
    }
    return true;
}

// Add 1 to no. in form of LL
Node* addOne(Node *head) {
    head = reverseList(head);
    Node *temp = head;
    while(temp != NULL) {
        if(temp->next == NULL && temp->data == 9) {
            temp->data = 0;
            temp->next = new Node(1);
            break;
        }
        else if(temp->data == 9) {
            temp->data = 0;
            temp = temp->next;
        }
        else {
            temp->data = temp->data + 1;
            break;
        }
    }
    return head = reverseList(head);
}

// Add two numbers in form of LLs 
Node* addTwoLists(Node* first, Node* second){
    first = reverse(first);
    second = reverse(second);
    Node* res = NULL;
    Node *prev = NULL;
    int carry = 0, sum, digit;
    while (first != NULL || second != NULL) {
        // takes all the data and makes a appropiate node for resultatnt digit
        sum = carry + (first ? first->data : 0) + (second ? second->data : 0);
        carry = sum/10;
        digit = sum % 10;
        
        Node *temp = new Node(digit);
        
        // if res == NULL means we are just beginning result list
        // else we have to join the `temp` node to last node of list 
        if (res == NULL) {res = temp;}
        else {prev->next = temp;}
       
        // update `prev` with last node of list
        prev = temp;
        
        // traverse the first and second list nodes
        if (first){first = first->next;}
        if (second){second = second->next;}
    }
    
    // still carry is left after both list traversal then create a node with only carry and join it to list 
    if (carry > 0){prev->next = new Node(carry);}
    
    return res = reverseList(res);
}

// Subtract two numbers in form of LLs 
int getLength(Node* n){
    int ans = 0;
    while(n){
        ans++;
        n = n->next;
    }
    return ans;
}
Node* reverse(Node *head){
    Node *curr = head;
    Node *prev = NULL;
    while(curr){
        Node *forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}
Node* subtractTwoLists(Node* l1, Node* l2){
    // remove trailing zeros ie. 0->0->2->3 |=> 2->3
    while(l1 && l1->data == 0){l1 = l1->next;}
    while(l2 && l2->data == 0){l2 = l2->next;}
    
    int len1 = getLength(l1);
    int len2 = getLength(l2);
    
    if(len1 < len2){swap(l1,l2);}
    if(len1 == len2){
        Node *t1 = l1;
        Node *t2 = l2;
        while(t1 && t2 && (t1->data == t2->data)){
            t1 = t1->next;
            t2 = t2->next;
            
            if(t1 == NULL){return new Node(0);}
        }
        if(t2->data > t1->data){swap(l1,l2);}
    }
    // now we can easily assume l1 >= l2 for further calculations
    
    l1 = reverse(l1);
    l2 = reverse(l2);
    
    Node* res = NULL;
    Node* t1 = l1;
    Node *t2 = l2;
    while(t1){
        int small = 0;
        if(t2){small = t2->data;}
        
        if(t1->data < small){ //carry le liya 
            t1->next->data = t1->next->data - 1;
            t1->data = t1->data + 10;
        }
        
        Node *n = new Node(t1->data - small);
        n->next = res;
        res = n;
        
        t1 = t1->next;
        if(t2) {t2 = t2->next;}
    }
    
    while(res->next && res->data==0){res = res->next;}
    
    return res;
}

// Fold of a linked list
Node* reverse(Node *head){
    Node *curr = head;
    Node *prev = NULL;
    while(curr){
        Node *forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}
Node *middle(Node *root){
    Node *slow = root, *fast = root->next;
    while (fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
Node* shuffleMerge(struct Node* a, struct Node* b){
    if (a == NULL) {return b;}
    if (b == NULL) {return a;}
 
    Node* recur = shuffleMerge(a->next, b->next);
 
    Node* result = a;           // one node from `a`
    a->next = b;                // one from `b`
    b->next = recur;            // then the `rest`
 
    return result;
}
Node *inPlace(Node *root){
    Node *first = root;
    Node *temp = middle(root);
    Node *second = temp->next;
    temp->next = NULL;
    
    second = reverse(second);
    
    root = shuffleMerge(first,second);
    return root;
}

// Unfold of a linked list
Node* reverse(Node* head) {
	Node* curr = head;
	Node* prev = NULL;
	while (curr) {
		Node* forw = curr->next;
		curr->next = prev;
		prev = curr;
		curr = forw;
	}
	return prev;
}
Node* unfold(Node* head) { 
	Node* temp1 = head;
	Node* temp2 = head->next;
	Node* a = temp1;
	Node* b = temp2;
	while (temp1->next) {
		temp1->next = temp2->next;
		temp1 = temp1->next;
		if (temp1 == NULL) {break;}
		temp2->next = temp1->next;
		temp2 = temp2->next;
	}
	b = reverseList(b);
	Node *temp = a;
	while(temp->next){
	    temp = temp->next;
	}
	temp->next = b;
	return head;
}

// Rearrange a LL such that it is converted to be of the form a < b > c < d > e < f ... 
// Input :  11 15 20 5 10
// Output : 11 20 5 15 10
Node *zigZag(Node* head){
    Node *temp = head;
    bool bit = false;
    while(temp->next){
        if(bit){
            if(temp->data < temp->next->data)  swap(temp->data,temp->next->data);
        }
        else{
            if(temp->data > temp->next->data) swap(temp->data,temp->next->data);
        }
        bit = !bit;
        temp = temp->next;
    }
    return head;
}

/*  
    typedef struct node{
        int data;
        struct node* next;
        struct node* child;
    } Node;

    5 -> 10 -> 19 -> 28
    |     |     |     | 
    7     20    22   35
    |           |     | 
    8          50    40
    |                 | 
    30               45 
            
        `CONVERTED TO` 
    
    5->7->8->10->19->20->22->28->30->35->40->45->50       
*/
Node *mergeTwoLLs(Node *a, Node *b){
    Node *temp = new Node(-1);
    Node *res = temp;
    while(a != NULL && b != NULL){
        if(a->data < b->data){
            temp->bottom = a;
            temp = temp->bottom;
            a = a->bottom;
        } else{
            temp->bottom = b;
            temp = temp->bottom;
            b = b->bottom;
        }
    }
    if(a != NULL){temp->bottom = a;}
    if(b != NULL){temp->bottom = b;}
    
    return res->bottom;
}
Node *flatten(Node *root){
   if(root == NULL || root->next == NULL){return root;}

    root->next = flatten(root->next);
    root = mergeTwoLLs(root, root->next);
    return root;
}

/*  
    typedef struct node{
        int data;
        struct node* next;
        struct node* child;
    } Node;

    10 -> 5 -> 12 -> 7 -> 11
    |                |
    v                v
    4 -> 20 -> 13    17 -> 6
          |     |    |
          v     v    v
          2     16   9 -> 8
                |    |
                v    v
                3    19 -> 15  
            
        `CONVERTED TO` 
    
    10->5->12->7->11->4->20->13->17->6->2->16->9->8->3->19->15             
*/
Node *flattenLL(Node *head){
	Node *tail = head;
	while(tail->next){tail = tail->next;}
	Node *curr = head;
	while(curr != tail){
	    if(curr->child){
	        tail->next = curr->child;
	        Node *temp = curr->child;
	        while(temp->next){temp = temp->next;}
	        tail = temp;
	    }
	    curr = curr->next;
	}
    return head;
}

/*  
    typedef struct node{
        int data;
        struct node* prev;
        struct node* next;
        struct node* child;
    } Node;

    1 = 2 = 3 = 4 = 5 = 6
            ||
            7 = 8 = 9 = 10
                ||
                11 = 12
            
        `CONVERTED TO` 
    
    1 = 2 = 3 = 7 = 8 = 11 = 12 = 9 = 10 = 4 = 5 = 6          
*/
Node* flattenDLL(Node* head) {
    for (Node* temp = head; temp != NULL; temp = temp->next){
		if (temp->child){
			Node* nextptr = temp->next;
			temp->next = temp->child;
			temp->next->prev = temp;
			temp->child = NULL;
			Node* temptraversal = temp->next;
			while (temptraversal->next) {temptraversal = temptraversal->next;}
			temptraversal->next = nextptr;
            if (nextptr) {nextptr->prev = temptraversal;}
		}
	}
	return head;
}

// Pairwise swap elements of a linked list
Node* pairWiseSwap(Node* head){
    if(head == NULL || head->next == NULL){return head;}
    
    Node *curr = head->next->next;
    Node *prev = head;
    head = head->next;
    head->next = prev;
    while(curr && curr->next){
        prev->next = curr->next;
        prev = curr;
        Node *temp = curr->next->next;
        curr->next->next = curr;
        curr = temp;
    }
    prev->next = curr;
    return head;
}

// Clone a linked list with random pointer
Node *copyList(Node *head){
    // Step 1: Create a copy of each node and insert it between the original nodes
    Node *curr = head;
    while(curr){
        Node *temp = curr->next;
        curr->next = new Node(curr->data);
        curr->next->next = temp;
        curr = temp;
    }
    
    // Step 2: Set the 'arb' (arbitrary) pointers for the copied list
    curr = head;
    while(curr){
        if(curr->next && curr->arb){
            curr->next->arb = curr->arb->next;
        }
        curr = (curr->next ? curr->next->next : curr->next);
    }
    
    // Step 3: Separate the original and copied lists
    Node *orig = head;
    Node *copy = head->next;
    Node *temp = copy;
    while(orig){
        orig->next = (orig->next ? orig->next->next : orig->next);
        copy->next = (copy->next ? copy->next->next : copy->next);
        orig = orig->next;
        copy = copy->next;
    }
    return temp;
}

// Intersection Point in Y Shaped Linked Lists
int getLength(Node* head){
    int l = 0;
    while(head != NULL){
        head = head->next;
        l++;
    }
    return l;
}
int intersectPoint(Node* head1, Node* head2){
    int l1 = getLength(head1);
    int l2 = getLength(head2);
    
    while(l1 > l2){
        head1 = head1->next;
        l1--;
    }
    while(l2 > l1){
        head2 = head2->next;
        l2--;
    }

    while(head1 != NULL && head2 != NULL){
        if(head1 == head2){return head1->data;}
        head1 = head1->next;
        head2 = head2->next;
    }
    return -1;
}

// Rearrange LL in a way that all odd position nodes are together and all even positions node are together.
// INPUT :  1 34 64 223 6 23 75 83 13 24
// OUTPUT : 1 64 6 75 13 34 223 23 83 24
void rearrangeEvenOdd(Node *head) {
    Node *odd = head;
    Node *even = head->next;
    Node *tail = even;
   
    while(odd->next && even->next){
        odd->next = even->next;
        odd = odd->next;
       
        even->next = odd->next;
        even = even->next;
    }
   
    odd->next = tail;
}

// Insertion Sort in LL
Node* insertionSort(Node* head){
    Node* res = new Node(-1);
    Node* temp = res;
    Node* curr = head;
    while(curr){
        temp = res;
        while(temp->next and curr->data >= temp->next->data){
            temp = temp->next;
        }
        
        Node* nextNode = temp->next;
        temp->next = curr;
        curr = curr->next;
        temp->next->next = nextNode;
    }
    head = res->next;
    delete res;
    return head;
}

// Merge Sort in LL
Node* findMid(Node* head){
    Node* slow = head;
    Node* fast = head->next;
    
    while(fast != NULL and fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
Node *mergeTwoLists(Node *first, Node *second){
    if(first == NULL){return second;}
    if(second == NULL){return first;}
    
    Node *temp = new Node(INT_MAX);
    Node *res = temp;
    
    while(first != NULL && second != NULL){
        if(first->data < second->data){
            temp->next = first;
            temp = temp->next;
            first = first->next;
        } else{
            temp->next = second;
            temp = temp->next;
            second = second->next;
        }
    }
    
    if(first != NULL){temp->next = first;}
    if(second != NULL){temp->next = second;}
    
    return res->next;
}
Node* mergeSort(Node* head) {
    if(head == NULL or head->next == NULL){return head;}
    
    Node *mid = findMid(head);
    
    Node *left = head;
    Node *right = mid->next;
    mid->next = NULL;
    
    left = mergeSort(left);
    right = mergeSort(right);
    
    Node *result = mergeTwoLists(left,right);
    return result;
}

// Quick Sort in LL
Node* partition(Node* start ,Node* end){
    int pivotdataue = start->data;
    Node* p = start;
    Node* q = start->next;
    while(q != end){
        if (q->data < pivotdataue){
            p = p->next;
            swap(p->data,q->data);
        }
        q = q->next;
    }
    swap(p->data,start->data);
    return p;
}
void helpersort(Node* start ,Node* end){
    if (start != end){
        Node* mid = partition(start,end);
        helpersort(start,mid);
        helpersort(mid->next,end);
    }
}
Node *quickSort(Node *head) {
    helpersort(head,NULL);
    return head;
}

// Segregate even and odd nodes in a Linked List
// INPUT  : 17 15 8 9 2 4 6
// OUTPUT : 8 2 4 6 17 15 9
bool isEven(int num){
    return (num % 2 == 0);  
}
Node *divide(int N, Node *head){
    Node *evenDummy = new Node(-1);
    Node *oddDummy = new Node(-1);
    
    Node *even = evenDummy;
    Node *odd = oddDummy;
    
    Node *temp=head;
    
    while(temp){
        if(isEven(temp->data)){
            even->next = temp;
            even = even->next;
        }
        else{
            odd->next = temp;
            odd = odd->next;
        }
        temp = temp->next;
    }
    
    if(evenDummy->next==NULL){return oddDummy->next;}
    
    
    even->next = oddDummy->next;
    odd->next = NULL;

    head = evenDummy->next;
    
    delete evenDummy;
    delete oddDummy;
    
    return head;
}

// Segregate vowel and consonent nodes in a Linked List
bool isVowel(char c){
    if(c == 'a' || c == 'i' || c == 'e' || c == 'o' || c == 'u'){return 1;}
    else{return 0;}
}
Node* arrangeVowelCons(Node *head){
    Node *evenDummy = new Node(-1);
    Node *oddDummy = new Node(-1);
    
    Node *even = evenDummy;
    Node *odd = oddDummy;
    
    Node *temp=head;
    
    while(temp){
        if(isVowel(temp->data)){
            even->next = temp;
            even = even->next;
        }
        else{
            odd->next = temp;
            odd = odd->next;
        }
        temp = temp->next;
    }
    
    if(evenDummy->next==NULL){return oddDummy->next;}
    
    even->next = oddDummy->next;
    odd->next = NULL;

    head = evenDummy->next;
    
    delete evenDummy;
    delete oddDummy;
    
    return head;
}

// Merge K sorted linked lists
Node *mergeKLists(Node *arr[], int K) {
    vector<Node *> vec;
    for (int i = 0; i < K; i++) {
        Node *curr = arr[i];
        while (curr) {
            vec.push_back(curr);
            curr = curr->next;
        }
    }

    sort(vec.begin(), vec.end(), [](Node *a, Node *b) {
        return a->data < b->data;
    });
    
    Node *head = new Node(0);  
    Node *temp = head;

    for (Node *nodeptr : vec) {
        temp->next = nodeptr;
        temp = temp->next;
    }

    temp = head->next;
    delete head;

    return temp; 
}

// Merge two sorted linked lists
Node* sortedMerge(Node* head1, Node* head2)  {  
    Node *first, *second;
    if (head1->data <= head2->data) {
        first = head1;
        second = head2;
    } else {
        first = head2;
        second = head1;
    }
    Node *temp1 = first;
    Node *next1 = first->next;
    Node *temp2 = second;
    if(temp1->next == NULL){
        temp1->next = temp2;
    }
    while (next1 != NULL && temp2 != NULL) {
        if (temp1->data <= temp2->data && temp2->data <= next1->data) {
            Node *next2 = temp2->next;
            temp2->next = next1;
            temp1->next = temp2;
            temp1 = temp2;
            temp2 = next2;
        } else {
            temp1 = next1;
            next1 = next1->next;
            if(next1 == NULL){
                temp1->next = temp2;
                return first;
            }
        }
    }
    return first;
}  

// Split the LL into two smaller lists and stored in `a` & `b`
Node *a = NULL;
Node *b = NULL;
void alternatingSplitList(Node* head) {
    Node* temp1 = head;
    Node* temp2 = head->next;
    a = temp1;
    b = temp2;
    while(temp1->next){
        temp1->next = temp2->next;
        temp1 = temp1->next;
        if(temp1 == NULL){break;}
        temp2->next = temp1->next;
        temp2 = temp2->next;
    }
}

/* Construct a 2D linked list representation of matrix
    typedef struct node{
        int data;
        struct node *right, *down;
    } Node;

Input : 2D matrix 
        1 2 3
        4 5 6
        7 8 9

Output :
        1 -> 2 -> 3 -> NULL
        |    |    |
        v    v    v
        4 -> 5 -> 6 -> NULL
        |    |    |
        v    v    v
        7 -> 8 -> 9 -> NULL
        |    |    |
        v    v    v
        NULL NULL NULL

*/
#define MAX 20
Node* constructLinkedMatrix(int mat[MAX][MAX], int n){
    Node *head = new Node(INT_MAX);
    Node *temp = head;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            temp->right = new Node(mat[i][j]);
            temp = temp->right;
        }
    }
    
    temp = head->right;
    Node *temp2 = head->right;
    for(int i = 0 ; i < n ; i++){temp2 = temp2->right;}
    while(temp2){
        temp->down = temp2;
        temp2 = temp2->right;
        temp = temp->right;
    }
    
    temp = head;
    head = head->right;
    delete temp;
    
    int count = 0; 
    temp = head;
    temp2 = head; 
    while (temp2) {
        if (count % n == 0 && count != 0) {
            temp->right = NULL;
        }
        count++;
        temp = temp2;
        temp2 = temp2->right;
    }
    
    return head;
}

// Length of longest palindrome in LL
int count(Node *first, Node *second){
    Node *a = first;
    Node *b = second;

    int cnt = 0;
    while(a && b){
        if(a->data == b->data){
            a = a->next;
            b = b->next;
            cnt++;
        } else{
            break;
        }
    }
    return cnt;
}
int maxPalindrome(Node *head){
    Node *curr = head;
    Node *prev = NULL;
    int ans = 0;
    while(curr){
        Node *nxt = curr->next;
        curr->next = prev;
        
        ans = max({ ans , 2*count(curr,nxt) , 2*count(prev,nxt)+1 });
        // 2*count(curr,nxt)    => For even palindrome case
        // 2*count(curr,prev)+1 => For odd palindrome case
        
        prev = curr;
        curr = nxt;
    }
    return ans;
}

/* Prime List
Replace all the values of the nodes with the nearest prime number. If more than one prime number exists at an equal distance, choose the smallest one.
*/
bool isPrime(int n){
    if (n <= 1)  {return false;}
    if (n <= 3)  {return true;}
   
    if (n%2 == 0 || n%3 == 0) {return false;}
   
    for (int i=5; i*i<=n; i=i+6){
        if (n%i == 0 || n%(i+2) == 0){return false;}    
    }
    return true;
}
vector<int> generatePrimes(int N) {
    vector<int> primes;
    
    if (N >= 2) primes.push_back(2);
    if (N >= 3) primes.push_back(3);
    
    for (int i = 5; i <= N; i += 6) {
        if (isPrime(i)) primes.push_back(i);
        if (i + 2 <= N && isPrime(i + 2)) primes.push_back(i + 2);
    }
    
    return primes;
}
Node *primeList(Node *head){
    int largest = INT_MIN;
    Node *temp = head;
    while(temp){
        largest = max(temp->data,largest);
        temp = temp->next;
    }
    bool found = false;
    while (!found) {
        largest++;
        if (isPrime(largest)){found = true;}
    }
    
    vector<int> p = generatePrimes(largest);
    
    temp = head;
    while(temp){
        int no = temp->data;
        vector<int>::iterator itGreaterThanNo = lower_bound(p.begin(),p.end(),no);
        vector<int>::iterator itLesserThanNo = upper_bound(p.begin(),p.end(),no-1)-1;
        
        int greatNo = *itGreaterThanNo;
        int lessNo = ((*itLesserThanNo == 0)?(2):(*itLesserThanNo));
        
        int distless = no - lessNo;
        int distmore = greatNo - no;
        
        if(distless < distmore){
            temp->data = lessNo;
        } else if (distless > distmore){
            temp->data = greatNo;
        } else{
            temp->data = lessNo;
        }
        temp = temp->next;
    }
    return head;
}

/* Leaves to DLL
    INPUT :
            1
          /   \
         2     3
        / \   / \
       4   5 6   7    

    OUTPUT: 
            1
          /   \
         2     3

    4 <-> 5 <-> 6 <-> 7

    Return the head of the DLL and remove those node from the tree as well.
*/
Node *helper(Node *root, Node *&lltemp, Node *par){
    if (root == NULL){return NULL;}
    if(root->left == NULL && root->right == NULL){
        lltemp->right = root;
        root->left = lltemp;
        lltemp = lltemp->right;
        return NULL;
    }
    root->left = helper(root->left,lltemp,root);
    root->right = helper(root->right,lltemp,root);
    return root;
}
Node *convertToDLL(Node *root){
    Node *DLLHead = new Node(INT_MAX);
    Node *DLLTemp = DLLHead;
    root = helper(root,DLLTemp,NULL);
    if(DLLHead) {
        DLLTemp = DLLHead;
        DLLHead = DLLHead->right;
        free(DLLTemp); 
        if(DLLHead) { DLLHead->left = NULL; }
    }
    return DLLHead;
}