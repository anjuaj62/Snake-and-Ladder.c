#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIN 100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIN         100
#define MAX_PLAYERS  10
#define NUM_SNAKES    3
#define NUM_LADDERS   3

/* ── Board data ── */
int snakeStart[NUM_SNAKES]  = { 17, 54, 62 };
int snakeEnd[NUM_SNAKES]    = {  7, 34, 19 };
int ladderStart[NUM_LADDERS]= {  3, 25, 56 };
int ladderEnd[NUM_LADDERS]  = { 22, 45, 78 };

/* ── Player data (global so all functions can access) ── */
int position[MAX_PLAYERS];
int started[MAX_PLAYERS];
int players;

/* ======================================================
   FUNCTION 1: setup_game()
   Ask how many players and initialise their data.
====================================================== */
void setup_game(void)
{
    int i;
    printf("===== Snake and Ladder Game =====\n\n");
    do {
        printf("Enter number of players (2 to %d): ", MAX_PLAYERS);
        scanf("%d", &players);
        while (getchar() != '\n');
        if (players < 2 || players > MAX_PLAYERS)
            printf("  Invalid! Please enter 2 to %d.\n", MAX_PLAYERS);
    } while (players < 2 || players > MAX_PLAYERS);

    for (i = 0; i < players; i++) {
        position[i] = 0;
        started[i]  = 0;
    }

    printf("\n  Snakes  (slide DOWN): 17->7  | 54->34 | 62->19\n");
    printf("  Ladders (climb UP)  :  3->22 | 25->45 | 56->78\n");
    printf("  Roll a 1 to enter. Roll a 6 for an extra turn.\n\n");
}

/* ======================================================
   FUNCTION 2: roll_dice()
   Returns a random number from 1 to 6.
====================================================== */
int roll_dice(void)
{
    return rand() % 6 + 1;
}

/* ======================================================
   FUNCTION 3: check_snake()
   If player landed on a snake head, return the tail.
   Otherwise return the same position (no change).
====================================================== */
int check_snake(int pos)
{
    int j;
    for (j = 0; j < NUM_SNAKES; j++) {
        if (pos == snakeStart[j]) {
            printf("  ~~~ SNAKE!  Slide from %d down to %d! ~~~\n",
                   snakeStart[j], snakeEnd[j]);
            return snakeEnd[j];
        }
    }
    return pos;
}

/* ======================================================
   FUNCTION 4: check_ladder()
   If player landed on a ladder foot, return the top.
   Otherwise return the same position (no change).
====================================================== */
int check_ladder(int pos)
{
    int j;
    for (j = 0; j < NUM_LADDERS; j++) {
        if (pos == ladderStart[j]) {
            printf("  *** LADDER! Climb from %d up to %d! ***\n",
                   ladderStart[j], ladderEnd[j]);
            return ladderEnd[j];
        }
    }
    return pos;
}

/* ======================================================
   FUNCTION 5: move_player()
   Move player by dice value, apply ladder/snake.
   Returns 1 if player won, else 0.
====================================================== */
int move_player(int player_num, int dice)
{
    int i = player_num - 1;   /* convert to 0-based index */

    /* Cannot go past 100 — need exact roll */
    if (position[i] + dice > WIN) {
        printf("  Needs exact roll to finish. Stays at %d.\n", position[i]);
        return 0;
    }

    position[i] += dice;
    printf("  Player %d moved to square %d.\n", player_num, position[i]);

    /* Apply ladder first, then snake */
    position[i] = check_ladder(position[i]);
    position[i] = check_snake(position[i]);

    /* Check win */
    if (position[i] == WIN) {
        printf("\n  =========================\n");
        printf("  Player %d WINS!\n", player_num);
        printf("  =========================\n");
        return 1;
    }
    return 0;
}

/* ======================================================
   FUNCTION 6: take_turn()
   Handles one full turn for a player including:
     - enter-on-1 rule
     - normal move
     - extra turn on 6
   Returns 1 if this player just won, else 0.
====================================================== */
int take_turn(int player_num)
{
    int i    = player_num - 1;
    int dice;

    printf("\n---------------------------------\n");
    printf("Player %d's turn", player_num);
    if (started[i])
        printf("  (at square %d)", position[i]);
    else
        printf("  (not on board yet)");
    printf("\nPress ENTER to roll...");
    while (getchar() != '\n');

    dice = roll_dice();
    printf("Dice = %d\n", dice);

    /* ── Must roll 1 to enter ── */
    if (!started[i]) {
        if (dice == 1) {
            started[i]  = 1;
            position[i] = 1;
            printf("  Player %d entered the board at square 1!\n", player_num);
        } else {
            printf("  Need a 1 to enter. Better luck next turn!\n");
        }
        return 0;   /* no win possible on entry turn */
    }

    /* ── Normal move ── */
    if (move_player(player_num, dice))
        return 1;

    /* ── Extra turn on 6 ── */
    while (dice == 6) {
        printf("\n  Player %d rolled a 6 — EXTRA TURN!\n", player_num);
        printf("  Press ENTER to roll again...");
        while (getchar() != '\n');

        dice = roll_dice();
        printf("  Dice = %d\n", dice);

        if (move_player(player_num, dice))
            return 1;
    }

    return 0;
}

/* ======================================================
   FUNCTION 7: play_game()
   Main game loop — keeps cycling through players
   until someone wins.
====================================================== */
void play_game(void)
{
    int i;
    while (1) {
        for (i = 0; i < players; i++) {
            if (take_turn(i + 1))
                return;   /* someone won — stop */
        }
    }
}

/* ======================================================
   MAIN — ties everything together
====================================================== */
int main(void)
{
    srand((unsigned int)time(NULL));
    setup_game();
    play_game();
    printf("\n  Thanks for playing!\n\n");
    return 0;
}