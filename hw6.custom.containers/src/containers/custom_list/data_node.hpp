namespace list
{
template <typename T>
class custom_list;  // forward declaration;

template <typename data_t>
class data_node
{
   private:
    data_t     data;
    data_node* next;
    data_node* prev;
    friend class custom_list<data_t>; 

   public:
    explicit data_node (data_t value, data_node* next = nullptr, data_node* prev = nullptr)
        : data (value), next (next), prev (prev)
    {
    }

    data_node& operator= (const data_node& other)
    {
        if (this != &other)
        {
            data = other.data;
        }
        return *this;
    }
};
}  // namespace list
