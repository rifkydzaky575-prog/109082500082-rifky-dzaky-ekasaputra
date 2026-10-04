#include <iostream>
using namespace std;

int main() {
    int nilai[3][3] = {
        {80, 85, 90},
        {75, 80, 85},
        {90, 95, 100}
    };

    cout << nilai[0][0] << endl; //80
    cout << nilai[1][1] << endl; //80
    cout << nilai[2][2] << " "; //100

    return 0;
}