/**
 * AUTHOR: Cohen Adair
 * DATE: 11/11/2012
 *
 * This is a linked list class that inludes several different methods
 * for creating and manipulating linked lists.
 *
 */

public class LinkedList {

	private LinkedListNode head = null;

	public LinkedList() {
	}

	// returns the head node of the LinkedList
	public LinkedListNode getHead() {

		return head;
	}

	// returns the sum of all the nodes in the LinkedList
	public int getSum() {

		return (head == null) ? 0 : head.getSum();
	}

	// returns the largest valued node in the LinkedList
	public int getMax() {

		return (head == null) ? 0 : head.getMax();
	}

	// returns the smallest valued node in the LinkedList
	public LinkedListNode smallest() {

		LinkedListNode smallest = null;

		if (head != null)
			smallest = head.smallest();

		// if the head is the only element, it is the smallest
		if (smallest == null)
			smallest = head;

		return smallest;
	}

	// returns the largest valued node in the LinkedList
	public LinkedListNode largest() {

		LinkedListNode largest = null;

		if (head != null)
			largest = head.largest();

		// if the head is the only element, it is the largest
		if (largest == null)
			largest = head;

		return largest;
	}

	// adds a node to the front of the LinkedList
	public void addfront (int i) {

		head = new LinkedListNode(i, head);
	}

	// deletes all nodes with value "i"
	public void Delete(int i) {

		if (head != null) {
			head.Delete(i);

			// check if the head needs to be deleted
			if (head.getInt() == i)
				head = (head.getNext() == null) ? null : head.getNext();
		}
	}

	// prints the LinkedList in forward order
	public void printforward() {

    	if (head == null)
    		return;

    	head.printforward();
  		System.out.println();
	}

	// prints the LinkedList in reverse order
	public void printbackward() {

    	if (head == null)
    		return;

    	head.printbackward();
		System.out.println();
	}
}

