/* LR8 */

/*
1) конструктор  +
2) деструктор  +
3) подсчёт кол-ва элементов  +
4) добавление значения в начало  +
5) добавление значения в конец  +
6) добавление значения по индексу
7) добавление значения по указателю (после элемента, указатель на который
передан)
8) извлечение значения из начала
9) извлечение значения из конца
10) извлечение по индексу
11) извлечение по указателю (извлекается элемент, указатель на который
передан)
12) получение значения по индексу
13) поиск позиции первого элемента, равного по значению искомому
14) печать на экран  +
 */

#include <iostream>

template <typename T>
struct Node
{
    T information;
    Node *next = nullptr;
    Node *previous = nullptr;
};

template <typename T>
struct Ring
{
    Node<T> *head;
    Node<T> *tail;
    int size = 0;
};

template <typename T>
void constructor(Ring<T>& ring)
{
    ring.head = nullptr;
    ring.tail = nullptr;
}

template <typename T>
void destructor(Ring<T>& ring)
{
    while (ring.size != 0)
    {
        Node<T> *element = ring.head->next;
        delete ring.head;
        ring.head = element;
        ring.size--;
    }
}

template <typename T>
unsigned int size(const Ring<T>& ring)
{
    int size = ring.size;
    return size;
}

template <typename T>
void insert_head(Ring<T>& ring, T information)
{
    ring.size++;
    Node<T> *element = new Node<T>;
    element->information = information;
    if (ring.head == nullptr)
        ring.head = element->next = element->previous = element;
    else
    {
        element->next = ring.head;
        element->previous = ring.head->previous;
        ring.head->previous->next = element;
        ring.head->previous = element;
        ring.head = element;
    }
}

template <typename T>
void insert_tail(Ring<T>& ring, T information)
{
    ring.size++;
    Node<T> *element = new Node<T>;
    element->information = information;
    if (ring.head == nullptr)
        ring.head = element->next = element->previous = element;
    else
    {
        element->next = ring.head;
        element->previous = ring.head->previous;
        ring.head->previous->next = element;
        ring.head->previous = element;
    }
}

template <typename T>
void insert_index(Ring<T>& ring, T information, int index)
{

}

template <typename T>
T pop_head(Ring<T>& ring)
{
    Node<T> *element = new Node<T>;
    ring.tail->next = ring.head->next;
    ring.head->next->previous = ring.tail;
    T final = ring.head->information;
    element = ring.head->next;
    delete ring.head;
    ring.head = element;
    return final;
}

template <typename T>
void print(const Ring<T> & ring)
{
    Node<T> *element = ring.head;
    do
    {
        std::cout << element->information << ' ';
        element = element->next;
    } while (element != ring.head);
}

int main()
{
    Ring<int> ring;

    constructor(ring);

    insert_head(ring, 2);
    insert_head(ring, 1);
    insert_tail(ring, 3);

    std::cout << "Elements: ";
    print(ring);
    std::cout << std::endl;

    std::cout << size(ring);

    std::cout << std::endl << "pop: " << pop_head(ring);

    return 0;
}