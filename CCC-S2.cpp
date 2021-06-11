//
//  main.cpp
//  CCC-S2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<bool> bvec;
typedef vector<bvec> bmatrix;
typedef vector<int> ivec;


ostream &operator<<(ostream &stream, ivec &obj)
{
    for (size_t i = 0; i < obj.size(); i++)
    {
        stream << obj[i] << " ";
    }
    return stream;
}

int main()
{
    // get all the input data
    
    int numRows;
    int numCols;
    
    cin >> numRows;
    cin >> numCols;
    
    int numFlips;
    
    cin >> numFlips;
    
    ivec rowFlips;
    ivec colFlips;
    
    for (int i = 0; i < numFlips; i++)
    {
        char flipType;
        cin >> flipType;
        
        int index;
        cin >> index;
        index--; // switch from count at 1 to count at 0 starting values
        
        if (flipType == 'R')
            rowFlips.push_back(index);
        else
            colFlips.push_back(index);
    }
    
    bmatrix bits; // F black, T gold
    
    for (int i = 0; i < numRows; i++)
    {
        bvec row;
        for (int j = 0; j < numCols; j++)
        {
            row.push_back(false);
        }
        bits.push_back(row);
    }
    
    // collate the data so we don't flip unnecessarily
    ivec countRowFlips;
    ivec countColFlips;
    
    for (int i = 0; i < numRows; i++)
    {
        countRowFlips.push_back(0);
    }
    
    for (int i = 0; i < rowFlips.size(); i++)
    {
        countRowFlips[rowFlips[i]]++;
    }

    for (int i = 0; i < countRowFlips.size(); i++)
    {
        countRowFlips[i] = countRowFlips[i] % 2;
    }

    //cout << "rowFlips = " << rowFlips << endl;
    //cout << "countRowFlips = " << countRowFlips << endl;

    for (int i = 0; i < numCols; i++)
    {
        countColFlips.push_back(0);
    }
    
    for (int i = 0; i < colFlips.size(); i++)
    {
        countColFlips[colFlips[i]]++;
    }

    for (int i = 0; i < countColFlips.size(); i++)
    {
        countColFlips[i] = countColFlips[i] % 2;
    }

    //cout << "colFlips = " << colFlips << endl;
    //cout << "countColFlips = " << countColFlips << endl;

    // Modify the bit matrix first  for rows, then for columns
    
    for (int row = 0; row < countRowFlips.size(); row++)
    {
        if (countRowFlips[row] == 0)
            continue;
        for (int col = 0; col < numCols; col++)
        {
            bits[row][col] = !bits[row][col];
        }
    }

    for (int col = 0; col < countColFlips.size(); col++)
    {
        if (countColFlips[col] == 0)
            continue;
        for (int row = 0; row < numRows; row++)
        {
            bits[row][col] = !bits[row][col];
        }
    }

    // count number of 1s
    int count = 0;
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            if (bits[row][col])
                count++;
        }
    }

    cout << count << endl;
    return 0;
}
