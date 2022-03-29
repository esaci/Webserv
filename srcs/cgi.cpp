#include "../include/w_library.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    php-cgi testcgi1.php //working test
    php-cgi lol.php //404 test 
*/
int basic_cgi(void){
    std::cout << "\nTEST CGI\n\n";


    std::string cmd = "php-cgi";
    std::string arg1 = "files_test/testcgi1.php";
    std::string arg2 = NULL;
    // char *args[3] = {"php-cgi", "'echo \"Hello World\n\";'\";", NULL};
    // execve(cmd, args, NULL);


    int		err;
	int		ret;
	pid_t	*pid;
    int     status;

	err = 0;
	ret = 1;
	*pid = fork();
    // char *cmd = "php-cgi";
    // char *args[3] = {"php-cgi", "testcgi1.php", NULL};
	if (*pid < 0)
		std::cout << "error: fork\n";
	if (*pid == 0){
        waitpid(*pid, &status, 0);
    }
	// 	// ret = ft_child(c, s);
	// else{

    //     ret = execve(args[0], args, NULL);
    //     exit(ret);
    // }
	// 	// ret = ft_parent(c, s);
    
	return (ret);
    return 0;
}

// int	ft_parent(t_command *c, t_mother *s)
// {
// 	int	ret;
// 	int	fd;

// 	ret = 0;
// 	// if (c->isprecededbypipe == 1)
// 	// 	close(c->previouspipe->pipes[0]);
// 	if (c->isfollowedbypipe == 1 || c->isprecededbypipe == 1)
// 	{
// 		close(c->pipes[1]);
// 		if (c->isfollowedbyche == 1)
// 			fd = open(c->outfile, O_RDWR | O_CREAT, 0666);
// 		if (c->nextpipe == NULL)
// 		{
// 			dup2(c->pipes[1], 0);
// 			close(c->pipes[0]);
// 		}
// 	}
// 	return (ret);
// }

// int	ft_child(t_command *c, t_mother *s)
// {
// 	int	err;
// 	int	ret;

// 	err = 0;
// 	ret = 1;
// 	if (c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1
// 		|| c->isprecededbyche == 1)
// 		err = ft_redirect(c, s);
// 	if (c->isprecededbypipe == 1 && !(c->isprecededbyche == 1
// 			|| c->isprecededbydoubleche == 1))
// 	{
// 		err = dup2(c->previouspipe->pipes[0], 0);
// 		if (err < 0)
// 			ft_error(s, "pipe iii dup2", -1);
// 	}
// 	if ((c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1))
// 		ret = ft_execfind(s, c);
// 	if ((c->isfollowedbyche == 1
// 			|| c->isfollowedbydoubleche == 1) && !(c->isfollowedbypipe == 1))
// 		exit(ret);
// 	ft_childnorm(c, s);
// 	if (!(c->isfollowedbyche == 1 || c->isfollowedbydoubleche == 1))
// 		ret = ft_execfind(s, c);
// 	exit(ret);
// }