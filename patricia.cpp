#include <stdlib.h>
#include <string.h>
#include <iostream>
typedef char* nPatriciaTrieKey;
template <class T> class nPatriciaTrie;

//----------------------------------------------------------------------------
template <class T>
class nPatriciaTrieNode {
	private:
		friend class nPatriciaTrie<T>;
		int bit_index;
		nPatriciaTrieKey        key;
		T                       data;
		nPatriciaTrieNode<T>*   left;
		nPatriciaTrieNode<T>*   right;

	public:
		nPatriciaTrieNode();
		nPatriciaTrieNode(nPatriciaTrieKey, T, int, nPatriciaTrieNode<T>*, nPatriciaTrieNode<T>*);
		virtual ~nPatriciaTrieNode();
		void					Initialize(nPatriciaTrieKey, T, int, nPatriciaTrieNode<T>*, nPatriciaTrieNode<T>*);
		T                       GetData();
		bool                    SetData(T);
		nPatriciaTrieKey        GetKey();
		nPatriciaTrieNode<T>*   GetLeft();
		nPatriciaTrieNode<T>*   GetRight();

};

//----------------------------------------------------------------------------
template <class T>
class nPatriciaTrie {
	private:
		void recursive_remove(nPatriciaTrieNode<T>*);
		int  bit_get(nPatriciaTrieKey, int);
		int  bit_first_different(nPatriciaTrieKey, nPatriciaTrieKey);
		bool key_compare(nPatriciaTrieKey, nPatriciaTrieKey);
		void key_copy(nPatriciaTrieNode<T>*, nPatriciaTrieNode<T>*);
		nPatriciaTrieNode<T>* head;
	public:
		nPatriciaTrie();
		virtual ~nPatriciaTrie();
		virtual nPatriciaTrieNode<T>*   Insert(nPatriciaTrieKey, T);
		virtual T                       Lookup(nPatriciaTrieKey);
		virtual nPatriciaTrieNode<T>*   LookupNode(nPatriciaTrieKey);
		virtual bool                    Delete(nPatriciaTrieKey);
};

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieNode<T>::nPatriciaTrieNode() {
	Initialize(NULL, NULL, -1, this, this);
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieNode<T>::nPatriciaTrieNode(nPatriciaTrieKey k,T d,int bi,nPatriciaTrieNode<T>* l,nPatriciaTrieNode<T>* r) {
    Initialize(k, d, bi, l, r);
}

//----------------------------------------------------------------------------
template <class T>
void nPatriciaTrieNode<T>::Initialize(nPatriciaTrieKey k,T d,int bi,nPatriciaTrieNode<T>* l,nPatriciaTrieNode<T>* r) {
	if (k)
		key = (nPatriciaTrieKey)strdup(k);
	else
	    key = k;
	data      = d;
	left      = l;
	right     = r;
	bit_index = bi;
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieNode<T>::~nPatriciaTrieNode() {
	if (key) {
		free(key);
		key = NULL;
	}
}

//----------------------------------------------------------------------------
template <class T>
T nPatriciaTrieNode<T>::GetData() {
	return data;
}

//----------------------------------------------------------------------------
template <class T>
bool nPatriciaTrieNode<T>::SetData(T d) {
	memcpy(&data, &d, sizeof(T));
	return true;
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieKey nPatriciaTrieNode<T>::GetKey() {
	return key;
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieNode<T>* nPatriciaTrieNode<T>::GetLeft() {
	return left;
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieNode<T>* nPatriciaTrieNode<T>::GetRight() {
	return right;
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrie<T>::nPatriciaTrie() {
	head = new nPatriciaTrieNode<T>();
    #define ZEROTAB_SIZE 256
	head->key = (char*)calloc(ZEROTAB_SIZE, 1);
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrie<T>::~nPatriciaTrie() {
	recursive_remove(head);
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieNode<T>* nPatriciaTrie<T>::Insert(nPatriciaTrieKey k, T d) {
	nPatriciaTrieNode<T> *p, *t, *x;
	p = head;
	t = (nPatriciaTrieNode<T>*)(p->right);
	while (p->bit_index < t->bit_index) {
		p = t;
		t = (nPatriciaTrieNode<T>*)(bit_get(k, t->bit_index) ? t->right : t->left);
	}
	if (key_compare(k, t->key))
		return NULL;
		
	int i = bit_first_different(k, t->key);
	p  = head;
	x  = (nPatriciaTrieNode<T>*)(p->right);
	while ( ( p->bit_index < x->bit_index ) &&
			( x->bit_index < i) ) {
		p = x;
		x = (nPatriciaTrieNode<T>*)(bit_get(k, x->bit_index) ? x->right : x->left);
	}

	t = new nPatriciaTrieNode<T>();
	t->Initialize(k, d, i, (bit_get(k, i) ? x : t), (bit_get(k, i) ? t : x));

	if (bit_get(k, p->bit_index))
		p->right = t;
	else
		p->left = t;

	return t;
}

//----------------------------------------------------------------------------
template <class T>
T nPatriciaTrie<T>::Lookup(nPatriciaTrieKey k) {

	nPatriciaTrieNode<T>* node = LookupNode(k);

	if (!node)
		return NULL;
		
	return node->data;
}

//----------------------------------------------------------------------------
template <class T>
nPatriciaTrieNode<T>* nPatriciaTrie<T>::LookupNode(nPatriciaTrieKey k) {

	nPatriciaTrieNode<T>* p;
	nPatriciaTrieNode<T>* x;

    p = head;
	x = (nPatriciaTrieNode<T>*)(head->right);

	while (p->bit_index < x->bit_index) {
		p = x;
		x = (nPatriciaTrieNode<T>*)(bit_get(k, x->bit_index) ? x->right : x->left);
	}

	if (!key_compare(k, x->key))
		return NULL;

	return x;
}

//----------------------------------------------------------------------------
template <class T>
bool nPatriciaTrie<T>::Delete(nPatriciaTrieKey k) {

	nPatriciaTrieNode<T> *p, *t, *x, *pp, *lp;
	int bp, bl, br;
	char* key = NULL;

	p  = head;
	t  = (nPatriciaTrieNode<T>*)(p->right);

	while (p->bit_index < t->bit_index) {
		pp = p;
		p  = t;
		t  = (nPatriciaTrieNode<T>*)(bit_get(k, t->bit_index) ? t->right : t->left);
	}

	if (!key_compare(k, t->key))
		return false;

	if (t != p)
		key_copy(p, t);

	bp = p->bit_index;
	bl = ((nPatriciaTrieNode<T>*)(p->left))->bit_index;
	br = ((nPatriciaTrieNode<T>*)(p->right))->bit_index;

	if ((bl > bp) || (br > bp)) {
		if (p != t) {
			key = strdup(p->key);
			lp = p;
			x  = (nPatriciaTrieNode<T>*)(bit_get(key, p->bit_index) ? p->right : p->left);
			while (lp->bit_index < x->bit_index) {
				lp = x;
				x  = (nPatriciaTrieNode<T>*)(bit_get(key, x->bit_index) ? x->right : x->left);
			}
            if (!key_compare(key, x->key)) {
                free(key);
				return false;
            }
			if (bit_get(key, lp->bit_index))
				lp->right = t;
			else
				lp->left = t;
		}

		if (pp != p) {
			nPatriciaTrieNode<T>* ch = (nPatriciaTrieNode<T>*)(bit_get(k, p->bit_index) ? p->left : p->right);
			if (bit_get(k, pp->bit_index))
				pp->right = ch;
			else
				pp->left = ch;
		}

        free(key);
        key = NULL;
	} else {
		if (pp != p) {
			nPatriciaTrieNode<T>* blx = (nPatriciaTrieNode<T>*)(p->left);
			nPatriciaTrieNode<T>* brx = (nPatriciaTrieNode<T>*)(p->right);
			if (bit_get(k, pp->bit_index))
				pp->right = (((blx == brx) && (blx == p)) ? pp : ((blx==p)?brx:blx));
			else
				pp->left  = (((blx == brx) && (blx == p)) ? pp : ((blx==p)?brx:blx));
		}
	}
	delete p;
	return true;
}

//----------------------------------------------------------------------------
template <class T>
void nPatriciaTrie<T>::recursive_remove(nPatriciaTrieNode<T>* root) {

	nPatriciaTrieNode<T>* l = (nPatriciaTrieNode<T>*)root->left;
	nPatriciaTrieNode<T>* r = (nPatriciaTrieNode<T>*)root->right;
	if ( (l->bit_index >= root->bit_index) && (l != root) && (l != head) )
		recursive_remove(l);
	if ( (r->bit_index >= root->bit_index) && (r != root) && (r != head) )
		recursive_remove(r);
	delete root;
}

//----------------------------------------------------------------------------
template <class T>
int nPatriciaTrie<T>::bit_get(nPatriciaTrieKey bit_stream, int n) {
  if (n < 0) return 2;
  int k = (n & 0x7);
  return ( (*(bit_stream + (n >> 3))) >> k) & 0x1;
}

//----------------------------------------------------------------------------
template <class T>
bool nPatriciaTrie<T>::key_compare(nPatriciaTrieKey k1, nPatriciaTrieKey k2) {
    if (!k1 || !k2)
        return false;
	return (strcmp((char*)k1, (char*)k2) == 0);
}

//----------------------------------------------------------------------------
template <class T>
int nPatriciaTrie<T>::bit_first_different(nPatriciaTrieKey k1, nPatriciaTrieKey k2) {
    if (!k1 || !k2)
        return 0;
	int n = 0;
	int d = 0;
	while (	(k1[n] == k2[n]) && (k1[n] != 0) && (k2[n] != 0) )
		n++;
	while (bit_get(&k1[n], d) == bit_get(&k2[n], d))
		d++;
	return ((n << 3) + d);
}

//----------------------------------------------------------------------------
template <class T>
void nPatriciaTrie<T>::key_copy(nPatriciaTrieNode<T>* src, nPatriciaTrieNode<T>* dest) {

	if (src == dest)
		return;

	if (strlen(dest->key) < strlen(src->key))
		dest->key = (nPatriciaTrieKey)realloc(dest->key, 1 + strlen(src->key));
	strcpy(dest->key, src->key);
	dest->data = src->data;
}
int main(){
    nPatriciaTrie<int>* p = new nPatriciaTrie<int>();
    printf("Inserting... %s\n", p->Insert("foobar1", 1) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar2", 2) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar3", 3) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar4", 4) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar5", 5) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("__2867", 23) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("_23437256", 234) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("c:\\work\\development", -20) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("c:\\work\\release", -22) ? "OK" : "FAILED!");

    printf("foobar1 = %d\n", p->Lookup("foobar1"));
	printf("foobar2 = %d\n", p->Lookup("foobar2"));
	printf("foobar3 = %d\n", p->Lookup("foobar3"));
	printf("foobar4 = %d\n", p->Lookup("foobar4"));
	printf("foobar5 = %d\n", p->Lookup("foobar5"));
	printf("__2867 = %d\n", p->Lookup("__2867"));
	printf("_23437256 = %d\n", p->Lookup("_23437256"));
	printf("c:\\work\\development = %d\n", p->Lookup("c:\\work\\development"));
	printf("c:\\work\\release = %d\n", p->Lookup("c:\\work\\release"));

	printf("Deleting 'foobar4'... %s\n", p->Delete("foobar4") ? "OK" : "Uh-oh!");
	printf("Deleting 'foobar5'... %s\n", p->Delete("foobar5") ? "OK" : "Uh-oh!");

    printf("Looking up 'foobar4'... %s\n", p->LookupNode("foobar4") ? "Still there!" : "Not there (OK).");
    printf("Looking up 'foobar5'... %s\n", p->LookupNode("foobar5") ? "Still there!" : "Not there (OK).");
    
	delete p;

	return 0;
}
