// using_heaps.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <functional>
#include <queue>
//#include <vector>


template<typename T>
void print_queue(T q) { // NB: pass by value so the print uses a copy
    while (!q.empty()) {
        std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << '\n';
}

//int main() {
//    std::priority_queue<int> q;
//
//    const auto data = { 1,8,5,6,3,4,0,9,7,2 };
//
//    for (int n : data)
//        q.push(n);
//
//    print_queue(q);
//
//    std::priority_queue<int, std::vector<int>, std::greater<int>>
//        q2(data.begin(), data.end());
//
//    print_queue(q2);
//
//    // Using lambda to compare elements.
//    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
//    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
//
//    for (int n : data)
//        q3.push(n);
//
//    print_queue(q3);
//}

class log_time_median
{

public:
    std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
    std::priority_queue<int> q1;
    int even = 1;

public:
    void push(int n)
    {
        
        if (q2.empty())
        {
            q2.push(n);
            even = 1 - even;
            return;
        }
        //else if (q1.empty())
        //{
        //    int x = q2.top();

        //    q1.push(n);
        //    return;
        //}

        if (even == 1)
        {
            int x = q1.top();
            if (n >= x)
                q2.push(n);
            else
            {
                q1.push(n);
                q1.pop();
                q2.push(x);
            }
        }
        else
        {
            int x = q2.top();
            if (n <= x)
                q1.push(n);
            else
            {
                q2.push(n);
                q2.pop();
                q1.push(x);
            }
        }
        even = 1 - even;
    }

    float get_median()
    {
        float med=0;
        if (even == 1)
        {
            if (q1.empty())
            {
                med = q2.top();
            }
            else
            {
                med = (static_cast<float>(q1.top()) + q2.top()) / 2;
            }

        }
        else 
        {
            if (q2.empty())
            { // this means our data struct is empty, and the median is undefined.
                med = 0;
            }
            else
            {
                med = q2.top();
            }

        }
        return med;
    }


};


int main()
{
    const auto data = { 1,8,5,6,3,4,0,9,7,2 };
    log_time_median ltm;

    for (int n : data)
    {
        // this is just for debugging
        //ltm.q2.push(n);
        //print_queue(ltm.q2);

        // uncomment this when done:
        ltm.push(n);
        std::cout << "the median: " << ltm.get_median() << std::endl;

        std::cout << "low Q: " << std::endl;
        print_queue(ltm.q1);
        std::cout << "hi Q: " << std::endl;
        print_queue(ltm.q2);
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
