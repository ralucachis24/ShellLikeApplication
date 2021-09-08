# ShellLikeApplication

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

