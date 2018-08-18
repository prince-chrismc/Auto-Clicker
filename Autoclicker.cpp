#include <windows.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    start:

    SetConsoleTitle("AutoClicker");
    int x, y, clicks, sleep;
    int done = 0;
    long int clicksleft, etc_ms;
    float etc_min;
    string choice;

    cout << "AutoClicker";
    cout << endl << "Version 0.0" << endl;

    cout << endl << "How Many clicks Would You Like To Click: ";
    cin >> clicks;

    cout << endl << "How Much Time Should I Wait Inbetween Clicks (MS): ";
    cin >> sleep;

    cout << endl << "Starting in 3...";
    Sleep(1000);
    cout << endl << "Starting in 2...";
    Sleep(1000);
    cout << endl << "Starting in 1...";
    Sleep(1000);
    cout << endl << "In Progress...";

    while (done < clicks)
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
        done++;

        COORD c;
        c.X = 0;
        c.Y = 11;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, c);

        clicksleft = (int)clicks - (int)done ;
        if(clicksleft == 0)
        {
            etc_ms = 0;
        }
        else
        {
            etc_ms = ((long int)clicksleft + 1) * (int)sleep;
        }
        etc_min = (long int)etc_ms / 60000.0;
        cout << endl << "Clicks remaining: " << (long int)clicksleft << ".                ";
        cout << endl << "Duration till end (ms): " << (long int)etc_ms << ".               ";
        cout << endl << "Duration till end (min): " << (float)etc_min << ".               ";

        Sleep(sleep);
    }

    cout << endl << endl << "AutoClicker Finished.";
    cout << endl << endl << "(y/n) Again: ";
    cin >> choice;
    if (choice == "y")
    {
        system("cls");
        goto start;
    }
    cin.get();
}
