#include "Game.h"
void Game::initialStage(std::vector<Player>& players, bool isFirstGame/*, PlayerRole& dealerPosition*/)
{//��ʼ�׶�
    if (isFirstGame) 
    {
        //��һ�ν�����Ϸ���ȳ�ʼ����ҵĽ�ɫ
        std::cout << "Welcome to Texas Hold'em!\n";
        //dealerPosition = PlayerRole::DEALER;
        if (players.size() == 2) {
            //ֻ��������ҵ�ʱ��ֻ��Ҫ��äע����ͨ��Ҽ���
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
        //������ǵ�һ����Ϸ������Ҫ����ҽ�ɫ������λ
        //std::vector<PlayerRole> roles = { PlayerRole::DEALER,  PlayerRole::SMALL_BLIND, PlayerRole::BIG_BLIND, PlayerRole::PLAYER };
        if (players.size() == 2)
        {
            //ֻ��������ҵ������ֻ����ͨ��Һʹ�äע����
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
            //����3����ң�����3����
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
{//���ƽ׶�
    //TODO:����Ҫ����һ���˿˿��Դ򼸾���Ϸ������Ԥ���浽ʣ��10-20�ŵ�ʱ��ʹ���һ���µ��˿�
    //��ÿ���û���licensingStageCardNUM����
    for(int i=0; i<= licensingStageCardNUM ; ++i)
    {
        for (int j = 0; j < players.size(); ++j)
        {
            players[i].setpalyercard(pt.dealingcard());
        }
    }
}

// �������ڴ�����ע�׶�
// ������
// - players: �洢�����Ϣ������
// - big_blind_index: ��äע����������е�����
// - current_bet: ��ǰ�������ע���
// - big_blind_bet: ��äע���
// - small_blind_bet: Сäע���
int32_t bettingStage(std::vector<Player>& players, int32_t big_blind_index, int32_t& current_bet, int32_t big_blind_bet, int32_t small_blind_bet)
{//��ע�׶�
    int num_players = players.size();
    int current_player_index = (big_blind_index + 1) % num_players; // �Ӵ�äע����һλ��ҿ�ʼ��ע
    int round = 0; // ��¼��ǰ����

    // �Ӵ�äע����һλ��ҿ�ʼ�����ж��Ƿ���ע
    while (round < num_players) {
        Player& current_player = players[current_player_index];

        // �������ѷ������ʽ��㣬������
        if (current_player.getfolded() || current_player.getplayermoneynow() == 0) {
            ++round;
            current_player_index = (current_player_index + 1) % num_players;
            continue;
        }

        std::cout << "��ǰ������" << round + 1 << "���ֵ���� " << current_player.getplayerid() << " ��ע��" << std::endl;

        // �ж��Ƿ���äעλ�ã��������ǿ���Ե���äע
        if (round == 0) {
            if (current_player_index == (big_blind_index + 1) % num_players) {
                std::cout << "��� " << current_player.getplayerid() << " �´�äע��" << big_blind_bet << std::endl;
                //current_player.money -= big_blind_bet;
                //current_player.bet += big_blind_bet;
                
                current_player.betting(big_blind_bet);
                current_player.setbet(big_blind_bet);
                current_bet = big_blind_bet;
            }
            else if (current_player_index == (big_blind_index + 2) % num_players) {
                std::cout << "��� " << current_player.getplayerid() << " ��Сäע��" << small_blind_bet << std::endl;
                //current_player.money -= small_blind_bet;
                //current_player.bet += small_blind_bet;
                //current_bet = small_blind_bet;
                current_player.betting(small_blind_bet);
                current_player.setbet(small_blind_bet);
                current_bet = small_blind_bet;
            }
        }

        // ѯ������Ƿ�Ҫ��ע
        std::cout << "����ǰ����ע���Ϊ " << current_player.getbet() << "�������ʽ�Ϊ " << current_player.getplayermoneynow() << std::endl;
        std::cout << "���Ƿ�Ҫ��ע��(y/n): ";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            std::cout << "��������Ҫ��ע�Ľ�";
            int additional_bet;
            std::cin >> additional_bet;

            // ��������ע����Ƿ�Ϸ�
            if (additional_bet > current_player.getplayermoneynow()) {
                std::cout << "�����ʽ��㣬�޷���ע��" << std::endl;
            }
            else if (additional_bet < current_bet - current_player.getbet()) {
                std::cout << "������ע������ڵ�ǰ�����ע�����������롣" << std::endl;
            }
            else {
                //current_player.money -= additional_bet;
                //current_player.bet += additional_bet;
                //current_bet = current_player.bet; // ���������ע���
                current_player.betting(additional_bet);
                current_player.setbet(additional_bet);
                current_bet = current_player.getbet();
            }
        }
        else {
            std::cout << "��ѡ����ע��" << std::endl;
        }

        ++round;
        // ������һλ��ҵ�����
        current_player_index = (current_player_index + 1) % num_players;
    }
}

void Game::flippingStage(PokerTable& pt, std::vector<Player>& players)
{
    //���ƽ׶�
    //�����ķ����൱�ڸ���������ƣ���������ֱ�Ӹ���Ҽ����ƴ���
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


// �������ڴ����ٴ���ע�׶�
// ������
// - players: �洢�����Ϣ������
// - current_bet: ��ǰ�������ע���
int32_t Game::bettingStageagain(std::vector<Player>& players, int& current_bet)
{//�ٴ���ע�׶�
    bool all_in = false;
    bool all_called = false;
    while (!all_in && !all_called) {
        all_in = true;
        all_called = true;
        for (int i = 0; i < players.size(); ++i) {
            uint32_t playerbet = players[i].getbet();
            uint32_t playermoneynow = players[i].getplayermoneynow();
            if (players[i].getfolded() || playermoneynow == 0) {
                continue; // �����Ѿ��������ʽ�ľ������
            }
            std::cout << "��� " << players[i].getplayerid() << "������ǰ����ע���Ϊ " << playerbet << "�������ʽ�Ϊ " << playermoneynow << std::endl;
            std::cout << "���Ƿ�Ҫ��ע��(c: ��ע, r: ��ע, f: ����, a: ȫѺ): ";
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
                        std::cout << "�����ʽ����Ը��ϵ�ǰ�����ע��������ѡ�������" << std::endl;
                        all_called = false;
                    }
                }
                break;
            case 'r':
                int raise_amount;
                std::cout << "��������Ҫ��ע�Ľ�";
                std::cin >> raise_amount;
                if (raise_amount > playermoneynow) {
                    std::cout << "�����ʽ����Լ�ע��������ѡ�������" << std::endl;
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
                std::cout << "��ѡ�����������Ϸ��" << std::endl;
                players[i].setfolded(true); 
                break;
            case 'a':
                std::cout << "��ѡ��ȫѺ��" << std::endl;
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
                std::cout << "��Ч��ѡ��������ѡ��" << std::endl;
                break;
            }
        }
    }
}


void Game::transferStage(PokerTable& pt, std::vector<Player>& players)
{//ת�ƽ׶�  ����ƽ׶���ͬ������

    for (int i = 0; i <= transferStageCardNUM; ++i)
    {
        for (int j = 0; j < players.size(); ++j)
        {
            players[i].setpalyercard(pt.dealingcard());
        }
    }
}


void Game::rivercardStage(PokerTable& pt, std::vector<Player>& players)	//���ƽ׶�=ת�ƽ׶�
{
    this->transferStage(pt, players);
}

// �������ڴ�����ƽ׶�
// ������
// - players: �洢�����Ϣ������
// - community_cards: ������
int32_t comparisonStage(std::vector<Player>& players, const std::vector<int>& community_cards)
{//���ƽ׶�
    //TODO:��Ҫ�Ż��������ϴ���淶�����������������ϵ�ѭ���ж����-�������㣩
// ��������δ��������ң��Ƚ������ƴ�С
    int32_t winerIndex = GameRule::compareHands(players);
    //TODO:Ӯ�һ�����г���������ʵ�ò���������Ǻܺõģ������Ȳ�д��


    /*
    for (int i = 0; i < players.size(); ++i) {
        if (!players[i].getfolded()) {
            for (int j = i + 1; j < players.size(); ++j) {
                if (!players[j].getfolded()) {
                    int result = compareHands(players[i].hand, players[j].hand);
                    if (result == 0) {
                        // ƽ�֣�����ҵĶ�ע����
                        players[i].bet += players[j].bet;
                        players[j].bet = 0;
                    }
                    else if (result > 0) {
                        // ���iʤ���������j�Ķ�עת�Ƹ����i
                        players[i].bet += players[j].bet;
                        players[j].bet = 0;
                    }
                    else {
                        // ���jʤ���������i�Ķ�עת�Ƹ����j
                        players[j].bet += players[i].bet;
                        players[i].bet = 0;
                    }
                }
            }
        }
    }*/
}