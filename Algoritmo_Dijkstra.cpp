#include <iostream>
#include <string>
using namespace std;

template <class T> 
struct Nodo{
    T Santuario;
    T Peso;
    T Tiempo;
    T Estabilidad;   
    Nodo *Siguiente;
    Nodo *Anterior;
    Nodo *Temp;
};
template <class T> 
class DobleLinkedList
{
    private:
        int Size;
        Nodo<T> *Head;
        Nodo<T> *Tail;
    
    public:
        DobleLinkedList(): Size (0), Head (nullptr), Tail (nullptr){}

        void Insert(T Dato) {
            Nodo<T> *NewNodo = new Nodo<T>();
            NewNodo->Santuario = Dato; // Asumo que 'Santuario' es tu variable de dato

            if (Head == nullptr) { // Caso 1: Lista vacía
                Head = NewNodo;
                Tail = NewNodo;
                NewNodo->Siguiente = nullptr;
                NewNodo->Anterior = nullptr;
            } 
            else { // Caso 2: Insertar después de Head
                NewNodo->Siguiente = Head->Siguiente;
                NewNodo->Anterior = Head;

                if (Head->Siguiente != nullptr) {
                    // Solo si hay un nodo después de Head, actualizamos su puntero Anterior
                    Head->Siguiente->Anterior = NewNodo;
                } else {
                    // Si no había nadie después de Head, el nuevo nodo es ahora el Tail
                    Tail = NewNodo;
                }
                
                Head->Siguiente = NewNodo;
            }
            Size++;
        }

        void Eliminar (T Dato){
            if (Head == nullptr) return;

            Nodo<T> *temp = Head;

            
            if (Dato == temp->info){
                Nodo<T> *Eliminar = temp->Siguiente;

                temp -> Siguiente = Eliminar -> Siguiente;
                Eliminar->Siguiente->Anterior = temp;

                delete Eliminar;
                Size--;
                return;

            }


            while (temp->Siguiente != nullptr && Dato != temp->Siguiente->info) { // 1 2 3 4 5 6 5

                temp = temp->Siguiente;
            }

            if (temp->Siguiente == nullptr){
                return;
            }

            Nodo<T> *Eliminar = temp->Siguiente;

            temp -> Siguiente = Eliminar -> Siguiente;
            Eliminar->Siguiente->Anterior = temp;

            delete Eliminar;
            Size--;


        }

        int GetHead (){
            if (Head == nullptr) return 0; 
            return Head->Santuario;

        }

       void ShowAll(){
            Nodo<T> *temp = Head;
            while (temp != nullptr){
                cout << temp->Santuario;
                temp = temp->Siguiente;
            }
            cout << endl;
        }



};


int main (){


    DobleLinkedList<int> L1;
    int Santuario, PesoMagico;
    int Contador = 1;
    int CriterioDeParada;

    cout << "Ingrese Santuario ";
    cin >> Santuario;
    L1.Insert(Santuario);

    while (true){

        if (Contador == 1){
            cout << "primer if ";
            CriterioDeParada = Santuario;
        }

        cout << "Ingrese PesoMagico ";
        cin >> PesoMagico;


        Contador++;
        cout << "Ingrese Santuario ";
        cin >> Santuario;
        L1.Insert(Santuario);

        

        cout<< " EL HEAD ES:" << L1.GetHead() << endl;
        if (CriterioDeParada == Santuario){
            cout << "segundo if ";
            break;
        }
        






    }
    

    cout << "sali del while";


}
