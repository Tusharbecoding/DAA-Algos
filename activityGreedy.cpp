#include <iostream>

using namespace std;

struct Activity
{
    int start, finish;
};

bool activityCompare(const Activity &a, const Activity &b)
{
    return (a.finish < b.finish);
}

void activitySelection(Activity activities[], int n)
{

    sort(activities, activities + n, activityCompare);

    int i = 0;
    cout << "Selected Activities:\n";
    cout << "Activity " << i + 1 << ": Start = " << activities[i].start << ", Finish = " << activities[i].finish << endl;

    for (int j = 1; j < n; j++)
    {

        if (activities[j].start >= activities[i].finish)
        {
            cout << "Activity " << j + 1 << ": Start = " << activities[j].start << ", Finish = " << activities[j].finish << endl;
            i = j;
        }
    }
}

int main()
{

    Activity activities[] = {{1, 2}, {2, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};

    int n = sizeof(activities) / sizeof(activities[0]);

    activitySelection(activities, n);

    return 0;
}
