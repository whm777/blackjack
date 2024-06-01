#include "GameRule.h"


PokerHand GameRule::getMaxPokerHand(const std::vector<Card>& hand) {
    if (isRoyalFlush(hand)) {
        return PokerHand::ROYAL_FLUSH;
    }
    else if (isStraightFlush(hand)) {
        return PokerHand::STRAIGHT_FLUSH;
    }
    else if (isFourKind(hand)) {
        return PokerHand::FOUR_OF_A_KIND;
    }
    else if (isFullHouse(hand)) {
        return PokerHand::FULL_HOUSE;
    }
    else if (isFlush(hand)) {
        return PokerHand::FLUSH;
    }
    else if (isStraight(hand)) {
        return PokerHand::STRAIGHT;
    }
    else if (isThreeKind(hand)) {
        return PokerHand::THREE_OF_A_KIND;
    }
    else if (isTowPair(hand)) {
        return PokerHand::TWO_PAIR;
    }
    else if (isOnePair(hand)) {
        return PokerHand::ONE_PAIR;
    }
    else {
        return PokerHand::HIGH_CARD;
    }
}

int32_t GameRule::compareHands(std::vector<Player>& players)
{
        // ��ʼ��ʤ���ߵ�������ʤ���ߵ�����
        int winnerIndex = -1;
        PokerHand maxHand = PokerHand::HIGH_CARD;

        // ����ÿ����ҵ�����
        for (size_t i = 0; i < players.size(); ++i) {
            // ��ȡ��ǰ��ҵ�����
            const std::vector<Card>& hand = players[i].getplayercard();

            // �жϵ�ǰ��ҵ�����
            PokerHand currentHand = getMaxPokerHand(hand);

            // �����ǰ��ҵ����͸��������ʤ���ߵ�������ʤ���ߵ�����
            if (currentHand > maxHand) {
                maxHand = currentHand;
                winnerIndex = i;
            }
            else if (currentHand == maxHand) { // ���������ͬ����Ƚϸ���
                Rank currentHighCard = getHighCard(hand);
                Rank winnerHighCard = getHighCard(players[winnerIndex].getplayercard());
                if (currentHighCard > winnerHighCard) {
                    winnerIndex = i;
                }
            }
        }

        return winnerIndex; // ����ʤ���ߵ�����
    }


bool checkBetting();

bool GameRule::isRoyalFlush(const std::vector<Card>& hand)
{//�ʼ�ͬ��˳
    // ����Ƿ���ͬ��
    Suit suit = hand[0].suit; // ��ȡ��һ���ƵĻ�ɫ
    for (const auto& card : hand) {
        if (card.suit != suit) { // �������һ���ƵĻ�ɫ���һ���Ʋ�ͬ������ͬ��
            return false;
        }
    }

    // ����Ƿ���˳�Ӳ����������ACE
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank); // �������Ƶĵ����洢��������
    }
    std::sort(ranks.begin(), ranks.end()); // �Ե�����������
    // �ʼ�ͬ��˳�ĵ���˳����10��J��Q��K��A����������ĵ����Ƿ��������˳��
    if (ranks != std::vector<Rank>{Rank::TEN, Rank::JACK, Rank::QUEEN, Rank::KING, Rank::ACE}) {
        return false;
    }

    return true; // �����ɫ��ͬ�ҵ�������10��J��Q��K��A��˳�����ǻʼ�ͬ��˳
}


bool GameRule::isStraightFlush(const std::vector<Card>& hand)
{ // ����Ƿ���ͬ��
    Suit suit = hand[0].suit; // ��ȡ��һ���ƵĻ�ɫ
    for (const auto& card : hand) {
        if (card.suit != suit) { // �������һ���ƵĻ�ɫ���һ���Ʋ�ͬ������ͬ��
            return false;
        }
    }

    // ����Ƿ���˳��
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank); // �������Ƶĵ����洢��������
    }
    std::sort(ranks.begin(), ranks.end()); // �Ե�����������
    // ��������ĵ����Ƿ���������
    for (size_t i = 1; i < ranks.size(); ++i) {
        //����ʹ����ǿ������ת����ʹ��Ĭ�ϵ�ö������ת��int�ǰ�ȫ��
        if (static_cast<int>(ranks[i]) != static_cast<int>(ranks[i - 1]) + 1) { // ������������Ƶĵ���������������˳��
            return false;
        }
    }

    return true; // �����ɫ��ͬ�ҵ����������ģ�����ͬ��˳
}


bool GameRule::isFourKind(const std::vector<Card>& hand)
{
    //����
    std::map<Rank, int> rankCount; // ����һ��ӳ�䣬���ڴ洢����������ִ���
    for (const auto& card : hand) {
        rankCount[card.rank]++; // ͳ��ÿ�������ĳ��ִ���
    }

    // ����Ƿ���ĳ�������������Ĵ�
    for (const auto& pair : rankCount) {
        if (pair.second == 4) { // �����ĳ�������������ĴΣ���������
            return true;
        }
    }

    return false; // ���û��ĳ�������������ĴΣ���������
}


bool GameRule::isFullHouse(const std::vector<Card>& hand)
{//��«
    std::map<Rank, int> rankCount; // ����һ��ӳ�䣬���ڴ洢����������ִ���
    for (const auto& card : hand) {
        rankCount[card.rank]++; // ͳ��ÿ�������ĳ��ִ���
    }

    // ����Ƿ���������ͬ�������ƺ�һ����ͬ��������
    bool hasThreeOfAKind = false; // �Ƿ���������ͬ��������
    bool hasPair = false; // �Ƿ���һ����ͬ��������
    for (const auto& pair : rankCount) {
        if (pair.second == 3) { // �����������ͬ�������ƣ������ñ�־Ϊtrue
            hasThreeOfAKind = true;
        }
        else if (pair.second == 2) { // �����һ����ͬ�������ƣ������ñ�־Ϊtrue
            hasPair = true;
        }
    }

    return hasThreeOfAKind && hasPair; // ���ͬʱ������������ͬ�������ƺ�һ����ͬ�������ƣ����Ǻ�«
}


bool GameRule::isFlush(const std::vector<Card>& hand)
{//ͬ��
      // ��ȡ��һ���ƵĻ�ɫ
    Suit suit = hand[0].suit;

    // ���ÿ���ƵĻ�ɫ�Ƿ����һ������ͬ
    for (const auto& card : hand) {
        if (card.suit != suit) { // �������һ���ƵĻ�ɫ���һ���Ʋ�ͬ������ͬ��
            return false;
        }
    }

    return true; // ��������ƵĻ�ɫ����ͬ������ͬ��
}


bool GameRule::isStraight(const std::vector<Card>& hand)
{//˳��
     // ���Ƶĵ����洢��һ��������
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank);
    }

    // �Ե�����������
    std::sort(ranks.begin(), ranks.end());

    // ����Ƿ��������ĵ���
    for (size_t i = 1; i < ranks.size(); ++i) {
        if (static_cast<int>(ranks[i]) != static_cast<int>(ranks[i - 1]) + 1) { // ������������Ƶĵ���������������˳��
            return false;
        }
    }

    return true; // ��������Ƶĵ������������ģ�����˳��
}


bool GameRule::isThreeKind(const std::vector<Card>& hand)
{//����
     // ͳ��ÿ���������ֵĴ���
    std::map<Rank, int> rankCount; // ����һ��ӳ�䣬���ڴ洢����������ִ���
    for (const auto& card : hand) {
        rankCount[card.rank]++; // ͳ��ÿ�������ĳ��ִ���
    }

    // ����Ƿ���������ͬ��������
    for (const auto& pair : rankCount) {
        if (pair.second == 3) { // �����������ͬ�������ƣ���������
            return true;
        }
    }

    return false; // ���û��������ͬ�������ƣ���������
}


bool GameRule::isTowPair(const std::vector<Card>& hand)
{//����
     // ͳ��ÿ���������ֵĴ���
    std::map<Rank, int> rankCount; // ����һ��ӳ�䣬���ڴ洢����������ִ���
    for (const auto& card : hand) {
        rankCount[card.rank]++; // ͳ��ÿ�������ĳ��ִ���
    }

    // ͳ�Ʋ�ͬ����������
    int pairCount = 0;
    for (const auto& pair : rankCount) {
        if (pair.second == 2) { // �����������ͬ�������ƣ�����һ��
            pairCount++;
        }
    }

    return pairCount == 2; // ��������Բ�ͬ�������ƣ���������
}


bool GameRule::isOnePair(const std::vector<Card>& hand)
{//һ��
        // ͳ��ÿ���������ֵĴ���
    std::map<Rank, int> rankCount; // ����һ��ӳ�䣬���ڴ洢����������ִ���
    for (const auto& card : hand) {
        rankCount[card.rank]++; // ͳ��ÿ�������ĳ��ִ���
    }

    // ����Ƿ���һ����ͬ��������
    for (const auto& pair : rankCount) {
        if (pair.second == 2) { // �����һ����ͬ�������ƣ�����һ��
            return true;
        }
    }

    return false; // ���û��һ����ͬ�������ƣ�����һ��
}


Rank GameRule::getHighCard(const std::vector<Card>& hand) {
    // ���Ƶĵ����洢��һ��������
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank);
    }

    // �Ե������������Ա��ҵ����ĵ���
    std::sort(ranks.begin(), ranks.end(), std::greater<Rank>());

    // ���������������еĵ�һ�������������ĵ��������ƣ�
    return ranks[0];
}


