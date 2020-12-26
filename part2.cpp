#include <iostream>
#include <string>

struct people
{
    std::string name;
    int mark;

    int operator = (int flag)
    {
        flag = 0;
        name = "";
        mark = 0;
        return flag;
    }

    int operator != (int flag)
    {
        if (name != "" && mark != 0)
        {
            flag = 1;
            return flag;
        }
        else
        {
            flag = 0;
            return flag;
        }
    }
};

std::ostream& operator << (std::ostream &output, const people &person)
{
    output << "Name: " << person.name << " Mark: " << person.mark << std::endl;
    return output;
}

template <typename T, int size>
struct List
{
    T array[size];
    int current;
};

template <typename T, int size>
void constructor(List<T, size>& list)
{
    list.current = 0;
    for (int i = 0; i < size; i++)
        list.array[i] = 0;
}

template <typename T, int size>
void destructor(List<T, size>& list)
{
    list.current = 0;
    for (int i = 0; i < size; i++)
        list.array[i] = 0;
}

template <typename T, int size>
unsigned int Lengh(const List<T, size>& list)
{
    unsigned int sum = 0;
    for (int i = 0; i < list.current; i++)
        sum++;
    return sum;
}

template <typename T, int size>
void push_tail(List<T, size>& list, T digit)
{
    list.current++;
    int i = 0;
    while (list.array[i] != 0)
        i++;
    if (list.current < size)
        list.array[i] = digit;
    else
    {
        std::cout << "Array is full" << std::endl << std::endl;
        list.current--;
    }
}

template <typename T, int size>
void push_index(List<T, size>& list, T digit, int index)
{
    if (list.current == size)
        std::cout << "Array is full" << std::endl << std::endl;
    else
    {
        for (int i = list.current - 1; i >= index; i--)
            list.array[i + 1] = list.array[i];
        list.array[index] = digit;
        list.current++;
    }
}

template <typename T, int size>
T pop_head(List<T, size>& list)
{
    T element = list.array[list.current - 1];
    for (int i = list.current - 1; i > 0; i--)
        list.array[i] = list.array[i - 1];
    for (int i = 0; i < list.current; i++)
        list.array[i] = list.array[i + 1];
    list.array[list.current - 1] = 0;
    list.current--;
    return element;
}

template <typename T, int size>
T pop_tail(List<T, size>& list)
{
    T element = list.array[0];
    for (int i = 1; i < list.current; i++)
        list.array[i - 1] = list.array[i];
    list.current--;
    list.array[list.current] = 0;
    return element;
}

template <typename T, int size>
T pop_index(List<T, size>& list, int index)
{
    T element = list.array[index - 1];
    for (int i = index + 1; i < list.current; i++)
        list.array[i - 1] = list.array[i];
    list.current--;
    list.array[list.current] = 0;
    return element;
}

template <typename T, int size>
T get_value(List<T, size>& list, int index)
{
    return list.array[index - 1];
}

template <typename T, int size>
int find(List<T, size>& list, T value)
{
    int finish = -1;
    for (int i = 0; i < list.current; i++)
        if (list.array[i] == value)
        {
            finish = i + 1;
            break;
        }
    return finish;
}

template <typename T, int size>
void print_info(const List<T, size>& list)
{
    if (list.current == 0)
        std::cout << "There aren't elements" << std::endl;
    else
    {
        std::cout << "Array: " << std::endl;
        for (int i = 0; i < Lengh(list); i++)
            std::cout << list.array[i] << " ";
        std::cout << std::endl << "Size: " << list.current << std::endl << std::endl;
    }
}

int main()
{

    List<int, 10> list;
    constructor(list);
    push_tail(list, 20);
    push_tail(list, 19);
    push_tail(list, 18);
    push_tail(list, 16);

    print_info(list);
    std::cout << std::endl;

    push_index(list, 17, 3);

    print_info(list);
    std::cout << std::endl;

    push_index(list, 100, 2);

    print_info(list);
    std::cout << std::endl;

    push_tail(list, 34);
    push_tail(list, 76);
    push_tail(list, 2);

    push_index(list, 23, 5);

    print_info(list);
    std::cout << std::endl;

    push_index(list, 3, 3);
    push_tail(list, 5);

    std:: cout << "Popped_head element is " << pop_head(list) << std::endl;
    print_info(list);

    std:: cout << "Popped_head element is " << pop_head(list) << std::endl;
    print_info(list);

    std:: cout << "Popped_tail element is " << pop_tail(list) << std::endl;
    print_info(list);

    std:: cout << "Popped_tail element is " << pop_tail(list) << std::endl;
    print_info(list);

    std:: cout << "Popped_head element is " << pop_head(list) << std::endl;
    print_info(list);

    std:: cout << "Popped_index element is " << pop_index(list, 5) << std::endl;
    print_info(list);

    std::cout << "Get_value element is " << get_value(list, 2) << std::endl << std::endl;

    if (find(list, 17) == -1)
        std::cout << "There isn't interest value";
    else
        std::cout << "Find element is " << find(list, 17) << std::endl << std::endl;

    destructor(list);

    print_info(list);

    List<people, 4> human;

    people man1 = { "Oleg", 5 };
    people man2 = { "Viktor", 4 };
    people woman1 = { "Marina", 3 };
    people woman2 = { "Vasilisa", 2 };

    constructor(human);

    push_tail(human, man1);
    push_tail(human, woman1);
    push_index(human, man2, 2);
    push_index(human, woman2, 3);

    print_info(human);

    pop_head(human);
    pop_tail(human);
    pop_index(human, 2);

    print_info(human);

    std::cout << "Get_value: " << get_value(human, 1) << std::endl;

    destructor(human);

    print_info(human);

    return 0;
}
