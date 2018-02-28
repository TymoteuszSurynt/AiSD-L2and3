#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;
long long int questionKey=0;
long long int changeKey =0;
bool showLogs=false;
//--------Utils--------//
void printarray(int* array,int start,int size){
    for(int i=start;i<size;i++){
        printf("%5d|",array[i]);
    }
    cout<<endl;
}
void randomArray(int* array, int size){
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000;
    }
}
//------Insertion------//
void insertionSort(int *array,int size){
    int j;
    for(int i=1;i<size;i++){
        j=i;
        while(j>0){
            questionKey++;
            if(array[j]<array[j-1]) {
                swap(array[j], array[j-1]);
                j--;
                changeKey++;
            }else{
                break;
            }
            if(showLogs) {
                cout << "Log, change:" << endl;
                printarray(array,0, size);
            }
        }
    }
}
void insertionSort1(int *array,int start, int end){
    int j;
    for(int i=start+1;i<=end;i++){
        j=i;
        while(j>start){
            questionKey++;
            if(array[j]<array[j-1]) {
                swap(array[j], array[j-1]);
                j--;
                changeKey++;
            }else{
                break;
            }
            if(showLogs) {
                cout << "Log, change:" << endl;
                printarray(array,0, end+1);
            }
        }
    }
}


void insertionSortNoLogs(int *array,int size){
    int j;
    for(int i=1;i<size;i++){
        j=i;
        while(j>0){
            questionKey++;
            if(array[j]<array[j-1]) {
                swap(array[j], array[j-1]);
                j--;
                changeKey++;
            }else{
                break;
            }
        }
    }
}
//-------Merge-------//
void mergeMS(int *a, int start, int mid, int end){
    int *array2=new int[end+1];
    int istart=start,jstart=mid+1,kstart=start;

    while (istart <= mid && jstart <= end){
        questionKey++;
        changeKey++;
        if (a[istart] < a[jstart]){
            array2[kstart] = a[istart];
            kstart++;
            istart++;
        }else{
            array2[kstart] = a[jstart];
            kstart++;
            jstart++;
        }
    }
    while (istart <= mid){
        changeKey++;
        array2[kstart] = a[istart];
        kstart++;
        istart++;
    }
    while (jstart <= end){
        changeKey++;
        array2[kstart] = a[jstart];
        kstart++;
        jstart++;
    }
    for (int i=start; i< kstart;i++){
        a[i] = array2[i];
    }
    delete [] array2;
}
void mergeSort(int* array, int start, int end){
    if(start<end){
        int mid=(start+end)/2;
        mergeSort(array,start,mid);
        mergeSort(array,mid+1,end);
        if(showLogs) {
            cout << "Log, change:" << endl;
            printarray(array,start, end);
        }
        mergeMS(array,start,mid,end);
    }
}
void mergeSort(int* array,int size){
    mergeSort(array,0,size);
}
void mergeSortInsert(int* array, int start, int end){
    if(end-start<8){
        insertionSort1(array,start,end);
    }else {
        int mid = (start + end) / 2;
        mergeSortInsert(array, start, mid);
        mergeSortInsert(array, mid + 1, end);
        if (showLogs) {
            cout << "Log, change:" << endl;
            printarray(array,start, end);
        }
        mergeMS(array, start, mid, end);
    }
}
void mergeSortInsert(int* array,int size){
    mergeSortInsert(array,0,size-1);
}
//-------Quick---------//
//Lomuto partition scheme

int partition(int * array, int start, int end)
{
    int i=start-1, pivot=array[end];
    for(int j=start;j<=end-1;j++){
        questionKey++;
        if(array[j]<=pivot){
            i++;
            changeKey++;
            swap(array[i],array[j]);
        }
    }
    changeKey++;
    swap(array[i+1],array[end]);
    return i+1;
}
void quickSort(int* array, int start, int end) {
    if (start < end){
        if(showLogs) {
            cout << "Log, change:" << endl;
            printarray(array,start, end);
        }
        int p=partition(array,start,end);
        quickSort(array, start,p-1);
        quickSort(array, p+1, end);
    }
}
void quickSortInsert(int* array, int start, int end) {
    if(end-start<8){
        insertionSort1(array,start,end);
    }else {
        if (start < end) {
            if (showLogs) {
                cout << "Log, change:" << endl;
                printarray(array,start, end);
            }
            int p = partition(array, start, end);
            quickSortInsert(array, start, p - 1);
            quickSortInsert(array, p + 1, end);
        }
    }
}
void dualPivotQuickSort(int *array,int start, int end){

    if(end-start<8 &&end>start){
        insertionSort1(array,start,end);
    }else if(end>start){
        questionKey++;
        if(array[start]>array[end]){
            swap(array[start],array[end]);
            changeKey++;
            if (showLogs) {
                cout << "Log, swap pivots:" << endl;
                printarray(array,start, end+1);
            }
        }
        int pivotL=array[start], pivotR=array[end],i=start+1,j=end-1;
        for(int k=start+1;k<=j;k++){
            questionKey++;
            if(array[k]<pivotL){
                changeKey++;
                swap(array[k],array[i]);
                i++;
                if (showLogs) {
                    printarray(array,start, end+1);
                }
            }else if(array[k]>=pivotR){
                while(k<j){
                    questionKey++;
                    if(array[j]<=pivotR){
                        break;
                    }
                    j--;
                }
                if(k!=j) {
                    changeKey++;
                    swap(array[k], array[j]);
                }
                if (showLogs) {
                    cout << "Log, change:" << endl;
                    printarray(array,start, end+1);
                }
                j--;
                questionKey++;
                if(array[k]<pivotL){
                    swap(array[k],array[i]);
                    if (showLogs) {
                        printarray(array,start, end+1);
                    }
                    i++;
                    changeKey++;
                }
            }

        }
        --i;
        j++;
        if(start!=i) {
            swap(array[start], array[i]);
            changeKey++;
        }
        if(end!=j) {
            swap(array[end], array[j]);
            changeKey++;
        }
        dualPivotQuickSort(array,start,i-1);
        dualPivotQuickSort(array,i+1,j-1);
        dualPivotQuickSort(array,j+1,end);

    }
}
//-----Radix Sort------//
void radixSort(int* array,int size){
    vector<int> vOfNumbers[10];
    int n=1,m=10,maxElement=array[0];
    for(int i=1;i<size;i++){
        questionKey++;
        if(array[i]>maxElement){
            maxElement=array[i];
        }
    }
    while(true){
        if(n>maxElement){
            break;
        }
        for(int i=0;i<size;i++){
            questionKey++;
            vOfNumbers[array[i]%m/n].push_back(array[i]);
        }
        int k=0;
        for(int i=0;i<10;i++){
            while(!vOfNumbers[i].empty()){
                array[k]=vOfNumbers[i].front();
                vOfNumbers[i].erase(vOfNumbers[i].begin());
                k++;
                changeKey++;
            }
        }
        n*=10;
        m*=10;
        if (showLogs) {
            cout << "Log, change:" << endl;
            printarray(array,0, size);
        }
    }
}
int main() {
    int sort1,sort2,size,test,log=0;
    while(true) {
        questionKey=0;
        changeKey=0;
        cout << "Choose: 1-User Input 2-Test All(zad1) 3-Test All (zad2) 4-Dual Pivot Test(zad3) 5-Radix Sort Test(lista3 zad1) 6-Exit" << endl;
        cin >> test;
        if(test==6){
            break;
        }
        if(log!=3 && log!=4) {
            cout << "Choose: 1-Logs 2- No logs 3-Always logs 4-Never logs" << endl;
            cin >> log;
            showLogs = log == 1 || log == 3;
        }

        if (test == 1) {
            changeKey=0;
            questionKey=0;
            cout << "Choose: 1-Insertion Sort 2-Merge Sort 3-Quick Sort 4-Merge + Insert Sort 5-Quick + Insert Sort 6-Dual Pivot Quick Sort 7-Radix Sort"
                 << endl;
            cin >> sort1;
            if (sort1 < 0 || sort1 > 7) {
                cout << "Wrong sort selected"<<endl;
            } else {
                cout << "Choose: 1-Random Array 2-Sorted Descending Array" << endl;
                cin >> sort2;
                if (sort2 < 0 || sort2 > 2) {
                    cout << "Wrong option selected"<<endl;
                } else {
                    cout << "Size:" << endl;
                    cin >> size;
                    if (size < 0 || sort2 > 100000) {
                        cout << "Wrong size";
                    } else {
                        int *array = new int[size];
                        if (sort2 == 1) {
                            randomArray(array, size);
                        } else if (sort2 == 2) {
                            for (int i = 0; i < size; i++) {
                                array[i] = size - i;
                            }
                        }
                        printarray(array,0, size);
                        cout << endl << endl;
                        if (sort1 == 1) {
                            insertionSort(array, size);
                            cout << "Result:" << endl;
                        } else if (sort1 == 2) {
                            mergeSort(array, size - 1);
                            cout << "Result:" << endl;
                        } else if (sort1 == 3) {
                            quickSort(array, 0, size - 1);
                            cout << "Result:" << endl;
                        } else if (sort1 == 4) {
                            mergeSortInsert(array, size);
                            cout << "Result:" << endl;
                        } else if (sort1 == 5) {
                            quickSortInsert(array, 0, size - 1);
                            cout << "Result:" << endl;
                        }else if (sort1 == 6) {
                            dualPivotQuickSort(array, 0, size - 1);
                            cout << "Result:" << endl;
                        }else if (sort1 == 7) {
                            radixSort(array, size);
                            cout << "Result:" << endl;
                        }
                        printarray(array,0, size);
                        cout << "Klucze zapytane: " << questionKey << " Klucze zmienione: " << changeKey << endl;
                        delete[] array;
                    }
                }
            }
        } else if (test == 2) {
            int **arrays = new int *[1000];
            for (int i = 0; i < 1000; i++) {
                arrays[i] = new int[(i + 1) * 100];
            }
            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            ofstream file;
            file.open("results.txt");
            long long int change[3];
            long long int check[3];
            long long int change1[3];
            long long int check1[3];
            long long int change2[2];
            long long int check2[2];
            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            file << endl
                 << "N\tMerge Sort Checked Key\tMerge Sort Changed Key\tQuick Sort Checked Key\tQuick Sort Changed Key\tInsertion Sort Checked Key\tInsertion Sort Changed Key"
                 << endl;
            for (int i = 0; i < 1000; i++) {
                questionKey = 0;
                changeKey = 0;
                mergeSort(arrays[i], 0, (i + 1) * 100 - 1);
                check[0] = questionKey;
                change[0] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                mergeSort(arrays[i], 0, (i + 1) * 100 - 1);
                check[1] = questionKey;
                change[1] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                mergeSort(arrays[i], 0, (i + 1) * 100 - 1);
                check[2] = questionKey;
                change[2] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                quickSort(arrays[i], 0, (i + 1) * 100 - 1);
                check1[0] = questionKey;
                change1[0] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                quickSort(arrays[i], 0, (i + 1) * 100 - 1);
                check1[1] = questionKey;
                change1[1] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                quickSort(arrays[i], 0, (i + 1) * 100 - 1);
                check1[2] = questionKey;
                change1[2] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                insertionSortNoLogs(arrays[i], (i + 1) * 100);
                check2[0] = questionKey;
                change2[0] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                insertionSortNoLogs(arrays[i], (i + 1) * 100);
                check2[1] = questionKey;
                change2[1] = changeKey;


                cout << "- - - - -" << endl << (i + 1) * 100 << endl;
                file << (i + 1) * 100 << "\t" << (check[0] + check[1] + check[2]) / 3 << "\t"
                     << (change[0] + change[1] + change[2]) / 3 << "\t" << (check1[0] + check1[1] + check1[2]) / 3
                     << "\t" << (change1[0] + change1[1] + change1[2]) / 3 << "\t" << (check2[0] + check2[1]) / 2
                     << "\t" << (change2[0] + change2[1]) / 2 << endl;
            }

            file.close();
            for (int i = 0; i < 1000; i++) {
                delete[] arrays[i];
            }
            delete[] arrays;


        } else if (test == 3) {
            int **arrays = new int *[1000];
            for (int i = 0; i < 1000; i++) {
                arrays[i] = new int[(i + 1) * 100];
            }
            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            ofstream file;
            file.open("results2.txt");
            long long int change[3];
            long long int check[3];
            long long int change1[3];
            long long int check1[3];

            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            file << endl
                 << "N\tMerge Sort + Insertion Checked Key\tMerge + Insertion Sort Changed Key\tQuick + Insertion Sort Checked Key\tQuick + Insertion Sort Changed Key"
                 << endl;
            for (int i = 0; i < 1000; i++) {
                questionKey = 0;
                changeKey = 0;
                mergeSortInsert(arrays[i], 0, (i + 1) * 100 - 1);
                check[0] = questionKey;
                change[0] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                mergeSortInsert(arrays[i], 0, (i + 1) * 100 - 1);
                check[1] = questionKey;
                change[1] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                mergeSortInsert(arrays[i], 0, (i + 1) * 100 - 1);
                check[2] = questionKey;
                change[2] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                quickSortInsert(arrays[i], 0, (i + 1) * 100 - 1);
                check1[0] = questionKey;
                change1[0] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                quickSortInsert(arrays[i], 0, (i + 1) * 100 - 1);
                check1[1] = questionKey;
                change1[1] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                quickSortInsert(arrays[i], 0, (i + 1) * 100 - 1);
                check1[2] = questionKey;
                change1[2] = changeKey;
                cout << "- - -" << endl << (i + 1) * 100 << endl;
                file << (i + 1) * 100 << "\t" << (check[0] + check[1] + check[2]) / 3 << "\t"
                     << (change[0] + change[1] + change[2]) / 3 << "\t" << (check1[0] + check1[1] + check1[2]) / 3
                     << "\t" << (change1[0] + change1[1] + change1[2]) / 3 << endl;

            }
            file.close();
            for (int i = 0; i < 1000; i++) {
                delete[] arrays[i];
            }
            delete[] arrays;
        } else if(test==4) {
            int **arrays = new int *[1000];
            for (int i = 0; i < 1000; i++) {
                arrays[i] = new int[(i + 1) * 100];
            }
            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            ofstream file;
            file.open("results3.txt");
            long long int change[3];
            long long int check[3];

            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            file
                    << "N\tDual Pivot Quick Sort Checked Key\tDual Pivot Quick Sort Sort Changed Key"
                    << endl;
            for (int i = 0; i < 1000; i++) {
                questionKey = 0;
                changeKey = 0;
                dualPivotQuickSort(arrays[i], 0, (i + 1) * 100 - 1);
                check[0] = questionKey;
                change[0] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                dualPivotQuickSort(arrays[i], 0, (i + 1) * 100 - 1);
                check[1] = questionKey;
                change[1] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                dualPivotQuickSort(arrays[i], 0, (i + 1) * 100 - 1);
                check[2] = questionKey;
                change[2] = changeKey;

                cout << "* * *" << endl << (i + 1) * 100 << endl;
                file << (i + 1) * 100 << "\t" << (check[0] + check[1] + check[2]) / 3 << "\t"
                     << (change[0] + change[1] + change[2]) / 3 << "\t" << endl;

            }
            file.close();
            for (int i = 0; i < 1000; i++) {
                delete[] arrays[i];
            }
            delete[] arrays;
        } else if(test==5) {
            int **arrays = new int *[1000];
            for (int i = 0; i < 1000; i++) {
                arrays[i] = new int[(i + 1) * 100];
            }
            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            ofstream file;
            file.open("results4.txt");
            long long int change[3];
            long long int check[3];

            for (int i = 0; i < 1000; i++) {
                randomArray(arrays[i], (i + 1) * 100);
            }
            file
                    << "N\tRadix Sort Checked Key\tRadix Sort Changed Key"
                    << endl;
            for (int i = 0; i < 1000; i++) {
                questionKey = 0;
                changeKey = 0;
                radixSort(arrays[i], (i + 1) * 100);
                check[0] = questionKey;
                change[0] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                radixSort(arrays[i], (i + 1) * 100);
                check[1] = questionKey;
                change[1] = changeKey;
                questionKey = 0;
                changeKey = 0;
                randomArray(arrays[i], (i + 1) * 100);
                radixSort(arrays[i], (i + 1) * 100);
                check[2] = questionKey;
                change[2] = changeKey;

                cout << "+ + +" << endl << (i + 1) * 100 << endl;
                file << (i + 1) * 100 << "\t" << (check[0] + check[1] + check[2]) / 3 << "\t"
                     << (change[0] + change[1] + change[2]) / 3 << "\t" << endl;

            }
            file.close();
            for (int i = 0; i < 1000; i++) {
                delete[] arrays[i];
            }
            delete[] arrays;
        }else {
            cout << "Wrong number"<<endl;
        }
    }
    return 0;
}