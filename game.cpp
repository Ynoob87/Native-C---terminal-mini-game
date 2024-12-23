#include <iostream>
#include <vector>
#include <string>

class Game
{
private:
    std::vector<std::vector<char>> map;
    std::string message;
    int playerX;
    int playerY;
    int mapSize;
    bool gameOver;
    const char PLAYER = 'X';
    const char EMPTY = 'O';

public:
    Game(int size)
    {
        mapSize = size;
        gameOver = false;

        map = std::vector<std::vector<char>>(size, std::vector<char>(size, EMPTY));

        playerX = 0;
        playerY = 0;

        map[playerY][playerX] = PLAYER;
        message = "開始遊戲 \n請輸入 w, s, a, d 移動玩家 輸入 q 結束遊戲";

        while (true)
        {
            if (gameOver)
                break;
            displayMap();
            handleInput();
        }
        system("pause");
    }

    void displayMap()
    {
        system("cls");

        if (!message.empty())
        {
            std::cout << message << "\n";
            message = "";
        }

        for (const auto &i : map)
        {
            for (char v : i)
            {
                std::cout << v << ' ';
            }
            std::cout << '\n';
        }
    }

    void handleInput()
    {
        char input;
        std::cin >> input;
        input = tolower(input);

        int oldX = playerX;
        int oldY = playerY;

        if (input == 'w')
        {
            playerY--;
        }
        else if (input == 's')
        {
            playerY++;
        }
        else if (input == 'a')
        {
            playerX--;
        }
        else if (input == 'd')
        {
            playerX++;
        }
        else if (input == 'q')
        {
            gameOver = true;
            message = "遊戲結束";
            return;
        }
        else
        {
            message = "僅限輸入 w, s, a, d, q";
            return;
        }

        if (playerX < 0 || playerX >= mapSize || playerY < 0 || playerY >= mapSize)
        {
            playerX = oldX;
            playerY = oldY;
            message = "超出地圖範圍";
            return;
        }

        message = "玩家已移動到 " + std::to_string(playerX) + ", " + std::to_string(playerY);

        map[oldY][oldX] = EMPTY;
        map[playerY][playerX] = PLAYER;
    }
};

int main()
{
    int size;
    std::cout << "請輸入地圖大小: ";
    std::cin >> size;

    Game newGame(size);

    return 0;
}