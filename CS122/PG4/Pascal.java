/**
 * AUTHOR: Cohen Adair
 * DATE: 20/10/2012
 *
 * This program will print a number at any postion in a weighted Pascal's Triangle.
 * The weight of the triangle and the position of the number is determined by the user.
 *
 */

import java.util.*;

public class Pascal
{
	public static Scanner in = new Scanner (System.in);

	public static void main(String[] args)
	{
		System.out.print("Enter weight a: ");
		int a = in.nextInt();

		System.out.print("Enter weight b: ");
		int b = in.nextInt();

		System.out.print("Enter row number: ");
		int row = in.nextInt();

		System.out.print("Enter column number: ");
		int column = in.nextInt();

		System.out.println("The number is: "+triangle(a, b, row, column));
	}

	// returns an integer in a weighted pascal's triangle of weight a, b, at position row, column
	public static int triangle(int a, int b, int row, int column)
	{
		if (row == 0 && column == 0) // single base case; first row of pascals triangle
			return 1;

		if (row < 0 || column < 0) // to catch negative parameters (out of bounds)
			return 0;

		return (a * triangle(a, b, row - 1, column - 1)) + (b * triangle(a, b, row - 1, column));
	}
}