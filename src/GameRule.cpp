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
        // 初始化胜利者的索引和胜利者的牌型
        int winnerIndex = -1;
        PokerHand maxHand = PokerHand::HIGH_CARD;

        // 遍历每个玩家的手牌
        for (size_t i = 0; i < players.size(); ++i) {
            // 获取当前玩家的手牌
            const std::vector<Card>& hand = players[i].getplayercard();

            // 判断当前玩家的牌型
            PokerHand currentHand = getMaxPokerHand(hand);

            // 如果当前玩家的牌型更大，则更新胜利者的索引和胜利者的牌型
            if (currentHand > maxHand) {
                maxHand = currentHand;
                winnerIndex = i;
            }
            else if (currentHand == maxHand) { // 如果牌型相同，则比较高牌
                Rank currentHighCard = getHighCard(hand);
                Rank winnerHighCard = getHighCard(players[winnerIndex].getplayercard());
                if (currentHighCard > winnerHighCard) {
                    winnerIndex = i;
                }
            }
        }

        return winnerIndex; // 返回胜利者的索引
    }


bool checkBetting();

bool GameRule::isRoyalFlush(const std::vector<Card>& hand)
{//皇家同花顺
    // 检查是否是同花
    Suit suit = hand[0].suit; // 获取第一张牌的花色
    for (const auto& card : hand) {
        if (card.suit != suit) { // 如果任意一张牌的花色与第一张牌不同，则不是同花
            return false;
        }
    }

    // 检查是否是顺子并且最大牌是ACE
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank); // 将所有牌的点数存储到向量中
    }
    std::sort(ranks.begin(), ranks.end()); // 对点数进行排序
    // 皇家同花顺的点数顺序是10、J、Q、K、A，检查排序后的点数是否满足这个顺序
    if (ranks != std::vector<Rank>{Rank::TEN, Rank::JACK, Rank::QUEEN, Rank::KING, Rank::ACE}) {
        return false;
    }

    return true; // 如果花色相同且点数符合10、J、Q、K、A的顺序，则是皇家同花顺
}


bool GameRule::isStraightFlush(const std::vector<Card>& hand)
{ // 检查是否是同花
    Suit suit = hand[0].suit; // 获取第一张牌的花色
    for (const auto& card : hand) {
        if (card.suit != suit) { // 如果任意一张牌的花色与第一张牌不同，则不是同花
            return false;
        }
    }

    // 检查是否是顺子
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank); // 将所有牌的点数存储到向量中
    }
    std::sort(ranks.begin(), ranks.end()); // 对点数进行排序
    // 检查排序后的点数是否是连续的
    for (size_t i = 1; i < ranks.size(); ++i) {
        //这是使用了强制类型转换，使用默认的枚举类型转换int是安全的
        if (static_cast<int>(ranks[i]) != static_cast<int>(ranks[i - 1]) + 1) { // 如果任意两张牌的点数不连续，则不是顺子
            return false;
        }
    }

    return true; // 如果花色相同且点数是连续的，则是同花顺
}


bool GameRule::isFourKind(const std::vector<Card>& hand)
{
    //四条
    std::map<Rank, int> rankCount; // 创建一个映射，用于存储点数及其出现次数
    for (const auto& card : hand) {
        rankCount[card.rank]++; // 统计每个点数的出现次数
    }

    // 检查是否有某个点数出现了四次
    for (const auto& pair : rankCount) {
        if (pair.second == 4) { // 如果有某个点数出现了四次，则是四条
            return true;
        }
    }

    return false; // 如果没有某个点数出现了四次，则不是四条
}


bool GameRule::isFullHouse(const std::vector<Card>& hand)
{//葫芦
    std::map<Rank, int> rankCount; // 创建一个映射，用于存储点数及其出现次数
    for (const auto& card : hand) {
        rankCount[card.rank]++; // 统计每个点数的出现次数
    }

    // 检查是否有三张相同点数的牌和一对相同点数的牌
    bool hasThreeOfAKind = false; // 是否有三张相同点数的牌
    bool hasPair = false; // 是否有一对相同点数的牌
    for (const auto& pair : rankCount) {
        if (pair.second == 3) { // 如果有三张相同点数的牌，则设置标志为true
            hasThreeOfAKind = true;
        }
        else if (pair.second == 2) { // 如果有一对相同点数的牌，则设置标志为true
            hasPair = true;
        }
    }

    return hasThreeOfAKind && hasPair; // 如果同时满足有三张相同点数的牌和一对相同点数的牌，则是葫芦
}


bool GameRule::isFlush(const std::vector<Card>& hand)
{//同花
      // 获取第一张牌的花色
    Suit suit = hand[0].suit;

    // 检查每张牌的花色是否与第一张牌相同
    for (const auto& card : hand) {
        if (card.suit != suit) { // 如果任意一张牌的花色与第一张牌不同，则不是同花
            return false;
        }
    }

    return true; // 如果所有牌的花色都相同，则是同花
}


bool GameRule::isStraight(const std::vector<Card>& hand)
{//顺子
     // 将牌的点数存储到一个向量中
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank);
    }

    // 对点数进行排序
    std::sort(ranks.begin(), ranks.end());

    // 检查是否是连续的点数
    for (size_t i = 1; i < ranks.size(); ++i) {
        if (static_cast<int>(ranks[i]) != static_cast<int>(ranks[i - 1]) + 1) { // 如果任意两张牌的点数不连续，则不是顺子
            return false;
        }
    }

    return true; // 如果所有牌的点数都是连续的，则是顺子
}


bool GameRule::isThreeKind(const std::vector<Card>& hand)
{//三条
     // 统计每个点数出现的次数
    std::map<Rank, int> rankCount; // 创建一个映射，用于存储点数及其出现次数
    for (const auto& card : hand) {
        rankCount[card.rank]++; // 统计每个点数的出现次数
    }

    // 检查是否有三张相同点数的牌
    for (const auto& pair : rankCount) {
        if (pair.second == 3) { // 如果有三张相同点数的牌，则是三条
            return true;
        }
    }

    return false; // 如果没有三张相同点数的牌，则不是三条
}


bool GameRule::isTowPair(const std::vector<Card>& hand)
{//两对
     // 统计每个点数出现的次数
    std::map<Rank, int> rankCount; // 创建一个映射，用于存储点数及其出现次数
    for (const auto& card : hand) {
        rankCount[card.rank]++; // 统计每个点数的出现次数
    }

    // 统计不同点数的数量
    int pairCount = 0;
    for (const auto& pair : rankCount) {
        if (pair.second == 2) { // 如果有两张相同点数的牌，则是一对
            pairCount++;
        }
    }

    return pairCount == 2; // 如果有两对不同点数的牌，则是两对
}


bool GameRule::isOnePair(const std::vector<Card>& hand)
{//一对
        // 统计每个点数出现的次数
    std::map<Rank, int> rankCount; // 创建一个映射，用于存储点数及其出现次数
    for (const auto& card : hand) {
        rankCount[card.rank]++; // 统计每个点数的出现次数
    }

    // 检查是否有一对相同点数的牌
    for (const auto& pair : rankCount) {
        if (pair.second == 2) { // 如果有一对相同点数的牌，则是一对
            return true;
        }
    }

    return false; // 如果没有一对相同点数的牌，则不是一对
}


Rank GameRule::getHighCard(const std::vector<Card>& hand) {
    // 将牌的点数存储到一个向量中
    std::vector<Rank> ranks;
    for (const auto& card : hand) {
        ranks.push_back(card.rank);
    }

    // 对点数进行排序，以便找到最大的点数
    std::sort(ranks.begin(), ranks.end(), std::greater<Rank>());

    // 返回排序后的向量中的第一个点数，即最大的点数（高牌）
    return ranks[0];
}


