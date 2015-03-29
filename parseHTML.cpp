#include<iostream>
#include<string>
#include <fstream>
using namespace std;

int findPosFromBegin(string s, string find){
    for(int i=0; i<s.length(); i++){
        if(s[i]!=find[0]) continue;
        int j=0;
        while(i+j < s.length() && j<find.length()){
            if(s[i+j]!=find[j]){
                j = -1; 
                break;
            }   
            j++;
       }   
       if(j==find.length()) return i;
   }   
   return -1; 
}

int findPosFromEnd(string s, string find){
   for(int i=s.length()-1; i>=0; i--){
       if(s[i]!=find[0]) continue;
       int j=0;
       while(i+j < s.length() && j<find.length()){
            if(s[i+j]!=find[j]){
                j = -1;
                break;
            }
            j++;
       }
       if(j==find.length()) return i;
   }
   return -1;
}
// get problem type
string getProblemType(string s){
    int pos = findPosFromEnd(s, "</td><td>");
    s = s.substr(0, pos);
    pos = findPosFromEnd(s, ">");
    s = s.substr(pos+1,  s.length()-pos);
    return s;
}
// get problem name
string getProblemName(string s){
    int pos =  findPosFromBegin(s, "</a>");
    s = s.substr(0, pos);
    pos = findPosFromEnd(s, ">");
    return s.substr(pos+1,  s.length()-pos);
}
// get problem type
string getProblemLevel(string s){
    int pos =  findPosFromBegin(s, "</a></td><td>");
    s = s.substr(pos+13);
    pos =  findPosFromBegin(s, "</td><td>");
    return s.substr(0, pos);
}
// get problem link
string getProblemLink(string s){
    int pos = findPosFromBegin(s, "v(");
    s = s.substr(pos+2);
    pos = findPosFromBegin(s, ")");
    s = s.substr(0, pos);
    return "http://community.topcoder.com/stat?c=problem_statement&pm=" + s;
}
// get round link
string getProblemRoundLink(string s){
    int pos = findPosFromBegin(s, "q(");
    s = s.substr(pos+2);
    pos = findPosFromBegin(s, ")");
    s = s.substr(0, pos);
    pos = findPosFromBegin(s, ",");
    return "http://community.topcoder.com/stat?c=coder_room_stats&rd="
            + s.substr(0, pos) + "&cr=" + s.substr(pos+1);
}
// get solution link
string getProblemSolutionLink(string s){
    int pos = findPosFromBegin(s, "f(");
    s = s.substr(pos+2);
    pos = findPosFromBegin(s, ")");
    s = s.substr(0, pos);
    pos = findPosFromBegin(s, ",");
    string s1 = s.substr(0, pos);
    s = s.substr(pos+1);
    pos = findPosFromBegin(s, ",");
    return "http://community.topcoder.com/stat?c=problem_solution&rd="+s1
        +"&pm="+s.substr(0, pos)  + "&cr=" + s.substr(pos+1);
}

int main(int argc, char* argv[]){
    string line, s;
    int pos;
    string rowSepStr = "</td></tr><tr>";
    ifstream infile (argv[1]);
    ofstream outfile (argv[2]);
    if (infile.is_open())
    {
        while ( getline (infile,s) )
        {
            cout << s << endl;
            pos = s.find(rowSepStr);
            while (pos!=-1) {
                line = s.substr(0, pos);
                outfile    << getProblemLevel(line) << ","
                << getProblemType(line) << ","
                << getProblemName(line) << ","
                << getProblemLink(line) << ","
                << getProblemRoundLink(line)   << ","
                << getProblemSolutionLink(line) << endl;
                s = s.substr(pos + rowSepStr.length());
                pos = s.find(rowSepStr);
            }
        }
        infile.close();
    }
    outfile.close();
    return 0;
}
