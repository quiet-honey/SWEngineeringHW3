#include "member.h"


const string& Member::getName()
{
    return name;
}

const string& Member::getId()
{
    return id;
}

const string& Member::getPw()
{
    return pw;
}

void Member::putRegistration(const ApplyInfo& applyInfo) {
    applyInfos.push_back(applyInfo);
}

ApplyInfo Member::removeApplyInfo(string bizNum) {

    ApplyInfo cancelledInfo("", "", "", 0, "");

    for (auto it = applyInfos.begin(); it != applyInfos.end(); it++) {
        if (it->getBizNum() == bizNum) {
            cancelledInfo.setCompanyName(it->getCompanyName());  // ȸ�� �̸� ����
            cancelledInfo.setbizNum(it->getBizNum());  // bizNum ����
            cancelledInfo.setWork(it->getWork());  // �۾� ����
            cancelledInfo.setNumOfPeople(it->getNumOfPeople());  // �ο� �� ����
            cancelledInfo.setDeadline(it->getDeadline());  // ������ ����
            applyInfos.erase(it);
            break;
        }
    }

    return cancelledInfo;
}
//vector<ApplyInfo>& applyInfos
map<string, int> Member::getApplyNum() {
    map<string, int> workCountMap;

    for (ApplyInfo& a : applyInfos) {
        const string& work = a.getWork();

        if (workCountMap.find(work) == workCountMap.end()) {
            workCountMap[work] = 1;
        }
        else workCountMap[work]++;
    }

    return workCountMap;
}


const string& NormalMember::getNum()
{
    return ssn;
}

const string& BizMember::getNum()
{
    return bizNum;
}

MemberList* MemberList::getInstance() {
    if (!instance) {
        instance = new MemberList();
    }
    return instance;
}

void MemberList::addMember(Member* member)
{
    members.push_back(member);
    cout << "ȸ��(ID = " << members.back()->getId() << ") DB�� ���� ����\n";
}

void MemberList::removeMember(Member* target)
{
    auto k = find(members.begin(), members.end(), target);
    if (k != members.end()) {
        members.erase(k);
        cout << "ȸ��(ID = " << target->getId() << ") DB���� ���� ����\n";
    }
    // printAllMembers();
}

void MemberList::setCurrentUser(Member* member)
{
    currentUser = member;
}

Member* MemberList::getCurrentUser()
{
    return currentUser;
}

Member* MemberList::findMemberById(const string& id) {
    for (Member* member : members) {
        if (member->getId() == id) {
            return member;
        }
    }
    return nullptr;
}

/*void MemberList::printAllMembers()
{
    for (Member* member : members) {
        cout << "ID: " << member->getId() << "\n";
        cout << "PW: " << member->getPw() << "\n";
        cout << "-------------------------" << "\n";
    }
}*/

void signUpUI::startInterface()
{
    cout << "1.1. ȸ������\n";
}

void signUpUI::signUp(const string& memberType, const string& name, const string& num, const string& id, const string& pw)
{
    startInterface();
    signUp::addNewMember(memberType, name, num, id, pw);
}

void signUpUI::signUpSuccess(const string& memberType, const string& name, const string& id)
{
    if (memberType == "1") cout << "���ο� ȸ�� ȸ������ �Ϸ�\n" << "ȸ�� �̸� : " << name << " " << "\nȸ�� ID : " << id << "\n";
    else cout << "���ο� �Ϲ� ȸ������ �Ϸ�\n" << "ȸ�� �̸� : " << name << " " << "\nȸ�� ID : " << id << "\n";

}

void signUp::addNewMember(const string& memberType, const string& name, const string& num, const string& id, const string& pw)
{
    MemberList* memberList = MemberList::getInstance();
    if (memberType == "1") {
        BizMember* bMember = new BizMember(name, num, id, pw);
        memberList->addMember(bMember);
        signUpUI::signUpSuccess(memberType, name, id);
    }
    else {
        NormalMember* nMember = new NormalMember(name, num, id, pw);
        memberList->addMember(nMember);
        signUpUI::signUpSuccess(memberType, name, id);
    }
    // memberList->printAllMembers();
}

void withdrawalUI::startInterface()
{
    cout << "1.2. ȸ��Ż��\n";
}

string withdrawalUI::withdrawal()
{
    startInterface();
    return withdrawal::deleteMember();
}

string withdrawalUI::withdrawalSuccess(const string& id)
{
    return id;
}

string withdrawal::deleteMember()
{
    MemberList* memberList = MemberList::getInstance();
    Member* currentUser = memberList->getCurrentUser();
    string targetId = currentUser->getId();
    if (currentUser != nullptr) {
        memberList->removeMember(currentUser);
        cout << "ȸ��(ID = " << targetId << ") ȸ��Ż�� ����\n";
    }
    memberList->setCurrentUser(nullptr);
    return withdrawalUI::withdrawalSuccess(targetId);
}

void loginUI::startInterface()
{
    cout << "2.1. �α���\n";
}

void loginUI::login(const string& id, const string& pw)
{
    startInterface();
    login::loginRequest(id, pw);
}

void loginUI::loginSuccess(const string& id, const string& pw)
{
    cout << "�α��� �Ϸ�\n";
    // cout << id << " " << pw << "\n";
    MemberList* memberList = MemberList::getInstance();
    cout << "�α����� ���� ID : " << memberList->getCurrentUser()->getId() << "\n";
}

void loginUI::loginFail()
{
    cout << "��ġ���� �ʴ� ID / PW\n";
}

void login::loginRequest(const string& id, const string& pw)
{
    MemberList* memberList = MemberList::getInstance();
    Member* member = memberList->findMemberById(id);
    if (member != nullptr) {
        // �Է��� PW�� ����� PW�� ��ġ�Ѵٸ� �α��� ����
        if (member->getPw() == pw) {
            memberList->setCurrentUser(member);
            loginUI::loginSuccess(id, pw);
        }
        else loginUI::loginFail(); // �׷��� �ʴٸ� �α��� ����
    }
}

void logoutUI::startInterface()
{
    cout << "2.2. �α׾ƿ�\n";
}

string logoutUI::logout()
{
    startInterface();
    return logout::logoutRequest();
}

string logoutUI::logoutSuccess(const string& id)
{
    return id;
}

string logout::logoutRequest()
{
    MemberList* memberList = MemberList::getInstance();
    Member* currentUser = memberList->getCurrentUser();
    string targetId = currentUser->getId();
    if (currentUser != nullptr) {
        memberList->setCurrentUser(nullptr);
        cout << "ȸ��(ID = " << targetId << ") �α׾ƿ� ����\n";
    }
    else "�α׾ƿ� ����\n";
    return logoutUI::logoutSuccess(targetId);
}