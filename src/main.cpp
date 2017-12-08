#include "Base.h"

#include <boost/tokenizer.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

class Tree
{
    public:
        Base *root;
        
        Tree() : root(0) {};
        Tree(Base *pointer) : root(pointer) {};
        
        void destructor(Base *);
};

void Tree::destructor(Base *curr) //will deallocate memory in tree (Base objects)
{
    if(dynamic_cast<Executable *>(curr) == NULL)
    {
        destructor(dynamic_cast<Connector *>(curr)->lhs);
        destructor(dynamic_cast<Connector *>(curr)->rhs);
    }
    delete curr; 
}

void checkForComment(std::string& userCommand) //comment checker
{
    for (unsigned int i = 0; i < userCommand.size(); i++)
    {
        if (userCommand.at(i) == '#')
        {
            userCommand.erase(i); //DELETES ANYTHING AFTER A HASH SYMBOL SINCE IT IS A COMMENT
            break;
        }
    }
}

void createTree(std::stack<Base *>& objects, std::vector<Base *>& postFix) //create tree
{
    Base *pointer;
    while (!postFix.empty())
    {
        if (dynamic_cast<Connector *>(postFix.at(0) ) == NULL) //IF COMMAND SIMPLY PUSH ONTO QUEUE 
        {
            objects.push(postFix.at(0));
            postFix.erase(postFix.begin());
        }
        else //IF CONNECTOR POP TWICE, SET FIRST POPPED VALUE TO CONNECTOR->LHS AND SECOND POPPED VALUE TO CONNECTOR->RHS
        {
            pointer = postFix.at(0);
            postFix.erase(postFix.begin()); 
            
            dynamic_cast<Connector *>(pointer)->rhs = objects.top(); //pop top set connector left to pointer
            objects.pop();
            
            dynamic_cast<Connector *>(pointer)->lhs = objects.top(); //pop top again set connect right to pointer
            objects.pop();
            objects.push(pointer);
        }
    }
}

int main()
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep{" ", ";()<>|"};
    
    while(1)
    {
        Tree *treePointer = new Tree(); //holds tree that will be built
        std::vector<std::string> tokens; //vector that will HOLD our tokens
        std::string userCommand; //input command string from user
        std::string commandLine; //string that we will CONSTRUCT to push in tokens
        
        std::cout << "$ "; //OUTPUT COMMAND PROMPT EVERY TIME
        std::getline(std::cin, userCommand); //get userCommand
        checkForComment(userCommand); //checks for command and erases rest of line if comment
        
        tokenizer tok{userCommand, sep}; //Parse, breaking up by spaces and semicolons 
        
        std::stack<std::string> parenStack; //stack to compute amount of parantheses
        //std::cout << parenStack.size() << std::endl;
        
        try
        {
            //Iterates through the token to find parentheses and checks if there is an imbalance
            for (tokenizer::iterator it = tok.begin(); it != tok.end(); it++) 
            {
                //std::cout << *it << "Checking parentheses" << std::endl;
                if (*it == "(")
                {
                    //std::cout << "Pushing to paren stack" << std::endl;
                    parenStack.push(*it);
                }
                else if (*it == ")")
                {
                    //std::cout << "Closing paren" << std::endl;
                    if (parenStack.empty())
                    {
                        //imbalanced, throw error
                        throw 'd';
                    }
                    else
                    {
                        //std::cout << "Popping" << std::endl;
                        parenStack.pop();
                    }
                }
            }
            if (parenStack.size() != 0)
            {
                //std::cout << "Imbalanced Parentheses" << std::endl;
                throw 'e';
            }
            
            if (userCommand.find("<<") != std::string::npos || userCommand.find("< <") != std::string::npos || userCommand.find("> >") != std::string::npos || userCommand.find("| |") != std::string::npos)
            {
                throw 1; //invalid connector 
            }
           
            bool notCommand = true; //FIXME: Name is confusing with use (the logic is flipped), use another name
            
            for (tokenizer::iterator it = tok.begin(); it != tok.end(); it++ ) //ITERATE THROUGH EVERY TOKEN
            {
                if (*it == "(" || *it == ")" )
                {
                    if (!commandLine.empty() )
                    {
                        tokens.push_back(commandLine);
                        commandLine.clear();
                    }
                    tokens.push_back(*it);
                }
                else if (*it != ";" && *it != "|" && *it != "&&" && *it != "<" && *it != ">") //if not a connector 
                {
                    if (notCommand) //if is command set to false so that we know
                    {
                        notCommand = false;
                        commandLine = *it;
                    }
                    else
                    {
                        commandLine += " " + *it; //append space
                    }
                }
                else
                {
                    if (notCommand) 
                    {
                        throw 1; //invalid connector 
                    }
                    notCommand = true;
                    if (!commandLine.empty())
                    {
                        tokens.push_back(commandLine);
                    }
                    if(*it == ">" || *it == "|")
                    {
                        tokenizer::iterator pipeIter = it; //need new iter to keep old one safe
                        pipeIter++;
                        if (pipeIter != tok.end() )
                        {
                            if (*pipeIter == "|" && *it == "|")
                            {
                                it++;
                                tokens.push_back("||");
                            }
                            else if (*pipeIter == ">" && *it == ">")
                            {
                                it++;
                                tokens.push_back(">>");
                            
                            }
                            else
                            {
                                tokens.push_back(*it);
                            }
                        }
                        else
                        {
                            throw 1; //FIXME change throw value maybe
                        }
                    }
                    else
                    {
                        tokens.push_back(*it);
                    }
                    commandLine.clear();
                }
            } //FOR LOOP
            //PUSHES IN LAST ARG IF NO CONNECTOR AFTER
            if (!commandLine.empty() )
            {
                tokens.push_back(commandLine);
            }
            else if (!tokens.empty() ) //FIXME TO ACCOUNT FOR NEW CONNECTORS
            {
                if (tokens.at(tokens.size() - 1) == ";" || tokens.at(tokens.size() - 1) == "||" || tokens.at(tokens.size() - 1) == "&&" || tokens.at(tokens.size() - 1) == ">" || tokens.at(tokens.size() - 1) == "<" || tokens.at(tokens.size() - 1) == "|" || tokens.at(tokens.size() - 1) == ">>") 
                {
                    throw 1; /// invalid connector
                }
            }
            else
            {
                throw 'e'; //empty command line
            }
            
            //Tester to check tokens
            // for(unsigned int i = 0; i < tokens.size(); i++)
            // {
            //     std::cout << tokens.at(i) << std::endl;
            // }
            //std::vector<std::string> stack;
            
            std::stack<std::string> stack;
            std::vector<Base *> postFix;
            Base *pointer;
            
            for (unsigned int i = 0; i < tokens.size(); i++ )
            {
                //std::cout << "Is token connector" << std::endl;
                //IF TOKEN IS CONNECTOR
                
                //FIXME: If | is found, check to see if next char is also |. If so, connector is OR. Else it is pipe
                if (tokens.at(i) == ";" || tokens.at(i) == "||" || tokens.at(i) == "&&" || tokens.at(i) == "<" || tokens.at(i) == ">" || tokens.at(i) == ">>" || tokens.at(i) == "|")
                {
                    if (!stack.empty() )
                    {
                        if (stack.top() == "||") //FIXME: Might break due to piping
                        {
                            pointer = new Or;
                            postFix.push_back(pointer);
                            stack.pop();
                        }
                        else if (stack.top() == "&&")
                        {
                            pointer = new And;
                            postFix.push_back(pointer);
                            stack.pop();
                        }
                        else if (stack.top() == ";")
                        {
                            pointer = new Semicolon;
                            postFix.push_back(pointer);
                            stack.pop();
                        }
                        else if (stack.top() == "<")
                        {
                            pointer = new InputRedirection;
                            postFix.push_back(pointer);
                            stack.pop();
                        }
                        else if (stack.top() == ">")
                        {
                            pointer = new SingleOutputRed;
                            postFix.push_back(pointer);
                            stack.pop();
                        }
                        else if (stack.top() == ">>")
                        {
                            pointer = new DoubleOutputRed;
                            postFix.push_back(pointer);
                            stack.pop();
                        }
                        else if (stack.top() == "|")
                        {
                            pointer = new Pipe;
                            postFix.push_back(pointer);
                            stack.pop();
                        }
                    }
                    stack.push(tokens.at(i) );
                }
                //ELSE IF OPEN CONNECTOR
                else if (tokens.at(i) == "(" ) 
                {
                    stack.push(tokens.at(i) );
                }
                //ELSE IF CLOSED CONNECTOR
                else if (tokens.at(i) == ")" )
                {
                    //Goes through the stack of operators and converts and pops
                    // until open paren
                    if(stack.empty()) //FIXME: Does this need to be here?
                    {
                        std::cout << "empty stack" << std::endl;
                    }
                    while(stack.top() != "(" )
                    {
                        if (stack.top() == "||") //FIXME: This might break due to piping
                        {
                            pointer = new Or;
                            postFix.push_back(pointer);
                        }
                        else if (stack.top() == "&&")
                        {
                            pointer = new And;
                            postFix.push_back(pointer);
                        }
                        else if(stack.top() == ";")
                        {
                            pointer = new Semicolon;
                            postFix.push_back(pointer);
                        }
                        else if(stack.top() == "<")
                        {
                            pointer = new InputRedirection;
                            postFix.push_back(pointer);
                        }
                        else if(stack.top() == ">")
                        {
                            pointer = new SingleOutputRed;
                            postFix.push_back(pointer);
                        }
                        else if(stack.top() == ">>")
                        {
                            pointer = new DoubleOutputRed;
                            postFix.push_back(pointer);
                        }
                        else if(stack.top() == "|")
                        {
                            pointer = new Pipe; 
                            postFix.push_back(pointer);
                        }
                        stack.pop();
                    }
                    stack.pop(); //pops open paren on stack
                }
                 //ELSE IT IS A COMMAND AND ITS ARGUMENTS, 
                else 
                //NEED TO BREAK UP THE COMMAND AND ITS ARGUMENTS INTO TWO SEPARATE STRINGS IN ORDER TO CREATE OBJECT
                {
                    //if is "test" need to break up the next string check for 
                    // '-' for flag, if no '-' the next string should be filepath string 
                    if (tokens.at(i).find(" ") != std::string::npos)
                    {
                        std::string commandString = tokens.at(i).substr(0, tokens.at(i).find(" ") );
                        std::string parameters = tokens.at(i).substr(tokens.at(i).find(" ") + 1);
                        
                        if (commandString == "exit")
                        {
                            pointer = new Exit;
                        }
                        else if (commandString == "test" || commandString == "[")  //CREATE TEST OBJECT WITH PARAMETERS
                        {
                            pointer = new Test(parameters);
                        }
                        else
                        {
                            pointer = new Command(commandString, parameters);
                        }
                        postFix.push_back(pointer);
                    }
                    else
                    {
                        if(tokens.at(i) == "exit")
                        {
                            pointer = new Exit;
                        }
                        else
                        {
                            pointer = new Command(tokens.at(i), "");
                        }
                        postFix.push_back(pointer);
                    }
                }
            }
            if (!stack.empty()) 
            {
                if (stack.top() == ";")
                {
                    pointer = new Semicolon;
                }
                else if (stack.top() == "||") //FIXME: This might break due to piping
                {
                    pointer = new Or;
                }
                else if (stack.top() == "&&")
                {
                    pointer = new And;
                }
                else if (stack.top() == "<")
                {
                    pointer = new InputRedirection;
                }
                else if (stack.top() == ">")
                {
                    pointer = new SingleOutputRed;
                }
                else if (stack.top() == ">>")
                {
                    pointer = new DoubleOutputRed;
                }
                else if (stack.top() == "|")
                {
                    pointer = new Pipe;
                }
                
                postFix.push_back(pointer);
            }
            
            std::stack<Base *> objects;
            // CREATE AND EXECUTE TREE, CURRENTLY DEALLOCATES MEMORY RIGHT AFTER EXECUTING THE TREE
            createTree(objects, postFix); 
            
            if (objects.empty()) //Prevents empty root from being made
            {
                throw 'e';
            }
            
            treePointer->root = objects.top();
            treePointer->root->execute(); //execute from root
            treePointer->destructor(treePointer->root); //deallocate memory
            delete treePointer; //delete container
            } // END TRY BLOCK
            
            //CATCH BLOCK FOR INVALID CONNECTOR INPUT
            catch (int formatError)
            {
                std::cout << "Invalid Connectors" << std::endl; //TESTING ONLY, WILL SIMPLY PROMPT FOR INPUT AGAIN IF THIS HAPPENS
            }
            
            //CATCH BLOCK FOR INVALID PARENTHESES
            catch (char emptyError) 
            {
                if(emptyError == 'e')
                {
                    std::cout << "Invalid Input: Imbalanced Parantheses or Empty Input" << std::endl; 
                }
            }
            
            //CATCH BLOCK FOR EXITTING LOOP AND DEALLOCATING MEMORY
            catch (bool error)
            {
                treePointer->destructor(treePointer->root);
                delete treePointer;
                
                exit(0);
            }
    }
    
    return 0;
}