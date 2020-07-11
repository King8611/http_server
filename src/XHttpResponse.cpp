#include"../include/XHttpResponse.h"
#include<iostream>
#include<regex>
#define FILE_PATH "www"
using namespace std;

XHttpResponse::XHttpResponse(){}
XHttpResponse::~XHttpResponse(){}
bool XHttpResponse::SetRequest(string request){
    string pattern="^([A-Z]+) (.+) HTTP/1";
    smatch mas;
    regex r(pattern);
    regex_search(request,mas,r);
    if(mas.size()==0){
        cout<<pattern<<endl;
        return false;
    }
    string type=mas[1];
    string path=mas[2];
    if(type!="GET"){
        return false;
    }
    if(path=="/"){
        path="/index.html";
    }
    path=FILE_PATH+path;
    fp=fopen(path.c_str(),"rb");
    if(fp==NULL){
        return false;
    }
    fseek(fp,0,SEEK_END);
    filesize=ftell(fp);
    fseek(fp,0,0);
    printf("file size is %d\n",filesize);
    return true;
}

string XHttpResponse::GetHead(){
    string rmsg="HTTP/1.1 200OK\r\n";
    rmsg+="Server:XHttp\r\n";
    rmsg+="Content-Type:text/html\r\n";
	rmsg+="Content-Length: ";
	rmsg+=std::to_string(filesize);
	rmsg+="\r\n\r\n";
    return rmsg;
}
int XHttpResponse::Read(char *buf, int bufsize){
    return fread(buf,1,bufsize,fp);
}