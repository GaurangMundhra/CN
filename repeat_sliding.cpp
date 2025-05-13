#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // For sleep

using namespace std;

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

// Frame structure
struct Frame
{
    int seq_num;
    bool acknowledged;

    Frame(int num) : seq_num(num), acknowledged(false) {}
};

// Simulate sending a frame (50% success rate)
bool transmit()
{
    return rand() % 2; // Returns 0 or 1 randomly
}

// Sender side logic
void selectiveRepeatSender()
{
    vector<Frame> frames;
    for (int i = 0; i < TOTAL_FRAMES; ++i)
    {
        frames.emplace_back(i);
    }

    int base = 0;

    cout << "=== Selective Repeat Protocol Simulation ===\n";

    while (base < TOTAL_FRAMES)
    {
        // Send frames in window
        for (int i = 0; i < WINDOW_SIZE && (base + i) < TOTAL_FRAMES; ++i)
        {
            int idx = base + i;
            if (!frames[idx].acknowledged)
            {
                cout << "Sending Frame: " << frames[idx].seq_num << " ... ";
                if (transmit())
                {
                    cout << "Sent\n";
                }
                else
                {
                    cout << "Lost during transmission\n";
                }
            }
        }

        sleep(1); // Simulate network delay

        // Receive ACKs (simulate receiver behavior)
        for (int i = 0; i < WINDOW_SIZE && (base + i) < TOTAL_FRAMES; ++i)
        {
            int idx = base + i;
            if (!frames[idx].acknowledged)
            {
                if (transmit())
                {
                    frames[idx].acknowledged = true;
                    cout << "ACK received for Frame: " << frames[idx].seq_num << "\n";
                }
                else
                {
                    cout << "ACK lost for Frame: " << frames[idx].seq_num << "\n";
                }
            }
        }

        // Slide the window for all consecutive acknowledged frames
        while (base < TOTAL_FRAMES && frames[base].acknowledged)
        {
            base++;
        }

        cout << "Sliding window to base: " << base << "\n\n";
        sleep(1);
    }

    cout << "All frames transmitted and acknowledged successfully!\n";
}

int main()
{
    srand(time(0)); // Seed for random transmission simulation

    selectiveRepeatSender();

    return 0;
}

// A Sliding Window Protocol is a method of flow control in computer networks where:

// Both sender and receiver have a "window" of frames they can send/receive at a time.

// The window size determines how many frames can be sent without waiting for an acknowledgment.

// The window slides forward as acknowledgments are received.

// Selective Repeat Automatic Repeat reQuest (ARQ) is an error control protocol used in data transmission:

// The sender sends multiple frames at a time (window-based)

// The receiver acknowledges each correctly received frame individually

// If any frame is lost or corrupted, only that specific frame is resent, not the entire window (unlike Go-Back-N ARQ)