#include <iostream>
using namespace std;
class nodo;
class lista;
struct node{
	int value;
	node *left;
	node *right;
};

class btree{
public:
	btree();
	~btree();

	void insert(int key);
	node *search(int key);
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();
    void recorrer(nodo*, btree*);
private:
	void destroy_tree(node *leaf);
	void insert(int key, node *leaf);
	node *search(int key, node *leaf);
	void inorder_print(node *leaf);
	void postorder_print(node *leaf);
	void preorder_print(node *leaf);

	node *root;
};


btree::btree(){
	root = NULL;
}

btree::~btree(){
	destroy_tree();
}

void btree::destroy_tree(node *leaf){
	if(leaf != NULL){
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(int key, node *leaf){

	if(key < leaf->value){
		if(leaf->left != NULL){
			insert(key, leaf->left);
		}else{
			leaf->left = new node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}else if(key >= leaf->value){
		if(leaf->right != NULL){
			insert(key, leaf->right);
		}else{
			leaf->right = new node;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}

}

void btree::insert(int key){
	if(root != NULL){
		insert(key, root);
	}else{
		root = new node;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

node *btree::search(int key, node *leaf){
	if(leaf != NULL){
		if(key == leaf->value){
			return leaf;
		}
		if(key < leaf->value){
			return search(key, leaf->left);
		}else{
			return search(key, leaf->right);
		}
	}else{
		return NULL;
	}
}

node *btree::search(int key){
	return search(key, root);
}

void btree::destroy_tree(){
	destroy_tree(root);
}

void btree::inorder_print(){
	inorder_print(root);
	cout << "\n";
}

void btree::inorder_print(node *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

void btree::postorder_print(){
	postorder_print(root);
	cout << "\n";
}

void btree::postorder_print(node *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->value << ",";
	}
}

void btree::preorder_print(){
	preorder_print(root);
	cout << "\n";
}

void btree::preorder_print(node *leaf){
	if(leaf != NULL){
		cout << leaf->value << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}
void recorrer(nodo* ldoble, btree *leaf){
	if(leaf != NULL){
		recorrer(ldoble,leaf->left);
		//cout << leaf->value << ",";
		ldoble->Insertar(leaf->value);
		recorrer(ldoble,leaf->right);
	}
}
/*
struct ldoble{
    node* head, tail;
    int size;
    ldoble(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    /*ldoble(int x){
        head = NULL;
        tail = NULL;
        
    }
    void push(int x){
        node* ptr = new node;
        if(head = NULL){
            ptr-> value = x;
            head = ptr;
            tail = ptr;
        }else{
            //tail->right = ptr;
            
        }
    }
};*/
class nodo {
   public:
    nodo(int v, nodo *sig = NULL, nodo *ant = NULL) :valor(v), siguiente(sig), anterior(ant) {}
   private:
    int valor;
    nodo *siguiente;
    nodo *anterior;
   friend class lista;
};

typedef nodo *pnodo;

class lista{
   public:
    lista() : plista(NULL) {}
    ~lista();
    void Insertar(int v);
    void Mostrar(int);
    void Siguiente();
    void Anterior();
    void Primero();
    void Ultimo();
    bool Actual() { return plista != NULL; }
    int ValorActual() { return plista-&gt;valor; }
    
   private:
    pnodo plista;
};

lista::~lista() {
   pnodo aux;
   Primero();
   while(plista) {
      aux = plista;
      plista = plista->siguiente;
      delete aux;
   }
}

void lista::Insertar(int v) {
   pnodo nuevo;
   Primero();
   if(ListaVacia() || plista->valor > v) {
      nuevo = new nodo(v, plista);
      if(!plista) plista = nuevo;
      else plista->anterior = nuevo;
   }
   else {
      while(plista->siguiente && plista->siguiente->valor <= v) Siguiente();
      nuevo = new nodo(v, plista->siguiente, plista);
      plista->siguiente = nuevo;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
   }
}

void lista::Borrar(int v) {
   pnodo nodo;
   nodo = plista;
   while(nodo && nodo->valor < v) nodo = nodo->siguiente;
   while(nodo && nodo->valor > v) nodo = nodo->anterior;

   if(!nodo || nodo->valor != v) return;
   if(nodo->anterior)
      nodo->anterior->siguiente = nodo->siguiente;
   if(nodo->siguiente)
      nodo->siguiente->anterior = nodo->anterior;
   delete nodo;
}

void lista::Mostrar(int orden) {
   pnodo nodo;
   if(orden == ASCENDENTE) {
      Primero();
      nodo = plista;
      while(nodo) {
         cout << nodo->valor << "-> ";
         nodo = nodo->siguiente;
      }
   }
   else {
      Ultimo();
      nodo = plista;
      while(nodo) {
         cout << nodo->valor << "-> ";
         nodo = nodo->anterior;
      }
   }
   cout << endl;
}

void lista::Siguiente() {
   if(plista) plista = plista->siguiente;
}

void lista::Anterior() {
   if(plista) plista = plista->anterior;
}

void lista::Primero() {
   while(plista && plista->anterior) plista = plista->anterior;
}

void lista::Ultimo() {
   while(plista && plista->siguiente) plista = plista->siguiente;
}
int main(){
	btree *tree = new btree();
	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);
	//tree->preorder_print();
	tree->inorder_print();
	//tree->postorder_print();
	ldoble r;
	tree->recorrer(r,tree);
	delete tree;

}
