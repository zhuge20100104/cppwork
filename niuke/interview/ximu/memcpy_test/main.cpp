#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

static int const MAX_LEN = 128;
static int const SRC_LEN = 6;

struct CopyItem {
    char* src;
    char* dst;

    int src_offset;
    int dst_offset;
    int copy_len;

    bool is_source{false};
};

void recover_source_and_dst(char* src, char* dst) {
    for (int i = 0; i < SRC_LEN; ++i) {
        if (i == SRC_LEN - 1) {
            src[i] = '\0';
        } else {
            src[i] = 'a' + i;
        }
    }
    
    memset(dst, 0, sizeof(dst));
}

int get_copy_len(CopyItem const& test_case) {
    auto copy_l = test_case.copy_len;
    auto copy_len = copy_l == -1 ? strlen(test_case.src) + 1 : copy_l;
    return copy_len;
}

int main(int argc, char* argv[]) {
    char src[SRC_LEN] = "abcde";
    char dst[MAX_LEN] = {0};

    vector<CopyItem> positive_test_cases{
        /* Case 1： src里面的所有字符拷贝到 dst，一把梭*/
        CopyItem{src, dst, 0, 0, -1, false},
        /* Case 2:  src里面的前三个字符拷贝回src, 还是abcde, 不会出现内存错误  */
        CopyItem{src, src, 0, 0, 3, true},
        /* Case 3:  src从第二个字符开始，拷贝三个字符到src，输出结果 cdede，不会出现内存错误 */
        CopyItem{src, src, 2, 0, 3, true},
        /* Case 4:  src拷一部分到dst, 应该没问题 */
        CopyItem{src, dst, 2, 0, 3, false}
    };

    for (auto const& test_case : positive_test_cases) {
        auto copy_len = get_copy_len(test_case);

        memcpy((char*)test_case.dst + test_case.dst_offset,
               (char*)test_case.src + test_case.src_offset, copy_len);
        char* res = test_case.is_source ? test_case.src : test_case.dst;

        cout << "Dest: " << res << endl;
        recover_source_and_dst(src, dst);
    }

    vector<CopyItem> negative_test_cases{
        /* Case 5: 把src拷贝到空串，没有足够存储空间，看能不能拷，这里应该崩 */
        CopyItem{src, (char*)"", 0, 0, -1, false},
        /* Case 6: 把src拷贝到nullptr, 空指针， 看能不能拷， 这里应该崩 */
        CopyItem{src, nullptr, 0, 0, -1, false}
    };

    for (auto const& test_case : negative_test_cases) {
        auto copy_len = get_copy_len(test_case);

        memcpy((char*)test_case.dst + test_case.dst_offset,
               (char*)test_case.src + test_case.src_offset, copy_len);
        char* res = test_case.is_source ? test_case.src : test_case.dst;

        cout << "Dest: " << res << endl;
    }


    return EXIT_SUCCESS;
}