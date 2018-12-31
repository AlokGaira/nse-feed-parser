#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../include/schema/Order_Message.h"

using namespace boost::archive;

std::stringstream ss;

class animal
{
public:
    animal() = default;
    animal(int legs, std::string name) : legs_{legs}, name_{name} {}
    int legs() const { return legs_; }
    std::string name() { return name_; }


private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version) { ar & legs_; ar & name_;}

    int legs_;
    std::string name_;
};

void save()
{
    std::ofstream file{"archive.txt"};
    text_oarchive oa{file};
    std::vector<Order_Message> order_message_arr;
    for (int32_t i = 0; i < 10000000; i++){
        Order_Message order_message = {
                .stream_header = Stream_Header{
                        .message_length = 1,
                        .stream_id = 1,
                        .sequence_number = 1,
                },
                .message_type = 'C',
                .timestamp = 1,
                .order_id = 1.0,
                .token = 1,
                .order_type = 'B',
                .price = 12,
                .quantity = 123
        };

        order_message_arr.push_back(order_message);
    }
    oa & order_message_arr;
}

void load()
{
    std::ifstream file{"archive.txt"};
    text_iarchive ia{file};
    animal a;
    ia >> a;
    std::cout << a.legs() << '\n';
    std::cout << a.name() << '\n';
}

int main()
{
    save();
//    load();
}