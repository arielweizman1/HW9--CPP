#include "string.h"
#include <cstring>

String::String() {
    data = new char[1];
    data[0] = '\0';
    length = 0;
}

String::String(const String &str) {
    this->length = str.length;
    data = new char[this->length + 1];
    strcpy(data, str.data);
}

String::String(const char *str) {
    length = strlen(str);
    data = new char[this->length + 1];
    strcpy(data, str);
}

String::~String() {
    delete[] data;
}

String &String::operator=(const String &rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] this->data;
    this->length = rhs.length;
    data = new char[this->length + 1];
    strcpy(data, rhs.data);
    return *this;
}

String &String::operator=(const char *str) {
    delete[] this->data;
    this->length = strlen(str);
    data = new char[this->length + 1];
    strcpy(data, str);
    return *this;
}

bool String::equals(const String &rhs) const {
    if (this->length != rhs.length) {
        return false;
    }
    for (size_t i = 0; i < this->length; ++i) {
        if (this->data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool String::equals(const char *rhs) const {
    char *p = this->data;
    while (*p && *rhs) {
        if (*p != *rhs) {
            return false;
        }
        rhs++;
        p++;
    }
    if (*p != '\0' || *rhs != '\0') {
        return false;
    }
    return true;
}

void 
String::split(const char *delimiters, String **output, size_t *size) const {
    int number_of_strings = 0;
    char *temp_data = new char[this->length + 1];
    strcpy(temp_data, data);
    for (char *p = strtok(temp_data, delimiters); 
        p != NULL; p = strtok(NULL, delimiters)) {
        number_of_strings++;
    }
    if (output == NULL) {
        delete[] temp_data;
        *size = number_of_strings;
        return;
    }
    strcpy(temp_data, data);
    String *strings = new String[number_of_strings];

    char *p = strtok(temp_data, delimiters);
    for (int i = 0; i < number_of_strings; i++) {
        strings[i] = p;
        p = strtok(NULL, delimiters);
    }
    *output = strings;
    *size = number_of_strings;
    delete[] temp_data;
}

int String::to_integer() const {
    return atoi(data);
}

String String::trim() const {
    int trimmed_string_length = 0;
    char *p = this->data;
    while (*p == ' ') {
        p++;
    }
    char *start = p;
    while (*p != '\0' && *p != ' ') {
        trimmed_string_length++;
        p++;
    }
    if (trimmed_string_length == 0) {
        return String();
    }

    char* new_data = new char[trimmed_string_length + 1];
    for (int i = 0; i < trimmed_string_length; ++i) {
        new_data[i] = *start;
        start++;
    }
    new_data[trimmed_string_length] = '\0';
    String trimmed_string(new_data);
    delete[] new_data;
    return trimmed_string;
}


