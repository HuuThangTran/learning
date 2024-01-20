/*
Minh Anh Le
2028648
*/


#include "List.h"
#include <stdlib.h>

struct NodeObj {
  int data;
  struct NodeObj* prev;
  struct NodeObj* next;
};

typedef struct NodeObj* Node;

struct ListStruct {
  Node front;
  Node back;
  Node cursor;
  int cursorIndex;
};

// Private function to create a new Node
Node newNode(int data) {
  Node N = (Node)malloc(sizeof(struct NodeObj));
  N->data = data;
  N->prev = NULL;
  N->next = NULL;
  return N;
}

// Private function to free a Node
void freeNode(Node* pN) {
  free(*pN);
  *pN = NULL;
}

List newList() {
  List L = (List)malloc(sizeof(struct ListStruct));
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->cursorIndex = -1;
  return L;
}

void freeList(List* pL) {
  listClear(*pL);
  free(*pL);
  *pL = NULL;
}

int length(List L) {
  int count = 0;
  Node iter = L->front;
  while (iter != NULL) {
    count++;
    iter = iter->next;
  }
  return count;
}

int listIndex(List L) {
  if (L->cursor != NULL) {
    return L->cursorIndex;
  }
  return -1;
}

int front(List L) {
  if (length(L) <= 0) {
    exit(EXIT_FAILURE);
  }
  return L->front->data;
}

int back(List L) {
  if (length(L) <= 0) {
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}

int get(List L) {
  if (length(L) <= 0 || listIndex(L) < 0) {
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

bool equals(List A, List B) {
  Node iterA = A->front;
  Node iterB = B->front;
  while (iterA != NULL && iterB != NULL) {
    if (iterA->data != iterB->data) {
      return false;
    }
    iterA = iterA->next;
    iterB = iterB->next;
  }
  return iterA == NULL && iterB == NULL;
}

void listClear(List L) {
  Node iter = L->front;
  while (iter != NULL) {
    Node next = iter->next;
    freeNode(&iter);
    iter = next;
  }
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->cursorIndex = -1;
}

void set(List L, int x) {
  if (length(L) <= 0 || listIndex(L) < 0) {
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
}

void moveFront(List L) {
  if (L->front != NULL) {
    L->cursor = L->front;
    L->cursorIndex = 0;
  }
}

void moveBack(List L) {
  if (L->back != NULL) {
    L->cursor = L->back;
    L->cursorIndex = length(L) - 1;
  }
}

void movePrev(List L) {
  if (L->cursor != NULL) {
    L->cursor = L->cursor->prev;
    L->cursorIndex--;
  }
}

void moveNext(List L) {
  if (L->cursor != NULL) {
    L->cursor = L->cursor->next;
    L->cursorIndex++;
    if (L->cursor == NULL) {
      L->cursorIndex = -1;
    }
  }
}

void prepend(List L, int x) {
  Node node = newNode(x);
  if (L->front == NULL) {
    L->front = node;
    L->back = node;
  } else {
    L->front->prev = node;
    node->next = L->front;
    L->front = node;
  }
  if (L->cursor != NULL) {
    L->cursorIndex++;
  }
}

void append(List L, int x) {
  Node node = newNode(x);
  if (L->back == NULL) {
    L->front = node;
    L->back = node;
  } else {
    L->back->next = node;
    node->prev = L->back;
    L->back = node;
  }
}

void insertBefore(List L, int x) {
  if (length(L) <= 0 || listIndex(L) < 0) {
    exit(EXIT_FAILURE);
  }
  Node node = newNode(x);
  node->next = L->cursor;
  node->prev = L->cursor->prev;
  if (L->cursor->prev == NULL) {
    L->front = node;
  } else {
    L->cursor->prev->next = node;
  }
  L->cursor->prev = node;
  L->cursorIndex++;
}

void insertAfter(List L, int x) {
  if (length(L) <= 0 || listIndex(L) < 0) {
    exit(EXIT_FAILURE);
  }
  Node node = newNode(x);
  node->next = L->cursor->next;
  node->prev = L->cursor;
  if (L->cursor->next == NULL) {
    L->back = node;
  } else {
    L->cursor->next->prev = node;
  }
  L->cursor->next = node;
}

void deleteFront(List L) {
  if (length(L) <= 0) {
    exit(EXIT_FAILURE);
  }
  if (L->cursor == L->front) {
    L->cursor = NULL;
    L->cursorIndex = -1;
  } else if (L->cursor != NULL) {
    L->cursorIndex--;
  }
  Node old = L->front;
  L->front = L->front->next;
  if (L->front == NULL) {
    L->back = NULL;
  } else {
    L->front->prev = NULL;
  }
  freeNode(&old);
}

void deleteBack(List L) {
  if (length(L) <= 0) {
    exit(EXIT_FAILURE);
  }
  if (L->cursor == L->back) {
    L->cursor = NULL;
    L->cursorIndex = -1;
  }
  Node old = L->back;
  L->back = L->back->prev;
  if (L->back == NULL) {
    L->front = NULL;
  } else {
    L->back->next = NULL;
  }
  freeNode(&old);
}

void delete(List L) {
  if (length(L) <= 0 || listIndex(L) < 0) {
    exit(EXIT_FAILURE);
  }
  Node old = L->cursor;
  if (L->cursor->prev == NULL) {
    L->front = L->cursor->next;
    if (L->front != NULL) {
      L->front->prev = NULL;
    } else {
      L->back = NULL;
    }
  } else {
    L->cursor->prev->next = L->cursor->next;
  }
  if (L->cursor->next == NULL) {
    L->back = L->cursor->prev;
    if (L->back != NULL) {
      L->back->next = NULL;
    } else {
      L->front = NULL;
    }
  } else {
    L->cursor->next->prev = L->cursor->prev;
  }
  L->cursor = NULL;
  L->cursorIndex = -1;
  freeNode(&old);
}

void printList(FILE* out, List L) {
  fprintf(out, "(");
  int count = 0;
  Node iter = L->front;
  while (iter != NULL) {
    if (count != 0) {
      fprintf(out, ", ");
    }
    if (count == L->cursorIndex) {
      if (iter != L->cursor) {
        exit(EXIT_FAILURE);
      }
      fprintf(out, "<");
    }
    fprintf(out, "%d", iter->data);
    if (count == L->cursorIndex) {
      fprintf(out, ">");
    }
    count++;
    iter = iter->next;
  }
  fprintf(out, ")");
}

List copyList(List L) {
  List N = newList();
  Node iter = L->front;
  while (iter != NULL) {
    append(N, iter->data);
    iter = iter->next;
  }
  return N;
}

List concatList(List A, List B) {
  List C = copyList(A);
  Node iter = B->front;
  while (iter != NULL) {
    append(C, iter->data);
    iter = iter->next;
  }
  return C;
}