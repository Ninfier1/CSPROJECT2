#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

using ItemType = std::string;

class Set

{
public:
    Set();
    ~Set();
    Set(const Set& aSet);
    Set& operator=(const Set& aSet);
    
    bool empty() const;
    int size() const;
    
    bool insert(const ItemType& value);
    
    bool erase(const ItemType& value);
    
    bool contains(const ItemType& value) const;
    
    bool get(int pos, ItemType& value) const;
    
    void swap(Set& other);
    
private:
    struct Node
    {
        ItemType s_value;
        Node* s_next;
        Node* s_prev;
    };
    Node* head;
    Node* tail;
    int s_size;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif
