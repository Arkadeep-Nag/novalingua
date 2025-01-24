// ast_node.hpp
#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() const = 0;  // Pure virtual function
};

class FunctionNode : public ASTNode {
public:
    FunctionNode(std::string name, std::vector<std::string> params);
    void addBodyNode(std::unique_ptr<ASTNode> node);
    void print() const override;

private:
    std::string name;
    std::vector<std::string> params;
    std::vector<std::unique_ptr<ASTNode>> body;
};

class ClassNode : public ASTNode {
public:
    ClassNode(std::string name, std::string parentClass = "");
    void addMember(std::unique_ptr<ASTNode> member);
    void print() const override;

private:
    std::string name;
    std::string parentClass;
    std::vector<std::unique_ptr<ASTNode>> members;
};

class VariableNode : public ASTNode {
public:
    VariableNode(std::string name, std::string value);
    void print() const override;

private:
    std::string name;
    std::string value;
};

#endif
