/*
 * 実践・自然言語s処理シリーズ第2巻　形態素解析の理論と実装
 *
 * Darts-cloneは下記リポジトリよりdarts.hを持ってきてください
 * https://github.com/s-yata/darts-clone
 */
#include <iostream>
#include <string>
#include <vector>
#include "darts.h"

int OneCharLen(const char* src) {
    return "\1\1\1\1\1\1\1\1\1\1\1\1\2\2\3\4"[(*src & 0xFF) >> 4];
}

int main(int argc, char **argv) {
    Darts::DoubleArray da;
    da.open("dictionary.data");
    // 検索結果を保持する配列（長さ, 値のペアの配列）
    constexpr int results_size = 512;
    Darts::DoubleArray::result_pair_type results[results_size];
    std::string line;
    while (std::getline(std::cin, line)) {
        const char *begin = line.data();
        const char *end = line.data() + line.size();
        while (begin < end) {
            const size_t size = da.commonPrefixSearch(
                begin, results, results_size,
                static_cast<size_t>(begin - end));
            // 見つかった単語と対応する値を出力
            for (size_t i = 0; i < size; ++i) {
                std::cout.write(begin, results[i].length);
                std::cout << " " << results[i].value << std::endl;
            }
            begin += OneCharLen(begin);
        }
    }
}
