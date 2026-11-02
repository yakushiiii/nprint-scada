#include "iec60870_header.hpp"

/*WORK IN PROGRESS -SOFIA */

/* Required Functions */
void *IEC60870::get_raw() {
    return (void *)raw;
}

void IEC60870Header::set_raw(void *raw) {
    this->raw = (struct iec60870 *)raw;
}

void IEC60870Header::print_header(FILE *out) {
    if (raw == NULL) {
        fprintf(out, "IEC60870Header:: raw data not set\n");
    } else {
        fprintf(out, "iec60870: type: %u, code: %u\n", raw->icmp_type, raw->icmp_code);
    }
}

void IEC60870Header::get_bitstring(std::vector<int8_t> &to_fill, int8_t fill_with) {
    if (raw == NULL) {
        make_bitstring(SIZE_IEC60870_HEADER_BITSTRING, NULL, to_fill, fill_with);
        return;
    }
    make_bitstring(SIZE_IEC60870_HEADER_BITSTRING, (void *)raw, to_fill, fill_with);
}

void IEC60870Header::get_bitstring_header(std::vector<std::string> &to_fill) {
    std::vector<std::tuple<std::string, uint32_t>> v;
    v.push_back(std::make_tuple("iec60870_type", 8));
    v.push_back(std::make_tuple("iec60870_code", 8));
    v.push_back(std::make_tuple("iec60870_cksum", 16));
    v.push_back(std::make_tuple("iec60870_roh", 32));

    PacketHeader::make_bitstring_header(v, to_fill);
}
