#include "port.h"

Port::Port(String pattern) : Field(pattern, PORT) {

}

bool Port::set_value(String val) {
    String *ports;
    size_t size;
    val.split("-", &ports, &size);
    if (size != 2) {
        if (size > 0) {
            delete[] ports;
        }
        return false;
    }
    int min_range = ports[0].to_integer();
    int max_range = ports[1].to_integer();
    delete[] ports;
    if (min_range < 0 || min_range > 65535 || max_range < 0 || 
        max_range > 65535 || max_range < min_range) {
        return false;
    }
    range[0] = min_range;
    range[1] = max_range;
    return true;
}

bool Port::match_value(String val) const {
    int port = val.to_integer();
    return port >= range[0] && port <= range[1];
}
