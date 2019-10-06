#include "abb.h"

Abb::Abb(){
	this->raiz.dado = int(NULL);
	this->raiz.ptr_esq = &this->ptrNULL;
	this->raiz.ptr_dir = &this->ptrNULL;
	this->raiz.pai = &this->ptrNULL;
};
Node Abb::getRaiz(){
      return this->raiz;
}
string Abb::inserir(Node* node){ //complexidade é O(log n) pois a cada nó ele ira perguntar se o valor é maior ou menor que o valor a ser inserido e irá descartar os outros elementos

	node->ptr_esq = &this->ptrNULL;
	node->ptr_dir = &this->ptrNULL;
	node->pai = &this->ptrNULL;
	Node *auxiliar = &this->raiz;
	if(this->raiz.dado == int(NULL)){
		this->raiz.dado = node->dado;
		this->raiz.nivel = 1;
		return "Elemento adicionado com sucesso!!!";
	}
	node->ptr_esq = &this->ptrNULL;
	node->ptr_dir = &this->ptrNULL;
	node->pai = &this->ptrNULL;
	while(true){
		if(node->dado < auxiliar->dado){
			if(auxiliar->ptr_esq != &this->ptrNULL){
				auxiliar = auxiliar->ptr_esq;
			}else{
				node->pai = auxiliar;
				auxiliar->ptr_esq = node;
				auxiliar->ptr_esq->nivel = auxiliar->nivel + 1;
				return "Elemento adicionado com sucesso!!!";
			}					
		}else if(node->dado > auxiliar->dado){
			if(auxiliar->ptr_dir != &this->ptrNULL){
				auxiliar = auxiliar->ptr_dir;
			}else{
				node->pai = auxiliar;
				auxiliar->ptr_dir = node;
				auxiliar->ptr_dir->nivel = auxiliar->nivel + 1;
				return "Elemento adicionado com sucesso!!!";
			}
		}else{
			return "Elemento já pertence a lista!!!";
		}

	}
};


string Abb::remover(Node node){//complexidade é O(log n) pois a cada nó ele ira perguntar se o valor é maior ou menor que o valor a ser removido e irá descartar os outros elementos
	cout << "Elemento a ser removido: " << node.dado << endl;
	Node * aux = &this->raiz;
	Node * maiorElementoEsq;
	int lado = 0;
	while(true){
		if(node.dado == aux->dado){
			if(aux->ptr_esq == &this->ptrNULL and aux->ptr_dir == &this->ptrNULL){ //Não tem filhos
 				if(lado == 1){
					aux->pai->ptr_esq = &this->ptrNULL;
				}else if(lado == 2){
					aux->pai->ptr_dir = &this->ptrNULL;
				}else{
					this->raiz.dado = this->ptrNULL.dado;
					this->raiz.ptr_esq = &this->ptrNULL;
					this->raiz.ptr_dir = &this->ptrNULL;
					this->raiz.pai = &this->ptrNULL;
				}
			}else if(aux->ptr_esq == &this->ptrNULL and aux->ptr_dir != &this->ptrNULL){ //Tem 1 filho no ponteiro da direita
				if(lado == 1){
					aux->pai->ptr_esq = aux->ptr_dir;
				}else if(lado == 2){
					aux->pai->ptr_dir = aux->ptr_dir;
				}else{
					this->raiz = *(aux->ptr_dir);
					this->raiz.pai = &this->ptrNULL;
				}
			}else if(aux->ptr_esq != &this->ptrNULL and aux->ptr_dir == &this->ptrNULL){ //Tem 1 filho no ponteiro da esquerda
				if(lado == 1){
					aux->pai->ptr_esq = aux->ptr_esq;
				}else if(lado == 2){
					aux->pai->ptr_dir = aux->ptr_esq;
				}else{
					this->raiz = *(aux->ptr_esq);
					this->raiz.pai = &this->ptrNULL;
				}
			}else{                                                                     //Tem 2 filhos
				maiorElementoEsq = this->maiorElementoEsq(aux);
				maiorElementoEsq->ptr_dir = aux->ptr_dir;
				maiorElementoEsq->ptr_esq = aux->ptr_esq;
				maiorElementoEsq->nivel = aux->nivel;
				if(aux->dado == this->raiz.dado){
					this->raiz = *(maiorElementoEsq);
					this->raiz.pai = &this->ptrNULL;
					return "Elemento removido com sucesso!!!";
				}
				maiorElementoEsq->pai = aux->pai;
				if(lado == 1){
					aux->pai->ptr_esq = maiorElementoEsq;
				}else if(lado == 2){
					aux->pai->ptr_dir = maiorElementoEsq;
				}
				return "Elemento removido com sucesso!!!";
			}
			this->subtrairNivel(aux);
			return "Elemento removido com sucesso!!!";
		}else if(node.dado < aux->dado){
			if(aux->ptr_esq != &this->ptrNULL){
				aux = aux->ptr_esq;
			}else{
				return "Elemento não encontrado!!!";
			}
			lado = 1;
		}else{
			if(aux->ptr_dir != &this->ptrNULL){
				aux = aux->ptr_dir;
			}else{
				return "Elemento não encontrado!!!";
			}
			lado = 2;
		}
	}
};


void Abb::subtrairNivel(Node * node){ //depende do nó passado, caso o nó seja a raiz ele percorre toda a árvore, por isso é O(n)
	node->nivel--;
	if(node->ptr_esq != &this->ptrNULL){
		subtrairNivel(node->ptr_esq);
	}
	if(node->ptr_dir != &this->ptrNULL){
		subtrairNivel(node->ptr_dir);
	}
};


Node* Abb::maiorElementoEsq(Node* node){
	Node *auxiliar = node->ptr_esq;
	Node *auxiliar2 = node;
	while(auxiliar->ptr_dir != &this->ptrNULL){// log(n), pecorrendo sempre o lado direito
			auxiliar2 = auxiliar;
			auxiliar = auxiliar->ptr_dir;
	}
	auxiliar2->ptr_dir = &this->ptrNULL;	
	if(auxiliar->ptr_esq != &this->ptrNULL){
		auxiliar2->ptr_dir = auxiliar->ptr_esq;
	}
	if(auxiliar == auxiliar2->ptr_esq){	
		auxiliar2->ptr_esq = &this->ptrNULL;
		subtrairNivel(auxiliar); //O(n)
		return auxiliar;
	}
	subtrairNivel(auxiliar);//O(n)
	return auxiliar;
};


bool Abb::buscar(Node node){ //complexidade é O(log n) pois a cada nó ele ira perguntar se o valor é maior ou menor que o buscado e irá descartar os outros elementos
	Node auxiliar = raiz;
	while(true){
		cout << auxiliar.dado << endl;
		if(auxiliar.dado == node.dado){
			return true;
		}else if(auxiliar.dado > node.dado){
			if(auxiliar.ptr_esq == &this->ptrNULL){
				return false;
			}
			auxiliar = *(auxiliar.ptr_esq);
		}else{
			if(auxiliar.ptr_dir == &this->ptrNULL){
				return false;
			}
			auxiliar = *(auxiliar.ptr_dir);
		}
	}
};

Abb::~Abb(){
};

int Abb::enesimoElemento (int n){
	string a = "";
	string s = " ";
	int f = 0;
	a = ordem(&raiz); //complexidade n
	int lista[sizeof(a)] = {0};
	for (int i = 0; i < a.size(); i++) // tamanho de a depende da quantidade de nós, logo é n
	{
		if (a[0] == ' ')
		{
			i = a.size();
		}
		if (a[i] != ' ')
		{
			s = s + (a)[i];
		}
		else{
			char p[sizeof(s)];  //somatório de um até n, que é o tamanho de p
			for (int j = 0; j < sizeof(p); j++) { 
			    p[j] = s[j];  
			}
			lista[f] = atoi(p);
			f = f + 1;
			s = " ";
		}
	}
	if (n > f)
	{
		cout << "Posição excedeu a quantidade de elementos";
	}
	return lista[n-1];	
}
int Abb::posicao (int dado){
	string a = "";
	string s = " ";
	int f = 0;
	int posicao = 0;
	a = ordem(&raiz); //complexidade n
	int lista[sizeof(a)];
	for (int i = 0; i < a.size(); i++)// tamanho de a depende da quantidade de nós, logo é n
	{
		if (a[0] == ' ')
		{
			i = a.size();
		}
		if (a[i] != ' ')
		{
			s = s + (a)[i];
		}
		else{
			char p[sizeof(s)];  //somatório de um até n, que é o tamanho de p
			for (int j = 0; j < sizeof(p); j++) { 
			    p[j] = s[j];  
			}
			lista[f] = atoi(p);
			f = f + 1;
			s = " ";
		}
	}
	for (int i = 0; i < f; i++) //complexidade n
	{
		if (lista[i] == dado)
		{
			posicao = i+1;
			break;
		}
	}
	return posicao;
}
int Abb::mediana(){
	string a = "";
	string s = " ";
	int f = 0;
	int posicao = 0;
	int mediana; 
	a = ordem(&raiz); //complexidade n
	int lista[sizeof(a)] = {0};
	for (int i = 0; i < a.size(); i++)// tamanho de a depende da quantidade de nós, logo é n
	{
		if (a[0] == ' ')
		{
			i = a.size();
		}
		if (a[i] != ' ')
		{
			s = s + (a)[i];
		}
		else{
			char p[sizeof(s)];    //somatório de um até n, que é o tamanho de p
			for (int j = 0; j < sizeof(p); j++) { 
			    p[j] = s[j];  
			}
			lista[f] = atoi(p);
			f = f + 1;
			s = " ";
		}
	}		
	for (int i = 0; i < sizeof(a); i++) //complexidade n
	{
		if (lista[i] == int(NULL))
		{
			posicao = i;
			break;
		}
	}
	if (posicao%2 == 0 )
	{
		mediana = posicao/2 - 1;
	}
	else{
		mediana = posicao/2;
	}

	return lista[mediana];
}

string Abb::ordem(Node *ptr){ //para todos os nós a função é chamada, logo é da ordem de n
        string percorrimento = "";

        if (ptr->dado == int(NULL)) {
            return "";
        }
        percorrimento += ordem(ptr->ptr_esq);
        percorrimento += to_string(ptr->dado) + " ";
        percorrimento += ordem(ptr->ptr_dir);

        return percorrimento;

}

bool Abb::ehCheia(Node no){ 
	int altura = calcularAltura(&no); //O(n)
    if(no.nivel < altura){//depende do nó passado, caso o nó seja a raiz ele percorre  toda a árvore no caso dela ser cheia, por isso é O(n)
        if((no.ptr_dir != nullptr) and (no.ptr_esq != nullptr)){
            bool b1 = ehCheia(*(no.ptr_dir));
            bool b2 = ehCheia(*(no.ptr_esq));
            if(b1 and b2){
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return true;
    }
}

bool Abb::ehCompleta(Node no){
	int altura = calcularAltura(&no); //O(n)
    if(no.nivel < altura){ //depende do nó passado, caso o nó seja a raiz ele percorre  toda a árvore no caso dela ser cheia, por isso é O(n)
        if((no.ptr_dir != nullptr) and (no.ptr_esq != nullptr)){
            bool b1 = ehCheia(*(no.ptr_dir));
            bool b2 = ehCheia(*(no.ptr_esq));
            if(b1 and b2){
                return true;
            } else {
                return false;
            }
        } else if((no.nivel == altura-1) and (no.ptr_dir == nullptr) and (no.ptr_esq == nullptr)){
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

int Abb::calcularAltura(Node * node){ //depende do nó passado, caso o nó seja a raiz ele percorre toda a árvore, por isso é O(n) 
	int x = 0, y = 0;
	if(node->ptr_esq == &this->ptrNULL and node->ptr_esq == &this->ptrNULL){
		return 2;
	}
	if(node->ptr_esq != &this->ptrNULL){
		x = calcularAltura(node->ptr_esq) + 1;	
	}
	if(node->ptr_dir != &this->ptrNULL){
		y = calcularAltura(node->ptr_dir) + 1;
	}
	if(node->ptr_esq != &this->ptrNULL and node->ptr_dir != &this->ptrNULL){
		x = calcularAltura(node->ptr_esq) + 1;
		y = calcularAltura(node->ptr_dir) + 1;
	}
	if (x > y){
		return x;
	}else{
		return y;
	}
}

string Abb::toString(){ //ele percorre toda a árvore por isso é O(n) 
	list<Node> lista;
	lista.push_back(this->raiz);
	string s = "";
	for(Node n: lista){
		s = s + to_string(n.dado)+ " ";
		if(n.ptr_esq != &this->ptrNULL){
			lista.push_back(*(n.ptr_esq));
		}
		if(n.ptr_dir != &this->ptrNULL){
			lista.push_back(*(n.ptr_dir));
		}
	}
	return s;
};

void Abb::comandos(string arquivo){
	ifstream comands(arquivo);
	string aux;
	while(comands >> aux){
		if(aux.compare("ENESIMO") == 0){
			comands >> aux;
			std::cout << "Elemento da posição " << aux << ": " << enesimoElemento(std::stoi(aux)) << "\n";
		} else if(aux.compare("POSICAO") == 0){
			comands >> aux;
			int x = posicao(std::stoi(aux));
			std::cout << "Posição do elemento " << aux <<": ";
			if(x != 0){
				cout << x << "\n";
			}
			else{
				cout << "O elemento não se encontra na árvore\n";
			}
		} else if(aux.compare("MEDIANA") == 0){
			std::cout << "Mediana: " << mediana() << "\n";
		} else if(aux.compare("CHEIA") == 0){
			std::cout << "Cheia: " << ehCheia(getRaiz()) << "\n";
		} else if(aux.compare("COMPLETA") == 0){
			std::cout << "Completa: " << ehCompleta(getRaiz()) << "\n";
		} else if(aux.compare("IMPRIMA") == 0){
			std::cout << toString() << "\n";
		} else if(aux.compare("INSIRA") == 0){
			comands >> aux;
			Node* node = new Node;
			node->dado = std::stoi(aux);
			std::cout << inserir(node) << "\n";
		} else if(aux.compare("REMOVA") == 0){
			comands >> aux;
			Node* node = new Node;
			node->dado = std::stoi(aux);
			std::cout << remover(*node) << "\n";
		}
	}
};


