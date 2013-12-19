public class UseLinkedList {

	public static void main(String[] args) {

		LinkedList ll = new LinkedList();

		print("Rountine tests for proper error handling");
		print("----------------------------------------");
		print("");

		print("1. The sum of an empty list is zero.");
		print("   - The sum is "+ll.getSum()+".");
		print("");

		print("2. The maximum of an empty list is zero.");
		print("   - The maximum is "+ll.getMax()+".");
		print("");

		print("3. The smallest and largest nodes of an empty list are null.");
		print("   - The smallest node is "+ll.smallest()+".");
		print("   - The largest node is "+ll.largest()+".");
		print("");

		print("4. The head of an empty list is null.");
		print("   The head node is "+ll.getHead()+".");
		print("");

		print("5. getNext() on the last element of a list should return null.");
		ll.addfront(10);
		print("   - Next on the last element is "+ll.getHead().getNext()+".");
		print("");
		ll.Delete(10);

		print("6. Deleting from or printing an empty list should do nothing.");
		LinkedList lll = new LinkedList();
		print("   - Calling the Delete method...");
		lll.Delete(10);
		print("   - Calling the printforward method...");
		lll.printforward();
		print("   - Calling the printbackward method...");
		lll.printbackward();
		print("");

		print("Rountine tests for method execution");
		print("-----------------------------------");
		print("");

		ll.addfront(68);
		ll.addfront(15);
		ll.addfront(342);
		ll.addfront(5);
		ll.addfront(35);
		ll.addfront(68);
		ll.addfront(342);
		ll.addfront(1547);
		ll.addfront(99);
		ll.addfront(5);
		ll.addfront(342);

		print("1. printforward()");
		ll.printforward();
		print("");

		print("2. printbackward()");
		ll.printbackward();
		print("");

		print("3. The sum is "+ll.getSum()+". (ans = 2868)");
		print("4. The maximum is "+ll.getMax()+". (ans = 1547)");
		print("");

		print("9. The smallest node is "+ll.smallest().getInt()+". (ans = 5)");
		print("10. The largest node is "+ll.largest().getInt()+". (ans = 1547)");
		print("");

		print("5. Delete(342) - the last node as well as duplicates");
		ll.Delete(342);
		ll.printforward();
		print("");

		print("6. Delete(5) - a middle node as well as duplicates");
		ll.Delete(5);
		ll.printforward();
		print("");

		print("7. Delete(68) - the front node as well as duplicates");
		ll.Delete(68);
		ll.printforward();
		print("");

		print("8. Delete() the rest of the list");
		ll.Delete(15);
		ll.Delete(35);
		ll.Delete(1547);
		ll.Delete(99);
		ll.printforward();
		print("");

		LinkedList l2 = new LinkedList();
		l2.addfront(1);
		l2.addfront(5);
		l2.addfront(10);
		print("11. The smallest (last) node is "+l2.smallest().getInt()+". (ans = 1)");

		LinkedList l3 = new LinkedList();
		l3.addfront(5);
		l3.addfront(1);
		l3.addfront(1);
		l3.addfront(10);
		print("12. The smallest (middle) node is "+l3.smallest().getInt()+". (ans = 1) - duplicates");

		LinkedList l4 = new LinkedList();
		l4.addfront(10);
		l4.addfront(5);
		l4.addfront(1);
		print("13. The smallest (first) node is "+l4.smallest().getInt()+". (ans = 1)");

		print("");

		LinkedList l5 = new LinkedList();
		l5.addfront(10);
		l5.addfront(5);
		l5.addfront(1);
		print("14. The largest (front) node is "+l5.largest().getInt()+". (ans = 10)");

		LinkedList l6 = new LinkedList();
		l6.addfront(5);
		l6.addfront(10);
		l6.addfront(1);
		print("15. The largest (middle) node is "+l6.largest().getInt()+". (ans = 10)");

		LinkedList l7 = new LinkedList();
		l7.addfront(1);
		l7.addfront(5);
		l7.addfront(10);
		print("16. The largest (last) node is "+l7.largest().getInt()+". (ans = 10)");

		print("");
	}

	public static void print(String s) {

		System.out.println(s);
	}
}