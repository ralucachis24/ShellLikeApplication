                #ifndef COMMANDS_H
                #define COMMANDS_H
                #define EXEC_ERROR -1

                #include <sys/wait.h>
                #include <string>
                #include <vector>
                #include <unistd.h>
                #include <iostream>
                #include <fstream>
                #include <cstring>

                using namespace std;

                extern char **environ;

                class Commands
                {
                public:
                    /*Print process env variables.Additional arguments are supplied in args*/
                    static void env(vector<string> args)
                    {
                        int argc = args.size();

                        if (argc == 1)
                        {
                            char **var = environ;
                            while (*var != 0)
                            {
                                cout << *var << endl;
                                var++;
                            }
                        }
                        if (argc == 2)
                        {
                            if (args[1] == "-u")
                                cerr << "env: -u optin requires an argument\n";
                            else if (args[1][0] == '-')
                                cerr << "env: unknown option " << args[1] << "\n";
                        }
                        if (argc == 3)
                        {
                            if (args[1] == "-u" && unsetenv(args[2].c_str()) != 0)
                                cerr << "env: couldn't remove env variable\n";
                            else if (args[1][0] == '-' && args[1][1] != 'u')
                                cerr << "env: unknown option " << args[1] << "\n";
                        }
                    }

                    static void cat(vector<string> args)
                    {
                        int argc = args.size();
                        if(argc == 1)
                        {
                            cerr<<"cat: requires an option and an argument\n";
                        }
                        else if (argc == 2)
                        {
                            if(args[1] == "-n")
                                cerr<<"cat: -n option requires an argument\n"; 
                            else if(args[1] == "-b")
                                cerr<<"cat: -b option requires an argument\n"; 
                            else if(args[1] == "-e")
                                cerr<<"cat: -e option requires an argument\n";
                            else if(args[1] == "-E")
                                cerr<<"cat: -E option requires an argument\n";
                            else if(args[1] == "-s")
                                cerr<<"cat: -s option requires an argument\n";
                        }
                        else if (argc==3)
                        {
                            ifstream fin(args[2]); 
                            if(fin.fail())
                                cerr<<"cat: can't open the file "<<endl;
                            else if(args[1] == "-n") 
                            {

                                //cout<<"iful din cat\n";
                                cat_nopt(fin); 
                            }
                            else if(args[1] == "-E" || args[1] == "-e")
                            {
                                cat_Eopt(fin);
                            }
                            else if(args[1] == "-b")
                            {
                                cat_bopt(fin);
                            } 
                            else if(args[1]=="-s")
                            {
                                cat_sopt(fin);
                            }
                            else
                                cerr<<"cat: invalid option";

                        }
                    
                    }

                    static void cat_nopt (ifstream &f)
                    {
                        string str2;
                        int a=1;
                        //cout<<"cat_nopt\n";
                        while(getline(f, str2))
                        {
                        
                        cout<<"     "<<a<<" "<<str2<<endl;
                        ++a;
                        }

                    }

                    static void cat_Eopt (ifstream &f)
                    {
                        string str2;
                        while(getline(f, str2))
                        {
                            cout<<str2<<"$"<<endl;
                        }
                    
                    }

                    static void cat_sopt (ifstream &f)
                    {
                        string str2; 
                        bool flg=false;
                        while(getline(f, str2))
                        {
                        if (!str2.empty()) 
                        {
                            cout<<str2<<endl; 
                            flg=false;
                        }
                        else if(str2.empty() && flg==false)
                        { 
                            cout<<endl;
                            flg=true;
                        }
                    
                        }
                    }

                    static void cat_bopt (ifstream &f)
                    {
                        string str2; 
                        int a=1;
                        while(getline(f, str2))
                        {
                            if (!str2.empty()){
                                cout<<"     "<<a<<" "<<str2<<endl;
                                ++a;
                            }
                            else
                                cout<<str2<<endl;
                        }

                    }
                    
                    static void head(vector<string> args)
                    {
                        int argc = args.size();
                        if(argc == 1)
                        {
                            cerr<<"head: requires an option and an argument\n";
                        }
                        else if (argc == 2)
                        {
                            if(args[1] == "-v")
                                cerr<<"head: -v option requires an argument\n"; 
                            else if(args[1] == "-q")
                                cerr<<"head: -q option requires an argument\n"; 
                            else if(args[1] == "-n")
                                cerr<<"head: -n option requires a number of lines and an argument\n";
                            else if(args[1] == "-c")
                                cerr<<"head: -c option requires a number of bytes and an argument\n";
                        }
                        else if (argc==3)
                        {
                            ifstream fin(args[2]); 
                            if(fin.fail())
                                cerr<<"head: can't open the file "<<endl;
                            else if(args[1] == "-v") 
                            {

                                cout<<"==> "<< args[2]<<" <=="<<endl;
                                head_vopt(fin); 
                            }
                            else if(args[1]=="-q") 
                            {
                                head_qopt(fin);
                            }
                            else
                                cerr<<"head: invalid option";
                        }
                        else if (argc==4)
                        {
                            ifstream fin(args[3]); 
                            if(fin.fail())
                                cerr<<"head: can't open the file "<<endl;
                            if(args[1]=="-n")
                            {
                                if(args[2].find("-") == 0)
                                {
                                    int ii=1; 
                                    int k=0;
                                    while(args[2][ii]){
                                        int aux = args[2][ii]-'0';
                                        k=k*10+aux;
                                        ++ii;
                                    }
                                    k=k%100; 
                                    cout<<k<<endl;
                                    //int k=args[2][1]-'0';
                                    head_noptLast(fin, k); 
                                
                                }
                                else 
                                {
                                    //cout<<"else last"<<endl; 
                                    int ii=0; 
                                    int k=0;
                                    while(args[2][ii]){
                                        int aux = args[2][ii]-'0';
                                        k=k*10+aux;
                                        ++ii;
                                    }
                                    k=k%100;
                                    //int k = args[2][0]-'0';
                                    head_noptFirst(fin, k);
                                }
                                
                            } 
                            else if(args[1]=="-c")
                            {
                            if(args[2].find("-") == 0)
                                {
                                    //int k = args[2][1]-'0';
                                    int ii=1; 
                                    int k=0;
                                    while(args[2][ii]){
                                        int aux = args[2][ii]-'0';
                                        k=k*10+aux;
                                        ++ii;
                                    }
                                    k=k%100; 
                                    cout<<k<<endl;
                                    head_coptLast(fin, k); 
                                
                                }
                                else 
                                {
                                    //int k = args[2][0]-'0';
                                    int ii=0; 
                                    int k=0;
                                    while(args[2][ii]){
                                        int aux = args[2][ii]-'0';
                                        k=k*10+aux;
                                        ++ii;
                                    }
                                    k=k%100; 
                                    cout<<k<<endl;
                                    head_coptFirst(fin, k);
                                }  
                            }
                        }
                    }
                
                static void head_vopt(ifstream &f)
                {
                    string str2; 
                    int a=0;
                    while(getline(f, str2) && a<10)
                    {
                        cout<<str2<<endl;
                        ++a;
                    }
                }


                static void head_qopt(ifstream &f)
                {
                        string str2;
                        int a=0;
                        while(getline(f, str2) && a<10)
                        {
                            cout<<str2<<endl;
                            ++a;
                        }
                }

                static void head_noptFirst(ifstream &f, int k)
                {
                    string str2;
                    int a=0;
                    while(getline(f, str2) && a<k)
                    {
                        cout<<str2<<endl;
                        ++a;

                    }
                }

                static void head_noptLast(ifstream &f, int k)
                {
                
                        string str2;
                        vector<string> lines;
                        //facem vector de linii
                        while(getline(f, str2))
                            lines.push_back(str2);

                        int limit = lines.size()-k+1;
                        for(int i=0; i<limit; ++i)
                        {
                            cout<<lines[i]<<endl;

                        }  
                }

                static void head_coptFirst(ifstream &f, int k)
                {
                    string str2;
                    string str22;
                    while(getline(f, str2))
                        str22+=str2+"\n";
                    //string newStr = str22.substr(0, k);
                    for(int it = 0; it < k; ++it)
                        {
                            cout<<str22[it];
                        } 
                    cout<<endl;
                } 

                static void head_coptLast(ifstream &f, int k)
                {
                    string str2;
                    string str22;
                    while(getline(f, str2))
                        str22+=str2+"\n";
                    int lim = str22.length() - k;
                    for(int it = 0; it < lim; ++it)
                        {
                            cout<<str22[it];
                        } 
                    cout<<endl;
                
                }

                    static void help()
                    {
                        cout << "Help menu\n"
                            <<"Supported commands:\n"
                            <<" - cat\n"
                            <<" - head\n"
                            <<" - env\n"
                            <<" - help\n"
                            <<" - version\n"
                            <<" - exit\n";
                    }

                    static void version()
                    {
                        cout<<"Author: Raluca Chis\n"
                            <<"Static hostname: ralu-VirtualBox\n"
                            <<"Icon name: computer-vm\n"
                            <<"Chassis: vm\n"
                            <<"Machine ID: 50a7e775815d4161a2ead972f92a05d0\n"
                            <<"Boot ID: 3d85266c411240d684f5993851a7e808\n"
                            <<"Virtualization: oracle\n"
                            <<"Operating System: Ubuntu 20.04.1 LTS\n"
                            <<"Kernel: Linux 5.4.0-58-generic\n"
                            <<"Architecture: x86-64\n";
                    }

                    static void exit(int pid)
                    {
                        kill(pid, SIGKILL);
                    }


                private:
                    Commands();
                };

                #endif