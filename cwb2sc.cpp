#include<fstream>

int main(int argc,char* argv[])
{
	if (argc < 2)
		exit(0);

	int i, j;
	int pureNameStartPoint;
	int dirNameLastPoint;
	for (i=strlen(argv[1]);i>=0;i--)
	{
		if (argv[1][i] == '/' || argv[1][i] == '\\')
		{
			pureNameStartPoint = i + 1;
			i--;
			for(;i>=0;i--)
				if (argv[1][i] != '/' && argv[1][i] != '\\')
				{
					dirNameLastPoint = i;
					goto myStop;
				}
		}
			
	}
	
	myStop:;

	char dir[5000];
	char pureName[1000];

	for (i = 0; i <= dirNameLastPoint; i++)
		dir[i] = argv[1][i];
	dir[i] = '\0';

	for (i = pureNameStartPoint, j = 0; i < strlen(argv[1]); i++, j++)
	{
		if (argv[1][i] == '.')
			break;
		pureName[j] = argv[1][i];
	}
	pureName[j] = '\0';

	std::fstream cwbF(argv[1], std::fstream::in);
	char line[50000],lastLine[50000];
	int lastLineSpaceNum, thisLineSpaceNum;

	//给第一个lastLineSpaceNum和lastLine赋值
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

	//开始读取
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
}
