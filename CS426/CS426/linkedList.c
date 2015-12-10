#include "linkedList.h"
#include <stdlib.h>

int singlyLinkedIsEmpty(LinkedList*);
void singlyLinkedAddLast(LinkedList*,ListNode*);
ListNode* singlyLinkedRemoveFirst(LinkedList*);

LinkedList* newLinkedList(void){
    LinkedList* listRef = (LinkedList*)calloc(1,sizeof(LinkedList));

    if(listRef == NULL){
        return NULL;
    }

    listRef->isEmpty = singlyLinkedIsEmpty;
    listRef->addLast = singlyLinkedAddLast;
    listRef->removeFirst = singlyLinkedRemoveFirst;
    return listRef;
}

int singlyLinkedIsEmpty(LinkedList* self){
    return self->head == NULL;
}

void singlyLinkedAddLast(LinkedList* self,ListNode* nodeRef){
    nodeRef->next = NULL;
    if(self->isEmpty(self)){
        self->head = nodeRef;
        self->tail = nodeRef;
        return;
    }
    self->tail->next = nodeRef;
    self->tail = nodeRef;
}

//Return first node in LinkedList. If list is empty return NULL.
ListNode* singlyLinkedRemoveFirst(LinkedList* self){
    if(self->isEmpty(self)){
        return NULL;
    }
    ListNode* temp = self->head;
    self->head = temp->next;
    temp->next = NULL;
    return temp;
}
