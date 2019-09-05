#include <iostream>
using namespace std;
template <class Type>
struct nodeType{
	Type info;
	nodeType<Type> *link;
};

template <class Type>
class linkedListIterator{
	public:
		linkedListIterator();
		linkedListIterator(nodeType<Type> *ptr);
		Type operator*();
		linkedListIterator<Type> operator++();
		bool operator==(const linkedListIterator<Type>& right) const;
		bool operator!=(const linkedListIterator<Type>& right) const;
	private:
		nodeType<Type> *current;
};

template <class Type>
linkedListIterator<Type>::linkedListIterator(){
	current = NULL;
}

template <class Type>linkedListIterator<Type>::linkedListIterator(nodeType<Type> *ptr){
	current = ptr;
}

template <class Type>
Type linkedListIterator<Type>::operator*(){
	return current->info;
}

template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++(){
	current = current->link;
	return *this;
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const{
	return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const{
	return (current != right.current);
}

template <class Type>
class linkedListType{
	public:
		const linkedListType<Type>& operator=(const linkedListType<Type>&);
		void initializeList();
		bool isEmptyList() const;
		void print() const;
		int length() const;
		void destroyList();
		Type front() const;
		Type back() const;
		virtual bool search(const Type& searchItem) const = 0;
		virtual void insertFirst(const Type& newItem) = 0;
		virtual void insertLast(const Type& newItem) = 0;
		virtual void deleteNode(const Type& deleteItem) = 0;
		linkedListIterator<Type> begin();
		linkedListIterator<Type> end();
		linkedListType();
		linkedListType(const linkedListType<Type>& otherList);
		~linkedListType();
	protected:
		int count;
		nodeType<Type> *first;
		nodeType<Type> *last;
	private:
		void copyList(const linkedListType<Type>& otherList);
};

template <class Type>
bool linkedListType<Type>::isEmptyList() const{
	return (first == NULL);
}

template <class Type>
linkedListType<Type>::linkedListType(){
	first = NULL;
	last = NULL;
	count = 0;
}

template <class Type>
void linkedListType<Type>::destroyList(){
	nodeType<Type> *temp;
	while (first != NULL){
		temp = first;
		first = first->link;
		delete temp;
	}
	last = NULL;
	count = 0;
}

template <class Type>
void linkedListType<Type>::initializeList(){
	destroyList();
}

template <class Type>
void linkedListType<Type>::print() const{
	nodeType<Type> *current;
	current = first;
	cout<<"[ ";
	if(current == NULL)
		cout<<"No hay nada\n";
	while (current != NULL){
		cout << current->info << " ";
		current = current->link;
	}
	cout<<"] ";
}

template <class Type>
int linkedListType<Type>::length() const{
	return count;
}

template <class Type>
Type linkedListType<Type>::front() const{
	assert(first != NULL);
	return first->info;
}

template <class Type>
Type linkedListType<Type>::back() const{
	assert(last != NULL);
	return last->info;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin(){
	linkedListIterator<Type> temp(first);
	return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end(){
	linkedListIterator<Type> temp(NULL);
	return temp;
}

template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type>& otherList){
	nodeType<Type> *newNode;
	nodeType<Type> *current;
	if (first != NULL)
		destroyList();
	if (otherList.first == NULL){
		first = NULL;
		last = NULL;
		count = 0;
	}else{
		current = otherList.first;
		count = otherList.count;
		first = new nodeType<Type>;
		first->info = current->info;
		first->link = NULL;
		last = first;
		current = current->link;
		while (current != NULL){
			newNode = new nodeType<Type>;
			newNode->info = current->info;
			newNode->link = NULL;
			last->link = newNode;
			last = newNode;
			current = current->link;
		}
	}
}

template <class Type>
linkedListType<Type>::~linkedListType(){
	destroyList();
}

template <class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type>& otherList){
	first = NULL;
	copyList(otherList);
}

template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(const linkedListType<Type>& otherList){
	if (this != &otherList){
		copyList(otherList);
	}
	return *this;
}

//
// LISTA DESORDENADA
//

template <class Type>
class unorderedLinkedList: public linkedListType<Type>{
	public:
	bool search(const Type& searchItem) const;
	void insertFirst(const Type& newItem);
	void insertLast(const Type& newItem);
	void deleteNode(const Type& deleteItem);
};

template <class Type>
bool unorderedLinkedList<Type>::search(const Type& searchItem) const{
	nodeType<Type> *current;
	bool found = false;
	current = this->first;
	while (current != NULL && !found)
		if (current->info == searchItem)
			found = true;
		else
			current = current->link;
	return found;
}

template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& newItem){
	nodeType<Type> *newNode;
	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = this->first;
	this->first = newNode;
	this->count++;
	if (this->last == NULL)
		this->last = newNode;
}

template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type& newItem){
	nodeType<Type> *newNode; 
	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = NULL;
	if (this->first == NULL){
		this->first = newNode;
		this->last = newNode;
		this->count++;
	}else{
		this->last->link = newNode;
		this->last = newNode;
		this->count++;
	}
}

template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem){
	nodeType<Type> *current;
	nodeType<Type> *trailCurrent;
	bool found;
	if (this->first == NULL)
	cout << "No se puede eliminar de una lista vacía."<< endl;
	else{
		if (this->first->info == deleteItem){
			current = this->first;
			this->first = this->first->link;
			this->count--;
			if (this->first == NULL)
				this->last = NULL;
			delete current;
		}else{
			found = false;
			trailCurrent = this->first;
			current = this->first->link;
			while (current != NULL && !found){
				if (current->info != deleteItem){
					trailCurrent = current;
					current = current-> link;
				}else
					found = true;
			}
			if (found){
				trailCurrent->link = current->link;
				this->count--;
				if (this->last == current)
					this->last = trailCurrent;
				delete current;
			}
			else
				cout << "El item a ser eliminado no está en la lista." << endl;
		}
	}
}

//
// LISTA ORDENADA
//

template <class Type>
class orderedLinkedList: public linkedListType<Type>{
	public:
	bool search(const Type& searchItem) const;
	void insert(const Type& newItem);
	void insertFirst(const Type& newItem);
	void insertLast(const Type& newItem);
	void deleteNode(const Type& deleteItem);
};

template <class Type>
bool orderedLinkedList<Type>::search(const Type& searchItem) const{
	bool found = false;
	nodeType<Type> *current;
	current = this->first;
	while (current != NULL && !found)
		if (current->info >= searchItem)
			found = true;
		else
			current = current->link;
	if (found)
		found = (current->info == searchItem);
	return found;
}

template <class Type>
void orderedLinkedList<Type>::insert(const Type& newItem){
	nodeType<Type> *current;
	nodeType<Type> *trailCurrent;
	nodeType<Type> *newNode;
	bool found;
	newNode = new nodeType<Type>;
	newNode->info = newItem;
	newNode->link = NULL;
	if (this->first == NULL){
		this->first = newNode;
		this->last = newNode;
		this->count++;
	}else{
		current = this->first;
		found = false;
		while (current != NULL && !found)
			if (current->info >= newItem)
				found = true;
			else{
				trailCurrent = current;
				current = current->link;
			}
		if (current == this->first){
			newNode->link = this->first;
			this->first = newNode;
			this->count++;
		}else{
			trailCurrent->link = newNode;
			newNode->link = current;
			if (current == NULL)
				this->last = newNode;
				this->count++;
		}
	}
}

template <class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem){
	insert(newItem);
}

template <class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem){
	insert(newItem);
}

template <class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem){
	nodeType<Type> *current;
	nodeType<Type> *trailCurrent;
	bool found;
	if (this->first == NULL)
		cout << "No se puede eliminar de una lista vacia" << endl;
	else{
		current = this->first;
		found = false;
		while (current != NULL && !found)
			if (current->info >= deleteItem)
				found = true;
			else{
				trailCurrent = current;
				current = current->link;
			}
		if (current == NULL)
			cout << "El elemento a ser eliminado no está en la lista"<< endl;
		else
			if (current->info == deleteItem){
				if (this->first == current){
					this->first = this->first->link;
					if (this->first == NULL)
						this->last = NULL;
						delete current;
			}else{
				trailCurrent->link = current->link;
				if (current == this->last)
					this->last = trailCurrent;
				delete current;
				}
			this->count--;
		}else
			cout << "El elemento a ser eliminado no está en la lista" << endl;
	}
}

int main(){
	orderedLinkedList<int> list1, list2;
	int num;
	cout << "Ingrese números terminando con -999." << endl;
	cin >> num;
	while (num != -999){
		list1.insert(num);
		cin >> num;
	}
	cout << endl; 
	cout << "Lista 1: ";
	list1.print();
	cout << endl;
	list2 = list1;
	cout << "Lista 2: ";
	list2.print();
	cout << endl;
	cout << "Ingrese número a ser eliminado: ";
	cin >> num;
	cout << endl;
	list2.deleteNode(num);
	cout << "Despues de eliminar \" "<< num << " \" \nLista 2: ";
	list2.print();
	cout << endl;
	return 0;
}