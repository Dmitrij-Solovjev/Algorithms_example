#include <iostream>
#include <random>
#include <algorithm>
#include <string>

typedef int Priority;

struct node {
    Priority priority;
    node *next, *prev;
    std::string Report;

    node(Priority _priority, node *_next, node *_prev, std::string _Report) {
        priority = _priority;
        next = _next;
        prev = _prev;
        Report = _Report;
    }
};

typedef node *link;
link randlist(int);
link scanlist(int &);
void showlist(link);

void showlist(link head) {
    if (head == nullptr) return;
/*    if (head->prev == nullptr) std::cout <<"(null<-";
    else std::cout <<" ("<<head->prev->priority<<"<-";
*/    std:: cout <<"  (" <<head->priority << " " << head->Report << ")  ";
    if (head->next == nullptr) std::cout <<"->null)" <<std::endl;
    else {//std::cout <<"->"<<head->next->priority<<") ";
        showlist(head->next);
    }
}

void showReport(link foot) {
    if (foot == nullptr) return;
    if (foot->prev != nullptr) {std::cout << foot->Report << std::endl; showReport(foot->prev);}
    else std::cout << foot->Report << std::endl;
}

link scanlist(int N) {
    int priority = 0; std::string rep;
    std::cin >> priority;
    std::cin >> rep;
    link ulala;
    if (N != 0) ulala = scanlist(N - 1);
    else ulala = nullptr;
    link t = new node(priority, ulala, nullptr, rep);
    if (t->next != nullptr) t->next->prev = t;
    return t;
}

link max(link A, link B){
    if (A->next->priority > B->next->priority) return A;
    else return B;
}

link findmax(link head) {
    if (head->next->next != nullptr) {
        return max(findmax(head->next), head);
    } else return head;
}

std::pair <link, link> linklistselection(link h) {
    node dummy(0, nullptr, nullptr, "");
    link head = &dummy;
    link out = nullptr;
    head->next = h;
    link in = nullptr;
    while (head->next != nullptr) {
        link max = findmax(head);
        link t = max->next;
        if (max->next->next != nullptr) max->next->next->prev = max;
        max->next = max->next->next;
        t->next = out;
        if (out != nullptr) out->prev = t;
        if(in == nullptr) in = t;
        out = t;
    }
    out->prev= nullptr;
    std::pair <link, link> A(out, in);
    return A;
}

std::string Reports[] = {"I", "II", "III"};

link randlist(int N) {
    link next;
    if (N != 0) next = randlist(N - 1);
    else next = nullptr;
    int rand_val = rand()%3;
    link t = new node(rand_val, next, nullptr, Reports[rand_val]);
    if (t->next != nullptr) t->next->prev = t;
    return t;
}

int main() {
    link t = randlist(10);

    showlist(t);

    std::pair<link, link> sorted_t = linklistselection(t);
    showlist(sorted_t.first);
    std::cout << "Обработка данных по приоритету:" <<std::endl;
    showReport(sorted_t.second);
    return 0;
}
