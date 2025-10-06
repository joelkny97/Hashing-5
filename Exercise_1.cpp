// Time Complexity: O(V+E)
// Space Complexity: O(1)
// Were you able to run the code on Leetcode: No
// Any problem you faced while coding this: No

#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;


class Solution {
public:
    
    string alienOrder(vector<string>& words) {

        if (words.size() == 0) return "";

        int n = words.size();
        // topological sort approach
        // store indegrees of all 26 lowercase characters
        vector<int> indegrees (26, 0);
        unordered_map<char, vector<char>> adjList;
        string res;

        // initialize all letters in adjacency list
        for (auto &w : words)
            for (char c : w)
                if (!adjList.count(c))
                    adjList[c] = {};
    

        // build the graph adjacency list and indegrees
        // we compare pairs of words, current and previous word and check if there is a mismatch
        for (int i=1; i<n; i++) {
            string prev = words[i-1];
            string curr = words[i];
            
            int pSize = prev.size(); 
            int cSize = curr.size();

            // check if the previous word is a prefix of the current word then return empty string
            if (pSize > cSize && prev.substr(0, cSize) == curr)
                return "";
            
            // check if there is a mismatch in the first m and n characters
            // if there is a mismatch, the character in the curr word indegree count is incremented 
            // and the incoming curr character is added to the adjacency list for that prev character establishing order of letters
            for (int j = 0; j<pSize && j<cSize; j++) {

                if (prev[j] != curr[j]) {
                    indegrees[curr[j]-'a']++;
                    adjList[prev[j]].push_back(curr[j]);
                    // break after mismatch is processed
                    break;
                }
            }

        }

        queue<char> q;

        // add all elements that have 0 indeg count in queue
        for(auto it: adjList) {
            int index = it.first-'a';
            if (indegrees[index] == 0){
                q.push(it.first);
            }
        }

        // Start BFS (Kahns Algorithm)
        // pop elements from the queue and add them to the result string
        // get the adjacent elements of the popped element and decrement their indegrees
        // if the adjacent element's indegrees is 0, add it to the queue

        while (!q.empty()) {
            
            
            char el = q.front();
            q.pop();
            res+=el;

            if (adjList.count(el) == 0) continue;
            
            for (char& ne: adjList[el]) {
                indegrees[ne-'a']--;
                if (indegrees[ne-'a'] == 0) {
                    q.push(ne);
                }
            }
            

        }

        // if the result string is not equal to the number of elements in the adjacency list, return empty string
        // there exists a cycle in the graph
        if (res.size() < adjList.size())
            return "";

        return res;

    }
};

// Main
int main() 
{ 

    // int n = sizeof(words)/sizeof(words[0]); 
    Solution ob;
    
    // 1️⃣ Standard example — expected "wertf"
    vector<string> words1 = {"wrt","wrf","er","ett","rftt"};
    cout << "Case 1: " << ob.alienOrder(words1) << endl; // ✅ "wertf"

    // 2️⃣ Simple ordering — expected "zx"
    vector<string> words2 = {"z","x"};
    cout << "Case 2: " << ob.alienOrder(words2) << endl; // ✅ "zx"

    // 3️⃣ Cycle present — expected ""
    vector<string> words3 = {"z","x","z"};
    cout << "Case 3: " << ob.alienOrder(words3) << endl;


    // 4️⃣ Prefix invalid (longer word before its prefix) — expected ""
    vector<string> words4 = {"abc","ab"};
    cout << "Case 4: " << ob.alienOrder(words4) << endl; // ✅ ""


    return 0; 
}