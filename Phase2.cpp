#include <iostream>
#include <fstream> //file handling
#include <string>
#include <ctype.h>
using namespace std;

char M[300][4];
char IR[4];
int IC;
char R[4];
bool C;
int PTR;
char buffer[40];
int EM;
int SI;
int TI;
int PI;
int RA, VA;
int all_pages[30];
fstream file1;
fstream file2;
int count = 0;
int PTE;
int pgnum;
bool error_occured;
int valid;
int term=0;
int dataerr=0;
void read();
void write();
void simulation();

struct ProcessControlBlock
{
    int jobid;
    int ttl; // time limit
    int ttc; // time counter
    int tll;
    int llc; // line limit counter
};
struct ProcessControlBlock pcb;

void init()
{
    {
        for (int i = 0; i < 300; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                M[i][j] = '\0';
            }
        }
        IR[0] = {'\0'};
        R[0] = {'\0'};
        C = false;
        pcb.llc=0;
        pcb.ttc=0;
        // error_occured=false;

        for (int i = 0; i < 30; i++)
        {
            all_pages[i] = 0;
        }

        // cout<<"Initialization"<<endl;
        // for(int i=0; i<100; i++){
        //         cout<<"M["<<i<<"]="<<M[i]<<endl;
        // }
    }
}

int addressmap(int VA);
int allocate();

void terminate(int EM)
{
    file2 << "\n\n";
    file2 << "Job Id   :" << pcb.jobid << "\n";
    switch (EM)
    {
    case 0:
        file2 << "Program executed successfully\n";
        file2 << "No Error\n";
        break;
    case 1:
        file2 << "Error Occured\n";
        file2 << "Out of Data\n";
        break;
    case 2:
        file2 << "Error Occured\n";
        file2 << "Line Limit Exceeded\n";
        break;
    case 3:
        file2 << "Error Occured\n";
        file2 << "Time Limit Exceeded\n";
        break;
    case 4:
        file2 << "Error Occured\n";
        file2 << "Operation Code Error\n";
        break;
    case 5:
        file2 << "Error Occured\n";
        file2 << "Operand Error\n";
        break;
    case 6:
        file2 << "Error Occured\n";
        file2 << "Invalid Page Fault\n";
    }
    file2 << "IC    :" << IC << endl;
    file2 << "IR    :";
    for(int i=0; i<4; i++) if(IR[i]!='\0') file2 << IR[i];
    file2<<endl;
    file2 << "SI    :" << SI << endl;
    file2 << "PI    :" << PI << endl;
    file2 << "TI    :" << TI << endl;
    file2 << "TLL   :" << pcb.tll << endl;
    file2 << "TTC   :" << pcb.ttc << endl;
    file2 << "LLC   :" << pcb.llc << endl;
    file2 << "TTL   :" << pcb.ttl << endl;
    file2 << "\n\n";
    term=1;
    SI = 0;
    PI = 0;
    TI = 0;

}

void mos()
{

    if (PI == 3 && TI == 0)
    {
        if(valid==1){
            cout << "Valid Page Fault: " << endl;

            pgnum = allocate();
            cout << "\nAllocated Page for Logical Page " << PTE%10<<": " << pgnum << endl;
            // cout<<endl<<"s"<<s<<endl<<"x:"<<x<<endl;

            M[PTE][0] = (pgnum / 10) + 48;
            M[PTE][1] = (pgnum % 10) + 48;
            // cout<<"M["<<PTR+count<<"][0]: "<<M[PTR+count][0]<<endl;

            //printing Page Table
            cout<<"Page Table"<<endl;
            for(int x=0; x<10; x++){
                cout<<"M["<<PTR+x<<"]="<<M[PTR+x][0]<<M[PTR+x][1]<<endl;
            }
            count++;
            PI = 0;
            cout << "IC: " << IC << endl;
            // IC++;
        }
        else{
            terminate(6);
        }
    }

    else if (PI == 2 && TI==0)
    {
        terminate(5);
    }

    else if (SI == 1 && TI == 0) // Read Mode
    {
        read();
    }

    else if (SI == 2 && TI == 0) // Write Mode
    {
        write();
    }
                                                                                                                                            
    else if (SI == 3 && TI == 0) // Terminate
    {
        terminate(0);
    }

    else if (PI == 1 && TI==0)
    {
        terminate(4);
    }

    else if (SI == 1 && TI == 2)
    {
        terminate(3);
    }  

    else if (SI == 2 && TI == 2)
    {
        write();
        terminate(3);
    } 

    else if (SI == 3 && TI == 2)
    {
        terminate(0);
    }  

    else if (PI == 1 && TI == 2)
    {
        terminate(3);
        terminate(4);
    }


    else if (PI == 2 && TI == 2)
    {
        terminate(3);
        terminate(5);
    }

    else if (PI == 3 && TI == 2)
    {
        terminate(3);
    }

}

void read()
{
    for (int i = 0; i <= 39; i++)
        buffer[i] = ' ';
    file1.getline(buffer, 40);

    //Out of data error
    if(buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D')
    {
        terminate(1);
        dataerr=1;
        return;
    }

    cout<<buffer[0]<<buffer[1]<<buffer[2]<<buffer[3]<<endl;
    int i = RA;
    cout << "RA is:" << RA << endl;
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
    cout << endl;
}

void write()
{
    pcb.llc+=1;
    //Line limit error
        if(pcb.llc>pcb.tll)
        {
            return terminate(2);
        }

    int i = RA;

    int stop = i + 9;
    for (i = RA; i <= stop; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (M[i][j] == '\0')
                continue;
            else
                // cout<<"M[i][j] = "<<M[i][j]<<endl;
                file2 << M[i][j];
        }
    }
    file2 << "\n";    
}

int addressmap(int VA)
{
    if (0 <= VA < 100)
    {
        PTE = PTR + (VA / 10);
        cout << "PTE IS " << PTE << endl;
        // cout<<endl<<"M[PTE][0] IS "<<M[PTE][0]<<endl;
        string s;
        s = M[PTE][0];
        cout << "M[" << PTE << "]=" << M[PTE][0] << M[PTE][1] << endl;

        if (M[PTE][0] == '\0')
        {
            PI = 3;
            mos();
        }
        else
        {

            s += M[PTE][1];
            int RA = stoi(s) * 10 + (VA % 10);
            cout << endl
                 << "RA is: " << RA << endl;
            if (0 <= RA < 300)
                return RA;
            else
            {
                PI = 2;
                mos();
            }
        }
    }
    else
    {
        PI = 2;
        mos();
    }
    return pgnum * 10;
}

void executeuserprogram()
{
    while (1)
    {
        term=0;
        RA = addressmap(IC);
        if (PI != 0)
            break;
        for (int i = 0; i < 4; i++) // Load in register
        {

            IR[i] = M[RA][i];
            cout << "IR[" << i << "]=" << IR[i] << endl;
        }

        if((M[RA][0]!='H') && (!isdigit(M[RA][2]) || !isdigit(M[RA][3])))
        {
            PI=2;
            mos();
        }


        cout << "IC: " << IC << endl;
        IC++;
        
        string s;
        s += IR[2];
        s += IR[3];

        // if ((int)s[0]>=48 && (int)s[0]<=57)
        // {
        //     //cout<<"Inside condition"<<endl;
        //     //cout<<(int)s[0]<<endl;
        //     VA = stoi(s);
        //     cout << "VA is: " << VA << endl;
        //     RA = addressmap(VA);
        // }
        
        if (IR[0] == 'G' && IR[1] == 'D') // GD
        {
            SI = 1;
            valid=1;
            if ((int)s[0]>=48 && (int)s[0]<=57)
            {
                //cout<<"Inside condition"<<endl;
                //cout<<(int)s[0]<<endl;
                VA = stoi(s);
                cout << "VA is: " << VA << endl;
                RA = addressmap(VA);
            }
            
            mos();
            simulation();
        }

        else if (IR[0] == 'P' && IR[1] == 'D') // PD
        {
            SI = 2;
            valid=0;
            if ((int)s[0]>=48 && (int)s[0]<=57)
            {
                //cout<<"Inside condition"<<endl;
                //cout<<(int)s[0]<<endl;
                VA = stoi(s);
                cout << "VA is: " << VA << endl;
                RA = addressmap(VA);
            }
            
            mos();
            simulation();

        }

        else if (IR[0] == 'H')
        {
            SI = 3;
            valid=0;
            mos();
            simulation();
            return;
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            //string s;
            // s += IR[2];
            // s += IR[3];
            // int i = stoi(s);
            valid=0;
            if ((int)s[0]>=48 && (int)s[0]<=57)
            {
                //cout<<"Inside condition"<<endl;
                //cout<<(int)s[0]<<endl;
                VA = stoi(s);
                cout << "VA is: " << VA << endl;
                RA = addressmap(VA);
            }
            
            for (int j = 0; j < 4; j++)
            {
                R[j] = M[RA][j];
                cout << "R[" << j << "]=" << R[j] << endl;
            }
            cout << endl;

            simulation();
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            valid=1;
            if ((int)s[0]>=48 && (int)s[0]<=57)
            {
                //cout<<"Inside condition"<<endl;
                //cout<<(int)s[0]<<endl;
                VA = stoi(s);
                cout << "VA is: " << VA << endl;
                RA = addressmap(VA);
            }
            
            for (int j = 0; j < 4; j++)
            {
                M[RA][j] = R[j];
                cout << "M[" << RA << "]["<<j<<"]="<< M[RA][j]<<endl;
            }
            cout << endl;

            simulation();
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            valid=0;
            if ((int)s[0]>=48 && (int)s[0]<=57)
            {
                //cout<<"Inside condition"<<endl;
                //cout<<(int)s[0]<<endl;
                VA = stoi(s);
                cout << "VA is: " << VA << endl;
                RA = addressmap(VA);
            }
            
            string s, s1, s2;
            // s += IR[2];
            // s += IR[3];
            // int i = stoi(s);
            // cout<<"M["<<i<<"]=";
            for (int j = 0; j < 4; j++)
            {
                s1 += M[RA][j];
                s2 += R[j];
            }
            if (s1 == s2)
            {
                C = true;
            }
            else
                C = false;
            cout << "C: " << C << endl;

            simulation();
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            valid=0;
            if ((int)s[0]>=48 && (int)s[0]<=57)
            {
                //cout<<"Inside condition"<<endl;
                //cout<<(int)s[0]<<endl;
                VA = stoi(s);
                cout << "VA is: " << VA << endl;
                RA = addressmap(VA);
            }
            if (C == true)
            {
                string s;
                s += IR[2];
                s += IR[3];
                IC = stoi(s);
                cout << "True\nIC = " << IC << endl;
            }

            simulation();
        }
        else{
                PI=1;
                SI=0;
                mos();          
        }
        if(term==1) return;  
   
    }
}

void startexecution()
{
    IC = 0;
    executeuserprogram();
}

int allocate()
{
    int pagenum;
    while (1)
    {
        pagenum = 0 + rand() % 29;
        if (all_pages[pagenum] == 0)
        {
            all_pages[pagenum] = 1;

            break;
        }
    }
    return pagenum;
}

void load()
{

    int m = 0;
    count = 0;
    while (!file1.eof())
    {
        for (int i = 0; i <= 39; i++) // clear buffer
            buffer[i] = '\0';

        file1.getline(buffer, 41);
        // cout<<buffer<<endl<<m<<endl;

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();
            pcb.jobid = 0;

            for (int counter = 4; counter < 8; counter++)
            {
                pcb.jobid = (buffer[4]-48)*1000+(buffer[5]-48)*100+(buffer[6]-48)*10+(buffer[7]-48);

            }
            pcb.ttl = 0;
            for (int counter = 8; counter < 12; counter++)
            {
                pcb.ttl = (buffer[8]-48)*1000+(buffer[9]-48)*100+(buffer[10]-48)*10+(buffer[11]-48);
            }
            pcb.tll = 0;
            for (int counter = 12; counter < 16; counter++)
            {
                pcb.tll = (buffer[12]-48)*1000+(buffer[13]-48)*100+(buffer[14]-48)*10+(buffer[15]-48);
            }
 
            PTR = allocate() * 10;
            cout << "\nAllocated Page is for Page Table: " << PTR / 10 << endl;
            cout << "Job ID : " << pcb.jobid << endl;
            cout << "Time Limit : " << pcb.ttl << endl;
            cout << "Line Limit : " << pcb.tll << endl;
            cout << "Time Counter : " << pcb.ttc << endl;
            cout << "Line Counter : " << pcb.llc << endl;
            continue;
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            cout << "Started Execution" << endl;
            startexecution();
            if (dataerr=1){
                m=0;
                count=0;
                dataerr=0;

            }
            continue;
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            m = 0;
            count = 0;
            continue;
        }
        else
        {

            PTE = allocate();
            cout << "\nAllocated Page for Page " << count << ": " << PTE << endl;
            // cout<<endl<<"s"<<s<<endl<<"x:"<<x<<endl;
            M[PTR + count][0] = (PTE / 10) + 48;
            M[PTR + count][1] = (PTE % 10) + 48;
            // cout<<"M["<<PTR+count<<"][0]: "<<M[PTR+count][0]<<endl;
            count++;

            int k = 0;
            m = PTE * 10;
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

        for (int x = 0; x < 300; x++)
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

void simulation()
{
    if(IR[0] == 'G' && IR[1] == 'D')
    {
        pcb.ttc+=2;
    }

    else if(IR[0] == 'P' && IR[1] == 'D')
    {
        pcb.ttc+=1;
    }

    else if(IR[0] == 'H')
    {
        pcb.ttc+=1;
    }

    else if(IR[0] == 'L' && IR[1] == 'R')
    {
        pcb.ttc+=1;
    }

    else if(IR[0] == 'S' && IR[1] == 'R')
    {
        pcb.ttc+=2;
    }

    else if(IR[0] == 'C' && IR[1] == 'R')
    {
        pcb.ttc+=1;
    }

    else if(IR[0] == 'B' && IR[1] == 'T')
    {
        pcb.ttc+=1;
    }

    //Time limit error

    if(pcb.ttc>pcb.ttl)
    {
        TI=2;
        mos();
    }
    
}

main()
{

    file1.open("input.txt");
    file2.open("output.txt");

    load();
    return 0;
}
