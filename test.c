#include <stdio.h>
#include <stdlib.h>

typedef struct s_shell
{
	int	exit_status;
}		t_shell;

int	main(void)
{
	t_shell	*shell;
	int		status;

	shell = malloc(sizeof(t_shell));
	shell->exit_status = 127;
	status = shell->exit_status;
	free(shell);
	printf("About to exit with: %d\n", status);
	exit(status);
}
