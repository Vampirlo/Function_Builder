#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <stdlib.h>

using namespace std;

int main()
{
    int num = 0;
    int i = 1;
    cout << "Write number" << endl;
    cin >> num;

    string filename = "test.dat";

    char path[260];
    GetModuleFileNameA(NULL, path, 260); // полный путь к exe
    string s = path;
    cout << s << endl; 
    // нам нужно получить "(полный путь текстового файла)"
    // путь к exe файлу обрезаем до \n
    for (int i = s.length(); s[i] != '\\'; i--)
    {
        s.erase(i, 1);
    }
    // к обрезанной строке добавляем название файла, 
    s += filename;
    s.insert(0, string("\""));
    s.insert(s.length(), string("\""));

    ofstream file;
    file.open(filename, ios::trunc);

    if (!file.is_open())
    {
        cout << "ERROR file cant be found";
    }
    else
    {
        cout << "file successfully opened";
    }

    file << num << " " << i << endl;

    while (num > 1)
    {
        i++;
        if (num % 2 == 0)
        {
            num = num / 2;
        }
        else
        {
            num = num * 3 + 1;
        }

        file << num << " " << i << endl;
    }
    file.close();

    string linef = "gnuplot -p -e \"plot '";
    string lines = "' using 1:2 smooth csplines\"";

    string lf_and_Filename = linef + filename;
    string lf_and_Filename_and_ls = lf_and_Filename + lines;

    system(lf_and_Filename_and_ls.c_str());

    //system("gnuplot -p -e \"plot 'test.dat' using 1:2 smooth csplines\"");

	return 0;
}
