/* LR8 */

/*
1) конструктор  +
2) деструктор  +
3) подсчёт кол-ва элементов  +
4) добавление значения в начало  +
5) добавление значения в конец  +
6) добавление значения по индексу +
7) добавление значения по указателю (после элемента, указатель на который
передан)  +
8) извлечение значения из начала +?
9) извлечение значения из конца +?
10) извлечение по индексу +?
11) извлечение по указателю (извлекается элемент, указатель на который
передан) +?
12) получение значения по индексу +
13) поиск позиции первого элемента, равного по значению искомому +
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
    unsigned int size = 0;
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
    unsigned int size = ring.size;
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
void insert_index(Ring<T>& ring, T information, int position)
{
    if (position == 1)
        insert_head(ring, information);
    else if (position == ring.size + 1)
        insert_tail(ring, information);
    else
    {
        ring.size++;
        Node<T> *new_element = new Node<T>;
        new_element->information = information;
        unsigned int counter = 0;
        Node<T> *element = ring.head;
        for (int i = 0; i < position - 2; i++)
            element = element->next;
        new_element->previous = element;
        element = element->next;
        new_element->next = element;
        new_element->previous->next = new_element;
        new_element->next->previous = new_element;
    }
}

template <typename T>
void insert_pointer(Ring<T>& ring, T information, Node<T>* pointer)
{
    ring.size++;
    Node<T> *new_element = new Node<T>;
    new_element->information = information;
    new_element->previous = pointer->previous;
    new_element->next = pointer;
    new_element->previous->next = new_element;
    new_element->next->previous = new_element;
}

template <typename T>
T pop_head(Ring<T>& ring)
{
    ring.size--;
    Node<T> *current = ring.head;
    T information = ring.head->information;
    ring.head->next->previous = ring.tail;
    ring.tail->next = ring.head->next;
    ring.head = ring.head->next;
    delete current;
    return information;
}

template <typename T>
T pop_tail(Ring<T>& ring)
{
    ring.size--;
    Node<T> *current = ring.tail;
    T information = ring.tail->information;
    ring.tail->previous->next = ring.head;
    ring.head->previous = ring.tail->previous;
    ring.tail = ring.tail->previous;
    delete current;
    return information;
}

template <typename T>
T pop_index(Ring<T>& ring, unsigned int position)
{
    ring.size--;
    if (position == 1)
        pop_head(ring);
    else if (position == ring.size)
        pop_tail(ring);
    else
    {
        unsigned int counter = 0;
        Node<T> *element = new Node<T>;
        element = ring.head;
        while (counter != position)
        {
            element = element->next;
            counter++;
        }
        element->previous->next = element->next;
        element->next->previous = element->previous;
        T used = element->information;
        delete element;
        return used;
    }
}

template <typename T>
T pop_pointer(Ring<T>& ring, Node<T> *pointer)
{
    pointer->next->previous = pointer->previous;
    pointer->previous->next = pointer->next;
    T used = pointer->information;
    delete pointer;
    return used;
}

template <typename T>
T get_value(const Ring<T>& ring, unsigned int position)
{
    unsigned int counter = 0;
    Node<T> *element = ring.head;
    while (counter != position)
    {
        element = element->next;
        counter++;
    }
    element = element->next;
    return element->information;
}

template <typename T>
T find(const Ring<T>& ring, T value)
{
    unsigned int position = 1;
    Node<T> *element = ring.head;
    while (element->information != value)
    {
        if (element != ring.head)
        {
            position++;
            element = element->next;
        }
        else if ((position == 1) && (element == ring.head))
        {
            position++;
            element = element->next;
        }
        else
        {
            position = -1;
            break;
        }
    }
    if (position != -1)
        return position;
    else
        return 0;
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
    insert_tail(ring, 4);

    std::cout << "Elements: ";
    print(ring);
    std::cout << std::endl <<"Size: " << size(ring) << std::endl << std::endl;

    insert_index(ring, 10, 2);
    std::cout << "Elements: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    Node<int> *pointer1 = ring.head->next;
    insert_pointer(ring, 9, pointer1);
    std::cout << "After insert by pointer: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    pop_head(ring);
    std::cout << "Elements after pop_head: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    pop_tail(ring);
    std::cout << "Elements after pop_tail: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    pop_index(ring, 2);
    std::cout << "Elements after pop_index: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    Node<int> *pointer2 = ring.head->next;
    pop_pointer(ring, pointer2);
    std::cout << "Elements after pop_pointer: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    std::cout << "Get value: " << get_value(ring, 2) << std::endl << std::endl;

    if (find(ring, 6) != 0)
        std::cout << "Find value: " << find(ring, 141);
    else
        std::cout << "There is no element you searched.";

    return 0;
}
