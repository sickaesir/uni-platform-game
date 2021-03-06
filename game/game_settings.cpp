#include "game_settings.hpp"
#include "../common.hpp"
#include "../utils/runtime_utils.hpp"

game::game_settings::game_settings(int argc, char** argv)
{
	initialize_settings();
	parse_cmd_settings(argc, argv);
}

void game::game_settings::initialize_settings()
{
	game_height = settings::game_height;
	game_width = settings::game_width;
	map_wall_padding = settings::map_wall_padding;
	console_mode = settings::console_mode;
	console_lines = settings::console_lines;
	io_inactive_ticks = settings::io_inactive_ticks;
	character_jump_velocity = settings::character_jump_velocity;
	gravity_ticks = settings::gravity_ticks;
	map_offsetting_min = settings::map_offsetting_min;
	map_offsetting_max = settings::map_offsetting_max;
	map_offset_threshold = settings::map_offset_threshold;
	rocks_gen_count = settings::rocks_gen_count;
	rock_gen_collision_padding = settings::rock_gen_collision_padding;
	max_character_life = settings::max_character_life;
	character_reattack_ticks = settings::character_reattack_ticks;
	powerup_heal_amount = settings::powerup_heal_amount;
	powerup_max_gen_amount = settings::powerup_max_gen_amount;
	powerup_max_total_jump = settings::powerup_max_total_jump;
	enemy_gen_count = settings::enemy_gen_count;
	enemy_character_distance = settings::enemy_character_distance;
	enemy_movement_tick_interval = settings::enemy_movement_tick_interval;
	enemy_shoot_tick_interval = settings::enemy_shoot_tick_interval;
	enemy_base_life = settings::enemy_base_life;
	enemy_base_laser_damage = settings::enemy_base_laser_damage;
	character_base_laser_damage = settings::character_base_laser_damage;
	powerup_points_increase = settings::powerup_points_increase;
	enemy_kill_points_increase = settings::enemy_kill_points_increase;
	map_exploration_points_increase = settings::map_exploration_points_increase;
	map_extension_points_increase = settings::map_extension_points_increase;
}

void game::game_settings::parse_cmd_settings(int argc, char** argv)
{
	game_path = argv[0];

	for(int i = 1; i < argc; i++)
	{
		char* arg = argv[i];
		int arg_len = utils::runtime_utils::strlen(arg);
		if(arg_len < 3 || arg[0] != '-' || arg[1] != '-')
		{
			// TODO: logging
			continue;
		}
		arg += 2;

		data::data_vector<char*> args_split;
		utils::runtime_utils::str_split(arg, '=', args_split);

		auto args_del = [&args_split]() {
			for(int i = 0; i < args_split.get_size(); i++)
				delete[] args_split[i];
		};

		if(args_split.get_size() != 2)
		{
			args_del();

			// TODO: logging
			continue;
		}

		if(!parse_cmd_arg(args_split[0], args_split[1]))
		{
			args_del();

			// TODO: logging
			continue;
		}

		// TODO: logging

		args_del();
	}

}

bool game::game_settings::parse_cmd_arg(char* arg, char* arg_value)
{
#define CMP_ARG(x) (utils::runtime_utils::strcmp(arg, (char* const)(x)))

	if(CMP_ARG("game-height"))
	{
		game_height = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("game-width"))
	{
		game_width = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("map-wall-padding"))
	{
		map_wall_padding = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("console-mode"))
	{
		console_mode = !!utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("console-lines"))
	{
		console_lines = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("io-inactive-ticks"))
	{
		io_inactive_ticks = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("character-jump-velocity"))
	{
		character_jump_velocity = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("gravity-ticks"))
	{
		gravity_ticks = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("map-offsetting-min"))
	{
		map_offsetting_min = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("map-offsetting-max"))
	{
		map_offsetting_max = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("map-offset-threshold"))
	{
		map_offset_threshold = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("rocks-gen-count"))
	{
		rocks_gen_count = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("rock-gen-collision-padding"))
	{
		rock_gen_collision_padding = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("max-character-life"))
	{
		max_character_life = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("character-reattack-ticks"))
	{
		character_reattack_ticks = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("powerup-heal-amount"))
	{
		powerup_heal_amount = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("powerup-max-gen-amount"))
	{
		powerup_max_gen_amount = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("powerup-max-total-jump"))
	{
		powerup_max_total_jump = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("enemy-gen-count"))
	{
		enemy_gen_count = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("enemy-character-distance"))
	{
		enemy_character_distance = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("enemy-movement-tick-interval"))
	{
		enemy_movement_tick_interval = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("enemy-shoot-tick-interval"))
	{
		enemy_shoot_tick_interval = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("enemy-base-life"))
	{
		enemy_base_life = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("enemy-base-laser-damage"))
	{
		enemy_base_laser_damage = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("character-base-laser-damage"))
	{
		character_base_laser_damage = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("powerup-points-increase"))
	{
		powerup_points_increase = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("enemy-kill-points-increase"))
	{
		powerup_points_increase = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("map-exploration-points-increase"))
	{
		map_exploration_points_increase = utils::runtime_utils::atoi(arg_value);
	}
	else if(CMP_ARG("map-extension-points-increase"))
	{
		map_extension_points_increase = utils::runtime_utils::atoi(arg_value);
	}

#undef CMP_ARG

	return true;
}

int game::game_settings::get_gravity_ticks()
{
	return gravity_ticks;
}

int game::game_settings::get_character_jump_velocity()
{
	return character_jump_velocity;
}

bool game::game_settings::get_console_mode()
{
	return console_mode;
}

int game::game_settings::get_game_height()
{
	return game_height;
}

int game::game_settings::get_game_width()
{
	return game_width;
}

int game::game_settings::get_map_wall_padding()
{
	return map_wall_padding;
}

int game::game_settings::get_console_lines()
{
	return console_lines;
}

int game::game_settings::get_io_inactive_ticks()
{
	return io_inactive_ticks;
}

int game::game_settings::get_map_offsetting_min()
{
	return map_offsetting_min;
}

int game::game_settings::get_map_offsetting_max()
{
	return map_offsetting_max;
}

int game::game_settings::get_map_offset_threshold()
{
	return map_offset_threshold;
}

int game::game_settings::get_rocks_gen_count()
{
	return rocks_gen_count;
}

int game::game_settings::get_rock_gen_collision_padding()
{
	return rock_gen_collision_padding;
}

int game::game_settings::get_max_character_life()
{
	return max_character_life;
}

int game::game_settings::get_character_reattack_ticks()
{
	return character_reattack_ticks;
}

int game::game_settings::get_powerup_heal_amount()
{
	return powerup_heal_amount;
}

int game::game_settings::get_powerup_max_gen_amount()
{
	return powerup_max_gen_amount;
}

int game::game_settings::get_powerup_max_total_jump()
{
	return powerup_max_total_jump;
}

int game::game_settings::get_enemy_gen_count()
{
	return enemy_gen_count;
}

int game::game_settings::get_enemy_character_distance()
{
	return enemy_character_distance;
}

int game::game_settings::get_enemy_movement_tick_interval()
{
	return enemy_movement_tick_interval;
}

int game::game_settings::get_enemy_shoot_tick_interval()
{
	return enemy_shoot_tick_interval;
}

int game::game_settings::get_enemy_base_life()
{
	return enemy_base_life;
}

int game::game_settings::get_enemy_base_laser_damage()
{
	return enemy_base_laser_damage;
}

int game::game_settings::get_character_base_laser_damage()
{
	return character_base_laser_damage;
}

int game::game_settings::get_powerup_points_increase()
{
	return powerup_points_increase;
}

int game::game_settings::get_enemy_kill_points_increase()
{
	return enemy_kill_points_increase;
}

int game::game_settings::get_map_exploration_points_increase()
{
	return map_exploration_points_increase;
}

int game::game_settings::get_map_extension_points_increase()
{
	return map_extension_points_increase;
}
