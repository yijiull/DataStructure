/*************************************************************************
  > File Name: 8sort.cpp
  > Author: yijiull
  > Mail: 1147161372@qq.com 
  > Created Time: 2017年11月14日 星期二 22时12分19秒
 ************************************************************************/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000010;
const int mod = 13131313;

int a[maxn], c[maxn], ary[maxn];
template <typename T>
void print(T *a, int n){
    for(int i = 0; i < n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

template <typename T>
void insertSort(T *a, int n){
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0 && a[j] < a[j-1]; j--){
            swap(a[j], a[j-1]);
        }
    }
}

template <typename T>
void bubbleSort(T *a, int n){
    for(int i = 0; i < n - 1; i++){
        int ok = 0;
        //０到ｉ已经排好序
        for(int j = n - 1; j > i; j--){
            if(a[j] < a[j-1]) {
                swap(a[j], a[j-1]);
                ok = 1;
            }
        }
        if(!ok) break;
    }
}
template <typename T>
void doubleSelectSort(T *a, int n){
    for(int i = 0; i < n; i++){
        //从ｊ到ｎ找到最小的元素和ｉ交换
        int min = i, max = n - 1 - i;
        for(int j = i; j <= n - 1 - i; j++){
            if(a[j] < a[min]) min = j;   //稳定
            if(a[j] > a[max]) max = j;
        }
        swap(a[i], a[min]);
        swap(a[n-i-1], a[max]);
    }
}
template <typename T>
void selectSort(T *a, int n){
    for(int i = 0; i < n; i++){
        //从ｊ到ｎ找到最小的元素和ｉ交换
        int id = i;
        for(int j = i + 1; j < n; j++){
            if(a[j] < a[id]) id = j;   //稳定
        }
        swap(a[i], a[id]);
    }
}

template <typename T>
void insertSort(T *a, int n, int from, int incr){
    for(int i = from + incr; i < n; i += incr){
        for(int j = i; j > from && a[j] < a[j-incr]; j -= incr){
            swap(a[j], a[j-incr]);
        }
    }
}
template <typename T>
void shellSort(T *a, int n){
    //分
    for(int i = n / 2; i >= 1; i /= 2){
        for(int j = 0; j < i; j++){
            insertSort(a, n, j, i);
        }
    }
}

template <typename T>
void quickSort(T *a, int s, int e, int n){
    if(s >= e) return ;
    //int id = (s+e)/2;
    int id = s;
    T temp = a[id];
    int i = s, j = e;
    while(i < j){
        while(j > i && a[j] >= temp) j--;
        a[i] = a[j];
        while(i < j && a[i] <= temp) i++;
        a[j] = a[i];
        //if(a[i] > a[j]) swap(a[i], a[j]);
    }
    a[i] = temp;
    quickSort(a, s, i-1, n);
    quickSort(a, i+1, e, n);
    return ; 
}
template <typename T>
void mergeSort(T *a, int l, int r, T *c){
    if(r - l > 1) {
        int m = l + (r - l) / 2;
        int p = l, q = m, i = l;
        mergeSort(a, l, m, c);
        mergeSort(a, m, r, c);
        while(p < m || q < r){
            if(q >= r || (p < m && a[p] <= a[q])) c[i++] = a[p++];
            else c[i++] = a[q++];
        }
        for(int i = l; i < r; i++) a[i] = c[i];
    }
}

//template <typename T>
//class MaxHeap{
//    public:
//        int cnt;
//        T heap[maxn];
//
//        MaxHeap(){}
//        MaxHeap(T *a, int n){
//            init(a, n);
//        }
//        void init(T *a, int n){
//            cnt = 0;
//            for(int i = 0; i < n; i++) heap[++cnt] = a[i];
//            for(int i = cnt / 2; i >= 1; i--) siftdown(i);
//        }
//        void init(){
//            cnt = 0;
//        }
//
//        void buildHeap(T *a, int n){
//            for(int i = 0; i < n; i++) heap[++cnt] = a[i];
//            for(int i = cnt / 2; i >= 1; i--) siftdown(i);
//        }
//        void siftdown(int pos){
//            while(pos <= cnt/2){
//                int ls = pos * 2;
//                int rs = pos * 2 + 1;
//                if(rs <= cnt && heap[ls] < heap[rs]){
//                    ls = rs;
//                }
//                if(heap[pos] >= heap[ls]) return ;
//                swap(heap[pos], heap[ls]);
//                pos = ls;
//            }
//        }
//        bool insert(T x){
//            int cur = ++cnt;
//            heap[cur] = x;
//            while(cur != 1 && heap[cur] > heap[cur/2]){
//                swap(heap[cur], heap[cur/2]);
//                cur /= 2;
//            }
//            return 1;
//        }
//        T removeMax(){
//            swap(heap[1], heap[cnt--]);
//            if(cnt != 1) siftdown(1);
//            return heap[cnt+1];
//        }
//        //?
//        void remove(int pos, T &it){
//            swap(heap[pos], heap[cnt--]);
//            while(pos != 1 && heap[pos] > heap[pos / 2]){
//                swap(heap[pos], heap[pos / 2]);
//                pos /= 2;
//            }
//            siftdown(pos);
//            it = heap[cnt+1];
//        }
//        void print(){
//            for(int i = 1; i <= cnt; i++) cout<<heap[i]<<" ";
//            cout<<endl;
//        }
//};
//MaxHeap<int> H;
//
//
//template <typename T>
//void heapSort(T *a, int n){
//    //MaxHeap<T> H(a, n);
//    //MaxHeap<T> H;
//    //H.init();
//    //for(int i = 0; i < n;  i++) H.insert(a[i]);
//    //H.print();
//    H.init(a, n);
//    for(int i = 0; i < n; i++){
//        a[n-i-1] = H.removeMax();
//    }
//}
void siftdown(int cur, int n){
    while(cur <= n/2){
        int ls = cur * 2;
        int rs = cur * 2 + 1;
        if(rs <= n && a[ls] < a[rs]) ls = rs;
        if(a[cur] >= a[ls]) break;
        swap(a[cur], a[ls]);
        cur = ls;
    }
}

template <typename T>
void buildHeap(T *a, int n){
    for(int i = n / 2; i >= 1; i--){
        siftdown(i, n);
    }
}

template <typename T>
void heapSort(T *a, int n){
    for(int i = n; i > 0; i--) a[i] = a[i-1];
    buildHeap(a, n);
    for(int i = n; i >= 1; i--){
        swap(a[1], a[i]);
        siftdown(1, i - 1);
    }
    for(int i = 0; i < n; i++){
        a[i] = a[i+1];
    }
}


template <typename T>
void binSort(T *a, int n, T *c){
    for(int i = 0; i < mod; i++){
        c[i] = 0;
    }
    for(int i = 0; i < n; i++){
        c[a[i]]++;
    }
    int cur = 0;
    for(int i = 0; i < mod; i++){
        for(int j = 0; j < c[i]; j++){
            a[cur++] = i;
        } 
    }
}

template <typename T> 
int maxBit(T *a, int n){
    int d = 1;
    int p = 10;
    for(int i = 0; i < n; i++){
        while(a[i] >= p){
            p *= 10;
            d++;
        }
    }
    return d;
}
template <typename T>
void radixSort(T *a, int n, T *c){
    int d = maxBit(a, n);
    int radix = 1;
    int *cnt = new int[10];
    for(int k = 1; k <= d; k++){
        for(int i = 0; i < 10; i++){
            cnt[i] = 0;
        }
        for(int i = 0; i < n; i++){
            int k = (a[i] / radix) % 10;
            cnt[k]++;
        }
        for(int i = 1; i < 10; i++){
            cnt[i] = cnt[i-1] + cnt[i];
        }
        for(int i = n - 1; i >= 0; i--){
            int k = (a[i] / radix) % 10;
            c[--cnt[k]] = a[i];
        }
        for(int i = 0; i < n; i++){
            a[i] = c[i];
        }
        radix *= 10;
    }
    delete[] cnt;
}

template <typename T>
void Sort(T *a, int n, T *c){
    double st, ed;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    insertSort(a, n);
    ed = clock();
    cout<<"插入排序："<<ed-st<<endl;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    bubbleSort(a, n);
    ed = clock();
    cout<<"冒泡排序："<<ed-st<<endl;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    selectSort(a, n);
    ed = clock();
    cout<<"选择排序："<<ed-st<<endl;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    shellSort(a, n);
    ed = clock();
    cout<<"希尔排序："<<ed-st<<endl;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    quickSort(a, 0, n-1, n);
    ed = clock();
    cout<<"快速排序："<<ed-st<<endl;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    mergeSort(a, 0, n, c);
    ed = clock();
    cout<<"归并排序："<<ed-st<<endl;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    heapSort(a, n);
    ed = clock();
    cout<<"堆排序："<<ed-st<<endl;
    //for(int i = 0; i < n; i++){
    //    cin>>a[i];
    //}
    //st = clock();
    //binSort(a, n, c);
    //ed = clock();
    //cout<<"箱排序："<<ed-st<<endl;
    for(int i = 0; i < n; i++){
        a[i] = ary[i];
    }
    st = clock();
    radixSort(a, n, c);
    ed = clock();
    cout<<"基数排序："<<ed-st<<endl;
}
int main(){
    for(int i = 0; i < maxn; i++) ary[i] = rand() % mod;
    while(1){
        cout<<"请输入数据规模：\n";
        int n;
        cin>>n;
        if(n == 0) break;
        Sort(a, n, c);
    }
    return 0;
}
