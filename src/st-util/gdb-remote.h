#ifndef GDB_REMOTE_H_
#define GDB_REMOTE_H_

int gdb_send_packet(int fd, char* data);
int gdb_recv_packet(int fd, char** buffer);
int gdb_check_for_interrupt(int fd);

#endif // GDB_REMOTE_H_
