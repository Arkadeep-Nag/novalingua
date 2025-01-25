#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "value.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

class Environment {
    std::unordered_map<std::string, Value> variables;

public:
    void define(const std::string& name, Value value) {
        variables[name] = value;
    }

    Value get(const std::string& name) {
        if (variables.find(name) != variables.end()) {
            return variables[name];
        }
        throw std::runtime_error("Undefined variable: " + name);
    }

    void assign(const std::string& name, Value value) {
        if (variables.find(name) != variables.end()) {
            variables[name] = value;
        } else {
            throw std::runtime_error("Undefined variable: " + name);
        }
    }
};

#endif
