#include "WorldEngine.h"

WorldEngine::WorldEngine() {
    directions = new int[CHARACTERS_AMOUNT];
	character_coordinates = new int*[CHARACTERS_AMOUNT];
	for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
		directions[i] = 0;
		character_coordinates[i] = new int[2];
	}

	char map_template[MAP_HEIGHT][MAP_WIDTH] = {
		"###############################",
		"#      G G G G                #",
		"### ################ ###### ###",
		"#   #      #########      # ###",
		"# # #### # ##        #### # # #",
		"# #      # ## ######    # # # #",
		"# #### ### ## #  P   ## # # # #",
		"# #           ##### ##### ### #",
		"# ###### ####       ##        #",
		"# #  ### ######### ####### ####",
		"# # ##                        #",
		"# # ## ############### ########",
		"#                             #",
		"###############################"
	};
	int current_ghost_index = 1;

	map = new char*[MAP_HEIGHT];
	for (int j = 0; j < MAP_HEIGHT; j++) {
		map[j] = new char[MAP_WIDTH];
		for (int x = 0; x < MAP_WIDTH; x++) {
			map[j][x] = map_template[j][x];

			if (map[j][x] == 'P') {
				character_coordinates[0][0] = x;
				character_coordinates[0][1] = j;
			} else if (map[j][x] == 'G') {
				character_coordinates[current_ghost_index][0] = x;
				character_coordinates[current_ghost_index][1] = j;
				current_ghost_index++;
			}
		}
	}
}


WorldEngine::~WorldEngine() {
}


char** WorldEngine::getMap() {
	return map;
}

int ** WorldEngine::getCharacterCoordinates() {
	return character_coordinates;
}

void WorldEngine::tick() {
	for (int i = 0; i < CHARACTERS_AMOUNT; i++) {
		int character_x = character_coordinates[i][0];
		int character_y = character_coordinates[i][1];
		int character_direction = directions[i];
		char character_symbol = i == 0 ? 'P' : 'G';

		switch (character_direction) {
		case VK_UP:
			if (character_y != 0 && map[character_y - 1][character_x] != '#') {
				character_coordinates[i][1]--;
			}
			break;
		case VK_DOWN:
			if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
				character_coordinates[i][1]++;
			}
			break;
		case VK_LEFT:
			if (character_x != 0 && map[character_y][character_x - 1] != '#') {
				character_coordinates[i][0]--;
			}
			break;
		case VK_RIGHT:			
			if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
				character_coordinates[i][0]++;
			}
			break;
		}
	}

}

void WorldEngine::changeDirection(int character_index, int direction) {
	int character_x = character_coordinates[character_index][0];
	int character_y = character_coordinates[character_index][1];

	switch (direction) {
	case VK_UP:
		if (character_y != 0 && map[character_y - 1][character_x] != '#') {
			directions[PLAYER_DIRECTION_INDEX] = direction;
		}
		break;
	case VK_DOWN:
		if (character_y != MAP_HEIGHT - 1 && map[character_y + 1][character_x] != '#') {
			directions[PLAYER_DIRECTION_INDEX] = direction;
		}
		break;
	case VK_LEFT:
		if (character_x != 0 && map[character_y][character_x - 1] != '#') {
			directions[PLAYER_DIRECTION_INDEX] = direction;
		}
		break;
	case VK_RIGHT:
		if (character_x != MAP_WIDTH - 1 && map[character_y][character_x + 1] != '#') {
			directions[PLAYER_DIRECTION_INDEX] = direction;
		}
		break;
	}
}