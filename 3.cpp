#include <iostream>
#include <cmath>
using namespace std;

int main()
{
int ip1, ip2, ip3, ip4;
int prefix;
char dot;

cout << "Enter IPv4 Address (e.g. 192.168.10.0): ";
cin >> ip1 >> dot >> ip2 >> dot >> ip3 >> dot >> ip4;

cout << "Enter Prefix (e.g. 24): ";
cin >> prefix;

if (prefix < 1 || prefix > 30)
{
cout << "Invalid Prefix!" << endl;
return 0;
}

string ipClass;

if (ip1 >= 1 && ip1 <= 126)
ipClass = "Class A";
else if (ip1 >= 128 && ip1 <= 191)
ipClass = "Class B";
else if (ip1 >= 192 && ip1 <= 223)
ipClass = "Class C";
else if (ip1 >= 224 && ip1 <= 239)
ipClass = "Class D";
else
ipClass = "Class E";

int hostBits = 32 - prefix;
int totalIPs = pow(2, hostBits);
int usableHosts = totalIPs - 2;

unsigned int subnetMask = 0xFFFFFFFF << (32 - prefix);

int mask1 = (subnetMask >> 24) & 255;
int mask2 = (subnetMask >> 16) & 255;
int mask3 = (subnetMask >> 8) & 255;
int mask4 = subnetMask & 255;

cout << "\n========== IPV4 DETAILS ==========\n";

cout << "IP Address : "
<< ip1 << "." << ip2 << "." << ip3 << "." << ip4 << endl;

cout << "CIDR Prefix : /" << prefix << endl;

cout << "IP Class : " << ipClass << endl;

cout << "Subnet Mask : "
<< mask1 << "."
<< mask2 << "."
<< mask3 << "."
<< mask4 << endl;

cout << "Total IP Addresses: "
<< totalIPs << endl;

cout << "Usable Hosts : "
<< usableHosts << endl;

cout << "\nIP Range: ";

if (ipClass == "Class A")
cout << "1.0.0.0 - 126.255.255.255";
else if (ipClass == "Class B")
cout << "128.0.0.0 - 191.255.255.255";
else if (ipClass == "Class C")
cout << "192.0.0.0 - 223.255.255.255";
else
cout << "Not Available";

cout << endl;

unsigned int ip =
(ip1 << 24) |
(ip2 << 16) |
(ip3 << 8) |
ip4;

unsigned int network = ip & subnetMask;
unsigned int broadcast = network | (~subnetMask);

cout << "\nNetwork Address : "
<< ((network >> 24) & 255) << "."
<< ((network >> 16) & 255) << "."
<< ((network >> 8) & 255) << "."
<< (network & 255) << endl;

cout << "First Host : "
<< ((network >> 24) & 255) << "."
<< ((network >> 16) & 255) << "."
<< ((network >> 8) & 255) << "."
<< ((network & 255) + 1) << endl;

cout << "Last Host : "
<< ((broadcast >> 24) & 255) << "."
<< ((broadcast >> 16) & 255) << "."
<< ((broadcast >> 8) & 255) << "."
<< ((broadcast & 255) - 1) << endl;

cout << "Broadcast Address: "
<< ((broadcast >> 24) & 255) << "."
<< ((broadcast >> 16) & 255) << "."
<< ((broadcast >> 8) & 255) << "."
<< (broadcast & 255) << endl;

return 0;
}
