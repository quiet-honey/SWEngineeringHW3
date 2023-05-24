// 헤더 선언
#include <iostream>
#include <string.h>
#include "recruitment.h"
using namespace std;

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// 함수 선언

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

// 변수 선언
FILE* in_fp, * out_fp;

int main()
{
    // 파일 입출력을 위한 초기화
    FILE* in_fp = fopen(INPUT_FILE_NAME, "r+");
    FILE* out_fp = fopen(OUTPUT_FILE_NAME, "w+");

    doTask();

    return 0;
}

void doTask() {
    // 메뉴 파싱을 위한 level 구분을 위한 변수
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        fscanf(in_fp, "%d %d ", &menu_level_1, &menu_level_2);


        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {/*
        case 1:
            switch (menu_level_2)
            {
            case 1:   // "1.1. 회원가입“ 메뉴 부분
                // signUp() 함수에서 해당 기능 수행 
                signUp();
                break;
            case 2: // "1.2. 회원탈퇴" 메뉴 부분
                // withdrawal() 함수에서 해당 기능 수행 
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
            case 1:   // "6.1. 종료“ 메뉴 부분
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
    fprintf(out_fp, "3.1. 채용 정보 등록\n");
    fprintf(out_fp, "%s %s\n", work, num, deadline);
}
void selectRecruitInfo(){
    fprintf(out_fp, "3.2. 등록된 채용 정보 조회\n");
    RecruitInquiryUI::selectRecruitInfo();
}

void program_exit() {
    fprintf(out_fp, "6.1. 종료\n");
}