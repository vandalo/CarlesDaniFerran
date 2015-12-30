//
//  mainGeneral.cpp
//  
//
//  Created by Ferran coma rosell on 29/12/15.
//
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include "hash/Hash.hpp"
#include "cercabinaria/CercaBinaria.hpp"
#include "bloom/bloom_filter.hpp"

using namespace std;


inline void print_capcalera(){
    cout << " ;---------------------------------------;" <<endl;
    cout << " ;                                       ;" <<endl;
    cout << " ;           MAIN - ALGORISMIA           ;" <<endl;
    cout << " ;            Comprovacio de             ;" <<endl;
    cout << " ;           temps de procesat           ;" <<endl;
    cout << " ;                                       ;" <<endl;
    cout << " ;---------------------------------------;" <<endl;
}


int main(){
    print_capcalera();
    cout << endl;
    clock_t start;
    double duration;
	vector<unsigned int> keys_diccionario;
	vector<unsigned int> valores_texto;
    
    //arxiu d'entrada
    ifstream arxiu("jocdeprobes/jp1.txt");
    int temanyDadesArxiu1;
    arxiu >> temanyDadesArxiu1;
	unsigned int buffer;
	while (arxiu >>buffer) keys_diccionario.push_back(buffer);
	
	//////////////////////////////////
	//////////////TESTS//////////////
	/////////////////////////////////
    
    cout << endl;
    cout << "Test amb " << temanyDadesArxiu1 << " dades en el diccionari" << endl;
    cout << endl;
    
    cout << "Insercio de hash..." << endl;
    //omplir taula de hash
    taula_hash hash(temanyDadesArxiu1);
	
	////ESTO ES SOLO PARA K TE FUNCIONE HASTA K CAMBIES A K LEA DEL VECTOR
	ifstream arxiu2("jocdeprobes/jp1.txt");
	arxiu2 >> buffer;
	///////////////////
	
    start = clock();
    while(!arxiu.eof()){
        int aux;
        arxiu2 >> aux;
        hash.insertKey(aux);
    }
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    cout << "Insercio de hash completada" << endl;
    cout << "Temps d'insercio: " << duration <<endl;
    cout << endl;
    
	
	
	
    //omplir filtre de bloom
	//////////////
	cout << "Insercio de la taula de bits del filtre de bloom..." << endl;
	const double expected_fpp = 1.0 / keys_diccionario.size();
	unsigned int random_seed = 0;
	bloom_parameters parameters(keys_diccionario.size(), expected_fpp, ++random_seed); //iniciar parametros
	bloom_filter filter(parameters); //iniciar filtro con parametros optimos
	
    start = clock();
	
	filter.insert(keys_diccionario.begin(),keys_diccionario.end()); //insertar lista de palabras
    
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "Insercio completada" << endl;
    cout << "Temps d'insercio: " << duration <<endl;
    cout << endl;
	
    
	/////////////////////////////////////
    //omplim vetor cerca binaria
    cout << "Insercio del vector de cerca binaria..." << endl;
    start = clock();
    
    CercaBinaria cb("jocdeprobes/jp1.txt");
    

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "Insercio al vector de cerca binaria completada" << endl;
    cout << "Temps d'insercio: " << duration <<endl;
    cout << endl;
    
    
    arxiu.close();
	
	
	
	
	
	
	
	    cout << endl << endl <<
			" ;---------------------------------------;" <<endl;
    cout << " ;          Prueba de contains           ;" <<endl;
	cout << " ;---------------------------------------;" <<endl << endl;
    
    //arxiu d'entrada2
    ifstream arxiuTexto("jocdeprobes/jp2.txt");
	while (arxiuTexto >>buffer) valores_texto.push_back(buffer);
	
    int trobats = 0, fallats = 0;
    
	
	
    //comprvar elements hash
    cout << "Comprovacio de hash..." << endl;
    start = clock();
    while(!arxiuTexto.eof()){
        int aux;
        arxiuTexto >> aux;
        if(hash.getKey(aux))trobats++;
        else fallats ++;
    }
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    cout << "Comprovacio de hash completada" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Temps d'acces: " << duration <<endl;
    cout << "Encerts: " << trobats << endl;
    cout << "Fallats: " << fallats << endl;
    cout << "Comprovacions relitzades totals: " << hash.getComprovacions() << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl << endl;
    
    //reset arxiu entrada2
    arxiuTexto.close();
    ifstream arxiu3("jocdeprobes/jp2.txt");
	
	
	
	
	//BLOOOOOM
	trobats = 0, fallats = 0;
    
    //comprvar elements cerca binaria
    cout << "Comprovacio del filtre de bloom..." << endl;
    start = clock();
	//COMPROBAMOS SI ALGUNA PALABRA DE LAS INEXISTENTES, 
	//LA DETECTA COMO EXISTENTE, PARA CONTARLA COMO FALSO POSITIVO
	trobats = filter.contains(valores_texto.begin(), valores_texto.end());
	fallats = valores_texto.size() - trobats;
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    cout << "Comprovacio de bloom completada" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Temps d'acces: " << duration <<endl;
    cout << "Encerts: " << trobats << endl;
    cout << "Fallats: " << fallats << endl;
    cout << "Comprovacions relitzades totals: " << cb.getComprovacions() << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
	
	
	
	
	
	
	
	
	
	
    trobats = 0, fallats = 0;
    
    //comprvar elements cerca binaria
    cout << "Comprovacio de cerca binaria..." << endl;
    start = clock();
    while(!arxiu3.eof()){
        int aux;
        arxiu3 >> aux;
        if(cb.existeix(aux))trobats++;
        else fallats ++;
    }
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    cout << "Comprovacio de cerca binaria completada" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Temps d'acces: " << duration <<endl;
    cout << "Encerts: " << trobats << endl;
    cout << "Fallats: " << fallats << endl;
    cout << "Comprovacions relitzades totals: " << cb.getComprovacions() << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
    
}


