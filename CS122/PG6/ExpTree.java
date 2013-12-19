/**
 * AUTHOR: Cohen Adair
 * DATE: 28/11/2012
 *
 * This is an expression tree class that inludes several different methods
 * for creating, printing, and evaluating expressions from postfix notation.
 *
 */

public class ExpTree {

	private ExpTreeNode root = null;

	// adds all the characters in the postfix parameter to a expression tree
	public void add(String postfix) {

		root = new ExpTreeNode();
		root.add(postfix);
	}

	// prints the tree in infix notation
	public void printInfix() {

		if (root != null)
			root.printInfix();
	}

	// prints the tree in prefix notation
	public void printPrefix() {

		if (root != null)
			root.printPrefix();
	}

	//evaluates the expression
	public float evaluate() {

		if (root != null)
			return root.evaluate();

		return 0;
	}
}