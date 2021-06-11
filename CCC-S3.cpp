/* sample data
1
0 1000 0

Result 0
 
2
10 4 3
20 4 2
 
Result 20
 
3
6 8 3
1 4 1
14 5 2
 
Result 43
 
3
5 5 0
10 6 6
7 8 2

Result 0

12
1 5 13
2 6 13
3 8 13
4 5 13
5 6 13
6 8 13
7 5 13
8 6 13
9 8 13
10 5 13
11 6 13
12 8 13

Result 0

12
1 5 3
2 6 1
3 8 2
4 5 5
5 6 4
6 8 7
7 5 1
8 6 2
9 8 4
10 5 2
11 6 5
12 8 7

Result 46

 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef vector<int> ivec;
typedef unsigned long long uint64;

ostream &operator<<(ostream &stream, ivec &obj)
{
    for (size_t i = 0; i < obj.size(); i++)
    {
        stream << obj[i] << " ";
    }
    return stream;
}

ivec positions;
ivec walkingSpeeds;
ivec hearingDistances;

int maxPosition = 0;

uint64 getMinTimeForPosition(int peggedPosition)
{
    uint64 totalTime = 0;
    for (int i = 0; i < positions.size(); i++)
    {
        int diffDist = abs(positions[i] - peggedPosition);
        if (diffDist > hearingDistances[i])
        {
            uint64 distanceWalked = diffDist - hearingDistances[i];
            uint64 walkSpeed = (uint64) walkingSpeeds[i];
            totalTime += distanceWalked * walkSpeed; // the walkingSpeed is weird, since it's # seconds/m, so this all works ok
        }
        // if less, then contributes nothing to the total time, since the person can already hear the music
    }
    
    return totalTime;
}

uint64 findMinTime(int leftPosition, int rightPosition)
{
    /*
    // inefficient version - go through all the possible positions and find the total min each time
    uint64 totalMinTime = getMinTimeForPosition(leftPosition);
    for (int i = leftPosition + 1; i <= rightPosition; i++)
    {
        uint64 timeAtPos = getMinTimeForPosition(i);
        if (timeAtPos < totalMinTime)
            totalMinTime = timeAtPos;
    }
    */

    uint64 leftTime = getMinTimeForPosition(leftPosition);
    uint64 rightTime = getMinTimeForPosition(rightPosition);
    uint64 totalMinTime = min(leftTime, rightTime);
    
    if (rightPosition - leftPosition <= 1) // nothing to do
        return totalMinTime;

    // divide and conquer
    // find middle-line, then recurse left or right
    int midPosition = (leftPosition + rightPosition) / 2;
    uint64 midTime = getMinTimeForPosition(midPosition);
    int nearLeftPosition = midPosition - 1;
    int nearRightPosition = midPosition + 1;
    uint64 nearLeftTime = getMinTimeForPosition(nearLeftPosition);
    uint64 nearRightTime = getMinTimeForPosition(nearRightPosition);

    if (midTime <= nearLeftTime && midTime <= nearRightTime)
        return midTime;
    else if (nearRightTime <= midTime) // recurse right
        return min(totalMinTime, findMinTime(midPosition, rightPosition));
    else
        return min(totalMinTime, findMinTime(leftPosition, midPosition));
}

int main()
{
    // get all the input data
    int numFriends;
    cin >> numFriends;

    // get the rest of the data and calculate max location
    for (int i = 0; i < numFriends; i++)
    {
        int position;
        int walkingSpeed;
        int hearingDistance;
        cin >> position;
        cin >> walkingSpeed;
        cin >> hearingDistance;
        
        maxPosition = max(position, maxPosition);

        positions.push_back(position);
        walkingSpeeds.push_back(walkingSpeed);
        hearingDistances.push_back(hearingDistance);
    }

    cout << findMinTime(0, maxPosition) << endl;
    
    return 0;
}
