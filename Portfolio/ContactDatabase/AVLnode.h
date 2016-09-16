/*
 * CSCI-2421: Data Structures and Program Design
 * University of Colorado Denver
 * AVL Tree Base Implementation.
 */
#ifndef AVLNode_H
#define AVLNode_H
#include "RecordType.h"
#include <iostream>




class RecordType;

class AVLNode : public RecordType
{
public:
    AVLNode();
    AVLNode(RecordType data, AVLNode* parent);
    AVLNode(RecordType data, AVLNode* left, AVLNode* right);
    AVLNode(RecordType data, AVLNode* left, AVLNode* right, int balance);
    ~AVLNode();

    void setData(RecordType data);
    void setBalance(int bal);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);

    RecordType getData() const;
    int getBalance() const;
    const AVLNode* const getLeft() const;
    const AVLNode* const getRight() const;

    bool operator < (const AVLNode& AVLNode) const;
    friend std::ostream& operator << (std::ostream& out, const AVLNode& AVLNode);

    /* Tree structure pointers */
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

    /* AVL Balance Factor */
    int balance;

    /* Node Internal Data */
    RecordType data;
};

#endif
