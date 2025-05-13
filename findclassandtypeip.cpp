#include <iostream>
#include <sstream>

using namespace std;

struct IPAddress
{
    unsigned char a, b, c, d;
};

bool isPrivateIP(const IPAddress &ip)
{
    return (ip.a == 10) ||
           (ip.a == 172 && (ip.b >= 16 && ip.b <= 31)) ||
           (ip.a == 192 && ip.b == 168);
}

bool isReservedIP(const IPAddress &ip)
{
    return (ip.a == 0) || (ip.a == 169 && ip.b == 254);
}

char getIPClass(const IPAddress &ip)
{
    if (ip.a >= 1 && ip.a <= 127)
        return 'A';
    if (ip.a >= 128 && ip.a <= 191)
        return 'B';
    if (ip.a >= 192 && ip.a <= 223)
        return 'C';
    if (ip.a >= 224 && ip.a <= 239)
        return 'D';
    if (ip.a >= 240 && ip.a <= 255)
        return 'E';
    return 'X';
}

bool isValidIP(const string &ip_string, IPAddress &ip)
{
    stringstream ss(ip_string);
    char dot;
    int a, b, c, d;

    if (!(ss >> a >> dot >> b >> dot >> c >> dot >> d) || !ss.eof() || dot != '.')
    {
        return false;
    }

    if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255)
    {
        return false;
    }

    ip = {static_cast<unsigned char>(a), static_cast<unsigned char>(b),
          static_cast<unsigned char>(c), static_cast<unsigned char>(d)};
    return true;
}

int main()
{
    string ip_string;
    IPAddress ip;

    cout << "Enter an IP address (IPv4): ";
    cin >> ip_string;

    if (!isValidIP(ip_string, ip))
    {
        cout << "Invalid IP address format." << endl;
        return 1;
    }

    char ip_class = getIPClass(ip);
    cout << "IP Class: " << ip_class << "\nType: ";

    if (isPrivateIP(ip))
    {
        cout << "Private" << endl;
    }
    else if (isReservedIP(ip))
    {
        cout << "Reserved" << endl;
    }
    else
    {
        cout << "Public" << endl;
    }

    return 0;
}

// An IP address is a 32-bit number, usually written in dotted-decimal notation like:

// Class A: 1–127

// Class B: 128–191

// Class C: 192–223

// Class D: 224–239 (Multicasting)

// 10.0.0.0 – 10.255.255.255 (Class A)

// 172.16.0.0 – 172.31.255.255 (Class B)

// 192.168.0.0 – 192.168.255.255 (Class C)