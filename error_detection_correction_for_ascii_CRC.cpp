#include <iostream>
using namespace std;

int main()
{
    int fs, gs;

    // Input Frame Size
    cout << "\nEnter Frame size: ";
    cin >> fs;
    if (fs <= 0 || fs > 20)
    {
        cout << "\nInvalid frame size. Please enter a size between 1 and 20.";
        return 1;
    }

    // Input Frame (Binary)
    int f[20];
    cout << "\nEnter Frame (only 0s and 1s): ";
    for (int i = 0; i < fs; i++)
    {
        cin >> f[i];
        if (f[i] != 0 && f[i] != 1)
        {
            cout << "\nInvalid input. Enter only binary values (0 or 1).";
            return 1;
        }
    }

    // Input Generator Size
    cout << "\nEnter Generator size: ";
    cin >> gs;
    if (gs <= 0 || gs > 20)
    {
        cout << "\nInvalid generator size. Please enter a size between 1 and 20.";
        return 1;
    }

    // Input Generator Polynomial (Binary)
    int g[20];
    cout << "\nEnter Generator (only 0s and 1s): ";
    for (int i = 0; i < gs; i++)
    {
        cin >> g[i];
        if (g[i] != 0 && g[i] != 1)
        {
            cout << "\nInvalid input. Enter only binary values (0 or 1).";
            return 1;
        }
    }
    if (g[0] != 1)
    {
        cout << "\nInvalid generator. The first bit must be 1.";
        return 1;
    }

    // Append Zero Bits for CRC Calculation
    int rs = gs - 1;
    cout << "\nNumber of 0's to be appended: " << rs;
    for (int i = fs; i < fs + rs; i++)
    {
        f[i] = 0;
    }

    // Copy Frame for Division
    int temp[20];
    for (int i = 0; i < 20; i++)
    {
        temp[i] = f[i];
    }

    // Perform CRC Division (XOR Method)
    for (int i = 0; i < fs; i++)
    {
        if (temp[i] == 1)
        {
            for (int j = 0, k = i; j < gs; j++, k++)
            {
                temp[k] = (temp[k] == g[j]) ? 0 : 1;
            }
        }
    }

    // Extract CRC Bits
    int crc[15];
    for (int i = 0, j = fs; i < rs; i++, j++)
    {
        crc[i] = temp[j];
    }

    // Display CRC
    cout << "\nCRC bits: ";
    for (int i = 0; i < rs; i++)
    {
        cout << crc[i];
    }

    // Transmitted Frame = Original Frame + CRC
    int tf[20];
    for (int i = 0; i < fs; i++)
    {
        tf[i] = f[i];
    }
    for (int i = fs, j = 0; i < fs + rs; i++, j++)
    {
        tf[i] = crc[j];
    }

    // Display Transmitted Frame
    cout << "\nTransmitted Frame: ";
    for (int i = 0; i < fs + rs; i++)
    {
        cout << tf[i];
    }

    // Receiver Input (Simulating Possible Transmission Errors)
    int rf[20];
    cout << "\n\nReceiver Side - Enter Received Frame (including CRC bits, only 0s and 1s): ";
    for (int i = 0; i < fs + rs; i++)
    {
        cin >> rf[i];
        if (rf[i] != 0 && rf[i] != 1)
        {
            cout << "\nInvalid input. Enter only binary values (0 or 1).";
            return 1;
        }
    }

    // Copy Received Frame for CRC Checking
    for (int i = 0; i < fs + rs; i++)
    {
        temp[i] = rf[i];
    }

    // Perform CRC Division on Received Frame
    for (int i = 0; i < fs; i++)
    {
        if (temp[i] == 1)
        {
            for (int j = 0, k = i; j < gs; j++, k++)
            {
                temp[k] = (temp[k] == g[j]) ? 0 : 1;
            }
        }
    }

    // Extract Remainder
    int rrem[15];
    cout << "\nRemainder after division: ";
    bool errorDetected = false;
    for (int i = fs, j = 0; i < fs + rs; i++, j++)
    {
        rrem[j] = temp[i];
        cout << rrem[j];
        if (rrem[j] != 0)
        {
            errorDetected = true;
        }
    }

    // Error Checking
    if (!errorDetected)
    {
        cout << "\nSince Remainder is 0, the message is CORRECT!";
    }
    else
    {
        cout << "\nSince Remainder is NOT 0, the message contains an ERROR!";
    }

    return 0;
}

// Cyclic Redundancy Check (CRC) is an error-detecting code used to detect accidental changes to raw data in digital networks and storage.

// It works by:

// Appending zeros to the frame (equal to degree of generator polynomial)

// Performing binary division (modulo-2) of the frame by the generator.

// The remainder becomes the CRC bits.

// At receiver end, same division is done — if remainder is 0 → no error, else error.

// CRC is widely used because it’s simple, fast, and reliable for detecting burst errors.

// 11001
// 101