#include <bits/stdc++.h>
#define Shelter main
using namespace std;

#define endFunc cout << "\n"

template<class T>
class Node {
    T data;
    Node *next, *prev;
    public:
        Node() { next = prev = nullptr; }
        Node(T val, Node<T> *tmpNext = nullptr, Node<T> *tmpPrev = nullptr) { data = val; next = tmpNext; prev = tmpPrev; }
        void setVal(T val) { data = val; }
        void setNext(Node<T> *tmpNext = nullptr) { next = tmpNext; }
        void setPrev(Node<T> *tmpPrev = nullptr) { prev = tmpPrev; }
        T &getVal() { return data; } 
        Node<T> *&getNext() { return next; }
        Node<T> *&getPrev() { return prev; }
};

template<class T>
class DoubleListIterator {
    Node<T> *curr;
    public:
        DoubleListIterator() { curr = nullptr; }
        DoubleListIterator(Node<T> *tmp) { curr = tmp; }
        Node<T> *getCurr() { return curr; }
		DoubleListIterator<T> &operator = (DoubleListIterator<T> tmp) {
			this->curr = tmp.getCurr();
			return *this;
		}
        bool operator == (DoubleListIterator<T> tmp) {
            return curr == tmp.getCurr();
        }
		bool operator != (DoubleListIterator<T> tmp) {
			return curr != tmp.getCurr();
		}
        DoubleListIterator<T> operator + (int t) {
            Node<T> *temp = curr;
            while (t--) temp = temp->getNext();
            return temp;
        }
		DoubleListIterator<T> operator ++ (int) {
			Node<T> *temp = curr;
			curr = curr->getNext();
			return temp;
		}
		DoubleListIterator<T> operator ++ () {
			curr = curr->getNext();
			return curr;
		}
		T &operator * () { return curr->getVal(); }       
};

template<class T>
class DoubleListReverseIterator {
    Node<T> *curr;
    public:
        DoubleListReverseIterator() { curr = nullptr; }
        DoubleListReverseIterator(Node<T> *tmp) { curr = tmp; }
        Node<T> *getCurr() { return curr; }
		DoubleListReverseIterator<T> &operator = (DoubleListReverseIterator<T> tmp) {
			this->curr = tmp.getCurr();
			return *this;
		}
		bool operator != (DoubleListReverseIterator<T> tmp) {
			return curr != tmp.getCurr();
		}
		DoubleListReverseIterator<T> operator ++ (int) {
			Node<T> *temp = curr;
			curr = curr->getPrev();
			return temp;
		}
		DoubleListReverseIterator<T> operator ++ () {
			curr = curr->getPrev();
			return curr;
		}
		T &operator * () { return curr->getVal(); }       
};

template<class T>
class DoubleList {
    int n;
    Node<T> *head, *tail;
    public:
        DoubleList() { head = tail = nullptr; n = 0; }
        DoubleList(int size, T val) {
            head = tail = nullptr; n = 0;
            for (int i = 0; i < size; i++) push_back(val);
        }
        DoubleListIterator<T> begin() { return head; }
        DoubleListIterator<T> end() { return nullptr; }
        DoubleListReverseIterator<T> rbegin() { return tail; }
        DoubleListReverseIterator<T> rend() { return nullptr; }
        int size() { return n; }
        bool empty() { return n == 0; }
        T &front() { return head->getVal(); }
        T &back() { return tail->getVal(); }
        void push_front(T val) {
            head = new Node<T> (val, head, nullptr);
            if (n == 0) tail = head;
            else head->getNext()->setPrev(head);
            n++;
        }
        void push_back(T val) {
            if (n == 0) push_front(val);
            else {
                tail->setNext(new Node<T> (val, nullptr, tail));
                tail = tail->getNext();
                n++;
            }
        }
        void pop_front() {
            if (n == 0) return;
            else if (n == 1) {
                head = tail = nullptr;
                n--;
            } else {
                head = head->getNext();
                n--;
            }
        }
        void pop_back() {
            if (n == 0) return;
            else if (n == 1) {
                head = tail = nullptr;
                n--;
            } else {
                tail->setPrev(tail->getPrev());
                tail->setNext(nullptr);
                n--;
            }
        }
        void insert(DoubleListIterator<T> it, T val) {
            if (it == end()) {
                push_back(val);
                return ;
            }

            Node<T> *pos = it.getCurr();
            Node<T> *newNode = new Node<T>(val);

            newNode->setNext(pos);
            newNode->setPrev(pos->getPrev());

            if (pos->getPrev()) pos->getPrev()->setNext(newNode);
            pos->setPrev(newNode);
            if (pos == head) head = newNode;
        }
        void erase(DoubleListIterator<T> it) {
            Node<T> *nodeToDelete = it.getCurr();
            if (nodeToDelete->getNext()) {
                nodeToDelete->getNext()->setPrev(nodeToDelete->getPrev());
            }
            if (nodeToDelete->getPrev()) {
                nodeToDelete->getPrev()->setNext(nodeToDelete->getNext());
            }
            if (nodeToDelete == head) {
                head = nodeToDelete->getNext();
            }
            if (nodeToDelete == tail) {
                tail = nodeToDelete->getPrev();
            }
            delete nodeToDelete;
        }

        void delDupp() {
            if (n == 1) return;
            unordered_set<int> seen;
            Node<T> *curr = head;
            seen.insert(curr->getVal());
            while (curr->getNext()) {
                if (seen.find(curr->getNext()->getVal()) != seen.end()) {
                    curr->setNext(curr->getNext()->getNext());
                    curr->getNext()->setPrev(curr);
                    n--;
                } else {
                    seen.insert(curr->getNext()->getVal());
                    curr = curr->getNext();
                }
            }
        }

        void incSort() {
            head = MergeSort(head);

            Node<T> *curr = head;
            while (curr->getNext() != nullptr) curr = curr->getNext();
            tail = curr;
        }

        void incInsert(T val) {
            Node<T> *newNode = new Node<T>(val);
            Node<T> *curr = head;
            while (curr->getVal() < newNode->getVal()) curr = curr->getNext();
            newNode->setNext(curr);
            curr = curr->getPrev();
            curr->setNext(newNode);
            newNode->setPrev(curr);
            curr->getNext()->getNext()->setPrev(newNode);

            n++;
        }

        void fun(int &x) {
            int t = (pow(x,2) - 7*x + 3);
            t %= 100;
            x = t;
        }
};

template <class T>
Node<T> *split(Node<T> *head) {
    Node<T> *fast = head;
    Node<T> *slow = head;
    while (fast != NULL && fast->getNext() != NULL && fast->getNext()->getNext() != NULL) {
        fast = fast->getNext()->getNext();
        slow = slow->getNext();
    }
    Node<T> *temp = slow->getNext();
    slow->setNext(NULL);
    if (temp != NULL) temp->setPrev(NULL);
    return temp;
}

template <class T>
Node<T> *merge(Node<T> *first, Node<T> *second) {
    if (first == NULL) return second;
    if (second == NULL) return first;

    if (first->getVal() < second->getVal()) {
        first->setNext(merge(first->getNext(), second));
        if (first->getNext() != NULL) {
            first->getNext()->setPrev(first);
        }
        first->setPrev(NULL);
        return first;
    } else {
        second->setNext(merge(first, second->getNext()));
        if (second->getNext() != NULL) {
            second->getNext()->setPrev(second);
        }
        second->setPrev(NULL);
        return second;
    }
}

template <class T>
Node<T> *MergeSort(Node<T> *head) {
    if (head == NULL || head->getNext() == NULL) {
        return head;
    }
    Node<T> *second = split(head);
    head = MergeSort(head);
    second = MergeSort(second);
    return merge(head, second);
}

Shelter() {
    freopen("inp.txt", "r", stdin);
    // freopen("out.txt", "w", stdin);

    int n; cin >> n;
    DoubleList<int> dList;

    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        dList.push_back(t);
    }

    cout << "Normal export: ";
    for (auto it = dList.begin(); it != dList.end(); it++) cout << *it << " ";

    endFunc;

    dList.delDupp();
    cout << "After deleted dupplicate: ";
    for (auto x:dList) cout << x << " ";

    endFunc;

    for (auto &x:dList) {
        dList.fun(x);
    }
    dList.delDupp();
    cout << "After func() and delDupp: ";
    for (auto x:dList) cout << x << " ";

    endFunc;

    dList.incSort();
    cout << "After sorted: ";
    for (auto x:dList) cout << x << " ";

    endFunc;

    dList.incInsert(4);
    cout << "After increase inserted 4: ";
    for (auto x:dList) cout << x << " ";

    endFunc;

    cout << "Decrease export: ";
    for (auto it = dList.rbegin(); it != dList.rend(); it++) {
        cout << *it << " ";
    }

    endFunc;

    dList.insert(dList.begin() + 4, 5);
    cout << "Insert test: ";
    for (auto x:dList) cout << x << " ";

    endFunc;

    dList.erase(dList.begin() + 4);
    cout << "Erase test: ";
    for (auto x:dList) cout << x << " ";
}