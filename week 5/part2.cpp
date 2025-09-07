#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <pthread.h>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <thread>
#include <cstdlib>
#include <sys/stat.h>

using namespace std;
using namespace chrono;

struct ListNode {
    long value;
    ListNode* nextPtr;
    ListNode(long val) : value(val), nextPtr(nullptr) {}
};

vector<long> inputData;
vector<ListNode*> nodeStorage;
ListNode* listHead = nullptr;
ListNode* listTail = nullptr;
long nextIndex = 0;
pthread_mutex_t indexMutex; 

struct ThreadData {
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
    ThreadData* data = (ThreadData*)arg;
    
    while (true) {
        int index;
        
        pthread_mutex_lock(&indexMutex);
        if (nextIndex >= data->elementCount) {
            pthread_mutex_unlock(&indexMutex);
            break;
        }
        index = nextIndex;
        nextIndex++;
        pthread_mutex_unlock(&indexMutex);
        
        long value = inputData[index];
        insertNodeAt(value, index);
    }
    
    return nullptr;
}

bool readFromFile(const string& filename, long count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }
    
        inputData.clear();
    inputData.reserve(count);
    
    long value;
    for (int i = 0; i < count && file >> value; i++) {
        inputData.push_back(value);
    }

    file.close();
    return true;
}

bool verifyList() {
    if (inputData.empty()) {
        return (listHead == nullptr);
    }
    
    ListNode* current = listHead;
    int index = 0;
    
    while (current != nullptr && static_cast<size_t>(index) < inputData.size()) {
        if (current->value != inputData[index]) {
            return false;
        }
        current = current->nextPtr;
        index++;
    }
    
    return (current == nullptr && static_cast<size_t>(index) == inputData.size());
}

void generateInputFile(const string& filename, long count) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not create file " << filename << endl;
        return;
    }
    
    srand(time(nullptr));
    for (long i = 0; i < count; i++) {
        file << rand() % 10000;
        if (i < count - 1) file << " ";
        if ((i + 1) % 20 == 0) file << "\n";
    }
    file.close();
}

double runPerformanceTest(long numElements, long numThreads, const string& filename) {
    pthread_mutex_init(&indexMutex, nullptr);
    nextIndex = 0;
    listHead = listTail = nullptr;
    nodeStorage.clear();
    nodeStorage.resize(numElements, nullptr);
    
    if (!readFromFile(filename, numElements)) {
        return -1;
    }
    
    pthread_t* threads = new pthread_t[numThreads];
    ThreadData* threadData = new ThreadData[numThreads];
    
    auto startTime = high_resolution_clock::now();
    
    for (int i = 0; i < numThreads; i++) {
        threadData[i].threadNum = i;
        threadData[i].elementCount = inputData.size();
        pthread_create(&threads[i], nullptr, threadProcess, &threadData[i]);
    }
    
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], nullptr);
    }
    
    connectNodes(inputData.size());
    
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(endTime - startTime);
    
    bool isValid = verifyList();
    return isValid ? (duration.count() / 1000.0) : -1;
}

int main() {
    mkdir("results", 0777);
    
    long coreCount = thread::hardware_concurrency();
    if (coreCount == 0) coreCount = 8;
    
    cout << "Found " << coreCount << " CPU cores" << endl;
    cout << endl;
    
    ofstream test1Stream("results/test1_thread_scaling.csv");
    test1Stream << "N,M,Time_ms" << endl;
    
    cout << "Creating input file with 1000000 numbers..." << endl;
    generateInputFile("input_1000000.txt", 1000000);
    
    cout << "Executing performance tests..." << endl;
    cout << "Threads\tTime(ms)" << endl;
    cout << "------\t--------" << endl;
    
    double baseTime = 0;
    long m = coreCount + 1;
    while (--m >= 1) {
        double totalTime = 0;
        long validCount = 0;
        
        long run = 3;
        while (run-- > 0) {
            double time = runPerformanceTest(1000000, m, "input_1000000.txt");
            if (time > 0) {
                totalTime += time;
                validCount++;
            }
        }
        
        if (validCount > 0) {
            totalTime /= validCount;
            if (m == 1) baseTime = totalTime;
            
            cout << m << "\t" << fixed << setprecision(2) << totalTime 
                 << "\t\t" << endl;
            
            test1Stream << 1000000 << "," << m << "," << fixed << setprecision(3) << totalTime << endl;
        }
    }
    test1Stream.close();
    
    cout << endl;
    
    ofstream test2Stream("results/test2_size_scaling.csv");
    test2Stream << "N,M,Time_ms" << endl;

    cout << "Fixed M=4, varying N" << endl;
    
    vector<long> sizeValues = {10, 100, 1000, 10000, 100000};
    
    cout << "Elements\tTime(ms)" << endl;
    cout << "--------\t--------" << endl;
    
    for (long n : sizeValues) {
        string fileName = "input_" + to_string(n) + ".txt";
            generateInputFile(fileName, n);
        
        double totalTime = 0;
        long validCount = 0;
        
        long run = 0;
        do {
            if (run >= 3) break;
            double time = runPerformanceTest(n, 4, fileName);
            if (time > 0) {
                totalTime += time;
                validCount++;
            }
            run++;
        } while (true);
        
        if (validCount > 0) {
            totalTime /= validCount;
            cout << n << "\t\t" << fixed << setprecision(3) << totalTime << endl;
            test2Stream << n << "," << 4 << "," << fixed << setprecision(3) << totalTime << endl;
        }
    }
    test2Stream.close();
    
    return 0;
}