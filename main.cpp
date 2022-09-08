#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <cctype>
#include <algorithm>
#include <conio.h>
#include <ctype.h>
using namespace std;

#pragma region

class Times{
    public:
        void timeset(int hour, int min, int sec);
        void timeshow(); 
    private: 
        int min;
        int hour;
        int sec;
};

Times T;

void printm() {
	cout << "***********************************"<< endl;
	cout << "*     The Program is Running      *"<< endl;
	cout << "***********************************"<< endl;
	cout << "*           ^(Q(oo)Q)^            *"<< endl;
	cout << "***********************************"<< endl;
	cout << "* 1.Timed Logout                  *"<< endl;
	cout << "* 2.Timed Shutdown                *"<< endl;
	cout << "* 3.Timed Restart                 *"<< endl;
	cout << "* 4.Shutdown immediately          *"<< endl;
	cout << "* 5.exit                          *"<< endl;
    cout << "***********************************"<< endl;
}

bool tiquan(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    //打开当前进程的权限令牌
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) 
        return false;

    //获得某一特定权限的权限标识LUID，保存在tkp中
    //查看里面的权限
    //第一个参数：NULL表示要查看的是当前本地系统
    //第二个参数：指定特权名称
    //第三个参数：用来接收返回的特权名称信息
    if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid)) 
        return false;

    //设置特权数组的个数
    tkp.PrivilegeCount = 1;
    //SE_PRIVILEGE_ENABLE_BY_DEFAULT    特权默认启动
    //SE_PRIVILEGE_ENABLED              特权启动
    //SE_PRIVILEGE_USER_FOR_ACCESS      用来访问一个对象或者服务
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;    //特权启动
    
    //调用AdjustTokenPrivileges来提升我们需要的系统权限
    //修改令牌的权限
    //第一个参数：调整特权的句柄
    //第二个参数：禁止所有权限表示
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, NULL, NULL, NULL)) 
        return false;

    return true;
}

void Times::timeshow(){
    cout<<"Countdown "<<hour<<":"<<min<<":"<<sec<<endl;
}

void Times::timeset(int h, int m, int s){
    hour=h;
    min=m;
    sec=s; 
}

void countdown(int h, int m, int s){
    while(true){
        T.timeset(h, m, s);
        T.timeshow();
        //1000毫秒为1秒
        Sleep(1000);
        s--;
        if(s<=0){
            s=59;
            m--;
            if(m<=0){
                m=59;
                h--;
                if(h<=0){
                    cout<<"Good Bye!"<<endl;
                    break;
                }
            }
        }
    }
}

//关机
bool shutdown(){
    if (!tiquan() || !ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION)) 
        return false;
    return true;
}

//注销
bool logoutc(){
    if (!tiquan() || !ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION)) 
        return false;
    return true;
}

//重启
bool restartc(){
    if (!tiquan() || !ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION)) 
        return false;
    return true;
}

void exitt(){
    int count=0;
    string pig="I am a pig";
    string upig;
    cout<<"Please enter 'I am a pig' to exit the program."<<endl;
    cout<<"                         ^(Q(oo)Q)^                      "<<endl; 
    getline(cin, upig);
    for (int i = 0; i < pig.length(); i++) {
        if (upig[i] != pig[i]) {
            cout << "Please type:" << endl;
            getline(cin, upig);
        }
        if (upig[i] == pig[i]) {
            exit(0);
        }
    }
}

int main() {
    
	int choice;
    int h;
    int m;
    int s;
	printm();
    cout << "Please Choose the Function Number :   ";
	while (true) {
        cin >> choice;
		while (choice == 1) {
            cout<<"Please enter how long after(hours): ";
            cin>>h;
            cout<<"Please enter how long after(min): ";
            cin>>m;
            cout<<"Please enter how long after(sec): ";    
            cin>>s;  
            
            countdown(h,m,s);

            if(!logoutc()){
                cout<<"Process Error!"<<endl;
                continue;
            }

            break;
        }
		while (choice == 2) {
            cout<<"Please enter how long after(hours): ";
            cin>>h;
            cout<<"Please enter how long after(min): ";
            cin>>m;
            cout<<"Please enter how long after(sec): ";    
            cin>>s; 

            countdown(h,m,s);

            if(!shutdown()){
                cout<<"Process Error!"<<endl;
                continue;
            }

            break;
        }
		while (choice == 3) {
            cout<<"Please enter how long after(hours): ";
            cin>>h;
            cout<<"Please enter how long after(min): ";
            cin>>m;
            cout<<"Please enter how long after(sec): ";    
            cin>>s; 

            countdown(h,m,s);

            if(!restartc()){
                cout<<"Process Error!"<<endl;
                continue;
            }

            break;
        }
		while (choice == 4) {
            char y;
            cout<<"Are you sure you want to shut down IMMEDIATELY? (y/n) ";
            cin>>y;
            if(y>='A' && y<='Z'){
                y=y+32;
            }
            if(y== 'y'){
                if(!shutdown()){
                    cout<<"Process Error!"<<endl;
                    continue;
                }
            }
            if(y=='n'){
                break;
            }

        }
        while (choice == 5) {exitt();}
        cout<<"Please enter the selected number again :  ";
	}
}