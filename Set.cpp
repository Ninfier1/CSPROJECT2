#include "Set.h"
#include <iostream>

using namespace std;

// Constructor
Set::Set()
{
    s_size = 0;
    head = nullptr;
    tail = nullptr;
}

// Destructor
Set::~Set() {
    Node* p = head;
    while (p != nullptr) {
        Node* next = p->s_next;
        delete p;
        p = next;
    }
}

// Copy Constructor
Set::Set(const Set& aSet) : head(nullptr), tail(nullptr), s_size(0) {
    Node* p = aSet.head;
    while (p != nullptr) {
        insert(p->s_value);
        p = p->s_next;
    }
}

// Assignment Operator
Set& Set::operator=(const Set& aSet) {
    if (this != &aSet) {
        Set temp(aSet);
        swap(temp);
    }
    return *this;
}

// Check if the set is empty
bool Set::empty() const {
    return s_size == 0;
}

// Return the size of the set
int Set::size() const {
    return s_size;
}

// Insert an item into the set
bool Set::insert(const ItemType& value) {
    if (contains(value)) // Do not insert if already exists
        return false;

    Node* newNode = new Node;
    newNode->s_value = value;
    newNode->s_next = nullptr;
    newNode->s_prev = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->s_next = newNode;
        newNode->s_prev = tail;
        tail = newNode;
    }

    s_size++;
    return true;
}

// Erase an item from the set
bool Set::erase(const ItemType& value) {
    Node* p = head;
    while (p != nullptr) {
        if (p->s_value == value) {
            if (p->s_prev != nullptr) {
                p->s_prev->s_next = p->s_next;
            } else {
                head = p->s_next;
            }

            if (p->s_next != nullptr) {
                p->s_next->s_prev = p->s_prev;
            } else {
                tail = p->s_prev;
            }

            delete p;
            s_size--;
            return true;
        }
        p = p->s_next;
    }
    return false; // Value not found
}

// Check if the set contains a specific item
bool Set::contains(const ItemType& value) const {
    Node* p = head;
    while (p != nullptr) {
        if (p->s_value == value)
            return true;
        p = p->s_next;
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const {
    // Check if the given index is valid
    if (pos >= s_size || pos < 0)
        return false;

    // Create a temporary copy of the set to erase values from
    Set t_set(*this);

    // Remove the minimum value from t_set pos times
    for (int i = 0; i < pos; ++i) {
        ItemType min;
        bool found = false;
        // Find the minimum value in t_set
        for (Node* cNode = t_set.head; cNode != nullptr; cNode = cNode->s_next) {
            if (!found || cNode->s_value < min) {
                min = cNode->s_value;
                found = true;
            }
        }
        // Erase the minimum value from t_set
        t_set.erase(min);
    }

    // Find the minimum value left in t_set and set value to it
    ItemType min;
    bool found = false;
    for (Node* cNode = t_set.head; cNode != nullptr; cNode = cNode->s_next) {
        if (!found || cNode->s_value < min) {
            min = cNode->s_value;
            found = true;
        }
    }
    value = min;
    return true;
}



// Swap the content of two sets
void Set::swap(Set& other) {
    Node* tempHead = head;
    Node* tempTail = tail;
    int tempSize = s_size;

    head = other.head;
    tail = other.tail;
    s_size = other.s_size;

    other.head = tempHead;
    other.tail = tempTail;
    other.s_size = tempSize;
}

// Implement the unite function
void unite(const Set& s1, const Set& s2, Set& result) {
    for (int i = 0; i < s1.size(); ++i) {
        ItemType value;
        s1.get(i, value);
        result.insert(value);
    }

    for (int i = 0; i < s2.size(); ++i) {
        ItemType value;
        s2.get(i, value);
        result.insert(value);
    }
}

// Implement the subtract function
void subtract(const Set& s1, const Set& s2, Set& result) {
    // Clear the result set to ensure it's empty before subtraction
    result = Set();
    
    // Iterate through each element of s1
    for (int i = 0; i < s1.size(); ++i) {
        ItemType value;
        if (s1.get(i, value)) {
            // If the element from s1 is not present in s2, insert it into the result set
            if (!s2.contains(value)) {
                result.insert(value);
            }
        }
    }
}

