#ifndef __BASE_H__
#define __BASE_H__

#include <string>
#include <vector>

class Base //ABSTRACT BASE CLASS
{
    public:
        Base() {};
        virtual ~Base() {};
        virtual bool execute(int, int) = 0;
        virtual std::string getCommand() = 0;
};

/////////////////////////////////////////////////EXECUTABLE AND DERIVED CLASSES

class Executable : public Base 
{
    public:
        Executable() {};
        virtual bool execute(int, int) = 0;
        virtual std::string getCommand() = 0;
};

class Command : public Executable
{
    protected:
        std::string commandString;
        std::string parameters;
    public:
        Command() : commandString(""), parameters("") {};
        Command(std::string element, std::string elements) : commandString(element), parameters(elements) {};
        bool execute(int, int);
        std::string getCommand();
};

class Test : public Executable
{
    protected:
        std::string flagAndPath;
    public: 
        Test() : flagAndPath("") {};
        Test(std::string userFlagAndPath) : flagAndPath(userFlagAndPath) {};
        bool execute(int, int);
        std::string getCommand();
};

class Exit : public Executable 
{
    public:
        Exit() {};
        bool execute(int, int);
        std::string getCommand();
};

//////////////////////////////////////////////////CONNECTOR AND DERIVED CLASSES

class Connector : public Base 
{
    public:
        Base *lhs;
        Base *rhs;
        
        Connector() : lhs(0), rhs(0) {};
        virtual bool execute(int, int) = 0;
        virtual std::string getCommand() = 0;
};

class And : public Connector
{
    public:
        And() {};
        bool execute(int, int);
        std::string getCommand() {return "";};
};

class Or : public Connector
{
    public:
        Or() {};
        bool execute(int, int);
        std::string getCommand() {return "";};
};

class Semicolon : public Connector
{
    public:
        Semicolon() {};
        bool execute(int, int);
        std::string getCommand() {return "";};
};

class InputRedirection : public Connector
{
    public:
        InputRedirection() {};
        bool execute(int, int);
        std::string getCommand() {return "";};
};

class SingleOutputRed : public Connector
{
    public:
        SingleOutputRed() {};
        bool execute(int, int);
        std::string getCommand() {return "";};
};

class DoubleOutputRed : public Connector
{
    public:
        DoubleOutputRed() {};
        bool execute(int, int);
        std::string getCommand() {return "";};
};

class Pipe : public Connector
{
    public:
        Pipe() {};
        bool execute(int, int);
        std::string getCommand() {return "";};
};

#endif