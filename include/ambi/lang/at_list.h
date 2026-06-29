#ifndef AT_LIST_H
#define AT_LIST_H

#include "ambi/mem/at_pool.h"
#include <new>

namespace atdb {


template <typename T, typename size_t = atuint>
class List {
public:
    struct Node {
        T     data;
        Node* prev;
        Node* next;

        Node(const T& val) : data(val), prev(NULL), next(NULL) {}
    };

private:
    MemPool<>           pool;
    Node*               head;
    Node*               tail;
    size_t              len;
    static const size_t NONE_LEN = TYPE_NONE(size_t);

    Node* allocNode(const T& val);
    atvoid freeNode(Node* node);
    Node* nodeAt(size_t pos) const;
    atvoid linkBefore(Node* node, const T& val);
    atvoid linkAfter(Node* node, const T& val);
    atvoid unlinkNode(Node* node);
    Node* mergeNodes(Node* left, Node* right);
    Node* mergeSort(Node* start);

public:
    List(MemPool<> p) : pool(p), head(NULL), tail(NULL), len(0) {}

    List(const List<T, size_t>& s, MemPool<> p);
    List(List<T, size_t>&& s) noexcept;
    List(size_t n, const T& c, MemPool<> p);
    ~List();

    List& operator=(const List<T, size_t>& s);
    List& operator=(List<T, size_t>&& s) noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    atbool empty() const noexcept { return 0 == len; }
    size_t size() const noexcept { return len; }

    atvoid clear();

    List<T, size_t>& insert(size_t pos, const T& c);
    List<T, size_t>& insert(size_t pos, size_t n, const T& c);
    List<T, size_t>& erase(size_t pos, size_t n = 1);

    atvoid push_front(const T& c);
    atvoid push_back(const T& c);
    atvoid pop_front();
    atvoid pop_back();

    List<T, size_t>& assign(const List<T, size_t>& s);
    List<T, size_t>& assign(List<T, size_t>&& s) noexcept;
    List<T, size_t>& assign(size_t n, const T& c);

    atvoid swap(List<T, size_t>& s) noexcept;

    atvoid resize(size_t n);
    atvoid resize(size_t n, const T& c);

    atvoid splice(size_t pos, List<T, size_t>& s);
    atvoid splice(size_t pos, List<T, size_t>& s, size_t spos);
    atvoid splice(size_t pos, List<T, size_t>& s, size_t spos, size_t n);

    atvoid remove(const T& c);
    atvoid unique();
    atvoid merge(List<T, size_t>& s);
    atvoid sort();
    atvoid reverse();

    size_t find(const T& c, size_t pos = 0) const;

    friend atbool operator==(const List<T, size_t>& s1, const List<T, size_t>& s2);
    friend atbool operator!=(const List<T, size_t>& s1, const List<T, size_t>& s2);
    friend atvoid swap(List<T, size_t>& s1, List<T, size_t>& s2);
};

template <typename T, typename size_t>
typename List<T, size_t>::Node* List<T, size_t>::allocNode(const T& val) {
    Node* node = (Node*)pool.alloc(sizeof(Node));
    ::new (node) Node(val);
    return node;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::freeNode(Node* node) {
    if (node != NULL) {
        node->~Node();
        pool.free((atbyte*)node);
    }
}

template <typename T, typename size_t>
typename List<T, size_t>::Node* List<T, size_t>::nodeAt(size_t pos) const {
    if (pos >= len)
        return NULL;

    Node* cur;
    if (pos < len / 2) {
        cur = head;
        for (size_t i = 0; i < pos; i++)
            cur = cur->next;
    } else {
        cur = tail;
        for (size_t i = len - 1; i > pos; i--)
            cur = cur->prev;
    }
    return cur;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::linkBefore(Node* node, const T& val) {
    Node* newNode = allocNode(val);
    newNode->prev = node->prev;
    newNode->next = node;

    if (node->prev != NULL)
        node->prev->next = newNode;
    else
        head = newNode;

    node->prev = newNode;
    len++;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::linkAfter(Node* node, const T& val) {
    Node* newNode = allocNode(val);
    newNode->prev = node;
    newNode->next = node->next;

    if (node->next != NULL)
        node->next->prev = newNode;
    else
        tail = newNode;

    node->next = newNode;
    len++;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::unlinkNode(Node* node) {
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        tail = node->prev;

    freeNode(node);
    len--;
}

template <typename T, typename size_t>
typename List<T, size_t>::Node* List<T, size_t>::mergeNodes(Node* left, Node* right) {
    Node* result = NULL;

    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->data < right->data) {
        result = left;
        result->next = mergeNodes(left->next, right);
        if (result->next != NULL)
            result->next->prev = result;
        result->prev = NULL;
    } else {
        result = right;
        result->next = mergeNodes(left, right->next);
        if (result->next != NULL)
            result->next->prev = result;
        result->prev = NULL;
    }

    return result;
}

template <typename T, typename size_t>
typename List<T, size_t>::Node* List<T, size_t>::mergeSort(Node* start) {
    if (start == NULL || start->next == NULL)
        return start;

    Node* slow = start;
    Node* fast = start->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    Node* mid = slow->next;
    slow->next = NULL;

    Node* left = mergeSort(start);
    Node* right = mergeSort(mid);

    return mergeNodes(left, right);
}

template <typename T, typename size_t>
List<T, size_t>::List(const List<T, size_t>& s, MemPool<> p) : pool(p), head(NULL), tail(NULL), len(0) {
    Node* cur = s.head;
    while (cur != NULL) {
        push_back(cur->data);
        cur = cur->next;
    }
}

template <typename T, typename size_t>
List<T, size_t>::List(List<T, size_t>&& s) noexcept : pool(s.pool), head(s.head), tail(s.tail), len(s.len) {
    s.head = NULL;
    s.tail = NULL;
    s.len  = 0;
}

template <typename T, typename size_t>
List<T, size_t>::List(size_t n, const T& c, MemPool<> p) : pool(p), head(NULL), tail(NULL), len(0) {
    for (size_t i = 0; i < n; i++)
        push_back(c);
}

template <typename T, typename size_t>
List<T, size_t>::~List() {
    clear();
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::operator=(const List<T, size_t>& s) {
    if (this == &s)
        return *this;

    clear();

    Node* cur = s.head;
    while (cur != NULL) {
        push_back(cur->data);
        cur = cur->next;
    }

    return *this;
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::operator=(List<T, size_t>&& s) noexcept {
    if (this == &s)
        return *this;

    clear();

    head = s.head;
    tail = s.tail;
    len  = s.len;

    s.head = NULL;
    s.tail = NULL;
    s.len  = 0;

    return *this;
}

template <typename T, typename size_t>
T& List<T, size_t>::front() {
    at_assert(head != NULL);
    return head->data;
}

template <typename T, typename size_t>
const T& List<T, size_t>::front() const {
    at_assert(head != NULL);
    return head->data;
}

template <typename T, typename size_t>
T& List<T, size_t>::back() {
    at_assert(tail != NULL);
    return tail->data;
}

template <typename T, typename size_t>
const T& List<T, size_t>::back() const {
    at_assert(tail != NULL);
    return tail->data;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::clear() {
    Node* cur = head;
    while (cur != NULL) {
        Node* next = cur->next;
        freeNode(cur);
        cur = next;
    }
    head = NULL;
    tail = NULL;
    len  = 0;
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::insert(size_t pos, const T& c) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    if (pos == 0) {
        push_front(c);
    } else if (pos == len) {
        push_back(c);
    } else {
        Node* cur = nodeAt(pos);
        linkBefore(cur, c);
    }

    return *this;
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::insert(size_t pos, size_t n, const T& c) {
    for (size_t i = 0; i < n; i++)
        insert(pos + i, c);
    return *this;
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::erase(size_t pos, size_t n) {
    if (pos >= len)
        throw Code::OUT_OF_RANGE;

    size_t eraseLen = n;
    if (eraseLen > len - pos)
        eraseLen = len - pos;

    for (size_t i = 0; i < eraseLen; i++) {
        Node* cur = nodeAt(pos);
        unlinkNode(cur);
    }

    return *this;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::push_front(const T& c) {
    Node* node = allocNode(c);
    node->next = head;

    if (head != NULL)
        head->prev = node;
    else
        tail = node;

    head = node;
    len++;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::push_back(const T& c) {
    Node* node = allocNode(c);
    node->prev = tail;

    if (tail != NULL)
        tail->next = node;
    else
        head = node;

    tail = node;
    len++;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::pop_front() {
    at_assert(head != NULL);
    Node* old = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;
    else
        tail = NULL;

    freeNode(old);
    len--;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::pop_back() {
    at_assert(tail != NULL);
    Node* old = tail;
    tail = tail->prev;

    if (tail != NULL)
        tail->next = NULL;
    else
        head = NULL;

    freeNode(old);
    len--;
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::assign(const List<T, size_t>& s) {
    return operator=(s);
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::assign(List<T, size_t>&& s) noexcept {
    return operator=(static_cast<List<T, size_t>&&>(s));
}

template <typename T, typename size_t>
List<T, size_t>& List<T, size_t>::assign(size_t n, const T& c) {
    clear();
    for (size_t i = 0; i < n; i++)
        push_back(c);
    return *this;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::swap(List<T, size_t>& s) noexcept {
    MemPool<> tmpPool = pool;
    Node* tmpHead = head;
    Node* tmpTail = tail;
    size_t tmpLen = len;

    pool = s.pool;
    head = s.head;
    tail = s.tail;
    len  = s.len;

    s.pool = tmpPool;
    s.head = tmpHead;
    s.tail = tmpTail;
    s.len  = tmpLen;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::resize(size_t n) {
    while (len > n)
        pop_back();

    if (len < n) {
        for (size_t i = len; i < n; i++)
            push_back(T());
    }
}

template <typename T, typename size_t>
atvoid List<T, size_t>::resize(size_t n, const T& c) {
    while (len > n)
        pop_back();

    if (len < n) {
        for (size_t i = len; i < n; i++)
            push_back(c);
    }
}

template <typename T, typename size_t>
atvoid List<T, size_t>::splice(size_t pos, List<T, size_t>& s) {
    splice(pos, s, 0, s.len);
}

template <typename T, typename size_t>
atvoid List<T, size_t>::splice(size_t pos, List<T, size_t>& s, size_t spos) {
    splice(pos, s, spos, 1);
}

template <typename T, typename size_t>
atvoid List<T, size_t>::splice(size_t pos, List<T, size_t>& s, size_t spos, size_t n) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    if (spos >= s.len || 0 == n)
        return;

    size_t copyLen = n;
    if (copyLen > s.len - spos)
        copyLen = s.len - spos;

    for (size_t i = 0; i < copyLen; i++) {
        Node* cur = s.nodeAt(spos);
        if (cur == NULL) break;

        if (cur->prev != NULL)
            cur->prev->next = cur->next;
        else
            s.head = cur->next;

        if (cur->next != NULL)
            cur->next->prev = cur->prev;
        else
            s.tail = cur->prev;

        s.len--;

        Node* atNode = nodeAt(pos);
        if (atNode != NULL) {
            cur->prev = atNode->prev;
            cur->next = atNode;

            if (atNode->prev != NULL)
                atNode->prev->next = cur;
            else
                head = cur;

            atNode->prev = cur;
        } else {
            cur->prev = tail;
            cur->next = NULL;

            if (tail != NULL)
                tail->next = cur;
            else
                head = cur;

            tail = cur;
        }

        len++;
        pos++;
    }
}

template <typename T, typename size_t>
atvoid List<T, size_t>::remove(const T& c) {
    Node* cur = head;
    while (cur != NULL) {
        Node* next = cur->next;
        if (cur->data == c)
            unlinkNode(cur);
        cur = next;
    }
}

template <typename T, typename size_t>
atvoid List<T, size_t>::unique() {
    Node* cur = head;
    while (cur != NULL && cur->next != NULL) {
        if (cur->data == cur->next->data) {
            Node* dup = cur->next;
            cur->next = dup->next;

            if (dup->next != NULL)
                dup->next->prev = cur;
            else
                tail = cur;

            freeNode(dup);
            len--;
        } else {
            cur = cur->next;
        }
    }
}

template <typename T, typename size_t>
atvoid List<T, size_t>::merge(List<T, size_t>& s) {
    if (this == &s)
        return;

    Node* cur1 = head;
    Node* cur2 = s.head;

    Node dummy(T());
    Node* tail_ = &dummy;
    tail_->next = NULL;

    while (cur1 != NULL && cur2 != NULL) {
        if (cur1->data < cur2->data) {
            tail_->next = cur1;
            cur1->prev = tail_;
            cur1 = cur1->next;
        } else {
            tail_->next = cur2;
            cur2->prev = tail_;
            cur2 = cur2->next;
        }
        tail_ = tail_->next;
    }

    if (cur1 != NULL) {
        tail_->next = cur1;
        cur1->prev = tail_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }

    if (cur2 != NULL) {
        tail_->next = cur2;
        cur2->prev = tail_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }

    head = dummy.next;
    if (head != NULL)
        head->prev = NULL;

    if (tail_ != NULL)
        tail_->next = NULL;
    tail = tail_;

    len += s.len;
    s.head = NULL;
    s.tail = NULL;
    s.len  = 0;
}

template <typename T, typename size_t>
atvoid List<T, size_t>::sort() {
    if (head == NULL || head->next == NULL)
        return;

    Node* sorted = mergeSort(head);

    head = sorted;
    if (head != NULL) {
        head->prev = NULL;
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
    }
}

template <typename T, typename size_t>
atvoid List<T, size_t>::reverse() {
    Node* cur = head;
    Node* tmp = NULL;

    while (cur != NULL) {
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    }

    if (tmp != NULL)
        head = tmp->prev;

    Node* cur2 = head;
    if (head != NULL) {
        while (cur2->next != NULL)
            cur2 = cur2->next;
        tail = cur2;
    }
}

template <typename T, typename size_t>
size_t List<T, size_t>::find(const T& c, size_t pos) const {
    if (pos >= len)
        return NONE_LEN;

    Node* cur = nodeAt(pos);
    size_t i = pos;

    while (cur != NULL) {
        if (cur->data == c)
            return i;
        cur = cur->next;
        i++;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
atbool operator==(const List<T, size_t>& s1, const List<T, size_t>& s2) {
    if (s1.len != s2.len)
        return FALSE;

    typename List<T, size_t>::Node* cur1 = s1.head;
    typename List<T, size_t>::Node* cur2 = s2.head;

    while (cur1 != NULL) {
        if (!(cur1->data == cur2->data))
            return FALSE;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    return TRUE;
}

template <typename T, typename size_t>
atbool operator!=(const List<T, size_t>& s1, const List<T, size_t>& s2) {
    return !(s1 == s2);
}

template <typename T, typename size_t>
atvoid swap(List<T, size_t>& s1, List<T, size_t>& s2) {
    s1.swap(s2);
}


} // end namespace atdb

#endif // AT_LIST_H
