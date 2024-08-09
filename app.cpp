#include <bits/stdc++.h>

using namespace std;

vector<string>words;
int cnt [131];
void initcnt();
void letterWeights(string word);
vector<string> findStrongest();
int wordWeight(string word);
void guessAccuracy();

int main (){
    ifstream fin("words.txt", ios::in);
    string input;
    while(fin>>input) words.push_back(input);
    fin.close();
    double total = (double) words.size();
    for(int i = 0; i<6; i++){
        guessAccuracy();
        cout<<"You have eliminated "<< setprecision(4)<<((double)(1- (double)(words.size()) /total) * 100)<< "% of all possible guesses\n";
        if(words.size() == 1) {cout<<"YAY YOU WIN\n"; break;}
        
        for(int i = 0; i<130; i++) cnt[i] = 0;
        for(int j = 0; j<words.size(); j++) letterWeights(words[j]);
        if(i<5){
            cout<<"Your next best guesses are: \n";
            vector<string>ans = findStrongest();
            for(int j = 0; j<3; j++){
                cout<<ans[j]<<"\n";
            }
        }
    }
    return 0;
}
void guessAccuracy(){
    string input, result;
    cin>>input>>result; //result is status of each letter
    //Y for yellow (in word, diff pos), B for blank(not in word), G for green (in word, same pos)
    for(int i = 0; i<5; i++){
        if(result[i] == 'B'){
            for(int j = 0; j<words.size(); j++){
                if(words[j].find(input[i])>=0 && words[j].find(input[i])<5){
                    words.erase(words.begin()+j); j--;
                }
            }
        }
        else if(result[i] == 'Y'){
            for(int j = 0; j<words.size(); j++){
                if(!(words[j].find(input[i])>=0 && words[j].find(input[i])<5) || words[j][i] == input[i]){
                    words.erase(words.begin()+j); j--;
                }
            }
        }
        else {
            for(int j = 0; j<words.size(); j++){
                if(words[j][i] != input[i]){
                    words.erase(words.begin()+j); j--;
                }
            }
        }
    }
}
void letterWeights(string word){
    for(int i = 0; i<5; i++){
        int pos = word[i] - 'a';
        cnt[pos*5+i]++;
    }
}
vector<string> findStrongest(){
    vector<string> bestWords;
    int strength1 = 0,strength2 = 0,strength3 =0;
    string word1, word2, word3;
    for(int i = 0; i<words.size(); i++){
        int s = wordWeight(words[i]);
        if(s > strength1){
            strength1 = s;
            word1 = words[i];
        }
        else if(s > strength2){
            strength2 = s;
            word2 = words[i];
        }
        else if(s>strength3){
            strength3 = s;
            word3 = words[i];
        }
    }
        bestWords.push_back(word1);
        bestWords.push_back(word2);
        bestWords.push_back(word3);
        //cout<<word1<<" "<<word2<<" "<<word3;
    return bestWords;
}

int wordWeight(string word){
    int strength = 0;
    for(int i = 0; i<5; i++){
        int pos = word[i] - 'a';
        strength+= cnt[pos*5+i];
    }
    return strength;
}