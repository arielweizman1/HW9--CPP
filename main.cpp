#include <iostream>
#include "string.h"
#include "ip.h"
#include "port.h"
#include "input.h"

using namespace std;

int main(int argc, char **argv) {
    if (check_args(argc, argv) != 0) {
        return -1;
    }
    String *rule;
    size_t size;
    String(argv[1]).split("=", &rule, &size);
    if (size != 2) {
        if (size != 0) {
            delete[] rule;
        }
        return -1;
    }
    const String &string_rule = rule[0].trim();
    const String &rhs_rule = rule[1].trim();
    if (string_rule.equals("src-ip") || string_rule.equals("dst-ip")) {
        Ip ip(string_rule);
        ip.set_value(rhs_rule);
        parse_input(ip);
        delete[] rule;
        return 0;
    }
    if (string_rule.equals("src-port") || string_rule.equals("dst-port")){
        Port port(string_rule);
        port.set_value(rhs_rule);
        parse_input(port);
        delete[] rule;
        return 0;
    }
    delete[] rule;
    return 0;
}
