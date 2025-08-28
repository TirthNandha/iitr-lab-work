#include <vector>
#include <chrono>
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

#define N 1000
#define M 4

using namespace std;
using namespace chrono;

struct ListNode {
    long value;
    ListNode* nextPtr;
    ListNode(long val) : value(val), nextPtr(nullptr) {}
};


vector<ListNode*> nodeStorage;
ListNode* listHead = nullptr;
vector<long> inputData;
long nextIndex = 0;
pthread_mutex_t mutexIndex;
ListNode* listTail = nullptr;

struct ThreadInfo {
    long threadNum;
    long elementCount;
};

void insertNodeAt(long val, long idx) {
    ListNode* newNode = new ListNode(val);
    nodeStorage[idx] = newNode;
}

void connectNodes(long totalCount) {
    if (totalCount == 0) return;
    
    listHead = nodeStorage[0];
    ListNode* curr = listHead;
    
    for (long i = 1; i < totalCount; ++i) {
        curr->nextPtr = nodeStorage[i];
        curr = nodeStorage[i];
    }
    
    listTail = curr;
}

void* threadProcess(void* arg) {
    ThreadInfo* info = (ThreadInfo*)arg;
    
    while (true) {
        long idx;
        
        pthread_mutex_lock(&mutexIndex);
        if (nextIndex >= info->elementCount) {
            pthread_mutex_unlock(&mutexIndex);
            break;
        }
        idx = nextIndex;
        nextIndex++;
        pthread_mutex_unlock(&mutexIndex);
        
        long val = inputData[idx];
        insertNodeAt(val, idx);
    }
    
    return nullptr;
}

void generateRandomValues(long count) {
    inputData.clear();
    inputData.reserve(count);
    
    srand(time(nullptr));
    
    cout << "Creating " << count << " random values..." << endl;
    for (long i = 0; i < count; ++i) {
        long randVal = rand() % 1000 + 1;
        inputData.push_back(randVal);
    }
}

bool verifyList() {
    if (inputData.empty()) {
        return (listHead == nullptr);
    }
    
    ListNode* curr = listHead;
    long idx = 0;
    
    do {
        if (curr == nullptr || idx >= static_cast<long>(inputData.size())) break;
        if (curr->value != inputData[idx]) {
            cout << "Mismatch at position " << idx 
                 << ": Vector value " << inputData[idx] 
                 << ", List value " << curr->value << endl;
            return false;
        }
        curr = curr->nextPtr;
        idx++;
    } while (true);
    
    if (curr != nullptr || idx < static_cast<long>(inputData.size())) {
        cout << "Size mismatch: Vector size " << inputData.size() 
             << ", List size " << idx << endl;
        return false;
    }
    
    return true;
}
void displayList(long maxCount = 10) {
    cout << "Linked List (first " << maxCount << " elements): ";
    ListNode* curr = listHead;
    long count = 0;
    while (curr != nullptr && count < maxCount) {
        cout << curr->value << " ";
        curr = curr->nextPtr;
        count++;
    }
    if (curr != nullptr) {
        cout << "...";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    int elementCount = N;
    int threadCount = M;
    
    if (argc > 1) {
        elementCount = atol(argv[1]);
    }
    if (argc > 2) {
        threadCount = atol(argv[2]);
    }
    
    cout << "Generating random values..." << endl;
    generateRandomValues(elementCount);
    cout << endl;
    
    pthread_mutex_init(&mutexIndex, nullptr);
    nextIndex = 0;
    listHead = listTail = nullptr;
    nodeStorage.clear();
    nodeStorage.resize(inputData.size(), nullptr);
    
    cout << "Starting " << threadCount << " threads with pthread..." << endl;
    
    pthread_t* threadArray = new pthread_t[threadCount];
    ThreadInfo* threadInfo = new ThreadInfo[threadCount];
    
    auto start = high_resolution_clock::now();
    
    for (int i = 0; i < threadCount; i++) {
        threadInfo[i].threadNum = i;
        threadInfo[i].elementCount = inputData.size();
        
        if (pthread_create(&threadArray[i], nullptr, threadProcess, &threadInfo[i]) != 0) {
            cout << "Failed to create thread " << i << endl;
            return 1;
        }
    }
    
    cout << "\nThreads working with shared index..." << endl;
    
    for (int i = threadCount; i-- > 0;) {
        pthread_join(threadArray[i], nullptr);
    }
    
    cout << "Connecting nodes in order..." << endl;
    connectNodes(inputData.size());
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Checking sequence correctness..." << endl;
    if (verifyList()) {
        cout << "Linked list matches vector!" << endl;
    } else {
        cout << "Linked list does not match vector!" << endl;
    }
    cout << endl;
    
    cout << "Input verification:" << endl;
    if (inputData.size() <= 20) {
        cout << "Original Vector: ";
        for (int val : inputData) {
            cout << val << " ";
        }
        cout << endl;
        displayList(inputData.size());
    } else {
        cout << "First 10 elements:" << endl;
        cout << "Original Vector: ";
        for (int i = 0; i < min(10L, static_cast<long>(inputData.size())); ++i) {
            cout << inputData[i] << " ";
        }
        cout << "..." << endl;
        displayList(10);
    }
    
    return 0;
}