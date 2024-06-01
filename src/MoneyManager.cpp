
#if 0
#include "MoneyManager.h"

MoneyManager::MoneyManager(const std::vector<int>& initial_bet)
{
    // 从文件加载筹码数据，如果文件不存在则使用初始筹码数据
    loadChipsFromFile();

    // 如果加载失败或者玩家数量与初始筹码数量不一致，则使用初始筹码数据
    if (players.empty() || players.size() != initial_bet.size()) {
        for (int i = 0; i < initial_bet.size(); ++i) {
            players.push_back(Player(i + 1, initial_bet[i]));
        }
    }
}
MoneyManager::~MoneyManager()
{
    saveChipsToFile();
}

void MoneyManager::placeMoney(int32_t player_id, int32_t betMoney)
{
    auto it = find_if(players.begin(), players.end(), [player_id](const Player& player) {
        return player.id == player_id;
        });

    if (it != players.end()) {
        it->chips -= bet_amount;
    }
}


void MoneyManager::collectBet(int32_t player_id, int32_t betMoney)
{
    auto it = find_if(players.begin(), players.end(), [player_id](const Player& player) {
        return player.id == player_id;
        });

    if (it != players.end()) {
        it->chips += bet_amount;
    }
}


void MoneyManager::printBet() const
{
    for (const Player& player : players) {
        cout << "玩家 " << player.id << " 筹码数量: " << player.chips << endl;
    }
}

void MoneyManager::loadChipsFromFile()
{
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            int id, chips;
            ss >> id >> chips;
            players.push_back(Player(id, chips));
        }
        file.close();
    }
}


void MoneyManager::saveChipsToFile()
{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Player& player : players) {
            file << player.id << " " << player.chips << endl;
        }
        file.close();
    }

}

#endif