/*
ʹ�÷�����
./cwb2sc your_file.cwb

˼·��
���ÿո��tab�Ӵ�����
1�������ֵ�ǰ�б���һ�пո��tab���࣬����һ��ĩβ��һ�� ��{��
2�������ֵ�ǰ�б���һ�пո��tab����n��������һ��ĩβ��n�� ��}��
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

	//����һ��lastLineSpaceNum��lastLine��ֵ
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

	//���ж�ȡcwb�ļ���������д��cpp�ļ�
	int chazhi;
	int helpArray[5000];
	int helpArrayLen = 0;
	int num;

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