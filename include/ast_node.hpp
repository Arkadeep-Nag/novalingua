#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Base class for all AST nodes
class ASTNode {
public:
    virtual void print() const = 0;
    virtual ~ASTNode() = default;
};

// Represents a function node
class FunctionNode : public ASTNode {
    std::string name;
    std::vector<std::string> params;
    std::vector<std::unique_ptr<ASTNode>> body;

public:
    FunctionNode(std::string name, std::vector<std::string> params);
    void addBodyNode(std::unique_ptr<ASTNode> node);
    void print() const override;

    const std::string& getName() const;
    const std::vector<std::string>& getParams() const;
    const std::vector<std::unique_ptr<ASTNode>>& getBody() const;
};

// Represents a class node
class ClassNode : public ASTNode {
    std::string name;
    std::string parentClass;
    std::vector<std::unique_ptr<ASTNode>> members;

public:
    ClassNode(std::string name, std::string parentClass = "");
    void addMember(std::unique_ptr<ASTNode> member);
    void print() const override;

    const std::string& getName() const;
    const std::string& getParentClass() const;
    const std::vector<std::unique_ptr<ASTNode>>& getMembers() const;
};

// Represents a variable node
class VariableNode : public ASTNode {
    std::string name;
    std::string value;

public:
    VariableNode(std::string name, std::string value);
    void print() const override;

    const std::string& getName() const;
    const std::string& getValue() const;
};

#endif // AST_NODE_HPP
