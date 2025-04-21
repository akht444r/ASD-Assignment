#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MinHeap {
private:
    vector<int> heapArray;

    void trickleUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && heapArray[parent] > heapArray[index]) {
            swap(heapArray[parent], heapArray[index]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void trickleDown(int index) {
        int size = heapArray.size();
        while (index * 2 + 1 < size) {
            int leftChild = index * 2 + 1;
            int rightChild = leftChild + 1;
            int smallerChild = leftChild;

            if (rightChild < size && heapArray[rightChild] < heapArray[leftChild]) {
                smallerChild = rightChild;
            }

            if (heapArray[index] <= heapArray[smallerChild]) {
                break;
            }

            swap(heapArray[index], heapArray[smallerChild]);
            index = smallerChild;
        }
    }

public:
    void insert(int key) {
        heapArray.push_back(key);
        trickleUp(heapArray.size() - 1);
    }

    int remove() {
        if (heapArray.empty()) return -1;
        int root = heapArray[0];
        heapArray[0] = heapArray.back();
        heapArray.pop_back();
        trickleDown(0);
        return root;
    }

    void displayHeap() {
        cout << "[";
        for (size_t i = 0; i < heapArray.size(); ++i) {
            cout << heapArray[i] << (i < heapArray.size() - 1 ? ", " : "]");
        }
        cout << endl;
    }

    int peek() {
        return heapArray.empty() ? -1 : heapArray[0];
    }
};

int main() {
    MinHeap heap;
    
    vector<int> values = {50, 30, 20, 15, 10, 8, 16};
    for (int val : values) {
        heap.insert(val);
    }

    cout << "Min Heap: ";
    heap.displayHeap();

    int root = heap.peek();
    if (root != -1) {
        cout << "Root element (peek): " << root << endl;
    } else {
        cout << "Heap is empty!" << endl;
    }

    return 0;
}
