#include <iostream>
using namespace std;

class Array
{
private:
    int *A;
    int size;
    int length;
    void resize(int newSize)
    {
        int *newA = new int[newSize];
        for (int i = 0; i < length; i++)
        {
            newA[i] = A[i];
        }
        delete[] A;
        A = newA;
        size = newSize;
        cout << "Your array has been resized to " << size << "." << endl;
    }

public:
    Array(int size)
    {
        this->size = size;
        A = new int[size];
        length = 0;
    }
    void display();
    void insert(int index, int x);
    void append(int x);
    void remove(int index);
    int searchKey(int key);
    int get(int index);
    void set(int index, int x);
    int binarySearch(int key);
    bool isSorted() const;
    double avg();
    int max();
    int min();
    int sum();
    void reverse();
    void leftShift();
    void rightShift();
    void leftRotate();
    void rightRotate();
    void sortedInsert(int x);
    void sortArray();
    Array *merge(const Array &arr2);
    Array *Union(const Array &arr2);
    Array *Intersection(const Array &arr2);
    Array *Difference(const Array &arr2);
    friend ostream &operator<<(ostream &out, const Array &arr);
    int &operator[](int index)
    {
        if (index >= 0 && index < length)
            return A[index];

        throw out_of_range("Index out of range");
    }

    const int &operator[](int index) const
    {
        if (index >= 0 && index < length)
            return A[index];

        throw out_of_range("Index out of range");
    }
    int getLength() { return length; }
    int getSize() { return size; }
    ~Array() { delete[] A; }
};

ostream &operator<<(ostream &out, const Array &arr)
{
    for (int i = 0; i < arr.length; i++)
    {
        out << arr[i] << " ";
    }
    return out;
}

Array *Array::Difference(const Array &arr2)
{
    // Step 0: Check for empty array!

    if (length == 0 || arr2.length == 0)
    {
        cout << "Empty array";
        return nullptr;
    }

    // Step 1: If not sorted, sort them!
    if (!this->isSorted())
        sortArray();
    if (!arr2.isSorted())
        const_cast<Array &>(arr2).sortArray();

    // Step 2: Create result array of maximum size.
    Array *result = new Array(this->length);
    int i = 0, j = 0, k = 0;

    // Step 3: Store only the A's most unique elements not in B

    while (i < this->length && j < arr2.length)
    {
        if (A[i] == arr2.A[j])
        {
            i++;
            j++;
        }
        else if (A[i] < arr2.A[j])
        {
            result->A[k++] = A[i++];
        }
        else
        {
            j++;
        }
    }

    // Step 4: Copy remaining from A
    while (i < this->length)
    {
        result->A[k++] = A[i++];
    }

    result->length = k;
    return result;
}

Array *Array::Intersection(const Array &arr2)
{
    // Step 0: Check for empty array!

    if (length == 0 || arr2.length == 0)
    {
        cout << "Empty array.";
        return nullptr;
    }

    // Step 1: If not sorted, sort them!

    if (!this->isSorted())
        sortArray();
    if (!arr2.isSorted())
        const_cast<Array &>(arr2).sortArray();

    // Step 2: Create result array of maximum size.

    int maxLength = (this->length < arr2.length) ? this->length : arr2.length;
    Array *result = new Array(maxLength);

    int i = 0, j = 0, k = 0;

    // Step 3: Merge only the duplicates!
    while (i < this->length && j < arr2.length)
    {
        if (A[i] == arr2.A[j])
        {
            result->A[k++] = A[i];
            i++;
            j++;
        }
        else if (A[i] < arr2.A[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }

    result->length = k;

    return result;
}

Array *Array::Union(const Array &arr2)
{
    // Step 0: Check for empty array!

    if (length == 0)
    {
        cout << "Empty array.";
        return nullptr;
    }
    // Step 1: If not sorted, sort them!
    if (!this->isSorted())
        sortArray();
    if (!arr2.isSorted())
        const_cast<Array &>(arr2).sortArray();

    // Step 2: Create result array of maximum size.
    Array *result = new Array(this->length + arr2.length);
    int i = 0, j = 0, k = 0;

    // Step 3: Merge without duplicates!
    while (i < this->length && j < arr2.length)
    {
        if (A[i] == arr2.A[j])
        {
            result->A[k++] = A[i];
            i++;
            j++;
        }
        else if (A[i] < arr2.A[j])
        {
            result->A[k++] = A[i++];
        }
        else
        {
            result->A[k++] = arr2.A[j++];
        }
    }

    // Step 4: Copy the leftovers.
    while (i < this->length)
    {
        result->A[k++] = A[i++];
    }
    while (j < arr2.length)
    {
        result->A[k++] = arr2.A[j++];
    }

    // Step 5: Update the result length.
    result->length = k;

    return result;
}

Array *Array::merge(const Array &arr2)
{
    // Step 1: If not sorted, sort them!
    if (!this->isSorted())
        sortArray();
    if (!arr2.isSorted())
        const_cast<Array &>(arr2).sortArray();

    Array *result = new Array(length + arr2.length);
    int i = 0, j = 0, k = 0;

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
        {
            result->A[k++] = A[i++];
        }
        else
        {
            result->A[k++] = arr2.A[j++];
        }
    }

    while (i < length)
    {
        result->A[k++] = A[i++];
    }
    while (j < arr2.length)
    {
        result->A[k++] = arr2.A[j++];
    }
    result->length = k;

    return result;
}

void Array::sortArray()
{
    if (!isSorted())
    {
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = 0; j < length - 1 - i; j++)
            {
                if (A[j] > A[j + 1])
                {
                    swap(A[j], A[j + 1]);
                }
            }
        }
    }
}

void Array::sortedInsert(int x)
{
    if (length == 0)

    {
        A[length++] = x;
        return;
    }

    if (!isSorted())
        sortArray();

    if (length == size)

    {
        resize(size * 2);
    }

    if (A[length - 1] <= x)

    {
        if (length == size)
        {
            resize(size * 2);
        }
        else
        {
            A[length++] = x;
        }
    }
    else
    {
        int i = length - 1;

        while (i >= 0 && A[i] > x)

        {
            A[i + 1] = A[i];
            i--;
        }

        A[i + 1] = x;
        length++;
    }
}

void Array::leftRotate()
{
    if (length == 0)
    {
        cout << "Empty array" << endl;
        return;
    }
    int temp = A[0];
    leftShift();
    A[length - 1] = temp;
}

void Array::rightRotate()
{
    if (length == 0)
    {
        cout << "Empty array" << endl;
        return;
    }
    int temp = A[length - 1];
    rightShift();
    A[0] = temp;
}

void Array::leftShift()
{
    if (length == 0)
    {
        cout << "Empty array." << endl;
        return;
    }
    for (int i = 0; i < length - 1; i++)
    {
        A[i] = A[i + 1];
    }
    A[length - 1] = 0;
}

void Array::rightShift()
{
    if (length == 0)
    {
        cout << "Empty array." << endl;
        return;
    }
    for (int i = length - 1; i > 0; i--)
    {
        A[i] = A[i - 1];
    }
    A[0] = 0;
}

void Array::display()
{
    for (int i = 0; i < length; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

void Array::append(int x)
{
    if (length == size)
        resize(size * 2);
    A[length++] = x;
}

void Array::insert(int index, int x)
{
    if (index < 0 || index > length)
        return;
    if (length == size)
        resize(size * 2);
    for (int i = length; i > index; i--)
    {
        A[i] = A[i - 1];
    }
    A[index] = x;
    length++;
}

void Array::remove(int index)
{
    if (index < 0 || index >= length)
        return;
    for (int i = index; i < length - 1; i++)
    {
        A[i] = A[i + 1];
    }
    length--;

    if (length < size / 4 && size > 2)
    {
        resize(size / 2);
    }
}

int Array::searchKey(int key)
{
    for (int i = 0; i < length; i++)
    {
        if (A[i] == key)
        {
            cout << "Key " << key << " was found at index: " << i << "." << endl;
            if (i != 0)
            {
                swap(A[i], A[0]);
            }
            return i;
        }
    }
    return -1;
}

void Array::set(int index, int x)
{
    if (index >= 0 && index < length)
    {
        A[index] = x;
    }
}

int Array::get(int index)
{
    if (index >= 0 && index < length)
    {
        return A[index];
    }
    else
    {
        return -1;
    }
}

bool Array::isSorted() const
{
    for (int i = 1; i < length; i++)
    {
        if (A[i] < A[i - 1])
            return false;
    }
    return true;
}

int Array::binarySearch(int key)
{
    if (!isSorted())
    {
        return searchKey(key);
    }
    int l = 0, h = length - 1;
    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (key == A[mid])
            return mid;
        else if (key < A[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

double Array::avg()
{
    if (length == 0)
        return 0.0;
    return static_cast<double>(sum()) / length;
}

int Array::max()
{
    if (length == 0)
    {
        cout << "Array is empty." << endl;
        return INT_MIN;
    }
    int max = A[0];
    for (int i = 1; i < length; i++)
    {
        if (A[i] > max)
        {
            max = A[i];
        }
    }
    return max;
}

int Array::min()
{
    if (length == 0)
    {
        cout << "Array is empty." << endl;
        return INT_MAX;
    }
    int min = A[0];
    for (int i = 1; i < length; i++)
    {
        if (A[i] < min)
        {
            min = A[i];
        }
    }
    return min;
}

int Array::sum()
{
    if (length == 0)
    {
        cout << "Array is empty." << endl;
        return -1;
    }
    int s = 0;
    for (int i = 0; i < length; i++)
    {
        s += A[i];
    }
    return s;
}

void Array::reverse()
{
    if (length == 0)
    {
        cout << "Empty array" << endl;
        return;
    }
    int i = 0, j = length - 1;
    while (i < j)
    {
        swap(A[i], A[j]);
        i++;
        j--;
    }
}

int main()
{
    return 0;
}