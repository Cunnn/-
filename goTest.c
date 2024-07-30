#include <stdio.h>
#include <string.h>

#define MAX_CORES 1000
#define MAX_SKILLS 10
#define MODE_ONE_CORES 4
#define MODE_ONE_SKILLS 6
#define MODE_TWO_CORES 6
#define MODE_TWO_SKILLS 9

typedef struct {
    int skills[MAX_SKILLS];
    int skillOrder[3];
} Core;

void modeOne(Core core[], int coreCount, char enumerate);
void modeTwo(Core core[], int coreCount, char enumerate);
void parseInput(Core core[], int *coreCount, const char *s);
void printCores(const Core core[], int coreCount);
void printSolution(int hold[], int coreCount, int skillCount, const Core core[]);
int checkSolution(int selected[], int skills);

int main() {
    char mode = '1';  // 設置模式
    char enumerate = '2';  // 設置是否列舉
    printf("楓之谷完美核心組合\n\n");
    
    // char s[] = "231,145,163,654,124,245,236,124,235,612,135,234,136,346,236,356,134,543";
    char s[] = "521,631,361,271,731,871,581,541,761,971,631,941,361,781,791,813,423,623,743,853,913,893,593,573,983,923,273,483,593,213,693,123,273,725,725,645,945,735,265,435,645,375,625,625,325,235,785,425,465,725,285,385,975,835,375,945,735,215,634,174,514,654,514,984,584,174,584,174,894,394,294,314,184,724,294,417,127,537,637,567,897,837,917,697,597,367,917,157,417,957,927,967,347,647,247,687,457,317,157,457,867,197,186,146,176,716,176,386,836,926,376,836,316,826,526,236,196,746,746,246,176,246,469,419,259,839,389,269,279,129,569,129,139,849,869,719.279,179,749,138,648,928,538,658,358,248,168,852,762,892,752,782,672,482,982,562,452,162,672,592,432,812,782,562";
    
    Core core[MAX_CORES];
    int coreCount = 0;
    
    parseInput(core, &coreCount, s);
    printCores(core, coreCount);
    
    if (mode == '2') {
        modeOne(core, coreCount, enumerate);
    } else {
        modeTwo(core, coreCount, enumerate);
    }
    
    getchar();
    return 0;
}

void parseInput(Core core[], int *coreCount, const char *s) {
    const char *p = s;
    *coreCount = 0;
    while (*p) {
        if (*p == ',') {
            p++;
            continue;
        }
        for (int i = 0; i < MAX_SKILLS; i++) {
            core[*coreCount].skills[i] = 0;
        }
        for (int i = 0; i < 3 && *p != '\0' && *p != ','; i++) {
            core[*coreCount].skillOrder[i] = *p - '0';
            core[*coreCount].skills[*p - '0'] = 1;
            p++;
        }
        (*coreCount)++;
    }
}

void printCores(const Core core[], int coreCount) {
    printf("列出所有核心並標示編號...\n");
    for (int i = 0; i < coreCount; i++) {
        printf("核心編號:%d, [ ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("%d ", core[i].skillOrder[j]);
        }
        printf("]\n");
    }
}

void printSolution(int hold[], int coreCount, int skillCount, const Core core[]) {
    printf("\n找到一組%d核%d技!\n", coreCount, skillCount);
    for (int i = 0; i < coreCount; i++) {
        printf("核心編號:%d, [ ", hold[i] + 1);
        for (int j = 0; j < 3; j++) {
            printf("%d ", core[hold[i]].skillOrder[j]);
        }
        printf("]\n");
    }
    printf("\n");
}

int checkSolution(int selected[], int skills) {
    for (int i = 1; i <= skills; i++) {
        if (selected[i] != 2) {
            return 0;
        }
    }
    return 1;
}

void modeOne(Core core[], int coreCount, char enumerate) {
    int selected[MAX_SKILLS] = {0};
    int hold[MODE_ONE_CORES];
    for (int i = 0; i < coreCount; i++) {
        memset(selected, 0, sizeof(selected));
        for (int a = 0; a < 3; a++) selected[core[i].skillOrder[a]]++;
        hold[0] = i;
        for (int j = 0; j < coreCount; j++) {
            if (j == i) continue;
            for (int a = 0; a < 3; a++) selected[core[j].skillOrder[a]]++;
            hold[1] = j;
            for (int k = 0; k < coreCount; k++) {
                if (k == i || k == j) continue;
                for (int a = 0; a < 3; a++) selected[core[k].skillOrder[a]]++;
                hold[2] = k;
                for (int l = 0; l < coreCount; l++) {
                    if (l == i || l == j || l == k) continue;
                    for (int a = 0; a < 3; a++) selected[core[l].skillOrder[a]]++;
                    hold[3] = l;
                    if (checkSolution(selected, MODE_ONE_SKILLS)) {
                        printSolution(hold, MODE_ONE_CORES, MODE_ONE_SKILLS, core);
                        if (enumerate == '2') return;
                    }
                    for (int a = 0; a < 3; a++) selected[core[l].skillOrder[a]]--;
                }
                for (int a = 0; a < 3; a++) selected[core[k].skillOrder[a]]--;
            }
            for (int a = 0; a < 3; a++) selected[core[j].skillOrder[a]]--;
        }
    }
    printf("\ndone(並未搜尋出符合的完美核心，請繼續努力蒐集)\n");
}

void modeTwo(Core core[], int coreCount, char enumerate) {
    int selected[MAX_SKILLS] = {0};
    int hold[MODE_TWO_CORES];
    for (int i = 0; i < coreCount; i++) {
        memset(selected, 0, sizeof(selected));
        for (int a = 0; a < 3; a++) selected[core[i].skillOrder[a]]++;
        hold[0] = i;
        for (int j = 0; j < coreCount; j++) {
            if (j == i) continue;
            for (int a = 0; a < 3; a++) selected[core[j].skillOrder[a]]++;
            hold[1] = j;
            for (int k = 0; k < coreCount; k++) {
                if (k == i || k == j) continue;
                for (int a = 0; a < 3; a++) selected[core[k].skillOrder[a]]++;
                hold[2] = k;
                for (int l = 0; l < coreCount; l++) {
                    if (l == i || l == j || l == k) continue;
                    for (int a = 0; a < 3; a++) selected[core[l].skillOrder[a]]++;
                    hold[3] = l;
                    for (int m = 0; m < coreCount; m++) {
                        if (m == i || m == j || m == k || m == l) continue;
                        for (int a = 0; a < 3; a++) selected[core[m].skillOrder[a]]++;
                        hold[4] = m;
                        for (int n = 0; n < coreCount; n++) {
                            if (n == i || n == j || n == k || n == l || n == m) continue;
                            for (int a = 0; a < 3; a++) selected[core[n].skillOrder[a]]++;
                            hold[5] = n;
                            if (checkSolution(selected, MODE_TWO_SKILLS)) {
                                printSolution(hold, MODE_TWO_CORES, MODE_TWO_SKILLS, core);
                                if (enumerate == '2') return;
                            }
                            for (int a = 0; a < 3; a++) selected[core[n].skillOrder[a]]--;
                        }
                        for (int a = 0; a < 3; a++) selected[core[m].skillOrder[a]]--;
                    }
                    for (int a = 0; a < 3; a++) selected[core[l].skillOrder[a]]--;
                }
                for (int a = 0; a < 3; a++) selected[core[k].skillOrder[a]]--;
            }
            for (int a = 0; a < 3; a++) selected[core[j].skillOrder[a]]--;
        }
    }
    printf("\ndone(並未搜尋出符合的完美核心，請繼續努力蒐集)\n");
}
