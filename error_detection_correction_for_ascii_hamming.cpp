#include <iostream>
using namespace std;

int main()
{
    int data[12], received[12], p1, p2, p4, p8, i, pos;

    cout << "Enter 7-bit ASCII data one by one (LSB first): ";

    // Taking 7-bit ASCII input into data[] leaving parity bit positions (1, 2, 4, 8)
    cin >> data[11]; // D7
    cin >> data[10]; // D6
    cin >> data[9];  // D5
    cin >> data[7];  // D4
    cin >> data[6];  // D3
    cin >> data[5];  // D2
    cin >> data[3];  // D1

    // Calculate Parity Bits using Hamming Code (even parity)
    data[1] = data[3] ^ data[5] ^ data[7] ^ data[9] ^ data[11];  // P1
    data[2] = data[3] ^ data[6] ^ data[7] ^ data[10] ^ data[11]; // P2
    data[4] = data[5] ^ data[6] ^ data[7];                       // P4
    data[8] = data[9] ^ data[10] ^ data[11];                     // P8

    cout << "\nEncoded Data (with parity bits): ";
    for (i = 1; i <= 11; i++)
        cout << data[i];

    // Simulating Transmission
    cout << "\n\nEnter received data bits (one by one):\n";
    for (i = 1; i <= 11; i++)
        cin >> received[i];

    // Recalculate parity to detect errors
    p1 = received[1] ^ received[3] ^ received[5] ^ received[7] ^ received[9] ^ received[11];
    p2 = received[2] ^ received[3] ^ received[6] ^ received[7] ^ received[10] ^ received[11];
    p4 = received[4] ^ received[5] ^ received[6] ^ received[7];
    p8 = received[8] ^ received[9] ^ received[10] ^ received[11];

    // Calculate error position
    pos = p8 * 8 + p4 * 4 + p2 * 2 + p1 * 1;

    if (pos == 0)
    {
        cout << "\nNo error detected!";
    }
    else
    {
        cout << "\nError detected at position: " << pos;
        received[pos] = (received[pos] == 0) ? 1 : 0; // Correct error

        cout << "\nCorrected Data: ";
        for (i = 1; i <= 11; i++)
            cout << received[i];
    }

    cout << "\n";

    return 0;
}

// Hamming Code is an error-detecting and error-correcting code developed by Richard Hamming.
// It uses parity bits placed at positions which are powers of 2 (1, 2, 4, 8…) to detect and correct single-bit errors in data transmission.

// For example:

// Data bits are placed at positions not occupied by parity bits.

// Each parity bit covers certain positions based on binary position indexing.
// --

// The user enters 11 bits of ASCII data (as bits 1 or 0), starting from least significant bit first (LSB).

// Data bits are stored in an array data[1..15] leaving spots at positions 1, 2, 4, 8 for parity bits.

// In the case of even parity, for a given set of bits, the number of 1’s are counted. If that count is odd, the parity bit value is set to 1, making the total count of occurrences of 1’s an even number. If the total number of 1’s in a given set of bits is already even, the parity bit’s value is 0.

// In the case of odd parity, for a given set of bits, the number of 1’s are counted. If that count is even, the parity bit value is set to 1, making the total count of occurrences of 1’s an odd number. If the total number of 1’s in a given set of bits is already odd, the parity bit’s value is 0.

// i/p -> 1 0 0 1 1 0 1
// 1 0 1 0 0 1 0 1 0 0 1 -> check i/p