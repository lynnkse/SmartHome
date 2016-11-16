#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

template <typename T>
class BlockingQueue
{
public:
    void Push(T const& value) 
	{
        {
            unique_lock<std::mutex> lock(this->d_mutex);
            d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }

    T Pop() 
	{
        unique_lock<std::mutex> lock(this->d_mutex);
        this->d_condition.wait(lock, [=]{ return !this->d_queue.empty(); });
        T rc(move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
    }

    int size() { return d_queue.size(); }

private:
    mutex d_mutex;
    condition_variable d_condition;
    deque<T> d_queue;
};
