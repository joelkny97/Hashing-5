// Time Complexity: O(nl) where n is the number of words and l is the length of the longest word
// Space Complexity: O(1)
// Were you able to run the code on Leetcode: Yes
// Any problem you faced while coding this: No


class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> order_map;

        // build the order map for all the characters in the order string
        for(int i=0; i<order.size(); i++){
            order_map[order[i]] = i;
        }

        // check pairs of words starting from 0th and 1st word and compare each word to estacblish order
        for (int i=1; i<words.size(); i++) {
            
            string currStr = words[i];
            string prevStr = words[i-1]; 

            // init pointers for both strings to check the if they are lexographically sorted based on the given order
            int cPtr=0, pPtr=0;
            // get the minimum length of both strings to compare only the min of those characters
            // we assume that if two strings are of different length, the longer string is lexographically greater 
            // than the shorter string if the shorter string is a prefix of the longer string
            // in other cases where the prev string is not a prefix of the current string, we check the order using the mapping indices
            // if prev string contains an element with higher index than the curr string, we return false
            int minL = min(currStr.size(), prevStr.size());
            bool diffFound = false;
            while(cPtr < minL && pPtr < minL){

                if (currStr[cPtr] != prevStr[pPtr]){
                    
                    if ( order_map[currStr[cPtr]] < order_map[prevStr[pPtr]] ) return false;
                    // flag used to track if a difference is found
                    diffFound = true;
                    break;  // order decided, no need to check further

                }
                cPtr++;
                pPtr++;
            }
            
            // if no diff found in the first minL characters, check if the prev string is longer than the curr string
            // if so, return false
            if (!diffFound && prevStr.size() > currStr.size()) {
                return false;
            }

    
        }
        // if all the pairs of words are lexographically sorted based on the given order, return true
        return true;
    }
};