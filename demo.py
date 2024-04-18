import matplotlib.pyplot as plt
import numpy as np
import os

FIGSIZE = (16, 9)

if __name__ == '__main__':
    abscissa = np.append(np.arange(1, 500), np.arange(500, 10000, 100))
    sorts_all = {"BubbleSort.txt": None, "InsertionSort.txt": None, "SelectionSort.txt": None, 
                  "HeapSort.txt": None, "MergeSort.txt": None, "QuickSort.txt": None, 
                  "RadixSortLSD.txt": None, "RadixSortMSD.txt": None, "ShellSort.txt": None, }

    for sort in sorts_all.keys():
        with open(os.path.join("times", "random_little_data", sort), 'r') as file:
            sorts_all[sort] = np.array(list(map(float, file.read().split(' '))))

    figure, axis = plt.subplots(figsize=FIGSIZE)

    axis.set_title("Sorts", fontsize=17, fontweight="bold", c="dimgray")

    axis.grid(True)

    for sort in sorts_all.keys():
        axis.plot(abscissa, sorts_all[sort], label=sort[:-4])

    axis.legend()
    plt.yscale('log')
    plt.show()

    figure.savefig("graphs/random_all_graphs", bbox_inches="tight")

# abscissa = np.append(np.append(np.arange(1, 500), np.arange(500, 100000, 500)), np.arange(100000, 500000, 2500))
# sorts_nlogn = {"HeapSort.txt": None, "MergeSort.txt": None, "QuickSort.txt": None, 
#              "RadixSortLSD.txt": None, "RadixSortMSD.txt": None, "ShellSort.txt": None, }

# for sort in sorts_nlogn.keys():
#     with open(os.path.join("times", "random", sort), 'r') as file:
#         sorts_nlogn[sort] = np.array(list(map(float, file.read().split(' '))))

# figure, axis = plt.subplots(figsize=FIGSIZE)
# axis.set_title("n*log(n) sorts", fontsize=17, fontweight="bold", c="dimgray")

# axis.grid(True)

# for sort in sorts_nlogn.keys():
#     axis.plot(abscissa, sorts_nlogn[sort], label=sort[:-4])

# axis.legend()

# plt.yscale('log')
# plt.show()

# figure.savefig("graphs/random_nlogn_graphs", bbox_inches="tight")


##############################################################


# abscissa = np.append(np.arange(1, 500), np.arange(500, 10000, 100))
# sorts_slow = {"BubbleSort.txt": None, "InsertionSort.txt": None, "SelectionSort.txt": None, }

# for sort in sorts_slow.keys():
#     with open(os.path.join("times", "random", sort), 'r') as file:
#         sorts_slow[sort] = np.array(list(map(float, file.read().split(' '))))

# figure, axis = plt.subplots(figsize=FIGSIZE)

# axis.set_title("n^2 sorts", fontsize=17, fontweight="bold", c="dimgray")

# axis.grid(True)

# for sort in sorts_slow.keys():
#     axis.plot(abscissa, sorts_slow[sort], label=sort[:-4])

# axis.legend()
# plt.yscale('log')
# plt.show()

# figure.savefig("graphs/random_slow_graphs", bbox_inches="tight")