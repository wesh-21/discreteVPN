#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/ip.h> // IP header structure
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in saddr;
    unsigned char *buffer = (unsigned char *)malloc(65535); // Large buffer for incoming packets

    // Create a raw socket that listens to all incoming packets
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sll_family = AF_PACKET;
    saddr.sll_protocol = htons(ETH_P_ALL);
    saddr.sll_ifindex = 0; // Bind to all interfaces

    // Bind socket to all local interfaces
    if (bind(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("Bind failed");
        close(sock);
        return 1;
    }

    while (1) {
        ssize_t data_size = recv(sock, buffer, 65535, 0); // Receive packets
        if (data_size < 0) {
            perror("Recv failed");
            continue;
        }

        printf("Received a packet of size %zd bytes\n", data_size);
    }

    close(sock);
    free(buffer);
    return 0;
}
