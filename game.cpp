#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Game
{
private:
    std::vector<std::vector<char>> map;
    std::string message;
    int playerX;
    int playerY;
    int starsX;
    int starsY;
    int score;
    int mapSize;
    bool gameOver;
    const char PLAYER = 'X';
    const char EMPTY = 'O';
    const char STARS = '*';

public:
    Game(int size)
    {
        std::srand(std::time(nullptr));
        mapSize = size;
        gameOver = false;

        map = std::vector<std::vector<char>>(size, std::vector<char>(size, EMPTY));

        playerX = 0;
        playerY = 0;
        starsX = 0;
        starsY = 0;
        score = 0;

        map[playerY][playerX] = PLAYER;

        randomStars();

        message = "遊戲已開始 \n請輸入 w, s, a, d 移動玩家 輸入 q 結束遊戲";

        while (!gameOver)
        {
            displayMap();
            handleInput();
        }
    }

    ~Game()
    {
        std::cout << "遊戲已結束! \n總得分: " << score << "\n";
        system("pause");
    }

    void randomStars()
    {
        do
        {
            starsX = rand() % mapSize;
            starsY = rand() % mapSize;
        } while (starsX == playerX && starsY == playerY);

        map[starsY][starsX] = STARS;
    }

    void displayMap()
    {
        system("cls");
        std::cout << "玩家位置: (" << playerX << "," << playerY << ")\n";
        std::cout << "星星位置: (" << starsX << "," << starsY << ")\n\n";
        std::cout << "得分: " << score << "\n";

        for (const auto &i : map)
        {
            for (char v : i)
            {
                std::cout << v << ' ';
            }
            std::cout << '\n';
        }

        if (!message.empty())
        {
            std::cout << message << "\n";
            message = "";
        }
    }

    void handleInput()
    {
        char input;
        std::cin >> input;
        input = tolower(input);

        int oldX = playerX;
        int oldY = playerY;

        switch (input)
        {
        case 'w':
            playerY--;
            break;
        case 's':
            playerY++;
            break;
        case 'a':
            playerX--;
            break;
        case 'd':
            playerX++;
            break;
        case 'q':
            gameOver = true;
            break;
        default:
            message = "僅限輸入 w, s, a, d, q";
            break;
        }

        if (playerX < 0 || playerX >= mapSize || playerY < 0 || playerY >= mapSize)
        {
            playerX = oldX;
            playerY = oldY;
            message = "超出地圖範圍";
            return;
        }

        bool hitStar = (map[playerY][playerX] == STARS);

        map[oldY][oldX] = EMPTY;
        map[playerY][playerX] = PLAYER;

        if (hitStar)
        {
            score++;
            randomStars();
        }
    }
};

int main()
{
    int size;

    do
    {
        std::cout << "請輸入地圖大小 (必須大於 1): ";
        std::cin >> size;
    } while (size < 2);

    Game newGame(size);

    return 0;
}