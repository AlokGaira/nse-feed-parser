//
// Created by alok on 27/11/18.
//

#ifndef LEARN_BOUNDED_QUEUE_H
#define LEARN_BOUNDED_QUEUE_H


#include <boost/circular_buffer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <boost/timer/timer.hpp> // for auto_cpu_timer

/**
 * https://www.boost.org/doc/libs/1_58_0/libs/circular_buffer/example/circular_buffer_bound_example.cpp
 */
template<class T>
class Bounded_Queue {
public:
    typedef boost::circular_buffer<T> container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::value_type value_type;
    typedef typename boost::call_traits<value_type>::param_type param_type;

    explicit Bounded_Queue(size_type capacity) : m_unread(0), m_container(capacity) {

    }

    void push_front(T &&item) {
        boost::mutex::scoped_lock lock(m_mutex);
        m_not_full.wait(lock, boost::bind(&Bounded_Queue<value_type>::is_not_full, this));
        m_container.push_back(item);
        ++m_unread;
        lock.unlock();
        m_not_empty.notify_one();
    }

    void pop_back(T *pItem) {
        boost::mutex::scoped_lock lock(m_mutex);
        m_not_empty.wait(lock, boost::bind(&Bounded_Queue<value_type>::is_not_empty, this));
        *pItem = m_container.front();
        m_container.pop_front();
        --m_unread;
        lock.unlock();
        m_not_full.notify_one();
    }

private:
    Bounded_Queue(const Bounded_Queue &);    //Disabled copy constructor.
    Bounded_Queue &operator=(const Bounded_Queue &); //Disabled assign operator

    bool is_not_empty() const { return m_unread > 0; }

    bool is_not_full() const { return m_unread < m_container.capacity(); }

    size_type m_unread;
    container_type m_container;
    boost::mutex m_mutex;
    boost::condition m_not_empty;
    boost::condition m_not_full;

};


#endif //LEARN_BOUNDED_QUEUE_H
