. #include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double getY(double x)
{
    return (pow(x, 2) / 4 + x / 2 + 1) * exp(x / 2);

}

double getSum(double x, int n)
{
    double sum = 0;
    double fact = 1;
    double powX = 1;
    for (long int k = 0; k <= n; k++)
    {
        sum += (pow(k, 2) + 1.0) / fact * powX;
        fact *= k + 1;
        powX *= x / 2;
    }
    return sum;
}

void drawTable(double a, double b, double h, int n, double getSum(double x, int n), double getY(double x))
{
    int k = 1;
    cout << setw(10) << "Number" << setw(15) << "Y(x)" << setw(15) << "Sum(x)" << setw(20) << "Difference" << endl;
    for (double x = a; x <= b; x += h) {
        double y = getY(x);
        double sum = getSum(x, n);
        double difference = abs(sum - y);
        cout << setw(10) << k << setw(15) << y << setw(15) << sum << setw(20) << difference << endl;
        k++;
    }
}


int main()
{

    double a, b, h;
    int n;

    cout << "Enter A: ";
    cin >> a;
    cout << "Enter B: ";
    cin >> b;
    cout << "Enter H: ";
    cin >> h;
    cout << "Enter N ";
    cin >> n;



    drawTable(a, b, h, n, getSum, getY);


    system("pause");
    return 0;
}
