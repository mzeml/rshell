#include "Base.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>

/*

Symbol >

    Takes result of process and outputs it to the file stated
    If no file exists, create one
    Overwrite any values in the target file before writing to it

Symbol >>
    Takes result of process and outputs it to the file stated
    If no file exists, create one
    Append the result to exisitng file (so push_back essentially)

Symbol |
    Takes result of process and uses it at a input into stated program




bool Command::execute() //execute(string cmdStr, string argStr)
{
    std::string argStr = parameters;
    std::string cmdStr = commandString;
    
    typedef std::vector<std::string> Tokens;
    Tokens token;
    boost::split(token, argStr, boost::is_any_of(" "));

    char* args[1500];
    args[0] = const_cast<char*>(cmdStr.c_str());
    
    if (argStr.empty() || argStr == " ") //case for ls or empty args
    {
        args[1] = nullptr;
    }
    else if (cmdStr == "echo") //if echo, don't split string
    {
        args[1] = const_cast<char*>(argStr.c_str());
        args[2] = nullptr;
    }
    else //split string
    {
        unsigned y = 1;
        for (y = 1; y < token.size() + 1; y++)
        {
            args[y] = const_cast<char*>(token.at(y - 1).c_str());
        }
        args[++y] = nullptr;
    }
   
    int status;
    
    pid_t child_id;
    
    //Begin execution process
    
    child_id = fork(); //assigns id to child
    
    if (child_id < 0) //Forks child and checks for error
    {
        perror("+++++ERROR: Forking failed!+++++\n");
        return false;
    }
    
    else if (child_id == 0) //This is the child process
    {
        if (execvp(args[0], args) < 0) //Actual exection
        {
            perror("-----ERROR: Execution failed!----- \n");
            exit(1);  //******************************************
            //return false; 
        }
    }
    
    else //this is the parent process
    {
        if (waitpid(child_id, &status, 0) == -1)
        {
            perror("*****ERROR: Wait failed!*****\n");
            return false;
        }
        if (WEXITSTATUS(status) != 0)
        {
            return false;
        }
    }
    return true;
}
bool Test::execute() //Handles test command and brackets
{
    std::string flag;
    std::string filePath;
    bool returnBool = false; 
    
    //std::cout << "TESTING, OUTPUTTING FLAGANDSTRING " << flagAndPath << std::endl;
    
    if(flagAndPath.at(0) == '-') //CHECK FOR FLAGS, then check for what type of flag
    {
        //is flag, determine what flag
        if(flagAndPath.at(1) == 'e')
        {
            flag = "e";
        }
        else if(flagAndPath.at(1) == 'f')
        {
            flag = "f";
        }
        else if(flagAndPath.at(1) == 'd')
        {
            flag = "d";
        }
        else //user input wrong flag
        {
            std::cout << "FLAG NOT RECOGNIZED" <<std::endl;
            return false;
        }
 
        if (flagAndPath.at(flagAndPath.length() - 1) == ']')
        {
            //needs to be 5, second parameter tells how long the substring will be, not ending index
            filePath = flagAndPath.substr(3, (flagAndPath.length() - 5));
        }
        else 
        {
            filePath = flagAndPath.substr(3, (flagAndPath.length() - 1));
        }
    }
    else //no flag
    {
        if (flagAndPath.at(flagAndPath.length() - 1) == ']')
        {
            //takes string as arg
            filePath = flagAndPath.substr(0, (flagAndPath.length() - 2));
            //std::cout << "No flag, found second bracket" << std::endl;
        }
        else 
        {
            filePath = flagAndPath; //also convulted
        }
        //std::cout << "TEST: No flag" << std::endl; //TEST!!!!!
    }
    
    //std::cout << "Filepath: " << filePath << "!!" << std::endl;

    //Check if file exists
    struct stat buf;
    int testResult = (stat(filePath.c_str(), &buf)); //If true, it returns 0
    
    //std::cout << "TEST IF FILE EXISTS: " << testResult << std::endl;
    
    if (flag == "e" || flag.empty()) //e flag handler. Also runs if no flag
    {
        //std::cout << "-e OR no flag" << std::endl;
        if (testResult == 0)
        {
            std::cout << "(TRUE)" << std::endl;
            returnBool = true;
        }
        else
        {
            std::cout << "(FALSE)" << std::endl;
            returnBool = false;
        }
    }
    else if (flag == "f") //f flag handler
    {
        //Do IS_REG
         //std::cout << "f flag" << S_ISREG(buf.st_mode) << std::endl;
        if (testResult == 0)
        {
            if (S_ISREG(buf.st_mode))
            {
                std::cout << "(TRUE)" << std::endl;
                returnBool = true;
            }
            else
            {
                std::cout << "(FALSE)" << std::endl;
                returnBool = false;
            }
        }
        else
        {
            std::cout << "(FALSE)" << std::endl;
            returnBool = false;
        }
    }
    else if (flag == "d")
    {
        if (testResult == 0)
        {
            //std::cout << "d flag" << S_ISDIR(buf.st_mode) << std::endl;
            if (S_ISDIR(buf.st_mode))
            {
                std::cout << "(TRUE)" << std::endl;
                returnBool = true;
            }
            else
            {
                std::cout << "(FALSE)" << std::endl;
                returnBool = false;
            }
        }
        else
        {
            std::cout << "(FALSE)" << std::endl;
            returnBool = false;
        }
    }
    return returnBool;
}
bool Exit::execute() 
{
    throw false;
}
bool And::execute()
{
    if (lhs->execute()) //left returns true
    {
        if(rhs->execute()) //right successful true
        {
            return true;
        }
        else //right child didn't execute successfully
        {
            return false;  
        }
    }
    else //left child didn't execute successfully so don't execute right child
    {
        return false; 
    }
}
bool Or::execute() 
{
    if (lhs->execute()) //left successful, don't execute right
    {
        return true;
    }
    else 
    {
        if (rhs->execute()) //right successful 
        {
            return true;
        }
        else //both unsuccessful 
        {
            return false; 
        }
    }
}
bool Semicolon::execute()
{
    lhs->execute(); //execute left child first
    if (rhs->execute()) //right hand child's success determines the bool value that execute returns
    {
        return true; 
    }
    else //unsuccessful
    {
        return false; 
    }
}