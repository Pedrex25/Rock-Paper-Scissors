#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "labels.c"

enum hands
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

enum rounds
{
    THREE_ROUNDS = 1,
    SIX_ROUNDS = 2,
    NINE_ROUNDS = 3
};

int main()
{

    unsigned short flag = 1;

    unsigned short total_rounds = 3;
    unsigned short choosen_rounds = 1;

    unsigned short min_rand_value = 1;
    unsigned short max_rand_value = 3;

    unsigned short player_hand;
    unsigned short player_score = 0;
    unsigned short cpu_score = 0;
    // short dificulty = 1;

    srand(time(NULL));

    logo();
    printf(WELCOME_MSG);
    printf(GAME_DURATION_OPTIONS_MSG);

    // printf("Game difficulties:\n\t[1]-Easy\n\t[2]-Medium\n\t[3]-Hard");

    while (flag == 1)
    {
        short inner_flag = 1;

        printf(GAME_DURATION_SELECTION_MSG);
        scanf("%hd", &choosen_rounds);

        if (choosen_rounds == THREE_ROUNDS)
        {
            total_rounds = 3;
        }
        else if (choosen_rounds == SIX_ROUNDS)
        {
            total_rounds = 6;
        }

        else if (choosen_rounds == NINE_ROUNDS)
        {
            total_rounds = 9;
        }
        else
        {
            printf(OPTION_NOT_AVAILABLE_MSG);
            continue;
        }

        short remaining_rounds = total_rounds;

        while (inner_flag == 1)
        {
            track_rounds(&remaining_rounds, &total_rounds);

            short name_not_valid = 1;

            int cpu_hand = min_rand_value + rand() % (max_rand_value - min_rand_value + 1); // Get a random value between 1-3

            show_all_hands();

            printf(PLAYER_TURN_MSG);

            // Restrict input to numbers only
            if (scanf("%hd", &player_hand) != 1)
            {
                printf(ONLY_NUMBERS_ALLOWED_MSG);
                continue;
            }

            // No winner cases
            if (player_hand == ROCK && cpu_hand == ROCK)
            {
                printf(LINE_SEPARATOR);
                printf(PLAYER_PLAY);

                show_rock();
                show_rock();

                printf(NO_WINNER_ROUND_MSG);
                printf(CPU_PLAY);
                printf(LINE_SEPARATOR);
            }
            else if (player_hand == PAPER && cpu_hand == PAPER)
            {
                printf(LINE_SEPARATOR);
                printf(PLAYER_PLAY);

                show_paper();
                show_paper();

                printf(CPU_PLAY);
                printf(NO_WINNER_ROUND_MSG);
                printf(LINE_SEPARATOR);
            }
            else if (player_hand == SCISSORS && cpu_hand == SCISSORS)
            {
                printf(LINE_SEPARATOR);
                printf(PLAYER_PLAY);

                show_scissors();
                show_scissors();

                printf(CPU_PLAY);
                printf(NO_WINNER_ROUND_MSG);
                printf(LINE_SEPARATOR);
            }

            // Player winning cases
            else if (player_hand == ROCK && cpu_hand == SCISSORS)
            {

                printf(LINE_SEPARATOR);
                printf(PLAYER_PLAY);

                show_rock_winner(PLAYER);
                show_scissors();

                printf(CPU_PLAY);
                printf(PLAYER_WINS_ROUND);
                printf(LINE_SEPARATOR);
                player_score++;
            }
            else if (player_hand == PAPER && cpu_hand == ROCK)
            {
                printf(LINE_SEPARATOR);
                printf(PLAYER_PLAY);

                show_paper_winner(PLAYER);
                show_rock();

                printf(CPU_PLAY);
                printf(PLAYER_WINS_ROUND);
                printf(LINE_SEPARATOR);
                player_score++;
            }
            else if (player_hand == SCISSORS && cpu_hand == PAPER)
            {

                printf(LINE_SEPARATOR);
                printf(PLAYER_PLAY);

                show_scissors_winner(PLAYER);
                show_paper();

                printf(CPU_PLAY);
                printf(PLAYER_WINS_ROUND);
                printf(LINE_SEPARATOR);
                player_score++;
            }

            // Cpu winning cases
            else if (cpu_hand == ROCK && player_hand == SCISSORS)
            {
                printf(LINE_SEPARATOR);
                printf(CPU_PLAY);

                show_rock_winner(CPU);
                show_scissors();

                printf(PLAYER_PLAY);
                printf(CPU_WINS_ROUND);
                printf(LINE_SEPARATOR);
                cpu_score++;
            }
            else if (cpu_hand == PAPER && player_hand == ROCK)
            {
                printf(LINE_SEPARATOR);
                printf(CPU_PLAY);

                show_paper_winner(CPU);
                show_rock();

                printf(PLAYER_PLAY);
                printf(CPU_WINS_ROUND);
                printf(LINE_SEPARATOR);
                cpu_score++;
            }
            else if (cpu_hand == SCISSORS && player_hand == PAPER)
            {
                printf(LINE_SEPARATOR);
                printf(CPU_PLAY);

                show_scissors_winner(CPU);
                show_paper();

                printf(PLAYER_PLAY);
                printf(CPU_WINS_ROUND);
                printf(LINE_SEPARATOR);
                cpu_score++;
            }

            remaining_rounds--;

            if (remaining_rounds == 0)
            {
                inner_flag = 0;
            }
        }

        if (player_score > cpu_score)
        {
            show_winner_score(PLAYER, &player_score);
        }
        else if (player_score < cpu_score)
        {
            show_winner_score(CPU, &cpu_score);
        }
        else
        {
            printf(NO_WINNER_GAME_MSG);
        }

        show_score(&cpu_score, &player_score);

        flag = 0;
    }
    return 0;
}