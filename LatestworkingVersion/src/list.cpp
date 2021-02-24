#include <stdio.h>
#include <stdlib.h>

#include <list.h>

int listTrash(Node **node) {
  Node *p = *node;
  if (p) {
      while (p->next) {
          free(p);
          p = p->next;
      }
      free(p);
      return 1;
  }
  return 0;
}

long long listLen(Node *n) {
    Node *p{n};
    unsigned long long len{1};
    if (!n) {
        return -1;
    }
    while (p->next) {
        p = p->next;
        len++;
    }
    return len;
}

void PrintList(Node **node, int *LIST_ERROR_CODE) {
    Node *p;
    if (!node) {
        *LIST_ERROR_CODE = 2;
        return;
    }
    p = *node;

    while (p) {
        printf("%f ", p->value);
        p = p->next;
    }
    printf("\n");
}

double popInd(Node **node, long long index, int *LIST_ERROR_CODE) {
    long long i;
    double tmp;
    Node *p;
    if (!node) {
        *LIST_ERROR_CODE = 2;
        return 0;
    }
    if (!*node) {
        *LIST_ERROR_CODE = 2;
        return 0;
    }
    p = *node;
    i = 0;
    while (i < index) {
        if (!p->next) {
            *LIST_ERROR_CODE = 5;
            return 0;
        }

        p = p->next;
        i++;
    }
    tmp = p->value;
    if (p->next) {
        p->next->prev = p->prev;
    }
    if (p->prev) {
        p->prev->next = p->next;
    } else {
        if (p->next) {
            *node = p->next;
            (*node)->prev = NULL;
        } else {
            *node = NULL;
        }
    }
    free(p);
    return tmp;
}

void insertInd(Node **node, long long index, double el, int *LIST_ERROR_CODE) {
    long long i;
    Node *p, *tmp;
    if (!node) {
        *LIST_ERROR_CODE = 2;
        return;
    }
    tmp = (Node*)malloc(sizeof(Node));
    if (!tmp) {
        *LIST_ERROR_CODE = 2;
        return;
    }
    tmp->value = el;
    if (!*node) {
        *node = tmp;
        tmp->next = NULL;
        tmp->prev = NULL;
        return;
    }
    p = *node;
    i = 0;
    while (i < index) {
        if (!p->next) {
            break;
        }
        p = p->next;
        i++;
    }
    tmp->prev = p;
    tmp->next = p->next;
    if (p->next) {
        p->next->prev = tmp;
    }
    p->next = tmp;
}
