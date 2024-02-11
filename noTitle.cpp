// noTitle.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

//コード内容：シューティングゲーム的なもの
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//マップ：10行20列の縦長マップ
#define sizeH 20
#define sizeW 10
#define HP 3

void func_attack(char [][sizeW]);
int can_move(char [][sizeW], char);
void func_move(char[][sizeW], int, int, int, int);

//マップの出力関数
void output_map(char map[sizeH][sizeW]) {
    putchar('\n');

    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            printf("%c", map[i][j]);
        }
        putchar('\n');
    }
}

//マップの初期化関数
void map_reset(char map[sizeH][sizeW]) {
    int temp = 0; //乱数の受け取り用

    for (int i = 0; i < sizeH; i++) {
        for (int j = 0; j < sizeW; j++) {
            //自機の配置
            if (i == 19 && j == 5) {
                map[i][j] = 'A';
            }

            //敵機の配置
            else if (i == 0) {
                temp = rand() % 3; //０～２

                //1/3の確率で敵を配置
                if (temp == 0) {
                    map[i][j] = 'e'; //小型敵機
                }
                else {
                    map[i][j] = '~'; //空白部分
                }
            }

            //空白部分の配置
            else {
                map[i][j] = '~';
            }
        }
    }
}

//入力の取得関数
int input_line(char map[sizeH][sizeW]) {
    char input; //入力を受け取る
    int checkMove = 0; //移動可否判定用

    //自機の操作
    scanf_s("%c%*[^\n]", &input, 1); //不要な入力を除く
    //printf("input = %c\n", input);

    //攻撃関数の呼び出し
    if (input == 'a') {
        func_attack(map);
        return 1;
    }

    //移動関数の呼び出し
    else if (input == 'r' || input == 'l' || input == 'u' || input == 'd') {
        //printf("\ninput = %c\n", input);
        checkMove = can_move(map, input);

        //移動可能
        if (checkMove == 1) {
            return 1;
        }

        //移動不可能
        else if(checkMove == 0) {
            printf("\n移動不可能です\n");
            return 0;
        }

        //例外
        else {
            printf("\nゲーム終了 : func_move\n");
            exit(0);
        }
        
    }

    //違法な入力：入力のやり直し
    else {
        //表示メッセージ
        printf("\n違法な入力です\n");
        return 0;
    }
}

//自機の攻撃処理関数
void func_attack(char map[sizeH][sizeW]) {
    //自機の探索
    int i = 0;
    int j = 0;
    while (i < sizeH) {
        while (j < sizeW) {
            //攻撃処理
            if (map[i][j] == 'A') {
                map[i][j + 1] = '>';

                //処理終了
                i = sizeH;
                j = sizeW;
            }
            else {
                i++;
                j++;
            }
        }
    }
}

//自機の移動可否判定関数
int can_move(char map[sizeH][sizeW], char dir) {
    int i = sizeH - 1;
    int j = 0;
    
    while (i >= 0) {
        while (j >= 0) {
            //自機の探索
            if (map[i][j] == 'A') {
                //右移動
                if (dir == 'r') {
                    //map内か
                    if (j + 1 < sizeW) {
                        //printf("\ndir = %c\n", dir);
                        func_move(map, i, j, i, j + 1);
                        return 1;
                    }
                    //map外
                    else {
                        return 0;
                    }
                }

                //左移動
                else if (dir == 'l') {
                    if (j - 1 >= 0) {
                        func_move(map, i, j, i, j - 1);
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
                
                //上移動
                else if (dir == 'u') {
                    if (i - 1 >= 0) {
                        func_move(map, i, j, i - 1, j);
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
                
                //下移動
                else if (dir == 'd') {
                    if (i + 1 < sizeH) {
                        func_move(map, i, j, i + 1, j);
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
            }
            else {
                //printf("\else\n");
                j++;
            }
        }
        i--;
        j = 0;
    }

    //自機が存在しない場合：例外
    printf("\nゲーム終了 : can_move\n");
    exit(0);
}

//自機の移動処理関数
void func_move(char map[sizeH][sizeW], int currY, int currX, int nextY, int nextX) {
    char temp;

    //位置の入れ替え
    temp = map[nextY][nextX];
    map[nextY][nextX] = map[currY][currX];
    map[currY][currX] = temp;
}

//ゲーム中の処理を行う関数
void now_gaming(char map[sizeH][sizeW]) {
    //マップの初期化
    map_reset(map);
    output_map(map);

    int checkInput = 0; //入力の取得ができているかのチェック
    while (1) {
        //入力の受け取り
        while (checkInput == 0) {
            //入力取得関数の呼び出し
            checkInput = input_line(map); //return 1で成功
            //printf("checkInput = %d\n", checkInput);
        }

        //output_map(map);
        //exit(0);

        //敵の行動

    }
}

//ゲーム開始時に初期化が必要なものは関数内、それ以外はmain内に記述
int main()
{
    //乱数生成用
    srand((unsigned int)time(NULL));

    //マップの作成
    char map[sizeH][sizeW]; //ゲームマップ

    //ゲーム開始

    while (1) {
        //ゲーム開始関数
        now_gaming(map);
    }

    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
