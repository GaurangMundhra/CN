#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FRAMES 10 // Maximum packets (frames) that can be handled is 10

struct frame
{
    char ack; // to store whether a packet is acknowledged ('y' for yes, 'n' for no)
    int data; // integer data of the packet
} frm[MAX_FRAMES];

int n; // Number of packets
int r; // Index of randomly 'lost' packet

int sender(void);
// Takes number of packets from user.

// Reads data for each packet.

// Sets their initial acknowledgment status to 'y' (assuming they’re received correctly).

void recvack(void);
// Randomly selects one of the sent frames (using rand() % n) to simulate a lost or corrupted frame.

// Sets its ack to 'n'

// Prints out which packet was not received.

void resend(void);

int main()
{
    printf("Selective Repeat ARQ Simulation\n");
    sender();
    recvack();
    resend();
    printf("\nAll packets processed successfully\n");

    return 0;
}

int sender()
{
    printf("\nEnter the number of packets to be sent: ");
    scanf("%d", &n);

    if (n > MAX_FRAMES)
    {
        printf("The maximum number of packets is %d\n", MAX_FRAMES);
        n = MAX_FRAMES;
    }

    for (int i = 0; i < n; i++)
    {
        printf("Enter data for packet[%d]: ", i + 1);
        scanf("%d", &frm[i].data);
        frm[i].ack = 'y';
    }
    return 0;
}

void recvack()
{
    r = rand() % n;
    frm[r].ack = 'n';

    for (int i = 0; i < n; i++)
    {
        if (frm[i].ack == 'n')
        {
            printf("\nThe packet number %d is not received\n", r + 1);
        }
    }
}

void resend()
{
    printf("\nResending packet %d...\n", r + 1);
    sleep(2);
    frm[r].ack = 'y';
    printf("The received packet is %d\n", frm[r].data);
}

// A Sliding Window Protocol is a method of flow control in computer networks where:

// Both sender and receiver have a "window" of frames they can send/receive at a time.

// The window size determines how many frames can be sent without waiting for an acknowledgment.

// The window slides forward as acknowledgments are received.

// Selective Repeat Automatic Repeat reQuest (ARQ) is an error control protocol used in data transmission:

// The sender sends multiple frames at a time (window-based)

// The receiver acknowledges each correctly received frame individually

// If any frame is lost or corrupted, only that specific frame is resent, not the entire window (unlike Go-Back-N ARQ)