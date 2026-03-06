template <typename T>
void print(T obj){
    std::cout << obj << std::endl;
}

template <typename T>
void print(list::custom_list<T>& obj) {
    std::cout << obj << std::endl;
}

