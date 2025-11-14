#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const; //done
	void printReverse() const; //done

	// Accessors
	[[nodiscard]] unsigned int getSize() const; //done
	
	typename LinkedList<T>::Node* getHead(); // i had to manually update these 4 caues it kept throwing an error
	const typename LinkedList<T>::Node* getHead() const;
	typename LinkedList<T>::Node* getTail();
	const typename LinkedList<T>::Node* getTail() const;

	// Insertion
	void addHead(const T& data); //done
	void addTail(const T& data); //done

	// Removal
	bool removeHead(); //done
	bool removeTail(); //done
	void Clear(); //done

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;//done
	LinkedList<T>& operator=(const LinkedList<T>& rhs); //done

	// Construction/Destruction
	LinkedList(); //done
	LinkedList(const LinkedList<T>& list); //done
	LinkedList(LinkedList<T>&& other) noexcept; //done
	~LinkedList(); //done

	void pushFront(const T& item) { addHead(item); } //this wasnt in the insturctions but from gradescope it looks like i need this
	void pushBack(const T& item) { addTail(item); }

	T popFront(); // I had to look this up i didnt get what i was supposed to do https://learn.microsoft.com/en-us/cpp/cpp/templates-cpp?view=msvc-170
	T popBack(); // again i swear this wasnt in the github instructions

	struct Node {
		T data;
		Node* prev;
		Node* next;

		Node(const T& d) {
			data = d;
			prev = nullptr;
			next = nullptr;
		}
	};

private:
	Node* head;
	Node* tail;
	unsigned int count;

};

template <typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
	head = nullptr;
	tail = nullptr;
	count = 0;
	Node* temp = list.head;
	while (temp != nullptr) {
		addTail(temp->data);
		temp = temp->next;
	}
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept {
	head = other.head;
	tail = other.tail;
	count = other.count;
	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Clear();
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	Clear();

	Node* temp = rhs.head;
	while (temp != nullptr) { //same as before
		addTail(temp->data);
		temp = temp->next;
	}
	return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
	if (this == &other) {
		return *this;
	}
	Clear();

	head = other.head;
	tail = other.tail;
	count = other.count;
	other.head = nullptr;
	other.tail = nullptr; //also same as before
	other.count = 0;

	return *this;
}

template <typename T>
void LinkedList<T>::addHead(const T& data) {
	Node* newNode = new Node(data);
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}

	count++;
}

template <typename T>
void LinkedList<T>::addTail(const T& data) {
	Node* newNode = new Node(data);

	if (tail == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}

	count++;
}

template <typename T>
bool LinkedList<T>::removeHead() {
	if (head == nullptr) {
		return false;
	}
	Node* temp = head;
	if (head == tail) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		head = head->next;
		head->prev = nullptr;
	}

	delete temp;
	count--;
	return true;
}

template <typename T>
bool LinkedList<T>::removeTail() {
	if (tail == nullptr) {
		return false;
	}
	Node* temp = tail;
	if (head == tail) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		tail = tail->prev;
		tail->next = nullptr;
	}

	delete temp;
	count--;
	return true;
}

template <typename T>
void LinkedList<T>::Clear() {
	Node* temp = head;

	while (temp != nullptr) {
		Node* nextNode = temp->next;
		delete temp;
		temp = nextNode;
	}

	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <typename T>
unsigned int LinkedList<T>::getSize() const {
	return count;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() {
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::getHead() const {
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getTail() {
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::getTail() const {
	return tail;
}

template <typename T>
void LinkedList<T>::printForward() const {
	Node* temp = head;

	while (temp != nullptr) {
		cout << temp->data << "\n";
		temp = temp->next;
	}

	cout << endl;
}

template <typename T>
void LinkedList<T>::printReverse() const {
	Node* temp = tail;

	while (temp != nullptr) {
		cout << temp->data << "\n";
		temp = temp->prev;
	}

	cout << endl;
}

// I used this for the below: https://learn.microsoft.com/en-us/cpp/cpp/templates-cpp?view=msvc-170
template <typename T>
T LinkedList<T>::popFront() {
    if (!head) {
        throw std::runtime_error("List is empty");
    }
    T value = head->data;
    removeHead();
    return value;
}

template <typename T>
T LinkedList<T>::popBack() {
    if (!tail) {
        throw std::runtime_error("List is empty");
    }
    T value = tail->data;
    removeTail();
    return value;
}