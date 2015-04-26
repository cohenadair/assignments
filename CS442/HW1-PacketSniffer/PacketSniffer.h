//
//  PacketSniffer.h
//
//  Created by Cohen Adair on 29/01/2015.
//  CS442, Northern Michigan University
//

#ifndef PACKET_SNIFFER
#define PACKET_SNIFFER

using namespace std;

// for testing
const char *FILENAME = "packets.db";

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <stdbool.h>
#include <pcap.h>
#include <iostream>

#define ETHER_MAC_SIZE 12
#define ETHER_SIZE 14
#define ETHERTYPE_IP4 0x0800 // IPv4
#define ETHERTYPE_IP6 0x86dd // IPv6
#define ETHERTYPE_ARP 0x0806 // Address Resolution Protocol
#define ETHERTYPE_IPX 0x8137 // Internetwork Packet Exchange

#define IP_RF 0x8000
	#define IP_SHR_RF 15
#define IP_DF 0x4000
	#define IP_SHR_DF 14
#define IP_MF 0x2000
	#define IP_SHR_MF 13
#define IP_OFF 0x1fff
#define IP_TCP 6
#define IP_UDP 17
#define IP_ICMP 1

#define TCP_FIN 0x0001
#define TCP_SYN 0x0002
	#define TCP_SHR_SYN 1
#define TCP_ACK 0x0010
	#define TCP_SHR_ACK 4

#define PCAP_MAX_BYTES 4

#define ERR_NO_DEVICE 1
#define ERR_NO_HANDLE 2

struct ip4_sniff {
	unsigned char v_ihl;			
	unsigned char dscp_ecn;		
	unsigned short len;
	unsigned short id;
	unsigned short flags_offset;		// Flags and Fragment Offset
	unsigned char time_to_live;	
	unsigned char protocol;
	unsigned short checksum;			// Header Checksum
	in_addr src;						// Source IP
	in_addr dst;						// Destination IP
};
#define IP_IHL(ip)	(((ip)->v_ihl) & 0x0f)
#define IP_VER(ip)	(((ip)->v_ihl) >> 4)
#define IP_DSCP(ip)	(((ip)->dscp_ecn) >> 2)
#define IP_ECN(ip)	(((ip)->dscp_ecn) & 0x03)		

struct ether_sniff {
	ether_addr dst;
	ether_addr src;
	unsigned short type;
};

struct tcp_sniff {
	unsigned short src;					// Source Port
	unsigned short dst;					// Destination Port
	unsigned int seq;					// Sequence Number
	unsigned int ack;					// Acknowledgement Number
	unsigned short data_flags;
};

int main(int argc, char *argv[]);
struct ip4_sniff *decode_ip4(const unsigned char *packet);
void print_ip4(struct ip4_sniff *ip);
struct ether_sniff *decode_ether(const unsigned char *packet);
void print_ether(struct ether_sniff *ether);
const char *ether_type_str(unsigned short type);
const char *ip_protocol_str(unsigned char protocol);
void decode_tcp(const unsigned char *packet, int ip_len);
void print_tcp(struct tcp_sniff *tcp);

#endif
