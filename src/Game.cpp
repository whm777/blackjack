#include "Game.h"
void Game::initialStage(std::vector<Player>& players, bool isFirstGame/*, PlayerRole& dealerPosition*/)
{//起始阶段
    if (isFirstGame) 
    {
        //第一次进行游戏，先初始化玩家的角色
        std::cout << "Welcome to Texas Hold'em!\n";
        //dealerPosition = PlayerRole::DEALER;
        if (players.size() == 2) {
            //只有两个玩家的时候只需要大盲注和普通玩家即可
            std::vector<PlayerRole> roles = {  PlayerRole::BIG_BLIND ,PlayerRole::PLAYER };
            for (int i = 0; i < 2; ++i) {
                players[i].setprole(roles[i]);
                //std::cout << "Player " << i + 1 << " is the " << static_cast<int>(roles[i]) + 1 << " to act.\n";
            }
        }
        else if(players.size() == 3) 
        {
            std::vector<PlayerRole> roles = { PlayerRole::DEALER,  PlayerRole::SMALL_BLIND, PlayerRole::BIG_BLIND, };
            for (int i = 0; i < players.size(); ++i) 
            {
                players[i].setprole(roles[i]);
                //std::cout << "Player " << i + 1 << " is the " << static_cast<int>(roles[i]) + 1 << " to act.\n";
            }
        }
        else
        {
            std::vector<PlayerRole> roles = { PlayerRole::DEALER,  PlayerRole::SMALL_BLIND, PlayerRole::BIG_BLIND, PlayerRole::PLAYER};
            for (int i = 0; i < 3; ++i)
            {
                players[i].setprole(roles[i]);
                //std::cout << "Player " << i + 1 << " is the " << static_cast<int>(roles[i]) + 1 << " to act.\n";
            }
            for (int i = 3; i < players.size(); ++i)
            {
                players[i].setprole(roles[4]);
            }
        }
    }
    else
    {
        //如果不是第一次游戏，就需要对玩家角色进行移位
        //std::vector<PlayerRole> roles = { PlayerRole::DEALER,  PlayerRole::SMALL_BLIND, PlayerRole::BIG_BLIND, PlayerRole::PLAYER };
        if (players.size() == 2)
        {
            //只有两个玩家的情况下只有普通玩家和大盲注两种
            for (int i = 0; i < players.size(); i++)
            {
                switch (players[i].getprole())
                {
                case PlayerRole::PLAYER:
                    players[i].setprole(PlayerRole::BIG_BLIND);
                    break;
                case PlayerRole::BIG_BLIND:
                    players[i].setprole(PlayerRole::PLAYER);
                    break;
                }
            }
        }
        else if (players.size() == 3)
        {
            //std::vector<PlayerRole> roles = { PlayerRole::DEALER,  PlayerRole::SMALL_BLIND, PlayerRole::BIG_BLIND, };
            for (int i = 0; i < players.size(); ++i)
            {
                switch (players[i].getprole()) {
                case PlayerRole::DEALER:
                    players[i].setprole(PlayerRole::SMALL_BLIND);
                    break;
                case PlayerRole::BIG_BLIND:
                    players[i].setprole(PlayerRole::DEALER);
                    break;
                case PlayerRole::SMALL_BLIND:
                    players[i].setprole(PlayerRole::BIG_BLIND);
                }
            }
        }
        else
        {
            //超过3个玩家（不含3个）
            std::vector<PlayerRole> roles = { PlayerRole::DEALER,  PlayerRole::SMALL_BLIND, PlayerRole::BIG_BLIND };
            switch (players[players.size()].getprole())
            {
            case PlayerRole::BIG_BLIND:
                for (int i = 0; i < players.size(); ++i)
                {
                    players[i].setprole(PlayerRole::PLAYER);
                }
                players[players.size()].setprole(PlayerRole::SMALL_BLIND);
                players[players.size()-1].setprole(PlayerRole::DEALER);
                players[0].setprole(PlayerRole::BIG_BLIND);
            case PlayerRole::SMALL_BLIND:
                for (int i = 0; i < players.size(); ++i)
                {
                    players[i].setprole(PlayerRole::PLAYER);
                }
                players[players.size()].setprole(PlayerRole::DEALER);
                players[1].setprole(PlayerRole::BIG_BLIND);
                players[0].setprole(PlayerRole::SMALL_BLIND);
            case PlayerRole::DEALER:
                for (int i = 0; i < players.size(); ++i)
                {
                    players[i].setprole(PlayerRole::PLAYER);
                }
                players[2].setprole(PlayerRole::BIG_BLIND);
                players[1].setprole(PlayerRole::SMALL_BLIND);
                players[0].setprole(PlayerRole::DEALER);
            }
        }
    }

}


void Game::licensingStage(PokerTable& pt, std::vector<Player>& players)
{//发牌阶段
    //TODO:这里要考虑一副扑克可以打几局游戏，初步预想玩到剩余10-20张的时候就创建一副新的扑克
    //给每个用户发licensingStageCardNUM张牌
    for(int i=0; i<= licensingStageCardNUM ; ++i)
    {
        for (int j = 0; j < players.size(); ++j)
        {
            players[i].setpalyercard(pt.dealingcard());
        }
    }
}

// 函数用于处理下注阶段
// 参数：
// - players: 存储玩家信息的向量
// - big_blind_index: 大盲注玩家在向量中的索引
// - current_bet: 当前的最高下注金额
// - big_blind_bet: 大盲注金额
// - small_blind_bet: 小盲注金额
int32_t bettingStage(std::vector<Player>& players, int32_t big_blind_index, int32_t& current_bet, int32_t big_blind_bet, int32_t small_blind_bet)
{//下注阶段
    int num_players = players.size();
    int current_player_index = (big_blind_index + 1) % num_players; // 从大盲注的下一位玩家开始下注
    int round = 0; // 记录当前轮数

    // 从大盲注的下一位玩家开始依次判断是否下注
    while (round < num_players) {
        Player& current_player = players[current_player_index];

        // 如果玩家已放弃或资金不足，则跳过
        if (current_player.getfolded() || current_player.getplayermoneynow() == 0) {
            ++round;
            current_player_index = (current_player_index + 1) % num_players;
            continue;
        }

        std::cout << "当前轮数：" << round + 1 << "，轮到玩家 " << current_player.getplayerid() << " 下注。" << std::endl;

        // 判断是否是盲注位置，是则进行强制性的下盲注
        if (round == 0) {
            if (current_player_index == (big_blind_index + 1) % num_players) {
                std::cout << "玩家 " << current_player.getplayerid() << " 下大盲注：" << big_blind_bet << std::endl;
                //current_player.money -= big_blind_bet;
                //current_player.bet += big_blind_bet;
                
                current_player.betting(big_blind_bet);
                current_player.setbet(big_blind_bet);
                current_bet = big_blind_bet;
            }
            else if (current_player_index == (big_blind_index + 2) % num_players) {
                std::cout << "玩家 " << current_player.getplayerid() << " 下小盲注：" << small_blind_bet << std::endl;
                //current_player.money -= small_blind_bet;
                //current_player.bet += small_blind_bet;
                //current_bet = small_blind_bet;
                current_player.betting(small_blind_bet);
                current_player.setbet(small_blind_bet);
                current_bet = small_blind_bet;
            }
        }

        // 询问玩家是否要下注
        std::cout << "您当前的下注金额为 " << current_player.getbet() << "，您的资金为 " << current_player.getplayermoneynow() << std::endl;
        std::cout << "您是否要下注？(y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            std::cout << "请输入您要下注的金额：";
            int additional_bet;
            std::cin >> additional_bet;

            // 检查玩家下注金额是否合法
            if (additional_bet > current_player.getplayermoneynow()) {
                std::cout << "您的资金不足，无法下注。" << std::endl;
            }
            else if (additional_bet < current_bet - current_player.getbet()) {
                std::cout << "您的下注金额少于当前最高下注金额，请重新输入。" << std::endl;
            }
            else {
                //current_player.money -= additional_bet;
                //current_player.bet += additional_bet;
                //current_bet = current_player.bet; // 更新最高下注金额
                current_player.betting(additional_bet);
                current_player.setbet(additional_bet);
                current_bet = current_player.getbet();
            }
        }
        else {
            std::cout << "您选择不下注。" << std::endl;
        }

        ++round;
        // 更新下一位玩家的索引
        current_player_index = (current_player_index + 1) % num_players;
    }
}

void Game::flippingStage(PokerTable& pt, std::vector<Player>& players)
{
    //翻牌阶段
    //牌桌的翻牌相当于给所有玩家牌，所以这里直接给玩家加手牌处理
    std::vector<Card> tmp_card;
    pt.showtablecard(tmp_card, flippingStageCardNUM);
    for (int i = 0; i <= flippingStageCardNUM; ++i)
    {
        for (int j = 0; j < players.size(); ++j)
        {
            players[j].setpalyercard(tmp_card[i]);
        }
    }
}


// 函数用于处理再次下注阶段
// 参数：
// - players: 存储玩家信息的向量
// - current_bet: 当前的最高下注金额
int32_t Game::bettingStageagain(std::vector<Player>& players, int& current_bet)
{//再次下注阶段
    bool all_in = false;
    bool all_called = false;
    while (!all_in && !all_called) {
        all_in = true;
        all_called = true;
        for (int i = 0; i < players.size(); ++i) {
            uint32_t playerbet = players[i].getbet();
            uint32_t playermoneynow = players[i].getplayermoneynow();
            if (players[i].getfolded() || playermoneynow == 0) {
                continue; // 跳过已经放弃或资金耗尽的玩家
            }
            std::cout << "玩家 " << players[i].getplayerid() << "，您当前的下注金额为 " << playerbet << "，您的资金为 " << playermoneynow << std::endl;
            std::cout << "您是否要下注？(c: 跟注, r: 加注, f: 放弃, a: 全押): ";
            char choice;
            std::cin >> choice;

            switch (choice) {
            case 'c':
                if (playerbet < current_bet) {
                    int diff = current_bet - playerbet;
                    if (playermoneynow >= diff) {
                        //players[i].money -= diff;
                        //players[i].bet += diff;
                        players[i].setbet(diff);
                    }
                    else {
                        std::cout << "您的资金不足以跟上当前最高下注金额，请重新选择操作。" << std::endl;
                        all_called = false;
                    }
                }
                break;
            case 'r':
                int raise_amount;
                std::cout << "请输入您要加注的金额：";
                std::cin >> raise_amount;
                if (raise_amount > playermoneynow) {
                    std::cout << "您的资金不足以加注，请重新选择操作。" << std::endl;
                    all_called = false;
                }
                else {
                   // players[i].money -= raise_amount;
                    //players[i].bet += raise_amount;
                    players[i].setbet(raise_amount);
                    current_bet += raise_amount;
                    all_called = false;
                }
                break;
            case 'f':
                std::cout << "您选择放弃本轮游戏。" << std::endl;
                players[i].setfolded(true); 
                break;
            case 'a':
                std::cout << "您选择全押！" << std::endl;
                if (playermoneynow > current_bet) {
                    //players[i].bet += players[i].money;
                    players[i].setbet(playermoneynow);
                    current_bet = players[i].getbet();
                }
                else {
                    //players[i].bet += players[i].money;
                    players[i].setbet(playermoneynow);
                    all_called = false;
                }
                all_in = false;
                break;
            default:
                std::cout << "无效的选择，请重新选择。" << std::endl;
                break;
            }
        }
    }
}


void Game::transferStage(PokerTable& pt, std::vector<Player>& players)
{//转牌阶段  与河牌阶段相同操作，

    for (int i = 0; i <= transferStageCardNUM; ++i)
    {
        for (int j = 0; j < players.size(); ++j)
        {
            players[i].setpalyercard(pt.dealingcard());
        }
    }
}


void Game::rivercardStage(PokerTable& pt, std::vector<Player>& players)	//河牌阶段=转牌阶段
{
    this->transferStage(pt, players);
}

// 函数用于处理比牌阶段
// 参数：
// - players: 存储玩家信息的向量
// - community_cards: 公共牌
int32_t comparisonStage(std::vector<Player>& players, const std::vector<int>& community_cards)
{//比牌阶段
    //TODO:需要优化，不符合代码规范（不可以有三层以上的循环判断语句-不含三层）
// 遍历所有未放弃的玩家，比较其手牌大小
    int32_t winerIndex = GameRule::compareHands(players);
    //TODO:赢家获得所有筹码这里其实用财务管理类是很好的，但是先不写了


    /*
    for (int i = 0; i < players.size(); ++i) {
        if (!players[i].getfolded()) {
            for (int j = i + 1; j < players.size(); ++j) {
                if (!players[j].getfolded()) {
                    int result = compareHands(players[i].hand, players[j].hand);
                    if (result == 0) {
                        // 平局，将玩家的赌注返回
                        players[i].bet += players[j].bet;
                        players[j].bet = 0;
                    }
                    else if (result > 0) {
                        // 玩家i胜利，将玩家j的赌注转移给玩家i
                        players[i].bet += players[j].bet;
                        players[j].bet = 0;
                    }
                    else {
                        // 玩家j胜利，将玩家i的赌注转移给玩家j
                        players[j].bet += players[i].bet;
                        players[i].bet = 0;
                    }
                }
            }
        }
    }*/
}