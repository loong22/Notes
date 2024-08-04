/*
把每个线程私有的数组（长度不一）放到同一个内存下，确保所有线程都可以访问到
*/
#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 每个进程有一个长度不一样的vector数组
    std::vector<int> local_array;
    // 假设每个进程的数组长度为rank+1
    for (int i = 0; i < rank + 1; ++i) {
        local_array.push_back(rank * 10 + i); // 假设数组内容为rank*10 + i
    }

    // 计算每个进程的数组总长度
    std::vector<int> recv_counts(size);
    MPI_Allgather(&local_array.size(), 1, MPI_INT,
                  recv_counts.data(), 1, MPI_INT, MPI_COMM_WORLD);

    // 计算每个进程的接收偏移量
    std::vector<int> displs(size);
    displs[0] = 0;
    for (int i = 1; i < size; ++i) {
        displs[i] = displs[i - 1] + recv_counts[i - 1];
    }

    // 合并所有进程的数组到一个共享的vector中
    std::vector<int> all_arrays(displs[size - 1] + recv_counts[size - 1]);
    MPI_Allgatherv(local_array.data(), local_array.size(), MPI_INT,
                    all_arrays.data(), recv_counts.data(), displs.data(), MPI_INT, MPI_COMM_WORLD);

    // 每个进程都可以访问合并后的数组
    std::cout << "Rank " << rank << ": ";
    for (const auto& elem : all_arrays) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}
