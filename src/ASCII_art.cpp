#include <fstream>
#include <iostream>
#include <cstdlib>
#define HeightRatio 1
#define WidthRatio 1.4

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
        for (int i = 0; i < HeightRatio * 73; ++i)
            for (int j = 0; j < WidthRatio * 51; ++j)
                m[i][j] = ' ';
    }
    

    void Set(int pt_start[10], int pt_end[10]);
    //pt_start[0] is y-coordinate of start_line
    //pt_end[0] is y-coordinate of end_line
    //line size does not include non-data zeros
    //array[9] is line size
    void Display();

private:
    char m[int(HeightRatio * 73) + 1][int(WidthRatio * 51) + 1];     //73*HeightRatio * 50*WidthRatio size character
};

void character::Set(int pt_start[10], int pt_end[10])
{
    int pattern = 0;        //NOT Changing
    for (int i = 1; i < pt_start[9]; ++i)
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
        while (k < pt_start[9] && pt_start[k] >= 0)
        {
            for (int i = WidthRatio * pt_start[k]; i < WidthRatio * pt_start[k+1]; ++i)
            {
                m[pt_start[0]][i] = filler;
            }
            k += 2;         //every two points make an interval(pt_start[k],pt_start[k+1]) filled with filler
        }
        for (int i = HeightRatio * (pt_start[0] - 1); i > HeightRatio * pt_end[0]; --i)
        {
            for (int j = 0; j < WidthRatio * 51; ++j)
            {
                m[i][j] = m[pt_start[0]][j];    //all lines are the same as the start_line
            }
        }
    }
    if (pattern == -1)
    {
        int k = 1;
        while (k < pt_start[9] && k < pt_end[9] && pt_start[k] >= 0)
        {
            for (int i = HeightRatio * pt_start[0]; i > HeightRatio * pt_end[0]; --i)
            {
                for (int j = WidthRatio * Interpolation(pt_start[k], pt_end[k], pt_start[0] - pt_end[0], pt_start[0] - i); 
                         j < WidthRatio * Interpolation(pt_start[k+1], pt_end[k+1], pt_start[0] - pt_end[0], pt_start[0] - i); ++j)
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
    for (int i = HeightRatio * 72; i >= 0; --i)
    {
        for (int j = 0; j < WidthRatio * 51; ++j)
        {
            std::cout << m[i][j];
        }
        std::cout << std::endl;
    }
}

void Load_font_data(int save[20][10], std::ifstream& fp, char ch)
{
    fp.seekg(0);
    while (fp.get() != ch)                          //search for character ch
        ;
    fp.get();       //ignore '\n'
    for (int i = 0; i < 20; ++i)
    {
        int &line_size = save[i][9];                //save[i][9] is the line size
        while (fp && fp.peek() != '\n')
        {
            fp >> save[i][line_size];
            ++ line_size;                           //save the line size
        }
        fp.get();                                   //ignore '\n'
        if (save[i][0] == 0)                        //all information of character ch has been loaded
            break;
   }
   return;        
}


int main(void)
{
    std::ifstream fin("FontData.txt");      
    if (!fin.is_open())
    {
        std::cout << "Fail to load the file!" << std::endl;
        exit(1);
    }

    while (true)
    {
        char ch = 'A';

        std::cout << "To convert: ";
        std::cin >> ch;
        ch = toupper(ch);
        if (ch < 'A' || ch > 'Z')       //FontData need to be completed
            break;
        std::cout << std::endl;

        int temp_save[20][10] = {};
        Load_font_data(temp_save, fin, ch);

        character letter;

        for (int i = 0; i < 20; ++i)
        {
            letter.Set(temp_save[i], temp_save[i+1]);
            if (temp_save[i+1][0] == 0)
                break;
        }
        letter.Display();
    }        
    return 0;
}