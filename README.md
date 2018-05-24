# python-style-cplusplus
A program convert python style c++ codes to standard c++ codes

Usage: 

./psc2sc your_psc_file.psc

Output:

your_psc_file.cpp

Explain:

I define my psc file (Python Style C++ code file) looking like this:

	while (pscF.getline(lastLine, 5000))
		for (i = 0; i < strlen(lastLine); i++)
			if (line[i] != ' ' && line[i] != '\t') break;
		if (i == strlen(lastLine))
			continue;
		else
			lastLineSpaceNum = i;
			break;
      
As you can see, the psc file cannot be complied by compiler, so can use this program to convert psc file to standard C++ code:

	while (pscF.getline(lastLine, 5000)){
		for (i = 0; i < strlen(lastLine); i++){
			if (line[i] != ' ' && line[i] != '\t') break;}
		if (i == strlen(lastLine)){
			continue;}
		else{
			lastLineSpaceNum = i;
			break;}}

And now only accomplished adding brace function. This means you can write this type of C++ code(without brace),and use this program to convert your code to standard C++ code.
