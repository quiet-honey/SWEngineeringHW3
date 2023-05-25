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
            case 1: // "1.1. ȸ������" �޴� �κ�
                signUp();
                break;
            case 2: // "1.2. ȸ��Ż��" �޴� �κ�
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
            case 1: // "2.1. �α���" �޴� �κ�
                login();
                break;
            case 2: // "2.2. �α׾ƿ�" �޴� �κ�
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
            case 1: // "3.1. ä�� ���� ���" �޴� �κ�
                createNewRecruit();
                break;
            case 2: // "3.2. ��ϵ� ä�� ���� ��ȸ" �޴� �κ�
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
            case 1: // "4.1. ä�� ���� �˻�" �޴� �κ�
                searchResult = searchRecruitment();
                break;
            case 2: // "4.2. ä�� ����" �޴� �κ�
                apply(searchResult);
                break;
            case 3: // "4.3. ���� ���� ��ȸ" �޴� �κ�
                selectApplyInfo();
                break;
            case 4: // "4.4. ���� ���" �޴� �κ�
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
            case 1: // "5.1. ���� ���� ���" �޴� �κ�
                showRecruitNumInfo();
                break;
            default:
                break;
            }
            break;
            
        case 6:
            switch (menu_level_2)
            {
            case 1: // "6.1. ����" �޴� �κ�
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

// "1.1. ȸ������"
void signUp() {
    char memberType[MAX_STRING], name[MAX_STRING], num[MAX_STRING], id[MAX_STRING], pw[MAX_STRING];

    // �Է� ���� : ȸ�� ����, �̸�, �ֹι�ȣ/����ڹ�ȣ, ID, PW�� ���Ϸκ��� ����
    fscanf(in_fp, "%s %s %s %s %s ", memberType, name, num, id, pw);

    // Boundary Class ȣ��
    signUpUI::signUp(memberType, name, num, id, pw);
    fprintf(out_fp, "1.1. ȸ������\n");
    fprintf(out_fp, "%s %s %s %s\n", name, num, id, pw);
}

// "1.2. ȸ��Ż��"
void withdrawal() {
    // Boundary Class ȣ��
    string id = withdrawalUI::withdrawal();
    fprintf(out_fp, "1.2. ȸ��Ż��\n");
    fprintf(out_fp, "%s\n", id.c_str());
}

// "2.1. �α���"
void login() {
    char id[MAX_STRING], pw[MAX_STRING];

    // �Է� ���� : ID, PW�� ���Ϸκ��� ����
    fscanf(in_fp, "%s %s", id, pw);

    // Boundary Class ȣ��
    loginUI::login(id, pw);
    fprintf(out_fp, "2.1. �α���\n");
    fprintf(out_fp, "%s %s\n", id, pw);
}

// "2.2. �α׾ƿ�"
void logout() {
    // Boundary Class ȣ��
    string id = logoutUI::logout();
    fprintf(out_fp, "2.2. �α׾ƿ�\n");
    fprintf(out_fp, "%s\n", id.c_str());
}

// "3.1. ä�� ���� ���"
void createNewRecruit() {
    char work[MAX_STRING], deadline[MAX_STRING];
    int num;
    fscanf(in_fp, "%s %d %s", work, &num, deadline);

    // Boundary Class ȣ��
    AddRecruitInfoUI::createNewRecruit(work, num, deadline);
    fprintf(out_fp, "3.1. ä�� ���� ���\n");
    fprintf(out_fp, "%s %d %s\n", work, num, deadline);
}

// "3.2. ��ϵ� ä�� ���� ��ȸ"
void selectRecruitInfo() {
    // Boundary Class ȣ��
    vector<Recruitment*> recruitments = RecruitInquiryUI::selectRecruitInfo();

    MemberList* memberList = MemberList::getInstance(); // ���� �α����� User ����
    string loginCompanyName = memberList->getCurrentUser()->getName();
    fprintf(out_fp, "3.2. ��ϵ� ä�� ���� ��ȸ\n");
    for (auto recruit : recruitments) {
        if(recruit->getCompany() == loginCompanyName) // �α����� ȸ�� ȸ���� ����� ä�� ���� ���
            fprintf(out_fp, "%s %d %s\n", recruit->getWork().c_str(), recruit->getNumberOfRecruit(), recruit->getDeadline().c_str());
    }
}

// "4.1. ä�� ���� �˻�"
Recruitment* searchRecruitment() {
    char company[MAX_STRING];
    // �Է�: ȸ�� �̸�(company)
    fscanf(in_fp, "%s", company);

    Member* member = MemberList::getInstance()->getCurrentUser(); // ���� �α����� User ����

    if (typeid(*member) == typeid(NormalMember)) { // �Ϲ� ȸ���� 4.1. �޴� ���� ����
        // Boundary Class ȣ��
        vector<Recruitment*> recruitments = GetRecruitmentUI::showRecruitment(); // ä�� ���� ����Ʈ �ҷ�����
        fprintf(out_fp, "4.1. ä�� ���� �˻�\n");
        for (auto recruit : recruitments) {
            if (recruit->getCompany() == company) // ä�� ���� ����Ʈ���� ���ϴ� ȸ�� �̸����� �˻�, ���
            {
                fprintf(out_fp, "%s %s %s %d %s\n", recruit->getCompany().c_str(), recruit->getBizNum().c_str(), recruit->getWork().c_str(), recruit->getNumberOfRecruit(), recruit->getDeadline().c_str());
                return recruit;
            }
        }
    }
}

// "4.2. ä�� ����"
void apply(Recruitment* recruitment) {
    char biznum[MAX_STRING];
    fscanf(in_fp, "%s", biznum);

    Member* normalmember = MemberList::getInstance()->getCurrentUser();

    if (recruitment->getBizNum() == biznum) {
        // Boundary Class ȣ��
        ApplyUI::apply(normalmember, recruitment);
        fprintf(out_fp, "4.2. ä�� ����\n");
        fprintf(out_fp, "%s %s %s\n", recruitment->getCompany().c_str(), recruitment->getBizNum().c_str(), recruitment->getWork().c_str());
    }
}

/*
    �Լ� �̸� : cmp()
    ���	  : ȸ�� �̸� ���� �������� ����
    ���� ���� : Recruitment*& (�񱳿� �ʿ��� �� ����)
    ��ȯ��    : bool
*/
bool cmp(Recruitment*& r1, Recruitment*& r2) {
    if (r1->getCompany() < r2->getCompany()) return true;
    return false;
}

// "4.3. ���� ���� ��ȸ"
void selectApplyInfo() {
    Member* normalMember = MemberList::getInstance()->getCurrentUser(); // ���� �α����� User ����

    fprintf(out_fp, "4.3. ���� ���� ��ȸ\n");
    // Boundary Class ȣ��
    vector<ApplyInfo*> applyinfo = ApplyInquiryUI::selectApplyInfo(); // ��� ä�������� ���� ���� applyinfo
    vector<Recruitment*> applyRecruitmentList; // ������ ä�������� ������ vector ���� applyRecruitmentList
    for (auto apply : applyinfo ) {
        if (apply->getNormalMember()->getId() == normalMember->getId() && apply->getNormalMember()->getPw() == normalMember->getPw()) { // ���� �α����� User�� ������ ä��������� vector�� ����
            applyRecruitmentList.push_back(apply->getRecruitment());
        }
    }

    // ȸ�� �̸� ���� �������� ����
    sort(applyRecruitmentList.begin(), applyRecruitmentList.end(), cmp);
    for (auto applyRecruitment : applyRecruitmentList) {
        fprintf(out_fp, "%s %s %s %d %s\n", applyRecruitment->getCompany().c_str(), applyRecruitment->getBizNum().c_str(), applyRecruitment->getWork().c_str(), applyRecruitment->getNumberOfRecruit(), applyRecruitment->getDeadline().c_str());
    }
}

// "4.4. ���� ���"
void cancelApplyInfo() {
    char biznum[MAX_STRING];
    // �Է�: ����ڹ�ȣ(biznum)
    fscanf(in_fp, "%s", biznum);

    fprintf(out_fp, "4.4. ���� ���� ���\n");
    // Boundary Class ȣ��
    Recruitment* canceled = CancelApplyInfoUI::cancelApplyInfo(biznum);
    fprintf(out_fp, "%s %s %s\n", canceled->getCompany().c_str(), canceled->getBizNum().c_str(), canceled->getWork().c_str());
}

// "5.1. ���� ���� ���"
void showRecruitNumInfo() {
    fprintf(out_fp, "5.1. ���� ���� ���\n");

    Member* member = MemberList::getInstance()->getCurrentUser(); // ���� �α����� User ����
    if (typeid(*member) == typeid(BizMember)) { // �α����� User�� ȸ��ȸ���̶��
        // Boundary Class ȣ��
        vector<Recruitment*> recruitments = GetRecruitNumUI::showRecruitNumInfo();
        for (auto recruit : recruitments) {
            if(recruit->getBizNum() == member->getBizNum()) // �ش� ȸ��ȸ���� ����� ��� ä������ ���
                fprintf(out_fp, "%s %d\n", recruit->getWork().c_str(), recruit->getNumberOfApplicants());
        }
    }
    else if (typeid(*member) == typeid(NormalMember)) { // �α����� User�� �Ϲ�ȸ���̶��
        // Boundary Class ȣ��
        map<string, int> mp = GetApplyNumUI::showApplyNumInfo();
        for (auto set : mp) { // �ش� �Ϲ�ȸ���� ������ ä�� ������ map<����, ���� Ƚ��>�� ����, ���
            fprintf(out_fp, "%s %d\n", set.first.c_str(), set.second);
        }
    }
}

// "6.1. ����"
void program_exit() {
    fprintf(out_fp, "6.1. ����\n");
}