#include <iostream>
#include <string>
using namespace std;

int main()
{
    string data;
    int h[8];

    cout << "\n========================================\n";
    cout << "        HAMMING CODE (7,4)\n";
    cout << "========================================\n";

    // ---------------- TRANSMITTER SIDE ----------------
    cout << "\n----------- TRANSMITTER SIDE -----------\n";

    cout << "Enter 4-bit Data: ";
    cin >> data;

    if (data.length() != 4)
    {
        cout << "Invalid Input! Enter exactly 4 bits.\n";
        return 0;
    }


    h[3] = data[0] - '0';
    h[5] = data[1] - '0';
    h[6] = data[2] - '0';
    h[7] = data[3] - '0';

   
    h[1] = h[3] ^ h[5] ^ h[7];
    h[2] = h[3] ^ h[6] ^ h[7];
    h[4] = h[5] ^ h[6] ^ h[7];

    cout << "\nData Bits : " << data;

    cout << "\nGenerated Codeword : ";
    for (int i = 1; i <= 7; i++)
        cout << h[i];

    cout << "\nCodeword Sent Successfully!\n";

    // ---------------- RECEIVER SIDE ----------------
    cout << "\n----------- RECEIVER SIDE -----------\n";

   
    int r[8];

    for (int i = 1; i <= 7; i++)
        r[i] = h[i];

    char choice;

    cout << "Do you want to introduce an error? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        int pos;

        cout << "Enter bit position to flip (1-7): ";
        cin >> pos;

        if (pos >= 1 && pos <= 7)
            r[pos] = !r[pos];
    }

    cout << "\nReceived Codeword : ";
    for (int i = 1; i <= 7; i++)
        cout << r[i];

   
    int c1 = r[1] ^ r[3] ^ r[5] ^ r[7];
    int c2 = r[2] ^ r[3] ^ r[6] ^ r[7];
    int c4 = r[4] ^ r[5] ^ r[6] ^ r[7];

    int error = c4 * 4 + c2 * 2 + c1;

    if (error == 0)
    {
        cout << "\n\nNo Error Detected.\n";
    }
    else
    {
        cout << "\n\nError Detected at Position : "
             << error << endl;

       
        r[error] = !r[error];

        cout << "Corrected Codeword : ";

        for (int i = 1; i <= 7; i++)
            cout << r[i];

        cout << endl;
    }

    cout << "\nOriginal Data : ";
    cout << r[3] << r[5] << r[6] << r[7] << endl;

    cout << "\nProgram Executed Successfully.\n";

    return 0;
}
