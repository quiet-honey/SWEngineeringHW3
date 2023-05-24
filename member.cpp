
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

const string& Member::getBizNum()
{
    throw logic_error("일반 회원입니다.");
}

const string& BizMember::getBizNum()
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
    cout << "회원(ID = " << members.back()->getId() << ") DB에 저장 성공\n";
}

void MemberList::removeMember(Member* target)
{
    auto k = find(members.begin(), members.end(), target);
    if (k != members.end()) {
        members.erase(k);
        cout << "회원(ID = " << target->getId() << ") DB에서 삭제 성공\n";
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
    cout << "1.1. 회원가입\n";
}

void signUpUI::signUp(const string& memberType, const string& name, const string& num, const string& id, const string& pw)
{  
    startInterface();
    signUp::addNewMember(memberType, name, num, id, pw);
}

void signUpUI::signUpSuccess(const string& memberType, const string& name, const string& id)
{
    if(memberType == "1") cout << "새로운 회사 회원가입 완료\n" << "회사 이름 : " << name << " " << "\n회원 ID : " << id << "\n";
    else cout << "새로운 일반 회원가입 완료\n" << "회원 이름 : " << name << " " << "\n회원 ID : " << id << "\n";

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
    cout << "1.2. 회원탈퇴\n";
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
    // cout << "TEST : " << currentUser->getName() << "\n";
    BizMember* bizMember = dynamic_cast<BizMember*>(currentUser);
    if (bizMember != nullptr) {
        const string& bizNum = bizMember->getBizNum();
        // bizNum 사용
        cout << bizNum << "\n";
    }
    string targetId = currentUser->getId();
    if (currentUser != nullptr) {
        memberList->removeMember(currentUser);
        cout << "회원(ID = " << targetId << ") 회원탈퇴 성공\n";
    }
    memberList->setCurrentUser(nullptr);
    return withdrawalUI::withdrawalSuccess(targetId);
}

void loginUI::startInterface()
{
    cout << "2.1. 로그인\n";
}

void loginUI::login(const string& id, const string& pw)
{
    startInterface();
    login::loginRequest(id, pw);
}

void loginUI::loginSuccess(const string& id, const string& pw)
{
    cout << "로그인 완료\n";
    // cout << id << " " << pw << "\n";
    MemberList* memberList = MemberList::getInstance();
    cout << "로그인한 유저 ID : " << memberList->getCurrentUser()->getId() << "\n";
}

void loginUI::loginFail()
{
    cout << "일치하지 않는 ID / PW\n";
}

void login::loginRequest(const string& id, const string& pw)
{
    MemberList* memberList = MemberList::getInstance();
    Member* member = memberList->findMemberById(id);
    if (member != nullptr) {
        // 입력한 PW와 저장된 PW가 일치한다면 로그인 성공
        if (member->getPw() == pw) {
            memberList->setCurrentUser(member);
            loginUI::loginSuccess(id, pw);
        }
        else loginUI::loginFail(); // 그렇지 않다면 로그인 실패
    }
}

void logoutUI::startInterface()
{
    cout << "2.2. 로그아웃\n";
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
        cout << "회원(ID = " << targetId << ") 로그아웃 성공\n";
    }
    else "로그아웃 실패\n";
    return logoutUI::logoutSuccess(targetId);
}