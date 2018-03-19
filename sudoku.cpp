#include "stdafx.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<sstream>
#include<time.h>
#include<fstream>
#include<istream>
#include<algorithm>
using namespace std;

struct SDK
{
	int SDK_Array[10][10] = { 0 };
};

int  StringToNum(string String_Num)//直接将字符串转换为数字的函数，很方便。
{
	int n;
	stringstream ss;
	ss.clear();

	ss << String_Num;
	ss >> n;
	return n;
}

bool OrderCheck(int arr, string check1, string check2)//对于输入的cmd指令格式进行检查
{
	if (arr == 3)
	{
		if (check1 == "-c")
		{
			for (int i = 0; i < check2.size(); i++)//注意一点就是输入的N值是字符串形式
			{
				if (check2[i] <'0' || check2[i]>'9')
				{
					cout << "The N is illegal";
					return false;
				}
			}
			return true;
		}
		else
		{
			cout << "The instruction line format error！\n";
			return false;
		}
	}
	else
	{
		cout << "Parameter number error";
		return false;
	}
}

void CoutToTxt(struct SDK N[], int n)//输出到txt文件里，固定操作，一般都是这样处理
{
	string target = "sudoku.txt";
	fstream CoutTo(target, ios::out);


	if (CoutTo.is_open())
	{
		for (int i = 0; i < n; i++)
		{

			for (int j = 0; j < 9; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					CoutTo << N[i].SDK_Array[j][k] << " ";
				}
				CoutTo << endl;
			}
			CoutTo << endl;
		}
	}
	else    CoutTo << "The file Error, unable to open!";

	CoutTo.close();

}


void TransformRow(struct SDK N[], int i);//变换行，然后进行列变换

void transform(struct SDK N[], int n)
{
	int temp[3];
	//这里进行变换，之后便出现三个不同的3x3宫格

	for (int i = 0; i < n;)
	{
		for (int j = 0; j < 3; j++)     temp[j] = N[i].SDK_Array[0][j];

		sort(temp, temp + 3);

		do
		{
			N[i].SDK_Array[1][6] = temp[0];
			N[i].SDK_Array[1][7] = temp[1];
			N[i].SDK_Array[1][8] = temp[2];
			i++;

		} while (next_permutation(temp, temp + 3) == true);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 3, k = 0, m = 0; m < 6; k++, j = (j + 1) % 9, m++)   N[i].SDK_Array[1][k] = N[i].SDK_Array[0][j];
		//进行第二行相关操作
		for (int j = 6, k = 0, m = 0; m < 9; k++, j = (j + 1) % 9, m++)   N[i].SDK_Array[2][k] = N[i].SDK_Array[0][j];
		//进行第三行相关操作
		TransformRow(N, i);
	}
}

void TransformRow(struct SDK N[], int i)//变换行，然后进行列变换
{
	int num = rand() % 2;

	if (num == 1)
	{

		for (int m = 0; m < 3; m++)
		{

			for (int j = m * 3; j < 3 * (m + 1); j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (j == 2 || j == 5 || j == 8)   N[i].SDK_Array[k + 3][j - 2] = N[i].SDK_Array[k][j];
					else   N[i].SDK_Array[k + 3][j + 1] = N[i].SDK_Array[k][j];
				}
			}
		}


		for (int m = 0; m < 3; m++)
		{
			for (int j = m * 3; j < 3 * (m + 1); j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (j == 0 || j == 3 || j == 6)   N[i].SDK_Array[k + 6][j + 2] = N[i].SDK_Array[k][j];
					else   N[i].SDK_Array[k + 6][j - 1] = N[i].SDK_Array[k][j];
				}
			}
		}
	}

	else
	{
		for (int m = 0; m < 3; m++)
		{
			for (int j = m * 3; j < 3 * (m + 1); j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (j == 0 || j == 3 || j == 6)   N[i].SDK_Array[k + 6][j + 2] = N[i].SDK_Array[k][j];
					else    N[i].SDK_Array[k + 6][j - 1] = N[i].SDK_Array[k][j];
				}
			}
		}
		for (int m = 0; m < 3; m++)
		{
			for (int j = m * 3; j < 3 * (m + 1); j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (j == 2 || j == 5 || j == 8)    N[i].SDK_Array[k + 3][j - 2] = N[i].SDK_Array[k][j];
					else    N[i].SDK_Array[k + 3][j + 1] = N[i].SDK_Array[k][j];
				}
			}
		}

	}
}



void TopRowCreate(struct SDK N[], int n)//对九宫格第一行的随机生成
{
	for (int i = 0; i < n; i++)   N[i].SDK_Array[0][0] = (0 + 6) % 9 + 1;
	//我自己的学号：031502206
	for (int i = 0; i < n;)
	{
		int temp[8] = { 9,5,3,4,2,6,8,1 };
		int count = 0;
		do
		{

			for (int j = 0; j < 8; j++)   N[i].SDK_Array[0][j + 1] = temp[j];
			i += 6;         //因为3的全排列 为 6，所以1个可以转换出6个不同的宫格
			count++;

		} while ((next_permutation(temp, temp + 8) == true && count != n / 6));
	}


	for (int i = 0; i < n; i += 6)
	{
		for (int j = 1; j < 6; j++)   N[i + j] = N[i];
	}
}


int main(int arr, char* argv[])//带参数的主函数，主要是为了接收cmd指令
{
	if (arr < 3)
	{
		cout << "Parameter number error";
		return 0;
	}

	string order1 = argv[1];
	string order2 = argv[2];


	if (OrderCheck(arr, order1, order2) == true)
	{

		int n = StringToNum(order2);
		int tempN = n;
		while (true)
		{
			if (tempN % 6 == 0) break;
			else tempN++;
		}

		SDK * N = new SDK[tempN];

		TopRowCreate(N, tempN);
		transform(N, tempN);

		CoutToTxt(N, n);
		return 0;

	}
	else    return 0;
}

