#ifndef STUDENT_INFOR_SYSTEAM_H
#define STUDENT_INFOR_SYSTEAM_H
#pragma once
#include<stdio.h>
#include<stdlib.h>
#ifndef __cplusplus
#include<stdbool.h>
#endif 
#ifndef __cplusplus
 static  const  char* File_Name;
#endif // __cplusplus
#ifdef __cplusplus
 const  constexpr char* File_Name = "Student.txt";
#endif // __cplusplus
#ifndef __cplusplus
 static const  char* File_Name = "Student.txt";
#endif // __cplusplus
struct Results {
	unsigned int Language_result;//语文成绩
	unsigned int Math_result;//数学成绩
	unsigned int English_result;//英语成绩
};
#ifndef __cplusplus
typedef struct Results  Results;
#endif 
struct Student {
	int id;//学生编号
	char name[64];//学生姓名
	Results Res;//各科成绩
	unsigned int Total_Res;//总成绩
};
#ifndef __cplusplus
typedef struct Student Student;
#endif
struct Student_Infor
{
	Student*data;
	unsigned int size;
};
#ifndef __cplusplus
typedef  struct Student_Infor Student_Infor;
#endif
struct Student_Infor_Systeam {
	Student_Infor infor;
	bool isFileExists;
	bool isFileEmpty;
};
#ifndef __cplusplus
typedef  struct Student_Infor_Systeam Student_Infor_Systeam;
#endif

#ifdef __cplusplus
extern "C" {
#endif //!__cplusplus

	void show_menu(void);
	bool input_choose(int*const choose);

	void copy_Data(Student* first, Student*last, Student*target);
	void Calculate_TotalScore(Student_Infor_Systeam * const Systeam);
	void Save_StudentInfor(Student_Infor_Systeam * const Systeam);

	int GetStudentInforNum(void);

	bool isFileExists(void);

	bool isFileEmpty(void);

	void GetStudentInfor(Student_Infor_Systeam * const Systeam);

	void init(Student_Infor_Systeam * const Systeam);

	void constructor(Student_Infor_Systeam * const Systeam);

	//添加学生信息
	void Add_StudentInfor(Student_Infor_Systeam * const Systeam);
	void Destroy(Student_Infor_Systeam*const Systeam);

	void Show_Student(const Student*const value);

	void Show_StudentInfor(const Student_Infor_Systeam *const Systeam);

	Student* isExists(const Student_Infor_Systeam*const systeam, const int *const id);

	void Delete_Studentinfor(Student_Infor_Systeam*const Systeam);

	void Find_Studentinfor(const Student_Infor_Systeam*const Systeam);

	void Modify_Studentinfor(Student_Infor_Systeam*const Systeam);

	bool compareId_less(Student* s1, Student*s2);

	bool compareId_greater(Student* s1, Student*s2);

	bool compareLanguage_result_less(Student* s1, Student*s2);

	bool compareLanguage_result_greater(Student* s1, Student*s2);

	bool compareMath_result_less(Student* s1, Student*s2);

	bool compareMath_result_greater(Student* s1, Student*s2);

	bool compareEnglish_result_less(Student* s1, Student*s2);

	bool compareEnglish_result_greater(Student* s1, Student*s2);

	bool compareTotal_Res_less(Student* s1, Student*s2);

	bool compareTotal_Res_greater(Student* s1, Student*s2);

	void Select_Sort(Student*First, Student*Last, bool(*compare)(Student*, Student*));

	void Sort_Studentinfor(Student_Infor_Systeam* const Systeam);

	void Clear_File(Student_Infor_Systeam*const Systeam);
#ifdef __cplusplus
}
#endif //!__cplusplus
#endif
