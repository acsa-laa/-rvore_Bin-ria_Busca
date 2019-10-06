#ifndef ABB_H
#define ABB_H

#include <iostream>
#include <list>
#include <fstream>

struct Node{
	int dado;
	int nivel;
	Node* ptr_esq;
	Node* ptr_dir;
	Node* pai;

};

using namespace std;
class Abb{
	private:
	Node raiz;
	Node ptrNULL;

	public:
	Abb();
	string inserir(Node* node);
	string ordem(Node* ptr);
	int enesimoElemento (int n);
	int posicao (int dado);
	int mediana();
	bool buscar(Node node);
	Node* maiorElementoEsq(Node* node);
	string remover(Node node);
	~Abb();
	void comandos(string arquivo);
	string toString();
	void subtrairNivel(Node * node);
	bool ehCompleta(Node no);
	bool ehCheia(Node no);
	int calcularAltura(Node * node);
	Node getRaiz();

};

#endif
