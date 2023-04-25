/*
Maps are a type of associative container in C++ that store key-value pairs. They allow efficient lookup and retrieval of values based on their corresponding keys.

Maps are implemented as a balanced binary search tree, with each node representing a key-value pair. The keys are stored in sorted order, which allows for fast searching and insertion operations. Maps are typically used in scenarios where you need to store a large amount of data and quickly retrieve values based on keys.

Some key features of maps in C++ include:

-They are associative containers that store key-value pairs
-They are implemented as balanced binary search trees, which allows for efficient lookup and retrieval of values
-The keys are stored in sorted order, which allows for fast searching and insertion operations
-They have a logarithmic time complexity for most operations, including insert, delete, and search
-They automatically sort and maintain their keys in a sorted order, which can be useful in some scenarios
-To use maps in C++, you need to include the <map> header file. The basic syntax for declaring a map is:
    std::map<key_type, value_type> map_name;
    
Here, key_type is the type of the keys you want to store in the map, and value_type is the type of the corresponding values. 
For example, if you want to store integers as keys and strings as values, you can declare a map like this:
    std::map<int, std::string> my_map;

Once you have declared a map, you can insert key-value pairs into it using the insert() function. For example:
    my_map.insert(std::make_pair(1, "one"));
    my_map.insert(std::make_pair(2, "two"));
    my_map.insert(std::make_pair(3, "three"));
    
You can also use the [] operator to insert or update a value based on a key:
    my_map[4] = "four";

To retrieve a value from a map, you can use the [] operator or the find() function:
    std::string value1 = my_map[1];
    std::string value2 = my_map.find(2)->second;    
    
To remove a key-value pair from a map, you can use the erase() function:
    my_map.erase(3);
*/

#include <iostream>
#include <map>

using namespace std;

int main() {
    // create a map with string keys and int values
    map<string, int> myMap;

    // insert some key-value pairs
    myMap.insert(make_pair("John", 25));
    myMap.insert(make_pair("Alice", 30));
    myMap.insert(make_pair("Bob", 20));

    // print the size of the map
    cout << "Size of map: " << myMap.size() << endl;

    // access the value associated with a key
    cout << "Age of Alice: " << myMap["Alice"] << endl;

    // check if a key exists in the map
    if (myMap.count("John") > 0) {
        cout << "John exists in the map" << endl;
    } else {
        cout << "John does not exist in the map" << endl;
    }

    // iterate through the map and print key-value pairs
    cout << "All key-value pairs:" << endl;
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }

    // remove a key-value pair
    myMap.erase("Bob");

    // print the size of the map after removal
    cout << "Size of map after removal: " << myMap.size() << endl;

    return 0;
}
