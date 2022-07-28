#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *replaceSpace(char *s) {
    int length = strlen(s);

    int spaceCount = 0;

    // 判读字符串中有多少个空格
    for (int i = 0; i < length; i++) {
        if (s[i] == ' ') {
            spaceCount++;
        }
    }

    char replaceSpaceStr[] = "%20";
    // 申请需要扩充的大小
    int dilitationCount = (strlen(replaceSpaceStr) - 1) * spaceCount;
    // 新内存的大小
    int totalCount = dilitationCount + length;

    // 申请新的内存
    char *newAddr = malloc(totalCount + 1);

    if (newAddr == NULL) {
        assert(newAddr != NULL);
    }

    // 遍历复制
    // int j = 0;
//   printf("totalCount: %d \n", totalCount);

    for (int i = 0, j = 0; i < totalCount; i++, j++) {
        if (s[j] == ' ') {
            //   printf("res:%d, char: %c , j: %d\n", i, s[i], j);
            newAddr[i] = '%';
            newAddr[i + 1] = '2';
            newAddr[i + 2] = '0';
            i += 2;
        } else {
            newAddr[i] = s[j];
        }
    }

    return newAddr;


    // newAddr[newCur+1] = '\0';

//   printf("res:%s \n", newAddr);

//   free(newAddr);
//   newAddr = NULL;


}

int main(int argc, char const *argv[]) {
    /* code */
    char str[] = "We are happy.";

    char *res = replaceSpace(str);

    printf("res: %s", res);
    return 0;
}
