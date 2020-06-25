//#include <iostream>
#include "serde.hpp"
#include "lcs.hpp"
#include "move.hpp"
#include "libra_types.hpp"


int main() {
    RawTransaction rawTransaction;
    rawTransaction.sequence_number = 2;
    rawTransaction.max_gas_amount = 1000000;
    rawTransaction.gas_unit_price = 1;
    rawTransaction.gas_currency_code = "LBR";
    rawTransaction.expiration_time = 42;

    auto serializer = LcsSerializer();
    Serializable<RawTransaction>::serialize(rawTransaction, serializer);
    auto output = std::move(serializer).bytes();
    for (uint8_t o: output) {
        printf("%d ", o);
    };
    return 0;
}
