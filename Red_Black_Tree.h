
/*
 * Author: Nathan Garcia, Ethan Vowels, Rylan Kinzle,
           Noah Mathew, Ethan Pritchett
 * Assignment Title: Red-Black Tree
 * Assignment Description: Implements a red-black tree
 * Due Date: 12/8/2024
 * Date Created: 10/5/2024
 * Date Last Modifed: 12/8/2024
 */

#ifndef RedBlackTree_h
#define RedBlackTree_h

#include <iostream>
#include <queue>
#include <string>
#include <cmath>
using namespace std;

class RedBlackTree;
enum Color {RED, BLACK};

struct Instructions {
    RedBlackTree* treeBefore;
    bool right;
    int depth;
    int breadth;

    Instructions(RedBlackTree* tree, bool r, int d, int b)
            : treeBefore(tree), right(r), depth(d), breadth(b) {}
};
queue<Instructions> treeInstructions;

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int input, Node* ptr = nullptr, Color iColor = RED): data(input)
            , color(iColor), parent(ptr), left(nullptr), right(nullptr) {};

    ~Node(){
        delete left;
        delete right;
    }
};

class RedBlackTree {
private:
    Node* root;

public:

    /*
     * description: Default constructor for RedBlackTree class.
     *              Initializes the tree with a sentinel root node.
     * return: none
     * precondition: none
     * postcondition: A tree with an empty (-1) root node is created.
     */
    RedBlackTree();

    /*
     * description: Inserts a new integer into the red-black tree
     *              while maintaining its properties.
     * return: void
     * precondition: The input is a valid integer.
     * postcondition: A new node with the given integer is added to the tree.
     */
    void insert(int input);

    /*
     * description: Removes a node with the given integer value from the tree.
     * return: bool
     * precondition: The input is a valid integer.
     * postcondition: The node with the specified value is
     *                removed from the tree, and the tree remains balanced.
     */
    bool remove(int input);

    /*
     * description: Searches for a node with the specified integer value.
     * return: Node*
     * precondition: The input is a valid integer.
     * postcondition: The pointer to the node is returned;
     *                the tree structure is unchanged.
     */
    Node* find(int input);

    /*
     * description: Finds the path to a node with the
     *              specified value and stores the path directions.
     * return: Node*
     * precondition: The input is a valid integer,
     *               and the direction queue is empty.
     * postcondition: The direction queue is populated with
     *                0 (left) or 1 (right) for the path.
     */
    Node* findPath(int input, queue<int>& d);

    /*
     * description: Checks if the red-black tree is empty.
     * return: bool
     * precondition: none
     * postcondition: Returns the status of the tree
     *                without altering its structure.
     */
    bool isEmpty();

    /*
     * description: Deletes all nodes in the tree and
     *              resets it to an empty state.
     * return: void
     * precondition: none
     * postcondition: The tree is cleared, leaving only a sentinel root node.
     */
    void clear();

    /*
     * description: Retrieves the root node of the tree.
     * return: Node*
     * precondition: none
     * postcondition: The root node is returned without
     *                altering the tree structure.
     */
    Node* getRoot();

    /*
     * description: Computes the maximum depth of the tree.
     * return: int
     * precondition: none
     * postcondition: The depth of the tree is returned;
     *                the tree remains unchanged.
     */
    int maxDepth() const;

    /*
     * description: Copy constructor that creates a
     *              deep copy of another RedBlackTree.
     * return: none
     * precondition: A valid RedBlackTree object exists to copy from.
     * postcondition: A new RedBlackTree is created with
     *                identical structure and values.
     */
    RedBlackTree(const RedBlackTree& other) {
        if (other.root->data != -1) {
            root = new Node(*other.root);
            deepCopyRecursive(root, other.root);
        } else {
            root = new Node(-1, nullptr, BLACK);
        }
    }

    /*
     * description: Helper function that recursively
     *              creates a deep copy of the tree structure.
     * return: void
     * precondition: Valid current and otherCurrent Node pointers.
     * postcondition: The subtree rooted at current is
     *                a deep copy of otherCurrent's subtree.
     */
    void deepCopyRecursive(Node* current, Node* otherCurrent) {
        //go down the left side and create new nodes to copy
        if (otherCurrent->left && otherCurrent->left->data != -1) {
            current->left = new Node(*otherCurrent->left);
            current->left->parent = current;
            deepCopyRecursive(current->left, otherCurrent->left);
        }
        //go down the right side and create new nodes to copy
        if (otherCurrent->right && otherCurrent->right->data != -1) {
            current->right = new Node(*otherCurrent->right);
            current->right->parent = current;
            deepCopyRecursive(current->right, otherCurrent->right);
        }
    }

    /*
     * description: Initiates a deep copy of a subtree structure.
     * return: void
     * precondition: Valid current and copy Node pointers.
     * postcondition: The subtree rooted at copy becomes
     *                a deep copy of current's subtree.
     */
    void deepCopy(Node* current, Node* copy){
        if(current){
            deepCopyRec(current, copy);
        }
    }

    /*
     * description: Recursive helper function for deepCopy
     *              that copies node data and structure.
     * return: void
     * precondition: Valid current and copy Node pointers.
     * postcondition: The node and its children are copied
     *                with identical structure and values.
     */
    void deepCopyRec(Node* current, Node* copy){
        //Node temp(current->data);
        //copy = &temp;
        copy->data = current->data;
        copy->color = current->color;
        copy->left = new Node(-1);
        copy->right = new Node(-1);
        if(copy->data != -1){
            deepCopyRec(current->left, copy->left);
            deepCopyRec(current->right, copy->right);
        }
    }

    /*
     * description: Performs a level-order (breadth-first)
     *              traversal of the tree.
     * return: queue<Node*>
     * precondition: none
     * postcondition: Returns a queue containing all nodes in level-order;
     *                the tree structure remains unchanged.
     */
    queue<Node*> levelOrderTraversal() {
        queue<Node*> result;
        if (root == nullptr || root->data == -1) {
            return result;
        }

        queue<Node*> processQueue;
        processQueue.push(root);

        while (!processQueue.empty()) {
            Node* currentNode = processQueue.front();
            processQueue.pop();

            result.push(currentNode);

            // Add children to the queue if they are valid
            if (currentNode->left && currentNode->left->data != -1) {
                processQueue.push(currentNode->left);
            }
            if (currentNode->right && currentNode->right->data != -1) {
                processQueue.push(currentNode->right);
            }
        }
        return result;
    }

private:

    /*
     * description: Calculates the depth of a target node from the root.
     * return: int
     * precondition: Valid root and target Node pointers.
     * postcondition: Returns the depth of the target node or -1 if not found;
     *                the tree structure remains unchanged.
     */
    int findDepth(Node* root, Node* target) {
        cout << "trying to find the depth of " << target->data << endl;
        //make sure they are not null nodes
        if (root == nullptr || target == nullptr) {
            return -1;
        }
        int depth = 0;
        Node* current = target;
        while (current != root) {
            current = current->parent;
            depth++;
        }
        cout << "Depth: " << depth << endl;
        return depth;
    }

    /*
     * description: Calculates the breadth (horizontal position) of a target node.
     * return: int
     * precondition: Valid root and target Node pointers.
     * postcondition: Returns the breadth value of the target node
     *                or -1 if not found; the tree structure remains unchanged
     */
    int findBreadth(Node* root, Node* target) {
        int breadth = 0;
        cout << "Trying to find the breadth of " << target->data << endl;
        //make sure they are not null nodes
        if (root == nullptr || target == nullptr) {
            return -1;
        }
        queue<int> directions;
        findPath(target->data, directions);

        /*
        while(!directions.empty()){
            cout << directions.front();
            directions.pop();
        }
        cout << endl;
        */
        if(directions.empty()){
            breadth = 0;
        }
        int n = 0;
        while(!directions.empty()){
            cout << directions.front();
            if(directions.front() == 1){
                breadth += pow(2,n);
            }
            n++;
            directions.pop();
        }
        cout << endl;
        cout << "Breadth: " << breadth << endl;

        return breadth;
    }

    /*
     * description: Performs a left rotation around the specified node.
     * return: void
     * precondition: The node has a valid right child.
     * postcondition: The tree structure is modified according to left
     *                rotation rules while maintaining red-black properties.
     */
    void rotateLeft(Node* ptr) {

        RedBlackTree *cc = new RedBlackTree();
        deepCopy(this->root,cc->getRoot());
        Instructions rotate(cc, false, findDepth(this->getRoot(),ptr), findBreadth(this->getRoot(),ptr));


        treeInstructions.push(rotate);

        //Perform the rotation
        Node* temp = ptr->parent;
        ptr->parent = ptr->right;
        ptr->right = ptr->parent->left;
        ptr->parent->left = ptr;
        ptr->parent->parent = temp;


        if (ptr->right) {
            ptr->right->parent = ptr;
        }

        if (temp == nullptr) {
            root = ptr->parent;
        }
        else if (temp->right == ptr) {
            temp->right = ptr->parent;
        }
        else {
            temp->left = ptr->parent;
        }
    }

    /*
     * description: Performs a right rotation around the specified node.
     * return: void
     * precondition: The node has a valid left child.
     * postcondition: The tree structure is modified
     *                while maintaining red-black properties.
     */
    void rotateRight(Node* ptr) {


        RedBlackTree *cc = new RedBlackTree();
        deepCopy(this->root,cc->getRoot());
        Instructions rotate(cc, true, findDepth(this->getRoot(),ptr), findBreadth(this->getRoot(),ptr));

        //Instructions rotate(this, true,findDepth(this->getRoot(),ptr),findBreadth(this->getRoot(),ptr));
        treeInstructions.push(rotate);

        Node* temp = ptr->parent;
        ptr->parent = ptr->left;
        ptr->left = ptr->parent->right;
        ptr->parent->right = ptr;
        ptr->parent->parent = temp;
        if (ptr->left) {
            ptr->left->parent = ptr;
        }

        if (temp == nullptr) {
            root = ptr->parent;
        }
        else if (temp->left == ptr) {
            temp->left = ptr->parent;
        }
        else {
            temp->right = ptr->parent;
        }
    }

    /*
     * description: Restores red-black tree properties after an insertion.
     * return: void
     * precondition: A new node has been inserted into the tree.
     * postcondition: The tree satisfies all red-black tree properties.
     */
    void fixInsert(Node* ptr) {
        while (ptr != root && ptr->parent->color == RED) {
            Node* uncle;  //used to refer to current node's parent's sibling
            if (ptr->parent->parent->right == ptr->parent) {
                uncle = ptr->parent->parent->left;
            }
            else {
                uncle = ptr->parent->parent->right;
            }

            if (uncle->color == BLACK) {

                if (uncle == uncle->parent->left) {
                    //fixes a zig-zag
                    if (ptr->parent->left == ptr) {
                        ptr = ptr->parent;
                        rotateRight(ptr);
                    }
                        //fixes a zig-zig
                    else {
                        ptr->parent->color = BLACK;
                        ptr->parent->parent->color = RED;
                        rotateLeft(ptr->parent->parent);
                    }
                }
                else {
                    //fixes a zig-zag
                    if (ptr->parent->right == ptr) {
                        ptr = ptr->parent;
                        rotateLeft(ptr);
                    }
                        //fixes a zig-zig
                    else {
                        ptr->parent->color = BLACK;
                        ptr->parent->parent->color = RED;
                        rotateRight(ptr->parent->parent);
                    }
                }
            }
            else {
                //flip colors of grandparent and its children
                ptr = ptr->parent->parent;
                ptr->color = RED;
                ptr->left->color = BLACK;
                ptr->right->color = BLACK;
            }
        }
        root->color = BLACK;
    }


    /*
     * description: Replaces one subtree with another in the tree structure.
     * return: void
     * precondition: Valid subtreeParent and subtreeRoot Node pointers.
     * postcondition: The subtree rooted at subtreeParent is replaced by
     *                the subtree rooted at subtreeRoot.
     */
    void transferSubtree(Node* subtreeParent, Node* subtreeRoot) {
        //Splices out a node and attaches its subtrees to its parent
        if (subtreeParent->parent == nullptr) {
            root = subtreeRoot;
        }
        else if (subtreeParent == subtreeParent->parent->left) {
            subtreeParent->parent->left = subtreeRoot;
        }
        else {
            subtreeParent->parent->right = subtreeRoot;
        }
        subtreeRoot->parent = subtreeParent->parent;
    }

    /*
     * description: Restores red-black tree properties after a node removal.
     * return: void
     * precondition: A node has been removed from the tree.
     * postcondition: The tree satisfies all red-black tree properties.
     */
    void fixRemove(Node* ptr) {
        while (ptr != root && ptr->color == BLACK) {
            Node* sibling = nullptr;
            //Assign a pointer to ptr's sibling
            if (ptr == ptr->parent->left) {
                sibling = ptr->parent->right;
            }
            else {
                sibling = ptr->parent->left;
            }
            //Case 1
            if (sibling->color == RED) {
                //flip sibling and parent's color
                sibling->color = BLACK;
                ptr->parent->color = RED;
                //rotate
                if (ptr == ptr->parent->left) {
                    rotateLeft(ptr->parent);
                    sibling = ptr->parent->right;
                }
                else {
                    rotateRight(ptr->parent);
                    sibling = ptr->parent->left;
                }
                //Check case 2, 3, or 4
            }
            //Case 2
            if ((sibling->left->color == BLACK) && (sibling->right->color == BLACK)){
                //flip color and perculate up
                sibling->color = RED;
                ptr = ptr->parent;
                //Check case 0, 1, 3, or 4
            }
            else {
                if (ptr == ptr->parent->left) {
                    //Case 3 (Left Child)
                    if (sibling->right->color == BLACK) {
                        //flip sibling and left child colors & rotate
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = ptr->parent->right;
                        //procceed to case 4
                    }
                    //Case 4 (Left Child)
                    sibling->color = ptr->parent->color;
                    ptr->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    rotateLeft(ptr->parent);
                    ptr = root; //return
                }
                else {
                    //Case 3 (Right Child)
                    if (sibling->left->color == BLACK) {
                        //flip sibling and right child colors & rotate
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = ptr->parent->left;
                        //procceed to case 4
                    }
                    //Case 4 (Right Child)
                    sibling->color = ptr->parent->color;
                    ptr->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rotateRight(ptr->parent);
                    ptr = root; //return
                }

            }
        }
        //recolor the root black to comply with rules
        ptr->color = BLACK;
    }

    /*
     * description: Recursively calculates the maximum depth of the tree.
     * return: int
     * precondition: Valid root Node pointer.
     * postcondition: Returns the maximum depth of the tree;
     *                the tree structure remains unchanged.
     */
    int calculateDepth(Node* root) const {
        // Handle null node or sentinel node (-1)
        if (root == nullptr || root->data == -1) {
            return 0;
        }

        // Recursively find the maximum depth
        int leftDepth = calculateDepth(root->left);
        int rightDepth = calculateDepth(root->right);

        // Return the larger depth + 1 for current node
        return 1 + max(leftDepth, rightDepth);
    }

};

RedBlackTree::RedBlackTree() {
    //-1 is associated with nullptr (allows null nodes to be assigned a color)
    root = new Node(-1);
}

void RedBlackTree::insert(int input) {

    while(!treeInstructions.empty()){
        treeInstructions.pop();
    }
    //If tree is empty, insert at root
    if (isEmpty()) {
        root->data = input;
        root->left = new Node(-1, root, BLACK);
        root->right = new Node(-1, root, BLACK);
        fixInsert(root);
    }
        //if tree isn't empty, insert at proper leaf node
    else {
        //progenitor = parent of node being pointed to
        Node* progenitor = root;
        Node* ptr = root;
        //Locate proper leaf node
        while (ptr->data != -1) {
            progenitor = ptr;
            if (input < ptr->data) {
                ptr = ptr->left;
            }
            else {
                ptr = ptr->right;
            }
        }
        //Creates a leaf node with the value to insert
        Node* temp = new Node(input, progenitor);
        temp->left = new Node(-1, temp, BLACK);
        temp->right = new Node(-1, temp, BLACK);

        if (input < progenitor->data) {
            progenitor->left = temp;
        }
        else {
            progenitor->right = temp;
        }
        //Rebalance tree
        fixInsert(temp);
    }
}

bool RedBlackTree::remove(int input) {

    while(!treeInstructions.empty()){
        treeInstructions.pop();
    }

    //Check if tree contains the input value
    Node* deleteable = find(input);
    if (deleteable->data == -1) {
        //return false if tree does not contain input value
        return false;
    }

    Node* replacement = deleteable;
    Node* ptr = nullptr;
    Color replacementColor = replacement->color;

    //2 null children
    if (deleteable->left->data == -1 && deleteable->right->data == -1) {
        ptr = deleteable->right;
        transferSubtree(deleteable, deleteable->right);
        //left child is null
    }
    else if (deleteable->left->data == -1) {
        ptr = deleteable->right;
        transferSubtree(deleteable, deleteable->right);
    }
            //right child is null
    else if (deleteable->right->data == -1) {
        ptr = deleteable->left;
        transferSubtree(deleteable, deleteable->left);
    }
            //no null children
    else {
        replacement = deleteable->left;
        //Find the max of the min
        while (replacement->right->data != -1) {
            replacement = replacement->right;
        }
        replacementColor = replacement->color;
        ptr = replacement->left;

        Node* originalParent = replacement->parent;

        //Reattach subtrees
        if (replacement->parent != deleteable) {
            transferSubtree(replacement, replacement->left);
            replacement->left = deleteable->left;
            replacement->left->parent = replacement;
        }
        //Reattach subtrees
        transferSubtree(deleteable, replacement);
        replacement->right = deleteable->right;
        replacement->right->parent = replacement;
        replacement->color = deleteable->color;

        if (originalParent == deleteable) {
            ptr->parent = replacement;
        }
    }

        //set children to nullptr to prevent recursive delete
        deleteable->left = nullptr;
        deleteable->right = nullptr;
        delete deleteable;

        //If deleted node is black, rebalance tree
        //(no need to rebalance if a red node is removed
        if (replacementColor == BLACK) {
            fixRemove(ptr);
        }

        return true;
    }

    Node* RedBlackTree::find(int input) {
        Node* ptr = root;  //Start searching from the root
        while (ptr->data != -1 && ptr->data != input) {  //Search until proper node is found or all possible locations are searched
            //if the item being searched for < current node, point to left child
            if (input < ptr->data) {
                ptr = ptr->left;
            }
                //if the item being searched for > current node, point to right child
            else {
                ptr = ptr->right;
            }
        }
        //Return a reference to the node (or nullptr if not found)
        return ptr;
    }

    Node* RedBlackTree::findPath(int input, queue<int>& direction) {

        Node* ptr = root;  //Start from the root
        while (ptr->data != -1 && ptr->data != input) {
            //if input < node->data, log a left traversal
            //point to left child
            if (input < ptr->data) {
                ptr = ptr->left;
                direction.push(0);
            }
                //if input > node->data, log a right traversal
                //point to right child
            else {
                ptr = ptr->right;
                direction.push(1);
            }
        }

        return ptr;
    }


    bool RedBlackTree::isEmpty() {
        return root->data == -1;
    }

    void RedBlackTree::clear() {
        delete root;
        root = new Node(-1, nullptr, BLACK);

    }

    Node* RedBlackTree::getRoot() {
        return root;
    }

    int RedBlackTree::maxDepth() const {
        return calculateDepth(this->root);
    }

#endif /* RedBlackTree_h */
