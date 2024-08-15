#include <iostream>
#include <mutex>
#include <pthread.h>

// Abstract base class
class SingletonBase {
public:
    // Delete copy constructor and assignment operator to prevent copying
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

    virtual ~SingletonBase() {}

    // Static method to access the singleton instance
    static SingletonBase* getInstance() {
        pthread_mutex_lock(&mutex_);
        if (instance_ == nullptr) {
            instance_ = new SingletonBase();
        }
        pthread_mutex_unlock(&mutex_);
        return instance_;
    }

protected:
    SingletonBase() {
        // Constructor protected to prevent direct instantiation
    }

private:
    static SingletonBase* instance_;
    static pthread_mutex_t mutex_;
};

// Initialize static members
SingletonBase* SingletonBase::instance_ = nullptr;
pthread_mutex_t SingletonBase::mutex_ = PTHREAD_MUTEX_INITIALIZER;

int main() {
    SingletonBase* singleton = SingletonBase::getInstance();
    // Use the singleton instance here

    return 0;
}
