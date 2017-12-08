#ifndef __BASE_H__
#define __BASE_H__

#include <string>
#include <vector>

class Base //ABSTRACT BASE CLASS
{
    public:
        Base() {};
        virtual ~Base() {};
        virtual bool execute() = 0;
};

/////////////////////////////////////////////////EXECUTABLE AND DERIVED CLASSES

class Executable : public Base 
{
    public:
        Executable() {};
        virtual bool execute() = 0;
};

class Command : public Executable
{
    protected:
        std::string commandString;
        std::string parameters;
    public:
        Command() : commandString(""), parameters("") {};
        Command(std::string element, std::string elements) : commandString(element), parameters(elements) {};
        bool execute();
};

class Test : public Executable
{
    protected:
        std::string flagAndPath;
    public: 
        Test() : flagAndPath("") {};
        Test(std::string userFlagAndPath) : flagAndPath(userFlagAndPath) {};
        bool execute();
};

class Exit : public Executable 
{
    public:
        Exit() {};
        bool execute();
};

//////////////////////////////////////////////////CONNECTOR AND DERIVED CLASSES

class Connector : public Base 
{
    public:
        Base *lhs;
        Base *rhs;
        
        Connector() : lhs(0), rhs(0) {};
        virtual bool execute() = 0;
};

class And : public Connector
{
    public:
        And() {};
        bool execute();
};

class Or : public Connector
{
    public:
        Or() {};
        bool execute();
};

class Semicolon : public Connector
{
    public:
        Semicolon() {};
        bool execute();
};

class InputRedirection : public Connector
{
    public:
        InputRedirection() {};
        bool execute();
};

class SingleOutputRed : public Connector
{
    public:
        SingleOutputRed() {};
        bool execute();
};

class DoubleOutputRed : public Connector
{
    public:
        DoubleOutputRed() {};
        bool execute();
};

class Pipe : public Connector
{
    public:
        Pipe() {};
        bool execute();
};

#endif