#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

// GLOBAL VARIABLE
bool print = true;


struct BstNode
{
    // set up the node of our binary search tree
    // with an integer data, a left pointer, a right pointer
    int data;
    BstNode* left;
    BstNode* right;
};

// these are the function we use in main function
void BST();
void FindMeaty();
// these are the algorithm.
BstNode* GetNewNode(int data);
BstNode* Insert(BstNode* root, int data);
bool Search(BstNode* root, int data);
BstNode* FindRightMin(BstNode* root);
BstNode* Delete(BstNode* root, int data);

int color = 0; 

/********************** THIS IS MAIN ************************/
int main(){

    // main menu
    cout << "(1) Binary Searching Tree." << endl;
    cout << "(2) Finding Meaty." << endl;
    cout << "(0) Escape and face to music next year." << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 0:
        exit(0); // end the program.
        break;
    case 1:
        BST(); // Binary Searching Tree.
        break;
    case 2:
        FindMeaty(); // Finding Meaty.
        break;
    }
}

/********************** BST ************************/

// functions in BST()
BstNode* InsertNode(BstNode* root);
void SearchNode(BstNode* root);
BstNode* DeleteNode(BstNode* root);
void PreOrder(BstNode* root);
void InOrder(BstNode* root);
void PostOrder(BstNode* root);
void LevelOrder(BstNode* root);

// Binary Searching Tree.
void BST(){   

    print = true; // print insert, delete

    // IMORTANT: we set the "root" as the "local variable" of BST()
    BstNode* root; // pointer to root node
    root = NULL; // setting tree as empty
    char choice;

    // BST() menu (THIS IS A LOOP)
    while(choice!='r'){
        // if we don't input 'r', we stay in BST()
        cout << "(I)nsert a number." << endl;
        cout << "(D)elete a number." << endl;
        cout << "(S)earh a number." << endl;
        cout << "(P)rint 4 kinds of orders." << endl;
        cout << "(R)eturn" << endl;
        cin >> choice;

        switch (choice)
        {
        case 'i':
            root = InsertNode(root);
            // we add node to the root (cahnge the root)
            // that's why InsertNode(root) is BstNode*
            break;
        case 'd':
            root = DeleteNode(root);
            // we need to change the tree (reorganize)
            // therefore, DeleteNode is BstNode*
            break;
        case 's':
            SearchNode(root); // search
            break;
        case 'p':
            cout << "The tree in prefix order: ";
            PreOrder(root); // print prefix order
            cout << "\nThe tree in infix oredr: ";
            InOrder(root); // print infix order
            cout << "\nThe tree in post order: ";
            PostOrder(root); // print post order
            cout << "\nThe tree in level order: ";
            LevelOrder(root); // print level order
            break;
        case 'r':
            main();
            // close BST(), go back to main()
            // the data will not be saved if we get out of BST()
            break;
        }
        cout << "\n";
    }
   
}

BstNode* InsertNode(BstNode* root){
    // IMPORTANT : the "root" is the "BST() root"

    // get the input(string).
    string str, temp;
    cout << "Enter numbers: ";
    getline(cin >> ws, str); 
    str += ' '; // make sure we get the last number
    // get input (we have to use ws to make sure we really get the string)

    for(int i = 0; i < str.length(); i++){
        // separate with a space
        if(str[i] != ' '){  
            temp += str[i];
        }
        else{
            int a = stoi(temp);  // turn into integer
            if(a == -1){
                // end with -1
                continue; // go back to BST()
            }else{
                root = Insert(root, a);
                // insert number a;
            }
            temp = "";
        }
    }
    return root;
}

BstNode* DeleteNode(BstNode* root){
    // IMPORTANT : the "root" is the "BST() root"

    // get the input(string).
    string str, temp;
    cout << "Enter numbers to delete: ";
    getline(cin >> ws, str); 
    str += ' '; // make sure we get the last number
    // get input (we have to use ws to make sure we really get the string)

    for(int i = 0; i < str.length(); i++){
        // separate with a space
        if(str[i] != ' '){  
            temp += str[i];
        }
        else{
            int a = stoi(temp);  // turn into integer
            if(a == -1){
                // end with -1
                continue; // go back to BST()
            }else{
                root = Delete(root, a);
                // delete number a;
            }
            temp = "";
        }
    }
    return root;
}

void SearchNode(BstNode* root){
    string str, temp;
    cout << "Enter elements to searching: ";
    getline(cin >> ws, str); 
    str += ' '; // make sure we get the last number
    // get input (we have to use ws to make sure we really get the string)

    for(int i = 0; i < str.length(); i++){
        // separate with a space
        if(str[i] != ' '){  
            temp += str[i];
        }
        else{
            int a = stoi(temp);  // turn into integer
            if(a == -1){
                // end with -1
                continue; // go back to BST()
            }else{
                if(Search(root, a) == true){
                    cout << "Bingo! " << a << " is found." << endl;
                }else{
                    cout << "SORRY. " << a << " is not found." << endl;
                }
            }
            temp = "";
        }
    }
}

// prefix order (visit: root, left, right)
void PreOrder(BstNode* root){
    if(root == NULL) return;

    cout << root->data << " "; // visit root
    PreOrder(root->left); // visit left
    PreOrder(root->right); // visit right
}
// infix order (visit: left, root, right)
void InOrder(BstNode* root){
    if(root == NULL) return;

    InOrder(root->left); // visit left
    cout << root->data << " "; // visit root
    InOrder(root->right); // visit right
}
// post order (visit: left, right, root)
void PostOrder(BstNode* root){
    if(root == NULL) return;

    PostOrder(root->left); // visit left
    PostOrder(root->right); // visit right
    cout << root->data << " "; // visit root
}
// we must use QUEUE here 
void LevelOrder(BstNode* root){

    // (1) put root into the Q
    // (2) pop out root, and put its L and R child into the Q
    // (3) THAT IS TO SAY: 
    // (4) if we want to pop someone out, we put its L and R child into the Q

    if(root == NULL) return;

    queue<BstNode*> Q;
    Q.push(root); // push root into the queue
    // while Q is not empty
    while (!Q.empty()){

        // we pop out the front, print it, and push in its L and R child

        // print the front
        BstNode* current = Q.front();
        cout << current->data << " ";

        // push its L and R child
        if(current->left != NULL) Q.push(current->left);
        if(current->right != NULL) Q.push(current->right);   

        Q.pop(); // pop the front   
    }
}

/********************** Find Meaty ************************/


// functions in Meaty
bool GetPath(BstNode* root, stack<int>& path, int data);
void PrintPath(BstNode* root, int node1, int node2);


// Finding Meaty.
void FindMeaty(){

    BstNode* root; // pointer to root node
    root = NULL; // setting tree as empty
    int arr[100000] = {0}; // array to record the data of the file
    int arr_length = 0; // the length of the file


    // enter the file the user want to load in
    string file = "";
    cout << "Please input the map file: ";
    cin >> file;

    //load in the bstmap.txt by using ifstream
    ifstream inFile;
    inFile.open(file);

    // MAKE SURE we successfully load the file
    if(inFile.is_open()){
        cout << "Load file success. \n" << endl;
        print = false; // we dont print the insertion

        // line means every line we get in bstmap.txt
        string line = "";
        while(getline(inFile, line)){
            //get the information line by line
            if(line!=""){
                int a = stoi(line);
                root = Insert(root, a);
                arr[arr_length] = a;
            }
            arr_length++;
        }
        print = true;
    }

    int node1, node2, index; // node1: sword location, node2: Meaty's location
    cout << "Please input the sword location: ";
    cin >> node1;
    cout << "Please input Meaty's location: ";
    cin >> node2;
    cout << "Please input the brocoli traps' index (0~9): ";
    cin >> index;
    cout << "\n";

    // delete brocoli traps
    for(int i = 0; i < arr_length; i++){

        // if there's a digit equal to index
        // delete it
        if(arr[i] >= 10000 && arr[i]/10000 == index){
            root = Delete(root, arr[i]);
        }else if(arr[i] >= 1000 && arr[i]/1000 == index){
            root = Delete(root, arr[i]);
        }else if(arr[i] >= 100 && arr[i]/100 == index){
            root = Delete(root, arr[i]);
        }else if(arr[i] >= 10 && arr[i]/10 == index){
            root = Delete(root, arr[i]);
        }else if(arr[i] < 100 && arr[i]%10 == index){
            root = Delete(root, arr[i]);
        }
        // we have to make sure when index = 10
        // it wont delete all the nodes
    }

    cout << "\nCapoo successfully found his favorite meaty <3.\n" << endl;
    PrintPath(root, node1, node2);
    
    main();
}

// the goal is to get the path(stack), from root to the num_node
// this function return true when there is a path
// IMPORTANT: stack<int>& path <= to get the path1 path2 from PrintPath
bool GetPath(BstNode* root, stack<int>& path, int num){
    if(root == NULL) return false;

    path.push(root->data);
    // put the data into the stack
    // and CHECK: ...

    // case1: the root's data is the num. That means there's a path
    if(root->data == num) return true;
    // case2: the num is in the L or R subtree, lets check
    if(GetPath(root->left, path, num) || GetPath(root->right, path, num)) return true;

    // case3: num is not in this (sub) tree
    path.pop(); // pop the node out, and return false
    return false;
}

void PrintPath(BstNode* root, int node1, int node2){

    stack<int> path1; // from root to node1
    stack<int> path2; // from root to node2

    GetPath(root, path1, node1); // get path1 
    GetPath(root, path2, node2); // get path2

    int p1_length = path1.size();
    int p2_length = path2.size();
    int arr1[p1_length], arr2[p2_length];
    // turn path from stack to array (easy to print)
    // root(last out) is arr[0]

    int a = p1_length - 1;
    int b = p2_length - 1;
    // store the array from the end
    while(!path1.empty()){
        arr1[a] = path1.top();
        path1.pop();
        a--;
    }while(!path2.empty()){
        arr2[b] = path2.top();
        path2.pop();
        b--;
    }

    cout << "Shortest path to find the meaty: " << endl;
    // print the path to get sword
    for(int i = 0; i < p1_length; i++){
        cout << arr1[i] << "->";
    }
    // print node1 to node2 (sword to meaty)
    // get the intersection of path1 and path2 (arr1 and arr2)
    int inter = 0;
    while(inter != p1_length || inter != p2_length){
        if(arr1[inter] == arr2[inter]){
            inter++;
        }else{
            break;
        }
    }
    inter--;

    // print from node1 to intersection
    for(int i = p1_length -2; i > inter; i--){
        cout << arr1[i] << "->";
    }
    // print from intersection to node2
    for(int i = inter; i < p2_length; i++){
        cout << arr2[i];
        if(i != p2_length -1){
            cout << "->";
        }
    }
    
    cout << "\n";
}


/**************************** Algorithm ********************************/


// create a new node in tree (dynamic memory) with a data
BstNode* GetNewNode(int data){
    BstNode* newNode = new BstNode();
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insert a node into tree
BstNode* Insert(BstNode* root, int data){

    // IMPORTANT the root here means "the root of a binary search tree"

    if(root == NULL){   // tree is empty
        root = GetNewNode(data);
        if(print) cout << "Number " << data << " is inserted." << endl;
    }
    else if(data < root->data){
        // if the data of the insertion is less than its root
        // make it the leftchild of root
        root->left = Insert(root->left, data);
    }
    else if(data > root->data){
        // if the data of the insertion is larger than its root
        // make it the rightchild of root
        root->right = Insert(root->right, data);
    }
    else if(data == root->data){
        // if the data of the insertion is equal to its root
        // error messege
        if(print) cout << "Error. Number " << data << " exists." << endl;
    }
    return root;
}


// search data from tree
bool Search(BstNode* root, int data){
    if(root == NULL){
        return false;   // can't find data
    }
    else if(root->data == data){
        return true;   // the data is found
    }
    else if(data < root->data){
        // if the data is less than the root's data
        // search for the left side of root
        return Search(root->left, data);
    }else{
        // if the data is larger than the root's data
        // search for the right side of root
        return Search(root->right, data);
    }
}


// find the minimun of the node's rightchild
BstNode* FindRightMin(BstNode* root){
    // the mini must be the leftest one
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}


// delete a node from tree
BstNode* Delete(BstNode* root, int data){

    // IMPORTANT the root here means "the root of a binary search tree"

    if(root == NULL){
        // cannot find the number (data)
        cout << "Number " << data << " does not exist." << endl;
    }
    else if(data < root->data){
        // if the data is less than its root
        // search the leftchild of its root
        root->left = Delete(root->left, data);
    }
    else if(data > root->data){
        // if the data is larger than its root
        // search the rightchild of its root
        root->right = Delete(root->right, data);
    }else if(data == root->data){
        // we found the number, get ready to be deleted!!
        // this node has....

        //case 1: No child (leaves)
        if(root->left == NULL && root->right == NULL){
            // delete it directly
            delete root;
            root = NULL;
        }
        // case 2: One child
        else if(root->left == NULL){
            BstNode* temp = root;  // point to root
            root = root->right; // skip the node, point to its rightchild
            delete temp; // delete the node
        }else if(root->right == NULL){
            BstNode* temp = root;  
            root = root->left; // skip the node, point to its leftchild
            delete temp; // delete the node
        }
        // case 3: Two children
        else{
            // find the mini of its rightchild
            BstNode* temp  = FindRightMin(root->right);
            root->data = temp->data; // put the mini_of_right to root
            print = false;
            // we don't print the following part
            root->right = Delete(root->right, temp->data);
            // its right child will be the pre_root's rightchild without itself.
            print = true;
        }
        if(print) cout << "Number " << data << " is deleted." << endl;
    }
    return root;
}

// BST 
// insert: 10 4 2 24 8 37 10 14 18 4 6 3 1 24 9 -1
// delete: 4 2 5 8 19 14 16 -1
// search: 10 4 24 18 37 5 2 3 1 14 9 -1
