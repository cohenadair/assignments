/**
 * AUTHOR: Cohen Adair
 * DATE: 06/09/2012
 *
 * This program will prompt the user to enter two numbers, and read them in as strings.
 * It will then print the product of the two numbers.  There is no limit to the length
 * of the numbers.
 *
 */

import java.util.*;

public class Mult
{
	public static Scanner in = new Scanner(System.in);

	public static void main(String[] args)
	{
		System.out.print("Please enter a multiplicand: ");
		String s = getValidString(in.nextLine());

		System.out.print("Please enter a multiplier: ");
		String s2 = getValidString(in.nextLine());

		System.out.println(s+" x "+s2+" = "+multiply(s, s2)+".");
	}

	// if "s" isn't valid, nags the user until it is valid; returns the valid string
	public static String getValidString(String s)
	{
		while (!isValid(s))
		{
			System.out.print("Number invalid, enter another: ");
			s = in.nextLine();
		}

		return s;
	}

	// returns true if ALL the characters in "num" are integers
	public static boolean isValid(String num)
	{
		if (num.length() == 0)
			return false;

		for (int i = 0; i < num.length(); i++)
		{
			int j = num.charAt(i) - '0';

			if (!(j >= 0 && j <= 9)) // makes sure the character is betwee 0 and 9
				return false;
		}

		return true;
	}

	// removes the 0's if any are found at the beginning of "num"
	public static String noLeadingZeros(String num)
	{
		String result = num;

		for (int i = 0; i <= (num.length() - 2); i++)
		{
			if (num.charAt(i) == '0')
				result = num.substring(i + 1);
			else
				return result; // return as soon as the first non-zero integer is found
		}

		return result;
	}

	// adds the strings "a" and "b" together
	public static String add(String a, String b)
	{
		while (a.length() < b.length())
			a = "0" + a;

  		while (b.length() < a.length())
  			b = "0" + b;

		int carry = 0;
		String result = "";

		for (int i = (a.length() - 1); i >= 0; i--)
		{
			int aPlusB = (a.charAt(i) - '0') + (b.charAt(i) - '0') + carry;

			if (aPlusB > 9)
			{
				aPlusB -= 10; // subtract 10 so the carry can be calculated in the next loop
				carry = 1;
			}
			else
				carry = 0;

			char aPlusBRes = (char)(aPlusB + '0');
			result = (aPlusBRes + result);

			// if the last addition requires a carry, add it to the beginning
			if ((i == 0) && (carry == 1))
				result = '1' + result;
		}

		return result;
	}

	// multiplies the strings "a" and "b" - there is no length limit to "a" and "b"
	public static String multiply(String a, String b)
	{
		while (a.length() < b.length())
			a = "0" + a;

		while (b.length() < a.length())
			b = "0" + b;

		String sum = "";

		for (int i = 0; i < a.length(); i++)
			for (int j = 0; j < b.length(); j++)
			{
				String n = Integer.toString((a.charAt(i) - '0') * (b.charAt(j) - '0'));
				int numOfZeros = ((a.length() - 1) - i) + ((b.length() - 1) - j);

				for (int k = 1; k <= numOfZeros; k++)
				   n = n + "0";

				sum = add(sum, n);
			}

		return noLeadingZeros(sum);
	}
}