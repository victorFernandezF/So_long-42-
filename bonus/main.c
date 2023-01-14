/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victofer <victofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:16:51 by victofer          #+#    #+#             */
/*   Updated: 2023/01/14 13:46:23 by victofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/so_long.h"

t_game	game_start_bonus(t_game game)
{
	game.map = map_list_init();
	game.mlx = mlx_init();
	game.collect = 0;
	game.is_finish = 0;
	game.moves = 0;
	game.map.height = count_map_lines(game.map_file);
	if (game.map.height == 1)
		ft_error("There are errors on the map file.");
	game.map.map = map_reader(game.map_file, game.map);
	game.og_map = map_reader(game.map_file, game.map);
	game.map.width = (ft_strlen(game.map.map[0]) - 1);
	check_map_not_sqare(game.map);
	game.map = check_map_bonus(game.map);
	check_map_number_items(game.map);
	game.win.size.x = game.map.width * 64;
	game.win.size.y = (game.map.height * 64) + 42;
	game = open_window_bonus(game);
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_args(argc, argv[1]))
		return (0);
	game.map_file = argv[1];
	game = game_start_bonus(game);
	mlx_key_hook(game.win.reference, key_management_bonus, &game);
	mlx_hook(game.win.reference, 17, 1L << 2, end_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
