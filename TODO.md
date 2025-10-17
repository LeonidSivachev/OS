# TODO

## Current tasks

- [ ] **Nasm** - remove all nasm code, we will use only gas.
- [ ] **Exceptions** - implement normal exception handlers to use debuger.
- [ ] **Sanitizers** - integrate sanitizers to detect UB.
- [ ] **Multiboot**  - fix issue with multiboot (believe that it happend because of UB).
- [ ] **Memory** - implement segment memory with protection.
- [ ] **System monitor** - implement normal system monitor, to interact with kernel. Add some commands, like 'backtrace', 'help' end ect...
- [ ] **UEFI data** - start to use data from uefi bios.

## Strategic plans

- [ ] **Paging** - implement transition to paging memory model, implement allocator and ect...
- [ ] **User-space** - implement transition to user space, impelement some syscalls.
- [ ] **Process** - implement processes.
