#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long int ll;

void transmission(ll *i, ll N, ll tf, ll *tt)
{
    while (*i <= tf)
    {
        int z = 0;
        for (ll k = *i; k < *i + N && k <= tf; k++)
        {
            printf("Sending Frame %lld...\n", k);
            (*tt)++;
        }

        for (ll k = *i; k < *i + N && k <= tf; k++)
        {
            int f = rand() % 2;
            if (!f)
            {
                printf("Acknowledgment for Frame %lld...\n", k);
                z++;
            }
            else
            {
                printf("Timeout!! Frame Number : %lld Not Received\n", k);
                printf("Retransmitting Window...\n");
                break;
            }
        }

        printf("\n");
        *i = *i + z;
    }
}

int main()
{
    ll tf, N, tt = 0;
    srand(time(NULL));

    printf("Enter the Total number of frames : ");
    scanf("%lld", &tf);
    printf("Enter the Window Size : ");
    scanf("%lld", &N);

    ll i = 1;
    transmission(&i, N, tf, &tt);

    printf("Total number of frames which were sent and resent are : %lld\n", tt);

    return 0;
}

// A Sliding Window Protocol is a method for reliable and efficient data transmission over unreliable or congested networks.

// It works like this:

// The sender can send multiple frames (up to the size of a "window") without waiting for an acknowledgment.

// If an acknowledgment (ACK) is received for a frame, the window slides forward.

// If a frame times out (lost or not acknowledged), the window slides back and resends frames starting from the lost one (in Go-Back-N) or just the lost frame (in Selective Repeat).

// Go back n
// Sender can send multiple frames up to a window size N without waiting for ACK.

// If a frame times out or is lost, all frames starting from that frame onwards in the window are resent.

// Window slides forward only when continuous ACKs are received.

// i — current frame number (passed by reference)

// N — window size

// tf — total number of frames

// tt — total frames sent or resent (passed by reference)