#include "ip.h"

Ip::Ip(String pattern) : Field(pattern, IP) {

}

bool Ip::set_value(String val) {
    String *ip_rule;
    size_t size = 0;
    val.split("/", &ip_rule, &size);
    if (size != MASK_SEGMENT) {
        if (size != 0) {
            delete[] ip_rule;
        }
        return false;
    }
    int number = ip_rule[1].to_integer();
    if (number < 0 || number > 32) {
        return false;
    }
    int number_of_dont_cares = 32 - number;
    String *classes;
    ip_rule[0].split(".", &classes, &size);
    if (size != SEGMENTS) {
        if (size != 0) {
            delete[] classes;
            delete[] ip_rule;
        }
        return false;
    }
    unsigned int ip = classes[0].to_integer() << 24 | 
                      classes[1].to_integer() << 16 | 
                      classes[2].to_integer() << 8 |
                      classes[3].to_integer();
    delete[] classes;
    delete[] ip_rule;
    unsigned int mask = ((unsigned int) 1 << number_of_dont_cares) - 1;
    if (number_of_dont_cares == 32) {
        mask = 0xFFFFFFFF;
    }

    low = ip & (~mask);
    high = ip | mask;
    return true;
}

bool Ip::match_value(String val) const {
    String *classes;
    size_t size;
    val.split(".", &classes, &size);
    if (size != 4) {
        if (size != 0) {
            delete[] classes;
        }
        return false;
    }
    unsigned int ip = classes[0].to_integer() << 24 | 
                      classes[1].to_integer() << 16 | 
                      classes[2].to_integer() << 8 |
                      classes[3].to_integer();
    delete[] classes;
    return ip <= high && ip >= low;
}
