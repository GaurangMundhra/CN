#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void calculateSubnetMask(int subnetBits, int subnetMask[])
{
    for (int i = 0; i < 4; i++)
    {
        if (subnetBits >= 8)
        {
            subnetMask[i] = 255;
            subnetBits -= 8;
        }
        else if (subnetBits > 0)
        {
            subnetMask[i] = 256 - (1 << (8 - subnetBits));
            subnetBits = 0;
        }
        else
        {
            subnetMask[i] = 0;
        }
    }
}

void printIP(int ip[])
{
    for (int i = 0; i < 4; i++)
    {
        printf("%d", ip[i]);
        if (i < 3)
            printf(".");
    }
    printf("\n");
}

char getIPClass(int firstOctet)
{
    if (firstOctet >= 1 && firstOctet <= 126) // -> Range of first octate
    {
        return 'A'; // Class
    }
    else if (firstOctet >= 128 && firstOctet <= 191)
    {
        return 'B';
    }
    else if (firstOctet >= 192 && firstOctet <= 223)
    {
        return 'C';
    }
    else
    {
        return 'X';
    }
}

void getDefaultSubnetMask(char ipClass, int subnetMask[]) // default subnet mask
{
    if (ipClass == 'A')
    {
        subnetMask[0] = 255;
        subnetMask[1] = 0;
        subnetMask[2] = 0;
        subnetMask[3] = 0;
    }
    else if (ipClass == 'B')
    {
        subnetMask[0] = 255;
        subnetMask[1] = 255;
        subnetMask[2] = 0;
        subnetMask[3] = 0;
    }
    else if (ipClass == 'C')
    {
        subnetMask[0] = 255;
        subnetMask[1] = 255;
        subnetMask[2] = 255;
        subnetMask[3] = 0;
    }
}

int main()
{
    char ipAddress[16];
    int subnetBits;
    int ip[4];
    int subnetMask[4];
    char ipClass;

    printf("Enter IP address : ");
    scanf("%s", ipAddress);
    sscanf(ipAddress, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

    ipClass = getIPClass(ip[0]);
    if (ipClass == 'X')
    {
        printf("Invalid or unsupported IP class!\n");
        return 1;
    }

    getDefaultSubnetMask(ipClass, subnetMask);

    printf("IP Class: %c\n", ipClass);
    printf("Default Subnet Mask: ");

    printIP(subnetMask);

    printf("Enter the number of subnet bits : ");
    scanf("%d", &subnetBits);

    calculateSubnetMask(subnetBits, subnetMask);

    printf("IP Address: ");
    printIP(ip);

    printf("Calculated Subnet Mask: ");
    printIP(subnetMask);

    return 0;
}

// A Subnet Mask is a 32-bit number used in computer networks to divide an IP address into network and host portions.
// It essentially tells the devices which part of the IP address refers to the network and which part refers to the specific device (host) within that network.
