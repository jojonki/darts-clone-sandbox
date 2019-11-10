/*
 * 実践・自然言語s処理シリーズ第2巻　形態素解析の理論と実装
 * 図4.7 Darts-cloneによるダブル配列の構築，の実装を利用
 *
 * Darts-cloneは下記リポジトリよりdarts.hを持ってきてください
 * https://github.com/s-yata/darts-clone
 *
 * 語彙としてmecab-ipadic-2.7.0-20070801から，392,126件の語彙辞書を作成
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "darts.h"

int main(int argc, char **argv) {
    // dic.txt から単語リストを読み込む
    std::string line;
    std::vector<std::string> dic;
    std::ifstream ifs("ipadic-vocab.txt");
    while (std::getline(ifs, line)) {
        dic.emplace_back(line);
    }
    // 単語リストを辞書順に整列
    std::sort(dic.begin(), dic.end());
    // Darts の入力にコピー．
    std::vector<const char *> key;
    std::vector<int> value;
    for (size_t i = 0; i < dic.size(); ++i) {
        key.emplace_back(dic[i].c_str());
        value.emplace_back(i); // 辞書順の番号
    }
    // ダブル配列の作成
    // 引数: 見出し語数, 整列済み見出し語の配列,
    // 見出し語長の配列（nullptr のときはstd::strlen() を使用）,
    // 値の配列
    std::cout << "Building a double-array" << std::endl;
    Darts::DoubleArray da;
    const clock_t begin_time = std::clock();
    da.build(key.size(),
        const_cast<char **>(key.data()), nullptr, value.data());
    std::cout << "Finished to build your double-array. (" 
            << float( clock () - begin_time ) /  CLOCKS_PER_SEC
            << " sec)" << std::endl;
    // 構築された辞書をファイルに保存
    da.save("dictionary.data");

    return 0;
}
