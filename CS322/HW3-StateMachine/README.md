Homework 3 - Scheme State Machine
=================================

Implement a state machine object in Scheme.

Implement a constructor function named make-dfa that takes one argument, a list of the following format:

(
        <list-of-state-specs>
        <list-of-input-letters>
        <name-of-start-state>
        <list-of-final-states>
)

<state-spec> ::= (<state-name> <assoc-list-of-transitions>)
It should produce a state machine object.

Consider a machine that recognizes even zeros in a string of 0s and 1s.

Ô(
	(
		(even ((0 . odd) (1 . even)))
		(odd    ((0 . even) (1 . odd)))
	)
	(0 1)
	even
	(even)
)