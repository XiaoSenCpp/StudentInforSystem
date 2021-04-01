#include"Student_Infor_Systeam.h"
void show_menu(void) {
	printf("-----------------------------------------------------------\n");
	printf("|----------------- ��ӭ����ѧ��ѧϰ����ϵͳ -------------|\n");
	printf("|----------------- 1 - ���ѧ����Ϣ \t-----------------|\n");
	printf("|----------------- 2 - ��ʾѧ����Ϣ \t-----------------|\n");
	printf("|----------------- 3 - ɾ��ѧ����Ϣ \t-----------------|\n");
	printf("|----------------- 4 - ����ѧ����Ϣ \t-----------------|\n");
	printf("|----------------- 5 - �޸�ѧ����Ϣ \t-----------------|\n");
	printf("|----------------- 6 - ����ѧ����Ϣ \t-----------------|\n");
	printf("|----------------- 7 - ����ļ���Ϣ \t-----------------|\n");
	printf("|----------------- 0 - �˳�ѧ��ѧϰ����ϵͳ -------------|\n");
	printf("-----------------------------------------------------------\n");
	printf("����ѡ��");
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
			printf("���浽�ļ��ɹ�! \n");
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


//���ѧ����Ϣ
void Add_StudentInfor(Student_Infor_Systeam * const Systeam) {
	//�ж�ָ��Ϸ���
	if (Systeam != NULL) {
		int number;
		int newsize;
		printf("���������ѧ������Ŀ��");
		scanf("%d", &number);
		if (number <= 0) {
			printf("�����������½�����ӹ���");
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
						printf_s("������� %u ��ѧ���ı�ţ�", i + 1);
						scanf("%d", &(input.id));
						fflush(stdin);
						for (int j = 0; j < Systeam->infor.size + number; j++) {
							if (input.id == newSpace[j].id) {
								printf("�ظ��ı�ţ�%d\n", input.id);
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

					printf_s("������� %u ��ѧ����������", i + 1);
					scanf("%s", input.name);
					fflush(stdin);

					printf_s("������� %u ��ѧ�������ĳɼ���", i + 1);
					scanf("%u", &((input.Res).Language_result));
					fflush(stdin);

					printf_s("������� %u ��ѧ������ѧ�ɼ���", i + 1);
					scanf("%u", &((input.Res).Math_result));
					fflush(stdin);

					printf_s("������� %u ��ѧ����Ӣ��ɼ���", i + 1);
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
				printf("�ɹ����ѧ����Ϣ%d����Ϣ\n", number);
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

		printf("ѧ����ţ�%d   ѧ��������%s   ѧ�����ĳɼ���%u   ѧ����ѧ�ɼ���%u  ѧ��Ӣ��ɼ���%u  ѧ���ܳɼ���%u\n",
			value->id, value->name, value->Res.Language_result, value->Res.Math_result, value->Res.English_result, value->Total_Res);
		fflush(stdout);
	}
}

void Show_StudentInfor(const Student_Infor_Systeam *const Systeam) {

	fflush(stdin);
	if (Systeam != NULL) {
		if (Systeam->isFileExists) {
			printf("û�д�������ļ�");

		}
		else if (Systeam->isFileEmpty) {
			printf("�ļ�Ϊ��");
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
			printf("û�д�������ļ�");

		}
		else if (Systeam->isFileEmpty) {
			printf("�ļ�Ϊ��");
		}
		else {
			int id;
			printf("��������Ҫɾ��ѧ������Ϣ�ı�ţ�");
			scanf("%d", &id);
			Student*ret = isExists(Systeam, &id);

			Student*Last = Systeam->infor.data + Systeam->infor.size;
			if (ret != NULL) {

				if (ret != Last) {
					Student *temp = ++ret;
					copy_Data(temp, Last, --ret);
					--Systeam->infor.size;
					printf("ɾ���ɹ�\n");
					Save_StudentInfor(Systeam);

					getchar();
					getchar();
					system("pause");
					return;
				}
			}
			printf("ɾ��ʧ�ܣ� û�����ѧ�����Ϊ�� %d\n", id);
		}
	}
}

void Find_Studentinfor(const Student_Infor_Systeam*const Systeam) {
	if (Systeam != NULL) {
		if (Systeam->isFileExists) {
			printf("û�д�������ļ�");

		}
		else if (Systeam->isFileEmpty) {
			printf("�ļ�Ϊ��");
		}
		else {
			int select;
			Student*Last = Systeam->infor.data + Systeam->infor.size;
			printf("1-����ѧ���ı�Ų���\n");
			printf("2-����ѧ������������\n");
			printf("���������ѡ��");

			scanf("%d", &select);
			if (select == 1) {
				getchar();
				int id;
				printf("�����������ҵ�ѧ����ţ�");
				scanf("%d", &id);

				const Student*value = isExists(Systeam, &id);
				if (value) {
					if (value != Last) {
						Show_Student(value);
					}
					else {
						printf("û�����ѧ�����Ϊ�� %d\n", id);
					}
				}
				else {
					printf("û�����ѧ�����Ϊ�� %d\n", id);
				}
			}
			else if (select == 2) {
				getchar();;
				char name[64];
				printf("�����������ҵ�ѧ��������");
				scanf("%s", name);
				bool flag = false;
				for (const Student*First = Systeam->infor.data; First != Last; ++First) {

					if (!strcmp(name, First->name)) {
						Show_Student(First);
						flag = true;
					}
				}

				if (!flag) {
					printf("û�����ѧ������Ϊ�� %s\n", name);
				}
			}
			else {
				printf("�������ѡ���ǣ�%d\n���½�����ҹ���\n", select);

			}
		}
		getchar();
		getchar();
	}
}

void Modify_Studentinfor(Student_Infor_Systeam*const Systeam) {

	if (Systeam != NULL) {

		if (Systeam->isFileExists) {
			printf("û�д�������ļ�");

		}
		else if (Systeam->isFileEmpty) {
			printf("�ļ�Ϊ��");
		}
		else {
			int id;
			printf("������ѧ����ţ�");
			scanf("%d", &id);
			Student*Last = Systeam->infor.data + Systeam->infor.size;
			Student*data = isExists(Systeam, &id);
			int select;
			if (data != NULL) {

				if (data != Last) {

					printf("1-�޸ı��\n");
					printf("2-�޸�����\n");
					printf("3-�޸����ĳɼ�\n");
					printf("4-�޸���ѧ�ɼ�\n");
					printf("5-�޸�Ӣ��ɼ�\n");
					getchar();
					scanf("%d", &select);
					if (select == 1) {
						getchar();
						printf("�����������޸ĵ�ѧ����ţ�");
						scanf("%d", data->id);
					}
					else if (select == 2) {
						getchar();
						printf("�����������޸ĵ�ѧ��������");
						scanf("%s", data->name);
					}
					else if (select == 3) {
						getchar();
						printf("�����������޸ĵ�ѧ�����ĳɼ���");
						scanf("%u", &data->Res.Language_result);
					}
					else if (select == 4) {
						getchar();
						printf("�����������޸ĵ�ѧ����ѧ�ɼ���");
						scanf("%u", &data->Res.Math_result);
					}
					else if (select == 5) {
						getchar();
						printf("�����������޸ĵ�ѧ��Ӣ��ɼ���");
						scanf("%u", &data->Res.English_result);
					}
					else {
						printf("�����������½����޸Ĺ���\n");
						getchar();
						getchar();
						return;
					}
					printf("�޸ĳɹ�!\n");
					Save_StudentInfor(Systeam);
				}
				else {
					printf("û�����ѧ�����Ϊ�� %d\n", id);
				}
			}
			else {
				printf("û�����ѧ�����Ϊ�� %d\n", id);
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
			printf("û�д�������ļ�");
			getchar();
			getchar();
			return;
		}
		else if (Systeam->isFileEmpty) {
			printf("�ļ�Ϊ��");
			getchar();
			getchar();
			return;
		}
		else {
			printf("1-- ���ձ������\n");
			printf("2-- �������ĳɼ�����\n");
			printf("3-- ������ѧ�ɼ�����\n");
			printf("4-- ����Ӣ��ɼ�����\n");
			printf("5-- �����ܳɼ�����\n");

			int select;
			int CompSelect;
			printf("���������ѡ��");
			scanf("%d", &select);
			bool flag = false;
			if (select == 1) {
				printf("1-- ���ձ������\n");
				printf("1-- ���ձ�Ž���\n");
				printf("���������ѡ��");
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
				printf("1-- ���ձ������\n");
				printf("1-- ���ձ�Ž���\n");
				printf("���������ѡ��");
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
				printf("1-- ���ձ������\n");
				printf("1-- ���ձ�Ž���\n");
				printf("���������ѡ��");
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
				printf("1-- ���ձ������\n");
				printf("1-- ���ձ�Ž���\n");
				printf("���������ѡ��");
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
				printf("1-- ���ձ������\n");
				printf("1-- ���ձ�Ž���\n");
				printf("���������ѡ��");
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
				printf("ѡ������ �����½���������\n");
			}


		}
	}
}
void Clear_File(Student_Infor_Systeam*const Systeam) {

	if (Systeam != NULL) {

		if (Systeam->isFileExists) {
			printf("û�д�������ļ�");
			getchar();
			getchar();
			return;
		}
		else if (Systeam->isFileEmpty) {
			printf("�ļ�Ϊ��");
			getchar();
			getchar();
			return;
		}
		else {
			printf("1---ȷ��");
			printf("0---ȡ��");

			printf("�Ƿ�����ļ���");
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
						printf("����ļ��ɹ�");
					}

				}
			}
			else if (Select == 0) {

			}
			else {
				printf("ѡ����󣬻ص��˹��� ��ѡ�����:%d\n", Select);
			}
		}
	}
	getchar();
	getchar();
}
