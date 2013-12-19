/**
 * AUTHOR: Cohen Adair
 * DATE: 28/11/2012
 *
 * This is a class to be used alongside the ExpTree class. It includes all the helper
 * methods for properly calculating/manipulating the methods of an ExpTree.
 *
 */

public class ExpTreeNode {

	private char c = ' ';
	private ExpTreeNode left = null;
	private ExpTreeNode right = null;

	// adds all the characters in the postfix parameter to the expression tree
	public String add(String postfix) {

		c = postfix.charAt(postfix.length() - 1);
		postfix = postfix.substring(0, postfix.length() - 1);

		if (c >= '0' && c <= '9')
			return postfix;

		right = new ExpTreeNode();
		postfix = right.add(postfix);

		left = new ExpTreeNode();
		postfix = left.add(postfix);

  		return postfix;
	}

	// prints the tree in infix notation
	public void printInfix() {

    	if (left != null) {
   			System.out.print("(");
   			left.printInfix();
  		}

  		System.out.print (c);

  		if (right != null) {
   			right.printInfix();
   			System.out.print(")");
  		}
	}

	// prints the tree in prefix notation
	public void printPrefix() {

		System.out.print(c);

		if (left != null)
			left.printPrefix();

		if (right != null)
			right.printPrefix();
	}

	// returns the result of the evaluated expression
	public float evaluate() {

		if (c >= '0' && c <= '9')
			return c - 48; // ASCII code for '0' is 48
		else {
			float l = left.evaluate();
			float r = right.evaluate();

			switch (c) {
				case '+': return l + r;
				case '-': return l - r;
				case '*': return l * r;
				case '/': return l / r;
				default: return 0;
			}
		}
	}
}