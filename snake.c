//snake game in c :)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#define WIDTH 60
#define HEIGHT 20
#define SNAKE 'O'
#define FOOD '*'
char board[HEIGHT + 2][WIDTH + 2];
int snake_length = 1;
int snake_x[100], snake_y[100];
int food_x, food_y;
int score = 0;
int lives = 3;
void welcome(){
    printf("\n\n\t\t\t\t\tWelcome to the classic snake game\n\n\t\t\t\t\t  press any key to continue...");
    getch();
    system("cls");
    printf("\n\t\t\t\t\tHINT\n\n\n To play this awesome game use keyboard arrows\n\n To grow your snake you have to let it eat food '*'\n\n When you eat food your score increases by ten so you feel like a hero\n\n You start with 3 lives but be careful not to hit the walls or yourself\n\n If you lost all your lives you can write your name so you enter history, you were a brave warrior T_T\n\n\n If you are ready press any key to start playing...");
    getch();
    system("cls");
}
void game_board() {
    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
                board[i][j] = '~';
            } else {
                board[i][j] = ' ';
            }
        }
    }
    snake_x[0] = HEIGHT / 2;
    snake_y[0] = WIDTH / 2;
    board[snake_x[0]][snake_y[0]] = SNAKE;
    food_x = rand() % HEIGHT + 1;
    food_y = rand() % WIDTH + 1;
    board[food_x][food_y] = FOOD;
}
void display_board() {
    system("cls");
    printf("\t\tScore: %d\t|\tLives: %d\n", score, lives);
    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
void move_snake(int dx, int dy) {
    int new_x = snake_x[0] + dx;
    int new_y = snake_y[0] + dy;
    if (board[new_x][new_y] == '~' || board[new_x][new_y] == SNAKE) {
        lives--;
        if (lives == 0) {
            printf("\n\t\tGAME OVER!\nFinal Score: %d\n", score);
            return;
        }
        game_board();
        return;
    }
    if (board[new_x][new_y] == FOOD) {
        snake_length++;
        score += 10;
        food_x = rand() % HEIGHT + 1;
        food_y = rand() % WIDTH + 1;
        board[food_x][food_y] = FOOD;
    } else {
        board[snake_x[snake_length - 1]][snake_y[snake_length - 1]] = ' ';
    }
    for (int i = snake_length - 1; i > 0; i--) {
        snake_x[i] = snake_x[i - 1];
        snake_y[i] = snake_y[i - 1];
    }
    snake_x[0] = new_x;
    snake_y[0] = new_y;
    board[new_x][new_y] = SNAKE;
}
int main() {
    srand(time(NULL));
    welcome();
    game_board();
    int dx = 0, dy = 1;
    while (1) {
        display_board();
        if (_kbhit()) {
            int key = _getch();
            if (key == 0 || key == 224) {
                key = _getch();
                switch (key) {
                    case 72:
                        if (dx != 1) { dx = -1; dy = 0; }
                        break;
                    case 80:
                        if (dx != -1) { dx = 1; dy = 0; }
                        break;
                    case 75:
                        if (dy != 1) { dx = 0; dy = -1; }
                        break;
                    case 77:
                        if (dy != -1) { dx = 0; dy = 1; }
                        break;
                }
            }
        }
        move_snake(dx, dy);
        if (lives <= 0) {
            break;
        }
        Sleep(150);
    }
    char username[50];
    printf("Enter your name: ");
    scanf("%s", username);
    FILE *file = fopen("player_data.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        return 0;
    }
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_str[26];
    strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(file, "Username: %s | Score: %d | Date: %s\n", username, score, time_str);
    fclose(file);
    file = fopen("player_data.txt", "r");
    if (file == NULL) {
        printf("No previous player data found.\n");
    } else {
        printf("\n\t\tPREVIOUS PLAYS:\n");
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
    return 0;
}
