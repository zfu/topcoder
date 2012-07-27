/*
 * ListNode.h
 *
 *  Created on: Jul 26, 2012
 *      Author: bqian
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_

#include <cassert>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {};
};

ListNode* fromString(string str) {
    int N = str.size();
    for (int i = 0; i < N; i++)
        if (str[i] == ',') str[i] = ' ';
    assert(str[0] == '{' && str[N-1] == '}');
    str = str.substr(1, N-2);
    ListNode* head = NULL, *curNode = NULL;
    istringstream stream(str);
    int val;
    while (stream >> val) {
        ListNode* newNode = new ListNode(val);
        if (head == NULL) {
            head = newNode;
            curNode = newNode;
        }
        else {
            curNode->next = newNode;
            curNode = curNode->next;
        }
    }
    return head;
}

string toString(ListNode* head) {
    ostringstream stream;
    stream << "{";
    while (head != NULL) {
        if (head->next == NULL) stream << head->val << "}";
        else stream << head->val << ",";
        head = head->next;
    }
    return stream.str();
};

string toPretty(ListNode* head) {
    ostringstream stream;
    while (head != NULL) {
        if (head->next == NULL) stream << head->val;
        else stream << head->val << "->";
        head = head->next;
    }
    return stream.str();
}

#endif /* LISTNODE_H_ */
