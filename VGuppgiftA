#include <iostream>
#include <stdexcept>

template <typename T, size_t Capacity>
class Queue {
private:
    T data[Capacity]; // Statisk array för att lagra köelement
    size_t front;     // Index för det första elementet i kön
    size_t back;      // Index för nästa tillgängliga plats i kön
    size_t count;     // Antal element i kön

public:
    Queue() : front(0), back(0), count(0) {}

    // Kontrollera om kön är tom
    bool isEmpty() const {
        return count == 0;
    }

    // Kontrollera om kön är full
    bool isFull() const {
        return count == Capacity;
    }

    // Lägg till ett element i kön
    void enqueue(const T& item) {
        if (isFull()) {
            throw std::overflow_error("Queue is full");
        }
        data[back] = item;
        back = (back + 1) % Capacity; // Cirkulär bufferhantering
        ++count;
    }

    // Ta bort ett element från kön
    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        T item = data[front];
        front = (front + 1) % Capacity; // Cirkulär bufferhantering
        --count;
        return item;
    }

    // Hämta det första elementet i kön utan att ta bort det
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return data[front];
    }

    // Hämta antal element i kön
    size_t size() const {
        return count;
    }
};

int main() {
    try {
        Queue<int, 5> q; // Skapar en kö för heltal med kapacitet 5

        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        q.enqueue(4);
        q.enqueue(5);

        std::cout << "First element: " << q.peek() << std::endl;

        while (!q.isEmpty()) {
            std::cout << "Dequeue: " << q.dequeue() << std::endl;
        }

        // Test av att lägga till och ta bort med full/tom kö
        q.enqueue(6);
        std::cout << "Enqueued 6, first element is now: " << q.peek() << std::endl;
        
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
