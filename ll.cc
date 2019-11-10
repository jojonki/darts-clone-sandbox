/*
 * 実践・自然言語s処理シリーズ第2巻　形態素解析の理論と実装
 *
 * Darts-cloneは下記リポジトリよりdarts.hを持ってきてください
 * https://github.com/s-yata/darts-clone
 */
#include <algorithm>
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
            size_t longest_length = 0;
            // 最長の単語を探す
            for (size_t i = 0; i < size; ++i) {
                longest_length =
                    std::max(longest_length, results[i].length);
            }
            // 辞書引きに失敗したときは，1 文字を単語とみなす
            if (longest_length == 0) {
                longest_length = OneCharLen(begin);
            }
            // 最長の単語と空白を出力
            std::cout.write(begin, longest_length);
            std::cout << ' ';
            // 次の検索開始位置までずらす
            begin += longest_length;
        }
        std::cout << std::endl;
    }
}
