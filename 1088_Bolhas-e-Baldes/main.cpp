#include <iostream>
#include <list>

using namespace std;

int main(){
    
    int n, e, swaps;
    list<int> lista;

    cin >> n;
    while (n){
        //Leitura da entrada
        for (int i = 0; i<n; i++){
            cin >> e;
            lista.push_back(e);
        }

        swaps = 0;

        //MergeSort modificado (Bottom-up)
        int size = 1;
        while(size < n){
            list<int>::iterator it1, it2, end;
            it1 = lista.begin();
            end = it2 = it1;
            //Percorrendo lista juntando sub-listas de tamanho "size"
            while(end != lista.end()){
                int i = 0;
                //Separando sub-lista 1
                while(i < size && it2 != lista.end()){
                    it2++;
                    i++;
                }
                end = it2;
                //Se existem duas sub-listas
                if (it2 != lista.end()){
                    i = 0;
                    //Separando sub-lista 2
                    while(i < size && end != lista.end()){
                        end++;
                        i++;
                    }
                    //Merge
                    i = 0;
                    while(it1 != it2 && it2 != end){
                        if( (*it1) <= (*it2) ){
                            it1++;
                            i++;
                        }else{
                            lista.insert(it1, (*it2));
                            it2 = lista.erase(it2);
                            //calculando swaps
                            swaps += size - i;
                        }
                    }
                    it1=it2=end;
                }
            }
            size *= 2;
        }

        cout << ((swaps%2)==0?"Carlos":"Marcelo") << endl;
        lista.clear();
        cin >> n;
    }

    return 0;
}