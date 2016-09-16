/*
 * CSCI-2421: Data Structures and Program Design
 * University of Colorado Denver
 * AVL Tree Base Implementation.
 */
#include "AVLTree.h"
#include "AVLNode.h"
#include <vector>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;

/*
 * The implementation of this class is completely self-contained with the exception
 * of the provided node class.
 */



AVLTree::AVLTree() {
    this->root = nullptr;
}

AVLTree::AVLTree(const AVLTree& tree) {
    this->copyTree(tree);
}

AVLTree::~AVLTree() {
    delete this->root;
}

bool AVLTree::copyTree(const AVLTree& tree) {
    if ( tree.root == nullptr ) return false;
    this->clearTree();
    this->root = this->copySubtree(tree.root);
    return true;
}


RecordType &AVLTree::locate(RecordType existingData) {
    
    AVLNode* node = this->root;
    AVLNode* parent = this->root;
    AVLNode* child = this->root;

    while ( child != nullptr )
    {
        parent = node;
        node = child;
        child = existingData >= node->data ? node->right : node->left;
        
        if ( existingData == node->data) return node->data;
    }

    return node->data;
}

bool AVLTree::insert(RecordType newData) {
    //------------------------------------------------------------------------------
    // If the tree is empy, insert a new node; otherwise insert the new data and
    // ensure the tree is rebalanced recursively.
    //------------------------------------------------------------------------------
    if ( this->root == nullptr ) {
        this->root = new AVLNode(newData, nullptr);
    }
    else {
        AVLNode* node = this->root;
        AVLNode* parent = nullptr;
        bool insertComplete = false;

        //------------------------------------------------------------------------------
        // Determine the correct position to insert the new data. If the new value is
        // already stored, return false since there can only be one unique key.
        //------------------------------------------------------------------------------
        while ( !insertComplete ) {
            if ( node->data == newData ) return false;

            parent = node;
            bool leftOp = node->data > newData;
            node = leftOp ? node->left : node->right;
 
            //------------------------------------------------------------------------------
            // If the correct position is determined, add the new node appropriately. This
            // may incur an imbalance in the tree that must then be resolved using one or
            // more node rotations. The node rotations are performed until the balance 
            // factor of each node is within the acceptable [-1, 1] bound.
            //------------------------------------------------------------------------------
            if ( node == nullptr ) {
                if ( leftOp ) parent->left = new AVLNode(newData, parent);
                else parent->right = new AVLNode(newData, parent);

                this->rebalance(parent);
                insertComplete = true;
            }
        }
    }
 
    return true;
}

bool AVLTree::printBalance() {
    if ( this->root == nullptr ) return false;
    this->printBalance(this->root);
    return true;
}

unsigned int AVLTree::height() const {
    return this->height(this->root);
}

unsigned int AVLTree::size() const {
    unsigned int count = 0;
    this->size(this->root, count);
    return count;
}

bool AVLTree::remove(RecordType existingData) {
    if ( this->root == nullptr ) return false;
 
    AVLNode* node = this->root;
    AVLNode* parent = this->root;
    AVLNode* deleteAVLNode = nullptr;
    AVLNode* child = this->root;

    //------------------------------------------------------------------------------
    // Determine the node that must be removed from the tree. This is simply a
    // traversal (based on the binary search tree) for the node that should be
    // removed. If the node is not found, then it cannot be removed.
    //------------------------------------------------------------------------------
    while ( child != nullptr ) {
        parent = node;
        node = child;
        child = existingData >= node->data ? node->right : node->left;

        if ( existingData == node->data ) deleteAVLNode = node;
    }

    //------------------------------------------------------------------------------
    // The node with the provided data was found in the tree. The node must then
    // be manually removed through pointer reassignment.
    //------------------------------------------------------------------------------
    if ( deleteAVLNode != nullptr ) {
        //------------------------------------------------------------------------------
        // Copy operation of the data. This is a slighly more expensive operation
        // (depending on the store data and the overloaded = operator), but simplifes
        // the process of removing the existing node.
        //------------------------------------------------------------------------------
        deleteAVLNode->data = node->data;

        child = node->left != nullptr ? node->left : node->right;

        //------------------------------------------------------------------------------
        // The reassignment of the tree incurs the rebalance operation. This will
        // recursively rebalance the tree due to the change in the height based on the
        // removal of the target node. Also perform the parent pointer check to 
        // reassign the parent child pointer correctly.
        //------------------------------------------------------------------------------
        if ( this->root->data == existingData) {
            this->root = child;
        }
        else {
            if ( parent->left == node ) parent->left = child;
            else parent->right = child;
 
            this->rebalance(parent);
        }
    }
    else return false;

    return true;
}

bool AVLTree::clearTree() {
    if ( this->root == nullptr )
        return false;
    else {
    delete this->root;
        this->root = nullptr;
    }
    return true;
}


std::string AVLTree::preorder() const {
    std::stringstream stream;
    this->preorder(stream, this->root);
    return stream.str();
}

std::string AVLTree::inorder() const {
    std::stringstream stream;
    this->inorder(stream, this->root);
    return stream.str();
}

std::string AVLTree::postorder() const {
    std::stringstream stream;
    this->postorder(stream, this->root);
    return stream.str();
}

std::string AVLTree::toString() const {
    return this->inorder();
}

AVLTree& AVLTree::operator = (const AVLTree& tree) {
    if ( this == &tree ) return *this;
    this->clearTree();
    this->copyTree(tree);
    return *this;
}

std::ostream& operator << (std::ostream& out, const AVLTree& tree) {
    out << tree.toString() << std::endl;
    return out;
}

unsigned int AVLTree::height(AVLNode* node) {
    if ( node == nullptr ) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

/*
 * Primary rebalance function of the AVL tree implementation. This function
 * extensively uses the standard AVL rotation functions to recursively
 * balance the tree until the balance factor of each node resides within
 * the acceptable bounds of [-1, 1].
 */
void AVLTree::rebalance(AVLNode* node) {
    this->setBalance(node);

    //------------------------------------------------------------------------------
    // This sub-tree is left heavy, which means that nodes have to be rotated to
    // the right to balance the load of the lower trees.
    //------------------------------------------------------------------------------
    if ( node->balance == LEFT_HEAVY ) {
        if ( height(node->left->left ) >= height(node->left->right) )
            node = rotateRight(node);
        else node = rotateLeftRight(node);
    }
    //------------------------------------------------------------------------------
    // This sub-tree is right heavy, which means that nodes have to be rotated to
    // the left to balance the load of the lower trees (opposite case from above).
    //------------------------------------------------------------------------------
    else if ( node->balance == RIGHT_HEAVY ) {
        if ( height(node->right->right) >= height(node->right->left) )
            node = rotateLeft(node);
        else node = rotateRightLeft(node);
    }

    //------------------------------------------------------------------------------
    // Balance propigation. If an insertion/deletion operation causes a signifiant
    // imbalance within the tree, the changes must be propigated to ensure that
    // the load is evenly distributed and the tree is balanced.
    //------------------------------------------------------------------------------
    if ( node->parent != nullptr ) this->rebalance(node->parent);
    else root = node;
}

/*
 * Set the balance of the current node which represents a sub-tree.
 * The height of both the left and right sub-trees of this node will
 * be recursively determined, then their difference will represent
 * how unbalanced they are.
 */
bool AVLTree::setBalance(AVLNode* node) {
    if ( node == nullptr ) return false;
    node->balance = height(node->right) - height(node->left);
    return true;
}

void AVLTree::printBalance(AVLNode* node) {
    if ( node == nullptr ) return;

    this->printBalance(node->left);
    std::cout << node->balance << " ";
    this->printBalance(node->right);
}

unsigned int AVLTree::height(AVLNode* node) const {
    if ( node == nullptr ) return 0;
    else {
        unsigned int leftHeight = this->height(node->left);
        unsigned int rightHeight = this->height(node->right);

        if ( leftHeight > rightHeight ) return leftHeight + 1;
        else return rightHeight + 1;
    }
}

void AVLTree::size(AVLNode* node, unsigned int& count) const {
    if ( node == nullptr ) return;

    this->size(node->left, count);
    count++;
    this->size(node->right, count);
}

void AVLTree::preorder(std::stringstream& out, AVLNode* node) const {
    if ( node == nullptr ) return;

    out << node->data.getID() << " ";
    this->preorder(out, node->left);
    this->preorder(out, node->right);
}

void AVLTree::inorder(std::stringstream& out, AVLNode* node) const {
    if ( node == nullptr ) return;

    this->inorder(out, node->left);
    out << node->data.getID() << " ";
    this->inorder(out, node->right);
}

void AVLTree::postorder(std::stringstream& out, AVLNode* node) const {
    if ( node == nullptr ) return;

    this->postorder(out, node->left);
    this->postorder(out, node->right);
    out << node->data.getID() << " ";
}

/*
 * Manual reassignment of the internal pointers for the standard left
 * rotation. This function also updates the balance of the rotated
 * sub-trees and updates the parent pointer correctly.
 */
AVLNode* AVLTree::rotateLeft(AVLNode* node) {
    if ( node == nullptr ) return nullptr;

    //------------------------------------------------------------------------------
    // In the common notation, node is labeld 'a', its right is 'b' and that
    // childs right is 'c'
    //------------------------------------------------------------------------------
    AVLNode* b = node->right;
    b->parent = node->parent;
    node->right = b->left;

    //------------------------------------------------------------------------------
    // Set the nodes right parent to be the current node.
    //------------------------------------------------------------------------------
    if ( node->right != nullptr ) node->right->parent = node;

    //------------------------------------------------------------------------------
    // Manual pointer reassignment.
    //------------------------------------------------------------------------------
    b->left = node;
    node->parent = b;

    //------------------------------------------------------------------------------
    // Determine the correct parent for the new root. This has to be done as a
    // check of both children from the uknown parent (because we do not know if
    // the current base rotation node is the left or right child of the tree above)
    //------------------------------------------------------------------------------
    if ( b->parent != nullptr ) {
        if ( b->parent->right == node ) b->parent->right = b;
        else b->parent->left = b;
    }

    //------------------------------------------------------------------------------
    // Update the balance values based on the height of the sub-trees for the
    // newly rotated nodes.
    //------------------------------------------------------------------------------
    this->setBalance(node);
    this->setBalance(b);

    //------------------------------------------------------------------------------
    // Return the new root of the rotated sub-tree.
    //------------------------------------------------------------------------------
    return b;
}

/*
 * Manual reassignment of the internal pointers for the standard right
 * rotation. This function also updates the balance of the rotated
 * sub-trees and updates the parent pointer correctly.
 */
AVLNode* AVLTree::rotateRight(AVLNode* node) {
    if ( node == nullptr )
        return node;

    //------------------------------------------------------------------------------
    // In the common notation, node is labeld 'a', its left is 'b' and that
    // childs left is 'c'
    //------------------------------------------------------------------------------
    AVLNode* b = node->left;
    b->parent = node->parent;
    node->left = b->right;

    //------------------------------------------------------------------------------
    // Set the nodes left parent to be the current node.
    //------------------------------------------------------------------------------
    if ( node->left != nullptr ) node->left->parent = node;
 
    //------------------------------------------------------------------------------
    // Manual pointer reassignment.
    //------------------------------------------------------------------------------
    b->right = node;
    node->parent = b;

    //------------------------------------------------------------------------------
    // Determine the correct parent for the new root. This has to be done as a
    // check of both children from the uknown parent (because we do not know if
    // the current base rotation node is the left or right child of the tree above)
    //------------------------------------------------------------------------------
    if ( b->parent != nullptr ) {
        if ( b->parent->right == node ) b->parent->right = b;
        else b->parent->left = b;
    }

    //------------------------------------------------------------------------------
    // Update the balance values based on the height of the sub-trees for the
    // newly rotated nodes.
    //------------------------------------------------------------------------------
    this->setBalance(node);
    this->setBalance(b);
    
    //------------------------------------------------------------------------------
    // Return the new root of the rotated sub-tree.
    //------------------------------------------------------------------------------
    return b;
}

/*
 * Perform a compound rotation based on the existing rotation
 * functions. The returned node is the parent of the newly
 * rotated sub-tree. Rotate left then right.
 */
AVLNode* AVLTree::rotateLeftRight(AVLNode* node) {
    node->left = this->rotateLeft(node->left);
    return this->rotateRight(node);
}

/*
 * Perform a compound rotation based on the existing rotation
 * functions. The returned node is the parent of the newly
 * rotated sub-tree. Rotate right then left.
 */
AVLNode* AVLTree::rotateRightLeft(AVLNode* node) {
    node->right = this->rotateRight(node->right);
    return this->rotateLeft(node);
}

AVLNode* AVLTree::copySubtree(AVLNode* node) {
    if ( node == nullptr ) return nullptr;

    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    AVLNode* parent = nullptr;

    //------------------------------------------------------------------------------
    // Recursively copy the left sub-tree.
    //------------------------------------------------------------------------------
    if ( node->left == nullptr ) left = nullptr;
    else left = this->copySubtree(node->left);

    //------------------------------------------------------------------------------
    // Recursively copy the right sub-tree.
    //------------------------------------------------------------------------------
    if ( node->right == nullptr ) right = nullptr;
    else right = this->copySubtree(node->right);

    //------------------------------------------------------------------------------
    // Create a new parent based on the new left and right constructed sub-trees.
    //------------------------------------------------------------------------------
    parent = new AVLNode(node->data, left, right, node->balance);
    return parent;
}



std::vector<RecordType> &AVLTree::addtoVector(AVLNode *node, std::vector<RecordType> &vec)
{
    if ( node != nullptr )
    {
        if(node->data.getFirst() != "")
        vec.push_back(node->data);
        
        addtoVector(node->left, vec);
        addtoVector(node->right, vec);
    }
    
    return vec;
}

std::vector<RecordType> &AVLTree::addtoVector(std::vector<RecordType> &vec)
{
  
    this->addtoVector(this->root, vec);
    
    return vec;
}

void Print(struct AVLNode *root, RecordType k1, RecordType k2)
{
    /* base case */
    if ( NULL == root )
        return;
    
    /* Since the desired o/p is sorted, recurse for left subtree first
     If root->data is greater than k1, then only we can get o/p keys
     in left subtree */
    if ( k1 < root->data )
        Print(root->left, k1, k2);
    
    /* if root's data lies in range, then prints root's data */
    if ( k1 <= root->data && k2 >= root->data )
        std::cout << root->data;
    
    /* If root->data is smaller than k2, then only we can get o/p keys
     in right subtree */
    if ( k2 > root->data )
        Print(root->right, k1, k2);
}





