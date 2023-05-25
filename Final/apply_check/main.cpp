#define _CRT_SECURE_NO_WARNINGS
// ��� ����
#include <iostream>
#include <string.h>
#include <algorithm>
#include <map>
#include "recruitment.h"
#include "member.h"
#include "applyinfo.h"
using namespace std;

// ��� ����
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// �Լ� ����
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

// ���� ����
FILE* in_fp, * out_fp;
MemberList* MemberList::instance = nullptr;
Recruitment* searchResult = nullptr;

int main()
{
    // ���� ������� ���� �ʱ�ȭ
    in_fp = fopen(INPUT_FILE_NAME, "r+");
    out_fp = fopen(OUTPUT_FILE_NAME, "w+");

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
        {
        case 1:
        {
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
        }
        case 2:
        {
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
        }
        case 3:
        {
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
        }
        case 4:
        {
            switch (menu_level_2)
            {
            case 1:
                searchResult = searchRecruitment();
                break;
            case 2:
                apply(searchResult);
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
        }
        
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
void signUp() {
    /*            !!!!!!!       �߿�        !!!!!!!!!
    * �ܼ��� ������ ���� ������ϴ� ����� ���̱� ���� �ڵ��̹Ƿ� �� �Լ����� �״�� ����ϸ� �ȵ�.
    * control �� boundary class�� �̿��ؼ� �ش� ����� �����ǵ��� �ؾ� ��.
    */
    char memberType[MAX_STRING], name[MAX_STRING], num[MAX_STRING], id[MAX_STRING], pw[MAX_STRING];

    // �Է� ���� : ȸ�� ����, �̸�, �ֹι�ȣ/����ڹ�ȣ, ID, PW�� ���Ϸκ��� ����
    fscanf(in_fp, "%s %s %s %s %s ", memberType, name, num, id, pw);

    // �ش� ��� ����
    signUpUI::signUp(memberType, name, num, id, pw);

    // ��� ����
    fprintf(out_fp, "1.1. ȸ������\n");
    fprintf(out_fp, "%s %s %s %s\n", name, num, id, pw);
}

void withdrawal() {
    // �ش� ��� ����  
    string id = withdrawalUI::withdrawal();

    // ��� ����
    fprintf(out_fp, "1.2. ȸ��Ż��\n");
    fprintf(out_fp, "%s\n", id.c_str());
}

void login() {
    char id[MAX_STRING], pw[MAX_STRING];

    // �Է� ���� : ID, PW�� ���Ϸκ��� ����
    fscanf(in_fp, "%s %s", id, pw);

    // �ش� ��� ����  
    loginUI::login(id, pw);

    // ��� ����
    fprintf(out_fp, "2.1. �α���\n");
    fprintf(out_fp, "%s %s\n", id, pw);
}

void logout() {
    // �ش� ��� ����  
    string id = logoutUI::logout();
    // ��� ����
    fprintf(out_fp, "2.2. �α׾ƿ�\n");
    fprintf(out_fp, "%s\n", id.c_str());
}

void createNewRecruit() {
    char work[MAX_STRING], deadline[MAX_STRING];
    int num;

    fscanf(in_fp, "%s %d %s", work, &num, deadline);
    AddRecruitInfoUI::createNewRecruit(work, num, deadline);
    fprintf(out_fp, "3.1. ä�� ���� ���\n");
    fprintf(out_fp, "%s %d %s\n", work, num, deadline);
}

void selectRecruitInfo() {
    fprintf(out_fp, "3.2. ��ϵ� ä�� ���� ��ȸ\n");
    vector<Recruitment*> recruitments = RecruitInquiryUI::selectRecruitInfo();

    MemberList* memberList = MemberList::getInstance();
    string loginCompanyName = memberList->getCurrentUser()->getName();
    for (auto recruit : recruitments) {
        if(recruit->getCompany() == loginCompanyName)
            fprintf(out_fp, "%s %d %s\n", recruit->getWork().c_str(), recruit->getNumberOfRecruit(), recruit->getDeadline().c_str());
    }
}

Recruitment* searchRecruitment() {
    fprintf(out_fp, "4.1. ä�� ���� �˻�\n");

    char company[MAX_STRING];

    fscanf(in_fp, "%s", company);

    Member* member = MemberList::getInstance()->getCurrentUser();

    if (typeid(*member) == typeid(NormalMember)) {
        //currentUser�� BizMember�� ��
        vector<Recruitment*> recruitments = GetRecruitmentUI::showRecruitment();

        for (auto recruit : recruitments) {

            if (recruit->getCompany() == company)
            {
                fprintf(out_fp, "%s %s %s %d %s\n", recruit->getCompany().c_str(), recruit->getBizNum().c_str(), recruit->getWork().c_str(), recruit->getNumberOfRecruit(), recruit->getDeadline().c_str());
                return recruit;
            }
        }
    }
}

void apply(Recruitment* recruitment) {
    char biznum[MAX_STRING];
    fscanf(in_fp, "%s", biznum);

    Member* normalmember = MemberList::getInstance()->getCurrentUser();

    if (recruitment->getBizNum() == biznum) {
        ApplyUI::apply(normalmember, recruitment);
        fprintf(out_fp, "4.2. ä�� ����\n");
        fprintf(out_fp, "%s %s %s\n", recruitment->getCompany().c_str(), recruitment->getBizNum().c_str(), recruitment->getWork().c_str());
    }
}

bool cmp(Recruitment*& r1, Recruitment*& r2) {
    if (r1->getCompany() < r2->getCompany()) return true;
    return false;
}

void selectApplyInfo() {
    Member* normalmember = MemberList::getInstance()->getCurrentUser();

    fprintf(out_fp, "4.3. ���� ���� ��ȸ\n");
    vector<ApplyInfo*> applyinfo = ApplyInquiryUI::selectApplyInfo();
    vector<Recruitment*> applyRecruitmentList;
    for (auto apply : applyinfo ) {
        if (apply->getNormalMember()->getId() == normalmember->getId() && apply->getNormalMember()->getPw() == normalmember->getPw()) {
            applyRecruitmentList.push_back(apply->getRecruitment());
        }
    }
    sort(applyRecruitmentList.begin(), applyRecruitmentList.end(), cmp);
    for (auto applyRecruitment : applyRecruitmentList) {
        fprintf(out_fp, "%s %s %s %d %s\n", applyRecruitment->getCompany().c_str(), applyRecruitment->getBizNum().c_str(), applyRecruitment->getWork().c_str(), applyRecruitment->getNumberOfRecruit(), applyRecruitment->getDeadline().c_str());
    }
}

void cancelApplyInfo() {
    char biznum[MAX_STRING];
    fscanf(in_fp, "%s", biznum);

    fprintf(out_fp, "4.4. ���� ���� ���\n");
    Recruitment* canceled = CancelApplyInfoUI::cancelApplyInfo(biznum);
    fprintf(out_fp, "%s %s %s\n", canceled->getCompany().c_str(), canceled->getBizNum().c_str(), canceled->getWork().c_str());
}

void showRecruitNumInfo() {
    fprintf(out_fp, "5.1. ���� ���� ���\n");

    Member* member = MemberList::getInstance()->getCurrentUser();
    if (typeid(*member) == typeid(BizMember)) {
        vector<Recruitment*> recruitments = GetRecruitNumUI::showRecruitNumInfo();
        for (auto recruit : recruitments) {
            if(recruit->getBizNum() == member->getBizNum())
                fprintf(out_fp, "%s %d\n", recruit->getWork().c_str(), recruit->getNumberOfApplicants());
        }
    }
    else if (typeid(*member) == typeid(NormalMember)) {
        map<string, int> mp = GetApplyNumUI::showApplyNumInfo();
        for (auto set : mp) {
            fprintf(out_fp, "%s %d\n", set.first.c_str(), set.second);
        }
    }
}

void program_exit() {
    fprintf(out_fp, "6.1. ����\n");
}