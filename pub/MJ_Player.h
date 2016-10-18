#ifndef MJ_PLAYER_H
#define MJ_PLAYER_H

#include <map>
#include <string>
#include "MJ_AnalyResult.h"

#define DEBUG

class MJ_Player
{
public:
    typedef int _L;
    typedef char CARD;
    typedef const char* pCCARD;

    //pCCARD __cards = "��ABCDEFG  ͲRSTUVWXYZ ��abcdefghi ��rstuvwxyz";
    enum MJ_CARDS{
        MJ_noCard=0,
        MJ_JIUWAN = 'r', MJ_BAWAN, MJ_QIWAN, MJ_LIUWAN, MJ_WUWAN, MJ_SIWAN, MJ_SANWAN, MJ_ERWAN, MJ_YIWAN,
        MJ_JIUTIAO = 'a', MJ_BATIAO, MJ_QITIAO, MJ_LIUTIAO, MJ_WUTIAO, MJ_SITIAO, MJ_SANTIAO, MJ_ERTIAO, MJ_YITIAO,
        MJ_JIUTONG = 'R', MJ_BATONG, MJ_QITONG, MJ_LIUTONG, MJ_WUTONG, MJ_SITONG, MJ_SANTONG, MJ_ERTONG, MJ_YITONG,
        MJ_BAN = 'A', MJ_FA, MJ_ZHONG, MJ_BEI, MJ_XI, MJ_NAN, MJ_DONG,
        MJ_WANG = '0', MJ_ANGNG='*'
    };

    friend class MJ_AnalyResult;

private:
    CARD wang;
    CARD NewCard;
    int paiReCount;//������������
    int paiCount;//���ϵ�������

    CARD paiRecord[50];//�������Ƽ���
    CARD paiList[16];// ���ϵ���

    CARD HuList[16];
    CARD cChiList[16];
    CARD cGangList[8];
    CARD cPengList[8];

    CARD gang[8];
    CARD peng[8];
    CARD chi[16];

    _L _g;
    _L _p;
    _L _c;
    _L _h;

    std::map<CARD, MJ_AnalyResult> AnalyResults;

    int stat;
    int x_ID;
    int p_ID;
    unsigned int score;
    int f_pri;
    std::string p_name;

private:
    bool hasSanLian(CARD*li, CARD c, CARD **res);
    bool hasErLian(CARD*li, CARD c, CARD **res);
    bool hasKanZhang(CARD*li, CARD c, CARD **res);

    void MJ_sort(typename MJ_Player::CARD *a, int len);

public:

    MJ_Player();

    // ���ֳ�ʼ�� �� ���� ���Ҿ���
    void init(pCCARD _paiList, CARD _wang) ;
    // ץ��
    void addCard(CARD newCard) ;

    // ����
    int delCard(CARD card);
    int delCard(int offset);

    int cChi() ;
    int cPeng() ;
    int cGang() ;
    int analysis();

    int Chi(CARD card, CARD c[3]);
    int Peng(CARD card);
    int Gang(CARD card);
    bool Hu(CARD card);

    //����һ���� ��ȡ�����ԳԵ�����ϡ�
    //����ֵ��-1  ������card����0��ʾû�п��ԳԵģ�������������ʾres���ж�����
    //res��Ž�������̰߳�ȫ
    int getCChiList(CARD card, CARD (*res)[3]);

    int copy_chiList(MJ_AnalyResult *);
    int copy_pengList(MJ_AnalyResult *);
    int copy_gangList(MJ_AnalyResult *);


#ifdef DEBUG
    void printTest();
    void printHu();
#endif
};

#define isFENG(card) ((card) <= MJ_Player::MJ_DONG && (card) >= MJ_Player::MJ_BAN)
#define isTONG(card) ((card) >= MJ_Player::MJ_JIUTONG && (card) <= MJ_Player::MJ_YITONG)
#define isTIAO(card) ((card) >= MJ_Player::MJ_JIUTIAO && (card) <= MJ_Player::MJ_YITIAO)
#define isWAN(card) ((card) >= MJ_Player::MJ_JIUWAN && (card) <= MJ_Player::MJ_YIWAN)

//  �ж���һ�źϷ�����
#define isMJCARD(card) (isFENG(card) || isTONG(card) || isTIAO(card) || isWAN(card))

//  ������ͬ����
#define hasSanTong(plist) ((plist)[0] == (plist)[1] && (plist)[0] == (plist)[2])
//  ����
//#define hasSanLian(plist) (!isFENG((plist)[0])) && strchr((plist), (plist)[0]-1) && strchr((plist), (plist)[0]-2)
//  ����
#define hasDuiZi(plist) ((plist)[0] == (plist)[1])
//  ����
//#define hasErLian(plist) (!isFENG((plist)[0]) && (strchr((plist), (plist)[0]-1))
//  ����
//#define hasKanZhang(plist) (!isFENG((plist)[0]) && (strchr((plist),(plist)[0]-2)))

#endif // MJ_Player_H