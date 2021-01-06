#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 10001;
int heap[MAXN], siz;
void go_up(int x) {
    int tmp = heap[x];
    while (tmp < heap[x >> 1]) {
        heap[x] = heap[x >> 1];
        x >>= 1;
    }
    heap[x] = tmp;
}
void go_down(int x) {
    int child;
    int tmp = heap[x];
    while ((x << 1) <= siz) {
        child = (x << 1);
        if (child < siz && heap[child] > heap[child + 1]) child++;
        if (tmp > heap[child]) {
            heap[x] = heap[child];
            x = child;
        }
        else break;
    }
    heap[x] = tmp;
}
void Add(int x) {
    heap[++siz] = x;
    go_up(siz);
}
int Search() {
    return heap[1];
}
void Delete() {
    swap(heap[1], heap[siz]);
    siz--;
    go_down(1);
}
int main() {
    heap[0] = -0x7fffffff;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        Add(k);
    }
    int sum = 0;
    for (int i = 1; i < n; i++) {
        int a = Search();
        Delete();
        int b = Search();
        Delete();
        Add(a + b);
        sum += a + b;
    }
    printf("%d", sum);
    return 0;
}