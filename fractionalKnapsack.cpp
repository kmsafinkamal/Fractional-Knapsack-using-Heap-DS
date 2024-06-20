#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent each item
struct Item {
    int weight;
    int benefit;
    double value; // value = benefit / weight

    // Constructor
    Item(int w, int b) : weight(w), benefit(b), value((double)b / w) {}
};

// Custom comparator for priority queue
// struct CompareItems {
//     bool operator()(const Item& a, const Item& b) {
//         return a.value < b.value; // Max heap based on item's value
//     }
// };

// Class to represent a Max Heap
class MaxHeap {
private:
    vector<Item> heap;

    void heapify(int idx) {
        int largest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heap.size() && heap[left].value > heap[largest].value)
            largest = left;

        if (right < heap.size() && heap[right].value > heap[largest].value)
            largest = right;

        if (largest != idx) {
            swap(heap[idx], heap[largest]);
            heapify(largest);
        }
    }

public:
    MaxHeap(vector<Item>& items) {
        heap = items;
        for (int i = heap.size() / 2 - 1; i >= 0; --i)
            heapify(i);
    }

    bool empty() const {
        return heap.empty();
    }

    Item pop() {
        if (empty())
            throw out_of_range("Heap is empty");

        Item root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return root;
    }
};

// Fractional Knapsack function
void fractionalKnapsack(vector<Item>& items, int W) {
    MaxHeap maxHeap(items);

    double totalValue = 0.0;
    double currentWeight = 0.0;

    while (!maxHeap.empty() && currentWeight < W) {
        Item item = maxHeap.pop();

        double fraction = min((double)item.weight, W - currentWeight);
        totalValue += fraction * item.value;
        currentWeight += fraction;

        cout << "Added item with weight " << fraction << " and benefit " << fraction * item.value << " fractionally." << endl;
    }

    cout << "Total value of items in knapsack: " << totalValue << endl;
}

int main() {
    //vector<Item> items = {{10, 60}, {20, 100}, {30, 120}}; // Example items: weight, benefit
    //vector<Item> items = {{3,10}, {3,15}, {2, 10}, {5, 12}, {1, 8}};
    vector<Item> items = {{10,40}, {30,30}, {20, 80}, {50, 70}};
    int W = 60; // Maximum weight capacity of knapsack

    fractionalKnapsack(items, W);

    return 0;
}
