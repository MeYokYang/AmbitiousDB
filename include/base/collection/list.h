#ifndef LIST_H
#define LIST_H

#include "collection.h"
#include "iterator.h"
#include "arr.h"


template <typename T>
class LinkedList : public List<T>
{
private:
    class Item
    {
    public:
        T       data;
        Item*   prev;
        Item*   next;

        Item(const T& d, Item* p = NULL, Item* n = NULL) : data(d), prev(p), next(n) {}

    };

    Item*       head;
    Item*       tail;

public:
    LinkedList() : head(NULL), tail(NULL) { this->len = 0; }
    ~LinkedList() { clear(); };
    LinkedList(const LinkedList<T>& other);
    LinkedList<T>& operator=(const LinkedList<T>& other);

    bool clear() override;

    class Iter
    // : public Iterator<T>
    {
    private:
        LinkedList  list;
        Item*       curr;

    public:
        Iter(const LinkedList& l, Item* p = NULL) : list(l), curr(p) {}

        T& operator*() { return curr->data; }
        Iter& operator++() { if (curr != NULL) curr = curr->next; return *this; }
        Iter operator++(int) { Iter i(list, curr); if (curr != NULL) curr = curr->next; return i; }
        Iter& operator--() { if (curr != head) curr = curr->prev; return *this; }
        Iter operator--(int) { Iter i(list, curr); if (curr != head) curr = curr->prev; return i; }
        bool operator==(const Iter& other) { return curr == other.curr ? TRUE : FALSE; }
        bool operator!=(const Iter& other) { return curr != other.curr ? TRUE : FALSE; }

        bool hasNext() const { return curr == NULL ? FALSE : TRUE; }
        Iter& next() { if (curr != NULL) curr = curr->next; return *this; }
        bool hasPrev() const { return curr == head ? FALSE : TRUE; }
        Iter& prev() { if (curr != head) curr = curr->prev; return *this; }
        bool insertBefore(const T& d);
        bool insertAfter(const T& d);
        bool insert(const T& d) { return insertBefore(d); };
        bool remove();
        bool replace(const T& d) const { if (curr == NULL) return FALSE; curr->data = d; return TRUE; }

    };

    Iter iter() const { return Iter(*this, head); }
    Iter begin() const { return Iter(*this, head); }
    Iter end() const { return Iter(*this, NULL); }

    bool insert(const T& d, ulong pos = ULONG_NONE) override;
    bool remove(ulong pos = ULONG_NONE) override;

};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(NULL), tail(NULL)
{
    this->len = 0;

    for (Iter i = other.begin(); i != other.end(); ++i) {
        if (FALSE == insert(*i)) {
            clear();
            break;
        }
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if (*this == other)
        return *this;

    clear();
    for (Iter i = other.begin(); i != other.end(); i++)
        if (FALSE == insert(*i))
            return FALSE;

    return *this;
}

template <typename T>
bool LinkedList<T>::clear()
{
    while (remove() == TRUE)
        continue;

    return TRUE;
}

template <typename T>
bool LinkedList<T>::Iter::insertBefore(const T& d)
{
    Item*       i = new Item(d, curr->prev, curr);

    if (curr->prev != NULL)
        curr->prev->next = i;
    else
        list.head = i;

    if (curr != NULL)
        curr->prev = i;
    else
        list.tail = i;

    list.len++;
    return TRUE;
}

template <typename T>
bool LinkedList<T>::Iter::insertAfter(const T& d)
{
    Item*       i;

    if (curr == NULL)
        return FALSE;

    i = new Item(d, curr, curr->next);

    if (curr->next != NULL)
        curr->next->prev = i;
    else
        tail = i;

    curr->next = i;
    this->len++;
    return TRUE;
}

template <typename T>
bool LinkedList<T>::Iter::remove()
{
    Item*       i;

    if (curr == NULL)
        return FALSE;

    i = curr->next;
    if (curr->prev != NULL)
        curr->prev->next = curr->next;
    else
        list.head = curr->next;

    if (curr->next != NULL)
        curr->next->prev = curr->prev;
    else
        list.tail = curr->prev;

    delete curr;
    list.len--;
    curr = i;
    return TRUE;
}

template <typename T>
bool LinkedList<T>::insert(const T& d, ulong pos)
{
    if (this->len == this->MAX_LEN)
        return FALSE;

    if (pos == ULONG_NONE) {
        Item* newItem = new Item(d);
        if (!tail) {
            head = tail = newItem;
        } else {
            tail->next = newItem;
            newItem->prev = tail;
            tail = newItem;
        }
        this->len++;
        return TRUE;
    } else if (pos > this->len) {
        return FALSE;
    } else {
        Iter iter = begin();
        for (ulong i = 0; i < pos; ++i) {
            ++iter;
        }
        return iter.insertBefore(d);
    }
}

template <typename T>
bool LinkedList<T>::remove(ulong pos)
{
    if (this->len == 0)
        return FALSE;

    if (pos == ULONG_NONE) {
        if (!tail) return FALSE;
        Item* toRemove = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete toRemove;
        this->len--;
        return TRUE;
    } else if (pos >= this->len) {
        return FALSE;
    } else {
        Iter iter = begin();
        for (ulong i = 0; i < pos; ++i) {
            ++iter;
        }
        return iter.remove();
    }
}


template <typename T>
class ArrayList : public List<T>, public RandomAccessible<T, ulong>
{
private:
    Arr<T>  arr;

public:
    ArrayList() : arr(0) { this->len = 0; }
    ~ArrayList() = default;
    ArrayList(const ArrayList<T>& other) = default;
    ArrayList& operator=(const ArrayList<T>& other) = default;

    bool clear() override { this->len = 0; return arr.cleanLen(); }

    class Iter
    // : public Iterator<T>
    {
    public:
        ulong   index;

        Iter(const ulong i = ULONG_NONE) : index(i) {}

        T& operator*() { return arr[index]; }
        Iter& operator++() { if (index < this->len) index++; return *this; }
        Iter operator++(int) { Iter i(index); if (index < this->len) index++; return i; }
        Iter& operator--() { if (index > 0) index--; return *this; }
        Iter operator--(int) { Iter i(index); if (index > 0) index--; return i; }
        bool operator==(const Iter& other) { return index == other.index ? TRUE : FALSE; }
        bool operator!=(const Iter& other) { return index != other.index ? TRUE : FALSE; }

        bool hasNext() const override { return index == this->len ? FALSE : TRUE; }
        Iter& next() override { return *(this++); }

    };

    Iter iter() const { return Iter(0); }
    Iter begin() const { return Iter(0); }
    Iter end() const { return Iter(this->len); }

    T& operator[](ulong i) { return arr[i]; }
    const T& operator[](ulong i) const { return arr[i]; }

    bool insert(const T& d, ulong pos = ULONG_NONE) override;
    bool remove(ulong pos = ULONG_NONE) override;

};

template <typename T>
bool ArrayList<T>::insert(const T& d, ulong pos)
{
    ulong       i;

    if (this->len == this->MAX_LEN)
        return FALSE;

    if (pos == ULONG_NONE) {
        if (arr.ensureCapacity(this->len + 1) == FALSE)
            return FALSE;

        arr[this->len] = d;
        this->len++;
    } else if (pos >= this->len)
        return FALSE;
    else {
        if (arr.ensureCapacity(this->len + 1) == FALSE)
            return FALSE;

        i = this->len;
        while (i > pos)
        {
            arr[i] = arr[i - 1];
            i--;
        }

        arr[pos] = d;
        this->len++;
    }
    return TRUE;
}

template <typename T>
bool ArrayList<T>::remove(ulong pos)
{
    if (this->len == 0)
        return FALSE;

    if (pos == ULONG_NONE)
        this->len--;
    else if (pos >= this->len)
        return FALSE;
    else {
        while (pos != this->len - 1)
        {
            arr[pos] = arr[pos + 1];
            pos++;
        }
        this->len--;
    }
    return TRUE;
}

#endif // LIST_H
