#ifndef C37118_HEADER
#define C37118_HEADER

#include "packet_header.hpp"

#define SIZE_C37118_HEADER_BITSTRING 16

class C37118Header : public PacketHeader {
  public:
    /* Required Functions */
    void *get_raw();
    void set_raw(void *raw);
    void print_header(FILE *out);
    uint32_t get_header_len();
    void get_bitstring(std::vector<int8_t> &to_fill, int8_t fill_with);
    void get_bitstring_header(std::vector<std::string> &to_fill);
    
    /* Header Specific */
    void set_info(uint32_t c37118_bytes);

  private:
    uint8_t *raw = NULL;
    uint32_t c37118_bytes = 0;
};

#endif