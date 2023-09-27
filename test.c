#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT	"$>"

int	check_input(char *input)
{
	char *exit = "exit"; 

	for (int i = 0; input[i] != 0; i++)
		if (input[i] != exit[i])
			return (0);
	free(input);
	return (1);
}

int main() {
    char *input;

    // Clear the history
    rl_clear_history();

    while (1) {
        input = readline(PROMPT); // Display a prompt and read input

        if (!input || check_input(input)) {
            // NULL input indicates an EOF (e.g., Ctrl-D), so exit the loop
            printf("Exiting...\n");
			break;
        }

        // Process the input (in this example, we'll just print it)
        // printf("You entered: ");
        for (int i = 0; input[i] != 0; i++)
            write (1, &input[i], 1);
        // printf (" newline\n");

        // Free the dynamically allocated input buffer
        free(input);
    }

    return 0;
}
/*
Certainly! I'll provide more detailed explanations for each of the functions you've listed, excluding those you mentioned:

1. **readline**: The `readline` function is part of the GNU Readline library and is used for reading 
lines of text with advanced line-editing capabilities. 
It displays a user-defined prompt, reads input from the user, and provides features like history 
navigation, command-line editing (e.g., arrow keys for navigation and editing), and tab completion. 
It dynamically allocates memory to store the input line.

2. **rl_clear_history**: This function is part of the GNU Readline library and is used to clear the
 command history managed by Readline. 
It removes all previously entered commands from the history list.

3. **rl_on_new_line**: `rl_on_new_line` is used in conjunction with Readline to inform the library 
that you've moved to a 
new line of input. It's typically used when constructing multiline prompts to manage the line-editing 
and display behavior correctly.

4. **rl_replace_line**: This function is used to replace the current line of input in Readline with a 
specified text.
 It's often used when you want to programmatically modify the content of the input line.

5. **rl_redisplay**: `rl_redisplay` is used to refresh the display to reflect any changes made to
 the current input line. 
For example, after calling `rl_replace_line`, you can use `rl_redisplay` to update the screen.

6. **add_history**: `add_history` is part of the GNU Readline library and is used to manually add a 
line of text to the 
command history. This allows you to add custom commands to the history list for the user to recall 
later.

7. **exit**: The `exit` function is used to terminate a program gracefully. It takes an exit 
status as an argument, which is 
typically 0 for success and a non-zero value for failure. When a program calls `exit`, it cleans 
up resources and returns control to the operating system.

8. **getcwd**: `getcwd` is used to retrieve the current working directory of the calling process.
 It returns the current directory as a string.

9. **chdir**: The `chdir` function is used to change the current working directory of the process 
to the specified directory path.

10. **stat, lstat, fstat**: These functions are used for retrieving file and file system information. 
`stat` retrieves 
information about a file specified by its path. `lstat` is similar but does not follow symbolic links,
 while `fstat` retrieves information about an open file descriptor.

11. **unlink**: The `unlink` function is used to delete (remove) a file from the file system.
 It removes the link to the 
file, and if there are no other links to it, the file is deleted.

12. **execve**: `execve` is used for executing a new program in the current process. It replaces
 the current process with a
 new one specified by the provided program file and arguments.

13. **opendir, readdir, closedir**: These functions are used for directory manipulation. `opendir`
 opens a directory stream, 
`readdir` reads entries from the directory, and `closedir` closes the directory stream.

14. **strerror, perror**: These functions are used for handling and reporting errors. `strerror`
 converts an error code to 
a human-readable string describing the error, while `perror` prints an error message along with 
the error description.

15. **isatty**: The `isatty` function checks whether a given file descriptor refers to a terminal 
(TTY). It returns a 
non-zero value if it's a terminal and zero otherwise.

16. **ttyname**: `ttyname` retrieves the name of the terminal associated with a given file descriptor, 
returning a string with the terminal's name.

17. **ttyslot**: The `ttyslot` function retrieves the slot number of the calling process's terminal in
 the `/etc/ttys` file.

18. **ioctl**: `ioctl` is a system call used for low-level input/output control. It can be used for 
various operations, 
including terminal control and device-specific functionality.

19. **getenv**: `getenv` retrieves the value of an environment variable specified by its name. It 
returns a pointer to the value as a string.

20. **tcsetattr, tcgetattr**: These functions are used to set and retrieve terminal attributes, 
such as input and output modes, baud rates, and more.

21. **tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs**: These functions are part of the Terminfo 
library and are 
used for terminal-related operations in terminal applications. They are used to interact with terminal 
capabilities for 
cursor movement, colors, and other terminal-specific features.

These functions cover a wide range of functionality, from input/output, process control, file
 manipulation, and error handling to terminal interaction in C programming.
*/