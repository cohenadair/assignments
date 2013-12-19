/**
 * AUTHOR: Cohen Adair
 * DATE: 28/11/2012
 *
 * This program asks the user to enter a postfix expression.  The program will
 * then print the expression in infix and prefix notation, as well as evaluate
 * the expression.
 *
 */

import java.util.*;

public class ReversePolish {

	private static Scanner in = new Scanner(System.in);

	public static void main(String[] args) {

		ExpTree tree = new ExpTree();

		System.out.print("Please enter a postfix expression: ");

		String e = in.nextLine();

		if (e.compareTo("") != 0) {
			tree.add(e);

			System.out.print("Infix notation: ");
			tree.printInfix();
			System.out.println("");

			System.out.print("Prefix notation: ");
			tree.printPrefix();
			System.out.println("");

			System.out.print("Answer: ");
			float a = tree.evaluate();
			System.out.println(a);
		}
	}
}