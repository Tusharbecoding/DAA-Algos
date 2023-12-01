#include <iostream>
#include <algorithm>

const int MAX_N = 100; // Maximum number of items (adjust as needed)

class FractionalKnapsack
{
private:
    struct Item
    {
        int weight;
        int value;
        double ratio; // Value-to-weight ratio
    };

    Item items[MAX_N];

public:
    FractionalKnapsack();
    void initializeItems();
    static bool compareItems(const Item &a, const Item &b);
    double fractionalKnapsack(int capacity);
};

FractionalKnapsack::FractionalKnapsack()
{
    initializeItems();
}

void FractionalKnapsack::initializeItems()
{
    std::cout << "Enter the weights and values of the items:" << std::endl;
    for (int i = 0; i < MAX_N; i++)
    {
        std::cout << "Item " << i + 1 << ": ";
        std::cin >> items[i].weight >> items[i].value;
        items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
    }
}

bool FractionalKnapsack::compareItems(const Item &a, const Item &b)
{
    return a.ratio > b.ratio;
}

double FractionalKnapsack::fractionalKnapsack(int capacity)
{
    // Sort items by their value-to-weight ratio in descending order
    std::sort(items, items + MAX_N, compareItems);

    double totalValue = 0.0;

    for (int i = 0; i < MAX_N; i++)
    {
        if (capacity == 0)
        {
            break;
        }

        if (items[i].weight <= capacity)
        {
            totalValue += items[i].value;
            capacity -= items[i].weight;
        }
        else
        {
            totalValue += (static_cast<double>(capacity) / items[i].weight) * items[i].value;
            break;
        }
    }

    return totalValue;
}

int main()
{
    FractionalKnapsack fractionalKnapsack;

    int capacity;
    std::cout << "Enter the capacity of the knapsack: ";
    std::cin >> capacity;

    double maxTotalValue = fractionalKnapsack.fractionalKnapsack(capacity);

    std::cout << "Maximum total value in the knapsack: " << maxTotalValue << std::endl;

    return 0;
}
