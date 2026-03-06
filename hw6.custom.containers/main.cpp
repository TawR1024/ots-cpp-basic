#include <iostream>

#include "src/containers/custom_vector/custom_vector.hpp"

#include "src/containers/custom_list/custom_list.hpp"
#include "src/utils/utils.hpp"




void Test_Custom_Vector(){
    
    print("--- TEST CUSTOM CONTAINER C-ARRAY BASED ---\n");

    print("Initializing container");
    vector::custom_vector<int> vec(2);

    print("Add elements [1..10]");
    for (size_t i =1; i<= 10; i++){
        vec.push_back(i);
    }

    print("Print elements");
    print(vec);

    print("Get container size");
    print(vec.size());

    print("Remove 3rd, 5th & 7th elements");
    vec.erase(3);
    vec.erase(5);
    vec.erase(7);
    print(vec);

    print("Insert 10 into 0 position");
    vec.insert(0, 10);
    print(vec);

    print("Insert 20 to the middle");
    vec.insert(vec.size()/2,20);
    print(vec);

    print("Insert 30 to the end");
    vec.push_back(30);
    print(vec);

    print("Erase data");
    vec.clear();
    print("Check that empty");
    std::cout << std::boolalpha;
    print(vec.empty());
    std::cout << std::boolalpha;
 
}

void Test_Custom_List(){
    print("--- TEST CUSTOM CONTAINER LINKED-LIST BASED ---\n");
    
    print("Initializing container");
    list::custom_list<int> my_list;

    print("Add elements [1..10]");
    for (size_t i =1; i<= 10; i++){
        my_list.push_back(i);
    }

    print("Print elements");
    print(my_list);

    print("Get container size");
    print(my_list.size());

    print("Remove 3rd, 5th & 7th elements");
    my_list.erase(3);
    my_list.erase(5);
    my_list.erase(7);
    print(my_list);

    print("Insert 10 into 0 position");
    my_list.insert(0, 10);
    print(my_list);

    print("Insert 20 to the middle");
    my_list.insert(my_list.size()/2,20);
    print(my_list);

    print("Insert 30 to the end");
    my_list.push_back(30);
    print(my_list);

    print("Erase data");
    my_list.clear();
    print("Check that empty");
    std::cout << std::boolalpha;
    print(my_list.empty());
    std::cout << std::boolalpha;
 
}

int main ()
{

    Test_Custom_Vector();
    Test_Custom_List();


    return 0;
}
