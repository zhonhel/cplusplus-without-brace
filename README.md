# cplusplus-without-brace
A program convert c++ codes which without brace to standard c++ codes

<h1>Complie</h1>

No third-part library used, directly use C++ complier to complie.

<h1>Usage</h1>

./cwb2sc your_file.cwb

<h1>Output</h1>

your_file.cpp

<h1>Explain</h1>

The cwb file is actually just txt format file.

I define cwb file which contains C++ codes without brace, and the codes looks like this:

	while (pscF.getline(lastLine, 5000))
		for (i = 0; i < strlen(lastLine); i++)
			if (line[i] != ' ' && line[i] != '\t') break;
		if (i == strlen(lastLine))
			continue;
		else
			lastLineSpaceNum = i;
			break;

As you can see, this type of code cannot be complied by compiler, so can use this program to convert these codes to standard C++ codes:

	while (pscF.getline(lastLine, 5000)){
		for (i = 0; i < strlen(lastLine); i++){
			if (line[i] != ' ' && line[i] != '\t') break;}
		if (i == strlen(lastLine)){
			continue;}
		else{
			lastLineSpaceNum = i;
			break;}}
