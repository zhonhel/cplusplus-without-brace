/*
Usage：
./cwb2sc your_c++_code.cwb

Method：
According to spaces and tabs to add braces.
Reading the cwb file line by line:
1. When finding current line has more spaces or tabs than the previous line, 
   add a '{' at the end of the previous line.
2. When finding current line has fewer spaces or tabs than the previous line,
   then find out how many '}' should be added at the end of the previous line.
*/

#include<fstream>
int main(int argc,char* argv[])
{
	if (argc < 2)
	{
		printf("\nPlease attach the cwb file's full name as a command line parameter\n\n\n");
		printf("eg : ./cwb2sc your_file.cwb\n\n\n");
		exit(0);
	}

	std::fstream cwbF(argv[1], std::fstream::in);
	char line[50000],lastLine[50000];
	int lastLineSpaceNum, thisLineSpaceNum;

	//get values of the first lastLineSpaceNum & lastLine variables.
	int i, j;
	while (cwbF.getline(lastLine, 50000))
	{
		for (i = 0; i < strlen(lastLine); i++)
			if (line[i] != ' ' && line[i] != '\t') break;
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

	char fileFullNameNew[5000];
	strcpy(fileFullNameNew, argv[1]);
	int fileFullNameNewLen = strlen(fileFullNameNew);
	fileFullNameNew[fileFullNameNewLen - 3] = 'c';
	fileFullNameNew[fileFullNameNewLen - 2] = 'p';
	fileFullNameNew[fileFullNameNewLen - 1] = 'p';

	FILE* cppF = fopen(fileFullNameNew, "w");

	while (cwbF.getline(line, 50000))
	{
		for (i = 0; i < strlen(line); i++)
			if (line[i] != ' ' && line[i] != '\t') break;
		if (i == strlen(line))
			continue;
		else
			thisLineSpaceNum = i;
		differenceValue = thisLineSpaceNum - lastLineSpaceNum;

		if (differenceValue > 0)
		{
			helpArray[helpArrayLen] = differenceValue;
			helpArrayLen += 1;
			lastLine[strlen(lastLine) + 1] = '\0';
			lastLine[strlen(lastLine)] = '{';
		}
		else if (differenceValue < 0)
		{
			for (i = helpArrayLen-1; i >= 0; i--)
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

		lastLineSpaceNum = thisLineSpaceNum;
		strcpy(lastLine, line);

	}

	for (i = 0; i <helpArrayLen; i++)
	{
		lastLine[strlen(lastLine) + 1] = '\0';
		lastLine[strlen(lastLine)] = '}';
	}
	fprintf(cppF, "%s\n", lastLine);

	fclose(cppF);

	printf("\n\n\nCongratulations! Transform successfully!\n\n\n");
}
