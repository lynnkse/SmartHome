#ifndef __SAFEDEQUE_H__
#define __SAFEDEQUE_H__

#pragma once

#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

template <class T>
class SafeDeque
{
public:
    void Push(const T& value) 
	{
        {
            unique_lock<std::mutex> lock(this->d_mutex);
            d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }

    T Pop() 
	{
        unique_lock<mutex> lock(this->d_mutex);
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

#endif
