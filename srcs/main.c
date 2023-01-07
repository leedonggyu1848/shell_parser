/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 10:24:53 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipe list -> token list -> token

void	print_token(void *content)
{
	t_token *token;

	token = (t_token *)content;
	printf("%d ", token->type);
	printf("%s@\n", token->str);
}

void	print_file_info(void *context)
{
	t_file_info	*info;

	info = (t_file_info *)context;
	printf(" [%d %s] ", info->type, info->filename);
}

void	print_cmd_info(void *context)
{
	char	*str;

	str = (char *)context;
	printf("[%s] ", str);
}

void	print_process(void *context)
{
	t_process	*process;

	process = (t_process*) context;
	printf("----- pipe start -----\n");
	printf("redirect_in: ");
	ft_lstiter(process->redirect_in, print_file_info);
	printf("\n");
	printf("redirect_out: ");
	ft_lstiter(process->redirect_out, print_file_info);
	printf("\n");
	printf("cmd: ");
	ft_lstiter(process->cmd_info, print_cmd_info);
	printf("\n----- pipe end -----\n");
}

int	main(int argc, __attribute__((unused))char **argv, __attribute__((unused))char *envp[])
{
	char	*input;
	t_list	*processes;

	if (argc != 1)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
			return (1);
		if (ft_strlen(input) == 0)
		{
			printf("path\n");
			free(input);
			continue ;
		}
		add_history(input);
		processes = parse(input);
		ft_lstiter(processes, print_process);
		ft_lstclear(&processes, process_destory);
		free(input);
	}
	return (0);
}
