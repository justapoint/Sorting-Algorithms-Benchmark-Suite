#include "benchmark_algorithm_runner.hpp"

#include "array_utils.hpp"
#include "sorting/base_sorter.hpp"
#include "sorting/bubble_sort.hpp"
#include "sorting/revised_bubble_sort.hpp"
#include "sorting/selection_sort.hpp"
#include "sorting/insertion_sort.hpp"
#include "sorting/merge_sort.hpp"
#include "sorting/quicksort.hpp"
#include "sort_bench.hpp"
#include "benchmark_progress.hpp"

namespace BenchmarkAlgorithmRunner {
    // Runs all sorting algorithms on random, reversed, and sorted arrays of size N
    void runForSize(int sizeIdx, int N, BenchmarkData::Data& data, int& currentOperation, int totalOperations) {
        // Generate test arrays with different characteristics
        auto rand_arr = ArrayGenerator::getRandomArray(N);
        auto rev_arr = ArrayGenerator::getReversedArray(N);
        auto sorted_arr_src = ArrayGenerator::getSortedArray(N);

        // Create instances of all sorting algorithms
        BubbleSort bubble;
        RevisedBubbleSort revisedBubble;
        SelectionSort selection;
        InsertionSort insertion;
        MergeSort merge;
        QuickSort quick;

        const int numAlgorithms = static_cast<int>(data.algorithmNames.size());

        // Test each algorithm on all three array types
        for (int algoIdx = 0; algoIdx < numAlgorithms; ++algoIdx) {
            BaseSorter* sorter = nullptr;
            std::string algoName = data.algorithmNames[algoIdx];

            // Select the appropriate sorting algorithm
            if (algoName == "Bubble") sorter = &bubble;
            else if (algoName == "Revised bubble") sorter = &revisedBubble;
            else if (algoName == "Selection") sorter = &selection;
            else if (algoName == "Insertion") sorter = &insertion;
            else if (algoName == "Merge") sorter = &merge;
            else if (algoName == "Quick") sorter = &quick;

            if (!sorter) continue;

            // Test on random array
            currentOperation++;
            BenchmarkProgress::showProgress(currentOperation, totalOperations);
            bool okRandom = false;
            double timeRandom = SortBench::runAndTime(sorter, rand_arr, okRandom);
            data.randomTimes[sizeIdx][algoIdx] = timeRandom;
            data.randomOk[sizeIdx][algoIdx] = okRandom;

            // Test on reversed array
            currentOperation++;
            BenchmarkProgress::showProgress(currentOperation, totalOperations);
            bool okReversed = false;
            double timeReversed = SortBench::runAndTime(sorter, rev_arr, okReversed);
            data.reversedTimes[sizeIdx][algoIdx] = timeReversed;
            data.reversedOk[sizeIdx][algoIdx] = okReversed;

            // Test on sorted array
            currentOperation++;
            BenchmarkProgress::showProgress(currentOperation, totalOperations);
            bool okSorted = false;
            double timeSorted = SortBench::runAndTime(sorter, sorted_arr_src, okSorted);
            data.sortedTimes[sizeIdx][algoIdx] = timeSorted;
            data.sortedOk[sizeIdx][algoIdx] = okSorted;
        }
    }
}






