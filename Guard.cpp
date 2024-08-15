#include <mutex>

class Guard {
public:
    // Constructor: Locks the mutex
    explicit Guard(std::mutex& mtx) : mtx_(mtx) {
        mtx_.lock();
    }

    // Destructor: Unlocks the mutex
    ~Guard() {
        mtx_.unlock();
    }

    // Delete the copy constructor and copy assignment operator
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;

private:
    std::mutex& mtx_;
};


