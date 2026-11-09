#include "iec104_header.hpp"

/*WORK IN PROGRESS -SOFIA */

/* Required Functions */
void *IEC104Header::get_raw() {
    return (void *)raw;
}

void IEC104Header::set_raw(void *raw) {
    this->raw = (struct iec104 *)raw;
}

void IEC104Header::print_header(FILE *out) {
    if (raw == NULL) {
        fprintf(out, "IEC104Header:: raw data not set\n");
    } 

    fprintf(out, "IEC104 header: srcprt: %u, dstprt: %u, len: %u, cksum: %u\n",
           ntohs(raw->uh_sport), ntohs(raw->uh_dport), ntohs(raw->uh_ulen),
           ntohs(raw->uh_sum));
}

uint32_t IEC104Header::get_header_len() {
    return 8;
}

void IEC104Header::get_bitstring(std::vector<int8_t> &to_fill, int8_t fill_with) {
    make_bitstring(SIZE_IEC104_HEADER_BITSTRING, raw, to_fill, fill_with);
}

void IEC104Header::get_bitstring_header(std::vector<std::string> &to_fill) {
    std::vector<std::tuple<std::string, uint32_t>> v;
    v.push_back(std::make_tuple("iec104_sport", 16));
    v.push_back(std::make_tuple("iec104_dport", 16));
    v.push_back(std::make_tuple("iec104_len", 16));
    v.push_back(std::make_tuple("iec104_cksum", 16));

    PacketHeader::make_bitstring_header(v, to_fill);
}

std::string IEC104Header::get_port(bool src) {
    if (raw == NULL) {
        return "NULL";
    } else if (src) {
        return std::to_string(ntohs(raw->uh_sport));
    } else {
        return std::to_string(ntohs(raw->uh_dport));
    }
}
