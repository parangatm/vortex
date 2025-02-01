#include <vx_spawn.h>
#include <vx_intrinsics.h>
#include <vx_print.h>
#include <inttypes.h>
#include "common.h"

// Copy all data from source register to destination register
void copy_reg(kernel_arg_t* __UNIFORM__ arg) {
    uint32_t i = blockIdx.x;
    uint32_t n = arg->num_points;
    TYPE* src_ptr = (TYPE*)arg->src_addr;
    TYPE* dst_ptr = (TYPE*)arg->dst_addr;

    if (i < n) {
        dst_ptr[i] = src_ptr[i];
    }

    vx_fence();
    vx_barrier(0, vx_num_warps());           // Synchronize warps within a core
}

// Runs on each individual thread for bitonic sort
void kernel_body(kernel_arg_t* __UNIFORM__ arg) {
    uint32_t i = blockIdx.x;  
    uint32_t n = arg->num_points;  
    uint32_t k = arg->k;  // Pass number
    uint32_t j = arg->j;  // Distance for comparison
    TYPE* data_ptr = (TYPE*)arg->dst_addr;

    if (i < n) {
        uint32_t i_comp = i ^ j;  // Calculate comparison index

        if (i_comp > i && i_comp < n) {
            bool direction;
            if ((i & k) == 0) {
                direction = true;  // Ascending order
            } else {
                direction = false; // Descending order
            }

            // Comparison and swap logic (in-place)
            if (direction) {
                if (data_ptr[i] > data_ptr[i_comp]) {
                    TYPE temp = data_ptr[i];
                    data_ptr[i] = data_ptr[i_comp];
                    data_ptr[i_comp] = temp;
                } // else already ascending
            } else {
                if (data_ptr[i] < data_ptr[i_comp]) {
                    TYPE temp = data_ptr[i];
                    data_ptr[i] = data_ptr[i_comp];
                    data_ptr[i_comp] = temp;
                } // else already descending
            }
        }
    }

    vx_fence();
    vx_barrier(0, vx_num_warps());           // Synchronize warps within a core
}

int main() {
    kernel_arg_t* arg = (kernel_arg_t*)csr_read(VX_CSR_MSCRATCH);
    uint32_t n = arg->num_points;

    // Copy data from src_ptr to dst_ptr
    {
        uint32_t num_blocks = n;
        vx_spawn_threads(1, &num_blocks, nullptr, (vx_kernel_func_cb)copy_reg, arg);
        vx_fence();  // Wait for all threads to complete
    }

    // Bitonic loop with in-place sorting
    for (uint32_t k = 2; k <= n; k *= 2) {
        for (uint32_t j = k / 2; j > 0; j /= 2) {
            arg->k = k;
            arg->j = j;

            uint32_t num_blocks = n;
            vx_spawn_threads(1, &num_blocks, nullptr, (vx_kernel_func_cb)kernel_body, arg);
            vx_fence();  // Ensure all threads complete this pass
            vx_barrier(0x80000000, vx_num_cores());  // Synchronize across all cores   
        }
    }
}
