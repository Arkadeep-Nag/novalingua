#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <variant>
#include <vector>
#include <iostream>

class ClassInstance;

using Value = std::variant<int, std::string, std::shared_ptr<ClassInstance>, std::nullptr_t>;

class ClassInstance {
    std::unordered_map<std::string, Value> fields;

public:
    void setField(const std::string& name, Value value) {
        fields[name] = value;
    }

    Value getField(const std::string& name) {
        if (fields.find(name) != fields.end()) {
            return fields[name];
        }
        throw std::runtime_error("Undefined field: " + name);
    }
};

inline std::ostream& operator<<(std::ostream& os, const Value& value) {
    if (std::holds_alternative<int>(value)) {
        os << std::get<int>(value);
    } else if (std::holds_alternative<std::string>(value)) {
        os << std::get<std::string>(value);
    } else if (std::holds_alternative<std::shared_ptr<ClassInstance>>(value)) {
        os << "Instance of class";
    } else {
        os << "null";
    }
    return os;
}

#endif
