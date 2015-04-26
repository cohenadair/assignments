The Packet Sniffer Assignment
=============================

You get one point for each feature of a packet you can decode.  You get one point for every item listed below, and you can also get a point for any other interesting item you also discover.  I get final say to decide if something is interesting (but you can always ask).

This program is out of 25 points.

You can find the official decoding of every packet be doing a 
> tcpdump  -n -S -vvv -r /home/rappleto/pub/Classes/CS442/Assignments/PacketSniffer/packets.db  | less

-and-
> cat /home/rappleto/pub/Classes/CS442/Assignments/PacketSniffer/packets.txt


You get one point for everything you decode. Examples include:

- Ethernet source MAC address
- Ethernet dest MAC address
- Ethernet type
- Ethernet length
- Data
- If it's an IP packet
    - Source IP address
    - Source host name (if available)
    - Dest IP address
    - Dest host name (if available)
    - IP length
    - If the packet is padded.
- If it's TCP
    - Source port
    - Dest port
    - Sequence number
    - Ack number
    - Fin bit
    - ACK bit
    - Syn bit
    - Any text that might be in the packet body
- If it's UDP
    - Source port
    - Dest port
    - Any text that might be in the packet body
- If it's ICMP
- If it's an ARP packet
    - IP number of the question
- If it's an NET-BIOS packet

YOU MUST EXTRACT AT LEAST ONE BIT FIELD
YOU MUST USE AT LEAST ONE STRUCTURE OR UNION

You lose points for each of the following

Any code repeated more than twice (make a function).
Any enormous hard to understand methods (split them up).
Every wrong answer.
Every class day after Wed Jan 28th at 4pm.