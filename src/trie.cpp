struct trie {
    trie** child;
    bool word;
   
    string* str;

    trie(string* str) {
        child=new trie*[26];
        for(int i=0; i<26; i++)
            child[i]=NULL;
        word=false;
        this->str=str;
    }

    void add(string& str, int pos=0) {
        if(pos == str.length()) {
            word=true;
            return;
        }
        int index=str[pos]-'a';

        string *tmp;
        if(this->str == NULL) tmp=new string();
        else tmp=new string(*this->str);
        (*tmp)+=str[pos];

        if(child[index] == NULL)
            child[index]=new trie(tmp);
        child[index]->add(str,pos+1);
    }

    bool isWord(string& str, int pos=0) {
        if(pos == str.length())
            return word;
        int index=str[pos]-'a';
        if(child[index] == NULL) return false;
        return child[index]->isWord(str,pos+1);
    }
}
