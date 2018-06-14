/*
Usage：
./cwb2sc your_c++_code.cwb

Method：
According to spaces and tabs to add braces.
Reading the cwb file line by line:
1. When finding current line has more spaces or tabs than last line,
add a '{' at the end of last line.
2. When finding current line has fewer spaces or tabs than last line,
then find out how many '}' should be added at the end of last line.
*/

#include<fstream>
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("\nPlease attach the cwb file's full name as a command line parameter\n\n\n");
		printf("eg : ./cwb2sc your_file.cwb\n\n\n");
		exit(0);
	}

	std::fstream cwbF(argv[1], std::fstream::in);
	char currentLine[50000], lastLine[50000];
	int currentLineSpaceNum, lastLineSpaceNum;

	//get values of the first lastLineSpaceNum & lastLine variables.
	int i, j;
	while (cwbF.getline(lastLine, 50000))
	{
		for (i = 0; i < strlen(lastLine); i++)
			if (lastLine[i] != ' ' && lastLine[i] != '\t') break;
		if (i == strlen(lastLine))
			continue;
		else
		{
			lastLineSpaceNum = i;
			break;
		}
	}

	//read .cwb file and convert it to standard C++ code into .cpp file line by line.
	int differenceValue;
	int helpArray[5000];
	int helpArrayLen = 0;
	int needBraceNum;

	char cppFileFullName[5000];
	strcpy(cppFileFullName, argv[1]);
	int cppFileFullNameLen = strlen(cppFileFullName);
	cppFileFullName[cppFileFullNameLen - 3] = 'c';
	cppFileFullName[cppFileFullNameLen - 2] = 'p';
	cppFileFullName[cppFileFullNameLen - 1] = 'p';

	FILE* cppF = fopen(cppFileFullName, "w");

	while (cwbF.getline(currentLine, 50000))
	{
		for (i = 0; i < strlen(currentLine); i++)
			if (currentLine[i] != ' ' && currentLine[i] != '\t') break;
		if (i == strlen(currentLine))
			continue;
		else
			currentLineSpaceNum = i;

		differenceValue = currentLineSpaceNum - lastLineSpaceNum;

		if (differenceValue > 0)
		{
			helpArray[helpArrayLen] = differenceValue;
			helpArrayLen += 1;
			lastLine[strlen(lastLine) + 1] = '\0';
			lastLine[strlen(lastLine)] = '{';
		}
		else if (differenceValue < 0)
		{
			for (i = helpArrayLen - 1; i >= 0; i--)
			{
				differenceValue += helpArray[i];
				if (differenceValue == 0)
				{
					needBraceNum = helpArrayLen - i;
					helpArrayLen = i;
					break;
				}
			}
			for (i = 0; i < needBraceNum; i++)
			{
				lastLine[strlen(lastLine) + 1] = '\0';
				lastLine[strlen(lastLine)] = '}';
			}
		}

		fprintf(cppF, "%s\n", lastLine);

		lastLineSpaceNum = currentLineSpaceNum;
		strcpy(lastLine, currentLine);
	}

	for (i = 0; i < helpArrayLen; i++)
	{
		lastLine[strlen(lastLine) + 1] = '\0';
		lastLine[strlen(lastLine)] = '}';
	}
	fprintf(cppF, "%s\n", lastLine);

	fclose(cppF);

	printf("\n\n\nCongratulations! Transform successfully!\n\n\n");
}
