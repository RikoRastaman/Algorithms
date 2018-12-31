#include <Windows.h>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    string fileName, str;
    cout << "Enter file name:";
    cin >> fileName;
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "File does not opened";
    }
    else
    {
        // fileName.getline()
        while (!file.eof())
        {
            getline(file, str);
            for (int i = 0; i < str.size(); i++)
            {
                cout << str[i];
            }
            // cout
            //     << str << endl;
        }
    }

    // int n = 1;
    // char *buffer = new char[n + 1];
    // buffer[n] = 0;

    // file.read(buffer, n);
    // while (!file.eof())
    // {

    //     cout << buffer;
    //     file.read(buffer, n);
    // }
    // delete[] buffer;
    // return 0;

    // char buff[50];
    // ifstream fin("test.txt");

    // fin.getline(buff, 50);
    // fin.close();
    // cout << buff << endl;

    // system("pause");
    // return 0;

    // ifstream file("test.txt");
    // int n = 255;
    // //Создаем буффер
    // char *buffer = new char[n + 1];
    // buffer[n] = 0;
    // file.get(buffer, n);
    // cout << buffer;
    // delete[] buffer;
}