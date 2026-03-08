#include <iostream>
#include <sstream>

using namespace std;

const int INF_MANUAL = 2147483647;

struct Arista {
    int Destino;
    int Time;
    int Estabilidad;
    Arista* Next;
    Arista(int d, int t, int m, Arista* sig) : Destino(d), Time(t), Estabilidad(m), Next(sig) {}
};

struct NodoSantuario {
    int id;
    int distanciaMin;
    NodoSantuario* padre;
    bool visitado;
    Arista* adyacencia;
    NodoSantuario* Next;

    NodoSantuario(int _id) : id(_id), distanciaMin(INF_MANUAL), padre(nullptr), visitado(false), adyacencia(nullptr), Next(nullptr) {}
};

struct Entrega {
    int santuario;
    int peso;
    Entrega* Next;
    Entrega(int s, int k) : santuario(s), peso(k), Next(nullptr) {}
};

class EnviosSantuarios {
    private:
        NodoSantuario* Head;
        Entrega* listaEntregas;
        Entrega* ultimaEntrega;
        int tiempoTotal;

    public:
        EnviosSantuarios() : Head(nullptr), listaEntregas(nullptr), ultimaEntrega(nullptr), tiempoTotal(0) {}

        void AgregarSantuario(int id) {
            if (FindNode(id)) return;
            NodoSantuario* nuevo = new NodoSantuario(id);
            nuevo->Next = Head;
            Head = nuevo;
        }

        NodoSantuario* FindNode(int id) {
            NodoSantuario* temp = Head;
            while (temp) {
                if (temp->id == id) return temp;
                temp = temp->Next;
            }
            return nullptr;
        }

        void AgregarEntrega(int s, int k) {
            Entrega* nueva = new Entrega(s, k);
            if (!listaEntregas) {
                listaEntregas = ultimaEntrega = nueva;
            } else {
                ultimaEntrega->Next = nueva;
                ultimaEntrega = nueva;
            }
        }

        void agregarSendero(int a, int b, int t, int m) {
            AgregarSantuario(a);
            AgregarSantuario(b);
            NodoSantuario* NodoA = FindNode(a);
            NodoSantuario* NodoB = FindNode(b);
            NodoA->adyacencia = new Arista(b, t, m, NodoA->adyacencia);
            NodoB->adyacencia = new Arista(a, t, m, NodoB->adyacencia);
        }

        void reiniciarDijkstra() {
            NodoSantuario* temp = Head;
            while (temp) {
                temp->distanciaMin = INF_MANUAL;
                temp->visitado = false;
                temp->padre = nullptr;
                temp = temp->Next;
            }
        }

        bool ejecutarDijkstra(int origen, int destino, int pesoCarga) {
            reiniciarDijkstra();
            NodoSantuario* inicio = FindNode(origen);
            if (!inicio) return false;
            
            inicio->distanciaMin = 0;

            while (true) {
                NodoSantuario* NodoActual = nullptr;
                NodoSantuario* NodoTemporal = Head;

                //nodo no buscado y con minima actual
                while (NodoTemporal) {
                    
                    if (!NodoTemporal->visitado && NodoTemporal->distanciaMin != INF_MANUAL) {
                        if (!NodoActual || NodoTemporal->distanciaMin < NodoActual->distanciaMin) {
                            NodoActual = NodoTemporal;
                        }
                    }
                    NodoTemporal = NodoTemporal->Next;
                }

                //Break Si no hay mas Nodos
                if (!NodoActual || NodoActual->id == destino) break;

                NodoActual->visitado = true;

                //ExploradorCaminos se encargar de buscar los posibles caminos y cual es el mejor
                Arista* ExploradorCaminos = NodoActual->adyacencia;
                while (ExploradorCaminos) {
                    // Si cumple con la estabilidad, sigue
                    if (ExploradorCaminos->Estabilidad >= pesoCarga) {
                        NodoSantuario* NodoVecino = FindNode(ExploradorCaminos->Destino);
                        //si no esta visitado busca
                        if (NodoVecino && !NodoVecino->visitado) {
                            int nuevaDistancia = NodoActual->distanciaMin + ExploradorCaminos->Time;
                            if (nuevaDistancia < NodoVecino->distanciaMin) {
                                NodoVecino->distanciaMin = nuevaDistancia;
                                NodoVecino->padre = NodoActual;
                            }
                        }
                    }
                    ExploradorCaminos = ExploradorCaminos->Next;
                }
            }

            NodoSantuario* NodoDestino = FindNode(destino);
            // Retorna true solo si el destino fue alcanzado 
            return (NodoDestino && NodoDestino->distanciaMin != INF_MANUAL);
        }

        void imprimirRutaRecursiva(NodoSantuario* n, bool esPrimerNodoAbsoluto) {
            if (!n) return;
            imprimirRutaRecursiva(n->padre, esPrimerNodoAbsoluto);
            // Si es el primer tramo del viaje, imprimimos todo.
            // Si no, evitamos imprimir el origen del tramo porque ya se imprimió como destino del anterior.
            if (esPrimerNodoAbsoluto || n->padre != nullptr) {
                cout << n->id << " ";
            }
        }

        void procesarViaje(int inicioMensajero) {
            int actualUbicacion = inicioMensajero;
            Entrega* Entregado = listaEntregas;
            bool primerTramoDelViaje = true;

            //Calcular el peso total inicial
            int pesoEnMochila = 0;
            Entrega* temp = listaEntregas;
            while (temp) {
                pesoEnMochila += temp->peso;
                temp = temp->Next;
            }

            while (Entregado) {
                //Dijkstra
                if (ejecutarDijkstra(actualUbicacion, Entregado->santuario, pesoEnMochila)) {
                    NodoSantuario* destNode = FindNode(Entregado->santuario);
                    tiempoTotal += destNode->distanciaMin;
                    imprimirRutaRecursiva(destNode, primerTramoDelViaje);

                    //Decrecimiento del precio
                    pesoEnMochila -= Entregado->peso; 

                    actualUbicacion = Entregado->santuario;
                    primerTramoDelViaje = false;
                }
                Entregado = Entregado->Next;
            }
            cout << endl << tiempoTotal << endl;
        }
};

int main() {
    EnviosSantuarios gm;
    string linea;

    // Lectura total del archivo
    while (getline(cin, linea)) {
        // Obviar lineas vacias
        if (linea.empty()) continue;

        stringstream ss(linea);
        int v1, v2, v3, v4;
        int conteo = 0;
        int temp;

        //números en esta línea específica
        stringstream buscador(linea);
        while (buscador >> temp) {
            conteo++;
        }

        // Clasificamos según la cantidad de números
        if (conteo == 2) {
            if (ss >> v1 >> v2) {
                gm.AgregarEntrega(v1, v2);
            }
        } 
        else if (conteo == 4) {
            // Es un Sendero (A B T M)
            if (ss >> v1 >> v2 >> v3 >> v4) {
                gm.agregarSendero(v1, v2, v3, v4);
            }
        } 
        else if (conteo == 1) {
            // Es el Punto de Inicio (I)
            if (ss >> v1) {
                gm.procesarViaje(v1);
            }
        }
    }

    return 0;
}

/*
CASO DE PRUEBA 
1 2
4 4 
2 10 
3 4 
1 2 3 18 
1 4 8 25 
1 3 3 10 
2 3 5 10 
2 4 4 20 
3 4 2 18 
1 
*/