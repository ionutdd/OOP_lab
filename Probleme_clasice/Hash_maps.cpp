/*
A hash map (also known as a hash table) is a data structure that stores key-value pairs in a way that allows for fast retrieval of values based on their keys. 
The basic idea behind a hash map is to use a hash function to compute an index into an array of buckets, where each bucket is a linked list of key-value pairs.
When a key-value pair is added to the hash map, the hash function is used to compute an index into the array of buckets. 
The key-value pair is then added to the linked list of the bucket at that index. When a value is retrieved from the hash map, the hash function is again used to compute the index of the bucket that should contain the key-value pair with the given key. 
Then the linked list of the bucket is searched to find the key-value pair with the given key.
The key benefit of a hash map is that it provides constant-time (O(1)) average case performance for insertion, deletion, and retrieval of key-value pairs. 
However, the actual performance can depend on the quality of the hash function used, the number of buckets in the array, and the distribution of the keys.
One potential issue with hash maps is collisions, which occur when two keys map to the same index in the array of buckets.
To handle collisions, a variety of collision resolution strategies can be used, such as separate chaining (where each bucket contains a linked list of key-value pairs), linear probing (where keys are placed in the next available empty bucket), or quadratic probing (where keys are placed in the next available bucket using a quadratic function). 
*/

//Example with chaining for collision resolution:

#include <iostream>
#include <vector>

using namespace std;

// Node class for chaining
template <typename K, typename V>
class Node {
public:
    K key;
    V value;
    Node<K, V>* next;

    Node(K key, V value) : key(key), value(value), next(nullptr) {}
};

template <typename K, typename V>
class HashMap {
private:
    std::vector<Node<K, V>*> table;
    int capacity;
    int size;

    // hash function to get index from key
    int hash(K key) {
        std::hash<K> hashFunc;
        return hashFunc(key) % capacity;
    }

public:
    HashMap(int capacity = 100) : capacity(capacity), size(0) {
        table.resize(capacity);
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node<K, V>* current = table[i];
            while (current != nullptr) {
                Node<K, V>* prev = current;
                current = current->next;
                delete prev;
            }
            table[i] = nullptr;
        }
    }

    void put(K key, V value) {
        int index = hash(key);
        Node<K, V>* current = table[index];

        // if key already exists, update value
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        // add new node
        Node<K, V>* newNode = new Node<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    V get(K key) {
        int index = hash(key);
        Node<K, V>* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        // key not found
        return V();
    }

    void remove(K key) {
        int index = hash(key);
        Node<K, V>* current = table[index];
        Node<K, V>* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    // first node in list
                    table[index] = current->next;
                } else {
                    // not first node in list
                    prev->next = current->next;
                }
                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool containsKey(K key) {
        int index = hash(key);
        Node<K, V>* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    int getSize() {
        return size;
    }
};

int main() {
    // create a HashMap with an initial capacity of 5
    HashMap<string, int> map(5);

    // add some key-value pairs
    map.put("apple", 1);
    map.put("banana", 2);
    map.put("cherry", 3);
    map.put("date", 4);
    map.put("elderberry", 5);

    // get the value associated with a key
    cout << "Value for key 'cherry': " << map.get("cherry") << endl;

    // remove a key-value pair
    map.remove("banana");

    // check if a key is in the map
    if (map.containsKey("date")) {
        cout << "Date is in the map" << endl;
    } else {
        cout << "Date is not in the map" << endl;
    }

    // get the size of the map
    cout << "Size of map: " << map.getSize() << endl;

    return 0;
}
