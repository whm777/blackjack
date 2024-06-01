// 20240124_game_blackjack_c++.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "inih/cpp/INIReader.h"

#define default_ini_path "./test.ini"
#define WIN 1  //赢
#define LOSE -1   //输
#define EQUAL 0  //得分相同
#define NOTWIN 2  //还没赢

using namespace std;



const uint32_t def_card_color_num = 4;
const uint32_t def_card_role_num = 13;
const uint32_t default_card_num = 52; //默认卡牌数目
const uint32_t default_poker_pairs_num = 4;  //默认卡牌套数
const uint32_t player_num_min = 2;   //最少玩家
const uint32_t player_num_max = 5;     //最多玩家
const string roles[2] = {"Master","Guest"};

struct S_poker_role
{
    uint32_t S_poker_num;
    char S_poker_color;   //颜色有heart(红心),spade（黑桃）.club（梅花）,diamond（方块）
};

void log(string logstring)
{
    //TODO   写日志
}


//卡牌基础角色
class Pker_card  
{
public:
    char poker_color[def_card_color_num] = { 'H','S','C','D' };   //默认卡牌颜色
    char pker_role[def_card_role_num]={'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
    //char role_color[4] = {""};//暂时不设置花色
    //返回卡牌牌面
    char get_role(uint32_t card_role)
    {
        if (card_role < 0 && card_role >13)
        {
            return NULL;
        }
        return this->pker_role[card_role];
    }
    //返回卡牌分数  
    //TODO:应该设置为protuct
    uint32_t get_card_num(uint32_t card_role)
    {
        switch (card_role)
        {
        case 1:
            return 1; break;//如果是A先返回1,需要在规则里面进行判断是否需要算作10
        case 2:
            return 2; break;
        case 3:
            return 3; break;
        case 4:
            return 4; break;
        case 5:
            return 5; break;
        case 6:
            return 6; break;
        case 7:
            return 7; break;
        case 8:
            return 8; break;
        case 9:
            return 9; break;
        case 10:
        case 11:
        case 12:
        case 13:
            return 10;
            break;
        default:
            break;
        }
    }

};

class Poker: public Pker_card
{

//扑克类：
// PS:使用4副扑克除大小王之外的208张牌
public:
    Poker()
    {
        //默认构造函数初始化
        this->poker_base_num = default_card_num;
        this->poker_res_num = this->poker_base_num * this->poker_pairs_num;
        this->poker_pairs_num = default_poker_pairs_num;
    }
    Poker(uint32_t poker_bn, uint32_t poker_pn)
    {
        this->poker_base_num = poker_bn;
        this->poker_pairs_num = poker_pn;
        this->poker_res_num = this->poker_base_num * this->poker_pairs_num;
    }
    //初始化扑克
    void init_poker()
    {
        //初始化扑克
        vector<S_poker_role> ini_pokers(52);//创建一副
        S_poker_role S1;
        
        for(int i =0 ; i < def_card_color_num ; i++)
        {
            for (int j = 0; j < def_card_role_num ; j++)
            {
                S1.S_poker_num = pker_role[j];
                S1.S_poker_color = poker_color[i];
                ini_pokers.push_back(S1);
            }
        }
        //创建对应的副数
        for(int i =0;i< poker_pairs_num;i++)
        { 
            pokers.insert(pokers.end(), ini_pokers.begin(), ini_pokers.end());
        }
    }
    void Shuffle_card()
    {
        random_device rd;
        mt19937 gen(rd());
        shuffle(pokers.begin(), pokers.end(), gen);   //这里的输出结果可能有问题，要注意验证，最好写一个验证接口

    }

    //发牌
    //无需参数，按照顺序输出扑克即可
    S_poker_role deal_poker()
    {
        auto it = pokers.back();
        pokers.pop_back();
        return it;
    }

    
private:
    vector<S_poker_role>  pokers;
    uint32_t poker_base_num;  //扑克的基础数量
    uint32_t poker_res_num;   //扑克的剩余数量
    uint32_t poker_pairs_num;  //扑克的副数
};


struct S_player_role
{
    string player_name;
    string player_role;    //Master
    uint32_t player_id;
    vector<S_poker_role> player_pokers ;
};


//游戏角色
//由2到5个人玩,庄家：游戏中第一个坐下的玩家默认为庄家。
//闲家：本轮不坐庄的玩家。
class player_role 
{
public:
    vector<S_player_role> players;
    uint32_t player_num;
    player_role()
    {
        this->player_num = 2;
        if (this->players.size() == 0)
        {
            S_player_role tem_player;
            tem_player.player_id = 0;
            tem_player.player_name = "dealer";  //名字是随便取的，dealer是发牌者
            tem_player.player_role = roles[0];  //用户角色必须是roles数组中
            this->players.push_back(tem_player);
            tem_player.player_id = 1;
            tem_player.player_name = "Guest1";  //名字是随便取的，
            tem_player.player_role = roles[1];
        }
    }
    void init_player()
    {
        //TODO:可以从文件读取配置
    }

    int32_t add_player(S_player_role player)
    {
        if (players.size() < 2)
        {
            log("add player error;");
            return -1;
        }
        if (comper_player(player) == -1)
        {
            log("add player error;");
            return -1;
        }
        this->players.push_back(player);
        return 0;
    }
    //这里可以重载，做到可以更加用户id或者用户名称删除，用户名称和用户id不可以重复
    int32_t del_player(uint32_t player_id)
    {
        if (players.size() <= 2)
        {
            log("del_player error;");
            return -1;
        }

        auto it = this->players.begin();
        auto endit = this->players.end();
        for (; it != endit; ++it)
        {
            if (it->player_id == player_id)
            {
                this->players.erase(it);
                break;
            }
        }
        return 0;
    }

    int32_t del_player(string player_name)
    {
        if (players.size() <= 2)
        {
            log("del_player error;");
            return -1;
        }

        auto it = this->players.begin();
        auto endit = this->players.end();
        for (; it != endit; ++it)
        {
            if (it->player_name == player_name)
            {
                this->players.erase(it);
                break;
            }
        }
        return 0;
    }

    uint32_t edit_player(uint32_t player_id, string player_name)
    {
        if (players.size() <= 2)
        {
            log("del_player error;");
            return -1;
        }

        auto it = this->players.begin();
        auto endit = this->players.end();
        for (; it != endit; ++it)
        {
            if (it->player_id == player_id)
            {
                S_player_role tem_player;
                tem_player.player_id = player_id;
                tem_player.player_name = player_name;
                tem_player.player_role = it->player_role;
                //先插入再删除
                this->players.insert(it, tem_player);
                this->players.erase(it);
                break;
            }
        }
        return 0;
    }

    void echo_player_name(S_player_role players)
    {
        cout << players.player_name << endl;
    }
    void echo_player_role(S_player_role players)
    {
        cout << players.player_role << endl;
    }
private:
        /*
        comper_player
        参数：S_player_role类型的数据
        返回值：-1表示相同，0表示都不同
        */
        bool comper_player(S_player_role player)
        {
            for (int i = 0; i <= this->players.size(); i++)
            {
                if (this->players[i].player_id == player.player_id || this->players[i].player_name == player.player_name)
                {
                    log("comper_player id or name is same");
                    return -1;
                }
            }
            return 0;
        }

};


//游戏规则
//限定参与人数
//限定牌数
//点数计算
//游戏目标
//胜负判定
class play_rule :public player_role, Poker
{
public:



    //玩家当前分数
    uint32_t player_getpokernum(S_player_role players)
    {
        auto it = players.player_pokers.begin();
        auto endit = players.player_pokers.end();
        uint32_t pokernum = 0;
        for (; it != endit; ++it)
        {
            pokernum = pokernum + get_card_num(it->S_poker_num);
        }
        cout << pokernum << endl;
        return pokernum;
    }

    
    //判断当前用户输赢，player1是庄家，player2是闲家
    int32_t judge_win(S_player_role dealer, S_player_role guest)
    {

        if (this->player_getpokernum(guest) == 21)
        {
            return WIN;
        }
        if (this->player_getpokernum(guest) > 21)
        {
            return LOSE;
        }
        return NOTWIN;
    }


};
    
//玩家得牌
void player_getpoker(S_player_role players)
{
    //传入用户，找到对应的用户然后给用户发牌，或者直接给传入的用户发牌即可
    players.player_pokers.push_back(deal_poker());
}

//输出玩家的牌面
void echo_player_poker(S_player_role players)
{
    auto it = players.player_pokers.begin();
    auto endit = players.player_pokers.end();
    for (; it != endit; ++it)
    {
        cout << it->S_poker_color << " " << it->S_poker_num << endl;
    }
}


int32_t play()
{
    //创建扑克
    player_role PLAY;
    PLAY.init_poker();  //默认有两个用户
    //获取用户信息
    
    //给每个玩家发基础牌
    for (uint32_t j = 0; j < 2; j++)
    { 
        for (uint32_t i = 0; i < PLAY.players.size(); i++)
        {
            PLAY.player_getpoker(PLAY.players[i]);
        }
    }
    //获得当前牌面分数
    PLAY.echo_player_name(PLAY.players[1]);
    PLAY.echo_player_role(PLAY.players[1]);
    PLAY.echo_player_poker(PLAY.players[1]);
    cout<<"当前牌面分数：" << PLAY.player_getpokernum(PLAY.players[1])<<endl;  //查看用户1 的牌面分数
    //输出牌面信息
    


    //初始化用户

    //给玩家发牌


}



int main(uint32_t argc, char* argv[])
{
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <filename>" <<"ini_path"<< "<conf_file_path>" << std::endl;
        return 1;
    }
    string conf_file_path;

    std::string filename = argv[1];
    for (uint32_t i = 2; i < argc; i++)
    {
        if (argv[2] == "ini_path" && argv[3] != nullptr)
        {
            conf_file_path = argv[3];
        }
        else if (argv[2] == "ini_path" && argv[3] == nullptr)
        {
            conf_file_path = default_ini_path;
        }
    }
    /*
    先设置一个默认参数
    用户数2，用户名默认，扑克数默认*/
    uint32_t player_num = 2;
    

    /*
    1.用户数
    2.用户名
    3.扑克牌数
    4.如果可以新增作弊模式或者增加难度  增加难度的方法是庄家可以看下一张牌，如果是闲家赢就自动重新洗牌，洗牌次数限定
    5.新增上帝视角：可以实时输出闲家获胜的概率

    */




    for (int i = 2; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    return 0;
}

