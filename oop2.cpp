#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

template <class T>
class Array {
public:

    Array(T* array, int length, int reserve = 10)
    {
        this->_size = length;
        this->_reserve = reserve;
        this->_capacity = length + reserve;
        this->_array = this->resize(array, length, this->_capacity);
    }

    Array(const Array& array) {
        this->_size = array._size;
        this->_reserve = array._reserve;
        this->_capacity = array._capacity;
        this->_array = this->resize(array._array, this->_size, this->_capacity);
    }

    Array(T* firstPointer, T* secondPointer, int reserve = 10)
    {
        this->_size = secondPointer - firstPointer;
        this->_reserve = reserve;
        this->_capacity = this->_size + this->_reserve;
        this->_array = this->resize(firstPointer, this->_size, this->_capacity);
    }

    ~Array()
    {
        delete[] this->_array;
    }


    int capacity() { return _capacity; }

    int size() { return _size; }

    void push(T value)
    {
        if (this->_size == this->_capacity) {
            this->_capacity += this->_reserve;
            this->_array = this->resize(this->_array, this->_size, this->_capacity, true);
        }
        this->_array[_size] = value;
        this->_size += 1;
    }

    T pop() throw(std::out_of_range)
    {
        if (this->_size == 0)
            throw std::out_of_range("Массив уже пуст");
        T deletedValue = this->_array[this->_size];
        this->_size -= 1;

        if (this->_capacity - this->_size > this->_reserve) {
            this->_capacity = this->_size + this->_reserve;
            this->_array = this->resize(this->_array, this->_size, this->_capacity, true);
        }
        return deletedValue;
    }

    T& operator[] (const int index) throw(std::out_of_range)
    {
        if (index < 0 || index >= this->_size)
            throw std::out_of_range("out of range");
        return this->_array[index];
    }

    Array& operator= (const Array& item)
    {
        if (this != &item) {
            this->_capacity = item._capacity;
            this->_size = item._size;
            this->_array = this->resize(item._array, item._size, item._capacity);
        }
        return *this;
    }

    class Iterator {
    public:
        friend class Array;

        Iterator(T* element) : current(element) {}

        Iterator(const Iterator& it) : current(it.current) {}

        bool operator== (const Iterator& it) { return this->current == it.current; }

        bool operator!= (const Iterator& it) { return this->current != it.current; }

        Iterator& operator++() { if (this->current != 0) this->current = this->current + 1; return *this; }

        Iterator& operator--() { if (this->current != 0) this->current = this->current + 1; return *this; }

        Iterator& operator+(int n)
        {
            Iterator result = this->current;
            for (int i = 0; i < n; i++)
                result.current = result.current + 1;
            return result;
        }
        Iterator& operator-(int n)
        {
            Iterator result = this->current;
            for (int i = 0; i < n; i++)
                result.current = result.current - 1;
            return result;
        }
        T& operator*() const
        {
            if (this->current != 0) return *this->current;
            else throw;
        }
    private:
        T* current;
    };


    Iterator begin() { return this->_array; }

    Iterator end() { return this->_array + this->_size; }

protected:
    T* resize(T* array, int length, int capacity, bool clear = false) throw(std::bad_alloc)
    {
        try {
            T* newArray = new T[capacity];
            for (int i = 0; i < capacity; i++)
                newArray[i] = array[i];
            if (clear)
                delete[] array;
            return newArray;
        }
        catch (std::bad_alloc e) {
            std::cout << "Ошибка выделения памяти " << e.what() << std::endl;
            exit(0);
        }

    }

    int _size;

    int _capacity;

    int _reserve;

    T* _array;
};

struct Pair {
    Pair(double x = 0, double p = 0)
    {
        this->x = x;
        this->p = p;
    }
    Pair(const Pair& a)
    {
        x = a.x;
        p = a.p;
    }
    Pair& operator= (const Pair& Data)
    {
        x = Data.x;
        p = Data.p;
        return *this;
    }
    friend std::ostream& operator<< (std::ostream& stream, const Pair& item)
    {
        stream << "(" << item.x << "," << item.p << ")";
        return stream;
    }
    friend std::istream& operator>> (std::istream& stream, Pair& item)
    {
        stream >> item.x >> item.p;
        return stream;
    }

    double x;
    double p;
};

class Rand : public Array<Pair>
{
public:
    Rand(Pair* array, int length, int reserve = 10) : Array(array, length, reserve)
    {

    }


    double getMonteCarlo()
    {
        double sumP = 0;
        for (int i = 0; i < this->_size; i++)
            sumP += this->_array[i].p;

        double a = this->_array[0].x;
        double b = this->_array[this->_size - 1].x;
        for (int i = 0; i < this->_size; i++) {
            if (a < this->_array[i].x)
                a = this->_array[i].x;
            if (b > this->_array[i].x)
                b = this->_array[i].x;
        }

        double coef = (b - a) / this->_size;

        return abs(coef * sumP);
    }

    double getMean(char varType = 'x', bool inSquare = false)
    {
        double mean = 0;
        for (int i = 0; i < this->_size; i++) {
            double value;
            if (varType == 'x')
                value = this->_array[i].x;
            else if (varType == 'y' || varType == 'p')
                value = this->_array[i].p;
            else
                throw std::invalid_argument("Неверное значение параметра varType");

            if (inSquare)
                value *= value;
            mean += (1.0 / this->_size) * value;
        }
        return mean;
    }


    double getDispersion(char varType = 'x')
    {
        if (!(varType == 'x' || varType == 'y' || varType == 'p'))
            throw std::invalid_argument("Неверное значение параметра varType");

        double dispersion = this->getMean(varType, true) - pow(this->getMean(varType), 2);
        return dispersion;
    }

    friend std::ostream& operator<< (std::ostream& os, Rand& rand) {
        std::cout << "argument ";
        for (int i = 0; i < rand._size; i++) {
            os << rand._array[i].x << " ";
        }
        os << std::endl << "function ";
        for (int i = 0; i < rand._size; i++) {
            os << rand._array[i].p << " ";
        }
        os << " MO X= " << rand.getMean('x') << " ";
        os << "Disp X= " << rand.getDispersion('x') << " ";
        os << "MO Y= " << rand.getMean('y') << " ";
        os << "Disp Y= " << rand.getDispersion('y') << " ";
        os << "MonteKarlo= " << rand.getMonteCarlo();
        return os;
    }

};


int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    std::cin >> n;
    Pair* inputArray = new Pair[n];
    for (int i = 0; i < n; i++)
        std::cin >> inputArray[i].x;
    for (int i = 0; i < n; i++)
        std::cin >> inputArray[i].p;
    Rand rand = Rand(inputArray, n);
    std::cout << "input= " << rand;

    std::cout << "Вывод" << std::endl;

    delete inputArray;

    return 0;
}
