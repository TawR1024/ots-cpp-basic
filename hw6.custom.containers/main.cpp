#include <iostream>

#include "src/containers/custom_vector/custom_vector.hpp"

template <typename T>
void print(T obj){
    std::cout << obj << std::endl;
}

void Test_Custom_Vector(){
    
    print("Initializing container");
    vector::custom_vector<int> vec(2);

    print("Add elements [1..10]");
    for (size_t i =0; i< 10; i++){
        vec.push_back(i+1);
    }

    print("Print elements");
    print(vec);

    print("Get container Size");
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
    print(vec.empty());
 
}

int main ()
{

    Test_Custom_Vector();
    // vector::custom_vector<int> vec;
    // for (int i = 0; i < 10; ++i)
    // {
    //     vec.push_back (i * 10);
    // }

    // std::cout << "insert done";
    // // // Выводим значения на экран
    // std::cout << "Show elements custom_vector:" << vec <<std::endl;
    
    // std::cout << "Container size: " << vec.size() << std::endl;

    // std::cout << "Remove elements" << std::endl;
    // vec.erase(20);
    // vec.erase(40);
    // std::cout << "Show elements after deletion:" << vec <<std::endl;


    // std::cout << "Insert elements" << std::endl;
    // vec.insert(300);
    // vec.erase(400);
    // std::cout << "Show elements after deletion:" << vec <<std::endl;

    // std::cout << "Clenup container" << std::endl;
    // vec.clear();
    // std::cout <<  vec.empty() << std::endl;






    return 0;
}
