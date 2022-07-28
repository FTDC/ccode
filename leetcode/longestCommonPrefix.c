#include <stdio.h>
#include <string.h>

char *longestCommonPrefix(char **strs, int strsSize) {
    int flag = 0;

    //   char prefix[] = "";
    // 直接判断第一个，和后面的字符串每一个对比
    int firstLen = strlen(strs[0]);
    for (int i = 0; i < firstLen; i++) {
        for (int j = 0; j < strsSize; j++) {
            if (strs[0][i] != strs[j][i]) {
                flag = 1;
                strs[0][i] = '\0';
                break;
            }
        }

        if (flag > 0) {
            break;
        }
    }

    return strs[0];
}

int main() {

    char strs[][10] = {"flower", "flow", "flight"};
    char *p[3];
    p[0] = strs[0];
    p[1] = strs[1];
    p[2] = strs[2];

    char *res = longestCommonPrefix(p, 3);

    printf("%s \n", res);

    return 0;
}