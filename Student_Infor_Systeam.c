#include"Student_Infor_Systeam.h"
void show_menu(void) {
	printf("-----------------------------------------------------------\n");
	printf("|----------------- 欢迎来到学生学习管理系统 -------------|\n");
	printf("|----------------- 1 - 添加学生信息 \t-----------------|\n");
	printf("|----------------- 2 - 显示学生信息 \t-----------------|\n");
	printf("|----------------- 3 - 删除学生信息 \t-----------------|\n");
	printf("|----------------- 4 - 查找学生信息 \t-----------------|\n");
	printf("|----------------- 5 - 修改学生信息 \t-----------------|\n");
	printf("|----------------- 6 - 排序学生信息 \t-----------------|\n");
	printf("|----------------- 7 - 清空文件信息 \t-----------------|\n");
	printf("|----------------- 0 - 退出学生学习管理系统 -------------|\n");
	printf("-----------------------------------------------------------\n");
	printf("请您选择：");
	fflush(stdout);
}

bool input_choose(int*const choose) {
	fflush(stdin);
	scanf("%d", choose);

	bool ret = *choose < 0 || *choose>7;
	return ret;
}

void copy_Data(Student* first, Student*last, Student*target) {
	while (first != last) {
		*target++ = *first++;
	}
	*((Student**)&target) = first;
}
void Calculate_TotalScore(Student_Infor_Systeam * const Systeam) {
	if (Systeam != NULL) {
		for (Student*First = Systeam->infor.data, *Last = Systeam->infor.data + Systeam->infor.size;
			First != Last; ++First) {
			First->Total_Res = First->Res.Language_result + First->Res.Math_result + First->Res.Language_result;
		}
	}
}
void Save_StudentInfor(Student_Infor_Systeam * const Systeam) {

	if (Systeam != NULL) {
		FILE *write = fopen(File_Name, "w");
		if (write != NULL) {
			for (Student*First = Systeam->infor.data, *Last = Systeam->infor.data + Systeam->infor.size; First != Last; ++First)
			{
				fprintf(write, "%d %s %u %u %u %d\n", First->id, First->name,
					First->Res.Language_result, First->Res.Math_result, First->Res.English_result,
					First->Total_Res);
				fflush(write);
			}
			fclose(write);
			printf("保存到文件成功! \n");
		}
	}
}
int GetStudentInforNum(void) {
	int ret = 0;
	FILE* read = fopen(File_Name, "r");
	if (!read) {
		return ret;
	}
	char buf[1024];
	while (fgets(buf, sizeof(buf), read))
	{
		++ret;
	}
	return ret;
}
bool isFileExists(void) {
	FILE* read = fopen(File_Name, "r");
	bool ret = read == NULL;
	if (!ret) {
		fclose(read);
	}
	return ret;
}
bool isFileEmpty(void) {
	FILE* read = fopen(File_Name, "r");
	bool ret = read != NULL;
	if (ret)
	{
		ret = (fgetc(read) == EOF) ? true : false;
		fclose(read);
	}
	return ret;
	//return false;
}
void GetStudentInfor(Student_Infor_Systeam * const Systeam) {

	if (Systeam != NULL) {

		FILE* read = fopen(File_Name, "r");
		if (!read) {
			return;
		}

		for (Student* First = Systeam->infor.data, *Last = Systeam->infor.data + Systeam->infor.size; First != Last; ++First)
		{
			fscanf(read, "%d %s %u %u %u %d", &First->id, First->name,
				&First->Res.Language_result, &First->Res.Math_result, &First->Res.English_result,
				&First->Total_Res);
			//fflush(write);
		}

		//fflush(write);
		fclose(read);
	}
}

void init(Student_Infor_Systeam * const Systeam) {
#ifdef __cplusplus
	Student*  newSpace = reinterpret_cast<Student*>(malloc(sizeof(Student)*newsize));
#endif // !1
	Student*  newSpace = (Student*)malloc(sizeof(Student)*Systeam->infor.size);
	if (newSpace != NULL) {
		Systeam->infor.data = newSpace;
		GetStudentInfor(Systeam);
		Calculate_TotalScore(Systeam);
	}
}

void constructor(Student_Infor_Systeam * const Systeam) {


	if (Systeam != NULL) {

		Systeam->isFileEmpty = isFileEmpty();
		Systeam->isFileExists = isFileExists();
		int num = GetStudentInforNum();
		if (num != 0) {
			Systeam->infor.size = num;
			init(Systeam);
		}
	}
}


//添加学生信息
void Add_StudentInfor(Student_Infor_Systeam * const Systeam) {
	//判断指针合法性
	if (Systeam != NULL) {
		int number;
		int newsize;
		printf("请输入添加学生的数目：");
		scanf("%d", &number);
		if (number <= 0) {
			printf("输入有误，重新进入添加功能");
			return;
		}
		else {
			newsize = number + Systeam->infor.size;
#ifdef __cplusplus
			Student*  newSpace =reinterpret_cast<Student*>( malloc(sizeof(Student)*newsize));
#endif // !1
			Student*  newSpace = (Student*)malloc(sizeof(Student)*newsize);
			
			Student input;
			bool flag = false;
			if (newSpace != NULL) {
				if (Systeam->infor.data != NULL) {
					copy_Data(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, newSpace);
				}
				for (int i = 0; i < number; ++i) {

					while (!flag) {
						printf_s("请输入第 %u 个学生的编号：", i + 1);
						scanf("%d", &(input.id));
						fflush(stdin);
						for (int j = 0; j < Systeam->infor.size + number; j++) {
							if (input.id == newSpace[j].id) {
								printf("重复的编号：%d\n", input.id);
								getchar();
								getchar();
								flag = false;
								break;
							}
							else {
								flag = true;
							}
						}
						if (flag) {
							break;
						}
					}

					printf_s("请输入第 %u 个学生的姓名：", i + 1);
					scanf("%s", input.name);
					fflush(stdin);

					printf_s("请输入第 %u 个学生的语文成绩：", i + 1);
					scanf("%u", &((input.Res).Language_result));
					fflush(stdin);

					printf_s("请输入第 %u 个学生的数学成绩：", i + 1);
					scanf("%u", &((input.Res).Math_result));
					fflush(stdin);

					printf_s("请输入第 %u 个学生的英语成绩：", i + 1);
					scanf("%u", &((input.Res).English_result));
					fflush(stdin);
					*(newSpace + (Systeam->infor.size + i)) = input;

				}
				if (Systeam->infor.data != NULL) {
					free(Systeam->infor.data);
					Systeam->infor.data = NULL;
				}

				Systeam->infor.data = newSpace;
				Systeam->infor.size = newsize;
				Save_StudentInfor(Systeam);
				printf("成功添加学生信息%d条信息\n", number);
			}
		}
	}
}

void Destroy(Student_Infor_Systeam*const Systeam) {

	if (Systeam != NULL) {
		if (Systeam->infor.data != NULL) {
			free(Systeam->infor.data);
			Systeam->infor.data = NULL;
			memset(Systeam, 0, sizeof(*Systeam));
		}
	}
}
void Show_Student(const Student*const value) {
	if (value != NULL) {

		printf("学生编号：%d   学生姓名：%s   学生语文成绩：%u   学生数学成绩：%u  学生英语成绩：%u  学生总成绩：%u\n",
			value->id, value->name, value->Res.Language_result, value->Res.Math_result, value->Res.English_result, value->Total_Res);
		fflush(stdout);
	}
}

void Show_StudentInfor(const Student_Infor_Systeam *const Systeam) {

	fflush(stdin);
	if (Systeam != NULL) {
		if (Systeam->isFileExists) {
			printf("没有存在这个文件");

		}
		else if (Systeam->isFileEmpty) {
			printf("文件为空");
		}
		else {
			Calculate_TotalScore(Systeam);

			for (const Student* First = Systeam->infor.data, *Last = Systeam->infor.data + Systeam->infor.size; First != Last; ++First)
			{
				Show_Student(First);
				fflush(stdout);
			}

		}
	}
	//fflush(stdin);
	getchar();
	getchar();
	fflush(stdin);
	system("cls");
}

Student* isExists(const Student_Infor_Systeam*const systeam, const int *const id) {

	Student*ret = NULL;
	if (systeam != NULL) {

		if (id != NULL) {

			Student*First = NULL;
			Student*Last = systeam->infor.data + systeam->infor.size;
			for (First = systeam->infor.data; First != Last; ++First) {
				if (First->id == *id) {
					ret = First;
					break;
				}
			}
			if (ret == NULL) {
				ret = First;
			}
		}
	}
	return ret;
}

void Delete_Studentinfor(Student_Infor_Systeam*const Systeam) {
	if (Systeam != NULL) {
		if (Systeam->isFileExists) {
			printf("没有存在这个文件");

		}
		else if (Systeam->isFileEmpty) {
			printf("文件为空");
		}
		else {
			int id;
			printf("请输入您要删除学生的信息的编号：");
			scanf("%d", &id);
			Student*ret = isExists(Systeam, &id);

			Student*Last = Systeam->infor.data + Systeam->infor.size;
			if (ret != NULL) {

				if (ret != Last) {
					Student *temp = ++ret;
					copy_Data(temp, Last, --ret);
					--Systeam->infor.size;
					printf("删除成功\n");
					Save_StudentInfor(Systeam);

					getchar();
					getchar();
					system("pause");
					return;
				}
			}
			printf("删除失败！ 没有这个学生编号为： %d\n", id);
		}
	}
}

void Find_Studentinfor(const Student_Infor_Systeam*const Systeam) {
	if (Systeam != NULL) {
		if (Systeam->isFileExists) {
			printf("没有存在这个文件");

		}
		else if (Systeam->isFileEmpty) {
			printf("文件为空");
		}
		else {
			int select;
			Student*Last = Systeam->infor.data + Systeam->infor.size;
			printf("1-按照学生的编号查找\n");
			printf("2-按照学生的姓名查找\n");
			printf("请输入你的选择：");

			scanf("%d", &select);
			if (select == 1) {
				getchar();
				int id;
				printf("请输入您查找的学生编号：");
				scanf("%d", &id);

				const Student*value = isExists(Systeam, &id);
				if (value) {
					if (value != Last) {
						Show_Student(value);
					}
					else {
						printf("没有这个学生编号为： %d\n", id);
					}
				}
				else {
					printf("没有这个学生编号为： %d\n", id);
				}
			}
			else if (select == 2) {
				getchar();;
				char name[64];
				printf("请输入您查找的学生姓名：");
				scanf("%s", name);
				bool flag = false;
				for (const Student*First = Systeam->infor.data; First != Last; ++First) {

					if (!strcmp(name, First->name)) {
						Show_Student(First);
						flag = true;
					}
				}

				if (!flag) {
					printf("没有这个学生姓名为： %s\n", name);
				}
			}
			else {
				printf("您输入的选择是：%d\n重新进入查找功能\n", select);

			}
		}
		getchar();
		getchar();
	}
}

void Modify_Studentinfor(Student_Infor_Systeam*const Systeam) {

	if (Systeam != NULL) {

		if (Systeam->isFileExists) {
			printf("没有存在这个文件");

		}
		else if (Systeam->isFileEmpty) {
			printf("文件为空");
		}
		else {
			int id;
			printf("请输入学生编号：");
			scanf("%d", &id);
			Student*Last = Systeam->infor.data + Systeam->infor.size;
			Student*data = isExists(Systeam, &id);
			int select;
			if (data != NULL) {

				if (data != Last) {

					printf("1-修改编号\n");
					printf("2-修改姓名\n");
					printf("3-修改语文成绩\n");
					printf("4-修改数学成绩\n");
					printf("5-修改英语成绩\n");
					getchar();
					scanf("%d", &select);
					if (select == 1) {
						getchar();
						printf("请输入您想修改的学生编号：");
						scanf("%d", data->id);
					}
					else if (select == 2) {
						getchar();
						printf("请输入您想修改的学生姓名：");
						scanf("%s", data->name);
					}
					else if (select == 3) {
						getchar();
						printf("请输入您想修改的学生语文成绩：");
						scanf("%u", &data->Res.Language_result);
					}
					else if (select == 4) {
						getchar();
						printf("请输入您想修改的学生数学成绩：");
						scanf("%u", &data->Res.Math_result);
					}
					else if (select == 5) {
						getchar();
						printf("请输入您想修改的学生英语成绩：");
						scanf("%u", &data->Res.English_result);
					}
					else {
						printf("输入有误，重新进入修改功能\n");
						getchar();
						getchar();
						return;
					}
					printf("修改成功!\n");
					Save_StudentInfor(Systeam);
				}
				else {
					printf("没有这个学生编号为： %d\n", id);
				}
			}
			else {
				printf("没有这个学生编号为： %d\n", id);
			}
		}
	}
	getchar();
	getchar();
}

bool compareId_less(Student* s1, Student*s2) {
	return s1->id < s2->id;
}

bool compareId_greater(Student* s1, Student*s2) {
	return s1->id > s2->id;
}

bool compareLanguage_result_less(Student* s1, Student*s2) {
	return s1->Res.Language_result < s2->Res.Language_result;
}

bool compareLanguage_result_greater(Student* s1, Student*s2) {
	return s1->Res.Language_result > s2->Res.Language_result;
}

bool compareMath_result_less(Student* s1, Student*s2) {
	return s1->Res.Math_result < s2->Res.Math_result;
}

bool compareMath_result_greater(Student* s1, Student*s2) {
	return s1->Res.Math_result > s2->Res.Math_result;
}

bool compareEnglish_result_less(Student* s1, Student*s2) {
	return s1->Res.English_result < s2->Res.English_result;
}

bool compareEnglish_result_greater(Student* s1, Student*s2) {
	return s1->Res.English_result > s2->Res.English_result;
}

bool compareTotal_Res_less(Student* s1, Student*s2) {
	return s1->Total_Res < s2->Total_Res;
}

bool compareTotal_Res_greater(Student* s1, Student*s2) {
	return s1->Total_Res > s2->Total_Res;
}
void Select_Sort(Student*First, Student*Last, bool(*compare)(Student*, Student*)) {

	if (First != Last) {
		for (First; First != Last; First++) {

			Student *MinOrMax = First;
			for (Student* UFirst = ++First; UFirst != Last; UFirst++) {
				if (compare(MinOrMax, UFirst)) {
					MinOrMax = UFirst;
				}
			}
			if (--First != MinOrMax) {
				Student Temp = *First;
				*First = *MinOrMax;
				*MinOrMax = Temp;
			}
		}
	}
}

void Sort_Studentinfor(Student_Infor_Systeam* const Systeam) {
	if (Systeam != NULL) {

		if (Systeam->isFileExists) {
			printf("没有存在这个文件");
			getchar();
			getchar();
			return;
		}
		else if (Systeam->isFileEmpty) {
			printf("文件为空");
			getchar();
			getchar();
			return;
		}
		else {
			printf("1-- 按照编号排序\n");
			printf("2-- 按照语文成绩排序\n");
			printf("3-- 按照数学成绩排序\n");
			printf("4-- 按照英语成绩排序\n");
			printf("5-- 按照总成绩排序\n");

			int select;
			int CompSelect;
			printf("请输入你的选择：");
			scanf("%d", &select);
			bool flag = false;
			if (select == 1) {
				printf("1-- 按照编号升序\n");
				printf("1-- 按照编号降序\n");
				printf("请输入你的选择：");
				scanf("%d", &CompSelect);
				if (CompSelect == 1) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareId_less);
					flag = true;
				}
				else if (CompSelect == 2) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareId_greater);
					flag = true;
				}
			}
			else if (select == 2) {
				printf("1-- 按照编号升序\n");
				printf("1-- 按照编号降序\n");
				printf("请输入你的选择：");
				scanf("%d", &CompSelect);
				if (CompSelect == 1) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareLanguage_result_less);
					flag = true;
				}
				else if (CompSelect == 2) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareLanguage_result_greater);
					flag = true;
				}
			}
			else if (select == 3) {
				printf("1-- 按照编号升序\n");
				printf("1-- 按照编号降序\n");
				printf("请输入你的选择：");
				scanf("%d", &CompSelect);
				getchar();
				if (CompSelect == 1) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareMath_result_less);
					flag = true;
				}
				else if (CompSelect == 2) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareMath_result_greater);
					flag = true;
				}
			}
			else if (select == 4) {
				printf("1-- 按照编号升序\n");
				printf("1-- 按照编号降序\n");
				printf("请输入你的选择：");
				scanf("%d", &CompSelect);
				getchar();
				if (CompSelect == 1) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareEnglish_result_less);
					flag = true;
				}
				else if (CompSelect == 2) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareEnglish_result_greater);
					flag = true;
				}
			}
			else if (select == 5) {
				printf("1-- 按照编号升序\n");
				printf("1-- 按照编号降序\n");
				printf("请输入你的选择：");
				scanf("%d", &CompSelect);
				getchar();
				if (CompSelect == 1) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareTotal_Res_less);
					flag = true;
				}
				else if (CompSelect == 2) {
					Select_Sort(Systeam->infor.data, Systeam->infor.data + Systeam->infor.size, compareTotal_Res_greater);
					flag = true;
				}
			}
			if (flag) {
				Save_StudentInfor(Systeam);
				Show_StudentInfor(Systeam);
			}
			else {
				printf("选择有误 ，重新进入排序功能\n");
			}


		}
	}
}
void Clear_File(Student_Infor_Systeam*const Systeam) {

	if (Systeam != NULL) {

		if (Systeam->isFileExists) {
			printf("没有存在这个文件");
			getchar();
			getchar();
			return;
		}
		else if (Systeam->isFileEmpty) {
			printf("文件为空");
			getchar();
			getchar();
			return;
		}
		else {
			printf("1---确定");
			printf("0---取消");

			printf("是否清空文件：");
			int Select;
			scanf("%d", &Select);
			if (Select == 1) {
				FILE* Trunc = fopen(File_Name, "w");
				if (Trunc != NULL) {
					fclose(Trunc);
					if (Systeam->infor.data != NULL) {
						free(Systeam->infor.data);
						Systeam->infor.data = NULL;
						Systeam->infor.size = 0;
						Systeam->isFileEmpty = true;
						printf("清空文件成功");
					}

				}
			}
			else if (Select == 0) {

			}
			else {
				printf("选择错误，回到此功能 您选择的是:%d\n", Select);
			}
		}
	}
	getchar();
	getchar();
}
