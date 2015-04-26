//
//  PacketSniffer.c
//
//  Created by Cohen Adair on 29/01/2015.
//  CS442, Northern Michigan University
//
//  pcap.h http://www.opensource.apple.com/source/libpcap/libpcap-18/libpcap/pcap.h
//  pcap library guide http://www.tcpdump.org/pcap.html
//  pcap example http://euclid.nmu.edu/~rappleto/Classes/CS442/Assignments/PacketSniffer/pcap_simple.cc
//

#include "PacketSniffer.h"

int main(int argc, char *argv[]) {
	char errbuf[PCAP_ERRBUF_SIZE];
	char *device;
	pcap_t *handle;
	struct pcap_pkthdr pheader;
	const unsigned char *packet;
	int count = 1;
	/*
	device = pcap_lookupdev(errbuf);
	if (device == NULL) {
		cout << "Error reading device: " << errbuf << "." << endl;
		exit(ERR_NO_DEVICE);
	}
	*/
	//handle = pcap_open_live(device, PCAP_MAX_BYTES, true, 1000, errbuf);
	handle = pcap_open_offline(FILENAME, errbuf);
	if (handle == NULL) {
		cout << "Error getting handle: " << errbuf << endl;
		exit(ERR_NO_HANDLE);
	}
	
	while ((packet = pcap_next(handle, &pheader)) != NULL) {
		cout << "Packet #" << dec << count << endl;
		struct ether_sniff *ether = decode_ether(packet);
		unsigned short ethertype = ntohs(*(unsigned short *)(packet + ETHER_MAC_SIZE));
		
		if (ethertype == ETHERTYPE_IP4) {
			struct ip4_sniff *ip = decode_ip4(packet);
			if ((int)ip->protocol == IP_TCP)
				decode_tcp(packet, IP_IHL(ip) * 4);
		} else if (ethertype == ETHERTYPE_ARP) {
		} else if (ethertype == ETHERTYPE_IPX) {
		} else if (ethertype == ETHERTYPE_IP6) {
		} else {
			cout << "Unknown Ethertype: " << hex << ethertype << endl;
		}
		cout << endl;
		count++;
	}
	
	cout << "Received " << dec << count - 1 << " packets!" << endl;
	exit(0);
}

struct ip4_sniff *decode_ip4(const unsigned char *packet) {
	struct ip4_sniff *ip = (struct ip4_sniff *)(packet + ETHER_SIZE);
	print_ip4(ip);
	return ip;
}

void print_ip4(struct ip4_sniff *ip) {
	cout << "IP Header:" << endl;
	cout << "	Version:	" << dec << IP_VER(ip) << endl;
	cout << "	IHL:		" << IP_IHL(ip) << endl;
	cout << "	DSCP:		" << IP_DSCP(ip) << endl;
	cout << "	ECN:		" << IP_ECN(ip) << endl;
	cout << "  	Length:		" << ntohs(ip->len) << endl;
	cout << "  	ID:		" << ntohs(ip->id) << endl;
	cout << "  	RF:		" << ((ntohs(ip->flags_offset) & IP_RF) >> IP_SHR_RF) << endl;
	cout << "  	DFF:		" << ((ntohs(ip->flags_offset) & IP_DF) >> IP_SHR_DF) << endl;
	cout << "  	MFF:		" << ((ntohs(ip->flags_offset) & IP_MF) >> IP_SHR_MF) << endl;
	cout << "  	Offset:		" << (ntohs(ip->flags_offset) & IP_OFF) << endl;
	cout << "  	TTL:		" << (int)ip->time_to_live << endl;
	cout << "  	Protocol:	" << (int)ip->protocol << " - " << ip_protocol_str((int)ip->protocol) << endl;
	cout << "  	Checksum:	" << ntohs(ip->checksum) << endl;
	cout << "  	From:		" << inet_ntoa(ip->src) << endl;
	cout << "  	To:		" << inet_ntoa(ip->dst) << endl;
}

struct ether_sniff *decode_ether(const unsigned char *packet) {
	struct ether_sniff *ether = (ether_sniff *)(packet);
	print_ether(ether);
	return ether;
}

void print_ether(struct ether_sniff *ether) {
	cout << "Ethernet Header:" << endl;
	cout << "	From MAC:	" << ether_ntoa(&ether->src) << endl;
	cout << "	To MAC:		" << ether_ntoa(&ether->dst) << endl;
	cout << "	Type:		0x" << hex << ntohs(ether->type) << " - "<< ether_type_str(ntohs(ether->type)) <<  endl;
}

const char *ether_type_str(unsigned short type) {
	switch (type) {
		case ETHERTYPE_IP4: return "IPv4";
		case ETHERTYPE_IP6: return "IPv6";
		case ETHERTYPE_ARP: return "ARP";
		case ETHERTYPE_IPX: return "IPX";
		default: return "Unknown";
	}
}

const char *ip_protocol_str(unsigned char protocol) {
	switch (protocol) {
		case IP_TCP: return "TCP";
		case IP_UDP: return "UDP";
		case IP_ICMP: return "ICMP";
		default: return "Unknown";
	}
}

void decode_tcp(const unsigned char *packet, int ip_len) {
	struct tcp_sniff *tcp = (tcp_sniff *)(packet + ETHER_SIZE + ip_len);
	print_tcp(tcp);
}

void print_tcp(struct tcp_sniff *tcp) {
	cout << "TCP Header:" << endl;
	cout << "	From:		" << ntohs(tcp->src) << endl;
	cout << "	To:		" << ntohs(tcp->dst) << endl;
	cout << "	Seq. #:		" << ntohl(tcp->seq) << endl;
	cout << "	Ack. #:		" << ntohl(tcp->ack) << endl;
	cout << "	FIN:		" << (ntohs(tcp->data_flags) & TCP_FIN) << endl;
	cout << "	ACK:		" << ((ntohs(tcp->data_flags) & TCP_ACK) >> TCP_SHR_ACK) << endl;
	cout << "	SYN:		" << ((ntohs(tcp->data_flags) & TCP_SYN) >> TCP_SHR_SYN) << endl;
}
