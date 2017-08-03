struct ipHeader {
    int version;
    int ihl;
    int dscp;
    int ecn;
    unsigned short length;
    unsigned short identification;
    int flags;
    int fragment_offset;
    int time_to_live;
    int protocol;
    unsigned short header_checksum;
    unsigned char source_ip[4];
    unsigned char destination_ip[4];
};

// Parses byte buffer into given IP header struct
void parseIp(struct ipHeader *ip, const void *buffer);

// Print the contents of the IP header
void printIp(const struct ipHeader *ip);

// Dumps the contents of the byte buffer as hexadecimal numbers
void hexdump(const void *buffer, unsigned int length);
