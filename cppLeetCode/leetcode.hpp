//
// Created by xcoderliu on 3/30/22.
//

#ifndef CPLUS_LEETCODE_HPP
#define CPLUS_LEETCODE_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <algorithm>

#pragma mark - common

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template<typename K, typename V>
bool CompareMap(const unordered_map<K, V>& map1, const unordered_map<K, V>& map2)
{
    if (map1.size() != map2.size())
    {
        return false;
    }

    for (auto iter1 : map1)
    {
        auto iter2 = map2.find(iter1.first);
        if (iter2 == map2.end())
        {
            return false;
        }
        else
        {
            if (iter1.second != iter2->second)
            {
                return false;
            }
        }
    }

    return true;
}

using namespace std;

#pragma mark - string

bool isAlphaOrNum(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        return true;
    }
    return false;
}

// https://leetcode-cn.com/problems/valid-palindrome/
bool isPalindrome(string s) {
    int l = 0;
    int r = (int)s.size() - 1;
    while (l < r) {
        while ((!isAlphaOrNum(tolower(s.at(l)))) && l + 1 <= r) {
            l++;
        }
        char leftValue = tolower(s.at(l));
        while ((!isAlphaOrNum(tolower(s.at(r)))) && r - 1 >= 0) {
            r--;
        }
        char rightValue = tolower(s.at(r));
        cout << leftValue << " : " << rightValue << endl;
        if (leftValue != rightValue && isAlphaOrNum(leftValue) && isAlphaOrNum(rightValue)) {
            return false;
        } else {
            l++;
            r--;
        }
    }
    return true;
}

// https://leetcode-cn.com/problems/reverse-string/
void reverseString(vector<char> &s) {
    int l = 0;
    int r = (int)s.size() - 1;
    while (l < r) {
        swap(s[l++], s[r--]);
    }
}

bool isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
        || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return true;
    }
    return false;
}

// https://leetcode-cn.com/problems/reverse-vowels-of-a-string/
string reverseVowels(string s) {
    int l = 0;
    int r = (int)s.size() - 1;
    while (l < r) {
        while (!isVowel(s.at(l)) && l + 1 < r) {
            l++;
        }
        while (!isVowel(s.at(r)) && r - 1 >= 0) {
            r--;
        }
        if (isVowel(s.at(l)) && isVowel(s.at(r))) {
            swap(s.at(l), s.at(r));
        }
        if (l + 1 < r) {
            l++;
        }
        if (r - 1 >= 0) {
            r--;
        }
    }
    return s;
}

// https://leetcode-cn.com/problems/valid-anagram/
bool isAnagram(string s, string t) {
    if( t.length() != s.length()) {
        return false;
    }
    int models[256] = {0};
    int modelt[256] = {0};
    for (int i = 0; i < s.length(); ++i) {
        models[s[i]]++;
        modelt[t[i]]++;
    }
    return 0 == memcmp(models, modelt, sizeof(int) * 256);
}

// https://leetcode-cn.com/problems/word-pattern/
bool wordPattern(string pattern, string s) {
    unordered_map<string, char> record;
    if (pattern.size() && s.size()) {
        string key;
        stringstream ss;
        vector<char> allValues;
        ss << s;
        int i = 0;
        while (getline(ss, key, ' ')) {
            if (i <= pattern.size() - 1) {
                char value = pattern.at(i++);
                auto iter = record.find(key);
                if (iter == record.end()) // not find
                    if (find(allValues.begin(), allValues.end(), value) == allValues.end()) {
                        record[key] = value;
                        allValues.push_back(value);
                    } else
                        return false;
                else { // find
                    if(iter->second != value)
                        return false;
                }
            } else {
                return false;
            }
        }
        if (i != pattern.size()) {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

// --------------------------- Medium -------------------------------------

// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(string s) {
    int start = 0;
    int end = -1;
    int result = 0;
    int temp[256] = {0};
    while (start < s.length()) {
        if (end + 1 < s.length() && temp[s[end + 1]] == 0) {
            temp[s[++end]]++;
        } else {
            temp[s[start++]]--;
        }
        result = max(end - start + 1, result);
    }
    return result;
}

// https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
vector<int> findAnagrams(string s, string p) {
    vector<int>res;
    int checkmodel[256] = {0};
    for( char c : p) {
        checkmodel[c]++;
    }
    int start = 0;
    int end = -1;
    int curmodel[256] = {0};
    while (start < s.length()) {
        if (end + 1 < s.length() && curmodel[s[end + 1]] < checkmodel[s[end+1]])
            curmodel[s[++end]]++;
        else
            curmodel[s[start++]]--;
        if (0 == memcmp(curmodel,checkmodel,sizeof(int) * 256))
            res.push_back(start);
    }
    return res;
}

#pragma mark - stack set array map

// https://leetcode-cn.com/problems/valid-parentheses/
bool isValid(string s) {
    stack<char> temp;
    for(int i = 0; i < s.size(); i++) {
        char c = s.at(i);
        if(c == '(' || c == '{' || c == '[') {
            temp.push(c);
        } else {
            if (temp.size() == 0) {
                return false;
            }
            char check = temp.top();
            if(c == ')') {
                if (check != '(') {
                    return false;
                }
            } else if(c == ']') {
                if (check != '[') {
                    return false;
                }
            } else if(c == '}') {
                if (check != '{') {
                    return false;
                }
            }
            temp.pop();
        }
    }
    if (temp.size() != 0){
        return false;
    }
    return true;
}

// https://leetcode-cn.com/problems/move-zeroes/
void moveZeroes(vector<int> &nums) {
    int k = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i])
            nums[k++] = nums[i];
    }
    for (int i = k; i < nums.size(); ++i) {
        nums[i] = 0;
    }
}

// https://leetcode.cn/problems/JFETK5/
string addBinary(string a, string b) {
    vector<int> va;
    vector<int> vb;
    for (char c : a) {
        va.push_back(atoi(&c));
    }
    reverse(va.begin(), va.end());
    for (char c : b) {
        vb.push_back(atoi(&c));
    }
    reverse(vb.begin(), vb.end());
    vector<int> vsum;
    int minIndex = (int)(min(va.size(),vb.size()));
    int left = 0;
    for (int i = 0;i < minIndex; i++) {
        int result = va[i] + vb[i] + left;
        left = 0;
        if (result > 1) {
            left = result / 2;
            vsum.push_back(result - result / 2 * 2);
        } else {
            vsum.push_back(result);
        }
    }
    int maxIndex = (int)(max(va.size(),vb.size()));
    vector<int> greater = va.size() > vb.size() ? va : vb;
    for (int i = minIndex; i < maxIndex; i++) {
        int result = greater[i] + left;
        left = 0;
        if (result > 1) {
            left = result / 2;
            vsum.push_back(result - result / 2 * 2);
        } else {
            vsum.push_back(result);
        }
    }
    if (left > 0) {
        vsum.push_back(1);
    }
    reverse(vsum.begin(), vsum.end());
    string result;
    for (int c : vsum) {
        result.append(to_string(c));
    }
    return result;
}

// https://leetcode-cn.com/problems/intersection-of-two-arrays/
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    set<int> result;
    for (int i = 0; i < nums1.size(); ++i) {
        if (find(nums2.begin(),nums2.end(),nums1[i]) != nums2.end()) {
            result.insert(nums1[i]);
        }
    }
    vector<int> resultvec;
    for (auto it = result.begin(); it != result.end(); it++) {
        resultvec.push_back(*it);
    }
    return resultvec;
}

// https://leetcode-cn.com/problems/intersection-of-two-arrays-ii/
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    map<int, int> record;
    for (int i = 0; i < nums1.size(); ++i) {
        record[nums1[i]]++;
    }
    vector<int> result;
    for (int i = 0; i < nums2.size(); ++i) {
        if (record[nums2[i]] > 0) {
            result.push_back(nums2[i]);
            record[nums2[i]]--;
        }
    }
    return result;
}

// https://leetcode-cn.com/problems/contains-duplicate-ii/
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_set<int> record;
    for (int i = 0; i < nums.size(); ++i) {
        if (record.find(nums[i]) != record.end()) {
            return true;
        } else {
            record.insert(nums[i]);
        }
        if (record.size() == k + 1) {
            record.erase(nums[i - k]);
        }
    }
    return false;
}

// https://leetcode-cn.com/problems/happy-number/
vector<int> getAllElementFromNum(int n) {
    vector<int> result;
    int temp = n;
    while (temp > 0) {
        int left = temp % 10;
        result.push_back(left);
        temp = (temp - left) / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}
int getNumFromAllElement(vector<int>nums) {
    int result = 0;
    int powInt = 0;
    for (int num : nums) {
        result = num * pow(10, powInt++) + result;
    }
    return result;
}
bool isHappy(int n) {
    set<vector<int>> check;
    int input = n;
    while(true) {
        vector<int> temp = getAllElementFromNum(input);
        input = 0;
        cout << "[ " ;
        for (int num : temp) {
            input += pow(num,2);
            cout << num << " ";
        }
        cout << "] -> " ;
        cout << input << endl;
        if (input == 1) {
            return true;
        }
        if (find(check.begin(),check.end(),temp) == check.end()) {
            check.insert(temp);
        } else {
            return false;
        }
    }
}

// https://leetcode-cn.com/problems/merge-sorted-array/
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int end = m + n - 1;
    while (n) {
        if (m == 0 || nums1[m - 1] <= nums2[n - 1]) {
            nums1[end--] = nums2[--n];
        } else {
            nums1[end--] = nums1[--m];
        }
    }
}

// --------------------------- Medium -------------------------------------

// https://leetcode-cn.com/problems/sort-colors/
void sortColors(vector<int> &nums)  {
    // 0....0 left.... 1 ...right 2...2
    int left = -1; // final left of 1
    int right = (int)nums.size();// final right of 1
    for (int i = 0; i < right;) {
        if (nums[i] == 0)
            swap(nums[i++],nums[++left]);
        else if (nums[i] == 2)
            swap(nums[i],nums[--right]);
        else
            i++;
    }
}

// https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
int findKthLargest(vector<int> &nums, int k) {
    vector<int> record;
    for (int i = 0; i < k; i++)
        record.push_back(nums[i]);
    sort(record.begin(),record.end());
    int index = k;
    while (index < nums.size()) {
        if (nums[index] > record[0]) {
            record[0] = nums[index];
            for (int i = 0;i < k - 1; i++) {
                if (record[i] > record[i+1])
                    swap(record[i],record[i+1]);
            }
        }
        index++;
    }
    return record[0];
}

// https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/
int evalRPN(vector<string>& tokens) {
    stack<int> numbers;
    for(int i = 0 ; i < tokens.size() ;++i){
        if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/"){
            int res = 0;
            int n2 = numbers.top();
            numbers.pop();
            int n1 = numbers.top();
            numbers.pop();
            
            if(tokens[i] == "+")
                res = n1 + n2;
            else if(tokens[i] == "-")
                res = n1 - n2;
            else if(tokens[i] == "/")
                res = n1 / n2;
            else
                res = n1 * n2;
            numbers.push(res);
        } else{
            numbers.push(stoi(tokens[i]));
        }
    }
    return numbers.top();
}

// https://leetcode-cn.com/problems/simplify-path/
string simplifyPath(string path) {
    stack<string> rec;
    bool start = false;
    int startIndex = 0;
    int endIndex = 0;
    for(int i = 0; i < path.size(); i++) {
        if (path.at(i) != '/') {
            if (!start) {
                startIndex = i;
                start = true;
            }
            if (i == path.size() - 1) { // last element need special handle
                endIndex = i;
                goto mark;
            }
        } else {
            endIndex = i - 1;
        mark:
            if (endIndex >= startIndex && start) {
                string pathCur = path.substr(startIndex, endIndex - startIndex + 1);
                start = false;
                if (pathCur.compare(".") == 0) {
                    
                } else if (pathCur.compare("..") == 0) {
                    if(rec.size() > 0) {
                        rec.pop();
                    }
                } else {
                    rec.push(pathCur);
                }
            }
        }
    }
    // rec is a stack with  root->xx->xx->left this pop last path first
    // to another stack with left->xx->xx->root so this will pop root first
    stack<string> res;
    while (rec.size() > 0) {
        res.push(rec.top());
        rec.pop();
    }
    string result = "";
    if (res.size() > 0) {
        while (res.size() > 0) {
            result.append("/" + res.top());
            res.pop();
        }
    } else {
        result = "/";
    }
    return result;
}

// https://leetcode-cn.com/problems/contains-duplicate-iii/
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<int> record;
    for (int i = 0; i < nums.size(); ++i) {
        if (record.lower_bound(nums[i] - t) != record.end() && *record.lower_bound(nums[i] - t) <= nums[i] + t) {
            return true;
        } else {
            record.insert(nums[i]);
        }
        if (record.size() == k + 1) {
            record.erase(nums[i - k]);
        }
    }
    return false;
}

// https://leetcode-cn.com/problems/sort-characters-by-frequency/
string frequencySort(string s) {
    unordered_map<char,int> record;
    for (char c: s) {
        record[c]++;
    }
    vector<pair<char, int>> temp(record.begin(), record.end());
    sort(temp.begin(), temp.end(), [](pair<char, int> &a, pair<char, int> &b){
        return a.second > b.second;
    });
    string result;
    for (const auto &[a, b]:temp) {
        for (int i = 0; i < b; i++) {
            result.push_back(a);
        }
    }
    return result;
}

// https://leetcode-cn.com/problems/4sum-ii/
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int,int> record;
    // record num3 num4 all sum
    for (int i = 0; i < nums3.size(); ++i) {
        for (int j = 0; j < nums4.size(); ++j) {
            record[nums3[i] + nums4[j]]++;
        }
    }
    int result = 0;
    // find is there a num1 + num2 = - (num3 + num4)
    for (int i = 0; i < nums1.size(); ++i) {
        for (int j = 0; j < nums2.size(); ++j) {
            if (record.find(- nums1[i] - nums2[j]) != record.end())
                result+=record[- nums1[i] - nums2[j]];
        }
    }
    return result;
}

// https://leetcode-cn.com/problems/number-of-boomerangs/
int numberOfBoomerangs(vector<vector<int>>& points) {
    int result = 0;
    for (int i = 0; i < points.size(); ++i) {
        unordered_map<int,int> record; //key distance value point
        for (int j = 0; j < points.size(); ++j) {
            if (j != i)
                record[((points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) + (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]))]++;
        }
        for (unordered_map<int,int>::iterator it = record.begin(); it != record.end();it++) {
            if (it->second >= 2)
                result+=(it->second)*(it->second - 1);
        }
    }
    return result;
}

// https://leetcode-cn.com/problems/flatten-nested-list-iterator/
class NestedInteger {
    vector<NestedInteger> fake;
public:
    bool isInteger() {return true;}
    int getInteger() {return 0;}
    vector<NestedInteger> &getList() {
        return fake;
    }
};
class NestedIterator {
public:
    vector<int> v;
    int index = 0;
    NestedIterator(vector<NestedInteger> &nestedList) {
        dfs(nestedList);
    }
    int next() {
        return v[index++];
    }
    bool hasNext() {
        if(index==v.size()) return false;
        else return true;
    }
    void dfs(vector<NestedInteger> &nestedList) {
        for(int i=0;i<nestedList.size();i++) {
            if(nestedList[i].isInteger())
                v.push_back(nestedList[i].getInteger());
            else dfs(nestedList[i].getList());
        }
    }
};

// https://leetcode-cn.com/problems/perfect-squares/
/*
 队列先进先出，所以我们从起点开始每次可以跳到 n - (1->k)^2 的地方
 那么就把跳到的节点再push进队列，再出栈继续跳，最短的路径肯定是最先达到走了n步
*/
int numSquaresQueue(int n) {
    queue<pair<int, int> > q;
    q.push(make_pair(n, 0));
    vector<bool> visited(n+1,false);
    visited[n] = true;
    while (!q.empty()) {
        int num = q.front().first;
        int step = q.front().second;
        q.pop();
        for (int i = 1;  ; i++) {
            int temp = num - i * i;
            if (temp < 0) {
                break;
            }
            if (temp == 0) {
                return step + 1;
            }
            if (!visited[temp]) {
                q.push(make_pair(temp , step + 1));
                visited[temp] = true;
            }
        }
    }
    return 0;
}

// https://leetcode-cn.com/problems/group-anagrams/
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<int*> record;
    vector<vector<string>> result;

    for (string  str: strs) {
        int *model = new int [26];
        memset(model,0,sizeof(int) * 26 );
        // get the model for current str
        for (char  c: str) {
            model[(int)c-97]++;
        }
        bool isNew = true;
        int findIndex = 0;
        // check is there a new model
        for (auto modelpre: record) {
            if (memcmp(model,modelpre, sizeof(int) * 26 ) == 0) {
                isNew = false;
                break;
            }
            findIndex++;
        }
        // new insert
        if (isNew) {
            record.push_back(model);
            vector<string> first;
            first.push_back(str);
            result.push_back(first);
        } else { // push to result
            delete [] model;
            result.at(findIndex).push_back(str);
        }
    }
    // clear temp
    for(vector<int*>::iterator it = record.begin();it != record.end();) {
        delete []*it;
        it = record.erase(it);
    }
    return result;
}

// https://leetcode-cn.com/problems/top-k-frequent-elements/
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> rec;
    for(int i = 0; i < nums.size();i++) {
        rec[nums[i]]++;
    }
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int>>> pq;
    for (unordered_map<int,int>::iterator it = rec.begin(); it != rec.end(); it++) {
        if (pq.size() == k) {
            if (it->second > pq.top().first) {
                pq.pop();
                pq.push(make_pair(it->second, it->first));
            }
        } else {
            pq.push(make_pair(it->second, it->first));
        }
        
    }
    vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    return result;
}

class CompareListNode {
public:
    bool operator() (ListNode* a, ListNode* b) {
        assert(a);
        assert(b);
        return a->val > b->val;
    }
};

// https://leetcode-cn.com/problems/merge-k-sorted-lists/
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.size() <= 1) {
        return lists.size() == 0 ? nullptr : lists[0];
    }
    priority_queue<ListNode*,vector<ListNode*>,CompareListNode >pq;
    for(ListNode* list : lists) {
        ListNode *cur = list;
        while (cur) {
            pq.push(cur);
            cur = cur->next;
        }
    }
    ListNode *pres = new ListNode(-1);
    ListNode *pre = nullptr;
    ListNode *cur = nullptr;
    while (!pq.empty()) {
        cur = pq.top();
        pq.pop();
        if (pre != nullptr) {
            pre->next = cur;
        } else {
            pres->next = cur;
        }
        pre = cur;
    }
    if(cur)
        cur->next = nullptr;
    ListNode *result = pres->next;
    delete pres;
    pres = nullptr;
    return result;
}

// --------------------------- Hard -------------------------------------

// https://leetcode-cn.com/problems/word-ladder/
bool laaderVaild(string s, string t) {
    if(s.size() != t.size()) {
        return false;
    }
    int diff = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) != t.at(i)) {
            diff++;
        }
    }
    return diff == 1;
}
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
        return 0;
    }
    queue<string>q;
    q.push(beginWord);
    vector<bool>visited(wordList.size() + 1,false);
    int res = 0;
    while (!q.empty()) {
        int size = (int)q.size();
        res++; //上一次加的都能pop出去就代表加了一层
        while (size-- > 0) {
            string word = q.front();
            q.pop();
            for (int i = 0; i < wordList.size(); i++) {
                if (visited[i]) {
                    continue;
                }
                string wordnew = wordList[i];
                if (laaderVaild(word,wordnew)) {
                    if (wordnew.compare(endWord) == 0) {
                        return res + 1;
                    }
                    q.push(wordnew); //能跳到下一个字典的都加入队列
                    visited[i] = true;
                }
            }
        }
    }
    return 0;
}

// https://leetcode-cn.com/problems/word-ladder-ii/
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
        return vector<vector<string>>();
    }
    queue<vector<string>>q;
    q.push({beginWord});
    vector<bool>visited(wordList.size() + 1,false);
    vector<vector<string>> res;
    while (!q.empty()) {
        int size = (int)q.size();
        vector<bool>levelVisited(wordList.size() + 1,false);
        while (size-- > 0) {
            vector<string> curPath = q.front();
            string curWord = curPath.back();
            q.pop();
            for (int i = 0; i < wordList.size(); i++) {
                if (visited[i]) {
                    continue;
                }
                string wordnew = wordList[i];
                if (laaderVaild(curWord,wordnew)) {
                    auto newPath = curPath;
                    newPath.push_back(wordnew);
                    if (wordnew.compare(endWord) == 0) {
                        res.push_back(newPath);
                    } else {
                        q.push(newPath); //能跳到下一个字典的都加入队列
                    }
                    levelVisited[i] = true; //同一层因为路径的问题还不能清空
                }
            }
        }
        // 跳出层之后再设置访问
        for (int i = 0; i < levelVisited.size(); i++) {
            if (levelVisited[i]) {
                visited[i] = true;
            }
        }
    }
    return res;
}

// 求最大回文矩阵
bool isPalindromicMatrix(vector<vector<int>> &matrix) {
    int n = (int)matrix.size();
    int checkLine = (n+1)/2;
    for (int row = 0; row <= checkLine; row++) {
        for (int col = 0; col < n; col++) {
            if(matrix[row][col] != matrix[n - row - 1][n - col - 1]) {
                return false;
            }
        }
    }
    return true;
}

int largestPalindromicSubmatrix(vector<vector<int>> &matrix) {
    int row = (int)matrix.size();
    int col = 0;
    if (row > 0) {
        col = (int)matrix[0].size();
    }
    if (row == 0 && col == 0) {
        return 0;
    }
    if (row == 0 || col == 0) {
        return 1;
    }
    int n = min(col,row);
    int res = 1;
    for (int i = 2; i <= n; i++) { // submatrix length
        for (int leftTopx = 0; leftTopx <= col - i; leftTopx++) {
            for (int leftTopy = 0; leftTopy <= row - i; leftTopy++) {
                vector<vector<int>> temp;
                for (int temprow = 0; temprow < i; temprow++) {
                    vector<int> newrow;
                    for (int tempcol = 0; tempcol < i; tempcol++) {
                        newrow.push_back(matrix[leftTopx + temprow][tempcol]);
                    }
                    temp.push_back(newrow);
                }
                if (isPalindromicMatrix(temp)) {
                    res = max(res, i);
                    break;
                }
            }
            if (res >= i) {
                break;
            }
        }
    }
    return res;
}

#pragma mark - sort

int partition(vector<int> &nums, int low, int high) {
    int key = nums[low];
    int partition = low;
    int big = high;
    for (int i = low + 1; i <= big;) {
        if (nums[i] <= key) {
            swap(nums[partition++], nums[i++]);
        } else {
            swap(nums[i], nums[big--]);
        }
    }
    return partition;
}

void quickSort(vector<int> &nums, int start, int end) {
    int pos = 0;
    if (start < end) {
        pos = partition(nums, start, end);
        quickSort(nums, start, pos - 1);
        quickSort(nums, pos + 1, end);
    }
}

#pragma mark - search

int binarySearch(vector<int> &nums, int target) {
    int left = 0;
    int right = (int)nums.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int key = nums[mid];
        if (target == key) {
            return mid;
        }
        if (target > key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;// not found
}

#pragma mark - double points

// https://leetcode-cn.com/problems/two-sum/
vector<int> twoSum(vector<int> &numbers, int target) {
    if (numbers.size() >= 2) {
        int l = 0;
        int r = (int)numbers.size() - 1;
        while (l < r) {
            int sum = numbers[l] + numbers[r];
            if (sum == target) {
                return vector<int>{l, r};
            } else {
                sum > target ? r-- : l++;
            }
        }
    }
    return vector<int>{};
}

// --------------------------- Medium -------------------------------------

// https://leetcode-cn.com/problems/container-with-most-water/
int maxArea(vector<int> &height) {
    int l = 0;
    int r = (int)height.size() - 1;
    int area = 0;
    int distance = r;
    while (l < r) {
        area = max(area, distance * min(height[l], height[r]));
        if (l < r && r >= 1) {
            if (height[l] < height[r]) {
                l++;
                distance--;
            } else {
                r--;
                distance--;
            }
        } else {
            break;
        }
    }
    return area;
}

// https://leetcode-cn.com/problems/minimum-size-subarray-sum/
int minSubArrayLen(int target, vector<int> &nums) {
    int l = 0;
    int r = -1;
    int min = (int)nums.size();
    if (nums[0] == target) {
        return 1;
    }
    bool find = false;
    int sum = 0;
    while (l < (nums.size())) {
        if (sum >= target) {
            find = true;
            min = std::min(min, r - l + 1);
            sum -= nums[l++];
        } else {
            if (r + 1 < nums.size()) {
                sum = sum + nums[++r];
            } else {
                l++;
            }
        }
    }
    return find ? min : 0;
}

// https://leetcode-cn.com/problems/3sum/
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    if(nums.size()<3) return result;
    sort(nums.begin(), nums.end());
    if(nums[0]>0) return result;
    int i = 0;
    while(i<nums.size()){
        if(nums[i]>0) break;
        int left = i+1, right = (int)nums.size()-1;
        while(left< right){
            long long y = static_cast<long long>(nums[i]);
            long long x = static_cast<long long>(nums[left]);
            long long z = static_cast<long long>(nums[right]);
            if(x + y >0-z)
                right--;
            else if(x + y <0-z)
                left++;
            else{
                result.push_back({nums[i], nums[left], nums[right]});
                while(left<right&&nums[left]==nums[left+1])
                    left++;
                while(left<right&&nums[right] == nums[right-1])
                    right--;
                left++;
                right--;
            }
        }
        // 避免nums[i]作为第一个数重复出现
        while(i+1<nums.size()&&nums[i] == nums[i+1])
            i++;
        i++;
    }
    return result;
}

#pragma mark - tree

void pre(TreeNode *root, int depth, vector<vector<int>> &result) {
    if (!root) return ;
    if (depth >= result.size())
        result.push_back(vector<int> ());
    result[depth].push_back(root->val);
    pre(root->left, depth + 1, result);
    pre(root->right, depth + 1, result);
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    pre(root, 0, result);
    for (vector<int> level  : result) {
        cout << "[ " ;
        for (int element: level) {
            cout << element << " ";
        }
        cout << "]" << endl;
    }
    return result;
}

void preOrderTraverseRec(TreeNode *root) {
    if (root != nullptr) {
        cout << root->val  << " ";
        preOrderTraverseRec(root->left);
        preOrderTraverseRec(root->right);
    }
}

void preOrderTraverseStack(TreeNode *root) {
    vector<TreeNode*> stack;
    TreeNode *pNode = root;
    while (pNode != nullptr || stack.size()) {
        if (pNode != nullptr) {
            cout << pNode->val  << " ";
            stack.push_back(pNode);
            pNode = pNode->left;
        } else { //pNode == null && !stack.isEmpty()
            TreeNode *node = stack.back();
            pNode = node->right;
            stack.pop_back();
        }
    }
    cout << endl;
}

// simulate the system stack in out
struct Command {
    string s; // go print
    TreeNode *node;
    Command(string s, TreeNode* node): s(s), node(node){
        cout << "Command: " << s << " val: " << node->val << endl;
    }
};

// https://leetcode-cn.com/problems/binary-tree-preorder-traversal/
vector<int> preorderTraversal(TreeNode *root) {
    vector<int> result;
    if (root == nullptr) {
        return result;
    }
    cout << "preorderTraversal start" << endl;
    stack<Command> stack;
    stack.push(Command("go", root));
    while (!stack.empty()) {
        Command cmd = stack.top();
        stack.pop();
        if (cmd.s == "print") {
            result.push_back(cmd.node->val);
        } else { // "go"
            if (cmd.node->right) {
                stack.push(Command("go", cmd.node->right));
            }
            if (cmd.node->left) {
                stack.push(Command("go", cmd.node->left));
            }
            stack.push(Command("print", cmd.node));
        }
    }
    cout << "preorderTraversal end" << endl;
    return result;
}

// https://leetcode-cn.com/problems/binary-tree-inorder-traversal/
vector<int> inorderTraverse(TreeNode *root) {
    vector<int> result;
    if (root == nullptr) {
        return result;
    }
    cout << "inorderTraverse start" << endl;
    stack<Command> stack;
    stack.push(Command("go", root));
    while (!stack.empty()) {
        Command cmd = stack.top();
        stack.pop();
        if (cmd.s == "print") {
            result.push_back(cmd.node->val);
        } else { // "go"
            if (cmd.node->right) {
                stack.push(Command("go", cmd.node->right));
            }
            stack.push(Command("print", cmd.node));
            if (cmd.node->left) {
                stack.push(Command("go", cmd.node->left));
            }
        }
    }
    cout << "inorderTraverse end" << endl;
    return result;
}

// https://leetcode-cn.com/problems/binary-tree-postorder-traversal/
vector<int> postorderTraverse(TreeNode *root) {
    vector<int> result;
    if (root == nullptr) {
        return result;
    }
    cout << "postorderTraverse start" << endl;
    stack<Command> stack;
    stack.push(Command("go", root));
    while (!stack.empty()) {
        Command cmd = stack.top();
        stack.pop();
        if (cmd.s == "print") {
            result.push_back(cmd.node->val);
        } else { // "go"
            stack.push(Command("print", cmd.node));
            if (cmd.node->right) {
                stack.push(Command("go", cmd.node->right));
            }
            if (cmd.node->left) {
                stack.push(Command("go", cmd.node->left));
            }
        }
    }
    cout << "postorderTraverse end" << endl;
    return result;
}

// https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
int maxDepth(TreeNode* root) {
    int level = 0;
    if(root == nullptr)
        return level;
    queue<pair<TreeNode*,int> > q;
    q.push(make_pair(root,level));
    while(!q.empty()) {
        TreeNode *node = q.front().first;
        int curlevel = q.front().second;
        q.pop();
        if(node->left)
            q.push(make_pair(node->left,curlevel+1));
        if(node->right)
            q.push(make_pair(node->right,curlevel+1));
        level = max(curlevel + 1,level);
    }
    return level;
}

int maxDepth_recursive(TreeNode* root) {
    if (root == nullptr)
        return 0;
    return max(maxDepth_recursive(root->left), maxDepth_recursive(root->right)) + 1;
}

// https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/
int minDepth(TreeNode* root) {
    int level = INT_MAX;
    if(root == nullptr)
        return 0;
    queue<pair<TreeNode*,int> > q;
    q.push(make_pair(root,0));
    while(!q.empty()) {
        TreeNode *node = q.front().first;
        int curlevel = q.front().second;
        q.pop();
        if(node->left)
            q.push(make_pair(node->left,curlevel+1));
        if(node->right)
            q.push(make_pair(node->right,curlevel+1));
        if(node->left == nullptr && node->right == nullptr)
            level = min(curlevel + 1,level);
    }
    return level;
}

// https://leetcode-cn.com/problems/invert-binary-tree/
TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr)
        return root;
    invertTree(root->left);
    invertTree(root->right);
    swap(root->left,root->right);
    return root;
}

// https://leetcode-cn.com/problems/same-tree/
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr || q == nullptr) {
        if (p == nullptr && q == nullptr)
            return true;
        else
            return false;
    } else {
        if (p->val != q->val)
            return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// https://leetcode-cn.com/problems/symmetric-tree/
bool compareforSymmetric(TreeNode* left, TreeNode* right) {
    if (left == nullptr || right == nullptr) {
        if (left == nullptr && right == nullptr)
            return true;
        else
            return false;
    }
    if (left->val != right->val)
        return false;
    return compareforSymmetric(left->left,right->right) && compareforSymmetric(left->right,right->left);
}
bool isSymmetric(TreeNode* root) {
    if (root == nullptr)
        return root;
    return compareforSymmetric(root->left,root->right);
}

// https://leetcode-cn.com/problems/count-complete-tree-nodes/
int _countNodes(TreeNode* root, int & count) {
    if (root != nullptr) {
        count = count+1;
        _countNodes(root->left, count);
        _countNodes(root->right, count);
    }
    return count;
}
int countNodes(TreeNode* root) {
    int result = 0;
    result = _countNodes(root,result);
    return result;
}

// https://leetcode-cn.com/problems/balanced-binary-tree/
bool _isBalanced(TreeNode *left, TreeNode*right) {
    if (left == nullptr || right == nullptr) {
        if(left == right)
            return true;
        if (left != nullptr) {
            return maxDepth(left) <= 1;
        }
        if (right != nullptr) {
            return maxDepth(right) <= 1;
        }
    }
    int levelleft = maxDepth(left);
    int levelright = maxDepth(right);
    if(abs(levelleft - levelright) > 1)
        return false;
    return _isBalanced(left->left,left->right) && _isBalanced(right->left,right->right);
}
bool isBalanced(TreeNode* root) {
    if(root == nullptr)
        return true;
    return _isBalanced(root->left,root->right);
}

// https://leetcode-cn.com/problems/path-sum/
bool hasPathSum(TreeNode* root, int targetSum) {
    if(root == nullptr)
        return false;
    if(root->left == nullptr && root->right == nullptr) {
        return root->val == targetSum;
    }
    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
}

// https://leetcode-cn.com/problems/sum-of-left-leaves/
int sumOfLeftLeaves(TreeNode* root) {
    if(root == nullptr)
        return 0;
    int res = 0;
    if(root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr)
        res = root->left->val;
    return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right) + res;
}

// https://leetcode-cn.com/problems/binary-tree-paths/
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    if(root == nullptr)
        return res;
    if(root->left == nullptr && root->right == nullptr) {
        res.push_back(to_string(root->val));
        return res;
    }
    
    vector<string>lefts = binaryTreePaths(root->left);
    for (int i = 0; i < lefts.size(); i++) {
        res.push_back(to_string(root->val) + "->" + lefts[i]);
    }
    
    vector<string>rights = binaryTreePaths(root->right);
    for (int i = 0; i < rights.size(); i++) {
        res.push_back(to_string(root->val) + "->" + rights[i]);
    }
    
    return res;
}

// https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr)
        return root;
    int less = p->val < q->val ? p->val : q->val;
    int big = p->val < q->val ? q->val : p->val;
    if (root->val > big)
        return lowestCommonAncestorBST(root->left,p,q);
    if (root->val < less)
        return lowestCommonAncestorBST(root->right,p,q);
    return root;
}

// https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/
TreeNode* _sortedArrayToBST(vector<int>& nums, int l, int r) {
    if (r < l) return nullptr;
    int mid = l + ((r - l) / 2);
    
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = _sortedArrayToBST(nums, l, mid - 1);
    root->right = _sortedArrayToBST(nums, mid + 1, r);
    return root;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return _sortedArrayToBST(nums, 0, (int)nums.size() - 1);
}

// --------------------------- Medium -------------------------------------

// https://leetcode-cn.com/problems/validate-binary-search-tree/
bool _isValidBST(TreeNode *node, long long less, long long greater) {
    if (node == nullptr)
        return true;
    if (node->val <= less || node->val >= greater)
        return false;
    return _isValidBST(node->left,less,node->val) && _isValidBST(node->right,node->val,greater);
}
bool isValidBST(TreeNode* root) {
    return _isValidBST(root, LONG_MIN, LONG_MAX);
}

// https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/
int _kthSmallestLeft(TreeNode* root){
    if(root==nullptr) return 0;
    return _kthSmallestLeft(root->left)+_kthSmallestLeft(root->right)+1;
}
int kthSmallest(TreeNode* root, int k) {
    int leftN=_kthSmallestLeft(root->left);
    if(leftN+1==k) return root->val;
    else if(k<=leftN){
        return kthSmallest(root->left, k);
    }
    else return kthSmallest(root->right, k-leftN-1);
}

// https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
bool canfindChild(TreeNode* node, int val) {
    if (node == nullptr)
        return false;
    if(node->val == val)
        return true;
    return canfindChild(node->left,val) || canfindChild(node->right,val);
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    queue<pair<TreeNode *, int>>theQ;
    theQ.push(make_pair(root,0));
    vector<vector<pair<TreeNode *, int>>> rec;
    while (!theQ.empty()) {
        TreeNode *node = theQ.front().first;
        int level = theQ.front().second;
        theQ.pop();
        if (level == rec.size())
            rec.push_back(vector<pair<TreeNode *, int>>());
        rec[level].push_back(make_pair(node, level));
        if(node->left)
            theQ.push(make_pair(node->left,level+1));
        if(node->right)
            theQ.push(make_pair(node->right,level+1));
    }
    int plevel = 0;
    int qlevel = 0;
    bool findp = false;
    bool findq = false;
    for(int i = 0; i < rec.size(); i++) {
        for (auto [node, level] : rec[i]) {
            if (node->val == p->val) {
                plevel = i;
                findp = true;
            }
            if (node->val == q->val) {
                qlevel = i;
                findq = true;
            }
        }
        if(findp && findq)
            break;
    }
    int uplever = min(plevel,qlevel);
    TreeNode* downNode =  plevel < qlevel ? p : q;
    TreeNode* upNode =  downNode->val == q->val ? p : q;
    // if we can find downNode from upNode
    if (canfindChild(upNode,downNode->val))
        return upNode;
    for (int i = uplever; i > 0 ; i--) {
        for (auto [node, level] : rec[i]) {
            if(canfindChild(node, upNode->val)&&canfindChild(node,downNode->val))
                return node;
        }
    }
    return root;
}

// https://leetcode-cn.com/problems/delete-node-in-a-bst/
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;
    if (root->val == key) {
        if (root->right == nullptr) { // 2.删除右节点
            return root->left;
        }
        TreeNode *cur = root->right;
        while (cur->left) {
            cur = cur->left;
        }
        swap(root->val, cur->val); // 1. 交换自己和右子树最小的点
    }
    root->left = deleteNode(root->left, key);
    root->right = deleteNode(root->right, key);
    return root;
}

// https://leetcode-cn.com/problems/path-sum-ii/
void dfsPathSum(TreeNode* root, vector<int> &tmp, int sum, vector<vector<int>> &res){
    if(!root)
        return;
    tmp.push_back(root->val);
    if(root->val==sum && (root->left == nullptr && root->right == nullptr)){ //叶子节点
        res.push_back(tmp);
    }
    dfsPathSum(root->left,tmp,sum - root->val, res);
    dfsPathSum(root->right,tmp,sum - root->val, res);
    tmp.pop_back();
}
vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> res;
    vector<int> tmp;
    dfsPathSum(root, tmp, sum, res);
    return res;
}

// https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/
void dfsSumNumbers(TreeNode* root, vector<int>&temp,vector<vector<int>> &res) {
    if (root == nullptr)
        return;
    temp.push_back(root->val);
    if (root->left == nullptr && root->right == nullptr) {
        res.push_back(temp);
    }
    dfsSumNumbers(root->left,temp,res);
    dfsSumNumbers(root->right,temp,res);
    temp.pop_back();
}

int sumNumbers(TreeNode* root) {
    vector<vector<int>> res;
    vector<int> tmp;
    dfsSumNumbers(root, tmp, res);
    int sum = 0;
    for( vector<int> path : res) {
        int num = 0;
        int powInt = (int)path.size() - 1;
        for (int i = 0;i < path.size();i++,powInt--) {
            num+=path[i] * pow(10,powInt);
        }
        sum+=num;
    }
    return sum;
}

// https://leetcode-cn.com/problems/path-sum-iii/
int64_t findPathSum(TreeNode *node, int64_t num) {
    if(nullptr == node)
        return 0;
    int64_t res = 0;
    if(num == node->val)
        res++;
    res+=findPathSum(node->left,num - node->val);
    res+=findPathSum(node->right,num - node->val);
    return res;
}
int64_t pathSum(TreeNode* root, int64_t targetSum) {
    if(nullptr == root)
        return 0;
    int64_t res = findPathSum(root, targetSum);
    res+=pathSum(root->left, targetSum);
    res+=pathSum(root->right,targetSum);
    return res;
}

// https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) {
        return result;
    }
    queue< pair<TreeNode*, int> > q;
    q.push(make_pair(root, 0));
    while (!q.empty()) {
        TreeNode *node = q.front().first;
        int level = q.front().second;
        q.pop();
        if (level == result.size()) {
            result.push_back(vector<int> ());
        }
        result[level].push_back(node->val);
        if (node->left) {
            q.push(make_pair(node->left, level+1));
        }
        if (node->right) {
            q.push(make_pair(node->right, level+1));
        }
    }
    int left = 0;
    int right = (int)result.size() - 1;
    while (left < right) {
        swap(result[left++], result[right--]);
    }
    return result;
}

// https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>>result;
    if(root == nullptr) {
        return result;
    }
    queue< pair<TreeNode*,int> > q;
    q.push(make_pair(root,0));
    while(!q.empty()) {
        TreeNode *node = q.front().first;
        int level = q.front().second;
        q.pop();
        if(level == result.size())
            result.push_back(vector<int>());
        result[level].push_back(node->val);
        if(node->left)
            q.push(make_pair(node->left,level+1));
        if(node->right)
            q.push(make_pair(node->right,level+1));
    }
    for (int i = 0; i < result.size(); i++) {
        if (i % 2 != 0) {
            int left = 0;
            int right = (int)result[i].size() - 1;
            while (left < right) {
                swap(result[i][left++], result[i][right--]);
            }
        }
    }
    return result;
}

// https://leetcode-cn.com/problems/binary-tree-right-side-view/
vector<int> rightSideView(TreeNode* root) {
    vector<vector<int>>result;
    if(root == nullptr) {
        return vector<int>();
    }
    queue< pair<TreeNode*,int> > q;
    q.push(make_pair(root,0));
    while(!q.empty()) {
        TreeNode *node = q.front().first;
        int level = q.front().second;
        q.pop();
        if(level == result.size())
            result.push_back(vector<int>());
        result[level].push_back(node->val);
        if(node->left)
            q.push(make_pair(node->left,level+1));
        if(node->right)
            q.push(make_pair(node->right,level+1));
    }
    vector<int>res;
    for( vector<int> level : result ) {
        res.push_back(level[level.size()-1]);
    }
    return res;
}

#pragma mark - Recursive

// https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
string getletterCombinations(int num) {
    if (num == 2) {
        return  "abc";
    } else  if (num == 3) {
        return  "def";
    } else  if (num == 4) {
        return  "ghi";
    }
    else  if (num == 5) {
       return  "jkl";
   } else  if (num == 6) {
       return  "mno";
   } else  if (num == 7) {
       return  "pqrs";
   } else  if (num == 8) {
       return  "tuv";
   } else  if (num == 9) {
       return  "wxyz";
   }
    return "";
}
void findLetterCombinations(const string &digits, int index, const string &s, vector<string> &res) {
    if (index == digits.size()) {
        res.push_back(s);
        return;
    }
    char c = digits[index];
    string letters = getletterCombinations(c - '0');
    for (int i = 0; i < letters.size(); i++) {
        findLetterCombinations(digits, index + 1,s + letters[i], res);
    }
}
vector<string> letterCombinations(string digits) {
    vector<string> res;
    if (digits.size() == 0)
        return res;
    findLetterCombinations(digits, 0, "", res);
    return res;
}

// https://leetcode.cn/problems/restore-ip-addresses/
bool _isVaildIpAddresses(const string &s, int start, int end) {
    if (start > end)
        return false;
    if(s[start] == '0' && start != end)
        return false;
    int num = 0;
    for (int i = start; i <= end; i++) {
        if(s[i] > '9' || s[i] < '0')
            return false;
        num = num * 10 + (s[i] - '0');
        if (num > 255)
            return false;
    }
    return true;
}
void _restoreIpAddresses(string s, int startIndex, int pointNum, vector<string> &res) {
    if (pointNum == 3) {
        if(_isVaildIpAddresses(s, startIndex, (int)s.size() - 1))
            res.push_back(s);
        else
            return;
    }
    for (int i = startIndex; i < s.size();i++) {
        if (_isVaildIpAddresses(s, startIndex, i)) {
            s.insert(s.begin() + i + 1,'.');
            pointNum++;
            _restoreIpAddresses(s,i+2,pointNum,res);
            pointNum--;
            s.erase(s.begin() + i + 1);
        } else {
            break;
        }
    }
}
vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    if (s.size() > 12) return res;
    _restoreIpAddresses(s, 0, 0, res);
    return res;
}

// https://leetcode.cn/problems/permutations/
void _permute(vector<int> nums, vector<int> &temp,vector<vector<int>> &res) {
    if (nums.size() == 0) {
        res.push_back(temp);
        return;
    }
    
    for(int i = 0; i < nums.size(); i++) {
        temp.push_back(nums[i]);
        vector<int> tempNums = nums;
        vector<int>::iterator needRemove = tempNums.begin() + i;
        tempNums.erase(needRemove);
        _permute(tempNums, temp, res);
        temp.pop_back();
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> temp;
    _permute(nums, temp,res);
    return res;
}

// https://leetcode.cn/problems/permutations-ii/
void _permuteUnique(vector<int> nums, vector<int> &temp,  vector<bool> &used,vector<vector<int>> &res) {
    if (temp.size() == nums.size()) {
        res.push_back(temp);
        return;
    }
    
    for(int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
            continue;
        if(used[i] == false) {
            used[i] = true;
            temp.push_back(nums[i]);
            _permuteUnique(nums, temp, used, res);
            used[i] =false;
            temp.pop_back();
        }
    }
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> temp;
    vector<bool> used(nums.size(),false);
    sort(nums.begin(),nums.end());
    _permuteUnique(nums, temp, used, res);
    return res;
}

// https://leetcode.cn/problems/combinations/
void _combine(int n, int k, int startIndex, vector<int> temp, vector<vector<int>> &res) {
    if (temp.size() == k) {
        res.push_back(temp);
        return;
    }
    
    for (int i = startIndex; i <= n - (k - temp.size()) + 1; i++) {
        temp.push_back(i);
        _combine(n, k, i + 1, temp, res);
        temp.pop_back();
    }
}
vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    if (k > n)
        return res;
    vector<int> temp;
    _combine(n, k, 1, temp, res);
    return res;
}

// https://leetcode.cn/problems/combination-sum/
void _combinationSum(vector<int>& candidates,int target, int sum, int index,  vector<int> &temp, vector<vector<int>> &res) {
    if (sum > target)
        return;
    if (sum == target) {
        res.push_back(temp);
        return;
    }
    for (int i = index; i < candidates.size(); i++) {
        temp.push_back(candidates[i]);
        sum+=candidates[i];
        _combinationSum(candidates, target, sum, i, temp, res);
        sum-=candidates[i];
        temp.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    _combinationSum(candidates, target, 0, 0, temp, res);
    return res;
}

// https://leetcode.cn/problems/combination-sum-ii/
void _combinationSum2(vector<int>& candidates,int target, int sum, int index, vector<bool> &used, vector<int> &temp, vector<vector<int>> &res) {
    if (sum > target)
        return;
    if (sum == target) {
        res.push_back(temp);
        return;
    }
    for (int i = index; i < candidates.size(); i++) {
        if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false)
            continue;
        if (!used[i]) {
            used[i] = true;
            if (used[i])
                temp.push_back(candidates[i]);
            sum+=candidates[i];
            _combinationSum2(candidates, target, sum, i+1, used, temp, res);
            sum-=candidates[i];
            temp.pop_back();
            used[i] = false;
        }
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    vector<bool> used(candidates.size(),false);
    sort(candidates.begin(),candidates.end());
    _combinationSum2(candidates, target, 0, 0, used, temp, res);
    return res;
}

// https://leetcode.cn/problems/combination-sum-iii/
void _combinationSum3(int k, int n, int startIndex, int sum, vector<int>&temp, vector<vector<int>> &res) {
    if (sum > n)
        return;
    if (temp.size() > k)
        return;
    if (sum == n && temp.size() == k) {
        res.push_back(temp);
        return;
    }
    for (int i = startIndex; i <= 9; i++) {
        sum+=i;
        temp.push_back(i);
        _combinationSum3(k, n, i + 1,sum, temp, res);
        sum-=i;
        temp.pop_back();
    }
}
vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> res;
    vector<int> temp;
    _combinationSum3(k, n, 1, 0, temp, res);
    return res;
}

// https://leetcode.cn/problems/subsets/
void _subsets(vector<int>& nums, int maxCount, int curIndex, vector<int> &temp, vector<vector<int>> &res) {
    if (temp.size() == maxCount) {
        res.push_back(temp);
        return;
    }
    for (int i = curIndex; i < nums.size() - (maxCount - temp.size()) + 1; i++) {
        temp.push_back(nums[i]);
        _subsets(nums, maxCount, i + 1,temp, res);
        temp.pop_back();
    }
}
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() == 0)
        return res;
    res.push_back(vector<int>());
    for (int i = 1; i <= nums.size(); i++) {
        vector<vector<int>> resTemp;
        vector<int> temp;
        _subsets(nums, i, 0, temp, resTemp);
        res.insert(res.end(),resTemp.begin(),resTemp.end());
    }
    return res;
}

// https://leetcode.cn/problems/subsets-ii/
void _subsetsWithDup(vector<int>& nums, int maxCount, int curIndex, vector<bool> &used, vector<int> &temp, vector<vector<int>> &res) {
    if (temp.size() == maxCount) {
        res.push_back(temp);
        return;
    }
    for (int i = curIndex; i < nums.size() - (maxCount - temp.size()) + 1; i++) {
        if (i - 1 >= 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
            continue;
        if (!used[i]) {
            used[i] = true;
            temp.push_back(nums[i]);
            _subsetsWithDup(nums, maxCount, i + 1, used,temp, res);
            temp.pop_back();
            used[i] = false;
        }
    }
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    vector<vector<int>> res;
    if (nums.size() == 0)
        return res;
    sort(nums.begin(), nums.end());
    res.push_back(vector<int>());
    for (int i = 1; i <= nums.size(); i++) {
        vector<bool> used(nums.size()+1,false);
        vector<vector<int>> resTemp;
        vector<int> temp;
        _subsetsWithDup(nums, i, 0, used, temp, resTemp);
        res.insert(res.end(),resTemp.begin(),resTemp.end());
    }
    return res;
}

#pragma mark - ListNode

ListNode* createList(int arr[],int n) {
    if (n == 0) {
        return nullptr;
    }
    ListNode *head = new ListNode(arr[0]);
    ListNode *cur = head;
    for (int i = 1; i < n; i++) {
        cur->next = new ListNode(arr[i]);
        cur = cur->next;
    }
    return head;
}


void printLinkedList(ListNode* head) {
    ListNode *cur = head;
    while (cur != nullptr) {
        cout << cur->val << " " << "-> ";
        cur = cur->next;
    }
    cout << "nullptr" << endl;
}

void deleteLinkedList(ListNode* head) {
    ListNode *cur = head;
    while (cur != nullptr) {
        ListNode *del = cur;
        cur = cur->next;
        delete del;
    }
    
}

// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/
ListNode* deleteDuplicates(ListNode* head) {
    ListNode *cur = head;
    ListNode *pre = nullptr;
    while (cur != nullptr) {
        if (pre && pre->val == cur->val) { // pre == cur
            ListNode *del = cur;
            cur = cur->next;
            delete del;
            pre->next = cur;
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

// https://leetcode-cn.com/problems/reverse-linked-list/
ListNode* reverseList(ListNode* head) {
    // node0 -> node1 -> node2 -> node3
    ListNode *pre = nullptr;
    ListNode *cur = head;
    while (cur != nullptr) {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}

// https://leetcode-cn.com/problems/remove-linked-list-elements/
ListNode* removeElements(ListNode* head, int val) {
    if (head == nullptr) {
     return head;
    }
    ListNode *cur = head;
    ListNode *pre = nullptr;
    while (cur != nullptr) {
        ListNode *deleteNode = nullptr;
        if (cur->val == val) {
            deleteNode = cur;
            if (pre != nullptr) {
                pre->next = cur->next;
            } else {
                head = cur->next;
            }
        } else {
            pre = cur;
        }
        if (deleteNode != nullptr) {
            delete deleteNode;
        }
        cur = cur->next;
    }
    return head;
}

// https://leetcode-cn.com/problems/merge-two-sorted-lists/
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode *cur1 = list1;
    ListNode *cur2 = list2;
    ListNode *preHeadRes = new ListNode(-1);
    ListNode *preHead = preHeadRes;
    while (cur1 != nullptr && cur2 != nullptr) {
        if (cur1->val <= cur2->val) {
            preHead->next = cur1;
            cur1 = cur1->next;
        } else {
            preHead->next = cur2;
            cur2 = cur2->next;
        }
        preHead = preHead->next;
    }
    preHead->next = cur1 == nullptr ? cur2 : cur1;
    return preHeadRes->next;
}

// https://leetcode-cn.com/problems/palindrome-linked-list/
bool isPalindrome(ListNode* head) {
    if (head == nullptr) {
        return false;
    }

    //find the mid of list by fast slow pointer
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *mid = slow->next;
    // cut the node to 2 pieces
    slow->next = nullptr;

    //reverse the second link
    ListNode *cur = mid;
    ListNode *pre = nullptr;
    while(cur) {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }

    // compare two lists
    cur = head;
    while(pre && cur) {
        if(pre->val != cur->val)
            return false;
        pre = pre->next;
        cur = cur->next;
    }
    return true;
}

// --------------------------- Medium -------------------------------------

// https://leetcode-cn.com/problems/reorder-list/
void reorderList(ListNode* head) {
    vector<ListNode*> temp;
    ListNode *cur = head;
    while(cur) {
        temp.push_back(cur);
        cur = cur->next;
    }
    int left = 0;
    int right = (int)temp.size() - 1;
    while (left < right) {
        temp[left]->next = temp[right];
        temp[right--]->next = temp[++left];
    }
    temp[left]->next = nullptr;
}

// https://leetcode-cn.com/problems/partition-list/
ListNode* partition(ListNode* head, int x) {
    ListNode* pre = nullptr;
    ListNode* cur = head;
    while (cur != nullptr) {
        if (cur->val >= x) {
            // find the first node < x
            ListNode* right = cur->next;
            ListNode* rightPre = cur;
            while (right) {
                if (right->val < x) {
                    if (pre) {
                        pre->next = right;
                    } else {
                        head = right;
                    }
                    rightPre->next = right->next;
                    right->next = cur;
                    cur = right;
                    break;
                }
                rightPre = right;
                right = right->next;
            }
        }
        pre = cur;
        cur = cur->next;
    }
    return head;
}

// https://leetcode-cn.com/problems/odd-even-linked-list/
ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *odd = head;
    ListNode *evenHead = head->next;
    ListNode *even = evenHead;
   
    if (even->next) {
        ListNode *cur = even->next;
        int index = 3;
        while (cur != nullptr) {
            if (index % 2 != 0) {
                odd->next = cur;
                odd = cur;
            } else {
                even->next = cur;
                even = cur;
            }
            cur = cur->next;
            index++;
        }
    }
    
    odd->next = evenHead;
    even->next = nullptr;
    return head;
}

// https://leetcode-cn.com/problems/reverse-linked-list-ii/
ListNode* reverseBetween(ListNode* head, int left, int right) {
    int start = left - 1;
    int end = right - 1;

    while (start < end) {
        ListNode* temp = head;
        ListNode* A = nullptr;
        for (int i = 0; i < right; i++) {
            if (i == start) {
                A = temp;
            } else if (i == end) {
                swap(A->val, temp->val);
                start++;
                end--;
                break;
            }
            temp = temp->next;
        }
    }
    return head;
}

// https://leetcode-cn.com/problems/add-two-numbers/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode *result = new ListNode();
    ListNode *tempPre = result;
    ListNode *temp1 = l1;
    ListNode *temp2 = l2;
    int sum = 0;
    int left = 0;
    bool isfirst = true;
    bool temp1end = false;
    bool temp2end = false;
    while (!temp1end || !temp2end || left) {
        sum += (temp1end ? 0 : temp1->val);
        sum += (temp2end ? 0 : temp2->val);
        if (temp1->next != nullptr) {
            temp1 = temp1->next;
        } else {
            temp1end = true;
        }
        if (temp2->next != nullptr) {
            temp2 = temp2->next;
        } else {
            temp2end = true;
        }
        sum += left;
        if (sum >= 10) {
            left = 1;
            sum -= 10;
        } else {
            left = 0;
        }
        cout << sum << endl;
        if (isfirst) {
            isfirst = false;
            tempPre->val = sum;
        } else {
            ListNode *temp = new ListNode();
            temp->val = sum;
            tempPre->next = temp;
            tempPre = temp;
        }
        sum = 0;
    }
    return result;
}

// https://leetcode-cn.com/problems/add-two-numbers-ii/
ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2) {
    vector<int>vec1;
    vector<int>vec2;
    ListNode *cur;
    cur = l1;
    while (cur != nullptr) {
        vec1.push_back(cur->val);
        cur = cur->next;
    }
    cur = l2;
    while (cur != nullptr) {
        vec2.push_back(cur->val);
        cur = cur->next;
    }
    
    int left = 0;
    vector<int>res;
    while (vec1.size() || vec2.size() || left) {
        int num1 = 0;
        int num2 = 0;
        if (vec1.size()) {
            num1 = vec1.back();
            vec1.pop_back();
        }
        if (vec2.size()) {
            num2 = vec2.back();
            vec2.pop_back();
        }
        int sum = left + num1 + num2;
        if (sum >= 10) {
            sum = sum - 10;
            left = 1;
        } else {
            left = 0;
        }
        res.push_back(sum);
    }
    ListNode *result = new ListNode(res.back());
    res.pop_back();
    cur = result;
    while (res.size() > 0) {
        int num = res.back();
        ListNode *temp = new ListNode(num);
        cur->next = temp;
        cur = temp;
        res.pop_back();
    }
    return result;
}

// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/
ListNode* deleteDuplicates2(ListNode* head) {
    if (head == nullptr) {
        return head;
    }
    ListNode *pre = nullptr;
    ListNode *cur = head;
    while (cur != nullptr) {
        bool repeat = false;
        ListNode *next = cur->next;
        if (next != nullptr) {
            if (next->val == cur->val) { //cur 开始重复
                repeat = true;
                while(next != nullptr && next->val == cur->val) {
                    next = next->next;
                }
                ListNode *lastNot = next != nullptr ? next : nullptr;
                if (pre != nullptr) {
                    pre->next = lastNot;
                    cur = lastNot;
                } else {
                    head = lastNot;
                    cur = head;
                }
            }
        }
        if (!repeat) {
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

// https://leetcode-cn.com/problems/swap-nodes-in-pairs/
ListNode* swapPairs(ListNode* head) {
    ListNode *preRes = new ListNode(0);
    ListNode *preHead = preRes;
    preHead->next = head;
    while(preHead->next && preHead->next->next) {
        ListNode* node1 = preHead->next;
        ListNode *node2 = node1->next;
        ListNode *next = node2->next;
        
        node2->next = node1;
        preHead->next = node2;
        node1->next = next;
        preHead = node1;
    }
    return preRes->next;
}

// https://leetcode-cn.com/problems/insertion-sort-list/
ListNode* insertionSortList(ListNode* head) {
    if (head == nullptr) {
        return head;
    }
    ListNode *preResult = new ListNode(0);
    preResult->next = head;
    ListNode *curProduce = head;
    ListNode *curConsumer = head;
    while (curProduce->next) {
        if (curConsumer->val <= curProduce->next->val) {
            curConsumer->next = curProduce->next;
            curProduce = curProduce->next;
            curConsumer = curConsumer->next;
        } else {
            ListNode *find = preResult->next;
            ListNode *findPre = nullptr;
            while (find) {
                if (find->val > curProduce->next->val || find->val == curConsumer->val) {
                    break;
                }
                findPre = find;
                find = find->next;
            }
            if (findPre) {//比他小的第一个数next指向他
                findPre->next = curProduce->next;
                
            } else {
                preResult->next = curProduce->next;
            }
            ListNode *temp = curProduce->next->next;
            curProduce->next->next = find; //他指向比他大的数
            curProduce->next = temp;//往后继续
        }
    }
    return  preResult->next;
}

// https://leetcode-cn.com/problems/sort-list/
ListNode* quickSort(ListNode *head,ListNode *end) {
    if (head == end || head->next == nullptr || head->next == end || head->next == nullptr || head->next->next == end) {
        return head;
    }
    ListNode *tempHead = new ListNode(-1);
    ListNode *tp = tempHead;
    ListNode *partition = head->next;
    ListNode *p = head->next;
    
    // store the small one in new list
    while (p->next != end) {
        if (p->next->val < partition->val){
            tp->next = p->next;
            tp = tp->next;
            p->next = p->next->next;
        }else {
            p = p->next;
        }
    }
    // merge lists
    tp->next = head->next;
    // put back in origin list
    head->next = tempHead->next;
    quickSort(head,partition);
    quickSort(partition,end);
    // remove pre head
    return head->next;
}
ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *preHead = new ListNode(-1);
    preHead->next = head;
    return quickSort(preHead, nullptr);
}

// https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *pre = new ListNode(-1);
    ListNode *result = pre;
    pre->next = head;
    ListNode *cur = pre;
    for (int i = 0; i < n+1; i++) {
        cur = cur->next;
    }
    while (cur) {
        pre = pre->next;
        cur = cur->next;
    }
    if(pre) {
        pre->next = pre->next->next;
    }
    return result->next;
}

// https://leetcode-cn.com/problems/rotate-list/
ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *pre = new ListNode(-1);
    ListNode *result = pre;
    pre->next = head;
    ListNode *cur = head;
    
    int time = 0;
    while (cur) {
        time++;
        cur = cur->next;
    }
    cur = result->next;
    if(k > time) {
        time = k % time;
    } else {
        time = k;
    }
    for (int i = 0; i < time; i++) {
        cur = result->next; //头结点
        pre = result;  //前一个简单
        ListNode *record = result->next; //删除后的头结点
        // find last
        while(cur->next != nullptr) {
            pre = cur;
            cur = cur->next;
        }
        pre->next = nullptr;
        result->next = cur;
        cur->next = record;
    }
    return result->next;
}

// https://leetcode-cn.com/problems/reverse-nodes-in-k-group/
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode *preHead = new ListNode(0);
    ListNode *prev = preHead;
    ListNode *cur = head;
    preHead->next = head;
    int length = 0;
    while(cur != nullptr) {
        length++;
        cur = cur->next;
    }
    //reset cur
    cur = preHead->next;
    for(int i = 0 ; i < length/k; i++) {
        for (int j = 0; j < k-1 ; j++) {
            ListNode *next = cur->next;
            cur->next = next->next; //删除next
            next->next = prev->next; // 设定好中间删除的下一个是prev的下一个
            prev->next = next; //插入到前面
        }
        prev = cur;
        cur = prev->next;
    }
    
    return preHead->next;
}

#pragma mark - greedy

// https://leetcode-cn.com/problems/assign-cookies/
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(s.begin(),s.end(),greater<int>());
    sort(g.begin(),g.end(),greater<int>());
    int res = 0;
    int si = 0;
    int gi = 0;
    while(si < s.size() && gi < g.size()) {
        if(s[si] >= g[gi]) {
            si++;
            gi++;
            res++;
        } else {
            gi++;
        }
    }
    return res;
}

// https://leetcode-cn.com/problems/is-subsequence/
bool isSubsequence(string s, string t) {
    int si = 0;
    int ti = 0;
    while(si < s.size() && ti < t.size()) {
        if (s[si] == t[ti]) {
            si++;
            ti++;
        } else {
            ti++;
        }
    }
    return si == s.size();
}

// https://leetcode-cn.com/problems/non-overlapping-intervals/
bool compareIntervalsEnd(vector<int> intervalA, vector<int> intervalB) {
    return intervalA[1] < intervalB[1];
}
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    stable_sort(intervals.begin(), intervals.end(), compareIntervalsEnd);
    int res = 1; //区间个数
    int end = intervals[0][1]; //分割点
    
    for (int i = 1; i < intervals.size();i++) {
        if (end <= intervals[i][0]) { // end 比下一个节点的起始值小
            end = intervals[i][1]; //end切换到下一个节点
            res++;
        }
    }
    return (int)intervals.size() - res;
}

#pragma mark - dynamic programming

// https://leetcode-cn.com/problems/climbing-stairs/
int climbStairs(int n) {
    vector<int> memRecord;
    memRecord = vector<int>(n + 1, -1);
    memRecord[0] = 1;
    memRecord[1] = 1;
    for(int i = 2; i <= n; i++) {
        memRecord[i] = memRecord[i - 1] + memRecord[i - 2];
    }
    return memRecord[n];
}

// --------------------------- Medium -------------------------------------

// https://leetcode-cn.com/problems/triangle/
int minimumTotal(vector<vector<int>>& triangle) {
    int size = (int)triangle.size();
    vector<vector<int>> memRecord = vector<vector<int>>(size, vector<int>(size));
    memRecord[0][0] = triangle[0][0];
    for (int i = 1; i < size; ++i) {
        memRecord[i][0] = memRecord[i - 1][0] + triangle[i][0];
        for (int j = 1; j < i; ++j) {
            memRecord[i][j] = min(memRecord[i-1][j-1], memRecord[i-1][j]) + triangle[i][j];
        }
        memRecord[i][i] = memRecord[i-1][i-1] + triangle[i][i];
    }
    return *min_element(memRecord[size-1].begin(),memRecord[size-1].end());
}

// https://leetcode-cn.com/problems/integer-break/
int integerBreak(int n) {
    vector<int> temp(n+1,-1);
    temp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            // j , i - j
            temp[i] = max(temp[i],max(j * (i - j),j * temp[i - j]));
        }
    }
    return temp[n];
}

// https://leetcode-cn.com/problems/perfect-squares/
/*
 定义一个函数f(n)表示我们要求的解。f(n)的求解过程为：
 f(n) = 1 + min{
    f(n-1^2), f(n-2^2), f(n-3^2), f(n-4^2), ... , f(n-k^2) //(k为满足k^2<=n的最大的k)
 }
 因为这里面任意一个加上对应(1->k)^2也就是一个数就可以得到 f(n)
*/
int numSquares(int n) {
    vector<int> f(n+1, 0);//n+1大小，f[0]为0
    for (int i = 1; i <= n; i++) {//从f[1]开始计算
        int minVal = INT_MAX;
        for ( int j = 1; j*j <= i ; j++ )
            minVal = min(minVal, f[i - j*j]);
        f[i] = minVal + 1;
    }
    return f[n];
}

// https://leetcode-cn.com/problems/decode-ways/
int numDecodings(string s) {
    int n = (int)s.size();
    vector<int> f(n + 1);
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] != '0') {
            f[i] += f[i - 1];
        }
        if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
            f[i] += f[i - 2];
        }
    }
    return f[n];
}

// https://leetcode-cn.com/problems/unique-paths/
int uniquePaths(int m, int n) {
    if(m < 2 || n < 2) {
        return 1;
    }
    vector<int> temp(n+1,1);
    vector<vector<int>> f(m+1,temp);
    for (int i = 2; i <= m; i++) { //行
        for (int j = 2; j <= n; j++) {
            f[i][j] = f[i-1][j] + f[i][j-1];
        }
    }
    return f[m][n];
}

// https://leetcode-cn.com/problems/unique-paths-ii/
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = (int)obstacleGrid.size();
    int n = 0;
    if (m) {
        n = (int)obstacleGrid[0].size();
    }
    if (m < 2 || n < 2) {
        if( m && n ) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (obstacleGrid[i][j]) {
                        return 0;
                    }
                }
            }
        }
        return 1;
    }

    vector<int> temp(n+1,1);
    vector<vector<int>> f(m+1,temp);

    // 第一行中存在阻碍
    bool haveObstacle = false;
    for (int i = 0;i < n; i++) {
        if(obstacleGrid[0][i])
            haveObstacle = true;
        if(haveObstacle)
            f[1][i+1] = 0;
    }

    // 第一列中存在阻碍
    haveObstacle = false;
    for (int i = 0;i < m; i++) {
        if(obstacleGrid[i][0])
            haveObstacle = true;
        if(haveObstacle)
            f[i+1][1] = 0;
    }
    
    for (int i = 2; i <= m; i++) { //行
        for (int j = 2; j <= n; j++) {
            if ((obstacleGrid[i-2][j-1] && obstacleGrid[i-1][j-2]) || obstacleGrid[i-1][j-1]) {
                f[i][j] = 0;
            } else if (obstacleGrid[i-2][j-1]) {
                f[i][j] = f[i][j-1];
            } else if (obstacleGrid[i-1][j-2]) {
                f[i][j] = f[i-1][j];
            } else {
                f[i][j] = f[i-1][j] + f[i][j-1];
            }
        }
    }
    return f[m][n];
}

#endif //CPLUS_LEETCODE_HPP
