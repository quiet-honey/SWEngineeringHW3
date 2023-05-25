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

/*
    함수 이름 : MemberList::getInstance()
    기능	  : MemberList를 사용하기 위함
    전달 인자 : 없음
    반환값    : MemberList* -> 싱글톤으로 존재하는 MemberList의 포인터
*/
MemberList* MemberList::getInstance() {
    if (!instance) { // 싱글톤 인스턴스가 존재하지 않으면
        instance = new MemberList(); // 새로운 인스턴스를 만들고
    }
    return instance; // 이미 존재한다면 단순히 반환해줌
}

/*
    함수 이름 : MemberList::addMember()
    기능	  : MemberList에 새로운 Member를 추가하기 위함
    전달 인자 : Member* -> MemberList에 추가할 Member의 포인터
    반환값    : 없음
*/
void MemberList::addMember(Member* member)
{
    members.push_back(member); // members에 member를 추가
}

/*
    함수 이름 : MemberList::removeMember()
    기능	  : MemberList에서 Member를 제거하기 위함
    전달 인자 : Member* -> MemberList에 제거할 Member의 포인터
    반환값    : 없음
*/
void MemberList::removeMember(Member* target)
{
    auto k = find(members.begin(), members.end(), target); // members에서 삭제를 원하는 member를 찾고
    if (k != members.end()) { // 존재한다면
        members.erase(k); // 그 member를 삭제
    }
}

/*
    함수 이름 : MemberList::setCurrentUser()
    기능	  : 현재 로그인 중인 Member를 저장하기 위함
    전달 인자 : Member* -> 로그인 중으로 처리할 Member의 포인터
    반환값    : 없음
*/
void MemberList::setCurrentUser(Member* member)
{
    currentUser = member;
}

Member* MemberList::getCurrentUser()
{
    return currentUser;
}

/*
    함수 이름 : MemberList::findMemberById()
    기능	  : MemberList에서 Id를 사용해 해당 Member를 찾기 위함
    전달 인자 : const string& -> 찾고자 하는 Member의 Id
    반환값    : Member* -> 찾은 Member의 포인터
*/
Member* MemberList::findMemberById(const string& id) {
    for (Member* member : members) { // members를 순회하면서
        if (member->getId() == id) { // id가 일치하는
            return member; // Member를 반환
        }
    }
    return nullptr; // 존재하지 않는다면 nullpointer 반환
}

/*
    함수 이름 : signUpUI::signUp()
    기능	  : 회원가입 진행을 위해 Control Class의 addNewMember() 호출
    전달 인자 : const string& -> 회원 가입에 필요한 정보들
    반환값    : 없음
*/
void signUpUI::signUp(const string& memberType, const string& name, const string& num, const string& id, const string& pw)
{
    signUp::addNewMember(memberType, name, num, id, pw);
}

/*
    함수 이름 : signUpUI::signUp()
    기능	  : 회원가입이 완료됨
    전달 인자 : const string& -> 회원 가입에 사용된 정보들
    반환값    : 없음
*/
void signUpUI::signUpSuccess(const string& memberType, const string& name, const string& id)
{
    if (memberType == "1") cout << "새로운 회사 회원가입 완료\n" << "회사 이름 : " << name << " " << "\n회원 ID : " << id << "\n";
    else cout << "새로운 일반 회원가입 완료\n" << "회원 이름 : " << name << " " << "\n회원 ID : " << id << "\n";
}

/*
    함수 이름 : signUp::addNewMember()
    기능	  : 회원 유형에 맞춰 회원가입을 진행하고, 회원가입이 완료됨을 사용자에게 알리기 위해 Boundary Class의 signUpSuccess() 호출
    전달 인자 : const string& -> 회원 가입 시 사용할 정보들
    반환값    : 없음
*/
void signUp::addNewMember(const string& memberType, const string& name, const string& num, const string& id, const string& pw)
{
    MemberList* memberList = MemberList::getInstance(); // Member를 저장할 MemberList 인스턴스
    if (memberType == "1") { // 회사 회원
        BizMember* bMember = new BizMember(name, num, id, pw); // 회사 회원 생성
        memberList->addMember(bMember); // 저장
        signUpUI::signUpSuccess(memberType, name, id); // 회원가입 완료
    }
    else { // 일반 회원
        NormalMember* nMember = new NormalMember(name, num, id, pw); // 일반 회원 생성
        memberList->addMember(nMember); // 저장
        signUpUI::signUpSuccess(memberType, name, id); // 회원가입 완료
    }
}

/*
    함수 이름 : withdrawalUI::withdrawal()
    기능	  : 회원탈퇴 진행을 위해 Control Class의 deleteMember() 호출
    전달 인자 : 없음
    반환값    : string -> 회원탈퇴한 Member의 Id
*/
string withdrawalUI::withdrawal()
{
    return withdrawal::deleteMember();
}

/*
    함수 이름 : withdrawalUI::withdrawalSuccess()
    기능	  : 회원탈퇴가 완료됨
    전달 인자 : const string& -> 회원탈퇴 완료한 Member의 Id
    반환값    : string -> 회원탈퇴한 Member의 Id
*/
string withdrawalUI::withdrawalSuccess(const string& id)
{
    return id;
}

/*
    함수 이름 : withdrawal::deleteMember()
    기능	  : 회원 탈퇴를 진행하고, 회원탈퇴가 완료됨을 사용자에게 알리기 위해 Boundary Class의 withdrawalSuccess() 호출
    전달 인자 : 없음
    반환값    : string -> 회원탈퇴한 Member의 Id
*/
string withdrawal::deleteMember()
{
    MemberList* memberList = MemberList::getInstance(); // Member를 저장할 MemberList 인스턴스
    Member* currentUser = memberList->getCurrentUser(); // 현재 로그인 중인 Member
    string targetId = currentUser->getId(); // 회원탈퇴를 진행할 Member의 Id
    if (currentUser != nullptr) { // 현재 로그인 중인지 체크
        memberList->removeMember(currentUser); // 현재 로그인 중인 Member 회원 탈퇴 진행
    }
    memberList->setCurrentUser(nullptr); // 회원 탈퇴하였으므로 현재 로그인 중인 Member는 없음
    return withdrawalUI::withdrawalSuccess(targetId); // 회원 탈퇴 완료
}

/*
    함수 이름 : loginUI::login()
    기능	  : 로그인 진행을 위해 Control Class의 loginRequest() 호출
    전달 인자 : const string& -> 로그인에 사용될 id와 pw
    반환값    : 없음
*/
void loginUI::login(const string& id, const string& pw)
{
    login::loginRequest(id, pw);
}

/*
    함수 이름 : loginUI::loginSuccess()
    기능	  : 로그인이 완료됨
    전달 인자 : 없음
    반환값    : 없음
*/
void loginUI::loginSuccess()
{
    MemberList* memberList = MemberList::getInstance();
    cout << "로그인한 유저 ID : " << memberList->getCurrentUser()->getId() << "\n";
}

/*
    함수 이름 : loginUI::loginFail()
    기능	  : 로그인에 실패함
    전달 인자 : 없음
    반환값    : 없음
*/
void loginUI::loginFail()
{
    cout << "일치하지 않는 ID / PW\n";
}

/*
    함수 이름 : login::loginRequest()
    기능	  : 로그인을 진행하고, ID/PW가 일치한다면 로그인이 성공함을 사용자에게 알리기 위해 Boundary Class의 loginSuccess() 호출 (만약 불일치한다면, loginFail() 호출)
    전달 인자 : const string& -> 로그인 시 사용할 정보들
    반환값    : 없음
*/
void login::loginRequest(const string& id, const string& pw)
{
    MemberList* memberList = MemberList::getInstance(); // Member를 저장할 MemberList 인스턴스
    Member* member = memberList->findMemberById(id); // Id로 로그인을 시도하는 member
    if (member != nullptr) { // 존재하는 member라면
        if (member->getPw() == pw) { // 입력받은 pw와 그 member의 pw가 일치하는지 확인
            memberList->setCurrentUser(member); // 로그인 중인 member로 설정
            loginUI::loginSuccess(); // 로그인 완료
        }
        else loginUI::loginFail(); // 그렇지 않다면 로그인 실패
    }
}

/*
    함수 이름 : logoutUI::logout()
    기능	  : 로그인 진행을 위해 Control Class의 loginRequest() 호출
    전달 인자 : 없음
    반환값    : string -> 로그아웃한 member의 Id
*/
string logoutUI::logout()
{
    return logout::logoutRequest();
}

/*
    함수 이름 : logoutUI::logoutSuccess()
    기능	  : 로그아웃에 성공함
    전달 인자 : const string& -> 로그아웃한 member의 Id
    반환값    : string -> 로그아웃한 member의 Id
*/
string logoutUI::logoutSuccess(const string& id)
{
    return id;
}

/*
    함수 이름 : logout::logoutRequest)
    기능	  : 로그아웃을 진행하고, 로그아웃이 성공한다면 Boundary Class의 loginSuccess() 호출
    전달 인자 : 없음
    반환값    : string -> 로그아웃한 member의 Id
*/
string logout::logoutRequest()
{
    MemberList* memberList = MemberList::getInstance(); // Member를 저장할 MemberList 인스턴스
    Member* currentUser = memberList->getCurrentUser(); // 현재 로그인 중인 Member
    string targetId = currentUser->getId(); // 로그아웃을 진행할 Member의 Id
    if (currentUser != nullptr) { // 현재 로그인 중인지 체크
        memberList->setCurrentUser(nullptr); // 로그아웃 진행
    }
    return logoutUI::logoutSuccess(targetId); // 로그아웃 성공
}