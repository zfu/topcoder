/*
 * Node.h
 *
 *  Created on: Jun 2, 2012
 *      Author: anson
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <limits>
#include <deque>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {};
    string toString() {
        ostringstream stream;
        stream << val;
        return stream.str();
    };
};

void fromStream(TreeNode*& node, int x, istream& stream) {
    if (x == -1) node = NULL;
    else {
        node = new TreeNode(x);
        if (stream >> x) fromStream(node->left, x, stream);
        if (stream >> x) fromStream(node->right, x, stream);
    }
}

TreeNode* fromString(string str) {
    int N = str.size();
    for (int i = 0; i < N; i++)
        if (str[i] == ',') str[i] = ' ';
    assert(str[0] == '{' && str[N-1] == '}');
    str = str.substr(1, N-2);
    istringstream stream(str);
    TreeNode* root;
    int val;
    stream >> val;
    fromStream(root, val, stream);
    return root;
}

void toStream(TreeNode* node, ostream& stream) {
    if(NULL == node) {
        stream << "-1" << ",";
        return;
    }
    stream << node->val << ",";
    toStream(node->left, stream);
    toStream(node->right, stream);
};

string toString(TreeNode* root) {
    ostringstream stream;
    stream << "{";
    toStream(root, stream);
    string res = stream.str();
    res[res.size()-1] = '}';
    return res;
}

int depth(TreeNode* node) {
    if(NULL == node) return 0;
    return 1 + max(depth(node->left), depth(node->right));
};

// Print the arm branches (eg, / \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue, ostringstream &stream) {
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++) {
        stream << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
        stream << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
    }
    stream << endl;
}

// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue, ostringstream &stream) {
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        stream << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
        stream << setw(branchLen+2) << ((*iter) ? (*iter)->toString() : "");
        stream << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
    }
    stream << endl;
}

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue, ostringstream &stream) {
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++)
        stream << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? ((*iter)->toString()) : "");
    stream << endl;
}

string toPretty(TreeNode* root) {
    ostringstream stream;
    int h = depth(root);
    int level = 1;
    int indentSpace = 0;
    int nodesInThisLevel = 1;

    // eq of the length of branch for each node of each level
    int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);
    // distance between left neighbor node's right arm and right neighbor node's left arm
    int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);
    // starting space to the first node to print of each level (for the left most node of each level only)
    int startLen = branchLen + (3-level) + indentSpace;

    deque<TreeNode*> nodesQueue;
    nodesQueue.push_back(root);
    for (int r = 1; r < h; r++) {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, stream);
        branchLen = branchLen/2 - 1;
        nodeSpaceLen = nodeSpaceLen/2 + 1;
        startLen = branchLen + (3-level) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, stream);

        for (int i = 0; i < nodesInThisLevel; i++) {
            TreeNode *currNode = nodesQueue.front();
            nodesQueue.pop_front();
            if (currNode) {
                nodesQueue.push_back(currNode->left);
                nodesQueue.push_back(currNode->right);
            } else {
                nodesQueue.push_back(NULL);
                nodesQueue.push_back(NULL);
            }
        }
        nodesInThisLevel *= 2;
    }
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, stream);
    printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, stream);
    return stream.str();
};

#endif /* TREENODE_H_ */
