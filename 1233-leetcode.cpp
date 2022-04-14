#include<bits/stdc++.h>
using namespace std;
/**
 *  1. Sorted the folders based on length 
 *  2. Constructed a trie for all the folders
 * 
 *
 * 
 *  
**/

class Solution {
public:
    class Folder {
     public:
        string name;
        unordered_map<string,Folder*> childs;
        bool empty;
        Folder(string name){
            this->name = name;
            this->empty = false;
        } 
    };
    class Trie {
    public:
        Folder* root;
        Trie(){
            root = new Folder("/");
        }
        void add(vector<string>&s){

            Folder* p = root;
            for(int i=0;i<s.size();i++){
                if(p->childs.find(s[i]) == p->childs.end()){
                    Folder* nf = new Folder(s[i]);
                    p->childs[s[i]] = nf;
                    p = p->childs[s[i]];
                }else {
                    p = p->childs[s[i]];
                }
            }
            p->empty = true;
        }
        void remove(vector<string> &s){
            Folder *p = root;
            for(int i=0;i<s.size();i++){
                p = p->childs[s[i]];
            }
            p->childs.clear();
            p->empty = true;
        }
        void dfs(Folder* root,string s,vector<string>&ans){
            string str = root->name;
            if(root->childs.size() == 0){
                ans.push_back(s);
            }
            for(auto [c,f] : root->childs){
                dfs(f,s +'/' + c,ans);
            }
        }
    };
    vector<string> getFolders(string &s){
        vector<string>tokens;
        string word= "";
        for(int i=0;i<s.length();i++){
            if(s[i] == '/'){
                if(word.length()>0){
                    tokens.push_back(word);
                    word = "";
                }
            }else {
                word+=s[i];
            }
        }
        if(word.length()>0){
            tokens.push_back(word);
            word = "";
        }
        return tokens;
    }
    vector<string> removeSubfolders(vector<string>& folder) {
        
        sort(folder.begin(),folder.end(),[&](const string &s1,const string &s2){
           return s1.length()>s2.length(); 
        });
        
        Trie* trie = new Trie();
        for(int i=0;i<folder.size();i++){
            vector<string> f = getFolders(folder[i]);
            trie->add(f);
            trie->remove(f);
        }
        vector<string>ans;
        trie->dfs(trie->root,"",ans);
        return ans;
    }
};