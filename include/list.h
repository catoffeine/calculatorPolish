#ifndef _012_LIST_H
#define _012_LIST_H

struct Node {
    double value;
    Node *next;
    Node *prev;
};

int listTrash(Node **node);

long long listLen(Node *n);

double popInd(Node **node, long long index, int *LIST_ERROR_CODE);
void insertInd(Node **node, long long index, double el, int *LIST_ERROR_CODE);
void PrintList(Node **node, int *LIST_ERROR_CODE);

#endif
