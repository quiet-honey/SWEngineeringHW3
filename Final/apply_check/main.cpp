#define _CRT_SECURE_NO_WARNINGS
// 헤더 선언
#include <iostream>
#include <string.h>
#include <algorithm>
#include <map>
#include "recruitment.h"
#include "member.h"
#include "applyinfo.h"
using namespace std;

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// 함수 선언
void doTask();
void signUp();
void withdrawal();

void login();
void logout();
void createNewRecruit();
void selectRecruitInfo();
Recruitment* searchRecruitment();
void apply(Recruitment*);
void selectApplyInfo();
void cancelApplyInfo();
void showRecruitNumInfo();
void program_exit();

// 변수 선언
FILE* in_fp, * out_fp;
MemberList* MemberList::instance = nullptr;
Recruitment* searchResult = nullptr;

int main()
{
    // 파일 입출력을 위한 초기화
    in_fp = fopen(INPUT_FILE_NAME, "r+");
    out_fp = fopen(OUTPUT_FILE_NAME, "w+");

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
        {
        case 1:
        {
            switch (menu_level_2)
            {
            case 1: // "1.1. 회원가입" 메뉴 부분
                signUp();
                break;
            case 2: // "1.2. 회원탈퇴" 메뉴 부분
                withdrawal();
                break;
            default:
                break;
            }
            break;
        }
        case 2:
        {
            switch (menu_level_2)
            {
            case 1: // "2.1. 로그인" 메뉴 부분
                login();
                break;
            case 2: // "2.2. 로그아웃" 메뉴 부분
                logout();
                break;
            default:
                break;
            }
            break;
        }
        case 3:
        {
            switch (menu_level_2)
            {
            case 1: // "3.1. 채용 정보 등록" 메뉴 부분
                createNewRecruit();
                break;
            case 2: // "3.2. 등록된 채용 정보 조회" 메뉴 부분
                selectRecruitInfo();
                break;
            default:
                break;
            }
            break;
        }
        case 4:
        {
            switch (menu_level_2)
            {
            case 1: // "4.1. 채용 정보 검색" 메뉴 부분
                searchResult = searchRecruitment();
                break;
            case 2: // "4.2. 채용 지원" 메뉴 부분
                apply(searchResult);
                break;
            case 3: // "4.3. 지원 정보 조회" 메뉴 부분
                selectApplyInfo();
                break;
            case 4: // "4.4. 지원 취소" 메뉴 부분
                cancelApplyInfo();
                break;
            default:
                break;
            }
            break;
        }
        
        case 5:
            switch (menu_level_2)
            {
            case 1: // "5.1. 지원 정보 통계" 메뉴 부분
                showRecruitNumInfo();
                break;
            default:
                break;
            }
            break;
            
        case 6:
            switch (menu_level_2)
            {
            case 1: // "6.1. 종료" 메뉴 부분
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

// "1.1. 회원가입"
void signUp() {
    char memberType[MAX_STRING], name[MAX_STRING], num[MAX_STRING], id[MAX_STRING], pw[MAX_STRING];

    // 입력 형식 : 회원 유형, 이름, 주민번호/사업자번호, ID, PW를 파일로부터 읽음
    fscanf(in_fp, "%s %s %s %s %s ", memberType, name, num, id, pw);

    // Boundary Class 호출
    signUpUI::signUp(memberType, name, num, id, pw);
    fprintf(out_fp, "1.1. 회원가입\n");
    fprintf(out_fp, "%s %s %s %s\n", name, num, id, pw);
}

// "1.2. 회원탈퇴"
void withdrawal() {
    // Boundary Class 호출
    string id = withdrawalUI::withdrawal();
    fprintf(out_fp, "1.2. 회원탈퇴\n");
    fprintf(out_fp, "%s\n", id.c_str());
}

// "2.1. 로그인"
void login() {
    char id[MAX_STRING], pw[MAX_STRING];

    // 입력 형식 : ID, PW를 파일로부터 읽음
    fscanf(in_fp, "%s %s", id, pw);

    // Boundary Class 호출
    loginUI::login(id, pw);
    fprintf(out_fp, "2.1. 로그인\n");
    fprintf(out_fp, "%s %s\n", id, pw);
}

// "2.2. 로그아웃"
void logout() {
    // Boundary Class 호출
    string id = logoutUI::logout();
    fprintf(out_fp, "2.2. 로그아웃\n");
    fprintf(out_fp, "%s\n", id.c_str());
}

// "3.1. 채용 정보 등록"
void createNewRecruit() {
    char work[MAX_STRING], deadline[MAX_STRING];
    int num;
    fscanf(in_fp, "%s %d %s", work, &num, deadline);

    // Boundary Class 호출
    AddRecruitInfoUI::createNewRecruit(work, num, deadline);
    fprintf(out_fp, "3.1. 채용 정보 등록\n");
    fprintf(out_fp, "%s %d %s\n", work, num, deadline);
}

// "3.2. 등록된 채용 정보 조회"
void selectRecruitInfo() {
    // Boundary Class 호출
    vector<Recruitment*> recruitments = RecruitInquiryUI::selectRecruitInfo();

    MemberList* memberList = MemberList::getInstance(); // 현재 로그인한 User 변수
    string loginCompanyName = memberList->getCurrentUser()->getName();
    fprintf(out_fp, "3.2. 등록된 채용 정보 조회\n");
    for (auto recruit : recruitments) {
        if(recruit->getCompany() == loginCompanyName) // 로그인한 회사 회원이 등록한 채용 정보 출력
            fprintf(out_fp, "%s %d %s\n", recruit->getWork().c_str(), recruit->getNumberOfRecruit(), recruit->getDeadline().c_str());
    }
}

// "4.1. 채용 정보 검색"
Recruitment* searchRecruitment() {
    char company[MAX_STRING];
    // 입력: 회사 이름(company)
    fscanf(in_fp, "%s", company);

    Member* member = MemberList::getInstance()->getCurrentUser(); // 현재 로그인한 User 변수

    if (typeid(*member) == typeid(NormalMember)) { // 일반 회원만 4.1. 메뉴 진행 가능
        // Boundary Class 호출
        vector<Recruitment*> recruitments = GetRecruitmentUI::showRecruitment(); // 채용 정보 리스트 불러오기
        fprintf(out_fp, "4.1. 채용 정보 검색\n");
        for (auto recruit : recruitments) {
            if (recruit->getCompany() == company) // 채용 정보 리스트에서 원하는 회사 이름으로 검색, 출력
            {
                fprintf(out_fp, "%s %s %s %d %s\n", recruit->getCompany().c_str(), recruit->getBizNum().c_str(), recruit->getWork().c_str(), recruit->getNumberOfRecruit(), recruit->getDeadline().c_str());
                return recruit;
            }
        }
    }
}

// "4.2. 채용 지원"
void apply(Recruitment* recruitment) {
    char biznum[MAX_STRING];
    fscanf(in_fp, "%s", biznum);

    Member* normalmember = MemberList::getInstance()->getCurrentUser();

    if (recruitment->getBizNum() == biznum) {
        // Boundary Class 호출
        ApplyUI::apply(normalmember, recruitment);
        fprintf(out_fp, "4.2. 채용 지원\n");
        fprintf(out_fp, "%s %s %s\n", recruitment->getCompany().c_str(), recruitment->getBizNum().c_str(), recruitment->getWork().c_str());
    }
}

/*
    함수 이름 : cmp()
    기능	  : 회사 이름 기준 오름차순 정렬
    전달 인자 : Recruitment*& (비교에 필요한 두 인자)
    반환값    : bool
*/
bool cmp(Recruitment*& r1, Recruitment*& r2) {
    if (r1->getCompany() < r2->getCompany()) return true;
    return false;
}

// "4.3. 지원 정보 조회"
void selectApplyInfo() {
    Member* normalMember = MemberList::getInstance()->getCurrentUser(); // 현재 로그인한 User 변수

    fprintf(out_fp, "4.3. 지원 정보 조회\n");
    // Boundary Class 호출
    vector<ApplyInfo*> applyinfo = ApplyInquiryUI::selectApplyInfo(); // 모든 채용정보를 담은 변수 applyinfo
    vector<Recruitment*> applyRecruitmentList; // 지원한 채용정보를 저장할 vector 변수 applyRecruitmentList
    for (auto apply : applyinfo ) {
        if (apply->getNormalMember()->getId() == normalMember->getId() && apply->getNormalMember()->getPw() == normalMember->getPw()) { // 현재 로그인한 User가 지원한 채용정보라면 vector에 저장
            applyRecruitmentList.push_back(apply->getRecruitment());
        }
    }

    // 회사 이름 기준 오름차순 정렬
    sort(applyRecruitmentList.begin(), applyRecruitmentList.end(), cmp);
    for (auto applyRecruitment : applyRecruitmentList) {
        fprintf(out_fp, "%s %s %s %d %s\n", applyRecruitment->getCompany().c_str(), applyRecruitment->getBizNum().c_str(), applyRecruitment->getWork().c_str(), applyRecruitment->getNumberOfRecruit(), applyRecruitment->getDeadline().c_str());
    }
}

// "4.4. 지원 취소"
void cancelApplyInfo() {
    char biznum[MAX_STRING];
    // 입력: 사업자번호(biznum)
    fscanf(in_fp, "%s", biznum);

    fprintf(out_fp, "4.4. 지원 정보 취소\n");
    // Boundary Class 호출
    Recruitment* canceled = CancelApplyInfoUI::cancelApplyInfo(biznum);
    fprintf(out_fp, "%s %s %s\n", canceled->getCompany().c_str(), canceled->getBizNum().c_str(), canceled->getWork().c_str());
}

// "5.1. 지원 정보 통계"
void showRecruitNumInfo() {
    fprintf(out_fp, "5.1. 지원 정보 통계\n");

    Member* member = MemberList::getInstance()->getCurrentUser(); // 현재 로그인한 User 변수
    if (typeid(*member) == typeid(BizMember)) { // 로그인한 User가 회사회원이라면
        // Boundary Class 호출
        vector<Recruitment*> recruitments = GetRecruitNumUI::showRecruitNumInfo();
        for (auto recruit : recruitments) {
            if(recruit->getBizNum() == member->getBizNum()) // 해당 회사회원이 등록한 모든 채용정보 출력
                fprintf(out_fp, "%s %d\n", recruit->getWork().c_str(), recruit->getNumberOfApplicants());
        }
    }
    else if (typeid(*member) == typeid(NormalMember)) { // 로그인한 User가 일반회원이라면
        // Boundary Class 호출
        map<string, int> mp = GetApplyNumUI::showApplyNumInfo();
        for (auto set : mp) { // 해당 일반회원이 지원한 채용 정보를 map<업무, 지원 횟수>로 저장, 출력
            fprintf(out_fp, "%s %d\n", set.first.c_str(), set.second);
        }
    }
}

// "6.1. 종료"
void program_exit() {
    fprintf(out_fp, "6.1. 종료\n");
}