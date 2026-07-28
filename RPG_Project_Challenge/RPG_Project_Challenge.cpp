#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm> // STEP 4: std::min 사용을 위해 추가
using namespace std;

// =============================================
// 도전 STEP 1 : setPotion 함수
// =============================================
void setPotion(int count, int* p_HPPotion, int* p_MPPotion)
{
    if (p_HPPotion != nullptr)
    {
        *p_HPPotion = count;
    }
    if (p_MPPotion != nullptr)
    {
        *p_MPPotion = count;
    }
}

struct Item
{
    string name;
    int price = 0;
    void PrintInfo() const
    {
        cout << name << " (" << price << "G)" << endl;
    }
};

struct PotionRecipe
{
    string potionName;

    string ingredient1;
    int ingredient1Count = 0;

    string ingredient2;
    int ingredient2Count = 0;

    void PrintInfo() const
    {
        cout << potionName
            << "("
            << ingredient1
            << "x"
            << ingredient1Count
            << ","
            << ingredient2
            << "x"
            << ingredient2Count
            << ")"
            << endl;
    }
};

class AlchemyWorkshop
{
private:
    vector<PotionRecipe> recipes;

public:
    AlchemyWorkshop()
    {
        PotionRecipe hpPotion;
        hpPotion.potionName = "HP 포션";
        hpPotion.ingredient1 = "붉은 허브";
        hpPotion.ingredient1Count = 1;
        hpPotion.ingredient2 = "맑은 물";
        hpPotion.ingredient2Count = 1;
        recipes.push_back(hpPotion);

        PotionRecipe mpPotion;
        mpPotion.potionName = "MP 포션";
        mpPotion.ingredient1 = "푸른 마나꽃";
        mpPotion.ingredient1Count = 1;
        mpPotion.ingredient2 = "맑은 물";
        mpPotion.ingredient2Count = 1;
        recipes.push_back(mpPotion);

        PotionRecipe staminaPotion;
        staminaPotion.potionName = "에너지 포션";
        staminaPotion.ingredient1 = "붉은 허브";
        staminaPotion.ingredient1Count = 1;
        staminaPotion.ingredient2 = "싱싱한 베리";
        staminaPotion.ingredient2Count = 1;
        recipes.push_back(staminaPotion);
    }

    void ShowAllRecipes() const
    {
        cout << "\n===== 전체 포션 레시피 =====\n";
        for (const PotionRecipe& recipe : recipes)
        {
            recipe.PrintInfo();
        }
    }

    void SearchByName(string name) const
    {
        bool found = false;
        cout << "\n검색 결과\n";

        for (const PotionRecipe& recipe : recipes)
        {
            if (recipe.potionName == name)
            {
                recipe.PrintInfo();
                found = true;
            }
        }

        if (found == false)
        {
            cout << "찾을 수 없습니다.\n";
        }
    }

    void SearchByIngredient(string ingredient) const
    {
        bool found = false;
        int foundCount = 0;

        cout << "\n검색 결과\n";

        for (const PotionRecipe& recipe : recipes)
        {
            if (recipe.ingredient1 == ingredient || recipe.ingredient2 == ingredient)
            {
                recipe.PrintInfo();
                found = true;
                foundCount++;
            }
        }

        if (found == false)
        {
            cout << "찾을 수 없습니다.\n";
        }
        else
        {
            cout << "총 " << foundCount << "개의 레시피를 찾았습니다.\n";
        }
    }
};

class Player
{
protected:
    string name;
    string job;

    int level;
    int exp;
    int maxExp;

    int hp;
    int maxHp; // STEP 4: 최대 HP
    int mp;
    int maxMp; // STEP 4: 최대 MP
    int power;
    int defence;

public:
    Player(string name, int hp, int mp, int power, int defence)
    {
        this->name = name;
        this->hp = hp;
        this->maxHp = hp;
        this->mp = mp;
        this->maxMp = mp;
        this->power = power;
        this->defence = defence;
        this->level = 1;
        this->exp = 0;
        this->maxExp = 100;
    }
    virtual ~Player() {}

    string getName() { return name; }
    string getJob() { return job; }
    int getLevel() { return level; }
    int getHp() { return hp; }
    int getMaxHp() { return maxHp; }
    int getMp() { return mp; }
    int getMaxMp() { return maxMp; }
    int getPower() { return power; }
    int getDefence() { return defence; }

    void setName(string name) { this->name = name; }
    void setJob(string job) { this->job = job; }
    void setLevel(int level) { this->level = level; }
    void setHp(int hp) { this->hp = hp; }
    void setMp(int mp) { this->mp = mp; }
    void setPower(int power) { this->power = power; }
    void setDefence(int defence) { this->defence = defence; }

    // =============================================
    // 도전 STEP 4 : 포션 사용 메소드
    // =============================================
    bool useHpPotion()
    {
        if (hp >= maxHp)
        {
            cout << "이미 HP가 가득 차 있습니다!\n";
            return false;
        }
        int oldHp = hp;
        hp = min(hp + 50, maxHp);
        cout << "* HP 포션 사용! HP 50 회복 (" << oldHp << " -> " << hp << ")\n";
        return true;
    }

    bool useMpPotion()
    {
        if (mp >= maxMp)
        {
            cout << "이미 MP가 가득 차 있습니다!\n";
            return false;
        }
        int oldMp = mp;
        mp = min(mp + 50, maxMp);
        cout << "* MP 포션 사용! MP 50 회복 (" << oldMp << " -> " << mp << ")\n";
        return true;
    }

    void gainExp(int amount)
    {
        exp += amount;
        cout << "-> 경험치 +" << amount << " 획득! (현재 경험치: " << exp << "/" << maxExp << ")\n";

        while (exp >= maxExp)
        {
            exp -= maxExp;
            int oldLevel = level;
            level++;

            maxHp += 10;
            hp = maxHp; // 레벨업 시 HP 완충
            maxMp += 5;
            mp = maxMp; // 레벨업 시 MP 완충
            power += 5;

            maxExp += 50;

            cout << "\n... 레벨업 조건 충족\n";
            cout << "-> 레벨 업! Lv." << oldLevel << " -> Lv." << level << "\n";
            cout << "-> HP +10, MP +5, 공격력 +5 증가!\n\n";
        }
    }

    void printPlayerStatus()
    {
        cout << "\n===== 캐릭터 정보 =====\n";
        cout << "이름 : " << name << endl;
        cout << "직업 : " << job << endl;
        cout << "레벨 : Lv." << level << " (EXP: " << exp << "/" << maxExp << ")" << endl;
        cout << "HP : " << hp << " / " << maxHp << endl;
        cout << "MP : " << mp << " / " << maxMp << endl;
        cout << "공격력 : " << power << endl;
        cout << "방어력 : " << defence << endl;
    }

    virtual void attack() = 0;
};

class Swordmaster : public Player
{
public:
    Swordmaster(string name, int hp, int mp, int power, int defence)
        : Player(name, hp, mp, power, defence)
    {
        job = "검사";
        this->power += 30;
        if (this->power > 60) this->power = 60;
    }
    void attack() override
    {
        cout << name << "이(가) 검으로 강하게 공격합니다!!\n";
        cout << "현재 공격력: " << power << endl;
    }
};

class Magician : public Player
{
public:
    Magician(string name, int hp, int mp, int power, int defence)
        : Player(name, hp, mp, power, defence)
    {
        job = "마법사";
        this->mp += 30;
        this->maxMp += 30;
    }
    void attack() override
    {
        cout << name << "이(가) 마법을 사용해 공격합니다!!\n";
        cout << "현재 MP: " << mp << endl;
    }
};

class Paladin : public Player
{
public:
    Paladin(string name, int hp, int mp, int power, int defence)
        : Player(name, hp, mp, power, defence)
    {
        job = "성기사";
        this->defence += 30;
        if (this->defence > 60) this->defence = 60;
    }
    void attack() override
    {
        cout << name << "이(가) 성력을 사용해 공격합니다!!\n";
        cout << "현재 방어력: " << defence << endl;
    }
};

class Monster
{
private:
    string name;
    int hp;
    int power;
    int defence;
    string dropItemName;
    int dropItemPrice;
    int expReward;

public:
    Monster(string name, int hp, int power, int defence, string dropItemName, int dropItemPrice, int expReward)
    {
        this->name = name;
        this->hp = hp;
        this->power = power;
        this->defence = defence;
        this->dropItemName = dropItemName;
        this->dropItemPrice = dropItemPrice;
        this->expReward = expReward;
    }

    void printMonsterStatus()
    {
        cout << "\n===== 몬스터 정보 =====\n";
        cout << "이름: " << name << endl;
        cout << "HP: " << hp << endl;
        cout << "공격력: " << power << endl;
        cout << "방어력: " << defence << endl;
        cout << "처치 시 경험치: " << expReward << " EXP" << endl;
    }

    void takeDamage(int damage)
    {
        hp -= damage;
        if (hp < 0) hp = 0;
    }

    string getName() { return name; }
    int getHp() { return hp; }
    int getPower() { return power; }
    int getDefence() { return defence; }
    string getDropItemName() { return dropItemName; }
    int getDropItemPrice() { return dropItemPrice; }
    int getExpReward() { return expReward; }

    void attack(Player* player)
    {
        int damage = power - player->getDefence();

        // 방어력≥공격력일 땐
        // 데미지가 0 이하가 되므로 최소 데미지 15를 적용 (레벨업 감안.기존 데미지에서 +5)

        if (damage <= 0)
        {
            damage = 15;
        }
        player->setHp(player->getHp() - damage);
        if (player->getHp() < 0) player->setHp(0);

        cout << name << "이(가) 공격합니다!\n";
        cout << damage << "의 데미지를 입었습니다!XoX\n";
        cout << "플레이어 잔여 HP : " << player->getHp() << endl;
    }
};

int InputStat(string statName, int minValue, int maxValue)
{
    int value;
    while (true)
    {
        cout << statName << "을(를) 입력하세요 (" << minValue << "~" << maxValue << "): ";
        cin >> value;

        if (cin.fail())
        {
            cout << "숫자만 입력하세요.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (value < minValue || value > maxValue)
        {
            cout << minValue << "부터 " << maxValue << " 사이의 값을 입력하세요.\n";
            continue;
        }

        if (value % 5 != 0)
        {
            cout << "양수이면서 5의 배수만 입력하세요.\n";
            continue;
        }

        break;
    }
    return value;
}

int InputMenuChoice(int minValue, int maxValue)
{
    int choice;
    while (true)
    {
        cout << "선택:";
        cin >> choice;

        if (cin.fail())
        {
            cout << "숫자로 입력하세요.☆\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice < minValue || choice > maxValue)
        {
            cout << minValue << "부터 " << maxValue << " 사이의 번호를 선택하세요.☆\n";
            continue;
        }

        return choice;
    }
}

int main()
{
    int HPPotion = 0;
    int MPPotion = 0;
    setPotion(5, &HPPotion, &MPPotion);
    cout << "[초기 설정 완료] HP 포션: " << HPPotion << "개, MP 포션: " << MPPotion << "개\n\n";

    string name;
    int stats[4];
    vector<Item> inventory;
    AlchemyWorkshop workshop;

    cout << "캐릭터 이름을 입력하세요^*^: ";
    cin >> name;

    stats[0] = InputStat("HP", 1, 100);
    stats[1] = InputStat("MP", 1, 100);
    stats[2] = InputStat("공격력", 1, 50);
    stats[3] = InputStat("방어력", 1, 50);

    Player* player = nullptr;

    cout << "\n===== 직업 선택 =====\n";
    cout << "1. 검사\n";
    cout << "2. 마법사\n";
    cout << "3. 성기사\n";

    int jobChoice = InputMenuChoice(1, 3);
    switch (jobChoice)
    {
    case 1:
        player = new Swordmaster(name, stats[0], stats[1], stats[2], stats[3]);
        break;
    case 2:
        player = new Magician(name, stats[0], stats[1], stats[2], stats[3]);
        break;
    case 3:
        player = new Paladin(name, stats[0], stats[1], stats[2], stats[3]);
        break;
    }

    player->printPlayerStatus();

    while (true)
    {
        cout << "\n====== 메인 5메뉴 ======\n";
        cout << " 1. 상태 확인 ^0^ \n";
        cout << " 2. 전투 진입 0o0\n";
        cout << " 3. 인벤토리 확인 OuO\n";
        cout << " 4. 포션 제작 +u< \n";
        cout << " 0. 종료 ^-^ \n";

        int menuChoice = InputMenuChoice(0, 5);

        switch (menuChoice)
        {
        case 1:
            player->printPlayerStatus();
            cout << "보유 HP 포션: " << HPPotion << "개 | 보유 MP 포션: " << MPPotion << "개\n";
            break;

        case 2:
        {
            cout << "\n===== 몬스터 선택 =====\n";
            cout << "1. 슬라임+_+\n";
            cout << "2. 고블린*h*\n";

            int monsterChoice = InputMenuChoice(1, 2);

            Monster monster("슬라임+_+", 30, 20, 10, "끈적한 젤리", 20, 30);

            if (monsterChoice == 2)
            {
                monster = Monster("고블린*h*", 50, 25, 15, "낡은 단검", 40, 50);
            }

            monster.printMonsterStatus();

            cout << "\n[ 전투 시작! ] "
                << player->getName() << "(" << player->getJob() << ")"
                << " vs " << monster.getName() << endl;

            while (player->getHp() > 0 && monster.getHp() > 0)
            {
                // =============================================
                // 도전 STEP 4 : 매 턴 행동 선택 (1. 공격 / 2. 아이템 사용)
                // =============================================
                cout << "\n--- 플레이어 턴 ---\n";
                cout << "1. 공격\n";
                cout << "2. 아이템 사용\n";

                int actionChoice = InputMenuChoice(1, 2);

                if (actionChoice == 1)
                {
                    player->attack();

                    int playerDamage = player->getPower() - monster.getDefence();
                    if (playerDamage <= 0) playerDamage = 1;

                    monster.takeDamage(playerDamage);
                    cout << monster.getName() << "에게 " << playerDamage << "의 데미지!\n";
                    cout << monster.getName() << " HP: " << monster.getHp() << endl;
                }
                else if (actionChoice == 2)
                {
                    cout << "\n[ 인벤토리 ]\n";
                    cout << "1. HP 포션 (" << HPPotion << "개 보유)\n";
                    cout << "2. MP 포션 (" << MPPotion << "개 보유)\n";

                    int itemChoice = InputMenuChoice(1, 2);

                    if (itemChoice == 1)
                    {
                        if (HPPotion > 0)
                        {
                            if (player->useHpPotion())
                            {
                                HPPotion--;
                            }
                        }
                        else
                        {
                            cout << "HP 포션이 부족합니다!\n";
                            continue; // 턴 소비 없이 다시 선택
                        }
                    }
                    else if (itemChoice == 2)
                    {
                        if (MPPotion > 0)
                        {
                            if (player->useMpPotion())
                            {
                                MPPotion--;
                            }
                        }
                        else
                        {
                            cout << "MP 포션이 부족합니다!\n";
                            continue; // 턴 소비 없이 다시 선택
                        }
                    }
                }

                if (monster.getHp() <= 0) break;

                // 몬스터 턴
                cout << "\n--- 몬스터 턴 ---\n";
                monster.attack(player);
            }

            if (monster.getHp() <= 0)
            {
                cout << "\n★ 전투 승리! ★\n";

                Item droppedItem;
                droppedItem.name = monster.getDropItemName();
                droppedItem.price = monster.getDropItemPrice();

                inventory.push_back(droppedItem);

                cout << monster.getName() << "을(를) 처치했습니다!★\n";
                cout << "획득 아이템 : " << monster.getDropItemName() << endl;
                cout << "판매 가격 : " << monster.getDropItemPrice() << " Gold\n";
                cout << "인벤토리에 저장되었습니다!\n";

                player->gainExp(monster.getExpReward());
            }
            else if (player->getHp() <= 0)
            {
                cout << "\nT_T전투에서 패배했습니다.T_T\n";
            }
            break;
        }

        case 3:
        {
            cout << "\n===== 인벤토리 (" << inventory.size() << "/10) =====\n";

            if (inventory.empty())
            {
                cout << "인벤토리가 비어 있습니다.\n";
            }
            else
            {
                int itemNumber = 1;
                for (const Item& item : inventory)
                {
                    cout << itemNumber << ". ";
                    item.PrintInfo();
                    itemNumber++;
                }
            }
            break;
        }

        case 4:
        {
            bool isWorkshopOpen = true;

            while (isWorkshopOpen)
            {
                cout << "\n===== 포션 제작소 =====\n";
                cout << "1. 전체 레시피 보기\n";
                cout << "2. 포션 이름으로 검색\n";
                cout << "3. 재료로 검색\n";
                cout << "0. 돌아가기\n";

                int workshopChoice = InputMenuChoice(0, 3);

                switch (workshopChoice)
                {
                case 1:
                    workshop.ShowAllRecipes();
                    break;

                case 2:
                {
                    string potionName;
                    cout << "검색할 포션 이름: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, potionName);
                    workshop.SearchByName(potionName);
                    break;
                }

                case 3:
                {
                    string ingredient;
                    cout << "검색할 재료 이름: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, ingredient);
                    workshop.SearchByIngredient(ingredient);
                    break;
                }

                case 0:
                    cout << "메인 메뉴로 돌아갑니다.\n";
                    isWorkshopOpen = false;
                    break;

                default:
                    cout << "잘못된 메뉴입니다.\n";
                    break;
                }
            }
            break;
        }

        case 0:
            cout << "게임을 종료합니다.\n";
            delete player;
            player = nullptr;
            return 0;

        default:
            cout << "잘못된 메뉴입니다.\n";
            break;
        }
    }
}