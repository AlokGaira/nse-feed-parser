//
// Created by alok on 27/11/18.
//

#include <iostream>
#include <boost/timer/timer.hpp>
#include <boost/thread/thread.hpp>

#include "../include/ds/Bounded_Queue.h"
const unsigned long queue_size     = 1000000L;
const unsigned long total_elements = queue_size * 100L;

//[circular_buffer_bound_example_2]
/*`To demonstrate, create two classes to exercise the buffer.

The producer class fills the buffer with elements.

The consumer class consumes the buffer contents.

*/

template<class Buffer>
class Producer
{

    typedef typename Buffer::value_type value_type;
    Buffer* m_container;

public:
    Producer(Buffer* buffer) : m_container(buffer)
    {}

    void operator()()
    {
        for (unsigned long i = 0L; i < total_elements; ++i)
        {
            m_container->push_front(value_type());
        }
    }
};

template<class Buffer>
class Consumer
{

    typedef typename Buffer::value_type value_type;
    Buffer* m_container;
    value_type m_item;

public:
    Consumer(Buffer* buffer) : m_container(buffer)
    {}

    void operator()()
    {
        for (unsigned long i = 0L; i < total_elements; ++i)
        {
            m_container->pop_back(&m_item);
        }
    }
};

/*`Create a first-int first-out test of the bound_buffer.
Include a call to boost::progress_timer

[@http://www.boost.org/doc/libs/1_53_0/libs/timer/doc/cpu_timers.html CPU timer]

*/
template<class Buffer>
void fifo_test(Buffer* buffer)
{
    // Start of timing.
    boost::timer::auto_cpu_timer progress;

    // Initialize the buffer with some values before launching producer and consumer threads.
    for (unsigned long i = queue_size / 2L; i > 0; --i)
    {
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x581))
        buffer->push_front(Buffer::value_type());
#else
        buffer->push_front(BOOST_DEDUCED_TYPENAME Buffer::value_type());
#endif
    }

    // Construct the threads.
    Consumer<Buffer> consumer(buffer);
    Producer<Buffer> producer(buffer);

    // Start the threads.
    boost::thread consume(consumer);
    boost::thread produce(producer);

    // Wait for completion.
    consume.join();
    produce.join();

    // End of timing.
    // destructor of boost::timer::auto_cpu_timer will output the time to std::cout.

}
//] [/circular_buffer_bound_example_2]
int main()
{
//[circular_buffer_bound_example_3]
    //`Construct a bounded_buffer to hold the chosen type, here int.
    Bounded_Queue<int> bb_int(queue_size);
    std::cout << "Testing bounded_buffer<int> ";

    //`Start the fifo test.
    fifo_test(&bb_int);
    //` destructor of boost::timer::auto_cpu_timer will output the time to std::cout

//] [/circular_buffer_bound_example_3]

    return 0;
}