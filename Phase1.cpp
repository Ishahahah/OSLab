#include <iostream>
#include <fstream> //file handling
#include <string>
using namespace std;

char M[100][4];
char IR[4];
int IC;
char R[4];
bool C;
char buffer[40];
int SI = 0;
fstream file1;
fstream file2;

void init()
{
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                M[i][j] = '\0';
            }
        }
        IR[0] = {'\0'};
        R[0] = {'\0'};
        C = false;

    }
}

void mos()
{
    if (SI == 1) // Read Mode
    {
        for (int i = 0; i <= 39; i++)
            buffer[i] = ' ';
        file1.getline(buffer, 40);
        string s;
        s += IR[2];
        s += IR[3];
        int i = stoi(s);
        int stop = i + 9;
        int k = 0;
        for (; i <= stop; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                M[i][j] = buffer[k];
                k++;
            }
            cout << "M[" << i << "]=" << M[i] << endl;
        }
    }

    else if (SI == 2) // Write Mode
    {

        string s;
        s += IR[2];
        s += IR[3];

        int i = stoi(s);
        // cout<<"i"<<i<<endl;
        int stop = i + 9;
        for (; i <= stop; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (M[i][j] == '\0')
                    continue;
                else
                    file2 << M[i][j];
            }
        }
        file2 << "\n";
    }

    else if (SI == 3) // Terminate
    {
        file2 << "\n";
        file2 << "\n";
    }
}

void executeuserprogram()
{
    while (1)
    // int count=10;
    // while(count--)
    {
        for (int i = 0; i < 4; i++) // Load in register
        {
            IR[i] = M[IC][i];
            cout << "IR[" << i << "]=" << IR[i] << endl;
        }
        cout << endl;
        IC++;

        if (IR[0] == 'G' && IR[1] == 'D') // GD
        {
            SI = 1;
            mos();
        }

        else if (IR[0] == 'P' && IR[1] == 'D') // PD
        {
            SI = 2;
            mos();
        }

        else if (IR[0] == 'H')
        {
            SI = 3;
            mos();
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            string s;
            s += IR[2];
            s += IR[3];
            int i = stoi(s);
            for (int j = 0; j < 4; j++)
            {
                R[j] = M[i][j];
                cout << "R[" << j << "]=" << R[j] << endl;
            }
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            string s;
            s += IR[2];
            s += IR[3];
            int i = stoi(s);
            cout << "M[" << i << "]=";
            for (int j = 0; j < 4; j++)
            {
                M[i][j] = R[j];
                cout << M[i][j];
            }
            cout << endl;
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            string s, s1, s2;
            s += IR[2];
            s += IR[3];
            int i = stoi(s);
            // cout<<"M["<<i<<"]=";
            for (int j = 0; j < 4; j++)
            {
                s1 += M[i][j];
                s2 += R[j];
            }
            if (s1 == s2)
            {
                C = true;
            }
            else
                C = false;
            cout << C << endl;
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C == true)
            {
                string s;
                s += IR[2];
                s += IR[3];
                IC = stoi(s);
            }
        }
        else
            break;
    }
}

void startexecution()
{
    IC = 0;
    executeuserprogram();
}

void load()
{

    int m = 0;
    while (!file1.eof())
    {
        for (int i = 0; i <= 39; i++) // clear buffer
            buffer[i] = '\0';

        file1.getline(buffer, 41);
        cout << buffer << endl
             << m << endl;

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();
            continue;
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            startexecution();
            continue;
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            m = 0;
            continue;
        }
        else
        {
            int k = 0;

            int stop = m + 10;
            for (; m < stop; m++)
            {
                for (int j = 0; j < 4; j++)
                {

                    M[m][j] = buffer[k];
                    k++;
                }
            }
        }
        for (int x = 0; x < 100; x++)
        {
            cout << "M[" << x << "]: ";
            for (int y = 0; y < 4; y++)
            {
                cout << M[x][y];
            }
            cout << endl;
        }
    }
}

main()
{

    file1.open("input.txt");
    file2.open("output.txt");
    load();
    return 0;
}
