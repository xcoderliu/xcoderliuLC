//
//  main.cpp
//  cppLeetCode
//
//  Created by xcoderliu on 4/23/22.
//

#include <iostream>
#import <vector>
#import "LRU.hpp"
#import "leetcode.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    //    vector<int> nums = {0, 1, 0, 3, 12};
    //    quickSort(nums,0,nums.size() - 1);
    //    for (int i = 0; i < nums.size(); ++i) {
    //        cout << nums.at(i) << ",";
    //    }
    //
    //    vector<int> nums = {1, 2, 4, 7, 11, 16, 21, 90};
    //    auto result = twoSum(nums, 27);
    //    for (int i = 0; i < result.size(); ++i) {
    //        cout << result.at(i) << ",";
    //    }
    //    cout << (isPalindrome("liuzhiminnimihzuil") ? "true" : "false") << endl;
    //    vector<int> nums = {2,3,1,2,4,3};
    //    cout << minSubArrayLen(7, nums) << endl;
    //
    
    addBinary("101111", "10");
    
    vector<vector<int>> obstacleGrid;
    obstacleGrid.push_back({0,0,0});
    obstacleGrid.push_back({0,1,0});
    obstacleGrid.push_back({0,0,0});
    uniquePathsWithObstacles(obstacleGrid);
    
    vector<vector<int>> matrix;
    matrix.push_back({9,8,7,6});
    matrix.push_back({2,3,2,5});
    matrix.push_back({7,8,9,7});
    matrix.push_back({5,4,3,2});
    matrix.push_back({6,7,8,9});
    largestPalindromicSubmatrix(matrix);
    
    TreeNode one = TreeNode(1);
    TreeNode two = TreeNode(2);
    TreeNode three = TreeNode(3);
    TreeNode four = TreeNode(4);
    TreeNode five = TreeNode(5);
    TreeNode six = TreeNode(6);
    TreeNode seven = TreeNode(7);
    TreeNode eight = TreeNode(8);
    
    one.left = &two;
    one.right = &three;
    two.left = &four;
    two.right = &five;
    three.right = &six;
    five.left = &seven;
    five.right = &eight;
    preorderTraversal(&one);
    inorderTraverse(&one);
    postorderTraverse(&one);
    levelOrder(&one);
    levelOrderBottom(&one);
    zigzagLevelOrder(&one);
    auto binaryTreePathsResult = sumNumbers(&one);
    cout << &binaryTreePathsResult << endl;
    
//    TreeNode *ac = lowestCommonAncestor(&one, &seven,&five);
    //
    //    levelOrder(&one);
    
    //    int a[] = {7,2,4,3};
    //    ListNode *l1 = createList(a, sizeof(a)/sizeof(int));
    //    printLinkedList(l1);
    //    reverseBetween(&head,1,5);
    //    head = reverseList(head);
    //    printLinkedList(head);
    //    deleteDuplicates(head);
    //    printLinkedList(head);
    //    partition(head,3);
    //    printLinkedList(head);
    //    oddEvenList(head);
    //    printLinkedList(head);
    //    deleteLinkedList(head);
    //    int b[] = {5,6,4};
    //    ListNode *l2 = createList(b, sizeof(b)/sizeof(int));
    //    printLinkedList(l2);
    //
    //    ListNode *l3 = addTwoNumbers2(l1, l2);
    //    printLinkedList(l3);
    //
    //    int a[] = {1,0,0};
    //    ListNode *list = createList(a, sizeof(a)/sizeof(int));
    //    printLinkedList(list);
    //
    //    bool result = isPalindrome(list);
    //    printLinkedList(list);
    
    //    cout << isHappy(19) << endl;
    
    //    cout << wordPattern("abba", "dog cat cat fish");
    //    vector<string> array = {"eat", "tea", "tan", "ate", "nat", "bat"};
    //    groupAnagrams(array);
    
    //    vector<vector<int>> triangle ={{2},{3,4},{6,5,7},{4,1,8,3}};
    //    cout << minimumTotal(triangle) << endl;
    
    simplifyPath("/a//b////c/d//././/..");
    
    cout << numSquaresQueue(12) << endl;
    vector<string> ladderDic = {"hot","dot","dog","lot","log","cog"};
    cout << ladderLength("hit", "cog", ladderDic) << endl;
    findLadders("hit", "cog", ladderDic);
    vector<int> nums = {2, 3, 2, 3, 12};
    topKFrequent(nums,2);
    getchar();
    return 0;
}
