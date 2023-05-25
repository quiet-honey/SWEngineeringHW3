#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 회사 회원과 일반 회원의 부모 클래스인 회원 클래스
class Member {
protected:
    string name; // 회원 이름
    string id; // 회원 Id
    string pw; // 회원 PW
public:
    const string& getName();
    const string& getId();
    const string& getPw();

    Member(const string& name, const string& id, const string& pw)
        : name(name), id(id), pw(pw) {}
    virtual const string& getBizNum(); // 가상 함수
};

// 일반 회원 클래스
class NormalMember : public Member {
private:
    string ssn; // 주민번호
public:
    NormalMember(const string& name, const string& ssn, const string& id, const string& pw)
        : Member(name, id, pw), ssn(ssn) {}
};

// 회사 회원 클래스
class BizMember : public Member {
private:
    string bizNum; // 사업자번호
public:
    BizMember(const string& name, const string& bizNum, const string& id, const string& pw)
        : Member(name, id, pw), bizNum(bizNum) {}
    const string& getBizNum() override; // 오버라이딩
};

// 채용 서비스의 회원들을 저장하고, 현재 로그인 중인 회원을 저장하고 있는 클래스
class MemberList {
private:
    vector<Member*> members; // 회원가입한 회원들이 저장될 Vector
    Member* currentUser; // 현재 로그인 중인 Member
    static MemberList* instance; // MemberList가 프로젝트에서 싱글톤으로 사용되기 위함

    MemberList() {} // 생성자를 private으로 두어, 아무나 MemberList를 생성하지 못하게 함

public:
    static MemberList* getInstance(); // MemberList의 인스턴스 반환
    void addMember(Member* member); // MemberList에 회원 추가
    void removeMember(Member* member); // MemberList에서 회원 삭제
    void setCurrentUser(Member* member); // 현재 로그인 중인 Member 설정
    Member* getCurrentUser(); // 현재 로그인 중인 Member 반환
    Member* findMemberById(const string& id); // Id를 통해 Member 찾기
};

// 회원가입 Boundary 클래스
class signUpUI
{
public:
    static void signUp(const string& memberType, const string& name, const string& num, const string& id, const string& pw);
    static void signUpSuccess(const string& memberType, const string& name, const string& id);
};

// 회원가입 Control 클래스
class signUp {
public:
    static void addNewMember(const string& memberType, const string& name, const string& num, const string& id, const string& pww);
};

// 회원탈퇴 Boundary 클래스
class withdrawalUI {
public:
    static string withdrawal();
    static string withdrawalSuccess(const string& id);
};

// 회원탈퇴 Control 클래스
class withdrawal {
public:
    static string deleteMember();
};

// 로그인 Boundary 클래스
class loginUI {
public:
    static void login(const string& id, const string& pw);
    static void loginSuccess();
    static void loginFail();
};

// 로그인 Control 클래스
class login {
public:
    static void loginRequest(const string& id, const string& pw);
};

// 로그아웃 Boundary 클래스
class logoutUI {
public:
    static string logout();
    static string logoutSuccess(const string& id);
};

// 로그아웃 Control 클래스
class logout {
public:
    static string logoutRequest();
};