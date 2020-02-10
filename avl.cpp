#include <iostream>
using namespace std;
struct nodo{
    int dato;
    int altura;
    nodo *izq, *der;
    nodo(){
        izq = der = nullptr;
    }
    nodo(int x){
        dato = x;
        izq = der = nullptr;
        altura = 1;
    }
};
// Función para comparar dos números y devolver al mayor
int mayor(int x, int y){
    return x>y?x:y;
}
//------------------------------------------------------------------------------

// Función para obtener la altura de un nodo , si es hoja = 0.
int get_altura(nodo* x){
    return (x == nullptr)? 0 : x->altura;
}
//------------------------------------------------------------------------------

// Función para obtener el balanceo de alturas en un nodo
int get_balance(nodo* x){
    return (x == nullptr)? 0 : get_altura(x->izq) - get_altura(x->der);
}
//------------------------------------------------------------------------------
class avl{
    // Puntero a la raiz del árbol
    nodo* root;
    //--------------------------------------------------------------------------
    
    // Recorrido inorden del arbol
    void ver_in(nodo* root){
        if(root){
            ver_in(root->izq);
            cout<<root->dato<<' ';
            ver_in(root->der);
        }
    }
    //--------------------------------------------------------------------------
    
    // Rotación simple del lado derecho 
    nodo* rotarD(nodo* x){
        nodo* y = x->der;
        nodo* z = y->izq;
        y->izq = x;
        x->der = z;
        // Actualización de altura dependiendo de los hijos
        x->altura = mayor( get_altura(x->izq) , get_altura(x->der) + 1);
        y->altura = mayor( get_altura(y->izq) , get_altura(y->der) + 1);
        return y;
    }
    //--------------------------------------------------------------------------
    
    // Rotación simple del lado izquierdo
    nodo* rotarI(nodo* x){
        nodo* y = x->izq;
        nodo* z = y->der;
        y->der = x;
        x->izq = z;
        // Actualización de altura dependiendo de los hijos
        x->altura = mayor( get_altura(x->izq) , get_altura(x->der) + 1);
        y->altura = mayor( get_altura(y->izq) , get_altura(y->der) + 1);
        return y;
    }
    //--------------------------------------------------------------------------
    
    // Rotación doble del lado derecho
    nodo* rotarDD(nodo* x){
        x->der = rotarI(x->der);
        return rotarD(x);
    }
    //--------------------------------------------------------------------------
    
    // Rotación doble del lado izquierdo
    nodo* rotarDI(nodo *x){
        x->izq = rotarD(x->izq);
        return rotarI(x);
    }
    //--------------------------------------------------------------------------
    
    // Inserción en el árbol
    nodo* insertar(nodo* &root, int x){
        cout<<"Entra a insertar\n";
        if(root == nullptr)
            return new nodo(x);
        cout<<"Llego\n";
        cout<<root->dato<<endl;
        if(x<root->dato){
            cout<<"Va al menor\n";
            root->izq = insertar(root->izq,x);
        }else if(x>root->dato){
            cout<<"Va al mayor\n";
            root->der = insertar(root->der,x);
        }else
            return root; //Caso de insertar un elemento ya contenido
        // Despues de actualizar los punteros a los hijos se hace lo mismo con
        // el padre 
        root->altura = 1+ mayor( get_altura(root->izq) , get_altura(root->der));
        int factor = get_balance(root);
        // Caso Sobrecargado total por derecha
        if(factor < -1 && x > root->der->dato){ return rotarD(root); }
        // Caso Sobrecargado total por izquierda
        if(factor > 1 && x < root->izq->dato){ return rotarI(root); }
        // Caso Zig Zag derecho
        if(factor < -1 && x < root->der->dato){ return rotarDD(root); }
        // Caso Zig Zag izquierdo
        if(factor > 1 && x > root->izq->dato){ return rotarDI(root); }
    }
    //--------------------------------------------------------------------------
    public:
        avl(){ root=nullptr; }// Constructor del arbol avl
        void insertar(int x){root = insertar(root,x);cout<<"Insertó\n";} 
        void ver_in(){ver_in(root);cout<<'\n';}
};
int main(){
    avl arbol;
    arbol.insertar(3);
    arbol.ver_in();
    arbol.insertar(5);
    arbol.ver_in();
    arbol.insertar(7);
    arbol.ver_in();
}
