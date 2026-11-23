#include "c37118_header.hpp"

/* Required Functions */
void *C37118Header::get_raw() {
    return (void *)raw;
}

void C37118Header::set_raw(void *raw) {
    this->raw = (uint8_t *)raw;
}

void C37118Header::print_header(FILE *out) {
    if (raw == NULL) {
        fprintf(out, "C37118Header:: raw data not set\n");
        return;
    } 
    if (c37118_bytes >= 16) {
        fprintf(out, "C37118 header: frame type: %u, version: %u, FRAMESIZE: %u, IDCODE: %u, SOC:  %u, time quality: 0x%02x, fraction of second: %u, STAT/CMD: 0x%04x\n",
        (raw[1] >> 4) & 0x07, raw[1] & 0x0F, ((uint32_t)raw[2] << 8)|raw[3], ((uint32_t)raw[4] << 8)|raw[5], ((uint32_t)raw[6] << 24)|((uint32_t)raw[7] << 16)|((uint32_t)raw[8] << 8)|raw[9], raw[10], ((uint32_t)raw[11] << 16)|((uint32_t)raw[12] << 8)|raw[13], ((uint32_t)raw[14] << 8)|raw[15]);
    } else {
        fprintf(out, "C37118 header: frame type: %u, version: %u, FRAMESIZE: %u, IDCODE: %u, SOC:  %u, time quality: 0x%02x, fraction of second: %u\n",
        (raw[1] >> 4) & 0x07, raw[1] & 0x0F, ((uint32_t)raw[2] << 8)|raw[3], ((uint32_t)raw[4] << 8)|raw[5], ((uint32_t)raw[6] << 24)|((uint32_t)raw[7] << 16)|((uint32_t)raw[8] << 8)|raw[9], raw[10], ((uint32_t)raw[11] << 16)|((uint32_t)raw[12] << 8)|raw[13]);
    }

}

uint32_t C37118Header::get_header_len() {
    if (raw == NULL){
        return 0;
    }
    return ((uint32_t)raw[2] << 8)|raw[3];
}

void C37118Header::get_bitstring(std::vector<int8_t> &to_fill, int8_t fill_with) {
    if (raw == NULL){
        make_bitstring(SIZE_C37118_HEADER_BITSTRING, NULL, to_fill, fill_with);
    } else if (c37118_bytes >= 16){
        make_bitstring(SIZE_C37118_HEADER_BITSTRING, raw, to_fill, fill_with);
    } else{
        make_bitstring(14, raw, to_fill, fill_with);
        make_bitstring(2, NULL, to_fill, fill_with);
    }
}

void C37118Header::get_bitstring_header(std::vector<std::string> &to_fill) {
    std::vector<std::tuple<std::string, uint32_t>> v;
    //application layer protocol

    //SYNC - 2 bytes
    v.push_back(std::make_tuple("c37118_sync", 8));
    v.push_back(std::make_tuple("c37118_reserved", 1));
    v.push_back(std::make_tuple("c37118_frametype", 3));
    v.push_back(std::make_tuple("c37118_version", 4));

    //FRAMESIZE
    v.push_back(std::make_tuple("c37118_framesize", 16));

    //IDCODE
    v.push_back(std::make_tuple("c37118_idcode", 16));

    //SOC
    v.push_back(std::make_tuple("c37118_soc", 32));
    
    //FRACSEC
    v.push_back(std::make_tuple("c37118_timequal", 8));
    v.push_back(std::make_tuple("c37118_fracsec", 24));

    //DATA FRAME BODY STAT
    v.push_back(std::make_tuple("c37118_stat_cmd", 16));

    PacketHeader::make_bitstring_header(v, to_fill);
}

void C37118Header::set_info(uint32_t c37118_bytes) {
    this->c37118_bytes = c37118_bytes;
}
