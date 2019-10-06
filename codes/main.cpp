#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include "abb.h"

int main(int argc, char *argv[]){

    // Verificando se tem as 3 entradas necessarias (executavel[0], arquivo_insercao[1],
    // arquivo_comando[2]).
    if(argc != 3){
        std::cout << "ERROR! Falta de informações..." << std::endl;
        return 0;
    }

    // Verificando se os arquivos existem    --------
    std::ifstream values(argv[1]);          //      |
    if(values.is_open()){                   //      |
        std::ifstream comands(argv[2]);     //      |
        if(comands.is_open()){              //      |

        // * Trabalhando com o arquivo de insercao * //
        Abb * abb = new Abb();
        int number; // variavel auxiliar para insercao
        // @ Retirar @  ----------------
        std::vector<int> toAdd;     // |
        //                             |

        // inserindo os numeros na arvore
        list <int> numeros;
	while(values >> number){
		numeros.push_back(number);
        }
	int aux = numeros.size();
	Node no[aux-1];
	list <int>::iterator it = numeros.begin();
	for(int i=0; i<aux; i++){
		no[i].dado = *it;
		++it;
		abb->inserir(&no[i]);
       	}
        // * Trabalhando com o arquivo de comandos * //
        abb->comandos(argv[2]);

        } else { // Caso não ache o arquivo de comandos
            std::cout << "Arquivo de comandos não encontrado!" << std::endl;
        }
    } else { // Caso não ache o arquivo de insercao
        std::cout << "Arquivo de inserção não encontrado!" << std::endl;
    }
    
}
