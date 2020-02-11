#include <iostream>
using namespace std;
struct nodo{
	int dato;
	nodo *izq,*der;
	nodo(){
		izq = der = nullptr;
	}
	nodo(int x){
		dato = x;
		izq = der = nullptr;
	}
};
class abb{
	nodo* root;
	void ver_in(nodo* root){
		if(root){
			ver_in(root->izq);
			cout<<root->dato<<' ';
			ver_in(root->der);
		}
	}
	void ver_pre(nodo* root){
		if(root){
			cout<<root->dato<<' ';
			ver_pre(root->izq);
			ver_pre(root->der);
		}
	}
	void ver_pos(nodo* root){
		if(root){
			ver_pos(root->izq);
			ver_pos(root->der);
			cout<<root->dato<<' ';
		}
	}
	void insertar(nodo* &root,int ndato){
		if(root==nullptr){
			root = new nodo(ndato);
		}else if(ndato < root->dato){
			insertar(root->izq,ndato);
		}else if(ndato > root->dato){
			insertar(root->der,ndato);
		}
	}
	void eliminar(nodo* &root,)
	public:
		abb(){
			root = nullptr;
		}
		void insertar(int ndato){
			insertar(root,ndato);
		}
		void eliminar(int ndato){
			eliminar(root,ndato);
		}
		void ver_in(){
			ver_in(root);
		}
		void ver_pre(){
			ver_pre(root);
		}
		void ver_pos(){
			ver_pos(root);
		}
};
int main(){
	abb arbol;
	arbol.insertar(5);
	arbol.insertar(9);
	arbol.insertar(4);
	arbol.insertar(2);
	arbol.insertar(3);
	arbol.insertar(10);
	arbol.insertar(12);
	arbol.ver_in();
	cout<<endl;
	arbol.ver_pos();
	cout<<endl;
}