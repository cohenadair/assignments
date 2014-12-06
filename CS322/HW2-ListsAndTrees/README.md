Homework 2 - Scheme Functions
=============================

(pick n lst) 
	return the nth item from a list
	if n > size of list, return Ô()

(my-reverse lst) 
	return a list that has the same elements as lst, in reverse order

(deep-reverse lst) 
	return a list that has all elements in reverse order, even in sub lists

(frontier tree) 
	return a list of the leaves of tree in order

Example:
(frontier (cons (cons 1 (cons 2 3)) (cons (cons 4 5) (cons 6 (cons 7 8)))))
	should return
( 1 2 3 4 5 6 7 8 )