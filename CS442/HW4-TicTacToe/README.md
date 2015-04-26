Homework 4 - RMI Game
=====================

**References:**

- [Bouncy ball game](http://euclid.nmu.edu/~rappleto/Classes/CS442/RMI/BouncyBallWithCallBack/)

**Requirements:**

1. Video game >= Tic Tac Toe
2. Real networking
3. Cross platform (2+ operating systems)
4. Use key/value store
5. Callbacks
6. Graphics

**Client Side:**

1. Implement interface
2. Export object
3. Set callback
4. Write callback method

**Server Side:**

1. Create callback/client array
2. On setCallBack, record pointer to client
3. On update, call clients

**Run Instructions:**

1. Install the latest Java
2. Use the VPN
3. Turn off the Windows firewall
4. Compile everything on UNIX and Windows

    javac *java

5. Generate all the stubs on the Unix side so the client can run

    rmic -keep Client
    rmic -keep RemoteObject

6. Copy stubs to Windows
7. Run the server

    java -Djava.security.policy=policy.txt Server

9. Run two applets on Windows

    appletviewer -J"-Djava.security.policy=policy.txt" Client.html

Due: Thursday, March 12th 2015.





