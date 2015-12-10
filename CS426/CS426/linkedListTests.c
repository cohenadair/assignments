#include "linkedListTests.h"

LinkedList* testListRef;

ListNode node1;
ListNode node2;
ListNode node3;
ListNode node4;
ListNode node5;


void setupLinkedListTestCase(){
  testListRef = newLinkedList();
}

void testList(){
    mt_assert(testListRef);
    mt_assert(testListRef->isEmpty(testListRef));
    testListRef->addLast(testListRef, &node1);
    mt_assert(!testListRef->isEmpty(testListRef));
    mt_assert(testListRef->removeFirst(testListRef) == &node1);
    mt_assert(testListRef->isEmpty(testListRef));
    testListRef->addLast(testListRef, &node1);
    mt_assert(testListRef->head == testListRef->tail);
    testListRef->addLast(testListRef, &node2);
    mt_assert(testListRef->tail == &node2);
    testListRef->addLast(testListRef, &node3);
    mt_assert(!testListRef->isEmpty(testListRef));
    mt_assert(testListRef->head != testListRef->tail);
    mt_assert(testListRef->removeFirst(testListRef) == &node1);
    mt_assert(testListRef->removeFirst(testListRef) == &node2);
    mt_assert(testListRef->removeFirst(testListRef) == &node3);
    mt_assert(testListRef->isEmpty(testListRef));
}

MT_Test linkedListTests[] = {
  {&testList, "testList"},
};

MT_TestCase linkedListTestCase = {
  linkedListTests, &setupLinkedListTestCase, "linkedListTests", 1
};
