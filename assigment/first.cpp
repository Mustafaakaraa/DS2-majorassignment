#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <numeric>
#include <set>
using namespace std;

// Problem 12
class Solution12 {

    int Sequence(int length, int start, int end)
    {
        if (length == 0) return 1;

        if (start > end) return 0;

        auto result = 0;

        for (int i = start; i <= end; i++)
        {
            result += Sequence(length - 1, i * 2, end);
        }

        return result;

    }

public:
    int numberSequence(int m, int n)
    {
        auto ret = Sequence(n, 1, m);

        return ret;
    }
};

// Problem 11
class Solution11
{
public:
    int isPossible(int A[], int N, int M, int mid) {
        int pageSum = 0;
        int count = 1;
        for (int i = 0; i < N; i++) {
            if (A[i] > mid) {
                return false;
            }
            if (A[i] + pageSum > mid) {
                count++;
                pageSum = A[i];

                if (count > M) {
                    return false;
                }
            }
            else {
                pageSum = pageSum + A[i];
            }
        }

        return true;
    }
    int findPages(int A[], int N, int M)
    {
        if (M > N) {
            return -1;
        }
        int ans = -1;
        int start = 0;
        int end = accumulate(A, A + N, 0);

        while (start <= end) {
            int mid = (start + end) >> 1;
            if (isPossible(A, N, M, mid)) {
                ans = mid;
                end = mid - 1;
            }
            else {
                start = mid + 1;
            }

        }
        return ans;
    }
};

// Problem 10
class Solution10 {
public:
    int kthElement(int arr1[], int arr2[], int n, int m, int k)
    {
        int i = 0;
        int j = 0;
        int count = 1;
        while (i < n && j < m) {
            if (arr1[i] <= arr2[j]) {

                if (count == k)return arr1[i];
                count++;
                i++;
            }
            else {

                if (count == k)return arr2[j];
                count++;
                j++;
            }
        }
        while (i < n) {

            if (count == k)return arr1[i];
            count++;
            i++;
        }
        while (j < m) {

            if (count == k)return arr2[j];
            count++;
            j++;
        }
        return 0;
    }
};

// Problem 9
class Solution9 {
public:
    static const int M = 4;
    static const int N = 4;

    string dictionary[M] = { "GEEKS", "FOR", "QUIZ", "GO" };
    int n = sizeof(dictionary) / sizeof(dictionary[0]);

    bool isWord(string& str)
    {
        for (int i = 0; i < n; i++)
            if (str.compare(dictionary[i]) == 0)
                return true;
        return false;
    }
    void findWordsUtil(char boggle[M][N], bool visited[M][N], int i,
        int j, string& str)
    {
        visited[i][j] = true;
        str = str + boggle[i][j];

        if (isWord(str))
            cout << str << endl;

        for (int row = i - 1; row <= i + 1 && row < M; row++)
            for (int col = j - 1; col <= j + 1 && col < N; col++)
                if (row >= 0 && col >= 0 && !visited[row][col])
                    findWordsUtil(boggle, visited, row, col, str);
        str.erase(str.length() - 1);
        visited[i][j] = false;
    }

    void findWords(char boggle[M][N])
    {
        bool visited[M][N] = { { false } };

        string str = "";

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                findWordsUtil(boggle, visited, i, j, str);
    }
};

// Problem 8
class Solution8 {
public:
    set<string> ans;

    bool check(string s) {
        int count = 0;
        int num = 0;
        string s2;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '.') {
                count++;
                num = 0;
                s2 = "";
            }
            else {
                s2.push_back(s[i]);
                if (s2.length() > 1 && s2[0] == '0')
                    return false;
                int num = stoi(s2);
                if (num > 255)
                    return false;
            }
        }

        if (s[0] != '.' && count == 4 && s.back() == '.')
            return true;

        return false;
    }

    void help(string s, string s1) {
        int n = s.length();
        if (n == 0) {
            if (check(s1)) {
                s1.pop_back();
                ans.insert(s1);
            }
            return;
        }
        for (int i = 0; i < n; i++) {
            help(s.substr(i + 1), s1 + s.substr(0, i + 1) + ".");
        }
    }

    vector<string> genIp(string& s) {
        ans.clear();
        help(s, "");

        vector<string> v;

        if (!ans.empty()) {
            for (auto& x : ans) {
                v.push_back(x);
            }
        }
        else {
            v.push_back("-1");
        }

        return v;
    }
};

// Problem 7
class Solution7 {
public:
    bool isSafe(int id, bool mat[101][101], vector<int>& colors, int n, int col) {
        for (int j = 0; j < n; j++) {
            if (j != id && mat[j][id] == 1 && colors[j] == col) return false;
        }
        return true;
    }

    bool solve(int id, bool mat[101][101], vector<int>& colors, int m, int n) {
        if (id == n) return true;


        for (int i = 1; i <= m; i++) {
            if (isSafe(id, mat, colors, n, i)) {
                colors[id] = i;
                if (solve(id + 1, mat, colors, m, n)) return true;

                colors[id] = 0;
            }
        }
        return false;
    }

    bool graphColoring(bool mat[101][101], int m, int n) {
        vector<int> colors(n, 0);

        if (solve(0, mat, colors, m, n)) {
            return true;
        }
        return false;

    }
};

// Problem 6
class Solution6 {
public:
    void solve(int row, int col, vector<string>& ans, string& path, vector<vector<int>>& m, int n, vector<vector<int>>& visited) {
        if (row == n - 1 && col == n - 1) {
            ans.push_back(path);
            return;
        }
        int drow[] = { -1,0,1,0 };
        int dcol[] = { 0,1,0,-1 };
        char dir[] = { 'U','R','D','L' };
        for (int i = 0; i < 4; i++) {
            int nrow = row + drow[i];
            int ncol = col + dcol[i];
            if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < n && visited[nrow][ncol] == 0 && m[nrow][ncol] == 1) {
                visited[nrow][ncol] = 1;
                path += dir[i];
                solve(nrow, ncol, ans, path, m, n, visited);
                visited[nrow][ncol] = 0;
                path.pop_back();
            }
        }
    }
    vector<string> findPath(vector<vector<int>>& m, int n) {
        if (m[0][0] == 0)return { "-1" };
        vector<string>ans;
        string path = "";
        vector<vector<int>>visited(n, vector<int>(n, 0));
        visited[0][0] = 1;
        solve(0, 0, ans, path, m, n, visited);
        return ans;
    }
};

// Problem 5
class Solution5 {
public:
    static bool cmp(pair<int, int> p1, pair<int, int> p2) {
        return p1.second < p2.second;
    }
    int maxChainLen(pair<int, int> p[], int n) {
        sort(p, p + n, cmp);
        int count = 1;
        int x = p[0].second;
        for (int i = 0; i < n - 1; i++) {
            if (x < p[i + 1].first) {
                count++;
                x = p[i + 1].second;
            }
        }
        return count;
    }
};

// Problem 4
class Solution4 {
public:
    int maxChainLength(pair<int, int> arr[], int n)
    {
        int i, j, max = 0;
        int* mcl = new int[sizeof(int) * n];

        for (i = 0; i < n; i++)
            mcl[i] = 1;

        for (i = 1; i < n; i++)
            for (j = 0; j < i; j++)
                if (arr[i].first > arr[j].second &&
                    mcl[i] < mcl[j] + 1)
                    mcl[i] = mcl[j] + 1;


        for (i = 0; i < n; i++)
            if (max < mcl[i])
                max = mcl[i];

        delete[] mcl;

        return max;
    }
};

// Problem 3
int maxMeetings(int start[], int end[], int n) {

    multimap<int, int> mp;
    for (int i = 0; i < n; i++)
        mp.insert(pair<int, int>(end[i], start[i]));


    int dp[n];
    dp[0] = 1;


    for (int i = 1; i < n; i++) {

        auto it = mp.begin();
        while (it != mp.end() && it->first < end[i])
            it++;
        dp[i] = max(dp[i - 1], dp[distance(mp.begin(), it)] + 1);
    }


    return dp[n - 1];
}

// Problem 2
class Solution2
{
public:
    static bool cmp(int J1[], int J2[]) {
        if (J1[1] != J2[1])
            return J1[1] < J2[1];
        return J1[0] > J2[0];
    }


    vector<int> JobScheduling(int arr[][2], int n) {
        sort(arr, arr + n, cmp);
        int curr = 0;
        int p = 0;

        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 0; i < n; i++) {
            int* J1 = arr[i];
            if (curr < J1[1]) {
                curr++;
                pq.push(J1[0]);
            }
            else if (curr == J1[1] and pq.top() < J1[0]) {
                pq.pop();
                pq.push(J1[0]);
            }
        }

        while (!pq.empty()) {
            p += pq.top();
            pq.pop();
        }

        return { curr, p };
    }
};

// Problem 1
int maxMeetings(int start[], int end[], int n)
{
    multimap<int, int> mp;
    for (int i = 0; i < n; i++)
        mp.insert(pair<int, int>(end[i], start[i]));
    int cnt = 1;
    int temp = mp.begin()->first;
    for (auto it : mp)
    {
        if (temp < it.second)
        {
            cnt++;
            temp = it.first;
        }
    }
    return cnt;
}

int main() {
    // Problem 12
    Solution12 sol12;
    int result12 = sol12.numberSequence(3, 3);
    cout << "Problem 12 Result: " << result12 << endl;

    // Problem 11
    Solution11 sol11;
    int arr11[] = { 10, 20, 30, 40 };
    int result11 = sol11.findPages(arr11, 4, 2);
    cout << "Problem 11 Result: " << result11 << endl;

    // Problem 10
    Solution10 sol10;
    int arr1[] = { 2, 3, 6, 7, 9 };
    int arr2[] = { 1, 4, 8, 10 };
    int result10 = sol10.kthElement(arr1, arr2, 5, 4, 5);
    cout << "Problem 10 Result: " << result10 << endl;

    // Problem 9
    Solution9 sol9;
    char boggle[Solution9::M][Solution9::N] = { { 'G', 'I', 'Z' },
                                                { 'U', 'E', 'K' },
                                                { 'Q', 'S', 'E' } };
    cout << "Problem 9 Result:" << endl;
    sol9.findWords(boggle);

    // Problem 8
    Solution8 sol8;
    string ip = "25525511135";
    vector<string> result8 = sol8.genIp(ip);
    cout << "Problem 8 Result:" << endl;
    for (const auto& ip : result8) {
        cout << ip << endl;
    }

    // Problem 7
    Solution7 sol7;
    bool graph[101][101] = { {0, 1, 1}, {1, 0, 1}, {1, 1, 0} };
    bool result7 = sol7.graphColoring(graph, 3, 3);
    cout << "Problem 7 Result: " << result7 << endl;

    // Problem 6
    Solution6 sol6;
    vector<vector<int>> maze = { {1, 0, 0, 0},
                                {1, 1, 0, 1},
                                {0, 1, 0, 0},
                                {1, 1, 1, 1} };
    vector<string> result6 = sol6.findPath(maze, 4);
    cout << "Problem 6 Result:" << endl;
    for (const auto& path : result6) {
        cout << path << endl;
    }

    // Problem 5
    Solution5 sol5;
    pair<int, int> p[] = { {5, 24}, {15, 25}, {27, 40}, {50, 60} };
    int result5 = sol5.maxChainLen(p, 4);
    cout << "Problem 5 Result: " << result5 << endl;

    // Problem 4
    Solution4 sol4;
    pair<int, int> arr[] = { {5, 24}, {15, 25}, {27, 40}, {50, 60} };
    int n4 = sizeof(arr) / sizeof(arr[0]);
    int result4 = sol4.maxChainLength(arr, n4);
    cout << "Problem 4 Result: " << result4 << endl;

    // Problem 3
    int start[] = { 1, 3, 0, 5, 8, 5 };
    int end[] = { 2, 4, 6, 7, 9, 9 };
    int result3 = maxMeetings(start, end, 6);
    cout << "Problem 3 Result: " << result3 << endl;

    // Problem 2
    Solution2 sol2;
    int jobs[][2] = { {1, 2}, {3, 5}, {6, 19}, {2, 100} };
    int n2 = sizeof(jobs) / sizeof(jobs[0]);
    vector<int> result2 = sol2.JobScheduling(jobs, n2);
    cout << "Problem 2 Result:" << endl;
    for (const auto& val : result2) {
        cout << val << endl;
    }

    // Problem 1
    int start1[] = { 1, 3, 0, 5, 8, 5 };
    int end1[] = { 2, 4, 6, 7, 9, 9 };
    int result1 = maxMeetings(start1, end1, 6);
    cout << "Problem 1 Result: " << result1 << endl;

    return 0;
}
