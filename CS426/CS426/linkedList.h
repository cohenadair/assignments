#ifndef _linkedList_
#define _linkedList_

typedef struct ListNode{
  struct ListNode* next;
}ListNode;

struct LinkedList;

typedef int (*pFunIntVoid)(struct LinkedList*);

typedef void (*pFunVoidNode)(struct LinkedList*,ListNode*);

typedef ListNode* (*pFunNodeVoid)(struct LinkedList*);

typedef struct LinkedList{
  ListNode* head;
  ListNode* tail;
  pFunIntVoid isEmpty;
  pFunVoidNode addLast;
  pFunNodeVoid removeFirst;
}LinkedList;

LinkedList* newLinkedList(void);

#endif
