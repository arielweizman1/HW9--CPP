#include "field.h"
#include <cstring>
#include "ip.h"
#include "port.h"
#include <iostream>

Field::Field(String pattern, field_type type) : pattern(pattern.trim()), 
                                                type(type) {}

Field::Field(String pattern) : Field(pattern, GENERIC) {}

Field::~Field() {}

field_type Field::get_type() const { return type; }

bool Field::set_value(String val) {
    //will never execute
    this->pattern = val;
    return false;
}

bool Field::match_value(String val) const {
    //will never execute
    val = this->pattern;
    return false;
}

bool Field::match(String packet) {
    String *packet_components;
    size_t size;
    packet.split(",", &packet_components, &size);
    for (size_t i = 0; i < size; i++) {
        String *single_component;
        size_t size_component;
        packet_components[i].split("=", &single_component, &size_component);
        if (single_component[0].trim().equals(this->pattern)) {
            const String& value_packet = single_component[1].trim();
            delete[] single_component;
            delete[] packet_components;
            if (type == IP) {
                return ((Ip *) this)->match_value(value_packet);
            } else if (type == PORT) {
                return ((Port *) this)->match_value(value_packet);
            } else {
                return false;
            }
        }
        delete[] single_component;
    }
    delete[] packet_components;
    return false;
}
