#include <iostream>
#include <iomanip>
using namespace std;

int countNonZeroRows(int **a, int i, int k, int n) {
    if (i >= k) {
        return 0;
    }

    bool hasZero = false;
    for (int j = 0; j < n; ++j) {
        if (a[i][j] == 0) {
            hasZero = true;
            break;
        }
    }

    int count = (hasZero ? 0 : 1);
    return count + countNonZeroRows(a, i + 1, k, n);
}

void Input(int **a, const int rowCount, const int colCount, int i, int j) {
    cout << "a[" << i << "][" << j << "] = ";
    cin >> a[i][j];
    if (j < colCount - 1)
        Input(a, rowCount, colCount, i, j + 1);
    else if (i < rowCount - 1) {
        cout << endl;
        Input(a, rowCount, colCount, i + 1, 0);
    }
    else
        cout << endl;
}

void Print(int **a, const int rowCount, const int colCount, int i, int j)
{
    cout << setw(4) << a[i][j];
    if (j < colCount - 1)
    {
        Print(a, rowCount, colCount, i, j + 1);
    }
    else
    {
        if (i < rowCount - 1)
        {
            cout << endl;
            Print(a, rowCount, colCount, i + 1, 0);
        }
        else
        {
            cout << endl
                 << endl;
        }
    }
}

void countElement(int **a, int k, int n, int element, int &count, int i, int j) {
    if (i < k) {
        if (j < n) {
            if (a[i][j] == element) {
                count++;
            }
            countElement(a, k, n, element, count, i, j + 1);
        } else {
            countElement(a, k, n, element, count, i + 1, 0);
        }
    }
}

void findMaxRepeated(int **a, int k, int n, int i, int j, int &maxRepeated, int &maxCount) {
    if (i < k) {
        if (j < n) {
            int element = a[i][j];
            int count = 0;
            countElement(a, k, n, element, count, 0, 0);

            if (count > 1 && element > maxRepeated) {
                maxRepeated = element;
                maxCount = count;
            }

            findMaxRepeated(a, k, n, i, j + 1, maxRepeated, maxCount);
        } else {
            findMaxRepeated(a, k, n, i + 1, 0, maxRepeated, maxCount);
        }
    }
}

int main() {
    int rowCount, colCount;

    cout << "Введіть кількість рядків: "; cin >> rowCount;
    cout << "Введіть кількість стовпців: "; cin >> colCount;

    int **a = new int *[rowCount];
    for (int i = 0; i < rowCount; ++i) {
        a[i] = new int[colCount];
    }

    Input(a, rowCount, colCount, 0, 0);
    Print(a, rowCount, colCount, 0, 0);

    cout << "Кількість рядків, що не містять жодного нульового елементу: " << countNonZeroRows(a, 0, rowCount, colCount) << endl;

    int maxRepeated = -1;
    int maxCount = 0;
    findMaxRepeated(a, rowCount, colCount, 0, 0, maxRepeated, maxCount);

    if (maxRepeated != -1) {
        cout << "Максимальне число, яке зустрічається більше одного разу: " << maxRepeated << endl;
        cout << "Кількість його зустрічей: " << maxCount << endl;
    } else {
        cout << "У матриці немає чисел, які зустрічаються більше одного разу." << endl;
    }

    for (int i = 0; i < rowCount; ++i) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
