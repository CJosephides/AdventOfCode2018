#include "double_list.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{

    int num_players = atoi(argv[1]);
    int last_marble = atoi(argv[2]);

    // Initialize the marbles.
    DLIPtr current = malloc(sizeof(DLI));
    current->x = 0;
    current->next = current;
    current->prev = current;
    
    int next_marble, next_player;

    long long scores[num_players];
    for (next_player = 0; next_player < num_players; scores[next_player++] = 0);
    next_marble = 1;
    next_player = 0;

    while (next_marble <= last_marble) {

        if (next_marble % 23 != 0 || next_marble == 0) {
            // Not a multiple of 23.
            disable_current(current);
            current = insert_marble(get_clockwise(current, 2), next_marble);
            enable_current(current);
        } else {
            // A multiple of 23.
            scores[next_player] += next_marble;
            scores[next_player] += get_counterclockwise(current, 7)->x;
            remove_marble(get_counterclockwise(current, 7));
            disable_current(current);
            current = get_counterclockwise(current, 6);
            enable_current(current);
        }

        // Finish.
        next_marble++;
        next_player = (next_player + 1) % num_players;
        //print_marbles(current);
    }

    int i;
    long long max_score = 0;
    for (i = 0; i < num_players; i++) {
        if (scores[i] > max_score)
            max_score = scores[i];
    }
    printf("Highest score = %lld.\n", max_score);

    return 0;
}
