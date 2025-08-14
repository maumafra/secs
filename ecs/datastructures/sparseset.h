// https://www.geeksforgeeks.org/dsa/sparse-set/
using namespace std;

class sparseset {
    int *sparse;    /* Stores the indexes */
    int *dense;     /* Stores the actual elements */
    int n;          /* Cur number of elements */
    int capacity;   /* Capacity of set or size of dense[] */
    int maxValue;   /* Maximum value in set or size of sparse[] */

public:
    sparseset(int maxV, int cap) {
        sparse = new int[maxV+1];
        dense = new int[cap];
        capacity = cap;
        maxValue = maxV;
        n = 0;
    }

    ~sparseset() {
        delete[] sparse;
        delete[] dense;
    }

    /* If element is present, returns index of element in dense[]. 
     * Else, returns -1. */
    int search(int x);

    /* Inserts a new element into set */
    void insert(int x);

    /* Deletes an element */
    void deletion(int x);

    /* Prints content of set */
    void print();

    /* Removes all elements from set */
    void clear() { n = 0; }

    sparseset* intersection(sparseset &ss);

    sparseset* setUnion(sparseset &ss);
};

int sparseset::search(int x) {

}
