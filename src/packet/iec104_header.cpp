#include "iec104_header.hpp"

/*WORK IN PROGRESS -SOFIA */

/* Required Functions */
void *IEC104Header::get_raw() {
    return (void *)raw;
}

void IEC104Header::set_raw(void *raw) {
    this->raw = (uint8_t *)raw;
}

void IEC104Header::print_header(FILE *out) {
    if (raw == NULL) {
        fprintf(out, "IEC104Header:: raw data not set\n");
        return;
    } 

    if (!(raw[2] & 0x01) && iec104_bytes >= 9) {
        fprintf(out, "IEC104 header: length: %u, ctrl1: %u, typeID: %u, COT: %u\n",
        raw[1], raw[2], raw[6], raw[8]);
    } else {
        fprintf(out, "IEC104 header: length: %u, ctrl1: %u\n",
           raw[1], raw[2]);
    }

}

uint32_t IEC104Header::get_header_len() {
    if (raw == NULL){
        return 0;
    }
    return raw[1] + 2; // because the length is explicitly stated in iec104 as the second byte, then add 2 for the inital byte that marks the packet as iec104 and the length byte
}

void IEC104Header::get_bitstring(std::vector<int8_t> &to_fill, int8_t fill_with) {
    if (raw == NULL){
        make_bitstring(SIZE_IEC104_HEADER_BITSTRING, NULL, to_fill, fill_with);
    } else if (!(raw[2] & 0x01) && iec104_bytes >= 15){
        make_bitstring(SIZE_IEC104_HEADER_BITSTRING, raw, to_fill, fill_with);
    } else{
        make_bitstring(6, raw, to_fill, fill_with);
        make_bitstring(9, NULL, to_fill, fill_with);
    }
}

void IEC104Header::get_bitstring_header(std::vector<std::string> &to_fill) {
    std::vector<std::tuple<std::string, uint32_t>> v;
    v.push_back(std::make_tuple("iec104_start", 8));
    v.push_back(std::make_tuple("iec104_length", 8));
    v.push_back(std::make_tuple("iec104_ctrl1", 8));
    v.push_back(std::make_tuple("iec104_ctrl2", 8));
    v.push_back(std::make_tuple("iec104_ctrl3", 8));
    v.push_back(std::make_tuple("iec104_ctrl4", 8));

    //I-frames only
    v.push_back(std::make_tuple("iec104_typeID", 8));
    v.push_back(std::make_tuple("iec104_VSQ", 8));
    v.push_back(std::make_tuple("iec104_COT", 8));
    v.push_back(std::make_tuple("iec104_orig_addr", 8));
    v.push_back(std::make_tuple("iec104_common_addr", 16));
    v.push_back(std::make_tuple("iec104_ioa", 24));

    PacketHeader::make_bitstring_header(v, to_fill);
}

void IEC104Header::set_info(uint32_t iec104_bytes) {
    this->iec104_bytes = iec104_bytes;
}
