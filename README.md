# ShellLikeApplication
For the Operating Systems course we had to implement a shell-like application which acts like the terminal application that is able to interpret a set of internally-implemented commands in Ubuntu. Upon startup, it should show a command line asking the user to enter a command. Additionally, I needed to add history support, if the user presses the Up or Down arrow key, it should show the previous or next command in the terminal just like the real terminal does and auto-complete them in the terminal. The commands implemented were exit, help, cat, head and env.


Commands
	cat -b, -E, -n, -s
	head -c, -n, -q, -v 
	env -u


###################################
CAT 
	-b : number nonempty lines
	-E : display $ at the end of each line
	-n : number all output lines 
	-s : squeeze-blank, suppress repeated empty output lines 

################################### 
HEAD
	-c (-)K :  print the first K bytes of a file,
                   with leading - print all but the last K bytes 
	-n (-)K : print the first K lines
		   with leading - print all but the last K lines
	-q : never print headers giving file name
	-v : prints with header giving file name 

###################################
ENV 
	-u : remove variable

