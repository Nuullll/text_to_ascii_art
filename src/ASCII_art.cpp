#include <fstream>
#include <iostream>
#include <cstdlib>

//Divide the interval(start,end) into n parts and calculate NO.t term...
inline int Interpolation(int start, int end, int n, int t)
{
    return start + t * (end - start) / n;
}

class character
{
public:
    character()
    {       //Set m to ' '
        for (int i = 0; i < 73; ++i)
        {
            for (int j = 0; j < 51; ++j)
            {
                m[i][j] = ' ';
            }
        }
    }
    

    void Set(int *pt_start, int *pt_end, int start_size, int end_size);
    //pt_start[0] is y-coordinate of start_line
    //pt_end[0] is y-coordinate of end_line
    void Display();

private:
    char m[73][51];     //73*50 size character
};

void character::Set(int *pt_start, int *pt_end, int pt_start_size, int pt_end_size)
{
    int pattern = 0;        //NOT Changing
    for (int i = 1; i < pt_start_size; ++i)
    {   
        if (pt_start[i] < 0)
        {
            pattern = -1;   //Changing smoothly from start_line to end_line
            break;
        }
    }
    
    char filler = '*';      //filler
    if (pattern == 0)       //0-pattern means: all lines are the same as the start_line, until reach the end_line.
    {
        int k = 1;
        while (k < pt_start_size && pt_start[k] >= 0)
        {
            for (int i = pt_start[k]; i < pt_start[k+1]; ++i)
            {
                m[pt_start[0]][i] = filler;
            }
            k += 2;         //every two points make an interval(pt_start[k],pt_start[k+1]) filled with filler
        }
        for (int i = pt_start[0] - 1; i > pt_end[0]; --i)
        {
            for (int j = 0; j < 51; ++j)
            {
                m[i][j] = m[pt_start[0]][j];    //all lines are the same as the start_line
            }
        }
    }
    if (pattern == -1)
    {
        int k = 1;
        while (k < pt_start_size && k < pt_end_size && pt_start[k] >= 0)
        {
            for (int i = pt_start[0]; i > pt_end[0]; --i)
            {
                for (int j = Interpolation(pt_start[k], pt_end[k], pt_start[0] - pt_end[0], pt_start[0] - i); 
                         j < Interpolation(pt_start[k+1], pt_end[k+1], pt_start[0] - pt_end[0], pt_start[0] - i); ++j)
                {
                    m[i][j] = filler;
                }
            }
            k += 2;
        }
    }
    return;
}

void character::Display()   //Display with cout
{
    for (int i = 72; i >= 0; --i)
    {
        for (int j = 0; j < 51; ++j)
        {
            std::cout << m[i][j];
        }
        std::cout << std::endl;
    }
}


int main(void)
{
    std::ifstream fin("FontData-A.txt");      //There are only parameters of character A... and are pure number...
    if (!fin.is_open())
    {
        std::cout << "Fail to load the file!" << std::endl;
        exit(1);
    }

    character A;

    while (true)
    {
    //get start array and end array.
        int start[10] = {0}, end[10] = {0};
        int start_size = 0, end_size = 0;
        int pos;

        while (fin && fin.peek() != '\n')
        {
            fin >> start[start_size];
            ++ start_size;
        }
        fin.get();              //get '\n'
        pos = fin.tellg();      //record position of last line
        while (fin && fin.peek() != '\n')
        {
            fin >> end[end_size];
            ++ end_size;
        }
        fin.get();              //get '\n'
        A.Set(start, end, start_size, end_size);
        if (end[0] == 0)        //if y-coordinate of end_line is zero, then break;
            break;
        fin.seekg(pos);         //move the read pointer to last line...
    }
    A.Display();                //Display...
    return 0;
}