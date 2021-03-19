#include <iostream>

using namespace std;

void MoveLastDisk(char start, char destination)
{
    //cout << "from tower "s << start << " in tower "s << destination << endl;
    cout << "из башни "s << start << " в башню "s << destination << endl;
}

void MoveTower(int disk_count, char start, char destination, char buffer)  //buffer -> temp tower
{
    if (disk_count == 0)
        return;

    MoveTower(disk_count - 1, start, buffer, destination);
    MoveLastDisk(start, destination);
    MoveTower(disk_count - 1, buffer, destination, start);
}


int main()
{
    setlocale(0, "rus");  //0 -> LC_ALL

    MoveTower(3, 'A', 'B', 'C');

    return 0;
}
