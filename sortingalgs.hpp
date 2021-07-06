#ifndef SORTINGALGS_HPP_INCLUDED
#define SORTINGALGS_HPP_INCLUDED

/*
    Egyik al�bb l�that� rendez�algoritmust se �n tal�ltam ki.
    T�bbs�g�t m�s �ltal kital�lt pszeudo k�d alapj�n implement�ltam a saj�t DrawableList oszt�lyomhoz.
    A pszeudo k�dok forr�sa nagyr�szt az algoritmus nev�vel megegyez� angol nyelv� Wikipedia oldal.
*/

/*
    Selection Sort
*/
template <typename T>
void SelectionSort(DrawableList<T>& ls) {
    int n = ls.size();

    for (int j = 0; j < n-1; ++j) {
        int iMin = j;
        for (int i = j+1; i < n; ++i) {
            if (ls[i] < ls[iMin]) {
                iMin = i;
            }
        }

        if(iMin != j) {
            Drawable<T> tmp = ls[j];
            ls[j] = ls[iMin];
            ls[iMin] = tmp;
        }
    }
}

/*
    Insertion Sort
*/
template <typename T>
void InsertionSort(DrawableList<T>& ls) {
    int n = ls.size();

    for (int i = 1; i < n; ++i) {
        int j = i;
        while ((j > 0) && (ls[j-1] > ls[j])) {
            Drawable<T> tmp = ls[j];
            ls[j] = ls[j-1];
            ls[j-1] = tmp;
            --j;
        }
    }
}

/*
    Seg�df�ggv�ny a Quick Sort-hoz.
    A rekurzi� miatt hoztam l�tre, hogy a QuickSort-ot ugyanazzal a param�terlist�val lehessen haszn�lni,
    mint b�rmelyik m�sik itt l�that� rendez� f�ggv�nyt.
*/
template <typename T>
void QuickSortHelper(DrawableList<T>& arr, int left, int right) {
    int i = left, j = right;
    Drawable<T> pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
                i++;
        while (arr[j] > pivot)
                j--;
        if (i <= j) {
                Drawable<T> tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
        }
    };

    if (left < j)
        QuickSortHelper(arr, left, j);
    if (i < right)
        QuickSortHelper(arr, i, right);
}

/*
    Quick Sort
*/
template <typename T>
void QuickSort(DrawableList<T>& ls) {
    QuickSortHelper(ls, 0, ls.size()-1);
}

/*
    std::sort
*/
template <typename T>
void StdSort(DrawableList<T>& ls) {
    std::sort(ls.begin(), ls.end(), [](Drawable<T> a, Drawable<T> b){return a < b;});
}

/*
    std::stable_sort
*/
template <typename T>
void StdStableSort(DrawableList<T>& ls) {
    std::stable_sort(ls.begin(), ls.end(), [](Drawable<T> a, Drawable<T> b){return a < b;});
}

/*
    Shell sort
*/
template <typename T>
void ShellSort(DrawableList<T>& ls) {
    int j;
    int n = ls.size();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            Drawable<T> temp = ls[i];
            for (j = i; j >= gap && temp < ls[j - gap]; j -= gap)
            {
                ls[j] = ls[j - gap];
            }
            ls[j] = temp;
        }
    }
}
#endif // SORTINGALGS_HPP_INCLUDED
