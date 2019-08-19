#ifndef _OPTION_HANDLE_H_
#define _OPTION_HANDLE_H_

void option_handle(int argc, char *argv[], char *envp[]);


void opt_help_handle(void);
void opt_version_handle(void);
void opt_log_handle(char *logname);
void opt_filename_handle(char *filename);
void opt_processid_handle(char *processid);

#endif
