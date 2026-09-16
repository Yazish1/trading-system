#ifndef ORDER_H
#define ORDER_H
#include <stdint.h>
enum Side
{
    side_buy,
    side_sell
};

enum OrderType
{
    order_limit,
    order_market
};
struct Order
{
    uint64_t id;
    enum Side side;
    enum OrderType type;
    double price;
    uint32_t quantity;
    uint64_t timestamp;
};

struct Trade
{
    uint64_t buyOrderId;
    uint64_t sellOrderId;
    double price;
    uint32_t quantity;
    uint64_t timestamp;
};

#endif