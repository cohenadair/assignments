Homework 1 - Parse A Log File
=============================

You are given a log file showing the output of compiling a large program. The compilation is loaded with warning messages. You will write a Perl program that produces a report about this output. You will be expected to test this program into existence. You need to turn in not only the program, but the test case that tests its functions.

Implicit in this is that I will not favorably grade a script that is one run on piece of code. I expect lots of small functions that each do one things and are named accordingly. Further, I expect to see at least one test function for each function used by the script. An important aspect of a unit test, is that it shows the reader how to use the function, and what to expect in return. This is infinitely more useful than a comment.

A big lesson to learn, is that far too often the little throw away one time scripts you write, often become standard utilities. If it turns out later to be broken or unmaintainable, it will not reflect well on you as a programmer. So, always strive to write code that is understandable and maintainable.

Part of this program, is that you need to record only once a warning for a particular line in a file. Let perl do the work on this one. A hash table behaves like a set in mathematics. If you record an entry at a specific key, that key will be in the hash table only once. So the best and fastest way to get unique line numbers is not to code yet another algorithm, but instead to use the right data structure.

Your task
---------

Write a script that puts out a line of text for each source file of the form <count>:<file path>: <line number>+

### Input

src/ext/exThapi.c: In function ‘NBAPIGetThreadLevels’:
src/ext/exThapi.c:1250: warning: unused variable ‘poopTable’
src/ext/exThapi.c:1250: warning: unused variable ‘soopTable’
src/ext/exThapi.c:1250: warning: unused variable ‘nilOop’
src/ext/exThapi.c: In function ‘NBAPICallbackReturn’:
src/ext/exThapi.c:1462: warning: unused variable ‘soopTable’
src/ext/exThapi.c:1462: warning: unused variable ‘nilOop’

### Output

2: src/ext/exThapi.c: 1250, 1462