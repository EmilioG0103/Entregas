// Emilio Gonzalez Rosete
// Franco Emmanuel Ortega Cervantes

#include <iostream>
#include <cmath>
#include <forward_list>
using namespace std;

// CLASE SENTINEL LINKED LIST

template <typename T>
class SentinelLinkedList 
{
private:
    template <typename U>
    class Node 
    {
    public:
        T data;             // Dato que guarda el nodo
        Node<U>* next;      // Puntero al siguiente nodo
        Node<U>* prev;      // Puntero al anterior

        Node() : next(nullptr), prev(nullptr) {}                   // Constructor vacío
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}   // Constructor con un valor
    };

    Node<T>* NIL;     // Nodo que marca inicio y fin
    int count;        // Número de elementos

public:
    SentinelLinkedList() 
    {
        count = 0;
        NIL = new Node<T>();
        NIL->next = NIL;
        NIL->prev = NIL;
    }

    int GetCount() { return count; }

    void PushBack(T value) 
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = NIL;
        newNode->prev = NIL->prev;
        NIL->prev->next = newNode;
        NIL->prev = newNode;
        count++;
    }

    T PopBack() 
    {
        if (count == 0) return {};
        Node<T>* penultimate = NIL->prev;
        T data = penultimate->data;
        NIL->prev = penultimate->prev;
        penultimate->prev->next = NIL;
        delete penultimate;
        count--;
        return data;
    }

    // La neva función 
    void PushFront(T value) 
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = NIL->next;
        newNode->prev = NIL;
        NIL->next->prev = newNode;
        NIL->next = newNode;
        count++;
    }

    T PopFront() 
    {
        if (count == 0) return {};
        Node<T>* front = NIL->next;
        T val = front->data;
        NIL->next = front->next;
        front->next->prev = NIL;
        delete front;
        count--;
        return val;
    }

    T Front() 
    {
        if (count == 0) return {};
        return NIL->next->data;
    }
};

// CLASE LQUEUE

template <typename T>
class LQueue 
{
private:
    SentinelLinkedList<T> data;

public:
    void Enqueue(T val) { data.PushBack(val); }   // Agrega al final
    T Dequeue() { return data.PopFront(); }       // Quita el de enfrente
    T Front() { return data.Front(); }            // Muestra el de enfrente
    int GetCount() { return data.GetCount(); }    // El total de elementos
};

// CLASE LSTACK 

template <typename T>
class LStack {
private:
    forward_list<T> list; // El STL forward_list
    int count;

public:
    LStack() : count(0) {}

    void Push(T val) 
    {
        list.push_front(val);
        count++;
    }

    T Pop() 
    {
        if (count == 0) return {};
        T val = list.front();
        list.pop_front();
        count--;
        return val;
    }

    T Peak() 
    {
        if (count == 0) return {};
        return list.front();
    }

    int Count() { return count; }
};

// CLASES DE FIGURAS GEOMÉTRICAS

class Figura 
{
protected:
    string nombre;

public:
    Figura(string n) : nombre(n) {}
    virtual ~Figura() {}

    virtual float CalcularArea() = 0;
    virtual float CalcularPerimetro() = 0;
    const string& ObtenerNombreDeFigura() { return nombre; }
};

class Circulo : public Figura 
{
private:
    float radio;

public:
    Circulo(float r) : Figura("Círculo"), radio(r) {}

    float CalcularArea() override { return 3.1416f * radio * radio; }
    float CalcularPerimetro() override { return 2 * 3.1416f * radio; }
};

class Cuadrado : public Figura 
{
protected:
    float lado;

public:
    Cuadrado(float l) : Figura("Cuadrado"), lado(l) {}

    float CalcularArea() override { return lado * lado; }
    float CalcularPerimetro() override { return 4 * lado; }
    float GetLado() const { return lado; }
};

class FiguraNLados : public Figura 
{
private:
    int lados;
    float longitud;

public:
    FiguraNLados(int n, float l) : Figura("Figura N Lados"), lados(n), longitud(l) {}

    float CalcularArea() override 
    {
        return (lados * longitud * longitud) / (4 * tan(3.1416f / lados));
    }

    float CalcularPerimetro() override { return lados * longitud; }
};

class Cubo : public Cuadrado 
{
public:
    Cubo(float l) : Cuadrado(l) { nombre = "Cubo"; }

    float Volumen() { return lado * lado * lado; }
    float Surface() { return 6 * lado * lado; }
};

class Linea : public Figura 
{
private:
    float* segmentos;
    int cantidad;

public:
    Linea(float* arr, int size) : Figura("Línea"), cantidad(size) 
    {
        segmentos = new float[cantidad];
        for (int i = 0; i < cantidad; i++) 
        {
            segmentos[i] = arr[i];
        }
    }

    float CalcularArea() override { return 0; }

    float CalcularPerimetro() override 
    {
        float suma = 0;
        for (int i = 0; i < cantidad; i++) 
        {
            suma += segmentos[i];
        }
        return suma;
    }

    ~Linea() {
        delete[] segmentos;
    }
};

// FUNCIÓN MAIN DE PRUEBA

int main() 
{
    // Prueb de LQueue
    LQueue<int> cola;
    cola.Enqueue(10);
    cola.Enqueue(20);
    cola.Enqueue(30);
    cout<<"Frente de la cola: "<<cola.Front()<<endl;
    cout<<"Dequeue: "<<cola.Dequeue()<<endl;
    cout<<"Nuevo frente: "<<cola.Front()<<endl;

    // Prueba de LStack
    LStack<string> pila;
    pila.Push("Hola");
    pila.Push("Mundo");
    cout<<"\nElemento al tope de la pila: "<<pila.Peak()<<endl;
    cout<<"Pop: "<<pila.Pop()<<endl;
    cout<<"Nuevo tope: "<<pila.Peak()<<endl;

    // Prueba con las figuras
    Figura* f1 = new Circulo(3);
    Figura* f2 = new Cuadrado(4);
    Figura* f3 = new FiguraNLados(6, 2);
    Cubo cubo(5);
    float segmentos[] = { 1.5, 2.5, 3.5 };
    Figura* f4 = new Linea(segmentos, 3);

    cout<<"\n"<<f1->ObtenerNombreDeFigura()<<": Área = "<<f1->CalcularArea()<<endl;
    cout<<f2->ObtenerNombreDeFigura()<<": Área = "<<f2->CalcularArea()<<endl;
    cout<<f3->ObtenerNombreDeFigura()<<": Área = "<<f3->CalcularArea()<<endl;
    cout<<f4->ObtenerNombreDeFigura()<<": Perímetro = "<<f4->CalcularPerimetro()<<endl;

    cout<<"Cubo: Volumen = "<<cubo.Volumen()<<" | Área superficial = "<<cubo.Surface()<<endl;

    delete f1;
    delete f2;
    delete f3;
    delete f4;

    return 0;
}

// Videos de YT que nos ayudo a entender un poco mejor: 103. Programación en C++ || Listas || Concepto de Lista Enlazada
// Y aparte solo le preguntamos a la IA sobre la libreria cmath, ya que no entendiamos bien la manera de poder calcular el area de los poligonos