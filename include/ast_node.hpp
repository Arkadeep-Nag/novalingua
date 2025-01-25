#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() const = 0;  // Pure virtual function
};

// Class for function nodes
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

// Class for class nodes
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

// Class for variable nodes
class VariableNode : public ASTNode {
public:
    VariableNode(std::string name, std::string value);
    void print() const override;

private:
    std::string name;
    std::string value;
};

// Class for conditional nodes (if-else)
class IfNode : public ASTNode {
public:
    IfNode(std::string condition, std::vector<std::unique_ptr<ASTNode>> trueBranch,
           std::vector<std::unique_ptr<ASTNode>> falseBranch);
    void print() const override;

private:
    std::string condition;
    std::vector<std::unique_ptr<ASTNode>> trueBranch;
    std::vector<std::unique_ptr<ASTNode>> falseBranch;
};

#endif
