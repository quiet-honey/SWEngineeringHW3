#include "member.h"

char* Member::getId()
{
    return id;
}

char* Member::getPw()
{
    return pw;
}

void signUpUI::startInterface()
{
    //cout << "1.1 회占쏙옙 占쏙옙占쏙옙" << "\n";
}

void signUpUI::signUp(char* memberType, char* name, char* num, char* id, char* pw)
{
    signUp::addNewMember(memberType, name, num, id, pw);
}

void signUpUI::signUpSuccess(char* memberType, char* name, char* num, char* id, char* pw)
{
    cout << memberType << " " << name << " " << num << " " << id << " " << pw << "\n";
}

void signUp::addNewMember(char* memberType, char* name, char* num, char* id, char* pw)
{
    if (strcmp(memberType, "1") == 0) {
        BizMember* bMember = new BizMember(name, num, id, pw);
        MemberList* memberList = MemberList::getInstance();
        memberList->addMember(bMember);
        signUpUI::signUpSuccess(memberType, name, num, id, pw);
    }
    else {
        NormalMember* nMember = new NormalMember(name, num, id, pw);
        MemberList* memberList = MemberList::getInstance();
        memberList->addMember(nMember);
        signUpUI::signUpSuccess(memberType, name, num, id, pw);
    }
}

void withdrawalUI::startInterface()
{
    //cout << "1.2 회占쏙옙탈占쏙옙" << "\n";
}

char* withdrawalUI::withdrawal()
{
    return withdrawal::deleteMember();
}

char* withdrawalUI::withdrawalSuccess(char* id)
{
    return id;
}

char* withdrawal::deleteMember()
{
    MemberList* memberList = MemberList::getInstance();
    Member* currentUser = memberList->getCurrentUser();
    if (currentUser != nullptr) {
        memberList->removeMember(currentUser);
        cout << "회원탈퇴 성공 : 회원 ID = " << currentUser->getId() << "\n";
    }
    memberList->setCurrentUser(nullptr);
    return withdrawalUI::withdrawalSuccess(currentUser->getId());
}

void loginUI::startInterface()
{
    //cout << "2.1 占싸깍옙占쏙옙" << "\n";
}

void loginUI::login(char* id, char* pw)
{
    login::loginRequest(id, pw);
}

void loginUI::loginSuccess(char* id, char* pw)
{
    cout << "로그인 완료" << "\n";
    cout << id << " " << pw << "\n";
    MemberList* memberList = MemberList::getInstance();
    cout << "로그인한 유저 ID : " << memberList->getCurrentUser()->getId() << "\n";
}

void loginUI::loginFail()
{
    cout << "일치하지 않는 ID / PW" << "\n";
}

void login::loginRequest(char* id, char* pw)
{
    MemberList* memberList = MemberList::getInstance();
    Member* member = memberList->findMemberById(id);
    if (member != nullptr) {
        // 입력한 PW와 저장된 PW가 일치한다면 로그인 성공
        if (strcmp(member->getPw(), pw) == 0) { 
            memberList->setCurrentUser(member);
            loginUI::loginSuccess(id, pw);
        }
        else loginUI::loginFail(); // 그렇지 않다면 로그인 실패
    }
}

void logoutUI::startInterface()
{
   // cout << "2.2 占싸그아울옙" << "\n";
}

char* logoutUI::logout()
{
    return logout::logoutRequest();
}

char* logoutUI::logoutSuccess(char *id)
{
    return id;
}

char* logout::logoutRequest()
{
    MemberList* memberList = MemberList::getInstance();
    Member* currentUser = memberList->getCurrentUser();
    if (currentUser != nullptr) cout << "로그아웃 성공 : 회원 ID = " << currentUser->getId() << "\n";
    memberList->setCurrentUser(nullptr);
    return logoutUI::logoutSuccess(currentUser->getId());
}

MemberList* MemberList::getInstance(){
    if (!instance) {
        instance = new MemberList();
    }
    return instance;
}

void MemberList::addMember(Member* member)
{
    members.push_back(member);
    cout << "회원가입 성공 : 회원 ID = " << members.back()->getId() << "\n";
}

void MemberList::removeMember(Member* target)
{
    /*for (Member* member : members) {
        if (member->getId() == target->getId()) {
            members.erase(target);
            cout << "회원 삭제 성공 : 회원 ID = " << (*k)->getId() << "\n";
            return;
        }
    }*/
    auto k = find(members.begin(), members.end(), target);
    if (k != members.end()) {
        cout << "회원삭제 성공 : 회원 ID = " << (*k)->getId() << "\n";
        members.erase(k);
    }
    /*for (auto k = members.begin(); k != members.end(); ++k) {
        if ((*k)->getId() == target->getId()) {
            members.erase(k);
            cout << "회원 삭제 성공 : 회원 ID = " << (*k)->getId() << "\n";
            (*k)->~Member();
            return;
        }
    }*/
}

void MemberList::setCurrentUser(Member* member)
{
    currentUser = member;
}

Member* MemberList::getCurrentUser()
{
    return currentUser;
}

Member* MemberList::findMemberById(char* id) {
    for (Member* member : members) {
        if (member->getId() == id) {
            return member;
        }
    }
    return nullptr;
 }
