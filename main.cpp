// ��� ����
#include <iostream>
#include <string.h>
#include "recruitment.h"
using namespace std;

// ��� ����
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// �Լ� ����

void doTask();
/*
void signUp();
void withdrawal();
void login();
void logout();
*/
void createNewRecruit();
void selectRecruitInfo();
/*
void searchRecruitment();
void apply();
void selectApplyInfo();
void cancelApplyInfo();
void showRecruitNumInfo();
*/
void program_exit();

// ���� ����
FILE* in_fp, * out_fp;

int main()
{
    // ���� ������� ���� �ʱ�ȭ
    FILE* in_fp = fopen(INPUT_FILE_NAME, "r+");
    FILE* out_fp = fopen(OUTPUT_FILE_NAME, "w+");

    doTask();

    return 0;
}

void doTask() {
    // �޴� �Ľ��� ���� level ������ ���� ����
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        // �Է����Ͽ��� �޴� ���� 2���� �б�
        fscanf(in_fp, "%d %d ", &menu_level_1, &menu_level_2);


        // �޴� ���� �� �ش� ���� ����
        switch (menu_level_1)
        {/*
        case 1:
            switch (menu_level_2)
            {
            case 1:   // "1.1. ȸ�����ԡ� �޴� �κ�
                // signUp() �Լ����� �ش� ��� ���� 
                signUp();
                break;
            case 2: // "1.2. ȸ��Ż��" �޴� �κ�
                // withdrawal() �Լ����� �ش� ��� ���� 
                withdrawal();
                break;
            default:
                break;
            }
            break;

        case 2:
            switch (menu_level_2)
            {
            case 1:
                login();
                break;
            case 2:
                logout();
                break;
            default:
                break;
            }
            break;
        */
        case 3:
            switch (menu_level_2)
            {
            case 1:
                createNewRecruit();
                break;
            case 2:
                selectRecruitInfo();
                break;
            default:
                break;
            }
            break;
        /*
        case 4:
            switch (menu_level_2)
            {
            case 1:
                searchRecruitment();
                break;
            case 2:
                apply();
                break;
            case 3:
                selectApplyInfo();
                break;
            case 4:
                cancelApplyInfo();
                break;
            default:
                break;
            }
            break;

        case 5:
            switch (menu_level_2)
            {
            case 1:
                showRecruitNumInfo();
                break;
            default:
                break;
            }
            break;
        */
        case 6:
            switch (menu_level_2)
            {
            case 1:   // "6.1. ���ᡰ �޴� �κ�
                program_exit();
                is_program_exit = 1;
                break;
            default:
                break;
            }
        
        default:
            break;
        }
    }
}

void createNewRecruit(){
    char work[MAX_STRING], deadline[MAX_STRING];
    int num;

    fscanf(in_fp, "%s %d %s\n", work, num, deadline);
    AddRecruitInfoUI::createNewRecruit(work, num, deadline);
    fprintf(out_fp, "3.1. ä�� ���� ���\n");
    fprintf(out_fp, "%s %s\n", work, num, deadline);
}
void selectRecruitInfo(){
    fprintf(out_fp, "3.2. ��ϵ� ä�� ���� ��ȸ\n");
    RecruitInquiryUI::selectRecruitInfo();
}

void program_exit() {
    fprintf(out_fp, "6.1. ����\n");
}