#include <iostream>

const int MAX_N = 10; // Maximum number of items (adjust as needed)

struct Item
{
    int weight;
    int value;
    double ratio; // Value-to-weight ratio
};

class Knapsack
{
private:
    int capacity;
    int currentWeight;
    int currentValue;
    int maxPossibleValue;
    int numItems;
    Item items[MAX_N];

    // Function to calculate the upper bound for the node
    double calculateUpperBound(int level, int weight, int value);

public:
    Knapsack(int knapsackCapacity, int itemCount);

    void initializeItems();
    void branchAndBound(int level, int weight, int value);

    void printSolution();
};

Knapsack::Knapsack(int knapsackCapacity, int itemCount)
    : capacity(knapsackCapacity), currentWeight(0), currentValue(0), maxPossibleValue(0), numItems(itemCount)
{
    initializeItems();
}

void Knapsack::initializeItems()
{
    std::cout << "Enter the weights and values of the items:" << std::endl;
    for (int i = 0; i < numItems; i++)
    {
        std::cout << "Item " << i + 1 << ": ";
        std::cin >> items[i].weight >> items[i].value;
        items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
        maxPossibleValue += items[i].value;
    }
}

double Knapsack::calculateUpperBound(int level, int weight, int value)
{
    double upperBound = value;
    int remainingWeight = capacity - weight;

    // Add the value of fractional items
    while (level < numItems && items[level].weight <= remainingWeight)
    {
        upperBound += items[level].value;
        remainingWeight -= items[level].weight;
        level++;
    }

    // Add the value of the remaining fractional item
    if (level < numItems)
    {
        upperBound += items[level].ratio * remainingWeight;
    }

    return upperBound;
}

void Knapsack::branchAndBound(int level, int weight, int value)
{
    if (weight <= capacity && value > currentValue)
    {
        currentValue = value;
        currentWeight = weight;
    }

    if (level == numItems)
    {
        return;
    }

    double upperBound = calculateUpperBound(level, weight, value);

    // Explore the left child (including the item)
    if (weight + items[level].weight <= capacity && value + items[level].value > currentValue)
    {
        branchAndBound(level + 1, weight + items[level].weight, value + items[level].value);
    }

    // Explore the right child (excluding the item)
    if (upperBound > currentValue)
    {
        branchAndBound(level + 1, weight, value);
    }
}

void Knapsack::printSolution()
{
    std::cout << "Maximum value in the knapsack: " << currentValue << std::endl;
    std::cout << "Selected items:" << std::endl;
    for (int i = 0; i < numItems; i++)
    {
        if (items[i].weight <= currentWeight)
        {
            std::cout << "Item " << i + 1 << ": Weight = " << items[i].weight << ", Value = " << items[i].value << std::endl;
        }
    }
}

int main()
{
    int capacity, numItems;

    std::cout << "Enter the capacity of the knapsack: ";
    std::cin >> capacity;

    std::cout << "Enter the number of items: ";
    std::cin >> numItems;

    Knapsack knapsack(capacity, numItems);
    knapsack.branchAndBound(0, 0, 0);
    knapsack.printSolution();

    return 0;
}
