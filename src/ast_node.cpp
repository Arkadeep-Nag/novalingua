#include "ast_node.hpp"

// FunctionNode implementation
FunctionNode::FunctionNode(std::string name, std::vector<std::string> params)
    : name(std::move(name)), params(std::move(params)) {}

void FunctionNode::addBodyNode(std::unique_ptr<ASTNode> node) {
    body.push_back(std::move(node));
}

void FunctionNode::print() const {
    std::cout << "Function: " << name << "(";
    for (size_t i = 0; i < params.size(); ++i) {
        std::cout << params[i];
        if (i < params.size() - 1) std::cout << ", ";
    }
    std::cout << ")\n";
    for (const auto& node : body) {
        node->print();
    }
}

const std::string& FunctionNode::getName() const { return name; }
const std::vector<std::string>& FunctionNode::getParams() const { return params; }
const std::vector<std::unique_ptr<ASTNode>>& FunctionNode::getBody() const { return body; }

// ClassNode implementation
ClassNode::ClassNode(std::string name, std::string parentClass)
    : name(std::move(name)), parentClass(std::move(parentClass)) {}

void ClassNode::addMember(std::unique_ptr<ASTNode> member) {
    members.push_back(std::move(member));
}

void ClassNode::print() const {
    std::cout << "Class: " << name;
    if (!parentClass.empty()) {
        std::cout << " extends " << parentClass;
    }
    std::cout << "\n";
    for (const auto& member : members) {
        member->print();
    }
}

const std::string& ClassNode::getName() const { return name; }
const std::string& ClassNode::getParentClass() const { return parentClass; }
const std::vector<std::unique_ptr<ASTNode>>& ClassNode::getMembers() const { return members; }

// VariableNode implementation
VariableNode::VariableNode(std::string name, std::string value)
    : name(std::move(name)), value(std::move(value)) {}

void VariableNode::print() const {
    std::cout << "Variable: " << name << " = " << value << "\n";
}

const std::string& VariableNode::getName() const { return name; }
const std::string& VariableNode::getValue() const { return value; }
