#include <stdio.h>

#define PLAYER_ONE 0
#define PLAYER_TWO 1

void play_game(int cur_n_value);
int get_new_n_value(int n);
int number_of_ones(int n);

int main() {
    int input;

    printf("enter N value (just a number):\n");
    scanf("%d",&input); //input is an integer -> 4 bytes, if input is 135 then it's binary form is:
                        //00000000 0000000 0000000 10000111


    play_game(input);

}

void play_game(int cur_n_value) {
    int current_player = PLAYER_ONE;

    while (cur_n_value != -1) {
        printf("value of N is: %d\n", cur_n_value);
        cur_n_value = get_new_n_value(cur_n_value);
        current_player = current_player == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE;
    }
    printf("the loser is %s\n", (current_player == PLAYER_ONE ? "player one" : "player two"));
}


/*
 *  returns a number n-2^k that has the
 *  same amount of 1's in its binary form
 *  -1 otherwise
 * */
int get_new_n_value(int n) {
    int temp = 1;

    while (temp < n){
        if (number_of_ones(n) == number_of_ones(n-temp)){
            return n-temp;
        }
        temp *= 2;
    }
    return -1;
}

/*
 * returns number of ones in n's binary form
 * algorithm: check if right most bit is 1, if yes: count.
 * move bits to the right and check again until number is 0
 * */
int number_of_ones(int n) {
    int ones_in_number = 0;

    while (n != 0){
        if (n&0x1){
            ones_in_number++;
        }
        n >>= 1;
    }

    return ones_in_number;
}