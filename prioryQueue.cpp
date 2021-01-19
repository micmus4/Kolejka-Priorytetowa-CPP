#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstdio>

using namespace std;


int heapSize = 0; // wielkosc kopca.
int length; // maksymalna wielkosc kopca.


    class Element{

    public:

        int priority; // priorytet zadania.
        int ID; // numer zadania.
        string task; // zadanie

        Element(){}

        Element(int x, int y){
            priority = x;
            ID = y;
        }
    };

    // metoda zamieniajaca dwa elementy klasy 'Element'.
    void swap_(Element *a, Element*b) {
        Element temp;
        temp = *a;
        *a = *b;
        *b = temp;
}

    // funkcja zwracajaca indeks rodzica.
    int getParent(int index, int arraySize){
            return index / 2;
    }

    // funkcja zwracajaca indeks lewego syna.
    int getLeftChild(int index, int arraySize){
            return 2 * index;
    }

    // funkcja zwracajaca indeks prawego syna.
    int getRightChild(int index, int arraySize){
            return 2 * index + 1;
    }

    // funkcja, ktora kladzie elementy w kopcu w odpowiedniej kolejnosci.
    void MaxHeapify(Element A[], int index, int arraySize){
        int maxIndex = index;
        if((getLeftChild(index, arraySize) <= heapSize) && (A[getLeftChild(index, arraySize)].priority > A[maxIndex].priority)){
                maxIndex = getLeftChild(index, arraySize);
        }
        else if((getLeftChild(index, arraySize) <= heapSize) && (A[getLeftChild(index, arraySize)].priority== A[maxIndex].priority) && (A[getLeftChild(index, arraySize)].ID < A[maxIndex].ID)){
                maxIndex = getLeftChild(index, arraySize);
        }

        if((getRightChild(index, arraySize) <= heapSize) && (A[getRightChild(index, arraySize)].priority > A[maxIndex].priority)){
                maxIndex = getRightChild(index, arraySize);
        }

        else if((getRightChild(index, arraySize) <= heapSize) && (A[getRightChild(index, arraySize)].priority == A[maxIndex].priority) && (A[getRightChild(index, arraySize)].ID < A[maxIndex].ID)){
                maxIndex = getRightChild(index, arraySize);
        }

        if(maxIndex != index){
            swap_(&A[maxIndex], &A[index]);
            MaxHeapify(A, maxIndex, arraySize);
        }
    }

    // sprawdza czy kolejka jest pusta.
    bool isEmpty(){
        if(heapSize == 0){
            return true;
        } 
            return false;
    }

    // sprawdza czy kolejka jest pelna.
    bool isFull(){
        if(heapSize == length){
            return true;
        }
        return false;
    }


    // zwraca zadanie o najwyzszym priorytecie.
    bool ExtractMax(Element A[], int arraySize) {
          if(isEmpty()){
              return false;
          }
          string maxTask;
          int maxID;
          int maxPriority;
          maxTask = A[1].task;
          maxID = A[1].ID;
          maxPriority = A[1].priority;
          A[1] = A[heapSize];
          heapSize--;
          MaxHeapify(A, 1, arraySize);
          cout << "Zadanie: " << maxTask << ", wstawione do kolejki jako: " << maxID << ", priorytet: " << maxPriority << endl;
          return true;
    }


    // umieszcza w odpowiednim miejscu nowy element kolejki.
    void IncreaseKey(Element A[], int index, Element key, int arraySize) {
          A[index] = key;
          while(index > 1 && ((A[getParent(index, arraySize)].priority < A[index].priority))) {
            swap_(&A[index], &A[getParent(index, arraySize)]);
            index = getParent(index, arraySize);
          }


    }

    // przygotowuje element do bycia wstawionym do kolejki.
    bool InsertToHeap(Element A[], Element key, int arraySize) {
          if(isFull()){
              return false;
          }        
          heapSize++;
          A[heapSize].priority = -1;
          IncreaseKey(A, heapSize, key, arraySize);
          return true;
    }

    



int main(){

    int arraySize;
    Element* kopiec;
    Element temp;
    string operacja;
    string task;
    int priority;
    int ID = 1;
    printf("Wybierz wielkosc priorytetowej kolejki: ");
    scanf("%d", &length);
    kopiec = new Element[length + 1];
    arraySize = length + 1;
    printf("Stworzyles priorytetowa kolejke o wielkosci: %d  (jego elementy znajduja sie na indeksach <1 ; %d>)\n", length, length);
    printf("Dostepne operacje:\n\n");
    printf("\t - ENQUEUE -> Dodaje zadanie do kolejki priorytetowej.\n");
    printf("\t - ISEMPTY -> Sprawdza czy kolejka priorytetowa jest pusta.\n");
    printf("\t - ISFULL -> Sprawdza czy kolejka priorytetowa jest pelna.\n");
    printf("\t - EXTRACT -> Wypisuje zadanie o najwyzszym priorytecie (jesli jest wiecej niz 1 o takim samym priorytecie to zwraca ten wstawiony jako pierwszy).\n");
    while(true){
        printf("Wpisz operacje: ");
        cin >> operacja;
        if(operacja == "ENQUEUE"){
            printf("Wpisz nazwe zadania do wykonania: ");
            cin.ignore();
            getline(cin, task, '\n');
            printf("Wpisz priorytet tego zadania (wartosc liczbowa): ");
            scanf("%d", &priority);
            temp.task = task;
            temp.priority = priority;
            temp.ID = ID;
            ID++;
            if(InsertToHeap(kopiec, temp, arraySize)){
                printf("Wstawiono nowe zadanie do kolejki priorytetowej.\n");
            } else {
                printf("Kolejka priorytetowa jest pelna, nie mozna wiec wstawic do niej nowego zadania.\n");
            }
        }
        if(operacja == "ISEMPTY"){
            if(isEmpty()){
                printf("Kolejka priorytetowa jest pusta.\n");
            } else {
                printf("Kolejka priorytetowa nie jest pusta.\n");
            }
        }
        if(operacja == "ISFULL"){
            if(isFull()){
                printf("Kolejka priorytetowa jest pelna.\n");
            } else {
                printf("Kolejka priorytetowa nie jest pelna.\n");
            }
        }
        if(operacja == "EXTRACT"){
            if(!ExtractMax(kopiec, arraySize)){
                printf("Kolejka priorytetowa jest pusta, nie mozna wiec zabrac z niej zadania.\n");
            }
        }
    }
}

