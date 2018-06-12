# cplusplus-without-brace
A program that **convert C++ codes which without brace to standard C++ codes**.

<h2>Complie</h2>

No third-part library used, directly use C++ complier to complie.

<h2>Usage</h2>

./cwb2sc your_file.cwb

<h2>Output</h2>

your_file.cpp

<h2>Explanation</h2>

The cwb file is actually just txt format file.

I define cwb file which contains C++ codes without brace, and the codes look like this:

	while (pscF.getline(lastLine, 5000))
		for (i = 0; i < strlen(lastLine); i++)
			if (line[i] != ' ' && line[i] != '\t') break;
		if (i == strlen(lastLine))
			continue;
		else
			lastLineSpaceNum = i;
			break;

As you can see, this type of codes cannot be complied by compiler, so can use this program to convert these codes to standard C++ codes:

	while (pscF.getline(lastLine, 5000)){
		for (i = 0; i < strlen(lastLine); i++){
			if (line[i] != ' ' && line[i] != '\t') break;}
		if (i == strlen(lastLine)){
			continue;}
		else{
			lastLineSpaceNum = i;
			break;}}
