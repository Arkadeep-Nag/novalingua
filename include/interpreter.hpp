#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast_node.hpp"
#include "environment.hpp"
#include <memory>
#include <unordered_map>
#include <functional>

struct ClassDefinition {
    std::string name;
    std::string parentClass;
    std::unordered_map<std::string, std::function<Value(ClassInstance&)>> methods;

    Value callMethod(const std::string& methodName, ClassInstance& instance) {
        if (methods.find(methodName) != methods.end()) {
            return methods[methodName](instance);
        }
        throw std::runtime_error("Undefined method: " + methodName);
    }
};

class Interpreter {
    Environment globalEnv;
    std::unordered_map<std::string, ClassDefinition> classDefinitions;

public:
    void interpret(const ASTNode& ast) {
        execute(ast);
    }

private:
    Value execute(const ASTNode& node) {
        if (auto* func = dynamic_cast<const FunctionNode*>(&node)) {
            return executeFunction(*func);
        } else if (auto* cls = dynamic_cast<const ClassNode*>(&node)) {
            return executeClass(*cls);
        } else if (auto* var = dynamic_cast<const VariableNode*>(&node)) {
            return executeVariable(*var);
        }
        throw std::runtime_error("Unknown ASTNode type");
    }

    Value executeFunction(const FunctionNode& func) {
        // Global functions are not tied to classes
        globalEnv.define(func.getName(), nullptr); // Placeholder for a function
        std::cout << "Defined function: " << func.getName() << "\n";
        return nullptr;
    }

    Value executeClass(const ClassNode& cls) {
        ClassDefinition newClass;
        newClass.name = cls.getName();
        newClass.parentClass = cls.getParentClass();

        // Add methods to the class
        for (const auto& member : cls.getMembers()) {
            if (auto* func = dynamic_cast<const FunctionNode*>(member.get())) {
                newClass.methods[func->getName()] = [func](ClassInstance& instance) -> Value {
                    // Simulate function execution (real execution will require argument passing)
                    std::cout << "Executing method " << func->getName() << " for instance.\n";
                    return nullptr;
                };
            }
        }

        classDefinitions[cls.getName()] = std::move(newClass);
        std::cout << "Defined class: " << cls.getName() << "\n";
        return nullptr;
    }

    Value executeVariable(const VariableNode& var) {
        globalEnv.define(var.getName(), var.getValue());
        std::cout << "Variable: " << var.getName() << " = " << var.getValue() << "\n";
        return var.getValue();
    }
};
#endif
