#include<fstream>

void getDirAndPureName(char* dir, char* pureName, char* inFFullName)
{
	int i, j;
	int pureNameStartPoint;
	int dirNameEndPoint;
	for (i = strlen(inFFullName); i >= 0; i--)
	{
		if (inFFullName[i] == '/' || inFFullName[i] == '\\')
		{
			pureNameStartPoint = i + 1;
			i--;
			for (; i >= 0; i--)
				if (inFFullName[i] != '/' && inFFullName[i] != '\\')
				{
					dirNameEndPoint = i;
					goto myStop;
				}
		}
	}

	myStop:;

	for (i = 0; i <= dirNameEndPoint; i++)
		dir[i] = inFFullName[i];
	dir[i] = '\0';

	for (i = pureNameStartPoint, j = 0; i < strlen(inFFullName); i++, j++)
	{
		if (inFFullName[i] == '.')
			break;
		pureName[j] = inFFullName[i];
	}
	pureName[j] = '\0';
}

int main(int argc,char* argv[])
{
	if (argc < 2)
	{
		printf("\nPlease attach the cwb file's full name as a command line parameter\n\n\n");
		printf("eg : ./cwb2sc your_file.cwb\n\n\n");
		exit(0);
	}
		
	char dir[5000];
	char pureName[1000];

	getDirAndPureName(dir, pureName, argv[1]);

	std::fstream cwbF(argv[1], std::fstream::in);
	char line[50000],lastLine[50000];
	int lastLineSpaceNum, thisLineSpaceNum;

	//给第一个lastLineSpaceNum和lastLine赋值
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

	//开始读取与处理
	int chazhi;
	int helpArray[5000];
	int helpArrayLen = 0;
	int num;
	char scFName[6000];
	sprintf(scFName, "%s/%s.cpp", dir, pureName);
	FILE* scF = fopen(scFName, "w");

	while (cwbF.getline(line, 50000))
	{
		for (i = 0; i < strlen(line); i++)
			if (line[i] != ' ' && line[i] != '\t') break;
		if (i == strlen(line))
			continue;
		else
			thisLineSpaceNum = i;
		chazhi = thisLineSpaceNum - lastLineSpaceNum;

		if (chazhi > 0)
		{
			helpArray[helpArrayLen] = chazhi;
			helpArrayLen += 1;
			lastLine[strlen(lastLine) + 1] = '\0';
			lastLine[strlen(lastLine)] = '{';
		}
		else if (chazhi < 0)
		{
			for (i = helpArrayLen-1; i >= 0; i--)
			{
				chazhi += helpArray[i];
				if (chazhi == 0)
				{
					num = helpArrayLen - i;
					helpArrayLen = i;
					break;
				}
			}
			for (i = 0; i < num; i++)
			{
				lastLine[strlen(lastLine) + 1] = '\0';
				lastLine[strlen(lastLine)] = '}';
			}
		}
		
		fprintf(scF, "%s\n", lastLine);

		lastLineSpaceNum = thisLineSpaceNum;
		strcpy(lastLine, line);


	}

	for (i = 0; i <helpArrayLen; i++)
	{
		lastLine[strlen(lastLine) + 1] = '\0';
		lastLine[strlen(lastLine)] = '}';
	}
	fprintf(scF, "%s\n", lastLine);

	fclose(scF);

	printf("\n\n\nCongratulations! Transform successfully!\n\n\n");
}
