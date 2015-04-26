Homework 3 - RMI Introduction
=============================

References
----------
- http://euclid.nmu.edu/~rappleto/Classes/CS442/RMI/howto-start.html

Assignment
----------

Your mission is to make a key/value store. It should implement the following methods:

**void store(String name, String value)**
Stores the name in the database with the value. If the name does not yet exist, create it. If the name does exist, this is the replacement.

**String read(String name)**
Returns the previous value associated with name. If there is no such value, return the null string.

**void delete(String name)** 
Deletes the name/value pair if it exists.

**boolean exists(String name)**
Returns true/false if the name is in the database.
	
One point for each item. Due Thursday when we get back from break.
