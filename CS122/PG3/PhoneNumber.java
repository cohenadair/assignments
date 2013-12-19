import java.io.*;
import java.util.*;

public class PhoneNumber
{
	private static Scanner in = new Scanner(System.in);

	// so the lengths can be changed easily
	final static int PHONE_LENGTH = 10;
	final static int NAME_LENGTH = 20;
	final static int RECORD_LENGTH = PHONE_LENGTH + NAME_LENGTH;

	public static void main (String[] args)	throws Exception
	{
		long[] loc = new long[2];

		System.out.print("Enter a file: ");
		RandomAccessFile file = new RandomAccessFile(in.nextLine(), "r");

		System.out.print("Enter a name: ");
		int searches = searchFile(file, in.nextLine(), loc);

		if (searches == -1)
			return;

		if (loc[0] <= loc[1])
			System.out.println("The phone number is "+getNumber(file, loc[0])+".");
		else
		{
			// at the start of the file
			if (loc[0] == 1 && loc[1] == 0)
				System.out.println("Record falls before "+getName(file, loc[0])+" and after the beginning of the file.");

			// in the middle of the file
			if (loc[0] <= (file.length() / RECORD_LENGTH) && loc[1] >= 1)
				System.out.println("Record falls before "+getName(file, loc[0])+" and after "+getName(file, loc[1])+".");

			// at the end of the file
			if (loc[0] > (file.length() / RECORD_LENGTH))
				System.out.println("Record falls after "+getName(file, loc[1])+" and before the end of the file.");
		}

		System.out.println("Searched through "+searches+" records.");
		file.close();
	}

	public static int searchFile (RandomAccessFile file, String name, long[] loc) throws Exception
	{
		// if the file is empty or has an invalid record
		if (file.length() == 0 || (file.length() % RECORD_LENGTH != 0))
		{
			System.out.println("Invalid file length.");
			return -1;
		}

		long l = 1, h = (file.length() / RECORD_LENGTH), t = 0;
		boolean found = false;
		int count = 0;

		while (l <= h && !found)
		{
			t = (l + h) / 2;
			String s = getName(file, t);

			count = count + 1;

			if (name.compareTo(s) < 0) // name comes before record
				h = t - 1;
			else if (name.compareTo(s) > 0) // name comes after record
				l = t + 1;
			else
				found = true;
		}

		if (found)
			loc[0] = loc[1] = t;
		else
		{
			loc[0] = l;
			loc[1] = h;
		}

		return count;
	}

	public static String getName(RandomAccessFile file, long loc) throws Exception
	{
		byte[] b = new byte[NAME_LENGTH];

		file.seek((loc - 1) * RECORD_LENGTH);
		file.readFully(b);

		String name = new String(b);
		name = name.trim();

		return name;
	}

	public static String getNumber(RandomAccessFile file, long loc) throws Exception
	{
		byte[] b = new byte [PHONE_LENGTH];

		file.seek((loc - 1) * RECORD_LENGTH + NAME_LENGTH);
		file.readFully(b);

		String number = new String(b);
		return number;
	}
}