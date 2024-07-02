#include "scheduler.h"
#include "../../hmem/smem/heap.h"
struct process_node_t {
    process_t* process;
    process_node_t* next;
};

static process_node_t* process_list_head = nullptr;
static process_node_t* current_node = nullptr;

void init_scheduler() {
    init_processes();
    process_list_head = nullptr;
    current_node = nullptr;
}

void add_process_to_schedule(process_t* process) {
    process_node_t* new_node = (process_node_t*)kalloc(sizeof(process_node_t));
    if (!new_node) return;

    new_node->process = process;
    new_node->next = nullptr;

    if (!process_list_head) {
        process_list_head = new_node;
        current_node = new_node;
    } else {
        process_node_t* temp = process_list_head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void remove_process_from_schedule(uint64_t pid) {
    process_node_t* prev = nullptr;
    process_node_t* temp = process_list_head;

    while (temp) {
        if (temp->process->pid == pid) {
            if (prev) {
                prev->next = temp->next;
            } else {
                process_list_head = temp->next;
            }

            if (current_node == temp) {
                current_node = current_node->next ? current_node->next : process_list_head;
            }

            kfree(temp->process);
            kfree(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void schedule(registers_t* regs) {
    if (!process_list_head) return;

    if (current_node && current_node->process) {
        current_node->process->regs = *regs;
    }

    if (!current_node || !current_node->next) {
        current_node = process_list_head;
    } else {
        current_node = current_node->next;
    }

    if (current_node && current_node->process) {
        *regs = current_node->process->regs;
    }
}