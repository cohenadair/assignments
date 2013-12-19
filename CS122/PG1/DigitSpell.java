/**
 * AUTHOR: Cohen Adair
 * DATE: 06/09/2012
 *
 * This program will ask for the user to unput a random string. If one of the
 * characters in the string is a number, it will return the number in written
 * form.
 *
 * 		Example: If you input: 5 + 3 = 8
 *				 It will print: FIVE + THREE = EIGHT
 *
 */

import java.util.*;

public class DigitSpell
{
	public static Scanner in = new Scanner(System.in);

 	public static void main (String[] args)
 	{
		System.out.print("Enter a line of text: ");
		String inputString = in.nextLine();

		String newString = "";

		char[] inputNumbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
		String[] fullNumbers = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};

		// loops through the input characters, checking to see if they're numbers
		for (int i = 0; i <= (inputString.length() - 1); i++)
		{
			char s = inputString.charAt(i);

			if (inputNumbers.length == fullNumbers.length) // results in error if array lengths are different
				for (int j = 0; j <= (inputNumbers.length - 1); j++)
				{
					if (s == inputNumbers[j])
					{
						System.out.print(fullNumbers[j]);
						break;
					} else
						if (j == (inputNumbers.length - 1)) // to make sure it compares all characters in inputChars before printing s
							System.out.print(s);
				}
		}

		System.out.println(newString);
 	}
}