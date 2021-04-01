#include"Student_Infor_Systeam.h"

void test(void) {

	bool flag = false;
	int select;
	Student_Infor_Systeam Systeam = {0};
	constructor(&Systeam);
	while (!flag) {
		system("cls");
		show_menu();
		if (input_choose(&select)) {
			printf("输入有误 重新输入!\n");

			fflush(stdin);
			getchar();
			system("cls");
		}
		else {
			switch (select) {
			case 1:
				Add_StudentInfor(&Systeam);
				break;
			case 2:
				Show_StudentInfor(&Systeam);
				break;
			case 3:
				Delete_Studentinfor(&Systeam);
				break;
			case 4:
				Find_Studentinfor(&Systeam);
				break;
			case 5:
				Modify_Studentinfor(&Systeam);
				break;
			case 6:
				Sort_Studentinfor(&Systeam);
				break;
			case 7:
				Clear_File(&Systeam);
				break;
			case 0:
				flag = true;
				break;
			default:
				break;
			}
		}
	}
	Destroy(&Systeam);
}

int main(void) {
	
	test();
	return 0;
}