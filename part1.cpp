#include <iostream>

template <typename T>
struct Node
{
    T information;
    Node *next = nullptr;
    Node *previous = nullptr;
};

struct people
{
    std::string name;
    int age;
    std::string hobby;
};

std::ostream& operator<< (std::ostream& output, const people& person)
{
    output << "Name: " << person.name << " Age: " << person.age << " Hobby: " << person.hobby << std::endl;
    return output;
}

template <typename T>
struct Ring
{
    Node<T> *head;
    Node<T> *tail;
    unsigned int size;
};

template <typename T>
void constructor(Ring<T>& ring)
{
    ring.head = nullptr;
    ring.tail = nullptr;
    ring.size = 0;
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
    {
        ring.head = element;
        ring.tail = element;
        element->next = element;
        element->previous = element;
    }
    else
    {
        element->next = ring.head;
        ring.head->previous = element;
        element->previous = ring.tail;
        ring.tail->next = element;
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
    {
        ring.tail = element;
        ring.head = element;
        element->next = element;
        element->previous = element;
    }
    else
    {
        ring.tail->next = element;
        element->previous = ring.tail;
        ring.head->previous = element;
        element->next = ring.head;
        ring.tail = element;
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
    Node<T> *element = new Node<T>;
    element->information = information;
    element->previous = pointer->previous;
    element->next = pointer;
    element->previous->next = element;
    element->next->previous = element;
}

template <typename T>
T pop_head(Ring<T>& ring)
{
    ring.size--;
    Node<T> *current = ring.head;
    T inf = ring.head->information;
    ring.head->next->previous = ring.tail;
    ring.tail->next = ring.head->next;
    ring.head = ring.head->next;
    delete current;
    return inf;
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
    if (position == 1)
        pop_head(ring);
    else if (position == size(ring))
        pop_tail(ring);
    else
    {
        unsigned int counter = 1;
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
        ring.size--;
        delete element;
        return used;
    }
}

template <typename T>
T pop_pointer(Ring<T>& ring, Node<T> *pointer)
{
    ring.size--;
    pointer->next->previous = pointer->previous;
    pointer->previous->next = pointer->next;
    T used = pointer->information;
    delete pointer;
    return used;
}

template <typename T>
T get_value(const Ring<T>& ring, unsigned int position)
{
    unsigned int counter = 1;
    Node<T> *element = ring.head;
    while (counter != position)
    {
        element = element->next;
        counter++;
    }
    T information = element->information;
    return information;
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
void print(const Ring<T>& ring)
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
    insert_head(ring, 2);
    insert_tail(ring, 3);
    insert_tail(ring, 4);
    insert_tail(ring, 1);

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

    std::cout << "Popped_head element is " << pop_head(ring) << std::endl;
    std::cout << "Elements after pop_head: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    std::cout << "Popped_tail element is " << pop_tail(ring) << std::endl;
    std::cout << "Elements after pop_tail: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    std::cout << "Popped_index element is " << pop_index(ring, 2) << std::endl;
    std::cout << "Elements after pop_index: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    Node<int> *pointer2 = ring.head->next;
    std::cout << "Popped_pointer element is " << pop_pointer(ring, pointer2) << std::endl;
    std::cout << "Elements after pop_pointer: ";
    print(ring);
    std::cout << std::endl << "Size: " << ring.size << std::endl << std::endl;

    std::cout << "Get value: " << get_value(ring, 5) << std::endl << std::endl;

    if (find(ring, 3) != -1)
        std::cout << "find value: " << find(ring, 3);
    else
        std::cout << "There is no element you searched.";

    destructor(ring);

    std::cout << "Size after destructor: " << size(ring);

    Ring<people> human;

    people man1 = { "Vasya", 16, "Music" };
    people woman1 = { "Viktroria", 25, "Art" };
    people man2 = { "Ivan", 18, "Chess" };
    people woman2 = { "Katerina", 30, "Photo" };

    constructor(human);

    insert_head(human, man1);
    insert_tail(human, woman1);
    insert_head(human, man2);
    insert_tail(human, woman2);

    print(human);
    std::cout << "Size of human: " << size(human) << std::endl << std::endl;

    people man3 = { "Grigory", 42, "Programming"};
    insert_index(human, man3, 3);

    std::cout << "People after insert_index: " << std::endl;
    print(human);
    std::cout << "Size of human: " << size(human) << std::endl << std::endl;

    people woman3 = { "Maria", 23, "Tennis"};
    Node<people> *pointer3 = human.head->next;
    insert_pointer(human, woman3, pointer3);

    std::cout << "People after insert_pointer: " << std::endl;
    print(human);
    std::cout << "Size of human: " << size(human) << std::endl << std::endl;

    std::cout << "Popped_head element is " << pop_head(human) << std::endl;
    std::cout << "People after pop_head:" << std::endl;
    print(human);
    std::cout << std::endl << "Size: " << size(human) << std::endl << std::endl;

    std::cout << "Popped_tail element is " << pop_tail(human) << std::endl;
    std::cout << "People after pop_tail:" << std::endl;
    print(human);
    std::cout << std::endl << "Size: " << size(human) << std::endl << std::endl;

    std::cout << "Popped_index element is " << pop_index(human, 3) << std::endl;
    std::cout << "People after pop_index:" << std::endl;
    print(human);
    std::cout << std::endl << "Size: " << size(human) << std::endl << std::endl;

    std::cout << "Popped_pointer element is " << pop_pointer(human, pointer3) << std::endl;
    std::cout << "People after pop_pointer:" << std::endl;
    print(human);
    std::cout << std::endl << "Size: " << size(human) << std::endl << std::endl;

    std::cout << "Get value: " << get_value(human, 2) << std::endl << std::endl;
    destructor(human);

    std::cout << "Size after destructor: " << size(human);

    return 0;
}
