// noTitle.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

//コード内容：シューティングゲーム的なもの
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//マップ：10行15列の横長マップ
#define sizeH 10
#define sizeW 20
#define HP 3

//マップの出力関数
void output_map(char map[sizeH][sizeW]) {
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
            if (i == 5 && j == 0) {
                map[i][j] = 'A';
            }

            //敵機の配置
            else if (j == 19) {
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

//ゲーム開始時に初期化が必要なものは関数内、それ以外はmain内に記述
int main()
{
    //乱数生成用
    srand((unsigned int)time(NULL));

    //マップの作成
    char map[sizeH][sizeW]; //ゲームマップ

    //ゲーム開始
    int i = 0;

    while (i == 0) {
        //マップの初期化
        map_reset(map);
        output_map(map);
        i++;

        //
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
