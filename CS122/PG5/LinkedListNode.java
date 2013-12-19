/**
 * AUTHOR: Cohen Adair
 * DATE: 11/11/2012
 *
 * This is a class to be used alongside the LinkedList class. It includes all the helper
 * methods for properly calculating/manipulating the methods of a LinkedList.
 *
 */

public class LinkedListNode {

	private int number = 0;
	private LinkedListNode next = null;
	private LinkedListNode prev = null;

	public LinkedListNode(int i, LinkedListNode n) {

		number = i;
		next = n;

		if (next != null)
			next.setPrev(this);
	}

	// returns the node's data value
	public int getInt() {

		return number;
	}

	// returns the next node in the LinkedList
	public LinkedListNode getNext() {

		return next;
	}

	// returns the previous node in the LinkedList
	public LinkedListNode getPrev() {

		return prev;
	}

	// sets the previous node in the LinkedList to "n"
	public void setPrev(LinkedListNode n) {

		prev = n;
	}

	// sets the next node in the LinkedList to "n"
	public void setNext(LinkedListNode n) {

		next = n;
	}

	// returns the sum of all the nodes in the LinkedList
	public int getSum() {

		if (next != null)
			return number + next.getSum();
		else
			return number;
	}

	// returns the highest value in the LinkedList
	public int getMax() {

		int max = 0;

		if (next != null) {
			int i = next.getMax();
			max = (i > number) ? i : number;
		} else
			max = number;

		return max;
	}

	// returns the smallest valued node in the LinkedList; returns null of there is only one element
	public LinkedListNode smallest() {

		LinkedListNode smallest = null;

		if (next != null) {
			LinkedListNode n = next.smallest();

			if (number < n.getInt()) {
				if (prev != null)
					smallest = prev.getNext();
			} else
				smallest = n;
		} else
			if (prev != null)
				smallest = prev.getNext();

		return smallest;
	}

	// returns the largest valued node in the LinkedList; returns null if there is only one element
	public LinkedListNode largest() {

		LinkedListNode largest = null;

		if (next != null) {
			LinkedListNode n = next.largest();

			if (number > n.getInt()) {
				if (prev != null)
					largest = prev.getNext();
			} else
				largest = n;
		} else
			if (prev != null)
				largest = prev.getNext();

		return largest;
	}

	// deletes the nodes with value of "i"
	public void Delete(int i) {

		if (next != null)
			next.Delete(i);

		if (number == i) {
			if (next != null && prev != null) {	// middle of the list
				 prev.setNext(next);
				 next.setPrev(prev);
			} else
				if (next == null && prev != null) // last in the list
					prev.setNext(null);
		}
	}

	// prints the LinkedList in forward order
	public void printforward() {

		System.out.println(number);

		if (next != null)
			next.printforward();
	}

	// prints the LinkedList in backward order
	public void printbackward() {

		if (next != null)
			next.printbackward();

		System.out.println(number);
	}
}