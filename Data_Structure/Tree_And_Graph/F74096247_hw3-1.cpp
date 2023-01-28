#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

struct Node
{
    // set up the node of our binary search tree
    // with an integer data, a left pointer, a right pointer
    int data;
    Node* left;
    Node* right;
};

string input_and_build(string s, int n, int pre_or_post[], int inorder[]);
Node* build_tree_pre(int preorder[], int inorder[], int start, int end);
Node* build_tree_post(int postorder[], int inorder[], int start, int end);
string PostOrder(Node* root);
string PreOrder(Node* root);

static int tree_index;
// THIS MUST BE STATIC, because we will keep changing it during the whole program
// tree index is used to build our tree (from inorder & pre_or_post order)

int main(){

    int m;

    // enter the file the user want to load in
    string file = "";
    cout << "Please input the file name: ";
    cin >> file;

    //load in the file.txt by using ifstream
    ifstream inFile;
    inFile.open(file);

    // MAKE SURE we successfully load the file
    if(inFile.is_open()){
        // get "m" (how many times should we do)
        string firstline = "";
        getline(inFile,firstline);
        m = stoi(firstline);
    }

    // string[] to store the answer
    string ans[m];

    /*********************************************/

    int i = 0; // use i to track ans[m]
    int j = 0; // use j to track line
    if(inFile.is_open()){
        string line = ""; // every line in inFile(file)
        string s = "";
        int n = 0;
        string pre_or_post = "";
        string inorder = "";

        while(getline(inFile, line)){
            if(j%4 == 0){
                s = line;
            }else if(j%4 == 1){
                // get "n"
                n = stoi(line);
            }else if(j%4 == 2){
                // get pre_or_post
                pre_or_post = line;
            }else{
                // get inorder
                inorder = line;

                int pre_post[n], in[n];
                // transfer string into int array
                stringstream prepost_stream(pre_or_post);
                string item;
                int a = 0;
                while(getline(prepost_stream, item, ' ')){
                    pre_post[a] = stoi(item);
                    a++;
                }
                stringstream in_stream(inorder);
                a = 0;
                while (getline(in_stream, item, ' ')){
                    in[a] = stoi(item);
                    a++;
                }
                    // get the answer
                    ans [i] = input_and_build(s, n, pre_post, in);

                    i++;
            }
            j++;
        }
    }

    /*********************************************/

    // create a output file with similar name
    string out_file_name;
    out_file_name.assign(file, 2, file.length()-2);
    // if: file = "input.txt", out_file_name = "put.txt"
    out_file_name = "out" + out_file_name;

    ofstream outFile(out_file_name);
    // print out the answer
    for(int k = 0; k < m; k++){
        outFile << ans[k] << endl;
    }
    outFile.close();
    
    return 0;
}

string input_and_build(string s, int n, int pre_or_post[], int inorder[]){

    string ans = "";

    Node* root = NULL;
    // 2. build tree, and get the answer string
    if(s == "preorder-inorder"){

        // IMPORTANT
        // set up tree index 
        // it should be different everytime we call the function input_and_build
        // we have to reset it (it's static), or it will remain itself

        tree_index = 0; // reset tree_index
        root = build_tree_pre(pre_or_post, inorder, 0, n-1); // build the tree
        ans += PostOrder(root); // record the answer
    }if(s == "postorder-inorder"){
        tree_index = n-1;
        root = build_tree_post(pre_or_post, inorder, 0, n-1);
        ans += PreOrder(root);
    }

    root = NULL; // clear the tree (may not be neccessary)

    return ans;
}

// how we create a new node
Node* GetNewNode(int data){
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// search for the node's position in the inorder right now 
int search(int inorder[], int start, int end, int curr){
    for(int i = start; i <= end; i++){
        if(inorder[i] == curr){
            return i;
        }
    }
    return -1; // error
}

// 1 2 3 4 5 6 7 (pre)
// 3 2 4 1 6 5 7 (in)
// build the tree
// 1. add root(pre[0], 1) into the tree, and get the position from in[]
//    we get the nodes of root's left right subtree (left: 3 2 4, right: 6 5 7)
//    (tree index will keep ++)
// 2. repeat step 2

// build from preorder and inorder
Node* build_tree_pre(int preorder[], int inorder[], int start, int end){
    
    // tree index would start from 0;

    if(start > end){
        return NULL;
    }  // means we have search the entire (sub)tree. Then return null

    int curr = preorder[tree_index];
    tree_index++;
    Node* node = GetNewNode(curr);
    // create a node we are currently at (the node's data is curr)
    // index++ move on (->)

    if(start == end){
        return node;
    }  // means we almost search the entire (sub)tree.

    int pos = search(inorder, start, end, curr); // the position of curr in inorder
    node->left = build_tree_pre(preorder, inorder, start, pos-1); // the tree's left would be the inorder's left subtree.
    node->right = build_tree_pre(preorder, inorder, pos+1, end); // the tree's right would be the inorder's right subtree.

    return node; // return the tree we build.
}

// 5 6 4 7 3 8 2 10 9 1 (post)
// 5 4 6 3 7 2 8 1 9 10 (in)
// build the tree
// 1. add root(pre[9], 1) into the tree, and get the position from in[]
//    we get the nodes of root's right left subtree (right: 9 10, left: 5 4 6 3 7 2 8)
//    (tree index will keep --)
// 2. repeat step 2

// build from postorder and inorder
Node* build_tree_post(int postorder[], int inorder[], int start, int end){

    // tree index start from end

    if(start > end){
        return NULL;
    }

    int curr = postorder[tree_index];
    tree_index--;
    Node* node = GetNewNode(curr);
    // create a node we are currently at (the node's data is curr)
    // index-- move on (<-)


    if(start == end){
        return node;
    }

    int pos = search(inorder, start, end, curr); // the position of curr in inorder
    node->right = build_tree_post(postorder, inorder, pos+1, end);  // the tree's right would be the inorder's right subtree.
    node->left = build_tree_post(postorder, inorder, start, pos-1);  // the tree's left would be the inorder's left subtree.
    
    return node; // return the tree we build.
}

string PostOrder(Node* root){
    if(root == NULL) return "";

    string ans = "";

    ans += PostOrder(root->left); // visit left
    ans += PostOrder(root->right); // visit right
    ans += to_string(root->data); // visit root
    ans += " ";
    return ans;
}
string PreOrder(Node* root){
    if(root == NULL) return "";

    string ans = "";

    ans += to_string(root->data); // visit root
    ans += " ";
    ans += PreOrder(root->left); // visit left
    ans += PreOrder(root->right); // visit right
    return ans;
}

