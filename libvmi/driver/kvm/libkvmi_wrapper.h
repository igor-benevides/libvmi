#ifndef LIBKVMI_WRAPPER_H
#define LIBKVMI_WRAPPER_H

#include <stdint.h>
#include <kvmi/libkvmi.h>

#include "private.h"

// wrapper struct
typedef struct {

    void *handle;

    void* (*kvmi_init_unix_socket)
    (const char *socket, kvmi_new_guest_cb accept_cb, kvmi_handshake_cb hsk_cb, void *cb_ctx);

    void (*kvmi_uninit)
    (void* ctx);

    void (*kvmi_close)
    (void* ctx);

    void (*kvmi_domain_close)
    (void *dom, bool do_shutdown);

    int (*kvmi_control_events)
    (void *dom, unsigned short vcpu, int id, bool enable);

    int (*kvmi_control_vm_events)
    (void *dom, int id, bool enable);

    int (*kvmi_control_cr)
    (void *dom, unsigned short vcpu, unsigned int cr, bool enable);

    int (*kvmi_control_msr)
    (void *dom, unsigned short vcpu, unsigned int msr, bool enable);

    int (*kvmi_pause_all_vcpus)
    (void *dom, unsigned int count);

    int (*kvmi_get_page_access)
    (void *dom, unsigned long long int gpa, unsigned char *access);

    int (*kvmi_set_page_access)
    (void *dom, unsigned long long int *gpa, unsigned char *access, unsigned short count);

    int (*kvmi_get_vcpu_count)
    (void *dom, unsigned int *count);

    int (*kvmi_inject_exception)
    (void *dom, unsigned short vcpu, unsigned long long int gva, unsigned int error, unsigned char vector);

    int (*kvmi_read_physical)
    (void *dom, unsigned long long int gpa, void *buffer, size_t size);

    int (*kvmi_write_physical)
    (void *dom, unsigned long long int gpa, const void *buffer, size_t size);

    int (*kvmi_get_registers)
    (void *dom, unsigned short vcpu, struct kvm_regs *regs, struct kvm_sregs *sregs,
     struct kvm_msrs *msrs, unsigned int *mode);

    int (*kvmi_set_registers)
    (void *dom, unsigned short vcpu, const struct kvm_regs *regs);

    int (*kvmi_reply_event)
    (void *dom, unsigned int msg_seq, const void *data, size_t data_size);

    int (*kvmi_pop_event)
    (void *dom, struct kvmi_dom_event **event);

    int (*kvmi_wait_event)
    (void *dom, kvmi_timeout_t ms);

    int (*kvmi_get_maximum_gfn)
    (void *dom, unsigned long long *gfn);

} libkvmi_wrapper_t;

status_t create_libkvmi_wrapper(struct kvm_instance *kvm);

#endif // !LIBKVMI_WRAPPER_H