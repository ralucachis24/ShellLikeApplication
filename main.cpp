#include <iostream>
#include <string>
#include <sstream>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "utils.h"
#include "commands.h"

using namespace std;

int main(int argc, char **argv, char **envp)
{

    while (true)
    {

        char *in = readline(">> ");
        string inString(in);
        add_history(in);

        vector<vector<string>> commands;
        commands = Utils::parseLineCommands(inString);
        if(commands.size()==1) //one com
            for (vector<string> cmd : commands)
            {
                if(cmd[0] == "help")
                    Commands::help();
                else if(cmd[0] == "version")
                    Commands::version();
                else if (cmd[0] == "env")
                    Commands::env(cmd);
                else if (cmd[0]=="cat")
                    Commands::cat(cmd);
                else if(cmd[0] == "head") 
                    Commands::head(cmd);
                else if (cmd[0] == "exit")
                    Commands::exit(getpid());
                else
                    cerr <<cmd[0]<< " command not implemented\n";
        }
        else if (commands.size() > 1) //piping
        {
            int l[105][2];
            for(int i = 0; i < commands.size(); i++)
                pipe(l[i]);

            int pp[2];
            pipe(pp);
            int c = 0;
            while(c < commands.size())
            {
                int counter = 0;
                char **ccmd = (char **)malloc(100*sizeof(char*));
                for(int k = 0; k < commands[c].size(); k++)
                {
                    ccmd[counter] = (char*)commands[c][k].c_str();
                    counter+=1;
                }
                counter+=1;
                ccmd[counter] = NULL;
                if(fork()) c++;
                else
                {
                    if(c+1 != commands.size()) dup2(l[c+1][1], STDOUT_FILENO);
                    else
                        dup2(pp[1], STDOUT_FILENO);
                    if(c) dup2(l[c][0], STDIN_FILENO);
                    for(int i = 0; i < commands.size(); i++)
                    {
                        close(l[i][0]);
                        close(l[i][1]);
                    }
                    execvp(ccmd[0], ccmd);
                }
            }
            for(int i = 0; i < commands.size(); i++)
            {
                close(l[i][0]);
                close(l[i][1]);
            }
            wait(NULL);
            char buff[5000];
            int r = read(pp[0], &buff, 4999);
            buff[r] = '\0';
            cout<<buff<<endl;
        }

        delete in;
    }
    return 0;
}