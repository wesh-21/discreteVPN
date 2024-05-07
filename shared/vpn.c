#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/ip.h> // For IP headers (Network Layer)
#include <linux/if_ether.h> // Ethernet headers (Data Link Layer)
#include <arpa/inet.h> // For inet_addr

// Function to encapsulate packets
void encapsulate_packet(unsigned char *packet, int packet_len) {
    // Add GRE header
    // Send to Machine B
}

// Function to decapsulate packets
void decapsulate_packet(unsigned char *packet, int packet_len) {
    // Remove GRE header
    // Redirect to correct destination in machine A
}

int main() {
    int sock;
    unsigned char *buffer = malloc(65536); // Adjust size as necessary

    // Set up a raw socket
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));    //We use ETH_P_ALL to receive all packets
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Main loop to capture packets
    while (1) {
        int packet_len = recv(sock, buffer, 65536, 0);
        if (packet_len < 0) {
            perror("Failed to capture packets");
            continue;
        }

        // Determine if the packet is incoming or outgoing
        // Use IP headers to check source and destination

        // Call encapsulate or decapsulate
    }

    free(buffer);
    close(sock);
    return 0;
}
