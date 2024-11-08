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
		bool operator != (DoubleListIterator<T> tmp) {
			return curr != tmp.getCurr();
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
        DoubleListIterator<T> operator -- (int) {
            Node<T> *temp = curr;
            curr = curr->getPrev();
            return temp;
        }
        DoubleListIterator<T> operator -- () { 
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
        DoubleListIterator<T> rbegin() { return tail; }
        DoubleListIterator<T> rend() { return nullptr; }
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
        void insert(int pos, T val) {
            if (pos < 0 || pos >= n) return;
            if (pos == 0) push_front(val);
            else if (pos == n-1) push_back(val);
            else {
                Node<T> *newNode(val, nullptr);
                Node<T> *currNode = head;
                for (int i = 0; i < pos; i++) {
                    currNode = currNode->next();
                }
                newNode->setPrev(currNode->getPrev());
                newNode->setNext(currNode);
                currNode->getPrev()->setNext(newNode);
                currNode->setPrev(newNode);
            }  
        }
        void erase(int pos) {
            if (pos < 0 || pos >= n) return;
            else {
                if (pos == 0) pop_front();
                else if (pos == n-1) pop_back();
                else {
                    Node<T> *currNode = head;
                    for (int i = 0; i < pos; i++) currNode = currNode->getNext();
                    currNode->setNext(currNode->getNext()->getNext());
                    currNode->getNext()->getNext()->setPrev(currNode);
                }
            }
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
            if (head == nullptr || n == 1) return ;
            Node<T> *sortedHead = nullptr;
            Node<T> *curr = head;
            while (curr != nullptr) {
                Node<T> *next = curr->getNext();
                if (sortedHead == nullptr || sortedHead->getVal() >= curr->getVal()) {
                    curr->setNext(sortedHead);
                    if (sortedHead != nullptr) sortedHead->setPrev(curr);
                    sortedHead = curr;
                    sortedHead->setPrev(nullptr);
                } else {
                    Node<T> *current_sorted = sortedHead;
                    while (current_sorted->getNext() != nullptr && current_sorted->getNext()->getVal() < curr->getVal()) {
                        current_sorted = current_sorted->getNext();
                    }
                    curr->setNext(current_sorted->getNext());
                    if (current_sorted->getNext() != nullptr)  current_sorted->getNext()->getPrev() = curr;
                    current_sorted->setNext(curr);
                    curr->setPrev(current_sorted);
                }
                if (curr->getNext() != nullptr) tail = curr->getNext();
                curr = next;
            }
            head = sortedHead;
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
    for (auto it = dList.rbegin(); it != dList.rend(); it--) {
        cout << *it << " ";
    }
}