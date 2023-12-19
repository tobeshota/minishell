/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 00:20:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/19 00:24:47 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	get_wild(t_env **expanded)
{
	char			cwd[PATH_MAX];
	DIR				*dir;
	struct dirent	*entry;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	dir = opendir(cwd);
	if (check_opendir(dir, cwd) == false)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (*expanded == NULL)
			*expanded = ft_nodenew(entry->d_name);
		else
			ft_nodeadd_back(expanded, ft_nodenew(entry->d_name));
		entry = readdir(dir);
	}
	check_closedir(closedir(dir));
	get_order(*expanded);
}

static bool	is_pattern_match(char *content, char *prefix, char *backward)
{
	int	ret;

	if (is_match(prefix, ".") == true)
		ret = !ft_strncmp(content, ".", 1);
	else
		ret = ft_strncmp(content, ".", 1);
	if (prefix[0] == '\0' && backward[0] == '\0')
		return (ret);
	if (prefix[0] == '\0')
		return (ret && !ft_strrncmp(content, backward, ft_strlen(backward)));
	if (backward[0] == '\0')
		return (ret && !ft_strncmp(content, prefix, ft_strlen(prefix)));
	else
		return (ret && !ft_strncmp(content, prefix, ft_strlen(prefix)) && \
		!ft_strrncmp(content, backward, ft_strlen(backward)));
}

static t_env	*del_unmatched_node(t_env *expanded, char *prefix,
		char *backward)
{
	while (true)
	{
		if (is_pattern_match(expanded->content, prefix, backward) == false)
		{
			if (is_node_only_one(expanded) == true)
				return (ft_nodedelone(&expanded), NULL);
			else if (is_node_last(expanded) == true)
				unset_last_node(&expanded);
			else if (is_node_first(expanded) == true)
			{
				unset_first_node(&expanded, NULL);
				continue ;
			}
			else
				unset_middle_node(expanded);
		}
		if (expanded->next == NULL)
			break ;
		expanded = expanded->next;
	}
	ft_nodefirst(&expanded);
	return (expanded);
}

static void	expand_argv_param_w_wildcard(t_env *node)
{
	char	*prefix;
	char	*backward;
	t_env	*expanded;
	char	**array;

	prefix = check_malloc(ft_substr(node->content, 0,
				strlen_until_c(node->content, '*')));
	backward = check_malloc(ft_strdup(ft_strrchr(node->content, '*') + 1));
	expanded = NULL;
	get_wild(&expanded);
	ft_nodesort(&expanded);
	expanded = del_unmatched_node(expanded, prefix, backward);
	if (expanded == NULL)
		return (free(prefix), free(backward));
	array = node_to_array(expanded);
	free(node->content);
	node->content = double_to_sigle(array, ' ');
	return (free(prefix), free(backward), ft_nodeclear(&expanded),
		all_free_tab(array));
}

void	expand_argv_w_wildcard(char **argv_to_be_updated)
{
	char	**array;
	t_env	*node;
	char	*tmp;

	array = split_wo_enclosed_str(*argv_to_be_updated, ' ');
	node = array_to_node(array);
	all_free_tab(array);
	while (true)
	{
		if (is_specified_wildcard(node->content))
			expand_argv_param_w_wildcard(node);
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	ft_nodefirst(&node);
	tmp = *argv_to_be_updated;
	array = node_to_array(node);
	*argv_to_be_updated = double_to_sigle(array, ' ');
	return (all_free_tab(array), free(tmp), ft_nodeclear(&node));
}
