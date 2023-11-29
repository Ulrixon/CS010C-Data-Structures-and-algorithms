
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

const int NUMBERS_SIZE = 50000;

int partition_midpoint(int numbers[], int i, int k) {
  int pivot = numbers[(i + k) / 2];
  while (i <= k) { // keep swapping if found bigger one on the left and smaller
                   // one on the right
    while (numbers[i] < pivot) {
      i++;
    }
    while (numbers[k] > pivot) {
      k--;
    }
    if (i >= k) {
      break;
    } else { // swap
      int temp = numbers[k];
      numbers[k] = numbers[i];
      numbers[i] = temp;

      // update index
      i++;
      k--;
    }
  }
  return k; // return high index
}

void Quicksort_midpoint(int numbers[], int i, int k) {
  if (i >= k) {
    return;
  }

  int lowEndIndex = partition_midpoint(numbers, i, k);
  Quicksort_midpoint(numbers, i, lowEndIndex);
  Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

int partition_medianOfThree(int numbers[], int i, int k) {
  int array[3] = {numbers[i], numbers[k], numbers[(i + k) / 2]};
  std::sort(std::begin(array), std::end(array));
  int pivot = array[1];
  while (i <= k) { // keep swapping if found bigger one on the left and smaller
                   // one on the right
    while (numbers[i] < pivot) {
      i++;
    }
    while (numbers[k] > pivot) {
      k--;
    }
    if (i >= k) {
      break;
    } else { // swap
      int temp = numbers[k];
      numbers[k] = numbers[i];
      numbers[i] = temp;

      // update index
      i++;
      k--;
    }
  }
  return k; // return high index
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
  if (i >= k) {
    return;
  }

  int lowEndIndex = partition_medianOfThree(numbers, i, k);
  Quicksort_medianOfThree(numbers, i, lowEndIndex);
  Quicksort_medianOfThree(numbers, lowEndIndex + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
  for (int i = 1; i < numbersSize; i++) {
    int insertPosition = i;
    while (insertPosition > 0 &&
           numbers[insertPosition] < numbers[insertPosition - 1]) {
      // swap
      int temp = numbers[insertPosition];
      numbers[insertPosition] = numbers[insertPosition - 1];
      numbers[insertPosition - 1] = temp;
      insertPosition--;
    }
  }
}

int genRandInt(int low, int high) { return low + rand() % (high - low + 1); }

void fillArrays(int arr1[], int arr2[], int arr3[]) {
  for (int i = 0; i < NUMBERS_SIZE; ++i) {
    arr1[i] = genRandInt(0, NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

int testSortingAlgorithm(int numbers[], std::string algorithm) {
  const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // clock per milliseconds
  clock_t Start;
  if (algorithm == "Quicksort_midpoint") {
    Start = clock();
    Quicksort_midpoint(numbers, 0, NUMBERS_SIZE - 1);

  } else if (algorithm == "Quicksort_medianOfThree") {
    Start = clock();
    Quicksort_medianOfThree(numbers, 0, NUMBERS_SIZE - 1);
  } else if (algorithm == "InsertionSort") {
    Start = clock();
    InsertionSort(numbers, NUMBERS_SIZE);
  } else {
    return 0;
  }

  clock_t End = clock();
  int elapsedTime =
      (End - Start) /
      CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
  return elapsedTime;
}

int main() {

  // fill the arrays
  int *arrayForQuickSortMidPoint = new int[NUMBERS_SIZE];
  int *arrayForQuickSortMedian = new int[NUMBERS_SIZE];
  int *arrayForSelectionSort = new int[NUMBERS_SIZE];
  fillArrays(arrayForQuickSortMidPoint, arrayForQuickSortMedian,
             arrayForSelectionSort);
  std::cout << "Quicksort_midpoint:"
            << testSortingAlgorithm(arrayForQuickSortMidPoint,
                                    "Quicksort_midpoint") << endl;
  std::cout << "Quicksort_medianOfThree:"
            << testSortingAlgorithm(arrayForQuickSortMedian,
                                    "Quicksort_medianOfThree") << endl;
  std::cout << "InsertionSort:"
            << testSortingAlgorithm(arrayForSelectionSort, "InsertionSort") << endl;
}